#include "render_manager.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

// Capturing reflection texture
void RenderManager::_captureSceneReflections(CameraManager& camera)
{
	// Check if water reflection needed
	bool waterReflectionsNeeded = (_renderBus.isWaterEffectsEnabled() && _entityBus->getWaterEntity() != nullptr) &&
		_entityBus->getWaterEntity()->isReflective();

	// Search for a reflective GAME entity
	bool anyReflectiveEntityFound = false;
	if (!waterReflectionsNeeded)
	{
		for (auto& [keyID, gameEntity]: _entityBus->getGameEntities())
		{
			if (gameEntity->isSceneReflective() && gameEntity->isVisible())
			{
				anyReflectiveEntityFound = true;
				break;
			}
		}
	}

	// Check if scene reflection needed (and not occupied by water rendering)
	bool sceneReflectionsNeeded = _renderBus.isSceneReflectionsEnabled() && anyReflectiveEntityFound && !waterReflectionsNeeded;
	
	// Check if needed to capture scene
	if (waterReflectionsNeeded || sceneReflectionsNeeded)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (camera.getPosition().y - _renderBus.getSceneReflectionHeight());

		// Start capturing reflections
		_sceneReflectionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Save and hide reflective GAME entities
		vector<string> reflectiveGameEntityIDs;
		if (sceneReflectionsNeeded)
		{
			for (auto& [keyID, gameEntity]: _entityBus->getGameEntities())
			{
				if (gameEntity->isSceneReflective() && gameEntity->isVisible())
				{
					gameEntity->setVisible(false);
					reflectiveGameEntityIDs.push_back(gameEntity->getID());
				}
			}
		}

		// Change camera angle
		Vec3 cameraPos = camera.getPosition();
		Vec3 newCameraPos = Vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool shadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Normalmapping are performance-heavy with little visual impact on reflections, so they should not appear
		bool normalMappingEnabled = _renderBus.isNormalMappingEnabled();
		_renderBus.setNormalMappingEnabled(false);

		// Sky HDR must not appear in reflections
		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

		// Render sky
		_renderSkyEntity();

		// Render terrain
		glEnable(GL_CLIP_DISTANCE0);
		_renderTerrainEntity();
		glDisable(GL_CLIP_DISTANCE0);

		// Render game & billboard entities only for scene reflections
		if (sceneReflectionsNeeded)
		{
			_renderGameEntities();
			_renderBillboardEntities();
		}

		// Revert reflection exceptions
		_renderBus.setShadowsEnabled(shadowsEnabled);
		_renderBus.setNormalMappingEnabled(normalMappingEnabled);
		if (skyEntity != nullptr)
		{ 
			skyEntity->setLightness(oldLightness);
		}

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = Vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Restore reflective GAME entities
		if (sceneReflectionsNeeded)
		{
			for (auto& [keyID, gameEntity] : _entityBus->getGameEntities()) // Loop over all GAME entities
			{
				for (auto& reflectiveID : reflectiveGameEntityIDs) // Loop over all reflective GAME entities
				{
					if (gameEntity->getID() == reflectiveID) // Check if IDs match
					{
						gameEntity->setVisible(true);
					}
				}
			}
		}

		// Stop capturing reflections
		_sceneReflectionFramebuffer.unbind();

		// Assign texture
		_renderBus.setSceneReflectionMap(_sceneReflectionFramebuffer.getTexture(0));
	}
}

// Capturing water refraction texture
void RenderManager::_captureSceneRefractions()
{
	// Temporary values
	bool waterRefractionEnabled = (_renderBus.isWaterEffectsEnabled() &&_entityBus->getWaterEntity() != nullptr) && 
		_entityBus->getWaterEntity()->isRefractive();

	if (waterRefractionEnabled)
	{
		// Bind
		_sceneRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render whole scene
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderGameEntities();
		_renderBillboardEntities();

		// Unbind
		_sceneRefractionFramebuffer.unbind();

		// Assign texture
		_renderBus.setSceneRefractionMap(_sceneRefractionFramebuffer.getTexture(0));
	}
}

// Capturing shadows
void RenderManager::_captureShadows()
{
	if (_renderBus.isShadowsEnabled())
	{
		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_shadowRenderer.bind();

		// Render GAME entities
		auto allGameEntities = _entityBus->getGameEntities();
		for (auto& [keyID, gameEntity] : allGameEntities)
		{
			// Check if LOD entity needs to be rendered
			if (gameEntity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				auto foundPair = allGameEntities.find(gameEntity->getLodEntityID());
				if (foundPair != allGameEntities.end())
				{
					auto lodEntity = foundPair->second;

					// Save original transformation
					Vec3 originalPosition = lodEntity->getTranslation();
					Vec3 originalRotation = lodEntity->getRotation();
					Vec3 originalSize = lodEntity->getScaling();
					bool originalVisibility = lodEntity->isVisible();

					// Change transformation
					lodEntity->setTranslation(gameEntity->getTranslation());
					lodEntity->setRotation(gameEntity->getRotation());
					lodEntity->setScaling((gameEntity->getScaling() / gameEntity->getOriginalScaling()) * originalSize);
					lodEntity->setVisible(gameEntity->isVisible());
					lodEntity->updateModelMatrix();

					// Render LOD entity
					_shadowRenderer.render(lodEntity);

					// Revert to original transformation
					lodEntity->setTranslation(originalPosition);
					lodEntity->setRotation(originalRotation);
					lodEntity->setScaling(originalSize);
					lodEntity->setVisible(originalVisibility);
					lodEntity->updateModelMatrix();
				}
				else
				{
					Logger::throwError("GAME entity \"" + gameEntity->getID() + "\" has a nonexisting LOD entity \"" + gameEntity->getLodEntityID() + "\"");
				}
			}
			else // Render high-quality entity
			{
				_shadowRenderer.render(gameEntity);
			}
		}

		// Unbind
		_shadowRenderer.unbind();
		_shadowFramebuffer.unbind();
		_renderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
}

// Capturing bloom parts
void RenderManager::_captureBloom()
{
	if (_renderBus.isBloomEnabled())
	{
		// Process scene texture
		_bloomHdrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		_bloomHdrRenderer.bind();
		_bloomHdrRenderer.render(_finalSurface, _renderBus.getSceneMap());
		_bloomHdrRenderer.unbind();
		_bloomHdrFramebuffer.unbind();

		// Blur scene texture
		_blurRenderer.bind();
		_renderBus.setBloomMap(_blurRenderer.blurTexture(_finalSurface, _bloomHdrFramebuffer.getTexture(0),
			static_cast<int>(BlurType::BLOOM), _renderBus.getBloomBlurSize(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_blurRenderer.unbind();
	}
}
#include "master_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void MasterRenderer::_captureSceneReflections(Camera& camera)
{
	// Check if water reflection needed
	bool waterReflectionsNeeded = (_renderBus.isWaterEffectsEnabled() && 
		(_entityBus->getWaterEntity() != nullptr) &&
		_entityBus->getWaterEntity()->isReflective());

	// Search for any reflective model entity
	bool anyReflectiveEntityFound = false;
	if (!waterReflectionsNeeded)
	{
		for (const auto& [keyID, modelEntity]: _entityBus->getModelEntities())
		{
			if (modelEntity->isSceneReflective() && modelEntity->isVisible())
			{
				anyReflectiveEntityFound = true;
				break;
			}
		}
	}

	// Check if scene reflection needed (and not occupied by water rendering)
	bool sceneReflectionsNeeded = (_renderBus.isSceneReflectionsEnabled() && anyReflectiveEntityFound && !waterReflectionsNeeded);
	
	// Check if needed to capture scene
	if (waterReflectionsNeeded || sceneReflectionsNeeded)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (camera.getPosition().y - _renderBus.getSceneReflectionHeight());

		// Start capturing reflections
		_sceneReflectionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Only if scene reflections enabled
		vector<string> savedModelEntityIDs;
		if (sceneReflectionsNeeded)
		{
			// Iterate through all MODEL entities
			for (const auto& [keyID, modelEntity]: _entityBus->getModelEntities())
			{
				// Check if necessary to hide
				if (modelEntity->isSceneReflective() && modelEntity->isVisible())
				{
					// Hide MODEL entity
					modelEntity->setVisible(false);
					savedModelEntityIDs.push_back(modelEntity->getID());
				}
			}
		}

		// Iterate through all BILLBOARD entities
		vector<string> savedBillboardEntityIDs;
		for (const auto& [keyID, billboardEntity] : _entityBus->getBillboardEntities())
		{
			// Check if necessary to hide
			if (!billboardEntity->isReflected() && billboardEntity->isVisible())
			{
				// Hide BILLBOARD entity
				billboardEntity->setVisible(false);
				savedBillboardEntityIDs.push_back(billboardEntity->getID());
			}
		}

		// Change camera angle
		Vec3 cameraPos = camera.getPosition();
		Vec3 newCameraPos = Vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.setPitch(-camera.getPitch());
		camera.updateMatrices();

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Normal mapping is performance-heavy with little visual impact on reflections, so they should not appear
		bool wasNormalMappingEnabled = _renderBus.isNormalMappingEnabled();
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

		// Render model entities & billboard entities only for scene reflections
		if (sceneReflectionsNeeded)
		{
			_renderModelEntities();
			_renderBillboardEntities();
		}

		// Revert reflection exceptions
		_renderBus.setShadowsEnabled(wasShadowsEnabled);
		_renderBus.setNormalMappingEnabled(wasNormalMappingEnabled);
		if (skyEntity != nullptr)
		{ 
			skyEntity->setLightness(oldLightness);
		}

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = Vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.setPitch(-camera.getPitch());
		camera.updateMatrices();

		// Only if scene reflections enabled
		if (sceneReflectionsNeeded)
		{
			// Iterate through all MODEL entities
			for (const auto& [keyID, modelEntity] : _entityBus->getModelEntities())
			{
				// Iterate through all saved MODEL entities
				for (const auto& reflectiveID : savedModelEntityIDs)
				{
					// Check if IDs match
					if (modelEntity->getID() == reflectiveID)
					{
						// Show MODEL entity again
						modelEntity->setVisible(true);
					}
				}
			}
		}

		// Iterate through all BILLBOARD entities
		for (const auto& [keyID, billboardEntity] : _entityBus->getBillboardEntities())
		{
			// Iterate through all saved BILLBOARD entities
			for (const auto& savedID : savedBillboardEntityIDs)
			{
				// Check if IDs match
				if (billboardEntity->getID() == savedID)
				{
					// Show BILLBOARD entity again
					billboardEntity->setVisible(true);
				}
			}
		}

		// Stop capturing reflections
		_sceneReflectionFramebuffer.unbind();

		// Assign texture
		_renderBus.setSceneReflectionMap(_sceneReflectionFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureSceneRefractions()
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
		_renderModelEntities();
		_renderBillboardEntities();

		// Unbind
		_sceneRefractionFramebuffer.unbind();

		// Assign texture
		_renderBus.setSceneRefractionMap(_sceneRefractionFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureShadows()
{
	if (_renderBus.isShadowsEnabled())
	{
		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_shadowRenderer.bind();

		// Render MODEL entities
		auto allModelEntities = _entityBus->getModelEntities();
		for (const auto& [keyID, modelEntity] : allModelEntities)
		{
			// Check if LOD entity needs to be rendered
			if (modelEntity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				auto foundPair = allModelEntities.find(modelEntity->getLodEntityID());
				if (foundPair != allModelEntities.end())
				{
					auto lodEntity = foundPair->second;

					// Save original transformation
					Vec3 originalPosition = lodEntity->getTranslation();
					Vec3 originalRotation = lodEntity->getRotation();
					Vec3 originalSize = lodEntity->getScaling();
					bool originalVisibility = lodEntity->isVisible();

					// Change transformation
					lodEntity->setTranslation(modelEntity->getTranslation());
					lodEntity->setRotation(modelEntity->getRotation());
					lodEntity->setScaling((modelEntity->getScaling() / modelEntity->getOriginalScaling()) * originalSize);
					lodEntity->setVisible(modelEntity->isVisible());
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
					Logger::throwError("Model entity with ID \"" + modelEntity->getID() + "\" has a non-existing LOD entity with ID \"" + modelEntity->getLodEntityID() + "\"");
				}
			}
			else // Render high-quality entity
			{
				_shadowRenderer.render(modelEntity);
			}
		}

		// Render BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			_shadowRenderer.render(entity);
		}

		// Unbind
		_shadowRenderer.unbind();
		_shadowFramebuffer.unbind();
		_renderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureBloom()
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
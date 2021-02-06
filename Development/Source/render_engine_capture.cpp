#include "render_engine.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

#include <chrono>
#include <algorithm>

// Capturing reflection texture
void RenderEngine::_captureSceneReflections(CameraManager& camera)
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
void RenderEngine::_captureSceneRefractions()
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
void RenderEngine::_captureShadows()
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
void RenderEngine::_captureBloom()
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

void RenderEngine::_captureSceneDepth()
{
	// Temporary values
	bool waterDepthNeeded = (_renderBus.isWaterEffectsEnabled() && _entityBus->getWaterEntity() != nullptr) &&
		_entityBus->getWaterEntity()->getTransparency() > 0.0f;
	bool isUnderWater = false;
	float clippingY = -(std::numeric_limits<float>::max)();

	// Prepare water depth
	if (waterDepthNeeded)
	{
		// Check if camera is underwater
		auto waterEntity = _entityBus->getWaterEntity();
		isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getTranslation().y + waterEntity->getWaveHeightFactor()));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().x > waterEntity->getTranslation().x - (waterEntity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().x < waterEntity->getTranslation().x + (waterEntity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().z > waterEntity->getTranslation().z - (waterEntity->getSize() / 2.0f));
		isUnderWater = isUnderWater && (_renderBus.getCameraPosition().z < waterEntity->getTranslation().z + (waterEntity->getSize() / 2.0f));
		
		// Determine clipping Y based on being underwater or not
		if (isUnderWater)
		{
			clippingY = waterEntity->getTranslation().y;
		}
		else
		{
			clippingY = (waterEntity->getTranslation().y + waterEntity->getWaveHeightFactor());
		}
	}
	
	// Determine if scene depth rendering is needed or not
	if (_renderBus.isDofEnabled() || _renderBus.isLensFlareEnabled() || waterDepthNeeded)
	{
		// Bind
		_sceneDepthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_depthRenderer.bind();

		// Render TERRAIN entity
		if (_entityBus->getTerrainEntity() != nullptr)
		{
			_depthRenderer.render(_entityBus->getTerrainEntity());
		}

		// Render GAME entities
		auto allGameEntities = _entityBus->getGameEntities();
		for (auto& [keyID, gameEntity] : allGameEntities)
		{
			// Check if entity must be included in depth map
			if (gameEntity->isDepthMapIncluded())
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
						_depthRenderer.render(lodEntity, clippingY, isUnderWater);

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
					_depthRenderer.render(gameEntity, clippingY, isUnderWater);
				}
			}
		}

		// Render BILLBOARD entities
		for (auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			// Check if entity must be included in depth map
			if (entity->isDepthMapIncluded())
			{
				_depthRenderer.render(entity, clippingY, isUnderWater);
			}
		}

		// Render AABB entities
		if (_renderBus.isAabbFrameRenderingEnabled())
		{
			for (auto& [keyID, entity] : _entityBus->getAabbEntities())
			{
				_depthRenderer.render(entity, clippingY, isUnderWater);
			}
		}

		// Unbind
		_depthRenderer.unbind();
		_sceneDepthFramebuffer.unbind();
		_renderBus.setSceneDepthMap(_sceneDepthFramebuffer.getTexture(0));
	}
}

void RenderEngine::_captureDofBlur()
{
	if (_renderBus.isDofEnabled())
	{
		_blurRenderer.bind();
		_renderBus.setBlurMap(_blurRenderer.blurTexture(_finalSurface, _renderBus.getSceneMap(), 
			static_cast<int>(BlurType::DOF), 6, 1.0f, BlurDirection::BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_capturePostProcessing()
{
	// Apply bloom, DOF & lens-flare on scene texture
	_postProcessingFramebuffer.bind();
	_postRenderer.bind();
	_postRenderer.render(_finalSurface);
	_postRenderer.unbind();
	_postProcessingFramebuffer.unbind();
	_renderBus.setPostProcessedSceneMap(_postProcessingFramebuffer.getTexture(0));
}

void RenderEngine::_captureMotionBlur(CameraManager& camera)
{
	// Temporary values
	static bool firstTime = true;
	static float lastYaw;
	static float lastPitch;

	// Timing values
	static std::chrono::high_resolution_clock::time_point previousMS = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point currentMS = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(currentMS - previousMS);
	float elapsedMS = static_cast<float>(timeDifference.count()) * 1000.0f;

	// If 1 frame passed
	if (elapsedMS >= Config::getInst().getUpdateMsPerFrame() || firstTime)
	{
		// Set for next frame
		previousMS = currentMS;

		// Check if motion blur is enabled
		if (_renderBus.isMotionBlurEnabled())
		{
			// Camera speed and blur direction variables
			float xDifference = fabsf(camera.getYaw() - lastYaw) * _renderBus.getMotionBlurStrength();
			float yDifference = fabsf(camera.getPitch() - lastPitch) * _renderBus.getMotionBlurStrength();

			// Temporary values
			static BlurDirection lastDirection = BlurDirection::NONE;
			BlurDirection direction = BlurDirection::NONE;

			// Determine blur direction & mix value
			if (xDifference != 0.0f || yDifference != 0.0f)
			{
				if (xDifference >= yDifference)
				{
					direction = BlurDirection::HORIZONTAL;
					_renderBus.setMotionBlurMixValue(xDifference);
				}
				else
				{
					direction = BlurDirection::VERTICAL;
					_renderBus.setMotionBlurMixValue(yDifference);
				}
			}
			else
			{
				_renderBus.setMotionBlurMixValue(0.0f);
			}

			// Set for next iteration
			lastYaw = camera.getYaw();
			lastPitch = camera.getPitch();

			// Apply motion blur
			if (direction == BlurDirection::NONE)
			{
				_renderBus.setMotionBlurMap(_renderBus.getPostProcessedSceneMap());
			}
			else
			{
				_blurRenderer.bind();
				_renderBus.setMotionBlurMap(_blurRenderer.blurTexture(_finalSurface, _renderBus.getPostProcessedSceneMap(),
					static_cast<int>(BlurType::MOTION), 10, 1.0f, direction));
				_blurRenderer.unbind();
			}

			// Set last direction
			lastDirection = direction;
			firstTime = false;
		}
		else // No motion blur
		{
			_renderBus.setMotionBlurMap(_renderBus.getPostProcessedSceneMap());
		}
	}
}

void RenderEngine::_captureLensFlare()
{
	if (_renderBus.isLensFlareEnabled())
	{
		// Calculate screen position
		Vec3 lightingPosition = _renderBus.getDirectionalLightPosition();
		Matrix44 viewMatrix = _renderBus.getViewMatrix();
		Matrix44 projectionMatrix = _renderBus.getProjectionMatrix();
		Vec4 clipSpacePosition = projectionMatrix * viewMatrix * Vec4(lightingPosition.x, lightingPosition.y, lightingPosition.z, 1.0f);
		float alpha = 0.0f;

		// Calculate transparency value
		if (clipSpacePosition.w <= 0.0f)
		{
			alpha = 0.0f;
		}
		else
		{
			float x = clipSpacePosition.x / clipSpacePosition.w;
			float y = clipSpacePosition.y / clipSpacePosition.w;
			alpha = 1.0f - (std::max(fabsf(x), fabsf(y)) * _renderBus.getLensFlareMultiplier());
			alpha = std::clamp(alpha, 0.0f, 1.0f);
		}

		// Update post-processing shader values
		_renderBus.setLensFlareAlpha(alpha);
		_renderBus.setFlareSourcePositionClipspace(clipSpacePosition);
		_renderBus.setFlareSourcePosition(lightingPosition);
	}
}
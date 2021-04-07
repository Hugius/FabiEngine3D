#include "render_manager.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

#include <chrono>
#include <algorithm>

void RenderManager::_captureSceneDepth()
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
		float waveHeight = (waterEntity->isWaving() ? waterEntity->getWaveHeightFactor() : 0.0f);
		isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getTranslation().y + waveHeight));
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
			clippingY = (waterEntity->getTranslation().y + waveHeight);
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
		auto allModelEntities = _entityBus->getModelEntities();
		for (auto& [keyID, modelEntity] : allModelEntities)
		{
			// Check if entity must be included in depth map
			if (modelEntity->isDepthMapIncluded())
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
						Logger::throwError("MODEL entity \"" + modelEntity->getID() + "\" has a nonexisting LOD entity \"" + modelEntity->getLodEntityID() + "\"");
					}
				}
				else // Render high-quality entity
				{
					_depthRenderer.render(modelEntity, clippingY, isUnderWater);
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

void RenderManager::_captureDofBlur()
{
	if (_renderBus.isDofEnabled())
	{
		_blurRenderer.bind();
		_renderBus.setBlurMap(_blurRenderer.blurTexture(_finalSurface, _renderBus.getSceneMap(), 
			static_cast<int>(BlurType::DOF), 6, 1.0f, BlurDirection::BOTH));
		_blurRenderer.unbind();
	}
}

void RenderManager::_capturePostProcessing()
{
	// Apply bloom, DOF & lens-flare on scene texture
	_postProcessingFramebuffer.bind();
	_postRenderer.bind();
	_postRenderer.render(_finalSurface);
	_postRenderer.unbind();
	_postProcessingFramebuffer.unbind();
	_renderBus.setPostProcessedSceneMap(_postProcessingFramebuffer.getTexture(0));
}

void RenderManager::_captureMotionBlur(CameraManager& camera)
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
	if (elapsedMS >= Config::MS_PER_UPDATE || firstTime)
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

void RenderManager::_captureLensFlare()
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
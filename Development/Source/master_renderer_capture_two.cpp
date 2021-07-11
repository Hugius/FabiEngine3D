#include "master_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

#include <chrono>
#include <algorithm>

void MasterRenderer::_captureSceneDepth()
{
	// Temporary values
	bool waterDepthNeeded = (_entityBus->getWaterEntity() != nullptr) && (_entityBus->getWaterEntity()->getTransparency() > 0.0f);
	bool isUnderWater = false;
	float clippingY = -(std::numeric_limits<float>::max)();

	// Prepare water depth
	if (waterDepthNeeded)
	{
		// Check if camera is underwater
		auto waterEntity = _entityBus->getWaterEntity();
		float waveHeight = (waterEntity->isWaving() ? waterEntity->getWaveHeight() : 0.0f);
		isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getTranslation().y + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > waterEntity->getTranslation().x - (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < waterEntity->getTranslation().x + (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > waterEntity->getTranslation().z - (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < waterEntity->getTranslation().z + (waterEntity->getSize() / 2.0f)));
		
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

		// Render MODEL entities
		auto allModelEntities = _entityBus->getModelEntities();
		for (const auto& [keyID, modelEntity] : allModelEntities)
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
						Logger::throwError("Model entity with ID \"" + modelEntity->getID() + "\" has a non-existing LOD entity with ID \"" + modelEntity->getLodEntityID() + "\"");
					}
				}
				else // Render high-quality entity
				{
					_depthRenderer.render(modelEntity, clippingY, isUnderWater);
				}
			}
		}

		// Render BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
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
			for (const auto& [keyID, entity] : _entityBus->getAabbEntities())
			{
				_depthRenderer.render(entity, clippingY, isUnderWater);
			}
		}

		// Unbind
		_depthRenderer.unbind();
		_sceneDepthFramebuffer.unbind();
		_renderBus.setSceneDepthMap(_sceneDepthFramebuffer.getTexture(0));
	}
	else
	{
		_renderBus.setSceneDepthMap(0);
	}
}

void MasterRenderer::_captureDofBlur()
{
	if (_renderBus.isDofEnabled())
	{
		_dofRenderer.bind();
		_renderBus.setDofMap(_dofRenderer.blurTexture(_finalSurface, _renderBus.getPrimarySceneMap(), 2, 1.0f, BlurDirection::BOTH));
		_dofRenderer.unbind();
	}
	else
	{
		_renderBus.setDofMap(0);
	}
}

void MasterRenderer::_capturePostProcessing()
{
	// Apply bloom, DOF & lens-flare on scene texture
	_postProcessingFramebuffer.bind();
	_postRenderer.bind();
	_postRenderer.render(_finalSurface);
	_postRenderer.unbind();
	_postProcessingFramebuffer.unbind();
	_renderBus.setFinalSceneMap(_postProcessingFramebuffer.getTexture(0));
}

void MasterRenderer::_captureMotionBlur(Camera& camera)
{
	// Temporary values
	static bool isFirstTime = true;
	static float lastYaw = 0.0f;
	static float lastPitch = 0.0f;

	// Timing values
	static std::chrono::high_resolution_clock::time_point previousMS = std::chrono::high_resolution_clock::now();
	const std::chrono::high_resolution_clock::time_point currentMS = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> timeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(currentMS - previousMS);
	const float elapsedMS = static_cast<float>(timeDifference.count()) * 1000.0f;

	// If 1 frame passed
	if (elapsedMS >= Config::MS_PER_UPDATE || isFirstTime)
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
			bool hasMoved = false;
			BlurDirection direction;

			// Determine blur direction & mix value
			if (xDifference != 0.0f || yDifference != 0.0f)
			{
				if (xDifference >= yDifference)
				{
					hasMoved = true;
					direction = BlurDirection::HORIZONTAL;
					_renderBus.setMotionBlurMixValue(xDifference);
				}
				else
				{
					hasMoved = true;
					direction = BlurDirection::VERTICAL;
					_renderBus.setMotionBlurMixValue(yDifference);
				}
			}

			// Set for next iteration
			lastYaw = camera.getYaw();
			lastPitch = camera.getPitch();

			// Apply motion blur
			if (hasMoved)
			{
				_motionBlurRenderer.bind();
				_renderBus.setMotionBlurMap(_motionBlurRenderer.blurTexture(_finalSurface, _renderBus.getFinalSceneMap(), 5, 1.0f, direction));
				_motionBlurRenderer.unbind();
			}
			else
			{
				_renderBus.setMotionBlurMixValue(0.0f);
				_renderBus.setMotionBlurMap(0);
			}

			// Miscellaneous
			isFirstTime = false;
		}
		else // No motion blur
		{
			_renderBus.setMotionBlurMixValue(0.0f);
			_renderBus.setMotionBlurMap(0);
		}
	}
}

void MasterRenderer::_captureLensFlare()
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
	else
	{
		_renderBus.setShadowMap(0);
	}
}

void MasterRenderer::_captureBloom()
{
	if (_renderBus.isBloomEnabled() && _renderBus.getBloomBlurCount() > 0 && _renderBus.getBloomIntensity() > 0.0f)
	{
		// Bind
		_bloomRenderer.bind();

		// Blur texture
		if (_renderBus.getBloomType() == BloomType::EVERYTHING)
		{
			_renderBus.setBloomMap(_bloomRenderer.blurTexture(_finalSurface, _renderBus.getPrimarySceneMap(),
				_renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		}
		else
		{
			_renderBus.setBloomMap(_bloomRenderer.blurTexture(_finalSurface, _renderBus.getSecondarySceneMap(),
				_renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		}

		// Unbind
		_bloomRenderer.unbind();
	}
	else
	{
		_renderBus.setBloomMap(0);
	}
}
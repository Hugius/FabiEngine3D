#include "master_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

#include <chrono>
#include <algorithm>

using std::max;
using std::numeric_limits;

void MasterRenderer::_captureSceneDepth()
{
	// Temporary values
	auto modelEntities = _entityBus->getModelEntities();
	auto billboardEntities = _entityBus->getBillboardEntities();
	float clippingY = -(numeric_limits<float>::max)();
	const bool waterDepthNeeded = (_entityBus->getWaterEntity() != nullptr) && (_entityBus->getWaterEntity()->getTransparency() > 0.0f);
	bool isUnderWater = false;

	// Prepare water depth
	if (waterDepthNeeded)
	{
		// Check if camera is underwater
		auto waterEntity = _entityBus->getWaterEntity();
		float waveHeight = (waterEntity->isWaving() ? waterEntity->getWaveHeight() : 0.0f);
		isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getPosition().y + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > waterEntity->getPosition().x - (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < waterEntity->getPosition().x + (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > waterEntity->getPosition().z - (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < waterEntity->getPosition().z + (waterEntity->getSize() / 2.0f)));
		
		// Determine clipping Y based on being underwater or not
		if (isUnderWater)
		{
			clippingY = waterEntity->getPosition().y;
		}
		else
		{
			clippingY = (waterEntity->getPosition().y + waveHeight);
		}
	}
	
	// Determine if scene depth rendering is needed or not
	if (_renderBus.isDofEnabled() || _renderBus.isLensFlareEnabled() || waterDepthNeeded)
	{
		// Bind
		_sceneDepthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		// Validate existence
		if (_entityBus->getTerrainEntity() != nullptr)
		{
			// Bind
			_terrainEntityDepthRenderer.bind();

			// Render TERRAIN entity
			_terrainEntityDepthRenderer.render(_entityBus->getTerrainEntity());

			// Unbind
			_terrainEntityDepthRenderer.unbind();
		}
		
		// Validate existence
		if (!modelEntities.empty())
		{
			// Bind
			_modelEntityDepthRenderer.bind();

			// Render MODEL entities
			for (const auto& [keyID, modelEntity] : modelEntities)
			{
				// Check if entity must be included in depth map
				if (modelEntity->isDepthMapIncluded())
				{
					// Check if LOD entity needs to be rendered
					if (modelEntity->isLevelOfDetailed())
					{
						// Try to find LOD entity
						auto foundPair = modelEntities.find(modelEntity->getLodEntityID());
						if (foundPair != modelEntities.end())
						{
							auto lodEntity = foundPair->second;

							// Save original transformation
							Vec3 originalPosition = lodEntity->getPosition();
							Vec3 originalRotation = lodEntity->getRotation();
							Vec3 originalSize = lodEntity->getSize();
							bool originalVisibility = lodEntity->isVisible();

							// Change transformation
							lodEntity->setPosition(modelEntity->getPosition());
							lodEntity->setRotation(modelEntity->getRotation());
							lodEntity->setSize((modelEntity->getSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
							lodEntity->setVisible(modelEntity->isVisible());
							lodEntity->updateModelMatrix();

							// Render LOD entity
							_modelEntityDepthRenderer.render(lodEntity, clippingY, isUnderWater);

							// Revert to original transformation
							lodEntity->setPosition(originalPosition);
							lodEntity->setRotation(originalRotation);
							lodEntity->setSize(originalSize);
							lodEntity->setVisible(originalVisibility);
							lodEntity->updateModelMatrix();
						}
						else
						{
							Logger::throwError("MasterRenderer::_captureSceneDepth");
						}
					}
					else // Render high-quality entity
					{
						_modelEntityDepthRenderer.render(modelEntity, clippingY, isUnderWater);
					}
				}
			}

			// Unbind
			_modelEntityDepthRenderer.unbind();
		}

		// Validate existence
		if (!billboardEntities.empty())
		{
			// Bind
			_billboardEntityDepthRenderer.bind();

			// Render BILLBOARD entities
			for (const auto& [keyID, entity] : billboardEntities)
			{
				// Check if entity must be included in depth map
				if (entity->isDepthMapIncluded())
				{
					_billboardEntityDepthRenderer.render(entity, clippingY, isUnderWater);
				}
			}

			// Unbind
			_billboardEntityDepthRenderer.unbind();
		}

		// Unbind
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
	_postProcessingFramebuffer.bind();
	_postProcessingRenderer.bind();
	_postProcessingRenderer.render(_finalSurface);
	_postProcessingRenderer.unbind();
	_postProcessingFramebuffer.unbind();
	_renderBus.setFinalSceneMap(_postProcessingFramebuffer.getTexture(0));
}

void MasterRenderer::_captureMotionBlur()
{
	// Check if motion blur is enabled
	if (_renderBus.isMotionBlurEnabled())
	{
		// Camera speed and blur direction variables
		float xDifference = (_cameraYawDifference * _renderBus.getMotionBlurStrength());
		float yDifference = (_cameraPitchDifference * _renderBus.getMotionBlurStrength());

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
	}
	else // No motion blur
	{
		_renderBus.setMotionBlurMixValue(0.0f);
		_renderBus.setMotionBlurMap(0);
	}
}

void MasterRenderer::_captureLensFlare()
{
	if (_renderBus.isLensFlareEnabled())
	{
		// Calculate screen position
		auto lightingPosition = _renderBus.getDirectionalLightPosition();
		auto viewMatrix = _renderBus.getViewMatrix();
		auto projectionMatrix = _renderBus.getProjectionMatrix();
		Vec4 clipSpacePosition = (projectionMatrix * viewMatrix * Vec4(lightingPosition.x, lightingPosition.y, lightingPosition.z, 1.0f));
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
			alpha = 1.0f - (max(fabsf(x), fabsf(y)) * _renderBus.getLensFlareMultiplier());
			alpha = std::clamp(alpha, 0.0f, 1.0f);
		}

		// Update shader properties
		_renderBus.setLensFlareAlpha(alpha);
		_renderBus.setFlareSourcePositionClipspace(clipSpacePosition);
		_renderBus.setFlareSourcePosition(lightingPosition);
	}
}

void MasterRenderer::_captureShadows()
{
	if (_renderBus.isShadowsEnabled())
	{
		// Temporary values
		auto modelEntities = _entityBus->getModelEntities();
		auto billboardEntities = _entityBus->getBillboardEntities();

		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		// Validate existence
		if (!modelEntities.empty())
		{
			// Bind
			_modelEntityShadowRenderer.bind();

			// Render MODEL entities
			for (const auto& [keyID, modelEntity] : modelEntities)
			{
				// Check if LOD entity needs to be rendered
				if (modelEntity->isLevelOfDetailed())
				{
					// Try to find LOD entity
					auto foundPair = modelEntities.find(modelEntity->getLodEntityID());
					if (foundPair != modelEntities.end())
					{
						auto lodEntity = foundPair->second;

						// Save original transformation
						Vec3 originalPosition = lodEntity->getPosition();
						Vec3 originalRotation = lodEntity->getRotation();
						Vec3 originalSize = lodEntity->getSize();
						bool originalVisibility = lodEntity->isVisible();

						// Change transformation
						lodEntity->setPosition(modelEntity->getPosition());
						lodEntity->setRotation(modelEntity->getRotation());
						lodEntity->setSize((modelEntity->getSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
						lodEntity->setVisible(modelEntity->isVisible());
						lodEntity->updateModelMatrix();

						// Render LOD entity
						_modelEntityShadowRenderer.render(lodEntity);

						// Revert to original transformation
						lodEntity->setPosition(originalPosition);
						lodEntity->setRotation(originalRotation);
						lodEntity->setSize(originalSize);
						lodEntity->setVisible(originalVisibility);
						lodEntity->updateModelMatrix();
					}
					else
					{
						Logger::throwError("MasterRenderer::_captureShadows");
					}
				}
				else // Render high-quality entity
				{
					_modelEntityShadowRenderer.render(modelEntity);
				}
			}

			// Unbind
			_modelEntityShadowRenderer.unbind();
		}
		
		// Validate existence
		if (!billboardEntities.empty())
		{
			// Bind
			_billboardEntityShadowRenderer.bind();

			// Render BILLBOARD entities
			for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				_billboardEntityShadowRenderer.render(entity);
			}

			// Unbind
			_billboardEntityShadowRenderer.unbind();
		}

		// Unbind
		_shadowFramebuffer.unbind();
		_renderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
	else
	{
		_renderBus.setShadowMap(0);
	}
}

void MasterRenderer::_captureAntiAliasing()
{
	if (_renderBus.isFxaaEnabled())
	{
		_antiAliasingFramebuffer.bind();
		_antiAliasingRenderer.bind();
		_antiAliasingRenderer.render(_finalSurface, _renderBus.getPrimarySceneMap());
		_antiAliasingRenderer.unbind();
		_antiAliasingFramebuffer.unbind();
		_renderBus.setPrimarySceneMap(_antiAliasingFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureBloom()
{
	if (_renderBus.isBloomEnabled() && _renderBus.getBloomBlurCount() > 0 && _renderBus.getBloomIntensity() > 0.0f)
	{
		// Determine texture to blur
		TextureID textureToBlur;
		if (_renderBus.getBloomType() == BloomType::EVERYTHING)
		{
			textureToBlur = _renderBus.getPrimarySceneMap();
		}
		else // Blur secondary scene map
		{
			textureToBlur = _renderBus.getSecondarySceneMap();
		}

		// Blur the scene map (high quality, small blur)
		_bloomRendererHighQuality.bind();
		_renderBus.setBloomMap(_bloomRendererHighQuality.blurTexture(_finalSurface, textureToBlur,
			_renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomRendererHighQuality.unbind();

		// Blur the blurred scene map (low quality, large blur)
		_bloomRendererLowQuality.bind();
		_renderBus.setBloomMap(_bloomRendererLowQuality.blurTexture(_finalSurface, _renderBus.getBloomMap(),
			_renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomRendererLowQuality.unbind();
	}
	else
	{
		_renderBus.setBloomMap(0);
	}
}
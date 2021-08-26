#include "master_renderer.hpp"
#include "render_bus.hpp"

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
		_sceneDepthCaptureBuffer.bind();
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
							lodEntity->updateTransformationMatrix();

							// Render LOD entity
							_modelEntityDepthRenderer.render(lodEntity, clippingY, isUnderWater);

							// Revert to original transformation
							lodEntity->setPosition(originalPosition);
							lodEntity->setRotation(originalRotation);
							lodEntity->setSize(originalSize);
							lodEntity->setVisible(originalVisibility);
							lodEntity->updateTransformationMatrix();
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
		_sceneDepthCaptureBuffer.unbind();

		// Update depth map
		_renderBus.setDepthMap(_sceneDepthCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setDepthMap(0);
	}
}

void MasterRenderer::_captureDOF()
{
	if (_renderBus.isDofEnabled())
	{
		// Blur final scene map
		_dofBlurRenderer.bind();
		_renderBus.setDofMap(_dofBlurRenderer.blurTexture(_renderSurface, _renderBus.getFinalSceneMap(), 2, 1.0f, BlurDirection::BOTH));
		_dofBlurRenderer.unbind();

		// Apply DOF & update final scene map
		_dofCaptureBuffer.bind();
		_dofRenderer.bind();
		_dofRenderer.render(_renderSurface);
		_dofRenderer.unbind();
		_dofCaptureBuffer.unbind();
		_renderBus.setFinalSceneMap(_dofCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setDofMap(0);
	}
}

void MasterRenderer::_captureLensFlare()
{
	if (_renderBus.isLensFlareEnabled())
	{
		// Apply lens flare & update final scene map
		_lensFlareCaptureBuffer.bind();
		_lensFlareRenderer.bind();
		_lensFlareRenderer.render(_renderSurface);
		_lensFlareRenderer.unbind();
		_lensFlareCaptureBuffer.unbind();
		_renderBus.setFinalSceneMap(_lensFlareCaptureBuffer.getTexture(0));
	}
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
			_motionBlurBlurRenderer.bind();
			_renderBus.setMotionBlurMap(_motionBlurBlurRenderer.blurTexture(_renderSurface, _renderBus.getFinalSceneMap(), 5, 1.0f, direction));
			_motionBlurBlurRenderer.unbind();
		}
		else
		{
			_renderBus.setMotionBlurMixValue(0.0f);
			_renderBus.setMotionBlurMap(0);
		}

		// Apply motion blur & update final scene map
		_motionBlurCaptureBuffer.bind();
		_motionBlurRenderer.bind();
		_motionBlurRenderer.render(_renderSurface);
		_motionBlurRenderer.unbind();
		_motionBlurCaptureBuffer.unbind();
		_renderBus.setFinalSceneMap(_motionBlurCaptureBuffer.getTexture(0));
	}
	else // No motion blur
	{
		_renderBus.setMotionBlurMap(0);
	}
}

void MasterRenderer::_captureAntiAliasing()
{
	if (_renderBus.isFxaaEnabled())
	{
		// Apply anti-aliasing & update final scene map
		_antiAliasingCaptureBuffer.bind();
		_antiAliasingRenderer.bind();
		_antiAliasingRenderer.render(_renderSurface);
		_antiAliasingRenderer.unbind();
		_antiAliasingCaptureBuffer.unbind();
		_renderBus.setFinalSceneMap(_antiAliasingCaptureBuffer.getTexture(0));
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
		_bloomBlurRendererHighQuality.bind();
		_renderBus.setBloomMap(_bloomBlurRendererHighQuality.blurTexture(_renderSurface, textureToBlur,
			_renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererHighQuality.unbind();

		// Blur the blurred scene map (low quality, large blur)
		_bloomBlurRendererLowQuality.bind();
		_renderBus.setBloomMap(_bloomBlurRendererLowQuality.blurTexture(_renderSurface, _renderBus.getBloomMap(),
			_renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererLowQuality.unbind();

		// Apply bloom & update final scene map
		_bloomCaptureBuffer.bind();
		_bloomRenderer.bind();
		_bloomRenderer.render(_renderSurface);
		_bloomRenderer.unbind();
		_bloomCaptureBuffer.unbind();
		_renderBus.setFinalSceneMap(_bloomCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setBloomMap(0);
	}
}
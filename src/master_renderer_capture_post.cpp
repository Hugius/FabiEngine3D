#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureWorldDepth()
{
	// Temporary values
	auto modelEntities = _entityBus->getModelEntities();
	auto billboardEntities = _entityBus->getBillboardEntities();
	float clippingY = numeric_limits<float>::lowest();
	const bool waterDepthNeeded = (_entityBus->getWaterEntity() != nullptr) && (_entityBus->getWaterEntity()->getTransparency() > 0.0f);
	bool isUnderWater = false;

	// Prepare water depth
	if(waterDepthNeeded)
	{
		// Check if camera is underwater
		auto waterEntity = _entityBus->getWaterEntity();
		float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < (waterEntity->getSize() / 2.0f)));

		// Determine clipping Y based on being underwater or not
		if(isUnderWater)
		{
			clippingY = waterEntity->getHeight();
		}
		else
		{
			clippingY = (waterEntity->getHeight() + waveHeight);
		}
	}

	// Determine if world depth rendering is needed or not
	if(_renderBus.isDofEnabled() || _renderBus.isLensFlareEnabled() || waterDepthNeeded)
	{
		// Bind
		_worldDepthCaptureBuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		// Validate existence
		if(_entityBus->getTerrainEntity() != nullptr)
		{
			// Bind
			_terrainEntityDepthRenderer.bind();

			// Render terrain entity
			_terrainEntityDepthRenderer.render(_entityBus->getTerrainEntity());

			// Unbind
			_terrainEntityDepthRenderer.unbind();
		}

		// Validate existence
		if(!modelEntities.empty())
		{
			// Bind
			_modelEntityDepthRenderer.bind();

			// Render model entities
			for(const auto& [keyID, modelEntity] : modelEntities)
			{
				// Check if entity must be included in depth map
				if(modelEntity->isDepthMapIncluded())
				{
					// Check if level of detail entity needs to be rendered
					if(modelEntity->isLevelOfDetailed())
					{
						// Try to find level of detail entity
						auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
						if(foundPair != modelEntities.end())
						{
							auto levelOfDetailEntity = foundPair->second;

							// Save initial transformation
							fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
							fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
							fvec3 initialSize = levelOfDetailEntity->getBaseSize();
							bool initialVisibility = levelOfDetailEntity->isVisible();

							// Change transformation
							levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
							levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
							levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
							levelOfDetailEntity->setVisible(modelEntity->isVisible());
							levelOfDetailEntity->updateTransformationMatrix();

							// Render level of detail entity
							_modelEntityDepthRenderer.render(levelOfDetailEntity, clippingY, isUnderWater);

							// Revert to initial transformation
							levelOfDetailEntity->setBasePosition(initialPosition);
							levelOfDetailEntity->setBaseRotation(initialRotation);
							levelOfDetailEntity->setBaseSize(initialSize);
							levelOfDetailEntity->setVisible(initialVisibility);
							levelOfDetailEntity->updateTransformationMatrix();
						}
						else
						{
							Logger::throwError("MasterRenderer::_captureWorldDepth");
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
		if(!billboardEntities.empty())
		{
			// Bind
			_billboardEntityDepthRenderer.bind();

			// Render billboard entities
			for(const auto& [keyID, entity] : billboardEntities)
			{
				// Check if entity must be included in depth map
				if(entity->isDepthMapIncluded())
				{
					_billboardEntityDepthRenderer.render(entity, clippingY, isUnderWater);
				}
			}

			// Unbind
			_billboardEntityDepthRenderer.unbind();
		}

		// Unbind
		_worldDepthCaptureBuffer.unbind();

		// Update depth map
		_renderBus.setDepthMap(_worldDepthCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setDepthMap(0);
	}
}

void MasterRenderer::_captureDOF()
{
	if(_renderBus.isDofEnabled())
	{
		// Blur final world map
		_dofBlurRenderer.bind();
		_renderBus.setDofMap(_dofBlurRenderer.blurTexture(_renderSurface, _renderBus.getFinalWorldMap(), 2, 1.0f, BlurDirection::BOTH));
		_dofBlurRenderer.unbind();

		// Apply DOF & update final world map
		_dofCaptureBuffer.bind();
		_dofRenderer.bind();
		_dofRenderer.render(_renderSurface);
		_dofRenderer.unbind();
		_dofCaptureBuffer.unbind();
		_renderBus.setFinalWorldMap(_dofCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setDofMap(0);
	}
}

void MasterRenderer::_captureLensFlare()
{
	if(_renderBus.isLensFlareEnabled())
	{
		// Apply lens flare & update final world map
		_lensFlareCaptureBuffer.bind();
		_lensFlareRenderer.bind();
		_lensFlareRenderer.render(_renderSurface);
		_lensFlareRenderer.unbind();
		_lensFlareCaptureBuffer.unbind();
		_renderBus.setFinalWorldMap(_lensFlareCaptureBuffer.getTexture(0));
	}
}

void MasterRenderer::_captureMotionBlur()
{
	// Check if motion blur is enabled
	if(_renderBus.isMotionBlurEnabled())
	{
		// Camera speed and blur direction variables
		float xDifference = (_cameraYawDifference * _renderBus.getMotionBlurStrength());
		float yDifference = (_cameraPitchDifference * _renderBus.getMotionBlurStrength());

		// Temporary values
		bool hasMoved = false;
		BlurDirection direction;

		// Determine blur direction & mix value
		if(xDifference != 0.0f || yDifference != 0.0f)
		{
			if(xDifference >= yDifference)
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
		if(hasMoved)
		{
			_motionBlurBlurRenderer.bind();
			_renderBus.setMotionBlurMap(_motionBlurBlurRenderer.blurTexture(_renderSurface, _renderBus.getFinalWorldMap(), 5, 1.0f, direction));
			_motionBlurBlurRenderer.unbind();
		}
		else
		{
			_renderBus.setMotionBlurMixValue(0.0f);
			_renderBus.setMotionBlurMap(0);
		}

		// Apply motion blur & update final world map
		_motionBlurCaptureBuffer.bind();
		_motionBlurRenderer.bind();
		_motionBlurRenderer.render(_renderSurface);
		_motionBlurRenderer.unbind();
		_motionBlurCaptureBuffer.unbind();
		_renderBus.setFinalWorldMap(_motionBlurCaptureBuffer.getTexture(0));
	}
	else // No motion blur
	{
		_renderBus.setMotionBlurMap(0);
	}
}

void MasterRenderer::_captureAntiAliasing()
{
	if(_renderBus.isAntiAliasingEnabled())
	{
		// Apply anti aliasing & update final world map
		_antiAliasingCaptureBuffer.bind();
		_antiAliasingRenderer.bind();
		_antiAliasingRenderer.render(_renderSurface);
		_antiAliasingRenderer.unbind();
		_antiAliasingCaptureBuffer.unbind();
		_renderBus.setFinalWorldMap(_antiAliasingCaptureBuffer.getTexture(0));
	}
}

void MasterRenderer::_captureBloom()
{
	if(_renderBus.isBloomEnabled() && _renderBus.getBloomBlurCount() > 0 && _renderBus.getBloomIntensity() > 0.0f)
	{
		// Determine texture to blur
		TextureID textureToBlur;
		if(_renderBus.getBloomType() == BloomType::EVERYTHING)
		{
			textureToBlur = _renderBus.getPrimaryWorldMap();
		}
		else // Blur secondary world map
		{
			textureToBlur = _renderBus.getSecondaryWorldMap();
		}

		// Blur the world map (high quality, small blur)
		_bloomBlurRendererHighQuality.bind();
		_renderBus.setBloomMap(_bloomBlurRendererHighQuality.blurTexture(_renderSurface, textureToBlur,
							   _renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererHighQuality.unbind();

		// Blur the blurred world map (low quality, large blur)
		_bloomBlurRendererLowQuality.bind();
		_renderBus.setBloomMap(_bloomBlurRendererLowQuality.blurTexture(_renderSurface, _renderBus.getBloomMap(),
							   _renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererLowQuality.unbind();

		// Apply bloom & update final world map
		_bloomCaptureBuffer.bind();
		_bloomRenderer.bind();
		_bloomRenderer.render(_renderSurface);
		_bloomRenderer.unbind();
		_bloomCaptureBuffer.unbind();
		_renderBus.setFinalWorldMap(_bloomCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setBloomMap(0);
	}
}
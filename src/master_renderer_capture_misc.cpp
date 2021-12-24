#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureWaterRefractions()
{
	// Temporary values
	const auto waterEntity = _entityBus->getWaterEntity();

	// Check if water refractions needed
	if((waterEntity != nullptr) && waterEntity->isRefractive())
	{
		// Start capturing refractions
		_waterRefractionCaptureBuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Shadows are not needed if no models are rendered, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		if((waterEntity->getQuality() == WaterQuality::SKY) || (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN))
		{
			_renderBus.setShadowsEnabled(false);
		}

		// Sky exposure must not appear in refractions
		float oldSkyLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if(skyEntity != nullptr)
		{
			oldSkyLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		// Check if camera underwater
		const float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		bool isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < (waterEntity->getSize() / 2.0f)));

		// Calculate clipping plane
		if(isUnderWater)
		{
			const float clippingHeight = -(waterEntity->getHeight());
			const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
			_renderBus.setClippingPlane(clippingPlane);
		}
		else
		{
			const float clippingHeight = (waterEntity->getHeight() + waveHeight);
			const fvec4 clippingPlane = fvec4(0.0f, -1.0f, 0.0f, clippingHeight);
			_renderBus.setClippingPlane(clippingPlane);
		}

		// Render sky entity
		_renderSkyEntity();

		// Render terrain entity
		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		// Render model entities
		if((waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS) ||
		   (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS))
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Render billboard entities
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Revert shadows
		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		// Revert sky lightness
		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}

		// Stop capturing refractions
		_waterRefractionCaptureBuffer.unbind();

		// Assign texture
		_renderBus.setWaterRefractionMap(_waterRefractionCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setWaterRefractionMap(0);
	}
}

void MasterRenderer::_captureShadows()
{
	if(_renderBus.isShadowsEnabled())
	{
		// Temporary values
		auto modelEntities = _entityBus->getModelEntities();
		auto billboardEntities = _entityBus->getBillboardEntities();

		// Bind
		_shadowCaptureBuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		// Validate existence
		if(!modelEntities.empty())
		{
			// Bind
			_modelEntityShadowRenderer.bind();

			// Render model entities
			for(const auto& [keyID, modelEntity] : modelEntities)
			{
				if(modelEntity->isLevelOfDetailed()) // Low quality
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
						_modelEntityShadowRenderer.render(levelOfDetailEntity);

						// Revert to initial transformation
						levelOfDetailEntity->setBasePosition(initialPosition);
						levelOfDetailEntity->setBaseRotation(initialRotation);
						levelOfDetailEntity->setBaseSize(initialSize);
						levelOfDetailEntity->setVisible(initialVisibility);
						levelOfDetailEntity->updateTransformationMatrix();
					}
					else
					{
						Logger::throwError("MasterRenderer::_captureShadows");
					}
				}
				else // High quality
				{
					_modelEntityShadowRenderer.render(modelEntity);
				}
			}

			// Unbind
			_modelEntityShadowRenderer.unbind();
		}

		// Validate existence
		if(!billboardEntities.empty())
		{
			// Bind
			_billboardEntityShadowRenderer.bind();

			// Render billboard entities
			for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				_billboardEntityShadowRenderer.render(entity);
			}

			// Unbind
			_billboardEntityShadowRenderer.unbind();
		}

		// Unbind
		_shadowCaptureBuffer.unbind();
		_renderBus.setShadowMap(_shadowCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setShadowMap(0);
	}
}
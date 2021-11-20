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
			const Vec4 clippingPlane = Vec4(0.0f, 1.0f, 0.0f, clippingHeight);
			_renderBus.setClippingPlane(clippingPlane);
		}
		else
		{
			const float clippingHeight = (waterEntity->getHeight() + waveHeight);
			const Vec4 clippingPlane = Vec4(0.0f, -1.0f, 0.0f, clippingHeight);
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
				// Check if LOD entity needs to be rendered
				if(modelEntity->isLevelOfDetailed())
				{
					// Try to find LOD entity
					auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
					if(foundPair != modelEntities.end())
					{
						auto lodEntity = foundPair->second;

						// Save initial transformation
						Vec3 initialPosition = lodEntity->getBasePosition();
						Vec3 initialRotation = lodEntity->getBaseRotation();
						Vec3 initialSize = lodEntity->getBaseSize();
						bool initialVisibility = lodEntity->isVisible();

						// Change transformation
						lodEntity->setBasePosition(modelEntity->getBasePosition());
						lodEntity->setBaseRotation(modelEntity->getBaseRotation());
						lodEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
						lodEntity->setVisible(modelEntity->isVisible());
						lodEntity->updateTransformationMatrix();

						// Render LOD entity
						_modelEntityShadowRenderer.render(lodEntity);

						// Revert to initial transformation
						lodEntity->setBasePosition(initialPosition);
						lodEntity->setBaseRotation(initialRotation);
						lodEntity->setBaseSize(initialSize);
						lodEntity->setVisible(initialVisibility);
						lodEntity->updateTransformationMatrix();
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
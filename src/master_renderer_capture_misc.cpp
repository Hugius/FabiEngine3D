#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureWaterRefractions()
{
	const auto waterEntity = _entityBus->getWaterEntity();

	if((waterEntity != nullptr) && waterEntity->isRefractive())
	{
		_waterRefractionCaptureBuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		if((waterEntity->getQuality() == WaterQuality::SKY) || (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN))
		{
			_renderBus.setShadowsEnabled(false);
		}

		float oldSkyLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if(skyEntity != nullptr)
		{
			oldSkyLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		const float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		bool isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < (waterEntity->getSize() / 2.0f)));

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

		_renderSkyEntity();

		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		if((waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS) ||
		   (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS))
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}

		_waterRefractionCaptureBuffer.unbind();

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
		auto modelEntities = _entityBus->getModelEntities();
		auto billboardEntities = _entityBus->getBillboardEntities();

		_shadowCaptureBuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		if(!modelEntities.empty())
		{
			_modelEntityShadowRenderer.bind();

			for(const auto& [keyID, modelEntity] : modelEntities)
			{
				if(modelEntity->isLevelOfDetailed())
				{
					auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
					if(foundPair != modelEntities.end())
					{
						auto levelOfDetailEntity = foundPair->second;

						fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
						fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
						fvec3 initialSize = levelOfDetailEntity->getBaseSize();
						bool initialVisibility = levelOfDetailEntity->isVisible();

						levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
						levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
						levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
						levelOfDetailEntity->setVisible(modelEntity->isVisible());
						levelOfDetailEntity->updateTransformationMatrix();

						_modelEntityShadowRenderer.render(levelOfDetailEntity);

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
				else
				{
					_modelEntityShadowRenderer.render(modelEntity);
				}
			}

			_modelEntityShadowRenderer.unbind();
		}

		if(!billboardEntities.empty())
		{
			_billboardEntityShadowRenderer.bind();

			for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				_billboardEntityShadowRenderer.render(entity);
			}

			_billboardEntityShadowRenderer.unbind();
		}

		_shadowCaptureBuffer.unbind();
		_renderBus.setShadowMap(_shadowCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setShadowMap(0);
	}
}
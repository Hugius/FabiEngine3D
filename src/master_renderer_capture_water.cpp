#include "master_renderer.hpp"

void MasterRenderer::_captureWaterReflections(RenderBus& renderBus, Camera& camera, EntityBus& entityBus)
{
	const auto waterEntity = entityBus.getWaterEntity();

	if((waterEntity != nullptr) && waterEntity->isReflective())
	{
		float cameraDistance = (camera.getPosition().y - waterEntity->getHeight());

		_waterReflectionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<string> savedModelEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			for(const auto& [key, entity] : entityBus.getModelEntities())
			{
				if(!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedModelEntityIDs.push_back(entity->getID());
					continue;
				}

				for(const auto& partID : entity->getPartIDs())
				{
					if(entity->isReflective(partID) && (entity->getReflectionType(partID) == ReflectionType::PLANAR) && entity->isVisible())
					{
						entity->setVisible(false);
						savedModelEntityIDs.push_back(entity->getID());
						break;
					}
				}
			}
		}

		vector<string> savedBillboardEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			for(const auto& [key, entity] : entityBus.getBillboardEntities())
			{
				if(!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedBillboardEntityIDs.push_back(entity->getID());
				}
			}
		}

		const fvec3 initialCameraPosition = camera.getPosition();
		camera.setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

		const float initialCameraPitch = camera.getPitch();
		camera.setPitch(-initialCameraPitch);

		camera.updateMatrices(renderBus);

		renderBus.setCameraPosition(initialCameraPosition);
		renderBus.setCameraPitch(initialCameraPitch);

		renderBus.setReflectionsEnabled(false);

		bool wasShadowsEnabled = renderBus.isShadowsEnabled();
		renderBus.setShadowsEnabled(false);

		float oldLightness = 0.0f;
		auto skyEntity = entityBus.getMainSkyEntity();
		if(skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		const float clippingHeight = -(waterEntity->getHeight());
		const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
		renderBus.setClippingPlane(clippingPlane);

		_renderSkyEntity(renderBus, entityBus);

		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity(renderBus, entityBus);
			glDisable(GL_CLIP_DISTANCE0);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities(renderBus, entityBus);
			glDisable(GL_CLIP_DISTANCE2);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities(renderBus, entityBus);
			glDisable(GL_CLIP_DISTANCE2);
		}

		_waterReflectionCaptor->unbind();

		renderBus.setWaterReflectionMap(_waterReflectionCaptor->getTexture(0));

		for(const auto& savedID : savedModelEntityIDs)
		{
			for(const auto& [key, entity] : entityBus.getModelEntities())
			{
				if(entity->getID() == savedID)
				{
					entity->setVisible(true);
				}
			}
		}

		for(const auto& savedID : savedBillboardEntityIDs)
		{
			for(const auto& [key, entity] : entityBus.getBillboardEntities())
			{
				if(entity->getID() == savedID)
				{
					entity->setVisible(true);
				}
			}
		}

		camera.setPitch(initialCameraPitch);

		camera.setPosition(initialCameraPosition);

		camera.updateMatrices(renderBus);

		renderBus.setReflectionsEnabled(true);

		renderBus.setShadowsEnabled(wasShadowsEnabled);

		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldLightness);
		}
	}
	else
	{
		renderBus.setWaterReflectionMap(0);
	}
}

void MasterRenderer::_captureWaterRefractions(RenderBus& renderBus, Camera& camera, EntityBus& entityBus)
{
	const auto waterEntity = entityBus.getWaterEntity();

	if((waterEntity != nullptr) && waterEntity->isRefractive())
	{
		_waterRefractionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool wasShadowsEnabled = renderBus.isShadowsEnabled();
		if((waterEntity->getQuality() == WaterQuality::SKY) || (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN))
		{
			renderBus.setShadowsEnabled(false);
		}

		float oldSkyLightness = 0.0f;
		auto skyEntity = entityBus.getMainSkyEntity();
		if(skyEntity != nullptr)
		{
			oldSkyLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		const float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		bool isUnderWater = (camera.getPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (camera.getPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (camera.getPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (camera.getPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (camera.getPosition().z < (waterEntity->getSize() / 2.0f)));

		if(isUnderWater)
		{
			const float clippingHeight = -(waterEntity->getHeight());
			const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
			renderBus.setClippingPlane(clippingPlane);
		}
		else
		{
			const float clippingHeight = (waterEntity->getHeight() + waveHeight);
			const fvec4 clippingPlane = fvec4(0.0f, -1.0f, 0.0f, clippingHeight);
			renderBus.setClippingPlane(clippingPlane);
		}

		_renderSkyEntity(renderBus, entityBus);

		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity(renderBus, entityBus);
			glDisable(GL_CLIP_DISTANCE0);
		}

		if((waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS) ||
		   (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS))
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities(renderBus, entityBus);
			glDisable(GL_CLIP_DISTANCE2);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities(renderBus, entityBus);
			glDisable(GL_CLIP_DISTANCE2);
		}

		renderBus.setShadowsEnabled(wasShadowsEnabled);

		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}

		_waterRefractionCaptor->unbind();

		renderBus.setWaterRefractionMap(_waterRefractionCaptor->getTexture(0));
	}
	else
	{
		renderBus.setWaterRefractionMap(0);
	}
}
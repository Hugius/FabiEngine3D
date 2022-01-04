#include "master_renderer.hpp"

void MasterRenderer::_captureWaterReflections()
{
	const auto waterEntity = _entityBus->getWaterEntity();

	if((waterEntity != nullptr) && waterEntity->isReflective())
	{
		float cameraDistance = (_camera.getPosition().y - waterEntity->getHeight());

		_waterReflectionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<string> savedModelEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			for(const auto& [key, entity] : _entityBus->getModelEntities())
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
			for(const auto& [key, entity] : _entityBus->getBillboardEntities())
			{
				if(!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedBillboardEntityIDs.push_back(entity->getID());
				}
			}
		}

		const fvec3 initialCameraPosition = _camera.getPosition();
		_camera.setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

		const float initialCameraPitch = _camera.getPitch();
		_camera.setPitch(-initialCameraPitch);

		_camera.updateMatrices();

		_renderBus.setCameraPosition(initialCameraPosition);
		_renderBus.setCameraPitch(initialCameraPitch);

		_renderBus.setReflectionsEnabled(false);

		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if(skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		const float clippingHeight = -(waterEntity->getHeight());
		const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
		_renderBus.setClippingPlane(clippingPlane);

		_renderSkyEntity();

		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
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

		_waterReflectionCaptor->unbind();

		_renderBus.setWaterReflectionMap(_waterReflectionCaptor->getTexture(0));

		for(const auto& savedID : savedModelEntityIDs)
		{
			for(const auto& [key, entity] : _entityBus->getModelEntities())
			{
				if(entity->getID() == savedID)
				{
					entity->setVisible(true);
				}
			}
		}

		for(const auto& savedID : savedBillboardEntityIDs)
		{
			for(const auto& [key, entity] : _entityBus->getBillboardEntities())
			{
				if(entity->getID() == savedID)
				{
					entity->setVisible(true);
				}
			}
		}

		_camera.setPitch(initialCameraPitch);

		_camera.setPosition(initialCameraPosition);

		_camera.updateMatrices();

		_renderBus.setReflectionsEnabled(true);

		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldLightness);
		}
	}
	else
	{
		_renderBus.setWaterReflectionMap(0);
	}
}
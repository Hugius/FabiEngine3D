#include "master_renderer.hpp"

void MasterRenderer::_captureWaterReflections()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity != nullptr) && waterEntity->isReflective())
	{
		float cameraDistance = (_camera->getPosition().y - waterEntity->getHeight());

		_waterReflectionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<string> savedModelEntityIds;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			for(const auto& [key, entity] : _modelEntityManager->getEntities())
			{
				if(entity->isVisible())
				{
					if(!entity->isReflected())
					{
						entity->setVisible(false);
						savedModelEntityIds.push_back(entity->getId());
						continue;
					}

					for(const auto& partId : entity->getPartIds())
					{
						if(entity->isReflective(partId) && (entity->getReflectionType(partId) == ReflectionType::PLANAR))
						{
							entity->setVisible(false);
							savedModelEntityIds.push_back(entity->getId());
							break;
						}
					}
				}
			}
		}

		vector<string> savedQuad3dEntityIds;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
			{
				if(!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedQuad3dEntityIds.push_back(entity->getId());
				}
			}
		}

		const fvec3 initialCameraPosition = _camera->getPosition();
		_camera->setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

		const float initialCameraPitch = _camera->getPitch();
		_camera->setPitch(-initialCameraPitch);

		_camera->updateMatrices();

		_renderBus->setCameraPosition(initialCameraPosition);
		_renderBus->setCameraPitch(initialCameraPitch);

		_renderBus->setReflectionsEnabled(false);

		bool wasShadowsEnabled = _renderBus->isShadowsEnabled();
		_renderBus->setShadowsEnabled(false);

		float skyExposureLightness = _renderBus->getSkyExposureLightness();
		_renderBus->setSkyExposureLightness(0.0f);

		const float clippingHeight = -(waterEntity->getHeight());
		const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
		_renderBus->setClippingPlane(clippingPlane);

		glEnable(GL_CLIP_DISTANCE0);

		switch(waterEntity->getQuality())
		{
			case WaterQuality::SKY:
			{
				_renderSkyEntity();
				break;
			}
			case WaterQuality::SKY_TERRAIN:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				break;
			}
			case WaterQuality::SKY_TERRAIN_MODEL:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderOpaqueModelEntities();
				_renderTransparentModelEntities();
				break;
			}
			case WaterQuality::SKY_TERRAIN_MODEL_QUAD3D:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderOpaqueModelEntities();
				_renderOpaqueQuad3dEntities();
				_renderTransparentModelEntities();
				_renderTransparentQuad3dEntities();
				break;
			}
			case WaterQuality::SKY_TERRAIN_MODEL_QUAD3D_TEXT3D:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderOpaqueModelEntities();
				_renderOpaqueQuad3dEntities();
				_renderOpaqueText3dEntities();
				_renderTransparentModelEntities();
				_renderTransparentQuad3dEntities();
				_renderTransparentText3dEntities();
				break;
			}
		}

		glDisable(GL_CLIP_DISTANCE0);

		_waterReflectionCaptor->unbind();

		_renderBus->setWaterReflectionMap(_waterReflectionCaptor->getTexture(0));

		for(const auto& savedID : savedModelEntityIds)
		{
			for(const auto& [key, entity] : _modelEntityManager->getEntities())
			{
				if(entity->getId() == savedID)
				{
					entity->setVisible(true);
				}
			}
		}

		for(const auto& savedID : savedQuad3dEntityIds)
		{
			for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
			{
				if(entity->getId() == savedID)
				{
					entity->setVisible(true);
				}
			}
		}

		_camera->setPitch(initialCameraPitch);

		_camera->setPosition(initialCameraPosition);

		_camera->updateMatrices();

		_renderBus->setReflectionsEnabled(true);

		_renderBus->setShadowsEnabled(wasShadowsEnabled);

		_renderBus->setSkyExposureLightness(skyExposureLightness);
	}
	else
	{
		_renderBus->setWaterReflectionMap(nullptr);
	}
}

void MasterRenderer::_captureWaterRefractions()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity != nullptr) && waterEntity->isRefractive())
	{
		_waterRefractionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const auto isShadowsEnabled = _renderBus->isShadowsEnabled();
		if((waterEntity->getQuality() == WaterQuality::SKY) || (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN))
		{
			_renderBus->setShadowsEnabled(false);
		}

		const auto skyExposureLightness = _renderBus->getSkyExposureLightness();
		_renderBus->setSkyExposureLightness(0.0f);

		const float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		bool isUnderWater = (_camera->getPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (_camera->getPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_camera->getPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_camera->getPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_camera->getPosition().z < (waterEntity->getSize() / 2.0f)));

		if(isUnderWater)
		{
			const float clippingHeight = -(waterEntity->getHeight());
			const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
			_renderBus->setClippingPlane(clippingPlane);
		}
		else
		{
			const float clippingHeight = (waterEntity->getHeight() + waveHeight);
			const fvec4 clippingPlane = fvec4(0.0f, -1.0f, 0.0f, clippingHeight);
			_renderBus->setClippingPlane(clippingPlane);
		}

		glEnable(GL_CLIP_DISTANCE0);

		switch(waterEntity->getQuality())
		{
			case WaterQuality::SKY:
			{
				_renderSkyEntity();
				break;
			}
			case WaterQuality::SKY_TERRAIN:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				break;
			}
			case WaterQuality::SKY_TERRAIN_MODEL:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderOpaqueModelEntities();
				_renderTransparentModelEntities();
				break;
			}
			case WaterQuality::SKY_TERRAIN_MODEL_QUAD3D:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderOpaqueModelEntities();
				_renderOpaqueQuad3dEntities();
				_renderTransparentModelEntities();
				_renderTransparentQuad3dEntities();
				break;
			}
			case WaterQuality::SKY_TERRAIN_MODEL_QUAD3D_TEXT3D:
			{
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderOpaqueModelEntities();
				_renderOpaqueQuad3dEntities();
				_renderOpaqueText3dEntities();
				_renderTransparentModelEntities();
				_renderTransparentQuad3dEntities();
				_renderTransparentText3dEntities();
				break;
			}
		}

		glDisable(GL_CLIP_DISTANCE0);

		_renderBus->setShadowsEnabled(isShadowsEnabled);

		_renderBus->setSkyExposureLightness(skyExposureLightness);

		_waterRefractionCaptor->unbind();

		_renderBus->setWaterRefractionMap(_waterRefractionCaptor->getTexture(0));
	}
	else
	{
		_renderBus->setWaterRefractionMap(nullptr);
	}
}
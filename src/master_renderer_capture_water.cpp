#include "master_renderer.hpp"

void MasterRenderer::_captureWaterReflections()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity == nullptr) || !waterEntity->isReflective())
	{
		_renderBus->setWaterReflectionMap(nullptr);
		return;
	}

	const auto waveHeight = ((waterEntity->getDisplacementMap() != nullptr) ? waterEntity->getWaveHeight() : 0.0f);
	const auto waterHeight = (waterEntity->getHeight() + waveHeight);
	const auto isUnderWater = (_camera->getPosition().y < waterHeight);

	if(isUnderWater)
	{
		_renderBus->setWaterReflectionMap(nullptr);
		return;
	}

	_waterReflectionCaptor->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelEntityIds;
	if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL ||
	   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D ||
	   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D_TEXT3D)
	{
		for(const auto& [key, entity] : _modelEntityManager->getEntities())
		{
			if(!entity->isVisible())
			{
				continue;
			}

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

	vector<string> savedQuad3dEntityIds;
	if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D ||
	   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D_TEXT3D)
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

	const auto cameraDistance = fabsf(_camera->getPosition().y - waterEntity->getHeight());
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalCameraPitch = _camera->getPitch();
	const auto originalSkyExposureLightness = _renderBus->getSkyExposureLightness();

	_camera->setPosition(fvec3(originalCameraPosition.x, (originalCameraPosition.y - (cameraDistance * 2.0f)), originalCameraPosition.z));
	_camera->setPitch(-originalCameraPitch);
	_camera->updateMatrices();

	_renderBus->setMinPosition(fvec3(-FLT_MAX, (waterEntity->getHeight() - 1.0f), -FLT_MAX));
	_renderBus->setCameraPosition(originalCameraPosition);
	_renderBus->setCameraPitch(originalCameraPitch);
	_renderBus->setReflectionsEnabled(false);
	_renderBus->setRefractionsEnabled(false);
	_renderBus->setSkyExposureLightness(0.0f);

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

	for(const auto& savedId : savedModelEntityIds)
	{
		for(const auto& [key, entity] : _modelEntityManager->getEntities())
		{
			if(entity->getId() == savedId)
			{
				entity->setVisible(true);
			}
		}
	}

	for(const auto& savedId : savedQuad3dEntityIds)
	{
		for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->getId() == savedId)
			{
				entity->setVisible(true);
			}
		}
	}

	_camera->setPosition(originalCameraPosition);
	_camera->setPitch(originalCameraPitch);
	_camera->updateMatrices();

	_renderBus->setWaterReflectionMap(_waterReflectionCaptor->getTexture(0));
	_renderBus->setMinPosition(fvec3(-FLT_MAX));
	_renderBus->setReflectionsEnabled(true);
	_renderBus->setRefractionsEnabled(true);
	_renderBus->setSkyExposureLightness(originalSkyExposureLightness);

	_waterReflectionCaptor->unbind();
}

void MasterRenderer::_captureWaterRefractions()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity == nullptr) || !waterEntity->isRefractive())
	{
		_renderBus->setWaterRefractionMap(nullptr);
		return;
	}

	const auto waveHeight = ((waterEntity->getDisplacementMap() != nullptr) ? waterEntity->getWaveHeight() : 0.0f);
	const auto waterHeight = (waterEntity->getHeight() + waveHeight);
	const auto isUnderWater = (_camera->getPosition().y < waterHeight);

	if(!isUnderWater)
	{
		_renderBus->setWaterRefractionMap(nullptr);
		return;
	}

	_waterRefractionCaptor->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const auto originalSkyExposureLightness = _renderBus->getSkyExposureLightness();

	_renderBus->setMinPosition(fvec3(-FLT_MAX, (waterEntity->getHeight() - 1.0f), -FLT_MAX));
	_renderBus->setSkyExposureLightness(0.0f);

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

	_renderBus->setWaterRefractionMap(_waterRefractionCaptor->getTexture(0));
	_renderBus->setMinPosition(fvec3(-FLT_MAX));
	_renderBus->setSkyExposureLightness(originalSkyExposureLightness);

	_waterRefractionCaptor->unbind();
}

void MasterRenderer::_captureWaterEdges()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity != nullptr) && waterEntity->isEdged())
	{
		_waterOpacityCaptor->bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		if(_terrainEntityManager->getSelectedEntity() != nullptr)
		{
			_terrainEntityDepthRenderer.bind();

			_terrainEntityDepthRenderer.render(_terrainEntityManager->getSelectedEntity());

			_terrainEntityDepthRenderer.unbind();
		}

		_waterOpacityCaptor->unbind();

		_renderBus->setWaterEdgeMap(_waterOpacityCaptor->getTexture(0));
	}
	else
	{
		_renderBus->setWaterEdgeMap(nullptr);
	}
}
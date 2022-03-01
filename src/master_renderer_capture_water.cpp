#include "master_renderer.hpp"

void MasterRenderer::captureWaterReflections()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity == nullptr) || !waterEntity->isReflective())
	{
		_renderStorage->setWaterReflectionMap(nullptr);
		return;
	}

	if(_camera->getPosition().y < waterEntity->getHeight())
	{
		_renderStorage->setWaterReflectionMap(nullptr);
		return;
	}

	_waterReflectionCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelEntityIds;
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

	vector<string> savedQuad3dEntityIds;
	for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedQuad3dEntityIds.push_back(entity->getId());
		}
	}

	const auto cameraDistance = fabsf(_camera->getPosition().y - waterEntity->getHeight());
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalCameraPitch = _camera->getPitch();
	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_camera->setPosition(fvec3(originalCameraPosition.x, (originalCameraPosition.y - (cameraDistance * 2.0f)), originalCameraPosition.z));
	_camera->setPitch(-originalCameraPitch);
	_camera->updateMatrices();
	_camera->setPosition(originalCameraPosition);
	_camera->setPitch(originalCameraPitch);

	_renderStorage->setMinPosition(fvec3(-FLT_MAX, (waterEntity->getHeight() - 1.0f), -FLT_MAX));
	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);

	_renderSkyEntity();
	_renderTerrainEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderAabbEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();

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

	_camera->updateMatrices();

	_renderStorage->setWaterReflectionMap(_waterReflectionCaptureBuffer->getTexture(0));
	_renderStorage->setMinPosition(fvec3(-FLT_MAX));
	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);

	_waterReflectionCaptureBuffer->unbind();
}

void MasterRenderer::captureWaterRefractions()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity == nullptr) || !waterEntity->isRefractive())
	{
		_renderStorage->setWaterRefractionMap(nullptr);
		return;
	}

	if(_camera->getPosition().y > waterEntity->getHeight())
	{
		_renderStorage->setWaterRefractionMap(nullptr);
		return;
	}

	_waterRefractionCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_renderStorage->setMinPosition(fvec3(-FLT_MAX, (waterEntity->getHeight() - 1.0f), -FLT_MAX));
	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);

	_renderSkyEntity();
	_renderTerrainEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderAabbEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();

	_renderStorage->setWaterRefractionMap(_waterRefractionCaptureBuffer->getTexture(0));
	_renderStorage->setMinPosition(fvec3(-FLT_MAX));
	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);

	_waterRefractionCaptureBuffer->unbind();
}

void MasterRenderer::captureWaterEdges()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity != nullptr) && waterEntity->isEdged())
	{
		_waterOpacityCaptureBuffer->bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		if(_terrainEntityManager->getSelectedEntity() != nullptr)
		{
			_terrainEntityDepthRenderer->bind();

			_terrainEntityDepthRenderer->render(_terrainEntityManager->getSelectedEntity());

			_terrainEntityDepthRenderer->unbind();
		}

		_waterOpacityCaptureBuffer->unbind();

		_renderStorage->setWaterEdgeMap(_waterOpacityCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setWaterEdgeMap(nullptr);
	}
}
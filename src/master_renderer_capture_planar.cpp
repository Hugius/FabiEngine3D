#include "master_renderer.hpp"

void MasterRenderer::_capturePlanarReflections()
{
	bool anyReflectiveModelFound = false;

	for(const auto& [key, entity] : _modelEntityManager->getEntities())
	{
		for(const auto& partId : entity->getPartIds())
		{
			if(entity->isReflective(partId) && (entity->getReflectionType(partId) == ReflectionType::PLANAR) && entity->isVisible())
			{
				anyReflectiveModelFound = true;
				break;
			}
		}
	}

	if(!anyReflectiveModelFound)
	{
		_renderBus->setPlanarReflectionMap(nullptr);
		return;
	}

	float cameraDistance = (_camera->getPosition().y - _renderBus->getPlanarReflectionHeight());

	_planarReflectionCaptor->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelEntityIds;
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

	vector<string> savedQuad3dEntityIds;
	for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedQuad3dEntityIds.push_back(entity->getId());
		}
	}

	const fvec3 originalCameraPosition = _camera->getPosition();
	_camera->setPosition(fvec3(originalCameraPosition.x, originalCameraPosition.y - (cameraDistance * 2.0f), originalCameraPosition.z));

	const float originalCameraPitch = _camera->getPitch();
	_camera->setPitch(-originalCameraPitch);

	_camera->updateMatrices();

	_renderBus->setCameraPosition(originalCameraPosition);
	_renderBus->setCameraPitch(originalCameraPitch);

	_renderBus->setReflectionsEnabled(false);

	const auto originalSkyExposureLightness = _renderBus->getSkyExposureLightness();
	_renderBus->setSkyExposureLightness(0.0f);

	const float clippingHeight = -(_renderBus->getPlanarReflectionHeight() + 0.0001f);
	_renderBus->setMinPosition(fvec3(-FLT_MAX, clippingHeight, -FLT_MAX));

	_renderSkyEntity();
	_renderTerrainEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();

	_planarReflectionCaptor->unbind();

	_renderBus->setPlanarReflectionMap(_planarReflectionCaptor->getTexture(0));

	for(const auto& [key, entity] : _modelEntityManager->getEntities())
	{
		for(const auto& savedId : savedModelEntityIds)
		{
			if(entity->getId() == savedId)
			{
				entity->setVisible(true);
			}
		}
	}

	for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
	{
		for(const auto& savedId : savedQuad3dEntityIds)
		{
			if(entity->getId() == savedId)
			{
				entity->setVisible(true);
			}
		}
	}

	_camera->setPitch(originalCameraPitch);

	_camera->setPosition(originalCameraPosition);

	_camera->updateMatrices();

	_renderBus->setReflectionsEnabled(true);

	_renderBus->setSkyExposureLightness(originalSkyExposureLightness);
}
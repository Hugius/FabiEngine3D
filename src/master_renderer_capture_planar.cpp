#include "master_renderer.hpp"

void MasterRenderer::_capturePlanarReflections()
{
	vector<shared_ptr<ModelEntity>> reflectiveModelEntities;

	for(const auto& [key, entity] : _modelEntityManager->getEntities())
	{
		for(const auto& partId : entity->getPartIds())
		{
			if(entity->isReflective(partId) && entity->isVisible())
			{
				if(entity->getReflectionType(partId) == ReflectionType::PLANAR)
				{
					entity->setVisible(false);
					reflectiveModelEntities.push_back(entity);
					break;
				}
			}
		}
	}

	if(reflectiveModelEntities.empty())
	{
		_renderBus->setPlanarReflectionMap(nullptr);
		return;
	}

	_planarReflectionCaptor->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<shared_ptr<ModelEntity>> savedModelEntities;
	savedModelEntities.insert(savedModelEntities.end(), reflectiveModelEntities.begin(), reflectiveModelEntities.end());
	for(const auto& [key, entity] : _modelEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntities.push_back(entity);
		}
	}

	vector<shared_ptr<Quad3dEntity>> savedQuad3dEntities;
	for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedQuad3dEntities.push_back(entity);
		}
	}

	vector<shared_ptr<Text3dEntity>> savedText3dEntities;
	for(const auto& [key, entity] : _text3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedText3dEntities.push_back(entity);
		}
	}

	const auto cameraDistance = fabsf(_camera->getPosition().y - _renderBus->getPlanarReflectionHeight());
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalCameraPitch = _camera->getPitch();
	const auto originalSkyExposureLightness = _renderBus->getSkyExposureLightness();

	_camera->setPosition(fvec3(originalCameraPosition.x, (originalCameraPosition.y - (cameraDistance * 2.0f)), originalCameraPosition.z));
	_camera->setPitch(-originalCameraPitch);
	_camera->updateMatrices();

	_renderBus->setMinPosition(fvec3(-FLT_MAX, _renderBus->getPlanarReflectionHeight(), -FLT_MAX));
	_renderBus->setCameraPosition(originalCameraPosition);
	_renderBus->setCameraPitch(originalCameraPitch);
	_renderBus->setReflectionsEnabled(false);
	_renderBus->setRefractionsEnabled(false);
	_renderBus->setSkyExposureLightness(0.0f);

	_renderSkyEntity();
	_renderTerrainEntity();
	_renderWaterEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();

	for(const auto& entity : savedModelEntities)
	{
		entity->setVisible(true);
	}

	for(const auto& entity : savedQuad3dEntities)
	{
		entity->setVisible(true);
	}

	for(const auto& entity : savedText3dEntities)
	{
		entity->setVisible(true);
	}

	_camera->setPitch(originalCameraPitch);
	_camera->setPosition(originalCameraPosition);
	_camera->updateMatrices();

	_renderBus->setPlanarReflectionMap(_planarReflectionCaptor->getTexture(0));
	_renderBus->setMinPosition(fvec3(-FLT_MAX));
	_renderBus->setReflectionsEnabled(true);
	_renderBus->setRefractionsEnabled(true);
	_renderBus->setSkyExposureLightness(originalSkyExposureLightness);

	_planarReflectionCaptor->unbind();
}
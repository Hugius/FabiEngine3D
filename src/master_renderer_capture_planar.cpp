#include "master_renderer.hpp"

void MasterRenderer::capturePlanarReflections()
{
	vector<shared_ptr<ModelEntity>> reflectiveModelEntities;

	for(const auto & [entityId, entity] : _modelEntityManager->getEntities())
	{
		for(const auto & partId : entity->getPartIds())
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
		_renderStorage->setPlanarReflectionMap(nullptr);
		return;
	}

	_planarReflectionCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<shared_ptr<ModelEntity>> savedModelEntities;
	savedModelEntities.insert(savedModelEntities.end(), reflectiveModelEntities.begin(), reflectiveModelEntities.end());
	for(const auto & [entityId, entity] : _modelEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntities.push_back(entity);
		}
	}

	vector<shared_ptr<Quad3dEntity>> savedQuad3dEntities;
	for(const auto & [entityId, entity] : _quad3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedQuad3dEntities.push_back(entity);
		}
	}

	vector<shared_ptr<Text3dEntity>> savedText3dEntities;
	for(const auto & [entityId, entity] : _text3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedText3dEntities.push_back(entity);
		}
	}

	const auto cameraDistance = fabsf(_camera->getPosition().y - _renderStorage->getPlanarReflectionHeight());
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalCameraPitch = _camera->getPitch();
	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_camera->setPosition(fvec3(originalCameraPosition.x, (originalCameraPosition.y - (cameraDistance * 2.0f)), originalCameraPosition.z));
	_camera->setPitch(-originalCameraPitch);
	_camera->updateMatrices();
	_camera->setPosition(originalCameraPosition);
	_camera->setPitch(originalCameraPitch);

	_renderStorage->setMinClippingPosition(fvec3(-FLT_MAX, _renderStorage->getPlanarReflectionHeight(), -FLT_MAX));
	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);

	_renderSkyEntity();
	_renderTerrainEntity();
	_renderWaterEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderAabbEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();

	for(const auto & entity : savedModelEntities)
	{
		entity->setVisible(true);
	}

	for(const auto & entity : savedQuad3dEntities)
	{
		entity->setVisible(true);
	}

	for(const auto & entity : savedText3dEntities)
	{
		entity->setVisible(true);
	}

	_camera->updateMatrices();

	_renderStorage->setPlanarReflectionMap(_planarReflectionCaptureBuffer->getTexture(0));
	_renderStorage->setMinClippingPosition(fvec3(-FLT_MAX));
	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);

	_planarReflectionCaptureBuffer->unbind();
}
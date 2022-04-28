#include "master_renderer.hpp"

void MasterRenderer::capturePlanarReflections()
{
	vector<shared_ptr<ModelEntity>> reflectiveModelEntities;

	for(const auto & [modelId, model] : _modelEntityManager->getEntities())
	{
		for(const auto & partId : model->getPartIds())
		{
			if(model->isReflective(partId) && model->isVisible())
			{
				if(model->getReflectionType(partId) == ReflectionType::PLANAR)
				{
					model->setVisible(false);
					reflectiveModelEntities.push_back(model);

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
	for(const auto & [modelId, model] : _modelEntityManager->getEntities())
	{
		if(!model->isReflected() && model->isVisible())
		{
			model->setVisible(false);
			savedModelEntities.push_back(model);
		}
	}

	vector<shared_ptr<Quad3dEntity>> savedQuad3dEntities;
	for(const auto & [quad3dId, quad3d] : _quad3dEntityManager->getEntities())
	{
		if(!quad3d->isReflected() && quad3d->isVisible())
		{
			quad3d->setVisible(false);
			savedQuad3dEntities.push_back(quad3d);
		}
	}

	vector<shared_ptr<Text3dEntity>> savedText3dEntities;
	for(const auto & [text3dId, text3d] : _text3dEntityManager->getEntities())
	{
		if(!text3d->isReflected() && text3d->isVisible())
		{
			text3d->setVisible(false);
			savedText3dEntities.push_back(text3d);
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

	_renderStorage->setMinClipPosition(fvec3(-FLT_MAX, _renderStorage->getPlanarReflectionHeight(), -FLT_MAX));
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

	for(const auto & model : savedModelEntities)
	{
		model->setVisible(true);
	}

	for(const auto & quad3d : savedQuad3dEntities)
	{
		quad3d->setVisible(true);
	}

	for(const auto & text3d : savedText3dEntities)
	{
		text3d->setVisible(true);
	}

	_camera->updateMatrices();

	_renderStorage->setPlanarReflectionMap(_planarReflectionCaptureBuffer->getTexture(0));
	_renderStorage->setMinClipPosition(fvec3(-FLT_MAX));
	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);

	_planarReflectionCaptureBuffer->unbind();
}
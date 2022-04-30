#include "master_renderer.hpp"

void MasterRenderer::capturePlanarReflections()
{
	vector<shared_ptr<Model>> reflectiveModels;

	for(const auto & [modelId, model] : _modelManager->getModels())
	{
		for(const auto & partId : model->getPartIds())
		{
			if(model->isReflective(partId) && model->isVisible())
			{
				if(model->getReflectionType(partId) == ReflectionType::PLANAR)
				{
					model->setVisible(false);
					reflectiveModels.push_back(model);

					break;
				}
			}
		}
	}

	if(reflectiveModels.empty())
	{
		_renderStorage->setPlanarReflectionMap(nullptr);

		return;
	}

	_planarReflectionCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<shared_ptr<Model>> savedModels;
	savedModels.insert(savedModels.end(), reflectiveModels.begin(), reflectiveModels.end());
	for(const auto & [modelId, model] : _modelManager->getModels())
	{
		if(!model->isReflected() && model->isVisible())
		{
			model->setVisible(false);
			savedModels.push_back(model);
		}
	}

	vector<shared_ptr<Quad3d>> savedQuad3ds;
	for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
	{
		if(!quad3d->isReflected() && quad3d->isVisible())
		{
			quad3d->setVisible(false);
			savedQuad3ds.push_back(quad3d);
		}
	}

	vector<shared_ptr<Text3d>> savedText3ds;
	for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
	{
		if(!text3d->isReflected() && text3d->isVisible())
		{
			text3d->setVisible(false);
			savedText3ds.push_back(text3d);
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

	_renderSky();
	_renderTerrain();
	_renderWater();
	_renderOpaqueModels();
	_renderOpaqueQuad3ds();
	_renderOpaqueText3ds();
	_renderAabbs();
	_renderTransparentModels();
	_renderTransparentQuad3ds();
	_renderTransparentText3ds();

	for(const auto & model : savedModels)
	{
		model->setVisible(true);
	}

	for(const auto & quad3d : savedQuad3ds)
	{
		quad3d->setVisible(true);
	}

	for(const auto & text3d : savedText3ds)
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
#include "master_renderer.hpp"

void MasterRenderer::captureWaterReflections()
{
	const auto water = _waterManager->getSelectedWater();

	if((water == nullptr) || !water->isReflective())
	{
		_renderStorage->setWaterReflectionMap(nullptr);

		return;
	}

	if(_camera->getPosition().y < water->getHeight())
	{
		_renderStorage->setWaterReflectionMap(nullptr);

		return;
	}

	_waterReflectionCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelIds;
	for(const auto & [modelId, model] : _modelManager->getModels())
	{
		if(!model->isVisible())
		{
			continue;
		}

		if(!model->isReflected())
		{
			model->setVisible(false);
			savedModelIds.push_back(model->getId());
			continue;
		}

		for(const auto & partId : model->getPartIds())
		{
			if(model->isReflective(partId) && (model->getReflectionType(partId) == ReflectionType::PLANAR))
			{
				model->setVisible(false);
				savedModelIds.push_back(model->getId());

				break;
			}
		}
	}

	vector<string> savedQuad3dIds;
	for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
	{
		if(!quad3d->isReflected() && quad3d->isVisible())
		{
			quad3d->setVisible(false);
			savedQuad3dIds.push_back(quad3d->getId());
		}
	}

	vector<string> savedText3dIds;
	for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
	{
		if(!text3d->isReflected() && text3d->isVisible())
		{
			text3d->setVisible(false);
			savedText3dIds.push_back(text3d->getId());
		}
	}

	const auto cameraDistance = fabsf(_camera->getPosition().y - water->getHeight());
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalCameraPitch = _camera->getPitch();
	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_camera->setPosition(fvec3(originalCameraPosition.x, (originalCameraPosition.y - (cameraDistance * 2.0f)), originalCameraPosition.z));
	_camera->setPitch(-originalCameraPitch);
	_camera->updateMatrices();
	_camera->setPosition(originalCameraPosition);
	_camera->setPitch(originalCameraPitch);

	_renderStorage->setMinClipPosition(fvec3(-FLT_MAX, (water->getHeight() - 1.0f), -FLT_MAX));
	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);

	_renderSky();
	_renderTerrain();
	_renderOpaqueModels();
	_renderOpaqueQuad3ds();
	_renderOpaqueText3ds();
	_renderAabbs();
	_renderTransparentModels();
	_renderTransparentQuad3ds();
	_renderTransparentText3ds();

	for(const auto & savedId : savedModelIds)
	{
		for(const auto & [modelId, model] : _modelManager->getModels())
		{
			if(model->getId() == savedId)
			{
				model->setVisible(true);
			}
		}
	}

	for(const auto & savedId : savedQuad3dIds)
	{
		for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
		{
			if(quad3d->getId() == savedId)
			{
				quad3d->setVisible(true);
			}
		}
	}

	for(const auto & savedId : savedText3dIds)
	{
		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			if(text3d->getId() == savedId)
			{
				text3d->setVisible(true);
			}
		}
	}

	_camera->updateMatrices();

	_renderStorage->setWaterReflectionMap(_waterReflectionCaptureBuffer->getTexture(0));
	_renderStorage->setMinClipPosition(fvec3(-FLT_MAX));
	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);

	_waterReflectionCaptureBuffer->unbind();
}

void MasterRenderer::captureWaterRefractions()
{
	const auto water = _waterManager->getSelectedWater();

	if((water == nullptr) || !water->isRefractive())
	{
		_renderStorage->setWaterRefractionMap(nullptr);

		return;
	}

	if(_camera->getPosition().y > water->getHeight())
	{
		_renderStorage->setWaterRefractionMap(nullptr);

		return;
	}

	_waterRefractionCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelIds;
	for(const auto & [modelId, model] : _modelManager->getModels())
	{
		if(!model->isVisible())
		{
			continue;
		}

		if(!model->isRefracted())
		{
			model->setVisible(false);
			savedModelIds.push_back(model->getId());

			continue;
		}

		for(const auto & partId : model->getPartIds())
		{
			if(model->isRefractive(partId) && (model->getRefractionType(partId) == RefractionType::PLANAR))
			{
				model->setVisible(false);
				savedModelIds.push_back(model->getId());

				break;
			}
		}
	}

	vector<string> savedQuad3dIds;
	for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
	{
		if(!quad3d->isRefracted() && quad3d->isVisible())
		{
			quad3d->setVisible(false);
			savedQuad3dIds.push_back(quad3d->getId());
		}
	}

	vector<string> savedText3dIds;
	for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
	{
		if(!text3d->isRefracted() && text3d->isVisible())
		{
			text3d->setVisible(false);
			savedText3dIds.push_back(text3d->getId());
		}
	}

	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_renderStorage->setMinClipPosition(fvec3(-FLT_MAX, (water->getHeight() - 1.0f), -FLT_MAX));
	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);

	_renderSky();
	_renderTerrain();
	_renderOpaqueModels();
	_renderOpaqueQuad3ds();
	_renderOpaqueText3ds();
	_renderAabbs();
	_renderTransparentModels();
	_renderTransparentQuad3ds();
	_renderTransparentText3ds();

	for(const auto & savedId : savedModelIds)
	{
		for(const auto & [modelId, model] : _modelManager->getModels())
		{
			if(model->getId() == savedId)
			{
				model->setVisible(true);
			}
		}
	}

	for(const auto & savedId : savedQuad3dIds)
	{
		for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
		{
			if(quad3d->getId() == savedId)
			{
				quad3d->setVisible(true);
			}
		}
	}

	for(const auto & savedId : savedText3dIds)
	{
		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			if(text3d->getId() == savedId)
			{
				text3d->setVisible(true);
			}
		}
	}

	_renderStorage->setWaterRefractionMap(_waterRefractionCaptureBuffer->getTexture(0));
	_renderStorage->setMinClipPosition(fvec3(-FLT_MAX));
	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);

	_waterRefractionCaptureBuffer->unbind();
}

void MasterRenderer::captureWaterEdges()
{
	const auto water = _waterManager->getSelectedWater();

	if((water != nullptr) && water->isEdged())
	{
		_waterOpacityCaptureBuffer->bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		if(_terrainManager->getSelectedTerrain() != nullptr)
		{
			_terrainDepthRenderer->bind();

			_terrainDepthRenderer->render(_terrainManager->getSelectedTerrain());

			_terrainDepthRenderer->unbind();
		}

		_waterOpacityCaptureBuffer->unbind();

		_renderStorage->setWaterEdgeMap(_waterOpacityCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setWaterEdgeMap(nullptr);
	}
}
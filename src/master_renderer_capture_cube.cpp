#include "master_renderer.hpp"

using std::make_shared;

void MasterRenderer::captureCubeReflections()
{
	if(_captorManager->getCaptors().empty())
	{
		return;
	}

	vector<shared_ptr<Model>> savedModels = {};

	for(const auto & [modelId, model] : _modelManager->getModels())
	{
		if(!model->isReflected() && model->isVisible())
		{
			model->setVisible(false);

			savedModels.push_back(model);
		}
	}

	vector<shared_ptr<Quad3d>> savedQuad3ds = {};

	for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
	{
		if(!quad3d->isReflected() && quad3d->isVisible())
		{
			quad3d->setVisible(false);

			savedQuad3ds.push_back(quad3d);
		}
	}

	vector<shared_ptr<Text3d>> savedText3ds = {};

	for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
	{
		if(!text3d->isReflected() && text3d->isVisible())
		{
			text3d->setVisible(false);

			savedText3ds.push_back(text3d);
		}
	}

	const auto originalCameraAspectRatio = _camera->getAspectRatio();
	const auto originalCameraFOV = _camera->getFov();
	const auto originalCameraYaw = _camera->getYaw();
	const auto originalCameraPitch = _camera->getPitch();
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalShadowInterval = _renderStorage->getShadowInterval();
	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_camera->invertUp();
	_camera->setAspectRatio(1.0f);
	_camera->setFov(90.0f);

	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);
	_renderStorage->setShadowInterval(0);

	for(const auto & [captorId, captor] : _captorManager->getCaptors())
	{
		if(captor->mustCaptureReflections())
		{
			const auto captureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(captor->getReflectionQuality()), 1, false);
			const auto wasExceptionModelVisible = (captor->getExceptionId().empty() ? false : _modelManager->getModel(captor->getExceptionId())->isVisible());

			if(!captor->getExceptionId().empty())
			{
				_modelManager->getModel(captor->getExceptionId())->setVisible(false);
			}

			_camera->setPosition(captor->getPosition());

			unsigned int textureId;

			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			for(int index = 0; index < 6; index++)
			{
				switch(index)
				{
					case 0:
					{
						_camera->setYaw(0.0f);
						_camera->setPitch(0.0f);

						break;
					}
					case 1:
					{
						_camera->setYaw(180.0f);
						_camera->setPitch(0.0f);

						break;
					}
					case 2:
					{
						_camera->setYaw(90.0f);
						_camera->setPitch(90.0f);

						break;
					}
					case 3:
					{
						_camera->setYaw(90.0f);
						_camera->setPitch(-90.0f);

						break;
					}
					case 4:
					{
						_camera->setYaw(90.0f);
						_camera->setPitch(0.0f);

						break;
					}
					case 5:
					{
						_camera->setYaw(270.0f);
						_camera->setPitch(0.0f);

						break;
					}
				}

				_camera->updateMatrices();

				_updateShadows();

				captureShadows();
				captureWaterEdges();

				captureBuffer->bind();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

				captureBuffer->unbind();

				const auto dataSize = (captor->getReflectionQuality() * captor->getReflectionQuality() * 3);
				const auto data = new unsigned char[dataSize];

				glBindTexture(GL_TEXTURE_2D, captureBuffer->getTexture(0)->getTboId());
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);

				glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
				glTexImage2D(cubeIndex, 0, GL_RGB, captor->getReflectionQuality(), captor->getReflectionQuality(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				delete[] data;
			}

			captor->setReflectionCubeMap(make_shared<TextureBuffer>(textureId));
			captor->setReflectionsCaptured();

			if(!captor->getExceptionId().empty())
			{
				_modelManager->getModel(captor->getExceptionId())->setVisible(wasExceptionModelVisible);
			}
		}
	}

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

	_camera->invertUp();
	_camera->setAspectRatio(originalCameraAspectRatio);
	_camera->setFov(originalCameraFOV);
	_camera->setPosition(originalCameraPosition);
	_camera->setYaw(originalCameraYaw);
	_camera->setPitch(originalCameraPitch);
	_camera->updateMatrices();

	_updateShadows();

	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);
	_renderStorage->setShadowInterval(originalShadowInterval);

	captureShadows();
	captureWaterEdges();

}

void MasterRenderer::captureCubeRefractions()
{
	if(_captorManager->getCaptors().empty())
	{
		return;
	}

	vector<shared_ptr<Model>> savedModels = {};

	for(const auto & [modelId, model] : _modelManager->getModels())
	{
		if(!model->isRefracted() && model->isVisible())
		{
			model->setVisible(false);

			savedModels.push_back(model);
		}
	}

	vector<shared_ptr<Quad3d>> savedQuad3ds = {};

	for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
	{
		if(!quad3d->isRefracted() && quad3d->isVisible())
		{
			quad3d->setVisible(false);

			savedQuad3ds.push_back(quad3d);
		}
	}

	vector<shared_ptr<Text3d>> savedText3ds = {};

	for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
	{
		if(!text3d->isRefracted() && text3d->isVisible())
		{
			text3d->setVisible(false);

			savedText3ds.push_back(text3d);
		}
	}

	const auto originalCameraAspectRatio = _camera->getAspectRatio();
	const auto originalCameraFOV = _camera->getFov();
	const auto originalCameraYaw = _camera->getYaw();
	const auto originalCameraPitch = _camera->getPitch();
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalShadowInterval = _renderStorage->getShadowInterval();
	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	_camera->invertUp();
	_camera->setAspectRatio(1.0f);
	_camera->setFov(90.0f);

	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);
	_renderStorage->setShadowInterval(0);

	for(const auto & [captorId, captor] : _captorManager->getCaptors())
	{
		if(captor->mustCaptureRefractions())
		{
			const auto captureBuffer = make_shared<CaptureBuffer>(ivec2(0), ivec2(captor->getRefractionQuality()), 1, false);
			const auto wasExceptionModelVisible = (captor->getExceptionId().empty() ? false : _modelManager->getModel(captor->getExceptionId())->isVisible());

			if(!captor->getExceptionId().empty())
			{
				_modelManager->getModel(captor->getExceptionId())->setVisible(false);
			}

			_camera->setPosition(captor->getPosition());

			unsigned int textureId;

			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			for(int index = 0; index < 6; index++)
			{
				switch(index)
				{
					case 0:
					{
						_camera->setYaw(0.0f);
						_camera->setPitch(0.0f);

						break;
					}
					case 1:
					{
						_camera->setYaw(180.0f);
						_camera->setPitch(0.0f);

						break;
					}
					case 2:
					{
						_camera->setYaw(90.0f);
						_camera->setPitch(90.0f);

						break;
					}
					case 3:
					{
						_camera->setYaw(90.0f);
						_camera->setPitch(-90.0f);

						break;
					}
					case 4:
					{
						_camera->setYaw(90.0f);
						_camera->setPitch(0.0f);

						break;
					}
					case 5:
					{
						_camera->setYaw(270.0f);
						_camera->setPitch(0.0f);

						break;
					}
				}

				_camera->updateMatrices();

				_updateShadows();

				captureShadows();
				captureWaterEdges();

				captureBuffer->bind();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

				captureBuffer->unbind();

				const auto dataSize = (captor->getRefractionQuality() * captor->getRefractionQuality() * 3);
				const auto data = new unsigned char[dataSize];

				glBindTexture(GL_TEXTURE_2D, captureBuffer->getTexture(0)->getTboId());
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);

				glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
				glTexImage2D(cubeIndex, 0, GL_RGB, captor->getRefractionQuality(), captor->getRefractionQuality(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				delete[] data;
			}

			captor->setRefractionCubeMap(make_shared<TextureBuffer>(textureId));
			captor->setRefractionsCaptured();

			if(!captor->getExceptionId().empty())
			{
				_modelManager->getModel(captor->getExceptionId())->setVisible(wasExceptionModelVisible);
			}
		}
	}

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

	_camera->invertUp();
	_camera->setAspectRatio(originalCameraAspectRatio);
	_camera->setFov(originalCameraFOV);
	_camera->setPosition(originalCameraPosition);
	_camera->setYaw(originalCameraYaw);
	_camera->setPitch(originalCameraPitch);
	_camera->updateMatrices();

	_updateShadows();

	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);
	_renderStorage->setShadowInterval(originalShadowInterval);

	captureShadows();
	captureWaterEdges();
}
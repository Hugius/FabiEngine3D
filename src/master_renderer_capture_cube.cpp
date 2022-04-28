#include "master_renderer.hpp"

using std::make_shared;

void MasterRenderer::captureCubeReflections()
{
	if(_captorEntityManager->getEntities().empty())
	{
		return;
	}

	vector<shared_ptr<ModelEntity>> savedModelEntities;
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

	for(const auto & [captorId, captor] : _captorEntityManager->getEntities())
	{
		if(captor->mustCapture())
		{
			const auto wasExceptionEntityVisible = (captor->getExceptionEntityId().empty() ? false : _modelEntityManager->getEntity(captor->getExceptionEntityId())->isVisible());
			if(!captor->getExceptionEntityId().empty())
			{
				_modelEntityManager->getEntity(captor->getExceptionEntityId())->setVisible(false);
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

				_cubeReflectionCaptureBuffer->bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
				_cubeReflectionCaptureBuffer->unbind();

				const auto dataSize = (_renderStorage->getCubeReflectionQuality() * _renderStorage->getCubeReflectionQuality() * 3);
				auto data = new unsigned char[dataSize];
				glBindTexture(GL_TEXTURE_2D, _cubeReflectionCaptureBuffer->getTexture(0)->getTboId());
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);
				glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
				glTexImage2D(cubeIndex, 0, GL_RGB, _renderStorage->getCubeReflectionQuality(), _renderStorage->getCubeReflectionQuality(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				delete[] data;
			}

			captor->setCubeMap(make_shared<TextureBuffer>(textureId));
			captor->setCaptured();

			if(!captor->getExceptionEntityId().empty())
			{
				_modelEntityManager->getEntity(captor->getExceptionEntityId())->setVisible(wasExceptionEntityVisible);
			}
		}
	}

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

	_camera->invertUp();
	_camera->setAspectRatio(originalCameraAspectRatio);
	_camera->setFov(originalCameraFOV);
	_camera->setPosition(originalCameraPosition);
	_camera->setYaw(originalCameraYaw);
	_camera->setPitch(originalCameraPitch);
	_camera->updateMatrices();

	_renderStorage->setReflectionsEnabled(true);
	_renderStorage->setRefractionsEnabled(true);
	_renderStorage->setSkyExposureEnabled(wasSkyExposureEnabled);
	_renderStorage->setShadowInterval(originalShadowInterval);

	_updateShadows();
}
#include "master_renderer.hpp"

void MasterRenderer::_captureCubeReflections()
{
	if(_reflectionEntityManager->getEntities().empty())
	{
		return;
	}

	vector<shared_ptr<ModelEntity>> savedModelEntities;
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

	const auto originalCameraAspectRatio = _camera->getAspectRatio();
	const auto originalCameraFOV = _camera->getFov();
	const auto originalCameraYaw = _camera->getYaw();
	const auto originalCameraPitch = _camera->getPitch();
	const auto originalCameraPosition = _camera->getPosition();
	const auto originalShadowInterval = _renderStorage->getShadowInterval();
	const auto wasSkyExposureEnabled = _renderStorage->isSkyExposureEnabled();

	//_camera->invertUpDirection();
	_camera->setAspectRatio(1.0f);
	_camera->setFov(90.0f);

	_renderStorage->setReflectionsEnabled(false);
	_renderStorage->setRefractionsEnabled(false);
	_renderStorage->setSkyExposureEnabled(false);
	_renderStorage->setShadowInterval(0);

	for(const auto& [key, entity] : _reflectionEntityManager->getEntities())
	{
		if(entity->mustCapture())
		{
			_camera->setPosition(entity->getPosition());

			BufferId textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			for(unsigned int i = 0; i < 6; i++)
			{
				switch(i)
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
						_camera->setPitch(270.0f);
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
				_captureShadows();

				_cubeReflectionCaptor->bind();
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
				_cubeReflectionCaptor->unbind();

				const auto dataSize = (_renderStorage->getCubeReflectionQuality() * _renderStorage->getCubeReflectionQuality() * 3);
				auto data = new unsigned char[dataSize];
				glBindTexture(GL_TEXTURE_2D, _cubeReflectionCaptor->getTexture(0)->getId());
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
				glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
				glTexImage2D(cubeIndex, 0, GL_RGB, _renderStorage->getCubeReflectionQuality(), _renderStorage->getCubeReflectionQuality(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			entity->setCubeMap(make_shared<TextureBuffer>(textureId));
			entity->setCaptured();
		}
	}

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

	//_camera->invertUpDirection();
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
#include "master_renderer.hpp"

void MasterRenderer::_captureCubeReflections()
{
	if(_reflectionEntityManager->getEntities().empty())
	{
		return;
	}

	const auto reflectionQuality = _renderBus->getCubeReflectionQuality();

	const auto originalCameraAspectRatio = _camera->getAspectRatio();
	const auto originalCameraFOV = _camera->getFOV();
	const auto originalCameraYaw = _camera->getYaw();
	const auto originalCameraPitch = _camera->getPitch();
	const auto originalCameraPosition = _camera->getPosition();

	vector<string> savedModelEntityIDs;
	for(const auto& [key, entity] : _modelEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
		}
	}

	vector<string> savedQuad3dEntityIDs;
	for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedQuad3dEntityIDs.push_back(entity->getID());
		}
	}

	_renderBus->setReflectionsEnabled(false);

	float originalSkyExposureLightness = _renderBus->getSkyExposureLightness();
	_renderBus->setSkyExposureLightness(0.0f);

	const auto originalShadowInterval = _renderBus->getShadowInterval();
	_renderBus->setShadowInterval(0);

	_camera->invertUpVector();
	_camera->setAspectRatio(1.0f);
	_camera->setFOV(90.0f);

	for(const auto& [key, entity] : _reflectionEntityManager->getEntities())
	{
		if(entity->mustCapture())
		{
			BufferID textureID;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			for(unsigned int i = 0; i < 6; i++)
			{
				_camera->setPosition(entity->getPosition());

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
				_renderTransparentModelEntities();
				_renderTransparentQuad3dEntities();
				_renderTransparentText3dEntities();
				_cubeReflectionCaptor->unbind();

				const auto dataSize = (reflectionQuality * reflectionQuality * 3);
				auto data = new unsigned char[dataSize];
				glBindTexture(GL_TEXTURE_2D, _cubeReflectionCaptor->getTexture(0)->getID());
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				const auto cubeIndex = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
				glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
				glTexImage2D(cubeIndex, 0, GL_RGB, reflectionQuality, reflectionQuality, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			entity->setCubeMap(make_shared<TextureBuffer>(textureID));
			entity->setCaptured();
		}
	}

	for(const auto& [key, entity] : _modelEntityManager->getEntities())
	{
		for(const auto& savedID : savedModelEntityIDs)
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	for(const auto& savedID : savedQuad3dEntityIDs)
	{
		for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	_camera->invertUpVector();
	_camera->setAspectRatio(originalCameraAspectRatio);
	_camera->setFOV(originalCameraFOV);
	_camera->setYaw(originalCameraYaw);
	_camera->setPitch(originalCameraPitch);
	_camera->setPosition(originalCameraPosition);
	_camera->updateMatrices();

	_renderBus->setShadowInterval(originalShadowInterval);
	_updateShadows();

	_renderBus->setSkyExposureLightness(originalSkyExposureLightness);

	_renderBus->setReflectionsEnabled(true);
}
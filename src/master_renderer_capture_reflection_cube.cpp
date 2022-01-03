#include "master_renderer.hpp"

void MasterRenderer::_captureCubeReflections()
{
	if(_entityBus->getReflectionEntities().empty())
	{
		return;
	}

	const auto reflectionQuality = _renderBus.getCubeReflectionQuality();

	const auto initialCameraAspectRatio = _camera.getAspectRatio();
	const auto initialCameraFOV = _camera.getFOV();
	const auto initialCameraYaw = _camera.getYaw();
	const auto initialCameraPitch = _camera.getPitch();
	const auto initialCameraPosition = _camera.getPosition();

	vector<string> savedModelEntityIDs;
	for(const auto& [key, entity] : _entityBus->getModelEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
		}
	}

	vector<string> savedBillboardEntityIDs;
	for(const auto& [key, entity] : _entityBus->getBillboardEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedBillboardEntityIDs.push_back(entity->getID());
		}
	}

	_renderBus.setReflectionsEnabled(false);

	float oldLightness = 0.0f;
	auto skyEntity = _entityBus->getMainSkyEntity();
	if(skyEntity != nullptr)
	{
		oldLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getInitialLightness());
	}

	_camera.invertUpVector();
	_camera.setAspectRatio(1.0f);
	_camera.setFOV(90.0f);

	for(const auto& [key, entity] : _entityBus->getReflectionEntities())
	{
		if(entity->mustCapture())
		{
			for(unsigned int i = 0; i < 6; i++)
			{
				_camera.setPosition(entity->getPosition());

				switch(i)
				{
					case 0:
					{
						_camera.setYaw(0.0f);
						_camera.setPitch(0.0f);
						break;
					}
					case 1:
					{
						_camera.setYaw(180.0f);
						_camera.setPitch(0.0f);
						break;
					}
					case 2:
					{
						_camera.setYaw(90.0f);
						_camera.setPitch(90.0f);
						break;
					}
					case 3:
					{
						_camera.setYaw(90.0f);
						_camera.setPitch(270.0f);
						break;
					}
					case 4:
					{
						_camera.setYaw(90.0f);
						_camera.setPitch(0.0f);
						break;
					}
					case 5:
					{
						_camera.setYaw(270.0f);
						_camera.setPitch(0.0f);
						break;
					}
				}

				_camera.updateMatrices();

				_shadowGenerator.generate();
				_captureShadows();

				_cubeReflectionCaptureBuffer->bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				_renderSkyEntity();
				_renderTerrainEntity();
				_renderModelEntities();

				_cubeReflectionCaptureBuffer->unbind();

				const auto dataSize = (reflectionQuality * reflectionQuality * 3);
				auto data = new unsigned char[dataSize];
				glBindTexture(GL_TEXTURE_2D, _cubeReflectionCaptureBuffer->getTexture(0)->getID());
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				const auto index = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
				glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getCubeMap()->getID());
				glTexImage2D(index, 0, GL_RGB, reflectionQuality, reflectionQuality, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			entity->setCaptured();
		}
	}

	for(const auto& [key, entity] : _entityBus->getModelEntities())
	{
		for(const auto& savedID : savedModelEntityIDs)
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	for(const auto& savedID : savedBillboardEntityIDs)
	{
		for(const auto& [key, entity] : _entityBus->getBillboardEntities())
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	_renderBus.setReflectionsEnabled(true);

	if(skyEntity != nullptr)
	{
		skyEntity->setLightness(oldLightness);
	}

	_camera.invertUpVector();
	_camera.setAspectRatio(initialCameraAspectRatio);
	_camera.setFOV(initialCameraFOV);
	_camera.setYaw(initialCameraYaw);
	_camera.setPitch(initialCameraPitch);
	_camera.setPosition(initialCameraPosition);
	_camera.updateMatrices();

	_shadowGenerator.generate();
}
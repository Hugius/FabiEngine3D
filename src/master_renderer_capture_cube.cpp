#include "master_renderer.hpp"

void MasterRenderer::_captureCubeReflections(ShadowGenerator& shadowGenerator, Camera& camera, EntityBus& entityBus)
{
	if(entityBus.getReflectionEntities().empty())
	{
		return;
	}

	const auto reflectionQuality = _renderBus.getCubeReflectionQuality();

	const auto initialCameraAspectRatio = camera.getAspectRatio();
	const auto initialCameraFOV = camera.getFOV();
	const auto initialCameraYaw = camera.getYaw();
	const auto initialCameraPitch = camera.getPitch();
	const auto initialCameraPosition = camera.getPosition();

	vector<string> savedModelEntityIDs;
	for(const auto& [key, entity] : entityBus.getModelEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
		}
	}

	vector<string> savedBillboardEntityIDs;
	for(const auto& [key, entity] : entityBus.getBillboardEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedBillboardEntityIDs.push_back(entity->getID());
		}
	}

	_renderBus.setReflectionsEnabled(false);

	float oldLightness = 0.0f;
	auto skyEntity = entityBus.getMainSkyEntity();
	if(skyEntity != nullptr)
	{
		oldLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getInitialLightness());
	}

	camera.invertUpVector();
	camera.setAspectRatio(1.0f);
	camera.setFOV(90.0f);

	for(const auto& [key, entity] : entityBus.getReflectionEntities())
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
				camera.setPosition(entity->getPosition());

				switch(i)
				{
					case 0:
					{
						camera.setYaw(0.0f);
						camera.setPitch(0.0f);
						break;
					}
					case 1:
					{
						camera.setYaw(180.0f);
						camera.setPitch(0.0f);
						break;
					}
					case 2:
					{
						camera.setYaw(90.0f);
						camera.setPitch(90.0f);
						break;
					}
					case 3:
					{
						camera.setYaw(90.0f);
						camera.setPitch(270.0f);
						break;
					}
					case 4:
					{
						camera.setYaw(90.0f);
						camera.setPitch(0.0f);
						break;
					}
					case 5:
					{
						camera.setYaw(270.0f);
						camera.setPitch(0.0f);
						break;
					}
				}

				camera.updateMatrices(_renderBus);

				shadowGenerator.generate(_renderBus);
				_captureShadows(entityBus);

				_cubeReflectionCaptor->bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				_renderSkyEntity(entityBus);
				_renderTerrainEntity(entityBus);
				_renderModelEntities(entityBus);
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

	for(const auto& [key, entity] : entityBus.getModelEntities())
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
		for(const auto& [key, entity] : entityBus.getBillboardEntities())
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

	camera.invertUpVector();
	camera.setAspectRatio(initialCameraAspectRatio);
	camera.setFOV(initialCameraFOV);
	camera.setYaw(initialCameraYaw);
	camera.setPitch(initialCameraPitch);
	camera.setPosition(initialCameraPosition);
	camera.updateMatrices(_renderBus);

	shadowGenerator.generate(_renderBus);
}
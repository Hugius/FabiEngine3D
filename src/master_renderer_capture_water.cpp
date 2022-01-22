#include "master_renderer.hpp"

void MasterRenderer::_captureWaterReflections()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity != nullptr) && waterEntity->isReflective())
	{
		float cameraDistance = (_camera->getPosition().y - waterEntity->getHeight());

		_waterReflectionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<string> savedModelEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			for(const auto& [key, entity] : _modelEntityManager->getEntities())
			{
				if(entity->isVisible())
				{
					if(!entity->isReflected())
					{
						entity->setVisible(false);
						savedModelEntityIDs.push_back(entity->getID());
						continue;
					}

					for(const auto& partID : entity->getPartIDs())
					{
						if(entity->isReflective(partID) && (entity->getReflectionType(partID) == ReflectionType::PLANAR))
						{
							entity->setVisible(false);
							savedModelEntityIDs.push_back(entity->getID());
							break;
						}
					}
				}
			}
		}

		vector<string> savedQuad3dEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
			{
				if(!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedQuad3dEntityIDs.push_back(entity->getID());
				}
			}
		}

		const fvec3 initialCameraPosition = _camera->getPosition();
		_camera->setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

		const float initialCameraPitch = _camera->getPitch();
		_camera->setPitch(-initialCameraPitch);

		_camera->updateMatrices();

		_renderBus->setCameraPosition(initialCameraPosition);
		_renderBus->setCameraPitch(initialCameraPitch);

		_renderBus->setReflectionsEnabled(false);

		bool wasShadowsEnabled = _renderBus->isShadowsEnabled();
		_renderBus->setShadowsEnabled(false);

		float oldLightness = 0.0f;
		auto skyEntity = _skyEntityManager->getSelectedEntity();
		if(skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		const float clippingHeight = -(waterEntity->getHeight());
		const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
		_renderBus->setClippingPlane(clippingPlane);

		_renderSkyEntity();

		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderQuad3dEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		_waterReflectionCaptor->unbind();

		_renderBus->setWaterReflectionMap(_waterReflectionCaptor->getTexture(0));

		for(const auto& savedID : savedModelEntityIDs)
		{
			for(const auto& [key, entity] : _modelEntityManager->getEntities())
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

		_camera->setPitch(initialCameraPitch);

		_camera->setPosition(initialCameraPosition);

		_camera->updateMatrices();

		_renderBus->setReflectionsEnabled(true);

		_renderBus->setShadowsEnabled(wasShadowsEnabled);

		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldLightness);
		}
	}
	else
	{
		_renderBus->setWaterReflectionMap(nullptr);
	}
}

void MasterRenderer::_captureWaterRefractions()
{
	const auto waterEntity = _waterEntityManager->getSelectedEntity();

	if((waterEntity != nullptr) && waterEntity->isRefractive())
	{
		_waterRefractionCaptor->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool wasShadowsEnabled = _renderBus->isShadowsEnabled();
		if((waterEntity->getQuality() == WaterQuality::SKY) || (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN))
		{
			_renderBus->setShadowsEnabled(false);
		}

		float oldSkyLightness = 0.0f;
		auto skyEntity = _skyEntityManager->getSelectedEntity();
		if(skyEntity != nullptr)
		{
			oldSkyLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		const float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		bool isUnderWater = (_camera->getPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (_camera->getPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_camera->getPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_camera->getPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_camera->getPosition().z < (waterEntity->getSize() / 2.0f)));

		if(isUnderWater)
		{
			const float clippingHeight = -(waterEntity->getHeight());
			const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
			_renderBus->setClippingPlane(clippingPlane);
		}
		else
		{
			const float clippingHeight = (waterEntity->getHeight() + waveHeight);
			const fvec4 clippingPlane = fvec4(0.0f, -1.0f, 0.0f, clippingHeight);
			_renderBus->setClippingPlane(clippingPlane);
		}

		_renderSkyEntity();

		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		if((waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL) ||
		   (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D))
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODEL_QUAD3D)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderQuad3dEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		_renderBus->setShadowsEnabled(wasShadowsEnabled);

		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}

		_waterRefractionCaptor->unbind();

		_renderBus->setWaterRefractionMap(_waterRefractionCaptor->getTexture(0));
	}
	else
	{
		_renderBus->setWaterRefractionMap(nullptr);
	}
}
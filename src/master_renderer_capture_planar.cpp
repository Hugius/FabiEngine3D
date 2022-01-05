#include "master_renderer.hpp"

void MasterRenderer::_capturePlanarReflections()
{
	bool anyReflectiveModelFound = false;

	for(const auto& [key, entity] : entityBus.getModelEntities())
	{
		for(const auto& partID : entity->getPartIDs())
		{
			if(entity->isReflective(partID) && (entity->getReflectionType(partID) == ReflectionType::PLANAR) && entity->isVisible())
			{
				anyReflectiveModelFound = true;
				break;
			}
		}
	}

	if(!anyReflectiveModelFound)
	{
		renderBus->setPlanarReflectionMap(0);
		return;
	}

	float cameraDistance = (camera.getPosition().y - renderBus->getPlanarReflectionHeight());

	_planarReflectionCaptor->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelEntityIDs;
	for(const auto& [key, entity] : entityBus.getModelEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
			continue;
		}

		for(const auto& partID : entity->getPartIDs())
		{
			if(entity->isReflective(partID) && (entity->getReflectionType(partID) == ReflectionType::PLANAR) && entity->isVisible())
			{
				entity->setVisible(false);
				savedModelEntityIDs.push_back(entity->getID());
				break;
			}
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

	const fvec3 initialCameraPosition = camera.getPosition();
	camera.setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

	const float initialCameraPitch = camera.getPitch();
	camera.setPitch(-initialCameraPitch);

	camera.updateMatrices(renderBus);

	renderBus->setCameraPosition(initialCameraPosition);
	renderBus->setCameraPitch(initialCameraPitch);

	renderBus->setReflectionsEnabled(false);

	float oldSkyLightness = 0.0f;
	auto skyEntity = entityBus.getMainSkyEntity();
	if(skyEntity != nullptr)
	{
		oldSkyLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getInitialLightness());
	}

	const float clippingHeight = -(renderBus->getPlanarReflectionHeight() + 0.0000001f);
	const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
	renderBus->setClippingPlane(clippingPlane);

	_renderSkyEntity(renderBus, entityBus);

	glEnable(GL_CLIP_DISTANCE0);
	_renderTerrainEntity(renderBus, entityBus);
	glDisable(GL_CLIP_DISTANCE0);

	glEnable(GL_CLIP_DISTANCE2);
	_renderModelEntities(renderBus, entityBus);
	_renderBillboardEntities(renderBus, entityBus);
	glDisable(GL_CLIP_DISTANCE2);

	_planarReflectionCaptor->unbind();

	renderBus->setPlanarReflectionMap(_planarReflectionCaptor->getTexture(0));

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

	for(const auto& [key, entity] : entityBus.getBillboardEntities())
	{
		for(const auto& savedID : savedBillboardEntityIDs)
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	camera.setPitch(initialCameraPitch);

	camera.setPosition(initialCameraPosition);

	camera.updateMatrices(renderBus);

	renderBus->setReflectionsEnabled(true);

	if(skyEntity != nullptr)
	{
		skyEntity->setLightness(oldSkyLightness);
	}
}
#include "master_renderer.hpp"

void MasterRenderer::_capturePlanarReflections()
{
	bool anyReflectiveModelFound = false;

	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
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
		_renderBus.setPlanarReflectionMap(0);
		return;
	}

	float cameraDistance = (_camera.getPosition().y - _renderBus.getPlanarReflectionHeight());

	_planarReflectionCaptureBuffer.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<string> savedModelEntityIDs;
	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
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
	for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedBillboardEntityIDs.push_back(entity->getID());
		}
	}

	const fvec3 initialCameraPosition = _camera.getPosition();
	_camera.setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

	const float initialCameraPitch = _camera.getPitch();
	_camera.setPitch(-initialCameraPitch);

	_camera.updateMatrices();

	_renderBus.setCameraPosition(initialCameraPosition);
	_renderBus.setCameraPitch(initialCameraPitch);

	_renderBus.setReflectionsEnabled(false);

	float oldSkyLightness = 0.0f;
	auto skyEntity = _entityBus->getMainSkyEntity();
	if(skyEntity != nullptr)
	{
		oldSkyLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getInitialLightness());
	}

	const float clippingHeight = -(_renderBus.getPlanarReflectionHeight() + 0.0000001f);
	const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
	_renderBus.setClippingPlane(clippingPlane);

	_renderSkyEntity();

	glEnable(GL_CLIP_DISTANCE0);
	_renderTerrainEntity();
	glDisable(GL_CLIP_DISTANCE0);

	glEnable(GL_CLIP_DISTANCE2);
	_renderModelEntities();
	_renderBillboardEntities();
	glDisable(GL_CLIP_DISTANCE2);

	_planarReflectionCaptureBuffer.unbind();

	_renderBus.setPlanarReflectionMap(_planarReflectionCaptureBuffer.getTexture(0));

	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		for(const auto& savedID : savedModelEntityIDs)
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		for(const auto& savedID : savedBillboardEntityIDs)
		{
			if(entity->getID() == savedID)
			{
				entity->setVisible(true);
			}
		}
	}

	_camera.setPitch(initialCameraPitch);

	_camera.setPosition(initialCameraPosition);

	_camera.updateMatrices();

	_renderBus.setReflectionsEnabled(true);

	if(skyEntity != nullptr)
	{
		skyEntity->setLightness(oldSkyLightness);
	}
}
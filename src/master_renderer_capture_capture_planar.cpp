#include "master_renderer.hpp"

void MasterRenderer::_capturePlanarReflections()
{
	// Temporary values
	bool anyReflectiveModelFound = false;

	// Search for any reflective model entity
	for (const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		for (const auto& partID : entity->getPartIDs())
		{
			if (entity->isReflective(partID) && (entity->getReflectionType(partID) == ReflectionType::PLANAR) && entity->isVisible())
			{
				anyReflectiveModelFound = true;
				break;
			}
		}
	}

	// Check if no planar reflections needed
	if (!anyReflectiveModelFound)
	{
		_renderBus.setPlanarReflectionMap(0);
		return;
	}

	// Calculate distance between camera and reflection surface
	float cameraDistance = (_camera.getPosition().y - _renderBus.getPlanarReflectionHeight());

	// Start capturing reflections
	_planarReflectionCaptureBuffer.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Iterate through all model entities
	vector<string> savedModelEntityIDs;
	for (const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Hide non-reflected model entity
		if (!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
			continue;
		}

		// Hide reflective model entity
		for (const auto& partID : entity->getPartIDs())
		{
			if (entity->isReflective(partID) && (entity->getReflectionType(partID) == ReflectionType::PLANAR) && entity->isVisible())
			{
				entity->setVisible(false);
				savedModelEntityIDs.push_back(entity->getID());
				break;
			}
		}
	}

	// Iterate through all billboard entities
	vector<string> savedBillboardEntityIDs;
	for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		// Hide non-reflected billboard entity
		if (!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedBillboardEntityIDs.push_back(entity->getID());
		}
	}

	// Move down
	const fvec3 initialCameraPosition = _camera.getPosition();
	_camera.setPosition(fvec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

	// Look up
	const float initialCameraPitch = _camera.getPitch();
	_camera.setPitch(-initialCameraPitch);

	// Update camera
	_camera.updateMatrices();

	// Use initial camera properties for correct specular lighting
	_renderBus.setCameraPosition(initialCameraPosition);
	_renderBus.setCameraPitch(initialCameraPitch);

	// Disable reflections
	_renderBus.setReflectionsEnabled(false);

	// Sky exposure must not appear in reflections
	float oldSkyLightness = 0.0f;
	auto skyEntity = _entityBus->getMainSkyEntity();
	if (skyEntity != nullptr)
	{
		oldSkyLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getInitialLightness());
	}

	// Calculate clipping plane
	const float clippingHeight = -(_renderBus.getPlanarReflectionHeight() + 0.0000001f);
	const fvec4 clippingPlane = fvec4(0.0f, 1.0f, 0.0f, clippingHeight);
	_renderBus.setClippingPlane(clippingPlane);

	// Render sky entity
	_renderSkyEntity();

	// Render terrain entity
	glEnable(GL_CLIP_DISTANCE0);
	_renderTerrainEntity();
	glDisable(GL_CLIP_DISTANCE0);

	// Render model entities & billboard entities
	glEnable(GL_CLIP_DISTANCE2);
	_renderModelEntities();
	_renderBillboardEntities();
	glDisable(GL_CLIP_DISTANCE2);

	// Stop capturing reflections
	_planarReflectionCaptureBuffer.unbind();

	// Assign texture
	_renderBus.setPlanarReflectionMap(_planarReflectionCaptureBuffer.getTexture(0));

	// Iterate through all model entities
	for (const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Iterate through all saved model entities
		for (const auto& savedID : savedModelEntityIDs)
		{
			// Check if IDs match
			if (entity->getID() == savedID)
			{
				// Show model entity again
				entity->setVisible(true);
			}
		}
	}

	// Iterate through all billboard entities
	for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		// Iterate through all saved billboard entities
		for (const auto& savedID : savedBillboardEntityIDs)
		{
			// Check if IDs match
			if (entity->getID() == savedID)
			{
				// Show billboard entity again
				entity->setVisible(true);
			}
		}
	}

	// Look down
	_camera.setPitch(initialCameraPitch);

	// Move up
	_camera.setPosition(initialCameraPosition);

	// Update camera
	_camera.updateMatrices();

	// Revert reflections
	_renderBus.setReflectionsEnabled(true);

	// Revert sky lightness
	if (skyEntity != nullptr)
	{
		skyEntity->setLightness(oldSkyLightness);
	}
}
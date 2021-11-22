#include "master_renderer.hpp"

void MasterRenderer::_captureCubeReflections()
{
	// Check if no cube reflections needed
	if(_entityBus->getReflectionEntities().empty())
	{
		return;
	}

	// Temporary values
	const auto reflectionQuality = _renderBus.getCubeReflectionQuality();

	// Save initial camera status
	const auto initialCameraAspectRatio = _camera.getAspectRatio();
	const auto initialCameraFOV = _camera.getFOV();
	const auto initialCameraYaw = _camera.getYaw();
	const auto initialCameraPitch = _camera.getPitch();
	const auto initialCameraPosition = _camera.getPosition();

	// Iterate through all model entities
	vector<string> savedModelEntityIDs;
	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Hide non-reflected model entity
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
		}
	}

	// Iterate through all billboard entities
	vector<string> savedBillboardEntityIDs;
	for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		// Hide non-reflected billboard entity
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedBillboardEntityIDs.push_back(entity->getID());
		}
	}

	// Disable reflections
	_renderBus.setReflectionsEnabled(false);

	// Sky exposure must not appear in reflections
	float oldLightness = 0.0f;
	auto skyEntity = _entityBus->getMainSkyEntity();
	if(skyEntity != nullptr)
	{
		oldLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getInitialLightness());
	}

	// Prepare camera
	_camera.invertUpVector();
	_camera.setAspectRatio(1.0f);
	_camera.setFOV(90.0f);

	// Iterate through all reflection entities
	for(const auto& [keyID, entity] : _entityBus->getReflectionEntities())
	{
		// Check if reflection must capture
		if(entity->mustCapture())
		{
			// Capture environment around entity
			for(unsigned int i = 0; i < 6; i++)
			{
				// Set camera position
				_camera.setPosition(entity->getPosition());

				// Set camera view
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

				// Update camera
				_camera.updateMatrices();

				// Update shadows
				_shadowGenerator.generate();
				_captureShadows();

				// Start capturing reflections
				_cubeReflectionCaptureBuffer.bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Render entities
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderModelEntities();

				// Stop capturing reflections
				_cubeReflectionCaptureBuffer.unbind();

				// Retrieve capture buffer texture data
				glBindTexture(GL_TEXTURE_2D, _cubeReflectionCaptureBuffer.getTexture(0));
				int dataSize = (static_cast<int>(reflectionQuality) * static_cast<int>(reflectionQuality) * 3);
				unsigned char* data = new unsigned char[dataSize];
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				// Update cube map
				glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getCubeMap());
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, reflectionQuality, reflectionQuality, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			// Miscellaneous
			entity->setCaptured();
		}
	}

	// Iterate through all model entities
	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Iterate through all saved model entities
		for(const auto& savedID : savedModelEntityIDs)
		{
			// Check if IDs match
			if(entity->getID() == savedID)
			{
				// Show model entity again
				entity->setVisible(true);
			}
		}
	}

	// Iterate through all saved billboard entities
	for(const auto& savedID : savedBillboardEntityIDs)
	{
		// Iterate through all billboard entities
		for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			// Check if IDs match
			if(entity->getID() == savedID)
			{
				// Show billboard entity again
				entity->setVisible(true);
			}
		}
	}

	// Revert reflections
	_renderBus.setReflectionsEnabled(true);

	// Revert sky lightness
	if(skyEntity != nullptr)
	{
		skyEntity->setLightness(oldLightness);
	}

	// Revert camera
	_camera.invertUpVector();
	_camera.setAspectRatio(initialCameraAspectRatio);
	_camera.setFOV(initialCameraFOV);
	_camera.setYaw(initialCameraYaw);
	_camera.setPitch(initialCameraPitch);
	_camera.setPosition(initialCameraPosition);
	_camera.updateMatrices();

	// Revert shadows
	_shadowGenerator.generate();
}

void MasterRenderer::_capturePlanarReflections()
{
	// Search for any reflective model entity
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

	// Check if no planar reflections needed
	if(!anyReflectiveModelFound)
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
	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Hide non-reflected model entity
		if(!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
			continue;
		}

		// Hide reflective model entity
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

	// Iterate through all billboard entities
	vector<string> savedBillboardEntityIDs;
	for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		// Hide non-reflected billboard entity
		if(!entity->isReflected() && entity->isVisible())
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
	if(skyEntity != nullptr)
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
	for(const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Iterate through all saved model entities
		for(const auto& savedID : savedModelEntityIDs)
		{
			// Check if IDs match
			if(entity->getID() == savedID)
			{
				// Show model entity again
				entity->setVisible(true);
			}
		}
	}

	// Iterate through all billboard entities
	for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		// Iterate through all saved billboard entities
		for(const auto& savedID : savedBillboardEntityIDs)
		{
			// Check if IDs match
			if(entity->getID() == savedID)
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
	if(skyEntity != nullptr)
	{
		skyEntity->setLightness(oldSkyLightness);
	}
}
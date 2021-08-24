#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureEnvironmentReflections()
{
	// Temporary values
	auto reflectionQuality = _renderBus.getReflectionQuality();

	// Save original camera status
	const auto originalCameraAspectRatio = _camera.getAspectRatio();
	const auto originalCameraFOV = _camera.getFOV();
	const auto originalCameraUpVector = _camera.getUpVector();
	const auto originalCameraYaw = _camera.getYaw();
	const auto originalCameraPitch = _camera.getPitch();
	const auto originalCameraPosition = _camera.getPosition();
	
	// Iterate through all MODEL entities
	vector<string> savedModelEntityIDs;
	for (const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Hide non-reflected MODEL entity
		if (!entity->isReflected() && entity->isVisible())
		{
			entity->setVisible(false);
			savedModelEntityIDs.push_back(entity->getID());
		}
	}

	// Iterate through all BILLBOARD entities
	vector<string> savedBillboardEntityIDs;
	for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
	{
		// Hide non-reflected BILLBOARD entity
		if (!entity->isReflected() && entity->isVisible())
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
	if (skyEntity != nullptr)
	{
		oldLightness = skyEntity->getLightness();
		skyEntity->setLightness(skyEntity->getOriginalLightness());
	}

	// Prepare camera
	_camera.setAspectRatio(1.0f);
	_camera.setFOV(90.0f);
	_camera.setUpVector(Vec3(0.0f, -1.0f, 0.0f));

	// Iterate through all REFLECTION entities
	for (const auto& [keyID, entity] : _entityBus->getReflectionEntities())
	{
		// Check if reflection must capture
		if (entity->mustCapture())
		{
			// Capture environment surrounding entity
			for (unsigned int i = 0; i < 6; i++)
			{
				// Set camera position
				_camera.setPosition(entity->getPosition());

				// Set camera view
				switch (i)
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
					_camera.setPitch(-90.0f);
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
					_camera.setYaw(-90.0f);
					_camera.setPitch(0.0f);
					break;
				}
				}

				// Update camera
				_camera.updateMatrices();

				// Update shadows
				_shadowGenerator.updateMatrix(_renderBus);
				_captureShadows();

				// Start capturing reflections
				entity->getCaptureBuffer(i).bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Render entities
				_renderSkyEntity();
				_renderTerrainEntity();
				_renderModelEntities();

				// Stop capturing reflections
				entity->getCaptureBuffer(i).unbind();

				// Retrieve capture buffer texture data
				glBindTexture(GL_TEXTURE_2D, entity->getCaptureBuffer(i).getTexture(0));
				int dataSize = (static_cast<int>(reflectionQuality) * static_cast<int>(reflectionQuality) * 3);
				unsigned char* data = new unsigned char[dataSize];
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				// Update environment map
				glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getEnvironmentMap());
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, reflectionQuality, reflectionQuality, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}
			
			_renderBus.setMainSkyReflectionCubeMap(entity->getEnvironmentMap());
		}
	}

	// Iterate through all MODEL entities
	for (const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		// Iterate through all saved MODEL entities
		for (const auto& savedID : savedModelEntityIDs)
		{
			// Check if IDs match
			if (entity->getID() == savedID)
			{
				// Show MODEL entity again
				entity->setVisible(true);
			}
		}
	}

	// Iterate through all saved BILLBOARD entities
	for (const auto& savedID : savedBillboardEntityIDs)
	{
		// Iterate through all BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			// Check if IDs match
			if (entity->getID() == savedID)
			{
				// Show BILLBOARD entity again
				entity->setVisible(true);
			}
		}
	}

	// Revert reflections
	_renderBus.setReflectionsEnabled(true);

	// Revert sky lightness
	if (skyEntity != nullptr)
	{
		skyEntity->setLightness(oldLightness);
	}

	// Revert camera
	_camera.setAspectRatio(originalCameraAspectRatio);
	_camera.setFOV(originalCameraFOV);
	_camera.setUpVector(originalCameraUpVector);
	_camera.setYaw(originalCameraYaw);
	_camera.setPitch(originalCameraPitch);
	_camera.setPosition(originalCameraPosition);
	_camera.updateMatrices();

	// Revert shadows
	_shadowGenerator.updateMatrix(_renderBus);
}

void MasterRenderer::_captureSceneReflections()
{
	// Search for any reflective model entity
	bool anyReflectiveModelFound = false;
	for (const auto& [keyID, entity] : _entityBus->getModelEntities())
	{
		if (entity->hasReflectionMap() && (entity->getReflectionType() == ReflectionType::SCENE) && entity->isVisible())
		{
			anyReflectiveModelFound = true;
			break;
		}
	}

	// Check if needed to capture scene
	if (anyReflectiveModelFound)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (_camera.getPosition().y - _renderBus.getSceneReflectionHeight());

		// Start capturing reflections
		_sceneReflectionCaptureBuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Iterate through all MODEL entities
		vector<string> savedModelEntityIDs;
		for (const auto& [keyID, entity] : _entityBus->getModelEntities())
		{
			// Hide reflective MODEL entity
			if (entity->hasReflectionMap() && (entity->getReflectionType() == ReflectionType::SCENE) && entity->isVisible())
			{
				entity->setVisible(false);
				savedModelEntityIDs.push_back(entity->getID());
			}

			// Hide non-reflected MODEL entity
			if (!entity->isReflected() && entity->isVisible())
			{
				entity->setVisible(false);
				savedModelEntityIDs.push_back(entity->getID());
			}
		}

		// Iterate through all BILLBOARD entities
		vector<string> savedBillboardEntityIDs;
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			// Hide non-reflected BILLBOARD entity
			if (!entity->isReflected() && entity->isVisible())
			{
				entity->setVisible(false);
				savedBillboardEntityIDs.push_back(entity->getID());
			}
		}

		// Move down
		const Vec3 originalCameraPosition = _camera.getPosition();
		_camera.setPosition(Vec3(originalCameraPosition.x, originalCameraPosition.y - (cameraDistance * 2.0f), originalCameraPosition.z));

		// Look up
		const float originalCameraPitch = _camera.getPitch();
		_camera.setPitch(-originalCameraPitch);

		// Update camera
		_camera.updateMatrices();

		// Use original camera properties for correct specular lighting
		_renderBus.setCameraPosition(originalCameraPosition);
		_renderBus.setCameraPitch(originalCameraPitch);

		// Disable reflections
		_renderBus.setReflectionsEnabled(false);

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Sky exposure must not appear in reflections
		float oldSkyLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldSkyLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

		// Calculate clipping plane
		const float clippingHeight = -(_renderBus.getSceneReflectionHeight() + 0.0000001f);
		const Vec4 clippingPlane = Vec4(0.0f, 1.0f, 0.0f, clippingHeight);
		_renderBus.setClippingPlane(clippingPlane);

		// Render SKY entity
		_renderSkyEntity();

		// Render TERRAIN entity
		glEnable(GL_CLIP_DISTANCE0);
		_renderTerrainEntity();
		glDisable(GL_CLIP_DISTANCE0);

		// Render MODEL entities & BILLBOARD entities
		glEnable(GL_CLIP_DISTANCE2);
		_renderModelEntities();
		_renderBillboardEntities();
		glDisable(GL_CLIP_DISTANCE2);

		// Stop capturing reflections
		_sceneReflectionCaptureBuffer.unbind();

		// Assign texture
		_renderBus.setSceneReflectionMap(_sceneReflectionCaptureBuffer.getTexture(0));

		// Iterate through all MODEL entities
		for (const auto& [keyID, entity] : _entityBus->getModelEntities())
		{
			// Iterate through all saved MODEL entities
			for (const auto& savedID : savedModelEntityIDs)
			{
				// Check if IDs match
				if (entity->getID() == savedID)
				{
					// Show MODEL entity again
					entity->setVisible(true);
				}
			}
		}

		// Iterate through all BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			// Iterate through all saved BILLBOARD entities
			for (const auto& savedID : savedBillboardEntityIDs)
			{
				// Check if IDs match
				if (entity->getID() == savedID)
				{
					// Show BILLBOARD entity again
					entity->setVisible(true);
				}
			}
		}

		// Look down
		_camera.setPitch(originalCameraPitch);

		// Move up
		_camera.setPosition(originalCameraPosition);

		// Update camera
		_camera.updateMatrices();

		// Revert reflections
		_renderBus.setReflectionsEnabled(true);

		// Revert shadows
		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		// Revert sky lightness
		if (skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}
	}
	else
	{
		_renderBus.setSceneReflectionMap(0);
	}
}

void MasterRenderer::_captureWaterReflections()
{
	// Temporary values
	const auto waterEntity = _entityBus->getWaterEntity();

	// Check if water reflections needed
	if ((waterEntity != nullptr) && waterEntity->isReflective())
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (_camera.getPosition().y - waterEntity->getPosition().y);

		// Start capturing reflections
		_waterReflectionCaptureBuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Save MODEL entities that must not be captured
		vector<string> savedModelEntityIDs;
		if (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS || 
			waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			// Iterate through all MODEL entities
			for (const auto& [keyID, entity] : _entityBus->getModelEntities())
			{
				// Hide reflective MODEL entity
				if (entity->hasReflectionMap() && (entity->getReflectionType() == ReflectionType::SCENE) && entity->isVisible())
				{
					entity->setVisible(false);
					savedModelEntityIDs.push_back(entity->getID());
				}

				// Hide non-reflected MODEL entity
				if (!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedModelEntityIDs.push_back(entity->getID());
				}
			}
		}

		// Save BILLBOARD entities that must not be captured
		vector<string> savedBillboardEntityIDs;
		if (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			// Iterate through all BILLBOARD entities
			for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				// Hide non-reflected BILLBOARD entity
				if (!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedBillboardEntityIDs.push_back(entity->getID());
				}
			}
		}

		// Move down
		const Vec3 originalCameraPosition = _camera.getPosition();
		_camera.setPosition(Vec3(originalCameraPosition.x, originalCameraPosition.y - (cameraDistance * 2.0f), originalCameraPosition.z));

		// Look up
		const float originalCameraPitch = _camera.getPitch();
		_camera.setPitch(-originalCameraPitch);

		// Update camera
		_camera.updateMatrices();

		// Use original camera properties for correct specular lighting
		_renderBus.setCameraPosition(originalCameraPosition);
		_renderBus.setCameraPitch(originalCameraPitch);

		// Disable reflections
		_renderBus.setReflectionsEnabled(false);

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Sky exposure must not appear in reflections
		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

		// Calculate clipping plane
		const float clippingHeight = -(waterEntity->getPosition().y);
		const Vec4 clippingPlane = Vec4(0.0f, 1.0f, 0.0f, clippingHeight);
		_renderBus.setClippingPlane(clippingPlane);

		// Render SKY entity
		_renderSkyEntity();

		// Render TERRAIN entity
		if (waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		// Render MODEL entities
		if (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
			waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Render BILLBOARD entities
		if (waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{		
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Stop capturing reflections
		_waterReflectionCaptureBuffer.unbind();

		// Assign texture
		_renderBus.setWaterReflectionMap(_waterReflectionCaptureBuffer.getTexture(0));

		// Iterate through all saved MODEL entities
		for (const auto& savedID : savedModelEntityIDs)
		{
			// Iterate through all MODEL entities
			for (const auto& [keyID, entity] : _entityBus->getModelEntities())
			{
				// Check if IDs match
				if (entity->getID() == savedID)
				{
					// Show MODEL entity again
					entity->setVisible(true);
				}
			}
		}

		// Iterate through all saved BILLBOARD entities
		for (const auto& savedID : savedBillboardEntityIDs)
		{
			// Iterate through all BILLBOARD entities
			for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				// Check if IDs match
				if (entity->getID() == savedID)
				{
					// Show BILLBOARD entity again
					entity->setVisible(true);
				}
			}
		}

		// Look down
		_camera.setPitch(originalCameraPitch);

		// Move up
		_camera.setPosition(originalCameraPosition);

		// Update camera
		_camera.updateMatrices();

		// Revert reflections
		_renderBus.setReflectionsEnabled(true);

		// Revert shadows
		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		// Revert sky lightness
		if (skyEntity != nullptr)
		{ 
			skyEntity->setLightness(oldLightness);
		}
	}
	else
	{
		_renderBus.setWaterReflectionMap(0);
	}
}
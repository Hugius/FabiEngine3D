#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureEnvironmentReflections()
{
	for (const auto& [keyID, entity] : _entityBus->getReflectionEntities())
	{
		const float originalCameraYaw = _camera.getYaw();
		const float originalCameraPitch = _camera.getPitch();
		const float originalCameraFOV = _camera.getFOV();

		_camera.setFOV(90.0f);

		for (unsigned int i = 0; i < 6; i++)
		{
			// Start capturing reflections
			entity->getCaptureBuffer(i).bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Set camera view
			if (i == 0)
			{
				_camera.setYaw(-90.0f);
			}
			else if (i == 1)
			{
				_camera.setYaw(90.0f);
			}
			else if (i == 2)
			{
				_camera.setPitch(90.0f);
			}
			else if (i == 3)
			{
				_camera.setPitch(90.0f);
			}
			else if (i == 4)
			{
				_camera.setYaw(180.0f);
			}
			else if (i == 5)
			{
				_camera.setYaw(0.0f);
			}

			// Render entities
			_renderSkyEntity();
			_renderTerrainEntity();
			_renderModelEntities();

			// Stop capturing reflections
			entity->getCaptureBuffer(i).unbind();
		}

		TextureID texture = entity->getEnvironmentMap();
		if (texture != 0)
		{
			glDeleteTextures(1, &texture);
		}
		texture = 0;
		glGenTextures(1, &texture);
		for (unsigned int i = 0; i < 6; i++)
		{
			glBindTexture(GL_TEXTURE_2D, entity->getCaptureBuffer(i).getTexture(0));
			void* data = nullptr;
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		entity->setEnvironmentMap(texture);
	}
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

		// Revert shadows
		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		// Revert sky lightness
		if (skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}

		// Look down
		_camera.setPitch(originalCameraPitch);

		// Move up
		_camera.setPosition(originalCameraPosition);

		// Update camera
		_camera.updateMatrices();

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

		// Stop capturing reflections
		_sceneReflectionCaptureBuffer.unbind();

		// Assign texture
		_renderBus.setSceneReflectionMap(_sceneReflectionCaptureBuffer.getTexture(0));
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

		// Revert shadows
		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		// Revert sky lightness
		if (skyEntity != nullptr)
		{ 
			skyEntity->setLightness(oldLightness);
		}

		// Look down
		_camera.setPitch(originalCameraPitch);

		// Move up
		_camera.setPosition(originalCameraPosition);

		// Update camera
		_camera.updateMatrices();

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

		// Stop capturing reflections
		_waterReflectionCaptureBuffer.unbind();

		// Assign texture
		_renderBus.setWaterReflectionMap(_waterReflectionCaptureBuffer.getTexture(0));
	}
	else
	{
		_renderBus.setWaterReflectionMap(0);
	}
}
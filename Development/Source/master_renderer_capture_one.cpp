#include "master_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

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
	if (_renderBus.isSceneReflectionsEnabled() && anyReflectiveModelFound)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (_camera.getPosition().y - _renderBus.getSceneReflectionHeight());

		// Start capturing reflections
		_sceneReflectionFramebuffer.bind();
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

		// Normal mapping is performance-heavy with little visual impact on reflections, so they should not appear
		bool wasNormalMappingEnabled = _renderBus.isNormalMappingEnabled();
		_renderBus.setNormalMappingEnabled(false);

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

		// Revert disabled graphics
		_renderBus.setShadowsEnabled(wasShadowsEnabled);
		_renderBus.setNormalMappingEnabled(wasNormalMappingEnabled);
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
		_sceneReflectionFramebuffer.unbind();

		// Assign texture
		_renderBus.setSceneReflectionMap(_sceneReflectionFramebuffer.getTexture(0));
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
		float cameraDistance = (_camera.getPosition().y - waterEntity->getTranslation().y);

		// Start capturing reflections
		_waterReflectionFramebuffer.bind();
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

		// Normal mapping is performance-heavy with little visual impact on reflections, so they should not appear
		bool wasNormalMappingEnabled = _renderBus.isNormalMappingEnabled();
		_renderBus.setNormalMappingEnabled(false);

		// Sky exposure must not appear in reflections
		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

		// Calculate clipping plane
		const float clippingHeight = -(waterEntity->getTranslation().y);
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
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{		
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Revert disabled graphics
		_renderBus.setShadowsEnabled(wasShadowsEnabled);
		_renderBus.setNormalMappingEnabled(wasNormalMappingEnabled);
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
		_waterReflectionFramebuffer.unbind();

		// Assign texture
		_renderBus.setWaterReflectionMap(_waterReflectionFramebuffer.getTexture(0));
	}
	else
	{
		_renderBus.setWaterReflectionMap(0);
	}
}

void MasterRenderer::_captureWaterRefractions()
{
	// Temporary values
	const auto waterEntity = _entityBus->getWaterEntity();

	// Check if water refractions needed
	if ((waterEntity != nullptr) && waterEntity->isRefractive())
	{
		// Start capturing refractions
		_waterRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Shadows are not needed when no models are rendered, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		if (waterEntity->getQuality() == WaterQuality::SKY || waterEntity->getQuality() == WaterQuality::SKY_TERRAIN)
		{
			_renderBus.setShadowsEnabled(false);
		}

		// Normal mapping is performance-heavy with little visual impact on refractions, so they should not appear
		bool wasNormalMappingEnabled = _renderBus.isNormalMappingEnabled();
		_renderBus.setNormalMappingEnabled(false);

		// Sky exposure must not appear in refractions
		float oldSkyLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldSkyLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

		// Check if camera underwater
		const float waveHeight = (waterEntity->isWaving() ? waterEntity->getWaveHeight() : 0.0f);
		bool isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getTranslation().y + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > waterEntity->getTranslation().x - (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < waterEntity->getTranslation().x + (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > waterEntity->getTranslation().z - (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < waterEntity->getTranslation().z + (waterEntity->getSize() / 2.0f)));

		// Calculate clipping plane
		if (isUnderWater)
		{
			const float clippingHeight = -(waterEntity->getTranslation().y);
			const Vec4 clippingPlane = Vec4(0.0f, 1.0f, 0.0f, clippingHeight);
			_renderBus.setClippingPlane(clippingPlane);
		}
		else
		{
			const float clippingHeight = (waterEntity->getTranslation().y + waveHeight);
			const Vec4 clippingPlane = Vec4(0.0f, -1.0f, 0.0f, clippingHeight);
			_renderBus.setClippingPlane(clippingPlane);
		}

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

		// Revert disabled graphics
		_renderBus.setShadowsEnabled(wasShadowsEnabled);
		_renderBus.setNormalMappingEnabled(wasNormalMappingEnabled);
		if (skyEntity != nullptr)
		{
			skyEntity->setLightness(oldSkyLightness);
		}

		// Stop capturing refractions
		_waterRefractionFramebuffer.unbind();

		// Assign texture
		_renderBus.setWaterRefractionMap(_waterRefractionFramebuffer.getTexture(0));
	}
	else
	{
		_renderBus.setWaterRefractionMap(0);
	}
}
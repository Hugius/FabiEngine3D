#include "master_renderer.hpp"

void MasterRenderer::_captureWaterReflections()
{
	// Temporary values
	const auto waterEntity = _entityBus->getWaterEntity();

	// Check if water reflections needed
	if((waterEntity != nullptr) && waterEntity->isReflective())
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (_camera.getPosition().y - waterEntity->getHeight());

		// Start capturing reflections
		_waterReflectionCaptureBuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Save model entities that must not be captured
		vector<string> savedModelEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			// Iterate through all model entities
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
		}

		// Save billboard entities that must not be captured
		vector<string> savedBillboardEntityIDs;
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			// Iterate through all billboard entities
			for(const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				// Hide non-reflected billboard entity
				if(!entity->isReflected() && entity->isVisible())
				{
					entity->setVisible(false);
					savedBillboardEntityIDs.push_back(entity->getID());
				}
			}
		}

		// Move down
		const Vec3 initialCameraPosition = _camera.getPosition();
		_camera.setPosition(Vec3(initialCameraPosition.x, initialCameraPosition.y - (cameraDistance * 2.0f), initialCameraPosition.z));

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

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Sky exposure must not appear in reflections
		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if(skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getInitialLightness());
		}

		// Calculate clipping plane
		const float clippingHeight = -(waterEntity->getHeight());
		const Vec4 clippingPlane = Vec4(0.0f, 1.0f, 0.0f, clippingHeight);
		_renderBus.setClippingPlane(clippingPlane);

		// Render sky entity
		_renderSkyEntity();

		// Render terrain entity
		if(waterEntity->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		// Render model entities
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
		   waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Render billboard entities
		if(waterEntity->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderBillboardEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Stop capturing reflections
		_waterReflectionCaptureBuffer.unbind();

		// Assign texture
		_renderBus.setWaterReflectionMap(_waterReflectionCaptureBuffer.getTexture(0));

		// Iterate through all saved model entities
		for(const auto& savedID : savedModelEntityIDs)
		{
			// Iterate through all model entities
			for(const auto& [keyID, entity] : _entityBus->getModelEntities())
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

		// Look down
		_camera.setPitch(initialCameraPitch);

		// Move up
		_camera.setPosition(initialCameraPosition);

		// Update camera
		_camera.updateMatrices();

		// Revert reflections
		_renderBus.setReflectionsEnabled(true);

		// Revert shadows
		_renderBus.setShadowsEnabled(wasShadowsEnabled);

		// Revert sky lightness
		if(skyEntity != nullptr)
		{
			skyEntity->setLightness(oldLightness);
		}
	}
	else
	{
		_renderBus.setWaterReflectionMap(0);
	}
}
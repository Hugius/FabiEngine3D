#include "master_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void MasterRenderer::_captureSceneReflections(Camera& camera)
{
	// Search for any reflective model entity
	bool anyReflectiveModelFound = false;
	for (const auto& [keyID, modelEntity] : _entityBus->getModelEntities())
	{
		if (modelEntity->isSceneReflective() && modelEntity->isVisible())
		{
			anyReflectiveModelFound = true;
			break;
		}
	}

	// Check if needed to capture scene
	if (_renderBus.isSceneReflectionsEnabled() && anyReflectiveModelFound)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (camera.getPosition().y - _renderBus.getSceneReflectionHeight());

		// Start capturing reflections
		_sceneReflectionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Iterate through all MODEL entities
		vector<string> savedModelEntityIDs;
		for (const auto& [keyID, entity] : _entityBus->getModelEntities())
		{
			// Check if necessary to hide
			if ((entity->isSceneReflective() || !entity->isReflected()) && entity->isVisible())
			{
				// Hide MODEL entity
				entity->setVisible(false);
				savedModelEntityIDs.push_back(entity->getID());
			}
		}

		// Iterate through all BILLBOARD entities
		vector<string> savedBillboardEntityIDs;
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			// Check if necessary to hide
			if (!entity->isReflected() && entity->isVisible())
			{
				// Hide BILLBOARD entity
				entity->setVisible(false);
				savedBillboardEntityIDs.push_back(entity->getID());
			}
		}

		// Change camera angle
		Vec3 cameraPos = camera.getPosition();
		Vec3 newCameraPos = Vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.setPitch(-camera.getPitch());
		camera.updateMatrices();

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Normal mapping is performance-heavy with little visual impact on reflections, so they should not appear
		bool wasNormalMappingEnabled = _renderBus.isNormalMappingEnabled();
		_renderBus.setNormalMappingEnabled(false);

		// Sky HDR must not appear in reflections
		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

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
			skyEntity->setLightness(oldLightness);
		}

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = Vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.setPitch(-camera.getPitch());
		camera.updateMatrices();

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
		_renderBus.setWaterReflectionMap(_sceneReflectionFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureWaterReflections(Camera& camera)
{
	// Check if water reflections needed
	if ((_entityBus->getWaterEntity() != nullptr) && _entityBus->getWaterEntity()->isReflective())
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (camera.getPosition().y - _entityBus->getWaterEntity()->getTranslation().y);

		// Start capturing reflections
		_waterReflectionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Save MODEL entities that must not be captured
		vector<string> savedModelEntityIDs;
		if (_entityBus->getWaterEntity()->getQuality() == WaterQuality::SKY_TERRAIN_MODELS || 
			_entityBus->getWaterEntity()->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			// Iterate through all MODEL entities
			for (const auto& [keyID, entity] : _entityBus->getModelEntities())
			{
				// Check if necessary to hide
				if ((entity->isSceneReflective() || !entity->isReflected()) && entity->isVisible())
				{
					// Hide MODEL entity
					entity->setVisible(false);
					savedModelEntityIDs.push_back(entity->getID());
				}
			}
		}

		// Save BILLBOARD entities that must not be captured
		vector<string> savedBillboardEntityIDs;
		if (_entityBus->getWaterEntity()->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			// Iterate through all BILLBOARD entities
			for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
			{
				// Check if necessary to hide
				if (!entity->isReflected() && entity->isVisible())
				{
					// Hide BILLBOARD entity
					entity->setVisible(false);
					savedBillboardEntityIDs.push_back(entity->getID());
				}
			}
		}

		// Change camera angle
		Vec3 cameraPos = camera.getPosition();
		Vec3 newCameraPos = Vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.setPitch(-camera.getPitch());
		camera.updateMatrices();

		// Shadows are performance-heavy with little visual impact on reflections, so they should not appear
		bool wasShadowsEnabled = _renderBus.isShadowsEnabled();
		_renderBus.setShadowsEnabled(false);

		// Normal mapping is performance-heavy with little visual impact on reflections, so they should not appear
		bool wasNormalMappingEnabled = _renderBus.isNormalMappingEnabled();
		_renderBus.setNormalMappingEnabled(false);

		// Sky HDR must not appear in reflections
		float oldLightness = 0.0f;
		auto skyEntity = _entityBus->getMainSkyEntity();
		if (skyEntity != nullptr)
		{
			oldLightness = skyEntity->getLightness();
			skyEntity->setLightness(skyEntity->getOriginalLightness());
		}

		// Render SKY entity
		_renderSkyEntity();

		// Render TERRAIN entity
		if (_entityBus->getWaterEntity()->getQuality() != WaterQuality::SKY)
		{
			glEnable(GL_CLIP_DISTANCE0);
			_renderTerrainEntity();
			glDisable(GL_CLIP_DISTANCE0);
		}

		// Render MODEL entities
		if (_entityBus->getWaterEntity()->getQuality() == WaterQuality::SKY_TERRAIN_MODELS ||
			_entityBus->getWaterEntity()->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
		{
			glEnable(GL_CLIP_DISTANCE2);
			_renderModelEntities();
			glDisable(GL_CLIP_DISTANCE2);
		}

		// Render BILLBOARD entities
		if(_entityBus->getWaterEntity()->getQuality() == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
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

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = Vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.setPitch(-camera.getPitch());
		camera.updateMatrices();

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
}

void MasterRenderer::_captureWaterRefractions()
{
	// Check if water refractions needed
	if (_entityBus->getWaterEntity() != nullptr && _entityBus->getWaterEntity()->isRefractive())
	{
		// Bind
		_waterRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render whole scene
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderModelEntities();
		_renderBillboardEntities();

		// Unbind
		_waterRefractionFramebuffer.unbind();

		// Assign texture
		_renderBus.setWaterRefractionMap(_waterRefractionFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureShadows()
{
	if (_renderBus.isShadowsEnabled())
	{
		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_shadowRenderer.bind();

		// Render MODEL entities
		auto allModelEntities = _entityBus->getModelEntities();
		for (const auto& [keyID, modelEntity] : allModelEntities)
		{
			// Check if LOD entity needs to be rendered
			if (modelEntity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				auto foundPair = allModelEntities.find(modelEntity->getLodEntityID());
				if (foundPair != allModelEntities.end())
				{
					auto lodEntity = foundPair->second;

					// Save original transformation
					Vec3 originalPosition = lodEntity->getTranslation();
					Vec3 originalRotation = lodEntity->getRotation();
					Vec3 originalSize = lodEntity->getScaling();
					bool originalVisibility = lodEntity->isVisible();

					// Change transformation
					lodEntity->setTranslation(modelEntity->getTranslation());
					lodEntity->setRotation(modelEntity->getRotation());
					lodEntity->setScaling((modelEntity->getScaling() / modelEntity->getOriginalScaling()) * originalSize);
					lodEntity->setVisible(modelEntity->isVisible());
					lodEntity->updateModelMatrix();

					// Render LOD entity
					_shadowRenderer.render(lodEntity);

					// Revert to original transformation
					lodEntity->setTranslation(originalPosition);
					lodEntity->setRotation(originalRotation);
					lodEntity->setScaling(originalSize);
					lodEntity->setVisible(originalVisibility);
					lodEntity->updateModelMatrix();
				}
				else
				{
					Logger::throwError("Model entity with ID \"" + modelEntity->getID() + "\" has a non-existing LOD entity with ID \"" + modelEntity->getLodEntityID() + "\"");
				}
			}
			else // Render high-quality entity
			{
				_shadowRenderer.render(modelEntity);
			}
		}

		// Render BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			_shadowRenderer.render(entity);
		}

		// Unbind
		_shadowRenderer.unbind();
		_shadowFramebuffer.unbind();
		_renderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
}

void MasterRenderer::_captureBloom()
{
	if (_renderBus.isBloomEnabled())
	{
		// Process scene texture
		_bloomHdrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		_bloomHdrRenderer.bind();
		_bloomHdrRenderer.render(_finalSurface, _renderBus.getSceneMap());
		_bloomHdrRenderer.unbind();
		_bloomHdrFramebuffer.unbind();

		// Blur scene texture
		_blurRenderer.bind();
		_renderBus.setBloomMap(_blurRenderer.blurTexture(_finalSurface, _bloomHdrFramebuffer.getTexture(0),
			static_cast<int>(BlurType::BLOOM), _renderBus.getBloomBlurSize(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_blurRenderer.unbind();
	}
}
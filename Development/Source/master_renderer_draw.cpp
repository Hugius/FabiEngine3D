#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;

void MasterRenderer::_renderSkyEntity()
{
	if (_entityBus->getMainSkyEntity() != nullptr)
	{
		// Bind
		_skyEntityRenderer.bind();

		// Render SKY entity
		_skyEntityRenderer.render(_entityBus->getMainSkyEntity(), _entityBus->getMixSkyEntity());

		// Unbind
		_skyEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if (_entityBus->getTerrainEntity() != nullptr)
	{
		// Bind
		_terrainEntityRenderer.bind();

		// Render LIGHT entities
		_terrainEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render TERRAIN entity
		_terrainEntityRenderer.render(_entityBus->getTerrainEntity());

		// Unbind
		_terrainEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if (_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		_waterEntityRenderer.bind();

		// Render LIGHT entities
		_waterEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render WATER entity
		_waterEntityRenderer.render(_entityBus->getWaterEntity());

		// Unbind
		_waterEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderModelEntities()
{
	if (!_entityBus->getModelEntities().empty())
	{
		// Bind
		_modelEntityRenderer.bind();

		// Render lights
		_modelEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

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
					_modelEntityRenderer.render(lodEntity);

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
				_modelEntityRenderer.render(modelEntity);
			}
		}

		// Unbind
		_modelEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderBillboardEntities()
{
	if (!_entityBus->getBillboardEntities().empty())
	{
		// Bind
		_billboardEntityRenderer.bind();

		// Render BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			_billboardEntityRenderer.render(entity);
		}

		// Unbind
		_billboardEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if (_renderBus.isAabbFrameRenderingEnabled())
	{
		if (!_entityBus->getAabbEntities().empty())
		{
			// Bind
			_aabbEntityRenderer.bind();

			// Render AABB entities
			for (const auto& [keyID, entity] : _entityBus->getAabbEntities())
			{
				_aabbEntityRenderer.render(entity);
			}

			// Unbind
			_aabbEntityRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalSceneTexture()
{
	_finalRenderer.bind();
	_finalRenderer.render(_finalSurface, _renderBus.getPostProcessedSceneMap(), _renderBus.getMotionBlurMap());
	_finalRenderer.unbind();
}

void MasterRenderer::_renderGUI()
{
	if (!_entityBus->getImageEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		// Bind
		_imageEntityRenderer.bind();

		// Sort rendering order
		std::map<unsigned int, shared_ptr<ImageEntity>> orderedEntityMap;
		for (const auto& [keyID, entity] : _entityBus->getImageEntities())
		{
			// Custom cursor entity must be rendered last
			if (entity->getID() != _renderBus.getCursorEntityID())
			{
				orderedEntityMap.insert(std::make_pair(entity->getDepth(), entity));
			}
		}
		for (const auto& [keyID, entity] : _entityBus->getTextEntities())
		{
			orderedEntityMap.insert(std::make_pair(entity->getDepth(), entity));
		}

		// Render entities
		for (const auto& [keyID, entity] : orderedEntityMap)
		{
			// Check if entity is a TEXT entity
			auto castedTextEntity = std::dynamic_pointer_cast<TextEntity>(entity);

			if (castedTextEntity == nullptr) // IMAGE entity
			{
				_imageEntityRenderer.render(entity);
			}
			else // TEXT entity
			{
				if (castedTextEntity->isDynamic()) // Dynamic text rendering
				{
					// Render every character individually
					for (const auto& characterEntity : castedTextEntity->getCharacterEntities())
					{
						_imageEntityRenderer.render(characterEntity);
					}
				}
				else // Static text rendering
				{
					_imageEntityRenderer.render(castedTextEntity);
				}
			}
		}

		// Unbind
		_imageEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderCustomCursor()
{
	for (const auto& [keyID, entity] : _entityBus->getImageEntities())
	{
		if (entity->getID() == _renderBus.getCursorEntityID())
		{
			_imageEntityRenderer.bind();
			_imageEntityRenderer.render(entity);
			_imageEntityRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderDebugScreens()
{
	// Temporary values
	const string fontPath = "engine_assets\\fonts\\font.ttf";
	const Vec3 color = Vec3(0.5f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	std::function<float(string)> calcTextWidth = [&](string text) {return static_cast<float>(text.size()) * charWidth; };

	// Normal scene - surface
	shared_ptr<ImageEntity> normalSurface = make_shared<ImageEntity>("normalSurface");
	normalSurface->setTexture(_renderBus.getPrimarySceneMap());
	normalSurface->addRenderBuffer(new RenderBuffer(-0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	normalSurface->setMirroredVertically(true);

	// Normal scene - text
	shared_ptr<TextEntity> normalText = make_shared<TextEntity>("normalText");
	normalText->setTexture(_textureLoader.getText("Default render", fontPath));
	normalText->addRenderBuffer(new RenderBuffer(-0.66666f, 0.4f, calcTextWidth("Default render"), charHeight, true, false));
	normalText->setColor(color);

	// Shadow scene - surface
	shared_ptr<ImageEntity> shadowSurface = make_shared<ImageEntity>("shadowSurface");
	shadowSurface->setTexture(_renderBus.getShadowMap());
	shadowSurface->addRenderBuffer(new RenderBuffer(-0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	shadowSurface->setMirroredVertically(true);

	// Shadow scene - text
	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setTexture(_textureLoader.getText("Shadow render", fontPath));
	shadowText->addRenderBuffer(new RenderBuffer(-0.66666f, -0.26f, calcTextWidth("Shadow render"), charHeight, true, false));
	shadowText->setColor(color);

	// Reflection scene - surface
	shared_ptr<ImageEntity> reflectionSurface = make_shared<ImageEntity>("reflectionSurface");
	reflectionSurface->setTexture(_renderBus.getWaterReflectionMap());
	reflectionSurface->addRenderBuffer(new RenderBuffer(-0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	reflectionSurface->setMirroredVertically(true);

	// Reflection scene - text
	shared_ptr<TextEntity> reflectionText = make_shared<TextEntity>("reflectionText");
	reflectionText->setTexture(_textureLoader.getText("Reflection render", fontPath));
	reflectionText->addRenderBuffer(new RenderBuffer(-0.66666f, -0.92f, calcTextWidth("Reflection render"), charHeight, true, false));
	reflectionText->setColor(color);

	// Refraction scene - surface
	shared_ptr<ImageEntity> refractionSurface = make_shared<ImageEntity>("refractionSurface");
	refractionSurface->setTexture(_renderBus.getWaterRefractionMap());
	refractionSurface->addRenderBuffer(new RenderBuffer(0.0f, 0.66666f, 0.66666f, 0.66666f, true, false));
	refractionSurface->setMirroredVertically(true);

	// Refraction scene - text
	shared_ptr<TextEntity> refractionText = make_shared<TextEntity>("refractionText");
	refractionText->setTexture(_textureLoader.getText("Refraction render", fontPath));
	refractionText->addRenderBuffer(new RenderBuffer(0.0f, 0.4f, calcTextWidth("Refraction render"), charHeight, true, false));
	refractionText->setColor(color);

	// Depth scene - surface
	shared_ptr<ImageEntity> depthSurface = make_shared<ImageEntity>("depthSurface");
	depthSurface->setDepthEntity(true);
	depthSurface->setTexture(_renderBus.getSceneDepthMap());
	depthSurface->addRenderBuffer(new RenderBuffer(0.0f, 0.0f, 0.66666f, 0.66666f, true, false));
	depthSurface->setMirroredVertically(true);

	// Depth scene - text
	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setTexture(_textureLoader.getText("Depth render", fontPath));
	depthText->addRenderBuffer(new RenderBuffer(0.0f, -0.26f, calcTextWidth("Depth render"), charHeight, true, false));
	depthText->setColor(color);

	// Bloom scene - surface
	shared_ptr<ImageEntity> bloomSurface = make_shared<ImageEntity>("bloomSurface");
	bloomSurface->setTexture(_renderBus.getBloomMap());
	bloomSurface->addRenderBuffer(new RenderBuffer(0.0f, -0.66666f, 0.66666f, 0.66666f, true, false));
	bloomSurface->setMirroredVertically(true);

	// Bloom scene - text
	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setTexture(_textureLoader.getText("Bloom render", fontPath));
	bloomText->addRenderBuffer(new RenderBuffer(0.0f, -0.92f, calcTextWidth("Bloom render"), charHeight, true, false));
	bloomText->setColor(color);
	
	// Blur scene - surface
	shared_ptr<ImageEntity> blurSurface = make_shared<ImageEntity>("blurSurface");
	blurSurface->setTexture(_renderBus.getBlurMap());
	blurSurface->addRenderBuffer(new RenderBuffer(0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	blurSurface->setMirroredVertically(true);

	// Blur scene - text
	shared_ptr<TextEntity> blurText = make_shared<TextEntity>("blurText");
	blurText->setTexture(_textureLoader.getText("Blur render", fontPath));
	blurText->addRenderBuffer(new RenderBuffer(0.66666f, 0.4f, calcTextWidth("Blur render"), charHeight, true, false));
	blurText->setColor(color);

	// Postprocessed scene - surface
	shared_ptr<ImageEntity> postprocessedSurface = make_shared<ImageEntity>("postprocessedSurface");
	postprocessedSurface->setTexture(_renderBus.getPostProcessedSceneMap());
	postprocessedSurface->addRenderBuffer(new RenderBuffer(0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	postprocessedSurface->setMirroredVertically(true);

	// Postprocessed scene - text
	shared_ptr<TextEntity> postprocessedText = make_shared<TextEntity>("postprocessedText");
	postprocessedText->setTexture(_textureLoader.getText("Postprocessed render", fontPath));
	postprocessedText->addRenderBuffer(new RenderBuffer(0.66666f, -0.26f, calcTextWidth("Postprocessed render"), charHeight, true, false));
	postprocessedText->setColor(color);

	// Motion scene - surface
	shared_ptr<ImageEntity> motionSurface = make_shared<ImageEntity>("motionSurface");
	motionSurface->setTexture(_renderBus.getMotionBlurMap());
	motionSurface->addRenderBuffer(new RenderBuffer(0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	motionSurface->setMirroredVertically(true);

	// Motion scene - text
	shared_ptr<TextEntity> motionText = make_shared<TextEntity>("motionText");
	motionText->setTexture(_textureLoader.getText("Motion render", fontPath));
	motionText->addRenderBuffer(new RenderBuffer(0.66666f, -0.92f, calcTextWidth("Motion render"), charHeight, true, false));
	motionText->setColor(color);
	
	// Render debug screens + text
	_imageEntityRenderer.bind();
	_imageEntityRenderer.render(normalSurface);
	_imageEntityRenderer.render(normalText);
	_imageEntityRenderer.render(shadowSurface);
	_imageEntityRenderer.render(shadowText);
	_imageEntityRenderer.render(reflectionSurface);
	_imageEntityRenderer.render(reflectionText);
	_imageEntityRenderer.render(refractionSurface);
	_imageEntityRenderer.render(refractionText);
	_imageEntityRenderer.render(depthSurface);
	_imageEntityRenderer.render(depthText);
	_imageEntityRenderer.render(bloomSurface);
	_imageEntityRenderer.render(bloomText);
	_imageEntityRenderer.render(blurSurface);
	_imageEntityRenderer.render(blurText);
	_imageEntityRenderer.render(postprocessedSurface);
	_imageEntityRenderer.render(postprocessedText);
	_imageEntityRenderer.render(motionSurface);
	_imageEntityRenderer.render(motionText);
	_imageEntityRenderer.unbind();
}
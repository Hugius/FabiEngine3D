#include "render_manager.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;

void RenderManager::_renderSkyEntity()
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

void RenderManager::_renderTerrainEntity()
{
	if (_entityBus->getTerrainEntity() != nullptr)
	{
		// Bind
		_terrainEntityRenderer.bind();

		// Render lights
		_terrainEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render TERRAIN entity
		_terrainEntityRenderer.render(_entityBus->getTerrainEntity());

		// Unbind
		_terrainEntityRenderer.unbind();
	}
}

void RenderManager::_renderWaterEntity()
{
	if (_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		_waterEntityRenderer.bind();

		// Render lights
		_waterEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render WATER entity
		_waterEntityRenderer.render(_entityBus->getWaterEntity());

		// Unbind
		_waterEntityRenderer.unbind();
	}
}

void RenderManager::_renderModelEntities()
{
	if (!_entityBus->getModelEntities().empty())
	{
		// Bind
		_modelEntityRenderer.bind();

		// Render lights
		_modelEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render GAME entities
		auto allModelEntities = _entityBus->getModelEntities();
		for (auto& [keyID, modelEntity] : allModelEntities)
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
					Logger::throwError("MODEL entity \"" + modelEntity->getID() + "\" has a nonexisting LOD entity \"" + modelEntity->getLodEntityID() + "\"");
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

void RenderManager::_renderBillboardEntities()
{
	if (!_entityBus->getBillboardEntities().empty())
	{
		// Bind
		_billboardEntityRenderer.bind();

		// Render BILLBOARD entities
		for (auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			_billboardEntityRenderer.render(entity);
		}

		// Unbind
		_billboardEntityRenderer.unbind();
	}
}

void RenderManager::_renderAabbEntities()
{
	if (_renderBus.isAabbFrameRenderingEnabled())
	{
		if (!_entityBus->getAabbEntities().empty())
		{
			// Bind
			_aabbEntityRenderer.bind();

			// Render AABB entities
			for (auto& [keyID, entity] : _entityBus->getAabbEntities())
			{
				_aabbEntityRenderer.render(entity);
			}

			// Unbind
			_aabbEntityRenderer.unbind();
		}
	}
}

void RenderManager::_renderFinalSceneTexture()
{
	_finalRenderer.bind();
	_finalRenderer.render(_finalSurface, _renderBus.getPostProcessedSceneMap(), _renderBus.getMotionBlurMap());
	_finalRenderer.unbind();
}

void RenderManager::_renderGuiEntities()
{
	if (!_entityBus->getGuiEntities().empty())
	{
		// Bind
		_guiEntityRenderer.bind();

		// Sort render order
		std::map<unsigned int, shared_ptr<GuiEntity>> orderedMap;
		for (auto& [keyID, entity] : _entityBus->getGuiEntities())
		{
			// Custom cursor entity must be rendered last
			if (entity->getID() != _renderBus.getCursorEntityID())
			{
				orderedMap.insert(std::make_pair(entity->getDepth(), entity));
			}
		}

		// Render all entities
		for (auto& [keyID, entity] : orderedMap)
		{
			_guiEntityRenderer.render(entity);
		}

		// Unbind
		_guiEntityRenderer.unbind();
	}
}

void RenderManager::_renderTextEntities()
{
	if (!_entityBus->getTextEntities().empty())
	{
		// Bind
		_guiEntityRenderer.bind();

		// Sort render order
		std::map<unsigned int, shared_ptr<TextEntity>> orderedMap;
		for (auto& [keyID, entity] : _entityBus->getTextEntities())
		{
			orderedMap.insert(std::make_pair(entity->getDepth(), entity));
		}

		// Render all entities
		for (auto& [keyID, textEntity] : orderedMap)
		{
			if (textEntity->isDynamic()) // Dynamic text rendering
			{
				// Render every character individually
				for (auto& characterEntity : textEntity->getCharacterEntities())
				{
					_guiEntityRenderer.render(characterEntity);
				}
			}
			else // Static text rendering
			{
				_guiEntityRenderer.render(textEntity);
			}
		}

		// Unbind
		_guiEntityRenderer.unbind();
	}
}

void RenderManager::_renderCustomCursor()
{
	for (auto& [keyID, entity] : _entityBus->getGuiEntities())
	{
		if (entity->getID() == _renderBus.getCursorEntityID())
		{
			_guiEntityRenderer.bind();
			_guiEntityRenderer.render(entity);
			_guiEntityRenderer.unbind();
		}
	}
}

void RenderManager::_renderDebugScreens()
{
	// Temporary values
	const string fontPath = "engine_assets\\fonts\\font.ttf";
	const Vec3 color = Vec3(0.5f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	std::function<float(string)> calcTextWidth = [&](string text) {return static_cast<float>(text.size()) * charWidth; };

	// Normal scene - surface
	shared_ptr<GuiEntity> normalSurface = make_shared<GuiEntity>("normalSurface");
	normalSurface->setTexture(_renderBus.getSceneMap());
	normalSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	normalSurface->setMirroredVertically(true);

	// Normal scene - text
	shared_ptr<TextEntity> normalText = make_shared<TextEntity>("normalText");
	normalText->setTexture(_textureLoader.getText("Default render", fontPath));
	normalText->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.4f, calcTextWidth("Default render"), charHeight, true, false));
	normalText->setColor(color);

	// Shadow scene - surface
	shared_ptr<GuiEntity> shadowSurface = make_shared<GuiEntity>("shadowSurface");
	shadowSurface->setTexture(_renderBus.getShadowMap());
	shadowSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	shadowSurface->setMirroredVertically(true);

	// Shadow scene - text
	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setTexture(_textureLoader.getText("Shadow render", fontPath));
	shadowText->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.26f, calcTextWidth("Shadow render"), charHeight, true, false));
	shadowText->setColor(color);

	// Reflection scene - surface
	shared_ptr<GuiEntity> reflectionSurface = make_shared<GuiEntity>("reflectionSurface");
	reflectionSurface->setTexture(_renderBus.getSceneReflectionMap());
	reflectionSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	reflectionSurface->setMirroredVertically(true);

	// Reflection scene - text
	shared_ptr<TextEntity> reflectionText = make_shared<TextEntity>("reflectionText");
	reflectionText->setTexture(_textureLoader.getText("Reflection render", fontPath));
	reflectionText->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.92f, calcTextWidth("Reflection render"), charHeight, true, false));
	reflectionText->setColor(color);

	// Refraction scene - surface
	shared_ptr<GuiEntity> refractionSurface = make_shared<GuiEntity>("refractionSurface");
	refractionSurface->setTexture(_renderBus.getSceneRefractionMap());
	refractionSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.66666f, 0.66666f, 0.66666f, true, false));
	refractionSurface->setMirroredVertically(true);

	// Refraction scene - text
	shared_ptr<TextEntity> refractionText = make_shared<TextEntity>("refractionText");
	refractionText->setTexture(_textureLoader.getText("Refraction render", fontPath));
	refractionText->addOglBuffer(new OpenGLBuffer(0.0f, 0.4f, calcTextWidth("Refraction render"), charHeight, true, false));
	refractionText->setColor(color);

	// Depth scene - surface
	shared_ptr<GuiEntity> depthSurface = make_shared<GuiEntity>("depthSurface");
	depthSurface->setDepthEntity(true);
	depthSurface->setTexture(_renderBus.getSceneDepthMap());
	depthSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 0.66666f, 0.66666f, true, false));
	depthSurface->setMirroredVertically(true);

	// Depth scene - text
	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setTexture(_textureLoader.getText("Depth render", fontPath));
	depthText->addOglBuffer(new OpenGLBuffer(0.0f, -0.26f, calcTextWidth("Depth render"), charHeight, true, false));
	depthText->setColor(color);

	// Bloom scene - surface
	shared_ptr<GuiEntity> bloomSurface = make_shared<GuiEntity>("bloomSurface");
	bloomSurface->setTexture(_renderBus.getBloomMap());
	bloomSurface->addOglBuffer(new OpenGLBuffer(0.0f, -0.66666f, 0.66666f, 0.66666f, true, false));
	bloomSurface->setMirroredVertically(true);

	// Bloom scene - text
	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setTexture(_textureLoader.getText("Bloom render", fontPath));
	bloomText->addOglBuffer(new OpenGLBuffer(0.0f, -0.92f, calcTextWidth("Bloom render"), charHeight, true, false));
	bloomText->setColor(color);
	
	// Blur scene - surface
	shared_ptr<GuiEntity> blurSurface = make_shared<GuiEntity>("blurSurface");
	blurSurface->setTexture(_renderBus.getBlurMap());
	blurSurface->addOglBuffer(new OpenGLBuffer(0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	blurSurface->setMirroredVertically(true);

	// Blur scene - text
	shared_ptr<TextEntity> blurText = make_shared<TextEntity>("blurText");
	blurText->setTexture(_textureLoader.getText("Blur render", fontPath));
	blurText->addOglBuffer(new OpenGLBuffer(0.66666f, 0.4f, calcTextWidth("Blur render"), charHeight, true, false));
	blurText->setColor(color);

	// Postprocessed scene - surface
	shared_ptr<GuiEntity> postprocessedSurface = make_shared<GuiEntity>("postprocessedSurface");
	postprocessedSurface->setTexture(_renderBus.getPostProcessedSceneMap());
	postprocessedSurface->addOglBuffer(new OpenGLBuffer(0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	postprocessedSurface->setMirroredVertically(true);

	// Postprocessed scene - text
	shared_ptr<TextEntity> postprocessedText = make_shared<TextEntity>("postprocessedText");
	postprocessedText->setTexture(_textureLoader.getText("Postprocessed render", fontPath));
	postprocessedText->addOglBuffer(new OpenGLBuffer(0.66666f, -0.26f, calcTextWidth("Postprocessed render"), charHeight, true, false));
	postprocessedText->setColor(color);

	// Motion scene - surface
	shared_ptr<GuiEntity> motionSurface = make_shared<GuiEntity>("motionSurface");
	motionSurface->setTexture(_renderBus.getMotionBlurMap());
	motionSurface->addOglBuffer(new OpenGLBuffer(0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	motionSurface->setMirroredVertically(true);

	// Motion scene - text
	shared_ptr<TextEntity> motionText = make_shared<TextEntity>("motionText");
	motionText->setTexture(_textureLoader.getText("Motion render", fontPath));
	motionText->addOglBuffer(new OpenGLBuffer(0.66666f, -0.92f, calcTextWidth("Motion render"), charHeight, true, false));
	motionText->setColor(color);
	
	// Render debug screens + text
	_guiEntityRenderer.bind();
	_guiEntityRenderer.render(normalSurface);
	_guiEntityRenderer.render(normalText);
	_guiEntityRenderer.render(shadowSurface);
	_guiEntityRenderer.render(shadowText);
	_guiEntityRenderer.render(reflectionSurface);
	_guiEntityRenderer.render(reflectionText);
	_guiEntityRenderer.render(refractionSurface);
	_guiEntityRenderer.render(refractionText);
	_guiEntityRenderer.render(depthSurface);
	_guiEntityRenderer.render(depthText);
	_guiEntityRenderer.render(bloomSurface);
	_guiEntityRenderer.render(bloomText);
	_guiEntityRenderer.render(blurSurface);
	_guiEntityRenderer.render(blurText);
	_guiEntityRenderer.render(postprocessedSurface);
	_guiEntityRenderer.render(postprocessedText);
	_guiEntityRenderer.render(motionSurface);
	_guiEntityRenderer.render(motionText);
	_guiEntityRenderer.unbind();
}
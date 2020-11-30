#include "render_engine.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;

void RenderEngine::_renderSkyEntity()
{
	if (_entityBus->getSkyEntity() != nullptr)
	{
		// Bind
		_skyEntityRenderer.bind();

		// Render SKY entity
		_skyEntityRenderer.render(_entityBus->getSkyEntity());

		// Unbind
		_skyEntityRenderer.unbind();
	}
}

void RenderEngine::_renderTerrainEntity()
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

void RenderEngine::_renderWaterEntity()
{
	if (_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		_waterEntityRenderer.bind();

		// Render WATER entity
		_waterEntityRenderer.render(_entityBus->getWaterEntity());

		// Unbind
		_waterEntityRenderer.unbind();
	}
}

void RenderEngine::_renderGameEntities()
{
	if (!_entityBus->getGameEntities().empty())
	{
		// Bind
		_gameEntityRenderer.bind();

		// Render lights
		_gameEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render GAME entities
		for (auto& [keyID, gameEntity] : _entityBus->getGameEntities())
		{
			// Check if LOD entity needs to be rendered
			if (gameEntity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				for (auto& [keyID, lodEntity] : _entityBus->getGameEntities())
				{
					if (gameEntity->getLodEntityID() == lodEntity->getID())
					{
						// Save original transformation
						Vec3 originalPosition = lodEntity->getTranslation();
						Vec3 originalRotation = lodEntity->getRotation();
						Vec3 originalSize = lodEntity->getScaling();
						bool originalVisibility = lodEntity->isVisible();

						// Change transformation
						lodEntity->setTranslation(gameEntity->getTranslation());
						lodEntity->setRotation(gameEntity->getRotation());
						lodEntity->setScaling((gameEntity->getScaling() / gameEntity->getOriginalScaling()) * originalSize);
						lodEntity->setVisible(gameEntity->isVisible());
						lodEntity->updateModelMatrix();

						// Render LOD entity
						_gameEntityRenderer.render(lodEntity);

						// Revert to original transformation
						lodEntity->setTranslation(originalPosition);
						lodEntity->setRotation(originalRotation);
						lodEntity->setScaling(originalSize);
						lodEntity->setVisible(originalVisibility);
						lodEntity->updateModelMatrix();
					}
				}
			}
			else // Render high-quality entity
			{
				_gameEntityRenderer.render(gameEntity);
			}
		}

		// Unbind
		_gameEntityRenderer.unbind();
	}
}

void RenderEngine::_renderBillboardEntities()
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

void RenderEngine::_renderAabbEntities()
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

void RenderEngine::_renderFinalSceneTexture()
{
	_finalRenderer.bind();
	_finalRenderer.render(_finalSurface, _renderBus.getMotionBlurMap());
	_finalRenderer.unbind();
}

void RenderEngine::_renderGuiEntities()
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

void RenderEngine::_renderTextEntities()
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

void RenderEngine::_renderCustomCursor()
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

void RenderEngine::_renderDebugScreens()
{
	// Temporary values
	const string fontPath = "engine\\fonts\\font.ttf";
	const Vec3 color = Vec3(0.5f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	std::function<float(string)> calcTextWidth = [&](string text) {return static_cast<float>(text.size()) * charWidth; };

	// Normal scene - surface
	shared_ptr<GuiEntity> normalSurface = make_shared<GuiEntity>("normalSurface");
	normalSurface->setDiffuseMap(_renderBus.getSceneMap());
	normalSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	normalSurface->setMirroredVertically(true);

	// Normal scene - text
	shared_ptr<TextEntity> normalText = make_shared<TextEntity>("normalText");
	normalText->setDiffuseMap(_textureLoader.getText("Default render", fontPath));
	normalText->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.4f, calcTextWidth("Default render"), charHeight, true, false));
	normalText->setColor(color);

	// Shadow scene - surface
	shared_ptr<GuiEntity> shadowSurface = make_shared<GuiEntity>("shadowSurface");
	shadowSurface->setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	shadowSurface->setMirroredVertically(true);

	// Shadow scene - text
	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setDiffuseMap(_textureLoader.getText("Shadow render", fontPath));
	shadowText->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.26f, calcTextWidth("Shadow render"), charHeight, true, false));
	shadowText->setColor(color);

	// Reflection scene - surface
	shared_ptr<GuiEntity> reflectionSurface = make_shared<GuiEntity>("reflectionSurface");
	reflectionSurface->setDiffuseMap(_renderBus.getSceneReflectionMap());
	reflectionSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	reflectionSurface->setMirroredVertically(true);

	// Reflection scene - text
	shared_ptr<TextEntity> reflectionText = make_shared<TextEntity>("reflectionText");
	reflectionText->setDiffuseMap(_textureLoader.getText("Reflection render", fontPath));
	reflectionText->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.92f, calcTextWidth("Reflection render"), charHeight, true, false));
	reflectionText->setColor(color);

	// Refraction scene - surface
	shared_ptr<GuiEntity> refractionSurface = make_shared<GuiEntity>("refractionSurface");
	refractionSurface->setDiffuseMap(_renderBus.getSceneRefractionMap());
	refractionSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.66666f, 0.66666f, 0.66666f, true, false));
	refractionSurface->setMirroredVertically(true);

	// Refraction scene - text
	shared_ptr<TextEntity> refractionText = make_shared<TextEntity>("refractionText");
	refractionText->setDiffuseMap(_textureLoader.getText("Refraction render", fontPath));
	refractionText->addOglBuffer(new OpenGLBuffer(0.0f, 0.4f, calcTextWidth("Refraction render"), charHeight, true, false));
	refractionText->setColor(color);

	// Depth scene - surface
	shared_ptr<GuiEntity> depthSurface = make_shared<GuiEntity>("depthSurface");
	depthSurface->setDepthEntity(true);
	depthSurface->setDiffuseMap(_renderBus.getSceneDepthMap());
	depthSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 0.66666f, 0.66666f, true, false));
	depthSurface->setMirroredVertically(true);

	// Depth scene - text
	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setDiffuseMap(_textureLoader.getText("Depth render", fontPath));
	depthText->addOglBuffer(new OpenGLBuffer(0.0f, -0.26f, calcTextWidth("Depth render"), charHeight, true, false));
	depthText->setColor(color);

	// Bloom scene - surface
	shared_ptr<GuiEntity> bloomSurface = make_shared<GuiEntity>("bloomSurface");
	bloomSurface->setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface->addOglBuffer(new OpenGLBuffer(0.0f, -0.66666f, 0.66666f, 0.66666f, true, false));
	bloomSurface->setMirroredVertically(true);

	// Bloom scene - text
	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setDiffuseMap(_textureLoader.getText("Bloom render", fontPath));
	bloomText->addOglBuffer(new OpenGLBuffer(0.0f, -0.92f, calcTextWidth("Bloom render"), charHeight, true, false));
	bloomText->setColor(color);
	
	// Blur scene - surface
	shared_ptr<GuiEntity> blurSurface = make_shared<GuiEntity>("blurSurface");
	blurSurface->setDiffuseMap(_renderBus.getBlurMap());
	blurSurface->addOglBuffer(new OpenGLBuffer(0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	blurSurface->setMirroredVertically(true);

	// Blur scene - text
	shared_ptr<TextEntity> blurText = make_shared<TextEntity>("blurText");
	blurText->setDiffuseMap(_textureLoader.getText("Blur render", fontPath));
	blurText->addOglBuffer(new OpenGLBuffer(0.66666f, 0.4f, calcTextWidth("Blur render"), charHeight, true, false));
	blurText->setColor(color);

	// Postprocessed scene - surface
	shared_ptr<GuiEntity> postprocessedSurface = make_shared<GuiEntity>("postprocessedSurface");
	postprocessedSurface->setDiffuseMap(_renderBus.getPostProcessedSceneMap());
	postprocessedSurface->addOglBuffer(new OpenGLBuffer(0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	postprocessedSurface->setMirroredVertically(true);

	// Postprocessed scene - text
	shared_ptr<TextEntity> postprocessedText = make_shared<TextEntity>("postprocessedText");
	postprocessedText->setDiffuseMap(_textureLoader.getText("Postprocessed render", fontPath));
	postprocessedText->addOglBuffer(new OpenGLBuffer(0.66666f, -0.26f, calcTextWidth("Postprocessed render"), charHeight, true, false));
	postprocessedText->setColor(color);

	// Final scene - surface
	shared_ptr<GuiEntity> finalSurface = make_shared<GuiEntity>("finalSurface");
	finalSurface->setDiffuseMap(_renderBus.getMotionBlurMap());
	finalSurface->addOglBuffer(new OpenGLBuffer(0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	finalSurface->setMirroredVertically(true);

	// Final scene - text
	shared_ptr<TextEntity> finalText = make_shared<TextEntity>("finalText");
	finalText->setDiffuseMap(_textureLoader.getText("Final render", fontPath));
	finalText->addOglBuffer(new OpenGLBuffer(0.66666f, -0.92f, calcTextWidth("Final render"), charHeight, true, false));
	finalText->setColor(color);
	
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
	_guiEntityRenderer.render(finalSurface);
	_guiEntityRenderer.render(finalText);
	_guiEntityRenderer.unbind();
}
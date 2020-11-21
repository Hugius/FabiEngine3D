#include "render_engine.hpp"
#include "render_bus.hpp"

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
		for (auto& entity : _entityBus->getGameEntities())
		{
			// Check if LOD entity needs to be rendered
			if (entity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				for (auto& lodEntity : _entityBus->getGameEntities())
				{
					if (entity->getLodEntityID() == lodEntity->getID())
					{
						// Save original transformation
						Vec3 originalPosition = lodEntity->getTranslation();
						Vec3 originalRotation = lodEntity->getRotation();
						Vec3 originalSize = lodEntity->getScaling();
						bool originalVisibility = lodEntity->isVisible();

						// Change transformation
						lodEntity->setTranslation(entity->getTranslation());
						lodEntity->setRotation(entity->getRotation());
						lodEntity->setScaling((entity->getScaling() / entity->getOriginalScaling()) * originalSize);
						lodEntity->setVisible(entity->isVisible());
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
				_gameEntityRenderer.render(entity);
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
		for (auto& entity : _entityBus->getBillboardEntities())
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
			for (auto& entity : _entityBus->getAabbEntities())
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

		// Render
		for (auto& entity : _entityBus->getGuiEntities())
		{
			// Custom cursor entity must be rendered last
			if (entity->getID() != _renderBus.getCursorEntityID())
			{
				_guiEntityRenderer.render(entity);
			}
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

		// Render
		for (auto& textEntity : _entityBus->getTextEntities())
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
	for (auto& entity : _entityBus->getGuiEntities())
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
	// Normal scene
	shared_ptr<GuiEntity> normalSurface = make_shared<GuiEntity>("normalSurface");
	normalSurface->setDiffuseMap(_renderBus.getSceneMap());
	normalSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	normalSurface->setMirroredVertically(true);

	// Shadow scene
	shared_ptr<GuiEntity> shadowSurface = make_shared<GuiEntity>("shadowSurface");
	shadowSurface->setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	shadowSurface->setMirroredVertically(true);

	// Reflection scene
	shared_ptr<GuiEntity> reflectionSurface = make_shared<GuiEntity>("reflectionSurface");
	reflectionSurface->setDiffuseMap(_renderBus.getSceneReflectionMap());
	reflectionSurface->addOglBuffer(new OpenGLBuffer(-0.66666f, -0.66666f, 0.66666f, 0.66666f, true, false));
	reflectionSurface->setMirroredVertically(true);

	// Refraction scene
	shared_ptr<GuiEntity> refractionSurface = make_shared<GuiEntity>("refractionSurface");
	refractionSurface->setDiffuseMap(_renderBus.getSceneRefractionMap());
	refractionSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.66666f, 0.66666f, 0.66666f, true, false));
	refractionSurface->setMirroredVertically(true);

	// Depth scene
	shared_ptr<GuiEntity> depthSurface = make_shared<GuiEntity>("depthSurface");
	depthSurface->setDepthEntity(true);
	depthSurface->setDiffuseMap(_renderBus.getSceneDepthMap());
	depthSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 0.66666f, 0.66666f, true, false));
	depthSurface->setMirroredVertically(true);

	// Bloom scene
	shared_ptr<GuiEntity> bloomSurface = make_shared<GuiEntity>("bloomSurface");
	bloomSurface->setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface->addOglBuffer(new OpenGLBuffer(0.0f, -0.66666f, 0.66666f, 0.66666f, true, false));
	bloomSurface->setMirroredVertically(true);
	
	// Blur scene
	shared_ptr<GuiEntity> blurSurface = make_shared<GuiEntity>("blurSurface");
	blurSurface->setDiffuseMap(_renderBus.getBlurMap());
	blurSurface->addOglBuffer(new OpenGLBuffer(0.66666f, 0.66666f, 0.66666f, 0.66666f, true, false));
	blurSurface->setMirroredVertically(true);

	// Final scene
	shared_ptr<GuiEntity> finalSurface = make_shared<GuiEntity>("finalSurface");
	finalSurface->setDiffuseMap(_renderBus.getMotionBlurMap());
	finalSurface->addOglBuffer(new OpenGLBuffer(0.66666f, 0.0f, 0.66666f, 0.66666f, true, false));
	finalSurface->setMirroredVertically(true);
	
	// Render debug screens
	_guiEntityRenderer.bind();
	_guiEntityRenderer.render(normalSurface);
	_guiEntityRenderer.render(shadowSurface);
	_guiEntityRenderer.render(reflectionSurface);
	_guiEntityRenderer.render(refractionSurface);
	_guiEntityRenderer.render(depthSurface);
	_guiEntityRenderer.render(bloomSurface);
	_guiEntityRenderer.render(blurSurface);
	_guiEntityRenderer.render(finalSurface);
	_guiEntityRenderer.unbind();
}
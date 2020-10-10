#include "render_engine.hpp"
#include "render_bus.hpp"

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
						vec3 originalPosition = lodEntity->getTranslation();
						vec3 originalRotation = lodEntity->getRotation();
						vec3 originalSize = lodEntity->getScaling();
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

void RenderEngine::_renderFinalSceneTexture()
{
	_finalRenderer.bind();
	_finalRenderer.render(_finalSurface, _renderBus.getMotionBlurMap());
	_finalRenderer.unbind();
}

void RenderEngine::_renderGuiEntities()
{
	for (auto & entity : _entityBus->getGuiEntities())
	{
		// Custom cursor entity must be rendered last
		if (entity->getID() != _renderBus.getCursorEntityID())
		{
			_guiEntityRenderer.bind();
			_guiEntityRenderer.render(entity);
			_guiEntityRenderer.unbind();
		}
	}
}

void RenderEngine::_renderTextEntities()
{
	for (auto & entity : _entityBus->getTextEntities())
	{
		_guiEntityRenderer.bind();
		_guiEntityRenderer.render(entity);
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
	GuiEntity normalSurface;
	normalSurface.setDiffuseMap(_renderBus.getSceneMap());
	normalSurface.load("normalSurface");
	normalSurface.addOglBuffer(new OpenGLBuffer(-0.75f, 0.75f, 0.5f, 0.5f, true));
	normalSurface.setMirroredVertically(true);

	// Shadow scene
	GuiEntity shadowSurface;
	shadowSurface.setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface.load("shadowSurface");
	shadowSurface.addOglBuffer(new OpenGLBuffer(-0.25f, 0.75f, 0.5f, 0.5f, true));
	shadowSurface.setMirroredVertically(true);
	shadowSurface.setDepthEntity(true);

	// Reflection scene
	GuiEntity reflectionSurface;
	reflectionSurface.setDiffuseMap(_renderBus.getSceneReflectionMap());
	reflectionSurface.load("reflectionSurface");
	reflectionSurface.addOglBuffer(new OpenGLBuffer(0.25f, 0.75f, 0.5f, 0.5f, true));
	reflectionSurface.setMirroredVertically(true);

	// Refraction scene
	GuiEntity refractionSurface;
	refractionSurface.setDiffuseMap(_renderBus.getSceneRefractionMap());
	refractionSurface.load("refractionSurface");
	refractionSurface.addOglBuffer(new OpenGLBuffer(0.75f, 0.75f, 0.5f, 0.5f, true));
	refractionSurface.setMirroredVertically(true);

	// Depth scene
	GuiEntity depthSurface;
	depthSurface.setDepthEntity(true);
	depthSurface.setDiffuseMap(_renderBus.getSceneDepthMap());
	depthSurface.load("depthSurface");
	depthSurface.addOglBuffer(new OpenGLBuffer(-0.75f, 0.25f, 0.5f, 0.5f, true));
	depthSurface.setMirroredVertically(true);

	// Bloom scene
	GuiEntity bloomSurface;
	bloomSurface.setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface.load("bloomSurface");
	bloomSurface.addOglBuffer(new OpenGLBuffer(-0.25f, 0.25f, 0.5f, 0.5f, true));
	bloomSurface.setMirroredVertically(true);
	
	// Blur scene
	GuiEntity blurSurface;
	blurSurface.setDiffuseMap(_renderBus.getBlurMap());
	blurSurface.load("blurSurface");
	blurSurface.addOglBuffer(new OpenGLBuffer(0.25f, 0.25f, 0.5f, 0.5f, true));
	blurSurface.setMirroredVertically(true);

	// Final scene
	GuiEntity finalSurface;
	finalSurface.setDiffuseMap(_renderBus.getMotionBlurMap());
	finalSurface.load("finalSurface");
	finalSurface.addOglBuffer(new OpenGLBuffer(0.75f, 0.25f, 0.5f, 0.5f, true));
	finalSurface.setMirroredVertically(true);
	
	// Render debug screens
	_guiEntityRenderer.bind();
	_guiEntityRenderer.render(&normalSurface);
	_guiEntityRenderer.render(&shadowSurface);
	_guiEntityRenderer.render(&reflectionSurface);
	_guiEntityRenderer.render(&refractionSurface);
	_guiEntityRenderer.render(&depthSurface);
	_guiEntityRenderer.render(&bloomSurface);
	_guiEntityRenderer.render(&blurSurface);
	_guiEntityRenderer.render(&finalSurface);
	_guiEntityRenderer.unbind();
}
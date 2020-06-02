#include "render_engine.hpp"
#include "shader_bus.hpp"

void RenderEngine::_renderSkyEntity()
{
	if (_entityBus->getSkyEntity() != nullptr)
	{
		// Bind
		_skyEntityRenderer.bind();

		// Render
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
		for (auto& light : _entityBus->getLightEntities())
		{
			_terrainEntityRenderer.placeLightEntity(light);
		}

		// Render terrain
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

		// Render water
		_waterEntityRenderer.render(_entityBus->getWaterEntity());

		// Unbind
		_waterEntityRenderer.unbind();
	}
}

void RenderEngine::_renderGameEntities()
{
	// Bind
	_gameEntityRenderer.bind();

	// Render lights
	for (auto & light : _entityBus->getLightEntities())
	{
		_gameEntityRenderer.placeLightEntity(light);
	}

	// Render game entities
	for (auto & entity : _entityBus->getGameEntities())
	{
		_gameEntityRenderer.render(entity);
	}

	// Unbind
	_gameEntityRenderer.unbind();
}

void RenderEngine::_renderBillboardEntities()
{
	// Bind
	_billboardEntityRenderer.bind();

	// Render game entities
	for (auto & entity : _entityBus->getBillboardEntities())
	{
		_billboardEntityRenderer.render(entity);
	}

	// Unbind
	_billboardEntityRenderer.unbind();
}

void RenderEngine::_renderAabbEntities()
{
	if (_shaderBus.isAabbFrameEnabled())
	{
		_aabbEntityRenderer.bind();
		for (auto& entity : _entityBus->getAabbEntities())
		{
			_aabbEntityRenderer.render(entity);
		}
		_aabbEntityRenderer.unbind();
	}
}

void RenderEngine::_renderFinalTexture()
{
	_finalRenderer.bind();
	_finalRenderer.render(_finalSurface, _shaderBus.getMotionBlurMap());
	_finalRenderer.unbind();
}

void RenderEngine::_renderGuiEntities()
{
	for (auto & entity : _entityBus->getGuiEntities())
	{
		_guiEntityRenderer.bind();
		_guiEntityRenderer.render(entity);
		_guiEntityRenderer.unbind();
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

void RenderEngine::_renderDebugScreens()
{
	// Normal scene
	GuiEntity normalSurface;
	normalSurface.setDiffuseMap(_shaderBus.getSceneMap());
	normalSurface.load("normalSurface");
	normalSurface.addOglBuffer(new OpenGLBuffer(-0.75f, 0.75f, 0.5f, 0.5f, true));
	normalSurface.setMirroredVertically(true);

	// Shadow scene
	GuiEntity shadowSurface;
	shadowSurface.setDiffuseMap(_shaderBus.getShadowMap());
	shadowSurface.load("shadowSurface");
	shadowSurface.addOglBuffer(new OpenGLBuffer(-0.25f, 0.75f, 0.5f, 0.5f, true));
	shadowSurface.setMirroredVertically(true);
	shadowSurface.setDepthEntity(true);

	// Reflection scene
	GuiEntity reflectionSurface;
	reflectionSurface.setDiffuseMap(_shaderBus.getSceneReflectionMap());
	reflectionSurface.load("reflectionSurface");
	reflectionSurface.addOglBuffer(new OpenGLBuffer(0.25f, 0.75f, 0.5f, 0.5f, true));
	reflectionSurface.setMirroredVertically(true);

	// Refraction scene
	GuiEntity refractionSurface;
	refractionSurface.setDiffuseMap(_shaderBus.getSceneRefractionMap());
	refractionSurface.load("refractionSurface");
	refractionSurface.addOglBuffer(new OpenGLBuffer(0.75f, 0.75f, 0.5f, 0.5f, true));
	refractionSurface.setMirroredVertically(true);

	// Depth scene
	GuiEntity depthSurface;
	depthSurface.setDepthEntity(true);
	depthSurface.setDiffuseMap(_shaderBus.getDepthMap());
	depthSurface.load("depthSurface");
	depthSurface.addOglBuffer(new OpenGLBuffer(-0.75f, 0.25f, 0.5f, 0.5f, true));
	depthSurface.setMirroredVertically(true);

	// Bloom scene
	GuiEntity bloomSurface;
	bloomSurface.setDiffuseMap(_shaderBus.getBloomMap());
	bloomSurface.load("bloomSurface");
	bloomSurface.addOglBuffer(new OpenGLBuffer(-0.25f, 0.25f, 0.5f, 0.5f, true));
	bloomSurface.setMirroredVertically(true);
	
	// Blur scene
	GuiEntity blurSurface;
	blurSurface.setDiffuseMap(_shaderBus.getBlurMap());
	blurSurface.load("blurSurface");
	blurSurface.addOglBuffer(new OpenGLBuffer(0.25f, 0.25f, 0.5f, 0.5f, true));
	blurSurface.setMirroredVertically(true);

	// Final scene
	GuiEntity finalSurface;
	finalSurface.setDiffuseMap(_shaderBus.getMotionBlurMap());
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
#include <WE3D/RenderEngine.hpp>
#include <WE3D/ShaderBus.hpp>

void RenderEngine::p_renderSkyEntity()
{
	if (p_entityBus->getSkyEntity() != nullptr)
	{
		// Bind
		p_skyEntityRenderer.bind();

		// Render
		p_skyEntityRenderer.render(p_entityBus->getSkyEntity());

		// Unbind
		p_skyEntityRenderer.unbind();
	}
}

void RenderEngine::p_renderTerrainEntity()
{
	if (p_entityBus->getTerrainEntity() != nullptr)
	{
		// Bind
		p_terrainEntityRenderer.bind();

		// Render lights
		for (auto& light : p_entityBus->getLightEntities())
		{
			p_terrainEntityRenderer.placeLightEntity(light);
		}

		// Render terrain
		p_terrainEntityRenderer.render(p_entityBus->getTerrainEntity());

		// Unbind
		p_terrainEntityRenderer.unbind();
	}
}

void RenderEngine::p_renderWaterEntity()
{
	if (p_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		p_waterEntityRenderer.bind();

		// Render water
		p_waterEntityRenderer.render(p_entityBus->getWaterEntity());

		// Unbind
		p_waterEntityRenderer.unbind();
	}
}

void RenderEngine::p_renderGameEntities()
{
	// Bind
	p_gameEntityRenderer.bind();

	// Render lights
	for (auto & light : p_entityBus->getLightEntities())
	{
		p_gameEntityRenderer.placeLightEntity(light);
	}

	// Render game entities
	for (auto & entity : p_entityBus->getGameEntities())
	{
		p_gameEntityRenderer.render(entity);
	}

	// Unbind
	p_gameEntityRenderer.unbind();
}

void RenderEngine::p_renderBillboardEntities()
{
	// Bind
	p_billboardEntityRenderer.bind();

	// Render game entities
	for (auto & entity : p_entityBus->getBillboardEntities())
	{
		p_billboardEntityRenderer.render(entity);
	}

	// Unbind
	p_billboardEntityRenderer.unbind();
}

void RenderEngine::p_renderAabbEntities()
{
	if (p_shaderBus.isAabbFrameEnabled())
	{
		p_aabbEntityRenderer.bind();
		for (auto& entity : p_entityBus->getAabbEntities())
		{
			p_aabbEntityRenderer.render(entity);
		}
		p_aabbEntityRenderer.unbind();
	}
}

void RenderEngine::p_renderFinalTexture()
{
	p_finalRenderer.bind();
	p_finalRenderer.render(&p_finalSurface, p_shaderBus.getMotionBlurMap());
	p_finalRenderer.unbind();
}

void RenderEngine::p_renderGuiEntities()
{
	for (auto & entity : p_entityBus->getGuiEntities())
	{
		p_guiEntityRenderer.bind();
		p_guiEntityRenderer.render(entity);
		p_guiEntityRenderer.unbind();
	}
}

void RenderEngine::p_renderTextEntities()
{
	for (auto & entity : p_entityBus->getTextEntities())
	{
		p_guiEntityRenderer.bind();
		p_guiEntityRenderer.render(entity);
		p_guiEntityRenderer.unbind();
	}
}

void RenderEngine::p_renderDebugScreens()
{
	// Normal scene
	GuiEntity normalSurface;
	normalSurface.setDiffuseMap(p_shaderBus.getSceneMap());
	normalSurface.load("normalSurface");
	normalSurface.addOglBuffer(new OpenGLBuffer(-0.75f, 0.75f, 0.5f, 0.5f, true));
	normalSurface.setMirroredVertically(true);

	// Shadow scene
	GuiEntity shadowSurface;
	shadowSurface.setDiffuseMap(p_shaderBus.getShadowMap());
	shadowSurface.load("shadowSurface");
	shadowSurface.addOglBuffer(new OpenGLBuffer(-0.25f, 0.75f, 0.5f, 0.5f, true));
	shadowSurface.setMirroredVertically(true);
	shadowSurface.setDepthEntity(true);

	// Reflection scene
	GuiEntity reflectionSurface;
	reflectionSurface.setDiffuseMap(p_shaderBus.getSSRMap());
	reflectionSurface.load("reflectionSurface");
	reflectionSurface.addOglBuffer(new OpenGLBuffer(0.25f, 0.75f, 0.5f, 0.5f, true));
	reflectionSurface.setMirroredVertically(true);

	// Refraction scene
	GuiEntity refractionSurface;
	refractionSurface.setDiffuseMap(p_shaderBus.getWaterRefractionMap());
	refractionSurface.load("refractionSurface");
	refractionSurface.addOglBuffer(new OpenGLBuffer(0.75f, 0.75f, 0.5f, 0.5f, true));
	refractionSurface.setMirroredVertically(true);

	// Depth scene
	GuiEntity depthSurface;
	depthSurface.setDepthEntity(true);
	depthSurface.setDiffuseMap(p_shaderBus.getDepthMap());
	depthSurface.load("depthSurface");
	depthSurface.addOglBuffer(new OpenGLBuffer(-0.75f, 0.25f, 0.5f, 0.5f, true));
	depthSurface.setMirroredVertically(true);

	// Bloom scene
	GuiEntity bloomSurface;
	bloomSurface.setDiffuseMap(p_shaderBus.getBloomMap());
	bloomSurface.load("bloomSurface");
	bloomSurface.addOglBuffer(new OpenGLBuffer(-0.25f, 0.25f, 0.5f, 0.5f, true));
	bloomSurface.setMirroredVertically(true);
	
	// Blur scene
	GuiEntity blurSurface;
	blurSurface.setDiffuseMap(p_shaderBus.getBlurMap());
	blurSurface.load("blurSurface");
	blurSurface.addOglBuffer(new OpenGLBuffer(0.25f, 0.25f, 0.5f, 0.5f, true));
	blurSurface.setMirroredVertically(true);

	// Final scene
	GuiEntity finalSurface;
	finalSurface.setDiffuseMap(p_shaderBus.getMotionBlurMap());
	finalSurface.load("finalSurface");
	finalSurface.addOglBuffer(new OpenGLBuffer(0.75f, 0.25f, 0.5f, 0.5f, true));
	finalSurface.setMirroredVertically(true);
	
	// Render debug screens
	p_guiEntityRenderer.bind();
	p_guiEntityRenderer.render(&normalSurface);
	p_guiEntityRenderer.render(&shadowSurface);
	p_guiEntityRenderer.render(&reflectionSurface);
	p_guiEntityRenderer.render(&refractionSurface);
	p_guiEntityRenderer.render(&depthSurface);
	p_guiEntityRenderer.render(&bloomSurface);
	p_guiEntityRenderer.render(&blurSurface);
	p_guiEntityRenderer.render(&finalSurface);
	p_guiEntityRenderer.unbind();
}
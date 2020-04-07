#include <WE3D/RenderEngine.hpp>
#include <WE3D/Configuration.hpp>
#include <WE3D/ShaderBus.hpp>

RenderEngine::RenderEngine(ShaderBus& shaderBus, Timer& timer) :
	p_shaderBus(shaderBus),
	p_timer(timer),
	p_skyEntityRenderer        ("SkyEntityShader.vert",       "SkyEntityShader.frag",       shaderBus),
	p_terrainEntityRenderer    ("TerrainEntityShader.vert",   "TerrainEntityShader.frag",   shaderBus),
	p_waterEntityRenderer      ("WaterEntityShader.vert",     "WaterEntityShader.frag",     shaderBus),
	p_gameEntityRenderer       ("GameEntityShader.vert",      "GameEntityShader.frag",      shaderBus),
	p_billboardEntityRenderer  ("BillboardEntityShader.vert", "BillboardEntityShader.frag", shaderBus),
	p_aabbEntityRenderer       ("AabbEntityShader.vert",      "AabbEntityShader.frag",      shaderBus),
	p_guiEntityRenderer        ("GuiEntityShader.vert",       "GuiEntityShader.frag",       shaderBus),
	p_blurRenderer             ("BlurShader.vert",            "BlurShader.frag",            shaderBus),
	p_bloomHdrRenderer         ("BloomHdrShader.vert",        "BloomHdrShader.frag",        shaderBus),
	p_shadowRenderer           ("ShadowShader.vert",          "ShadowShader.frag",          shaderBus),
	p_depthRenderer            ("DepthShader.vert",           "DepthShader.frag",           shaderBus),
	p_postRenderer             ("PostShader.vert",            "PostShader.frag",            shaderBus),
	p_finalRenderer            ("FinalShader.vert",           "FinalShader.frag",           shaderBus)
{
	// Framebuffers
	p_screenFramebuffer.createColorTexture(Config::getInst().getWindowSize(), 1, false);
	p_msaaFramebuffer.createMsaaTexture(Config::getInst().getWindowSize(), 1, Config::getInst().getMsaaQuality() < 1 ? 1 : Config::getInst().getMsaaQuality() > 16 ? 16 : Config::getInst().getMsaaQuality());
	p_aaProcessorFramebuffer.createColorTexture(Config::getInst().getWindowSize(), 1, false);
	p_bloomDofAdditionFramebuffer.createColorTexture(Config::getInst().getWindowSize(), 1, false);
	p_waterRefractionFramebuffer.createColorTexture(ivec2(Config::getInst().getWaterQuality()), 1, false);
	p_ssrFramebuffer.createColorTexture(ivec2(Config::getInst().getSSRQuality()), 1, false);
	p_bloomHdrFramebuffer.createColorTexture(Config::getInst().getWindowSize()*Config::getInst().getBloomQuality(), 1, false);
	p_shadowFramebuffer.createDepthTexture(ivec2(Config::getInst().getShadowQuality()), 1);
	p_depthFramebuffer.createDepthTexture(Config::getInst().getWindowSize(), 1);
	p_blurRenderer.addFramebuffer(BLUR_BLOOM,  true);
	p_blurRenderer.addFramebuffer(BLUR_DOF,    true);
	p_blurRenderer.addFramebuffer(BLUR_MOTION, true);

	// Final screen texture
	p_finalSurface.load("finalSurface");
	p_finalSurface.addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	p_finalSurface.setMirroredVertically(true);
}

void RenderEngine::renderEngineIntro(GuiEntity * entity, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);
	p_guiEntityRenderer.bind();
	p_guiEntityRenderer.render(entity);
	p_guiEntityRenderer.unbind();
}

void RenderEngine::renderScene(EntityBus * entityBus, CameraManager & camera, ivec2 mousePos)
{
	// General stuff
	p_entityBus = entityBus;
	glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());

	// Wireframe or non-wireframe rendering
	if (p_shaderBus.isWireframeEnabled())
	{
		p_timer.start("wireframe");
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		p_renderSkyEntity();
		p_renderTerrainEntity();
		p_renderWaterEntity();
		p_renderGameEntities();
		p_renderGuiEntities();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		p_timer.stop();
	}
	else
	{
		// Pre-rendering
		p_timer.start("SSRPreRender");
		p_captureSSR(camera);
		p_timer.stop();
		p_timer.start("waterPreRender");
		p_captureWaterRefractions();
		p_timer.stop();
		p_timer.start("shadowPreRender");
		p_captureShadows();
		p_timer.stop();
		p_timer.start("depthPreRender");
		p_captureDepth();
		p_timer.stop();

		// Bind screen framebuffer
		p_timer.start("aaBind");
		if (p_shaderBus.isMSAAEnabled())
		{
			p_msaaFramebuffer.bind();
		}
		else
		{
			p_screenFramebuffer.bind();
		}
		p_timer.stop();

		// 3D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		p_timer.start("skyEntity");
		p_renderSkyEntity();
		p_timer.stop();
		p_timer.start("terrainEntity");
		p_renderTerrainEntity();
		p_timer.stop();
		p_timer.start("waterEntity");
		p_renderWaterEntity();
		p_timer.stop();
		p_timer.start("gameEntities");
		p_renderGameEntities();
		p_timer.stop();
		p_timer.start("billboardEntities");
		p_renderBillboardEntities();
		p_timer.stop();
		p_timer.start("aabbEntities");
		p_renderAabbEntities();
		p_timer.stop();

		// Unbind screen framebuffer
		p_timer.start("aaUnbind");
		if (p_shaderBus.isMSAAEnabled())
		{
			p_msaaFramebuffer.processAAData(&p_aaProcessorFramebuffer);
			p_msaaFramebuffer.unbind();
			p_finalSurface.setDiffuseMap(p_aaProcessorFramebuffer.getTexture(0));
			p_shaderBus.setSceneMap(p_aaProcessorFramebuffer.getTexture(0));
		}
		else
		{
			p_screenFramebuffer.unbind();
			p_finalSurface.setDiffuseMap(p_screenFramebuffer.getTexture(0));
			p_shaderBus.setSceneMap(p_screenFramebuffer.getTexture(0));
		}
		p_timer.stop();

		// Post captures
		p_timer.start("postProcessing");
		p_captureBloom();
		p_captureDofBlur();
		p_capturePostProcessing();
		p_captureMotionBlur(camera, mousePos);

		// 2D rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Render debug or normal
		if (p_shaderBus.isDebugRenderEnabled())
		{
			p_renderDebugScreens();
			p_timer.stop();
		}
		else
		{
			// Render final postprocessed texture
			p_renderFinalTexture();
			p_timer.stop();

			// Render GUI
			p_timer.start("guiRender");
			p_renderGuiEntities();
			p_timer.stop();

			// MSAA text
			p_timer.start("textRender");
			p_msaaFramebuffer.bind();
			glClear(GL_COLOR_BUFFER_BIT);
			p_renderTextEntities();
			p_msaaFramebuffer.processAAData(&p_aaProcessorFramebuffer);
			p_msaaFramebuffer.unbind();
			p_finalSurface.setDiffuseMap(p_aaProcessorFramebuffer.getTexture(0));
			
			// Render text
			p_guiEntityRenderer.bind();
			p_guiEntityRenderer.render(&p_finalSurface);
			p_guiEntityRenderer.unbind();
			p_timer.stop();
		}
	}
}
#include "RenderEngine.hpp"
#include "Configuration.hpp"
#include "ShaderBus.hpp"

RenderEngine::RenderEngine(ShaderBus& shaderBus, Timer& timer) :
	_shaderBus(shaderBus),
	_timer(timer),
	_skyEntityRenderer        ("SkyEntityShader.vert",       "SkyEntityShader.frag",       shaderBus),
	_terrainEntityRenderer    ("TerrainEntityShader.vert",   "TerrainEntityShader.frag",   shaderBus),
	_waterEntityRenderer      ("WaterEntityShader.vert",     "WaterEntityShader.frag",     shaderBus),
	_gameEntityRenderer       ("GameEntityShader.vert",      "GameEntityShader.frag",      shaderBus),
	_billboardEntityRenderer  ("BillboardEntityShader.vert", "BillboardEntityShader.frag", shaderBus),
	_aabbEntityRenderer       ("AabbEntityShader.vert",      "AabbEntityShader.frag",      shaderBus),
	_guiEntityRenderer        ("GuiEntityShader.vert",       "GuiEntityShader.frag",       shaderBus),
	_blurRenderer             ("BlurShader.vert",            "BlurShader.frag",            shaderBus),
	_bloomHdrRenderer         ("BloomHdrShader.vert",        "BloomHdrShader.frag",        shaderBus),
	_shadowRenderer           ("ShadowShader.vert",          "ShadowShader.frag",          shaderBus),
	_depthRenderer            ("DepthShader.vert",           "DepthShader.frag",           shaderBus),
	_postRenderer             ("PostShader.vert",            "PostShader.frag",            shaderBus),
	_finalRenderer            ("FinalShader.vert",           "FinalShader.frag",           shaderBus)
{
	// Framebuffers
	_screenFramebuffer.createColorTexture(Config::getInst().getVpSize(), 1, false);
	_msaaFramebuffer.createMsaaTexture(Config::getInst().getVpSize(), 1, Config::getInst().getMsaaQuality() < 1 ? 1 : Config::getInst().getMsaaQuality() > 16 ? 16 : Config::getInst().getMsaaQuality());
	_aaProcessorFramebuffer.createColorTexture(Config::getInst().getVpSize(), 1, false);
	_bloomDofAdditionFramebuffer.createColorTexture(Config::getInst().getVpSize(), 1, false);
	_waterRefractionFramebuffer.createColorTexture(ivec2(Config::getInst().getWaterQuality()), 1, false);
	_sceneReflectionFramebuffer.createColorTexture(ivec2(Config::getInst().getReflectionQuality()), 1, false);
	_bloomHdrFramebuffer.createColorTexture(Config::getInst().getVpSize(), 1, false);
	_shadowFramebuffer.createDepthTexture(ivec2(Config::getInst().getShadowQuality()), 1);
	_depthFramebuffer.createDepthTexture(Config::getInst().getVpSize(), 1);
	_blurRenderer.addFramebuffer(BLUR_BLOOM,  true);
	_blurRenderer.addFramebuffer(BLUR_DOF,    true);
	_blurRenderer.addFramebuffer(BLUR_MOTION, true);

	// Final screen texture
	_finalSurface.load("finalSurface");
	_finalSurface.addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	_finalSurface.setMirroredVertically(true);
}

void RenderEngine::renderEngineIntro(GuiEntity * entity, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);
	_guiEntityRenderer.bind();
	_guiEntityRenderer.render(entity);
	_guiEntityRenderer.unbind();
}

void RenderEngine::renderScene(EntityBus * entityBus, CameraManager & camera, ivec2 mousePos)
{
	// General stuff
	_entityBus = entityBus;

	// Wireframe or non-wireframe rendering
	if (_shaderBus.isWireframeEnabled())
	{
		_timer.start("wireframe");
		glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderWaterEntity();
		_renderGameEntities();
		_renderGuiEntities();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		_timer.stop();
	}
	else
	{
		// Pre-rendering
		_timer.start("reflectionPreRender");
		_captureSceneReflections(camera);
		_timer.stop();
		_timer.start("waterPreRender");
		_captureWaterRefractions();
		_timer.stop();
		_timer.start("shadowPreRender");
		_captureShadows();
		_timer.stop();
		_timer.start("depthPreRender");
		_captureDepth();
		_timer.stop();

		// Bind screen framebuffer
		_timer.start("aaBind");
		if (_shaderBus.isMSAAEnabled())
		{
			_msaaFramebuffer.bind();
		}
		else
		{
			_screenFramebuffer.bind();
		}
		_timer.stop();

		// 3D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_timer.start("skyEntity");
		_renderSkyEntity();
		_timer.stop();
		_timer.start("terrainEntity");
		_renderTerrainEntity();
		_timer.stop();
		_timer.start("waterEntity");
		_renderWaterEntity();
		_timer.stop();
		_timer.start("gameEntities");
		_renderGameEntities();
		_timer.stop();
		_timer.start("billboardEntities");
		_renderBillboardEntities();
		_timer.stop();
		_timer.start("aabbEntities");
		_renderAabbEntities();
		_timer.stop();

		// Unbind screen framebuffer
		_timer.start("aaUnbind");
		if (_shaderBus.isMSAAEnabled())
		{
			_msaaFramebuffer.processAAData(&_aaProcessorFramebuffer);
			_msaaFramebuffer.unbind();
			_finalSurface.setDiffuseMap(_aaProcessorFramebuffer.getTexture(0));
			_shaderBus.setSceneMap(_aaProcessorFramebuffer.getTexture(0));
		}
		else
		{
			_screenFramebuffer.unbind();
			_finalSurface.setDiffuseMap(_screenFramebuffer.getTexture(0));
			_shaderBus.setSceneMap(_screenFramebuffer.getTexture(0));
		}
		_timer.stop();

		// Post captures
		_timer.start("postProcessing");
		_captureBloom();
		_captureDofBlur();
		_capturePostProcessing();
		_captureMotionBlur(camera, mousePos);

		// 2D rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Render debug or normal
		if (_shaderBus.isDebugRenderEnabled())
		{
			_renderDebugScreens();
			_timer.stop();
		}
		else
		{
			// Render final postprocessed texture
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y);
			_renderFinalTexture();
			glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
			_timer.stop();

			// Render GUI
			_timer.start("guiRender");
			_renderGuiEntities();
			_timer.stop();

			// MSAA text
			_timer.start("textRender");
			_renderTextEntities();
			_timer.stop();
		}
	}
}
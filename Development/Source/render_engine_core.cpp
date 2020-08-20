#include "render_engine.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

RenderEngine::RenderEngine(RenderBus& renderBus, Timer& timer) :
	_renderBus(renderBus),
	_timer(timer),
	_skyEntityRenderer        ("sky_entity_shader.vert",       "sky_entity_shader.frag",       renderBus),
	_terrainEntityRenderer    ("terrain_entity_shader.vert",   "terrain_entity_shader.frag",   renderBus),
	_waterEntityRenderer      ("water_entity_shader.vert",     "water_entity_shader.frag",     renderBus),
	_gameEntityRenderer       ("game_entity_shader.vert",      "game_entity_shader.frag",      renderBus),
	_billboardEntityRenderer  ("billboard_entity_shader.vert", "billboard_entity_shader.frag", renderBus),
	_aabbEntityRenderer       ("aabb_entity_shader.vert",      "aabb_entity_shader.frag",      renderBus),
	_guiEntityRenderer        ("gui_entity_shader.vert",       "gui_entity_shader.frag",       renderBus),
	_blurRenderer             ("blur_shader.vert",             "blur_shader.frag",             renderBus),
	_bloomHdrRenderer         ("bloom_hdr_shader.vert",        "bloom_hdr_shader.frag",        renderBus),
	_shadowRenderer           ("shadow_shader.vert",           "shadow_shader.frag",		   renderBus),
	_depthRenderer            ("depth_shader.vert",            "depth_shader.frag",			   renderBus),
	_postRenderer             ("post_shader.vert",             "post_shader.frag",			   renderBus),
	_finalRenderer            ("final_shader.vert",            "final_shader.frag",			   renderBus)
{
	// Framebuffers
	_screenFramebuffer.createColorTexture(ivec2(0), Config::getInst().getVpSize(), 1, false);
	_msaaFramebuffer.createMsaaTexture(ivec2(0), Config::getInst().getVpSize(), 1, Config::getInst().getMsaaQuality() < 1 ? 1 : Config::getInst().getMsaaQuality() > 16 ? 16 : Config::getInst().getMsaaQuality());
	_aaProcessorFramebuffer.createColorTexture(ivec2(0), Config::getInst().getVpSize(), 1, false);
	_sceneRefractionFramebuffer.createColorTexture(ivec2(0), ivec2(Config::getInst().getRefractionQuality()), 1, false);
	_sceneReflectionFramebuffer.createColorTexture(ivec2(0), ivec2(Config::getInst().getReflectionQuality()), 1, false);
	_bloomHdrFramebuffer.createColorTexture(ivec2(0), Config::getInst().getVpSize(), 1, false);
	_postProcessingFramebuffer.createColorTexture(ivec2(0), Config::getInst().getVpSize(), 1, false);
	_shadowFramebuffer.createDepthTexture(ivec2(0), ivec2(Config::getInst().getShadowQuality()), 1);
	_dofDepthFramebuffer.createDepthTexture(ivec2(0), Config::getInst().getVpSize(), 1);
	_waterDepthFramebuffer.createDepthTexture(ivec2(0), Config::getInst().getVpSize(), 1);
	_blurRenderer.addFramebuffer(static_cast<int>(BlurType::BLOOM),  true);
	_blurRenderer.addFramebuffer(static_cast<int>(BlurType::DOF),    true);
	_blurRenderer.addFramebuffer(static_cast<int>(BlurType::MOTION), true);

	// Final screen texture
	_finalSurface = new GuiEntity();
	_finalSurface->load("finalSurface");
	_finalSurface->addOglBuffer(new OpenGLBuffer(0.0f, 0.0f, 2.0f, 2.0f, true));
	_finalSurface->setMirroredVertically(true);
}

void RenderEngine::renderEngineLogo(GuiEntity * entity, ivec2 viewport)
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
	if (_renderBus.isWireframeRenderingEnabled())
	{
		glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderWaterEntity();
		_renderGameEntities();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
		_renderGuiEntities();
		_renderTextEntities();
	}
	else
	{
		// Pre-rendering
		_timer.start("reflectionPreRender");
		_captureSceneReflections(camera);
		_timer.stop();
		_timer.start("refractionPreRender");
		_captureSceneRefractions();
		_timer.stop();
		_timer.start("shadowPreRender");
		_captureShadows();
		_timer.stop();
		_timer.start("dofDepthPreRender");
		_captureDofDepth();
		_timer.stop();
		_timer.start("waterDepthPreRender");
		_captureWaterDepth();
		_timer.stop();

		// Bind screen framebuffer
		if (_renderBus.isMsaaEnabled())
		{
			_msaaFramebuffer.bind();
		}
		else
		{
			_screenFramebuffer.bind();
		}

		// 3D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderBus.setTriangleCountingEnabled(true);
		_timer.start("skyEntityRender");
		_renderSkyEntity();
		_timer.stop();
		_timer.start("terrainEntityRender");
		_renderTerrainEntity();
		_timer.stop();
		_timer.start("waterEntityRender");
		_renderWaterEntity();
		_timer.stop();
		_timer.start("gameEntityRender");
		_renderGameEntities();
		_timer.stop();
		_timer.start("billboardEntityRender");
		_renderBillboardEntities();
		_timer.stop();
		_timer.start("aabbEntityRender");
		_renderAabbEntities();
		_timer.stop();
		_renderBus.setTriangleCountingEnabled(false);

		// Unbind screen framebuffer
		_timer.start("antiAliasing");
		if (_renderBus.isMsaaEnabled())
		{
			_msaaFramebuffer.processAAData(&_aaProcessorFramebuffer);
			_msaaFramebuffer.unbind();
			_finalSurface->setDiffuseMap(_aaProcessorFramebuffer.getTexture(0));
			_renderBus.setSceneMap(_aaProcessorFramebuffer.getTexture(0));
		}
		else
		{
			_screenFramebuffer.unbind();
			_finalSurface->setDiffuseMap(_screenFramebuffer.getTexture(0));
			_renderBus.setSceneMap(_screenFramebuffer.getTexture(0));
		}
		_timer.stop();

		// Post captures
		_timer.start("postProcessing");
		_captureBloom();
		_captureDofBlur();
		_captureLensFlare();
		_capturePostProcessing();
		_captureMotionBlur(camera, mousePos);

		// 2D rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Render debug or normal
		if (_renderBus.isDebugRenderingEnabled())
		{
			_renderDebugScreens();
			_timer.stop();
		}
		else
		{
			// Render final postprocessed texture
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y+1);
			_renderFinalSceneTexture();
			glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
			_timer.stop();

			// Render GUI entities
			_timer.start("guiEntityRender");
			_renderGuiEntities();
			_timer.stop();

			// Render text entities
			_timer.start("textEntityRender");
			_renderTextEntities();
			_timer.stop();

			// Render custom cursor entity
			_renderCustomCursor();
		}
	}
}
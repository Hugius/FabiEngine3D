#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::make_shared;

MasterRenderer::MasterRenderer(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader, Camera& camera) :
	_renderBus(renderBus),
	_timer(timer),
	_textureLoader(textureLoader),
	_camera(camera),
	_skyEntityRenderer        ("sky_entity_shader.vert",       "sky_entity_shader.frag",       renderBus),
	_terrainEntityRenderer    ("terrain_entity_shader.vert",   "terrain_entity_shader.frag",   renderBus),
	_waterEntityRenderer      ("water_entity_shader.vert",     "water_entity_shader.frag",     renderBus),
	_modelEntityRenderer      ("model_entity_shader.vert",     "model_entity_shader.frag",     renderBus),
	_billboardEntityRenderer  ("billboard_entity_shader.vert", "billboard_entity_shader.frag", renderBus),
	_aabbEntityRenderer       ("aabb_entity_shader.vert",      "aabb_entity_shader.frag",      renderBus),
	_imageEntityRenderer      ("image_entity_shader.vert",     "image_entity_shader.frag",     renderBus),
	_dofRenderer			  ("blur_shader.vert",             "blur_shader.frag",             renderBus),
	_motionBlurRenderer		  ("blur_shader.vert",			   "blur_shader.frag",			   renderBus),
	_bloomRenderer			  ("blur_shader.vert",			   "blur_shader.frag",			   renderBus),
	_shadowRenderer           ("shadow_shader.vert",           "shadow_shader.frag",		   renderBus),
	_depthRenderer            ("depth_shader.vert",            "depth_shader.frag",			   renderBus),
	_postRenderer             ("post_shader.vert",             "post_shader.frag",			   renderBus),
	_finalRenderer            ("final_shader.vert",            "final_shader.frag",			   renderBus)
{
	// Create framebuffers
	_screenFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 2, false);
	_waterRefractionFramebuffer.createColorTexture(Ivec2(0), Ivec2(0), 1, false);
	_waterReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(0), 1, false);
	_postProcessingFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_shadowFramebuffer.createDepthTexture(Ivec2(0), Ivec2(0));
	_sceneDepthFramebuffer.createDepthTexture(Ivec2(0), Config::getInst().getVpSize());
	_dofRenderer.loadFramebuffers(BlurType::DOF, 2);
	_motionBlurRenderer.loadFramebuffers(BlurType::MOTION, 3);
	_bloomRenderer.loadFramebuffers(BlurType::BLOOM, 4);

	// Final screen texture
	_finalSurface = make_shared<ImageEntity>("finalSurface");
	_finalSurface->addRenderBuffer(new RenderBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
	_finalSurface->setMirroredVertically(true);
}

void MasterRenderer::update()
{
	static float lastYaw = _camera.getYaw();
	static float lastPitch = _camera.getPitch();
	_cameraYawDifference = fabsf(_camera.getYaw() - lastYaw);
	_cameraPitchDifference = fabsf(_camera.getPitch() - lastPitch);
	lastYaw = _camera.getYaw();
	lastPitch = _camera.getPitch();
}

void MasterRenderer::renderEngineLogo(shared_ptr<ImageEntity> logo, shared_ptr<TextEntity> text, Ivec2 viewport)
{
	// Prepare
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind
	_imageEntityRenderer.bind();

	// Render logo
	_imageEntityRenderer.render(logo);

	// Render text
	if (text != nullptr)
	{
		_imageEntityRenderer.render(text);
	}

	// Unbind
	_imageEntityRenderer.unbind();
}

void MasterRenderer::renderScene(EntityBus * entityBus)
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
		_renderModelEntities();
		_renderBillboardEntities();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
		_renderGUI();
		_renderCustomCursor();
	}
	else
	{
		// Pre-rendering
		_timer.startDeltaPart("reflectionPreRender");
		_captureSceneReflections();
		_captureWaterReflections();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("refractionPreRender");
		_captureWaterRefractions();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("shadowPreRender");
		_captureShadows();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("depthPreRender");
		_captureSceneDepth();
		_timer.stopDeltaPart();

		// Bind screen framebuffer
		_screenFramebuffer.bind();

		// 3D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderBus.setTriangleCountingEnabled(true);
		_timer.startDeltaPart("skyEntityRender");
		_renderSkyEntity();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("terrainEntityRender");
		_renderTerrainEntity();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("waterEntityRender");
		_renderWaterEntity();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("modelEntityRender");
		_renderModelEntities();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("billboardEntityRender");
		_renderBillboardEntities();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("aabbEntityRender");
		_renderAabbEntities();
		_timer.stopDeltaPart();
		_renderBus.setTriangleCountingEnabled(false);

		// Unbind screen framebuffer
		_screenFramebuffer.unbind();
		_renderBus.setPrimarySceneMap(_screenFramebuffer.getTexture(0));
		_renderBus.setSecondarySceneMap(_screenFramebuffer.getTexture(1));

		// Postprocessing captures
		_timer.startDeltaPart("postProcessing");
		_captureBloom();
		_captureDofBlur();
		_captureLensFlare();
		_capturePostProcessing();
		_captureMotionBlur();
		_timer.stopDeltaPart();

		// 2D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render debug screens
		if (_renderBus.isDebugRenderingEnabled())
		{
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y + 1);
			_renderDebugScreens();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
		}
		else // Render final postprocessed texture
		{
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y +0);
			_renderFinalSceneTexture();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
			
		}

		// Render IMAGE entities & TEXT entities
		_timer.startDeltaPart("guiEntityRender");
		_renderBus.setTriangleCountingEnabled(true);
		_renderGUI();

		// Render custom cursor entity
		_renderCustomCursor();
		_renderBus.setTriangleCountingEnabled(false);
		_timer.stopDeltaPart();
	}
}

void MasterRenderer::loadShadowFramebuffer(int quality)
{
	_shadowFramebuffer.reset();
	_shadowFramebuffer.createDepthTexture(Ivec2(0), Ivec2(quality));
	_renderBus.setShadowMapSize(quality);
}

void MasterRenderer::loadReflectionFramebuffer(int quality)
{
	_sceneReflectionFramebuffer.reset();
	_waterReflectionFramebuffer.reset();
	_sceneReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(quality), 1, false);
	_waterReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(quality), 1, false);
	_renderBus.setReflectionMapSize(quality);
}

void MasterRenderer::loadRefractionFramebuffer(int quality)
{
	_waterRefractionFramebuffer.reset();
	_waterRefractionFramebuffer.createColorTexture(Ivec2(0), Ivec2(quality), 1, false);
	_renderBus.setRefractionMapSize(quality);
}
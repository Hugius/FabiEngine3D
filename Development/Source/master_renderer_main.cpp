#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::make_shared;

MasterRenderer::MasterRenderer(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader, Camera& camera)
	:
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
	_depthRenderer			  ("depth_shader.vert",			   "depth_shader.frag",			   renderBus),
	_shadowRenderer			  ("shadow_shader.vert",		   "shadow_shader.frag",		   renderBus),
	_antiAliasingRenderer	  ("anti_aliasing_shader.vert",	   "anti_aliasing_shader.frag",	   renderBus),
	_dofRenderer			  ("blur_shader.vert",             "blur_shader.frag",             renderBus),
	_motionBlurRenderer		  ("blur_shader.vert",			   "blur_shader.frag",			   renderBus),
	_bloomRendererHighQuality ("blur_shader.vert",			   "blur_shader.frag",			   renderBus),
	_bloomRendererLowQuality  ("blur_shader.vert",			   "blur_shader.frag",			   renderBus),
	_postProcessingRenderer   ("post_processing_shader.vert",  "post_processing_shader.frag",  renderBus),
	_finalRenderer            ("final_shader.vert",            "final_shader.frag",			   renderBus)
{
	// Load framebuffers
	_sceneReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterRefractionFramebuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFRACTION_QUALITY), 1, false);
	_sceneDepthFramebuffer.createDepthTexture(Ivec2(0), Config::getInst().getVpSize());
	_shadowFramebuffer.createDepthTexture(Ivec2(0), Ivec2(Config::MIN_SHADOW_QUALITY));
	_screenFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 2, false);
	_antiAliasingFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_postProcessingFramebuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_dofRenderer.loadFramebuffers(BlurType::DOF, 2);
	_motionBlurRenderer.loadFramebuffers(BlurType::MOTION, 4);
	_bloomRendererHighQuality.loadFramebuffers(BlurType::BLOOM, 2);
	_bloomRendererLowQuality.loadFramebuffers(BlurType::BLOOM, 6);

	// Final screen texture
	_finalSurface = make_shared<ImageEntity>("finalSurface");
	_finalSurface->addRenderBuffer(new RenderBuffer(0.0f, 0.0f, 2.0f, 2.0f, true, false));
}

void MasterRenderer::update()
{
	static float lastYaw = _camera.getYaw();
	static float lastPitch = _camera.getPitch();
	float currentYaw = _camera.getYaw();
	float currentPitch = _camera.getPitch();
	_cameraYawDifference = fabsf(Math::calculateReferenceAngle(currentYaw) - Math::calculateReferenceAngle(lastYaw));
	_cameraPitchDifference = fabsf(Math::calculateReferenceAngle(currentPitch) - Math::calculateReferenceAngle(lastPitch));
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

	if (_renderBus.isWireFrameRenderingEnabled()) // Wire frame rendering
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
	else // Normal rendering
	{
		// Pre-captures
		_timer.startDeltaPart("reflectionPreRender");
		_captureSceneReflections();
		_captureWaterReflections();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("refractionPreRender");
		_captureWaterRefractions();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("depthPreRender");
		_captureSceneDepth();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("shadowPreRender");
		_captureShadows();
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

		// Post-captures
		_timer.startDeltaPart("postProcessing");
		_captureAntiAliasing();
		_captureBloom();
		_captureDofBlur();
		_captureLensFlare();
		_capturePostProcessing();
		_captureMotionBlur();
		_timer.stopDeltaPart();

		// 2D rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (_renderBus.isDebugRenderingEnabled()) // Render debug screens
		{
			glViewport(Config::getInst().getVpPos().x, Config::getInst().getVpPos().y, Config::getInst().getVpSize().x, Config::getInst().getVpSize().y + 1);
			_renderDebugScreens();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
		}
		else // Render final scene texture
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

void MasterRenderer::reloadShadowFramebuffer()
{
	_shadowFramebuffer.reset();
	_shadowFramebuffer.createDepthTexture(Ivec2(0), Ivec2(_renderBus.getShadowQuality()));
}

void MasterRenderer::reloadSceneReflectionFramebuffer()
{
	_sceneReflectionFramebuffer.reset();
	_sceneReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionFramebuffer()
{
	_waterReflectionFramebuffer.reset();
	_waterReflectionFramebuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionFramebuffer()
{
	_waterRefractionFramebuffer.reset();
	_waterRefractionFramebuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getRefractionQuality()), 1, false);
}
#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::make_shared;
using std::max;
using std::clamp;

MasterRenderer::MasterRenderer(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader, Camera& camera, ShadowGenerator& shadowGenerator)
	:
	_renderBus(renderBus),
	_timer(timer),
	_textureLoader(textureLoader),
	_camera(camera),
	_shadowGenerator(shadowGenerator),
	_skyEntityColorRenderer("sky_entity_color_shader.vert", "sky_entity_color_shader.frag", renderBus),
	_terrainEntityColorRenderer("terrain_entity_color_shader.vert", "terrain_entity_color_shader.frag", renderBus),
	_terrainEntityDepthRenderer("terrain_entity_depth_shader.vert", "terrain_entity_depth_shader.frag", renderBus),
	_waterEntityColorRenderer("water_entity_color_shader.vert", "water_entity_color_shader.frag", renderBus),
	_modelEntityColorRenderer("model_entity_color_shader.vert", "model_entity_color_shader.frag", renderBus),
	_modelEntityDepthRenderer("model_entity_depth_shader.vert", "model_entity_depth_shader.frag", renderBus),
	_modelEntityShadowRenderer("model_entity_shadow_shader.vert", "model_entity_shadow_shader.frag", renderBus),
	_billboardEntityColorRenderer("billboard_entity_color_shader.vert", "billboard_entity_color_shader.frag", renderBus),
	_billboardEntityDepthRenderer("billboard_entity_depth_shader.vert", "billboard_entity_depth_shader.frag", renderBus),
	_billboardEntityShadowRenderer("billboard_entity_shadow_shader.vert", "billboard_entity_shadow_shader.frag", renderBus),
	_aabbEntityColorRenderer("aabb_entity_color_shader.vert", "aabb_entity_color_shader.frag", renderBus),
	_imageEntityColorRenderer("image_entity_color_shader.vert", "image_entity_color_shader.frag", renderBus),
	_antiAliasingRenderer("anti_aliasing_shader.vert", "anti_aliasing_shader.frag", renderBus),
	_bloomRenderer("bloom_shader.vert", "bloom_shader.frag", renderBus),
	_dofRenderer("dof_shader.vert", "dof_shader.frag", renderBus),
	_lensFlareRenderer("lens_flare_shader.vert", "lens_flare_shader.frag", renderBus),
	_motionBlurRenderer("motion_blur_shader.vert", "motion_blur_shader.frag", renderBus),
	_bloomBlurRendererHighQuality("blur_shader.vert", "blur_shader.frag", renderBus),
	_bloomBlurRendererLowQuality("blur_shader.vert", "blur_shader.frag", renderBus),
	_dofBlurRenderer("blur_shader.vert", "blur_shader.frag", renderBus),
	_motionBlurBlurRenderer("blur_shader.vert", "blur_shader.frag", renderBus)
{
	// Post-processing capture buffers
	_sceneDepthCaptureBuffer.createDepthTexture(Ivec2(0), Config::getInst().getVpSize());
	_sceneColorCaptureBuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 2, false);
	_antiAliasingCaptureBuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_bloomCaptureBuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_dofCaptureBuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_lensFlareCaptureBuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_motionBlurCaptureBuffer.createColorTexture(Ivec2(0), Config::getInst().getVpSize(), 1, false);
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getVpSize() / Config::MIN_BLOOM_SIZE);
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getVpSize() / (Config::MIN_BLOOM_SIZE * 2));
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getVpSize() / Config::MIN_DOF_SIZE);
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getVpSize() / Config::MIN_MOTION_BLUR_SIZE);

	// Miscellaneous capture buffers
	_cubeReflectionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_planarReflectionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterReflectionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterRefractionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(Config::MIN_REFRACTION_QUALITY), 1, false);
	_shadowCaptureBuffer.createDepthTexture(Ivec2(0), Ivec2(Config::MIN_SHADOW_QUALITY));

	// Render surface
	_renderSurface = make_shared<ImageEntity>("renderSurface");
	_renderSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
}

void MasterRenderer::update()
{
	_updateMotionBlur();
	_updateLensFlare();
}

void MasterRenderer::renderEngineLogo(shared_ptr<ImageEntity> logo, shared_ptr<TextEntity> text, Ivec2 viewport)
{
	// Prepare
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind
	_imageEntityColorRenderer.bind();

	// Render logo
	_imageEntityColorRenderer.render(logo);

	// Render text
	if (text != nullptr)
	{
		_imageEntityColorRenderer.render(text);
	}

	// Unbind
	_imageEntityColorRenderer.unbind();
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
		_captureCubeReflections();
		_capturePlanarReflections();
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

		// Bind scene capture buffer
		_sceneColorCaptureBuffer.bind();

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

		// Unbind scene capture buffer
		_sceneColorCaptureBuffer.unbind();
		_renderBus.setFinalSceneMap(_sceneColorCaptureBuffer.getTexture(0));
		_renderBus.setPrimarySceneMap(_sceneColorCaptureBuffer.getTexture(0));
		_renderBus.setSecondarySceneMap(_sceneColorCaptureBuffer.getTexture(1));

		// Post-captures
		_timer.startDeltaPart("postProcessing");
		_captureAntiAliasing();
		_captureBloom();
		_captureDOF();
		_captureLensFlare();
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
			_renderFinalSceneImage();
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

void MasterRenderer::reloadBloomBlurCaptureBuffer()
{
	_bloomBlurRendererHighQuality.resetCaptureBuffer();
	_bloomBlurRendererLowQuality.resetCaptureBuffer();
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getVpSize() / _renderBus.getBloomSize());
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getVpSize() / (_renderBus.getBloomSize() * 2));
}

void MasterRenderer::reloadDofBlurCaptureBuffer()
{
	_dofBlurRenderer.resetCaptureBuffer();
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getVpSize() / _renderBus.getDofSize());
}

void MasterRenderer::reloadMotionBlurBlurCaptureBuffer()
{
	_motionBlurBlurRenderer.resetCaptureBuffer();
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getVpSize() / _renderBus.getMotionBlurSize	());
}

void MasterRenderer::reloadCubeReflectionCaptureBuffer()
{
	_cubeReflectionCaptureBuffer.reset();
	_cubeReflectionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionCaptureBuffer()
{
	_planarReflectionCaptureBuffer.reset();
	_planarReflectionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionCaptureBuffer()
{
	_waterReflectionCaptureBuffer.reset();
	_waterReflectionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionCaptureBuffer()
{
	_waterRefractionCaptureBuffer.reset();
	_waterRefractionCaptureBuffer.createColorTexture(Ivec2(0), Ivec2(_renderBus.getRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowCaptureBuffer()
{
	_shadowCaptureBuffer.reset();
	_shadowCaptureBuffer.createDepthTexture(Ivec2(0), Ivec2(_renderBus.getShadowQuality()));
}

void MasterRenderer::_updateMotionBlur()
{
	if (_renderBus.isMotionBlurEnabled())
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
}

void MasterRenderer::_updateLensFlare()
{
	if (_renderBus.isLensFlareEnabled())
	{
		// Calculate screen position
		auto lightPosition = _renderBus.getDirectionalLightingPosition();
		auto viewMatrix = _renderBus.getViewMatrix();
		auto projectionMatrix = _renderBus.getProjectionMatrix();
		Vec4 clipSpacePosition = (projectionMatrix * viewMatrix * Vec4(lightPosition.x, lightPosition.y, lightPosition.z, 1.0f));
		float alpha = 0.0f;

		// Calculate transparency value
		if (clipSpacePosition.w > 0.0f)
		{
			const float x = (clipSpacePosition.x / clipSpacePosition.w);
			const float y = (clipSpacePosition.y / clipSpacePosition.w);
			alpha = (1.0f - (max(fabsf(x), fabsf(y)) * _renderBus.getLensFlareMultiplier()));
			alpha = clamp(alpha, 0.0f, 1.0f);
		}

		// Update shader properties
		_renderBus.setLensFlareAlpha(alpha);
		_renderBus.setFlareSourcePositionClipspace(clipSpacePosition);
		_renderBus.setFlareSourcePosition(lightPosition);
	}
}
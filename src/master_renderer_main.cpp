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
	_worldDepthCaptureBuffer.createDepthTexture(ivec2(0), Config::getInst().getViewportSize());
	_worldColorCaptureBuffer.createColorTexture(ivec2(0), Config::getInst().getViewportSize(), 2, false);
	_antiAliasingCaptureBuffer.createColorTexture(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_bloomCaptureBuffer.createColorTexture(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_dofCaptureBuffer.createColorTexture(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_lensFlareCaptureBuffer.createColorTexture(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_motionBlurCaptureBuffer.createColorTexture(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_BLOOM_QUALITY);
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (Config::MIN_BLOOM_QUALITY * 2));
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_DOF_QUALITY);
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_MOTION_BLUR_QUALITY);

	_cubeReflectionCaptureBuffer.createColorTexture(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_planarReflectionCaptureBuffer.createColorTexture(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterReflectionCaptureBuffer.createColorTexture(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterRefractionCaptureBuffer.createColorTexture(ivec2(0), ivec2(Config::MIN_REFRACTION_QUALITY), 1, false);
	_shadowCaptureBuffer.createDepthTexture(ivec2(0), ivec2(Config::MIN_SHADOW_QUALITY));

	_renderSurface = make_shared<ImageEntity>("renderSurface");
	_renderSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
}

void MasterRenderer::update()
{
	_updateMotionBlur();
	_updateLensFlare();
}

void MasterRenderer::renderEngineLogo(shared_ptr<ImageEntity> logo, shared_ptr<TextEntity> text, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);

	_imageEntityColorRenderer.bind();

	_imageEntityColorRenderer.render(logo);

	if(text != nullptr)
	{
		_imageEntityColorRenderer.render(text);
	}

	_imageEntityColorRenderer.unbind();
}

void MasterRenderer::renderWorld(EntityBus* entityBus)
{
	_entityBus = entityBus;

	if(_renderBus.isWireframeRenderingEnabled()) // Wireframe rendering
	{
		glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y);
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
		_renderCursor();
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
		_captureWorldDepth();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("shadowPreRender");
		_captureShadows();
		_timer.stopDeltaPart();

		// Bind world capture buffer
		_worldColorCaptureBuffer.bind();

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
		_timer.startDeltaPart("billboardEntityRender");
		_renderBillboardEntities();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("aabbEntityRender");
		_renderAabbEntities();
		_timer.stopDeltaPart();
		_timer.startDeltaPart("modelEntityRender");
		_renderModelEntities();
		_timer.stopDeltaPart();
		_renderBus.setTriangleCountingEnabled(false);

		// Unbind world capture buffer
		_worldColorCaptureBuffer.unbind();
		_renderBus.setFinalWorldMap(_worldColorCaptureBuffer.getTexture(0));
		_renderBus.setPrimaryWorldMap(_worldColorCaptureBuffer.getTexture(0));
		_renderBus.setSecondaryWorldMap(_worldColorCaptureBuffer.getTexture(1));

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

		if(_renderBus.isDebugRenderingEnabled()) // Render debug screens
		{
			glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y + 1);
			_renderDebugScreens();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
		}
		else // Render final world texture
		{
			glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y + 0);
			_renderFinalWorldImage();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);

		}

		// Render image entities & text entities
		_timer.startDeltaPart("guiEntityRender");
		_renderBus.setTriangleCountingEnabled(true);
		_renderGUI();

		// Render custom cursor entity
		_renderCursor();
		_renderBus.setTriangleCountingEnabled(false);
		_timer.stopDeltaPart();
	}
}

void MasterRenderer::reloadBloomBlurCaptureBuffer()
{
	_bloomBlurRendererHighQuality.resetCaptureBuffer();
	_bloomBlurRendererLowQuality.resetCaptureBuffer();
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus.getBloomQuality());
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (_renderBus.getBloomQuality() * 2));
}

void MasterRenderer::reloadDofBlurCaptureBuffer()
{
	_dofBlurRenderer.resetCaptureBuffer();
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus.getDofQuality());
}

void MasterRenderer::reloadMotionBlurBlurCaptureBuffer()
{
	_motionBlurBlurRenderer.resetCaptureBuffer();
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus.getMotionBlurQuality());
}

void MasterRenderer::reloadCubeReflectionCaptureBuffer()
{
	_cubeReflectionCaptureBuffer.reset();
	_cubeReflectionCaptureBuffer.createColorTexture(ivec2(0), ivec2(_renderBus.getCubeReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionCaptureBuffer()
{
	_planarReflectionCaptureBuffer.reset();
	_planarReflectionCaptureBuffer.createColorTexture(ivec2(0), ivec2(_renderBus.getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionCaptureBuffer()
{
	_waterReflectionCaptureBuffer.reset();
	_waterReflectionCaptureBuffer.createColorTexture(ivec2(0), ivec2(_renderBus.getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionCaptureBuffer()
{
	_waterRefractionCaptureBuffer.reset();
	_waterRefractionCaptureBuffer.createColorTexture(ivec2(0), ivec2(_renderBus.getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowCaptureBuffer()
{
	_shadowCaptureBuffer.reset();
	_shadowCaptureBuffer.createDepthTexture(ivec2(0), ivec2(_renderBus.getShadowQuality()));
}

void MasterRenderer::_updateMotionBlur()
{
	if(_renderBus.isMotionBlurEnabled())
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
	if(_renderBus.isLensFlareEnabled())
	{
		// Temporary values
		auto flareSourcePosition = _renderBus.getDirectionalLightingPosition();
		auto viewMatrix = _renderBus.getViewMatrix();
		auto projectionMatrix = _renderBus.getProjectionMatrix();
		float transparency = 0.0f;

		// Calculate screen position
		fvec4 flareSourceClip = (projectionMatrix * viewMatrix * fvec4(flareSourcePosition.x, flareSourcePosition.y, flareSourcePosition.z, 1.0f));
		fvec2 flareSourceNDC = (fvec2(flareSourceClip.x, flareSourceClip.y) / flareSourceClip.w);
		fvec2 flareSourceUV = fvec2(((flareSourceNDC.x + 1.0f) / 2.0f), ((flareSourceNDC.y + 1.0f) / 2.0f));

		// Check if flare source is visible
		if((flareSourceNDC.x > -1.0f) && (flareSourceNDC.x < 1.0f) && (flareSourceNDC.y > -1.0f) && (flareSourceNDC.y < 1.0f))
		{

			transparency = (1.0f - (max(fabsf(flareSourceNDC.x), fabsf(flareSourceNDC.y)) / _renderBus.getLensFlareSensitivity()));
			transparency = clamp(transparency, 0.0f, 1.0f);
		}

		// Update shader properties
		_renderBus.setLensFlareTransparency(transparency);
		_renderBus.setFlareSourcePosition(flareSourcePosition);
		_renderBus.setFlareSourceUV(flareSourceUV);
	}
}
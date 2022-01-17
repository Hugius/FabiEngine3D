#include "master_renderer.hpp"
#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::make_shared;
using std::max;
using std::clamp;

MasterRenderer::MasterRenderer()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_renderSurface = make_shared<Quad2dEntity>("renderQuad");
	_renderSurface->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	_renderSurface->setCentered(true);

	_skyEntityColorShader = make_shared<ShaderBuffer>("sky_entity_color_shader.vert", "sky_entity_color_shader.frag");
	_terrainEntityColorShader = make_shared<ShaderBuffer>("terrain_entity_color_shader.vert", "terrain_entity_color_shader.frag");
	_terrainEntityDepthShader = make_shared<ShaderBuffer>("terrain_entity_depth_shader.vert", "terrain_entity_depth_shader.frag");
	_waterEntityColorShader = make_shared<ShaderBuffer>("water_entity_color_shader.vert", "water_entity_color_shader.frag");
	_modelEntityColorShader = make_shared<ShaderBuffer>("model_entity_color_shader.vert", "model_entity_color_shader.frag");
	_modelEntityDepthShader = make_shared<ShaderBuffer>("model_entity_depth_shader.vert", "model_entity_depth_shader.frag");
	_modelEntityShadowShader = make_shared<ShaderBuffer>("model_entity_shadow_shader.vert", "model_entity_shadow_shader.frag");
	_quad3dEntityColorShader = make_shared<ShaderBuffer>("billboard_entity_color_shader.vert", "billboard_entity_color_shader.frag");
	_quad3dEntityDepthShader = make_shared<ShaderBuffer>("billboard_entity_depth_shader.vert", "billboard_entity_depth_shader.frag");
	_quad3dEntityShadowShader = make_shared<ShaderBuffer>("billboard_entity_shadow_shader.vert", "billboard_entity_shadow_shader.frag");
	_aabbEntityColorShader = make_shared<ShaderBuffer>("aabb_entity_color_shader.vert", "aabb_entity_color_shader.frag");
	_quad2dEntityColorShader = make_shared<ShaderBuffer>("quad2d_entity_color_shader.vert", "quad2d_entity_color_shader.frag");
	_antiAliasingShader = make_shared<ShaderBuffer>("anti_aliasing_shader.vert", "anti_aliasing_shader.frag");
	_bloomShader = make_shared<ShaderBuffer>("bloom_shader.vert", "bloom_shader.frag");
	_dofShader = make_shared<ShaderBuffer>("dof_shader.vert", "dof_shader.frag");
	_lensFlareShader = make_shared<ShaderBuffer>("lens_flare_shader.vert", "lens_flare_shader.frag");
	_motionBlurShader = make_shared<ShaderBuffer>("motion_blur_shader.vert", "motion_blur_shader.frag");
	_blurShader = make_shared<ShaderBuffer>("blur_shader.vert", "blur_shader.frag");

	_worldDepthCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize);
	_worldColorCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 2, false);
	_antiAliasingCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_bloomCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_dofCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_lensFlareCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_motionBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_cubeReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_planarReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterRefractionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFRACTION_QUALITY), 1, false);
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_SHADOW_QUALITY));
	_bloomBlurCaptorHighQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / Config::MIN_BLOOM_QUALITY), 1, true);
	_bloomBlurCaptorLowQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / (Config::MIN_BLOOM_QUALITY * 2)), 1, true);
	_dofBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / Config::MIN_DOF_QUALITY), 1, true);
	_motionBlurBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / Config::MIN_MOTION_BLUR_QUALITY), 1, true);

	_skyEntityColorRenderer.inject(_skyEntityColorShader);
	_terrainEntityColorRenderer.inject(_terrainEntityColorShader);
	_terrainEntityDepthRenderer.inject(_terrainEntityDepthShader);
	_waterEntityColorRenderer.inject(_waterEntityColorShader);
	_modelEntityColorRenderer.inject(_modelEntityColorShader);
	_modelEntityDepthRenderer.inject(_modelEntityDepthShader);
	_modelEntityShadowRenderer.inject(_modelEntityShadowShader);
	_quad3dEntityColorRenderer.inject(_quad3dEntityColorShader);
	_quad3dEntityDepthRenderer.inject(_quad3dEntityDepthShader);
	_quad3dEntityShadowRenderer.inject(_quad3dEntityShadowShader);
	_aabbEntityColorRenderer.inject(_aabbEntityColorShader);
	_quad2dEntityColorRenderer.inject(_quad2dEntityColorShader);
	_antiAliasingRenderer.inject(_antiAliasingShader);
	_bloomRenderer.inject(_bloomShader);
	_dofRenderer.inject(_dofShader);
	_lensFlareRenderer.inject(_lensFlareShader);
	_motionBlurRenderer.inject(_motionBlurShader);
	_bloomBlurRendererHighQuality.inject(_blurShader);
	_bloomBlurRendererHighQuality.inject(_bloomBlurCaptorHighQuality);
	_bloomBlurRendererLowQuality.inject(_blurShader);
	_bloomBlurRendererLowQuality.inject(_bloomBlurCaptorLowQuality);
	_dofBlurRenderer.inject(_blurShader);
	_dofBlurRenderer.inject(_dofBlurCaptor);
	_motionBlurBlurRenderer.inject(_blurShader);
	_motionBlurBlurRenderer.inject(_motionBlurBlurCaptor);
}

void MasterRenderer::update()
{
	_updateMotionBlur();
	_updateLensFlare();
}

void MasterRenderer::renderLogo(shared_ptr<Quad2dEntity> logo, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);

	glClear(GL_COLOR_BUFFER_BIT);

	_quad2dEntityColorRenderer.bind();

	_quad2dEntityColorRenderer.render(logo);

	_quad2dEntityColorRenderer.unbind();
}

void MasterRenderer::renderApplication()
{
	const auto& config = Config::getInst();

	if(_renderBus->isWireframeRenderingEnabled())
	{
		glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderWaterEntity();
		_renderModelEntities();
		_renderQuad3dEntities();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);
		_renderGUI();
		_renderCursor();
		return;
	}

	_timer->startDeltaPart("reflectionPreRender");
	_captureCubeReflections();
	_capturePlanarReflections();
	_captureWaterReflections();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("refractionPreRender");
	_captureWaterRefractions();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("depthPreRender");
	_captureWorldDepth();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("shadowPreRender");
	_captureShadows();
	_timer->stopDeltaPart();

	_worldColorCaptor->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_renderBus->setTriangleCountingEnabled(true);
	_timer->startDeltaPart("skyEntityRender");
	_renderSkyEntity();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("terrainEntityRender");
	_renderTerrainEntity();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("waterEntityRender");
	_renderWaterEntity();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("quad3dEntityRender");
	_renderQuad3dEntities();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("aabbEntityRender");
	_renderAabbEntities();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("modelEntityRender");
	_renderModelEntities();
	_timer->stopDeltaPart();
	_renderBus->setTriangleCountingEnabled(false);

	_worldColorCaptor->unbind();
	_renderBus->setPrimarySceneMap(_worldColorCaptor->getTexture(0));
	_renderBus->setSecondarySceneMap(_worldColorCaptor->getTexture(1));
	_renderBus->setFinalSceneMap(_renderBus->getPrimarySceneMap());

	_timer->startDeltaPart("postProcessing");
	_captureAntiAliasing();
	_captureBloom();
	_captureDOF();
	_captureLensFlare();
	_captureMotionBlur();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
	_renderFinalSceneMap();
	glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);
	_timer->stopDeltaPart();

	_timer->startDeltaPart("guiEntityRender");
	_renderBus->setTriangleCountingEnabled(true);
	_renderGUI();
	_renderCursor();
	_renderBus->setTriangleCountingEnabled(false);
	_timer->stopDeltaPart();
}

void MasterRenderer::reloadBloomBlurCaptureBuffer()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_bloomBlurCaptorHighQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderBus->getBloomQuality()), 1, true);
	_bloomBlurCaptorLowQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / (_renderBus->getBloomQuality() * 2)), 1, true);
}

void MasterRenderer::reloadDofBlurCaptureBuffer()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_dofBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderBus->getDofQuality()), 1, true);
}

void MasterRenderer::reloadMotionBlurBlurCaptureBuffer()
{
	const auto viewportSize = Config::getInst().getViewportSize();

	_motionBlurBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / _renderBus->getMotionBlurQuality()), 1, true);
}

void MasterRenderer::reloadCubeReflectionCaptureBuffer()
{
	_cubeReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getCubeReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionCaptureBuffer()
{
	_planarReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionCaptureBuffer()
{
	_waterReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionCaptureBuffer()
{
	_waterRefractionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowCaptureBuffer()
{
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus->getShadowQuality()));
}

void MasterRenderer::_updateMotionBlur()
{
	if(_renderBus->isMotionBlurEnabled())
	{
		static auto lastYaw = _camera->getYaw();
		static auto lastPitch = _camera->getPitch();
		const auto currentYaw = _camera->getYaw();
		const auto currentPitch = _camera->getPitch();

		_cameraYawDifference = fabsf(Math::calculateReferenceAngle(currentYaw) - Math::calculateReferenceAngle(lastYaw));
		_cameraPitchDifference = fabsf(Math::calculateReferenceAngle(currentPitch) - Math::calculateReferenceAngle(lastPitch));

		lastYaw = _camera->getYaw();
		lastPitch = _camera->getPitch();
	}
}

void MasterRenderer::_updateLensFlare()
{
	if(_renderBus->isLensFlareEnabled())
	{
		auto flareSourcePosition = _renderBus->getDirectionalLightingPosition();
		auto viewMatrix = _renderBus->getViewMatrix();
		auto projectionMatrix = _renderBus->getProjectionMatrix();
		float transparency = 0.0f;

		fvec4 flareSourceClip = (projectionMatrix * viewMatrix * fvec4(flareSourcePosition.x, flareSourcePosition.y, flareSourcePosition.z, 1.0f));
		fvec2 flareSourceNdc = (fvec2(flareSourceClip.x, flareSourceClip.y) / flareSourceClip.w);
		fvec2 flareSourceUv = fvec2(((flareSourceNdc.x + 1.0f) / 2.0f), ((flareSourceNdc.y + 1.0f) / 2.0f));

		if((flareSourceNdc.x > -1.0f) && (flareSourceNdc.x < 1.0f) && (flareSourceNdc.y > -1.0f) && (flareSourceNdc.y < 1.0f))
		{
			transparency = (1.0f - (max(fabsf(flareSourceNdc.x), fabsf(flareSourceNdc.y)) / _renderBus->getLensFlareSensitivity()));
			transparency = clamp(transparency, 0.0f, 1.0f);
		}

		_renderBus->setLensFlareTransparency(transparency);
		_renderBus->setFlareSourcePosition(flareSourcePosition);
		_renderBus->setFlareSourceUv(flareSourceUv);
	}
}
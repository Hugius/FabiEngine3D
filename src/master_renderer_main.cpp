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
	_renderQuad = make_shared<QuadEntity>("renderQuad");
	_renderQuad->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	_renderQuad->setCentered(true);

	_skyEntityColorShader = make_shared<ShaderBuffer>("sky_entity_color_shader.vert", "sky_entity_color_shader.frag");
	_terrainEntityColorShader = make_shared<ShaderBuffer>("terrain_entity_color_shader.vert", "terrain_entity_color_shader.frag");
	_terrainEntityDepthShader = make_shared<ShaderBuffer>("terrain_entity_depth_shader.vert", "terrain_entity_depth_shader.frag");
	_waterEntityColorShader = make_shared<ShaderBuffer>("water_entity_color_shader.vert", "water_entity_color_shader.frag");
	_modelEntityColorShader = make_shared<ShaderBuffer>("model_entity_color_shader.vert", "model_entity_color_shader.frag");
	_modelEntityDepthShader = make_shared<ShaderBuffer>("model_entity_depth_shader.vert", "model_entity_depth_shader.frag");
	_modelEntityShadowShader = make_shared<ShaderBuffer>("model_entity_shadow_shader.vert", "model_entity_shadow_shader.frag");
	_billboardEntityColorShader = make_shared<ShaderBuffer>("billboard_entity_color_shader.vert", "billboard_entity_color_shader.frag");
	_billboardEntityDepthShader = make_shared<ShaderBuffer>("billboard_entity_depth_shader.vert", "billboard_entity_depth_shader.frag");
	_billboardEntityShadowShader = make_shared<ShaderBuffer>("billboard_entity_shadow_shader.vert", "billboard_entity_shadow_shader.frag");
	_aabbEntityColorShader = make_shared<ShaderBuffer>("aabb_entity_color_shader.vert", "aabb_entity_color_shader.frag");
	_quadEntityColorShader = make_shared<ShaderBuffer>("quad_entity_color_shader.vert", "quad_entity_color_shader.frag");
	_antiAliasingShader = make_shared<ShaderBuffer>("anti_aliasing_shader.vert", "anti_aliasing_shader.frag");
	_bloomShader = make_shared<ShaderBuffer>("bloom_shader.vert", "bloom_shader.frag");
	_dofShader = make_shared<ShaderBuffer>("dof_shader.vert", "dof_shader.frag");
	_lensFlareShader = make_shared<ShaderBuffer>("lens_flare_shader.vert", "lens_flare_shader.frag");
	_motionBlurShader = make_shared<ShaderBuffer>("motion_blur_shader.vert", "motion_blur_shader.frag");
	_blurShader = make_shared<ShaderBuffer>("blur_shader.vert", "blur_shader.frag");

	_worldDepthCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize());
	_worldColorCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 2, false);
	_antiAliasingCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_bloomCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_dofCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_lensFlareCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_motionBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false);
	_cubeReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_planarReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false);
	_waterRefractionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFRACTION_QUALITY), 1, false);
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_SHADOW_QUALITY));

	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_BLOOM_QUALITY);
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (Config::MIN_BLOOM_QUALITY * 2));
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_DOF_QUALITY);
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_MOTION_BLUR_QUALITY);
}

void MasterRenderer::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

void MasterRenderer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void MasterRenderer::inject(shared_ptr<ShadowGenerator> shadowGenerator)
{
	_shadowGenerator = shadowGenerator;
}

void MasterRenderer::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void MasterRenderer::inject(shared_ptr<SkyEntityManager> skyEntityManager)
{
	_skyEntityManager = skyEntityManager;
}

void MasterRenderer::inject(shared_ptr<TerrainEntityManager> terrainEntityManager)
{
	_terrainEntityManager = terrainEntityManager;
}

void MasterRenderer::inject(shared_ptr<WaterEntityManager> waterEntityManager)
{
	_waterEntityManager = waterEntityManager;
}

void MasterRenderer::inject(shared_ptr<ModelEntityManager> modelEntityManager)
{
	_modelEntityManager = modelEntityManager;
}

void MasterRenderer::inject(shared_ptr<BillboardEntityManager> billboardEntityManager)
{
	_billboardEntityManager = billboardEntityManager;
}

void MasterRenderer::inject(shared_ptr<AabbEntityManager> aabbEntityManager)
{
	_aabbEntityManager = aabbEntityManager;
}

void MasterRenderer::inject(shared_ptr<QuadEntityManager> quadEntityManager)
{
	_quadEntityManager = quadEntityManager;
}

void MasterRenderer::inject(shared_ptr<TextEntityManager> textEntityManager)
{
	_textEntityManager = textEntityManager;
}

void MasterRenderer::inject(shared_ptr<PointlightEntityManager> pointlightEntityManager)
{
	_pointlightEntityManager = pointlightEntityManager;
}

void MasterRenderer::inject(shared_ptr<SpotlightEntityManager> spotlightEntityManager)
{
	_spotlightEntityManager = spotlightEntityManager;
}

void MasterRenderer::inject(shared_ptr<ReflectionEntityManager> reflectionEntityManager)
{
	_reflectionEntityManager = reflectionEntityManager;
}

void MasterRenderer::update()
{
	_updateMotionBlur();
	_updateLensFlare();
}

void MasterRenderer::renderLogo(shared_ptr<QuadEntity> logo, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);

	glClear(GL_COLOR_BUFFER_BIT);

	_quadEntityColorRenderer.bind();

	_quadEntityColorRenderer.render(logo);

	_quadEntityColorRenderer.unbind();
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
		_renderBillboardEntities();
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
	_timer->startDeltaPart("billboardEntityRender");
	_renderBillboardEntities();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("aabbEntityRender");
	_renderAabbEntities();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("modelEntityRender");
	_renderModelEntities();
	_timer->stopDeltaPart();
	_renderBus->setTriangleCountingEnabled(false);

	_worldColorCaptor->unbind();
	_renderBus->setFinalSceneMap(_worldColorCaptor->getTexture(0));
	_renderBus->setPrimarySceneMap(_worldColorCaptor->getTexture(0));
	_renderBus->setSecondarySceneMap(_worldColorCaptor->getTexture(1));

	_timer->startDeltaPart("postProcessing");
	_captureAntiAliasing();
	_captureBloom();
	_captureDOF();
	_captureLensFlare();
	_captureMotionBlur();
	_timer->stopDeltaPart();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(_renderBus->isDebugRenderingEnabled())
	{
		glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
		_renderDebugScreens();
		glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);
	}
	else
	{
		glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
		_renderFinalSceneMap();
		glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);

	}

	_timer->startDeltaPart("guiEntityRender");
	_renderBus->setTriangleCountingEnabled(true);
	_renderGUI();
	_renderCursor();
	_renderBus->setTriangleCountingEnabled(false);
	_timer->stopDeltaPart();
}

void MasterRenderer::reloadBloomBlurCaptureBuffer()
{
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus->getBloomQuality());
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (_renderBus->getBloomQuality() * 2));
}

void MasterRenderer::reloadDofBlurCaptureBuffer()
{
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus->getDofQuality());
}

void MasterRenderer::reloadMotionBlurBlurCaptureBuffer()
{
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus->getMotionBlurQuality());
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
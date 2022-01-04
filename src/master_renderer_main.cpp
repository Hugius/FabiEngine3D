#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::make_shared;
using std::max;
using std::clamp;

MasterRenderer::MasterRenderer(RenderBus& renderBus)
	:
	_renderBus(renderBus),
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
	_quadEntityColorRenderer("quad_entity_color_shader.vert", "quad_entity_color_shader.frag", renderBus),
	_antiAliasingRenderer("anti_aliasing_shader.vert", "anti_aliasing_shader.frag", renderBus),
	_bloomRenderer("bloom_shader.vert", "bloom_shader.frag", renderBus),
	_dofRenderer("dof_shader.vert", "dof_shader.frag", renderBus),
	_lensFlareRenderer("lens_flare_shader.vert", "lens_flare_shader.frag", renderBus),
	_motionBlurRenderer("motion_blur_shader.vert", "motion_blur_shader.frag", renderBus),
	_bloomBlurRendererHighQuality("blur_shader.vert", "blur_shader.frag", renderBus),
	_bloomBlurRendererLowQuality("blur_shader.vert", "blur_shader.frag", renderBus),
	_dofBlurRenderer("blur_shader.vert", "blur_shader.frag", renderBus),
	_motionBlurBlurRenderer("blur_shader.vert", "blur_shader.frag", renderBus),
	_worldDepthCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize())),
	_worldColorCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 2, false)),
	_antiAliasingCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false)),
	_bloomCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false)),
	_dofCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false)),
	_lensFlareCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false)),
	_motionBlurCaptor(make_shared<CaptureBuffer>(ivec2(0), Config::getInst().getViewportSize(), 1, false)),
	_cubeReflectionCaptor(make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false)),
	_planarReflectionCaptor(make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false)),
	_waterReflectionCaptor(make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFLECTION_QUALITY), 1, false)),
	_waterRefractionCaptor(make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_REFRACTION_QUALITY), 1, false)),
	_shadowCaptor(make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_SHADOW_QUALITY)))
{
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_BLOOM_QUALITY);
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (Config::MIN_BLOOM_QUALITY * 2));
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_DOF_QUALITY);
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / Config::MIN_MOTION_BLUR_QUALITY);

	_renderQuad = make_shared<QuadEntity>("renderQuad");
	_renderQuad->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	_renderQuad->setCentered(true);
}

void MasterRenderer::update(Camera& camera)
{
	_updateMotionBlur(camera);
	_updateLensFlare();
}

void MasterRenderer::render(shared_ptr<QuadEntity> logo, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);

	_quadEntityColorRenderer.bind();

	_quadEntityColorRenderer.render(logo);

	_quadEntityColorRenderer.unbind();
}

void MasterRenderer::render(Camera& camera, ShadowGenerator& shadowGenerator, Timer& timer, EntityBus& entityBus)
{
	if(_renderBus.isWireframeRenderingEnabled())
	{
		glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderSkyEntity(entityBus);
		_renderTerrainEntity(entityBus);
		_renderWaterEntity(entityBus);
		_renderModelEntities(entityBus);
		_renderBillboardEntities(entityBus);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
		_renderGUI(entityBus);
		_renderCursor(entityBus);
	}
	else
	{
		timer.startDeltaPart("reflectionPreRender");
		_captureCubeReflections(shadowGenerator, camera, entityBus);
		_capturePlanarReflections(camera, entityBus);
		_captureWaterReflections(camera, entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("refractionPreRender");
		_captureWaterRefractions(camera, entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("depthPreRender");
		_captureWorldDepth(entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("shadowPreRender");
		_captureShadows(entityBus);
		timer.stopDeltaPart();

		_worldColorCaptor->bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderBus.setTriangleCountingEnabled(true);
		timer.startDeltaPart("skyEntityRender");
		_renderSkyEntity(entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("terrainEntityRender");
		_renderTerrainEntity(entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("waterEntityRender");
		_renderWaterEntity(entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("billboardEntityRender");
		_renderBillboardEntities(entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("aabbEntityRender");
		_renderAabbEntities(entityBus);
		timer.stopDeltaPart();
		timer.startDeltaPart("modelEntityRender");
		_renderModelEntities(entityBus);
		timer.stopDeltaPart();
		_renderBus.setTriangleCountingEnabled(false);

		_worldColorCaptor->unbind();
		_renderBus.setFinalSceneMap(_worldColorCaptor->getTexture(0));
		_renderBus.setPrimarySceneMap(_worldColorCaptor->getTexture(0));
		_renderBus.setSecondarySceneMap(_worldColorCaptor->getTexture(1));

		timer.startDeltaPart("postProcessing");
		_captureAntiAliasing();
		_captureBloom();
		_captureDOF();
		_captureLensFlare();
		_captureMotionBlur();
		timer.stopDeltaPart();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(_renderBus.isDebugRenderingEnabled())
		{
			glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y + 1);
			_renderDebugScreens();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
		}
		else
		{
			glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y + 0);
			_renderFinalSceneMap();
			glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);

		}

		timer.startDeltaPart("guiEntityRender");
		_renderBus.setTriangleCountingEnabled(true);
		_renderGUI(entityBus);
		_renderCursor(entityBus);
		_renderBus.setTriangleCountingEnabled(false);
		timer.stopDeltaPart();
	}
}

void MasterRenderer::reloadBloomBlurCaptureBuffer()
{
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus.getBloomQuality());
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (_renderBus.getBloomQuality() * 2));
}

void MasterRenderer::reloadDofBlurCaptureBuffer()
{
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus.getDofQuality());
}

void MasterRenderer::reloadMotionBlurBlurCaptureBuffer()
{
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / _renderBus.getMotionBlurQuality());
}

void MasterRenderer::reloadCubeReflectionCaptureBuffer()
{
	_cubeReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus.getCubeReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionCaptureBuffer()
{
	_planarReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus.getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionCaptureBuffer()
{
	_waterReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus.getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionCaptureBuffer()
{
	_waterRefractionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus.getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowCaptureBuffer()
{
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(_renderBus.getShadowQuality()));
}

void MasterRenderer::_updateMotionBlur(Camera& camera)
{
	if(_renderBus.isMotionBlurEnabled())
	{
		static auto lastYaw = camera.getYaw();
		static auto lastPitch = camera.getPitch();
		const auto currentYaw = camera.getYaw();
		const auto currentPitch = camera.getPitch();

		_cameraYawDifference = fabsf(Math::calculateReferenceAngle(currentYaw) - Math::calculateReferenceAngle(lastYaw));
		_cameraPitchDifference = fabsf(Math::calculateReferenceAngle(currentPitch) - Math::calculateReferenceAngle(lastPitch));

		lastYaw = camera.getYaw();
		lastPitch = camera.getPitch();
	}
}

void MasterRenderer::_updateLensFlare()
{
	if(_renderBus.isLensFlareEnabled())
	{
		auto flareSourcePosition = _renderBus.getDirectionalLightingPosition();
		auto viewMatrix = _renderBus.getViewMatrix();
		auto projectionMatrix = _renderBus.getProjectionMatrix();
		float transparency = 0.0f;

		fvec4 flareSourceClip = (projectionMatrix * viewMatrix * fvec4(flareSourcePosition.x, flareSourcePosition.y, flareSourcePosition.z, 1.0f));
		fvec2 flareSourceNdc = (fvec2(flareSourceClip.x, flareSourceClip.y) / flareSourceClip.w);
		fvec2 flareSourceUv = fvec2(((flareSourceNdc.x + 1.0f) / 2.0f), ((flareSourceNdc.y + 1.0f) / 2.0f));

		if((flareSourceNdc.x > -1.0f) && (flareSourceNdc.x < 1.0f) && (flareSourceNdc.y > -1.0f) && (flareSourceNdc.y < 1.0f))
		{
			transparency = (1.0f - (max(fabsf(flareSourceNdc.x), fabsf(flareSourceNdc.y)) / _renderBus.getLensFlareSensitivity()));
			transparency = clamp(transparency, 0.0f, 1.0f);
		}

		_renderBus.setLensFlareTransparency(transparency);
		_renderBus.setFlareSourcePosition(flareSourcePosition);
		_renderBus.setFlareSourceUv(flareSourceUv);
	}
}
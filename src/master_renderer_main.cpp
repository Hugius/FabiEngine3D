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

void MasterRenderer::update(RenderBus& renderBus, Camera& camera)
{
	_updateMotionBlur(renderBus, camera);
	_updateLensFlare(renderBus);
}

void MasterRenderer::render(RenderBus& renderBus, shared_ptr<QuadEntity> logo, ivec2 viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(GL_COLOR_BUFFER_BIT);

	_quadEntityColorRenderer.bind(_quadEntityColorShader, renderBus);

	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, logo);

	_quadEntityColorRenderer.unbind(_quadEntityColorShader);
}

void MasterRenderer::render(RenderBus& renderBus, Camera& camera, ShadowGenerator& shadowGenerator, Timer& timer, EntityBus& entityBus)
{
	const auto& config = Config::getInst();

	if(renderBus.isWireframeRenderingEnabled())
	{
		glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_renderSkyEntity(renderBus, entityBus);
		_renderTerrainEntity(renderBus, entityBus);
		_renderWaterEntity(renderBus, entityBus);
		_renderModelEntities(renderBus, entityBus);
		_renderBillboardEntities(renderBus, entityBus);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);
		_renderGUI(renderBus, entityBus);
		_renderCursor(renderBus, entityBus);
		return;
	}

	timer.startDeltaPart("reflectionPreRender");
	_captureCubeReflections(renderBus, shadowGenerator, camera, entityBus);
	_capturePlanarReflections(renderBus, camera, entityBus);
	_captureWaterReflections(renderBus, camera, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("refractionPreRender");
	_captureWaterRefractions(renderBus, camera, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("depthPreRender");
	_captureWorldDepth(renderBus, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("shadowPreRender");
	_captureShadows(renderBus, entityBus);
	timer.stopDeltaPart();

	_worldColorCaptor->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderBus.setTriangleCountingEnabled(true);
	timer.startDeltaPart("skyEntityRender");
	_renderSkyEntity(renderBus, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("terrainEntityRender");
	_renderTerrainEntity(renderBus, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("waterEntityRender");
	_renderWaterEntity(renderBus, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("billboardEntityRender");
	_renderBillboardEntities(renderBus, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("aabbEntityRender");
	_renderAabbEntities(renderBus, entityBus);
	timer.stopDeltaPart();
	timer.startDeltaPart("modelEntityRender");
	_renderModelEntities(renderBus, entityBus);
	timer.stopDeltaPart();
	renderBus.setTriangleCountingEnabled(false);

	_worldColorCaptor->unbind();
	renderBus.setFinalSceneMap(_worldColorCaptor->getTexture(0));
	renderBus.setPrimarySceneMap(_worldColorCaptor->getTexture(0));
	renderBus.setSecondarySceneMap(_worldColorCaptor->getTexture(1));

	timer.startDeltaPart("postProcessing");
	_captureAntiAliasing(renderBus);
	_captureBloom(renderBus);
	_captureDOF(renderBus);
	_captureLensFlare(renderBus);
	_captureMotionBlur(renderBus);
	timer.stopDeltaPart();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(renderBus.isDebugRenderingEnabled())
	{
		glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
		_renderDebugScreens(renderBus);
		glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);
	}
	else
	{
		glViewport(config.getViewportPosition().x, config.getViewportPosition().y, config.getViewportSize().x, config.getViewportSize().y);
		_renderFinalSceneMap(renderBus);
		glViewport(0, 0, config.getWindowSize().x, config.getWindowSize().y);

	}

	timer.startDeltaPart("guiEntityRender");
	renderBus.setTriangleCountingEnabled(true);
	_renderGUI(renderBus, entityBus);
	_renderCursor(renderBus, entityBus);
	renderBus.setTriangleCountingEnabled(false);
	timer.stopDeltaPart();
}

void MasterRenderer::reloadBloomBlurCaptureBuffer(RenderBus& renderBus)
{
	_bloomBlurRendererHighQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / renderBus.getBloomQuality());
	_bloomBlurRendererLowQuality.loadCaptureBuffer(Config::getInst().getViewportSize() / (renderBus.getBloomQuality() * 2));
}

void MasterRenderer::reloadDofBlurCaptureBuffer(RenderBus& renderBus)
{
	_dofBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / renderBus.getDofQuality());
}

void MasterRenderer::reloadMotionBlurBlurCaptureBuffer(RenderBus& renderBus)
{
	_motionBlurBlurRenderer.loadCaptureBuffer(Config::getInst().getViewportSize() / renderBus.getMotionBlurQuality());
}

void MasterRenderer::reloadCubeReflectionCaptureBuffer(RenderBus& renderBus)
{
	_cubeReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(renderBus.getCubeReflectionQuality()), 1, false);
}

void MasterRenderer::reloadPlanarReflectionCaptureBuffer(RenderBus& renderBus)
{
	_planarReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(renderBus.getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterReflectionCaptureBuffer(RenderBus& renderBus)
{
	_waterReflectionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(renderBus.getPlanarReflectionQuality()), 1, false);
}

void MasterRenderer::reloadWaterRefractionCaptureBuffer(RenderBus& renderBus)
{
	_waterRefractionCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(renderBus.getPlanarRefractionQuality()), 1, false);
}

void MasterRenderer::reloadShadowCaptureBuffer(RenderBus& renderBus)
{
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(renderBus.getShadowQuality()));
}

void MasterRenderer::_updateMotionBlur(RenderBus& renderBus, Camera& camera)
{
	if(renderBus.isMotionBlurEnabled())
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

void MasterRenderer::_updateLensFlare(RenderBus& renderBus)
{
	if(renderBus.isLensFlareEnabled())
	{
		auto flareSourcePosition = renderBus.getDirectionalLightingPosition();
		auto viewMatrix = renderBus.getViewMatrix();
		auto projectionMatrix = renderBus.getProjectionMatrix();
		float transparency = 0.0f;

		fvec4 flareSourceClip = (projectionMatrix * viewMatrix * fvec4(flareSourcePosition.x, flareSourcePosition.y, flareSourcePosition.z, 1.0f));
		fvec2 flareSourceNdc = (fvec2(flareSourceClip.x, flareSourceClip.y) / flareSourceClip.w);
		fvec2 flareSourceUv = fvec2(((flareSourceNdc.x + 1.0f) / 2.0f), ((flareSourceNdc.y + 1.0f) / 2.0f));

		if((flareSourceNdc.x > -1.0f) && (flareSourceNdc.x < 1.0f) && (flareSourceNdc.y > -1.0f) && (flareSourceNdc.y < 1.0f))
		{
			transparency = (1.0f - (max(fabsf(flareSourceNdc.x), fabsf(flareSourceNdc.y)) / renderBus.getLensFlareSensitivity()));
			transparency = clamp(transparency, 0.0f, 1.0f);
		}

		renderBus.setLensFlareTransparency(transparency);
		renderBus.setFlareSourcePosition(flareSourcePosition);
		renderBus.setFlareSourceUv(flareSourceUv);
	}
}
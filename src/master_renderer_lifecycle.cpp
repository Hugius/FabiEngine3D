#include "master_renderer.hpp"
#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"
#include "tools.hpp"
#include <algorithm>

using std::make_shared;
using std::min;
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
	_waterEntityDepthShader = make_shared<ShaderBuffer>("water_entity_depth_shader.vert", "water_entity_depth_shader.frag");
	_modelEntityColorShader = make_shared<ShaderBuffer>("model_entity_color_shader.vert", "model_entity_color_shader.frag");
	_modelEntityDepthShader = make_shared<ShaderBuffer>("model_entity_depth_shader.vert", "model_entity_depth_shader.frag");
	_modelEntityShadowShader = make_shared<ShaderBuffer>("model_entity_shadow_shader.vert", "model_entity_shadow_shader.frag");
	_quad3dEntityColorShader = make_shared<ShaderBuffer>("quad3d_entity_color_shader.vert", "quad3d_entity_color_shader.frag");
	_quad3dEntityDepthShader = make_shared<ShaderBuffer>("quad3d_entity_depth_shader.vert", "quad3d_entity_depth_shader.frag");
	_quad3dEntityShadowShader = make_shared<ShaderBuffer>("quad3d_entity_shadow_shader.vert", "quad3d_entity_shadow_shader.frag");
	_aabbEntityColorShader = make_shared<ShaderBuffer>("aabb_entity_color_shader.vert", "aabb_entity_color_shader.frag");
	_aabbEntityDepthShader = make_shared<ShaderBuffer>("aabb_entity_depth_shader.vert", "aabb_entity_depth_shader.frag");
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
	_waterOpacityCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize);
	_shadowCaptor = make_shared<CaptureBuffer>(ivec2(0), ivec2(Config::MIN_SHADOW_QUALITY));
	_bloomBlurCaptorHighQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / Config::MIN_BLOOM_QUALITY), 1, true);
	_bloomBlurCaptorLowQuality = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / (Config::MIN_BLOOM_QUALITY * 2)), 1, true);
	_dofBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / Config::MIN_DOF_QUALITY), 1, true);
	_motionBlurBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), (viewportSize / Config::MIN_MOTION_BLUR_QUALITY), 1, true);

	_skyEntityColorRenderer.inject(_skyEntityColorShader);
	_terrainEntityColorRenderer.inject(_terrainEntityColorShader);
	_terrainEntityDepthRenderer.inject(_terrainEntityDepthShader);
	_waterEntityColorRenderer.inject(_waterEntityColorShader);
	_waterEntityDepthRenderer.inject(_waterEntityDepthShader);
	_modelEntityColorRenderer.inject(_modelEntityColorShader);
	_modelEntityDepthRenderer.inject(_modelEntityDepthShader);
	_modelEntityShadowRenderer.inject(_modelEntityShadowShader);
	_quad3dEntityColorRenderer.inject(_quad3dEntityColorShader);
	_quad3dEntityDepthRenderer.inject(_quad3dEntityDepthShader);
	_quad3dEntityShadowRenderer.inject(_quad3dEntityShadowShader);
	_aabbEntityColorRenderer.inject(_aabbEntityColorShader);
	_aabbEntityDepthRenderer.inject(_aabbEntityDepthShader);
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

	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MasterRenderer::update()
{
	_updateSkyExposure();
	_updateShadows();
	_updateMotionBlur();
	_updateLensFlare();
}

void MasterRenderer::_updateSkyExposure()
{
	if(_renderBus->isSkyExposureEnabled())
	{
		const auto pitch = max(0.0f, _renderBus->getCameraPitch());
		const auto targetLightness = (((90.0f - pitch) / 90.0f) * _renderBus->getSkyExposureIntensity());
		auto lightness = _renderBus->getSkyExposureLightness();

		if(lightness > targetLightness)
		{
			lightness -= (_renderBus->getSkyExposureSpeed() * 2.0f);

			if(lightness < targetLightness)
			{
				lightness = targetLightness;
			}
		}
		if(lightness < targetLightness)
		{
			lightness += _renderBus->getSkyExposureSpeed();

			if(lightness > targetLightness)
			{
				lightness = targetLightness;
			}
		}

		_renderBus->setSkyExposureLightness(lightness);
	}
	else
	{
		_renderBus->setSkyExposureLightness(0.0f);
	}
}

void MasterRenderer::_updateShadows()
{
	if(_renderBus->isShadowsEnabled())
	{
		if((_renderBus->getShadowInterval() == 0) || (_timer->getPassedTickCount() % _renderBus->getShadowInterval()) == 0)
		{
			if(_renderBus->isShadowsFollowingCamera())
			{
				const auto cameraPosition = _renderBus->getCameraPosition();
				const auto eyeOffset = _renderBus->getShadowEyeOffset();
				const auto centerOffset = _renderBus->getShadowCenterOffset();

				_renderBus->setShadowEyePosition(fvec3((cameraPosition.x + eyeOffset.x), (cameraPosition.y + eyeOffset.y), (cameraPosition.z + eyeOffset.z)));
				_renderBus->setShadowCenterPosition(fvec3((cameraPosition.x + centerOffset.x), (cameraPosition.y + centerOffset.y), (cameraPosition.z + centerOffset.z)));
			}
			else
			{
				_renderBus->setShadowEyePosition(_renderBus->getShadowEyeOffset());
				_renderBus->setShadowCenterPosition(_renderBus->getShadowCenterOffset());
			}

			const auto leftX = -(_renderBus->getShadowSize() * 0.5f);
			const auto rightX = (_renderBus->getShadowSize() * 0.5f);
			const auto bottomY = -(_renderBus->getShadowSize() * 0.5f);
			const auto topY = (_renderBus->getShadowSize() * 0.5f);
			const auto nearZ = 0.01f;
			const auto farZ = Math::calculateDistance(fvec3(_renderBus->getShadowSize()), fvec3(0.0f));

			const auto viewMatrix = Math::createViewMatrix(_renderBus->getShadowEyePosition(), _renderBus->getShadowCenterPosition(), fvec3(0.0f, 1.0f, 0.0f));
			const auto projectionMatrix = Math::createOrthographicProjectionMatrix(leftX, rightX, bottomY, topY, nearZ, farZ);
			const auto shadowMatrix = (projectionMatrix * viewMatrix);

			_renderBus->setShadowMatrix(shadowMatrix);
		}
	}
}

void MasterRenderer::_updateMotionBlur()
{
	if(_renderBus->isMotionBlurEnabled())
	{
		static auto lastYaw = _camera->getYaw();
		static auto lastPitch = _camera->getPitch();

		fvec2 difference;
		difference.x = fabsf(Math::calculateReferenceAngle(_camera->getYaw()) - Math::calculateReferenceAngle(lastYaw));
		difference.y = fabsf(Math::calculateReferenceAngle(_camera->getPitch()) - Math::calculateReferenceAngle(lastPitch));
		_renderBus->setMotionBlurDifference(difference);

		lastYaw = _camera->getYaw();
		lastPitch = _camera->getPitch();
	}
}

void MasterRenderer::_updateLensFlare()
{
	if(_renderBus->isLensFlareEnabled())
	{
		const auto flareSourcePosition = _renderBus->getDirectionalLightingPosition();
		const auto flareSourceClip = (_renderBus->getProjectionMatrix() * _renderBus->getViewMatrix() * fvec4(flareSourcePosition.x, flareSourcePosition.y, flareSourcePosition.z, 1.0f));
		const auto flareSourceNdc = (fvec2(flareSourceClip.x, flareSourceClip.y) / flareSourceClip.w);
		const auto flareSourceUv = fvec2(((flareSourceNdc.x + 1.0f) * 0.5f), ((flareSourceNdc.y + 1.0f) * 0.5f));

		if(flareSourceClip.z < 1.0f)
		{
			return;
		}

		float opacity = 0.0f;
		if((flareSourceNdc.x > -1.0f) && (flareSourceNdc.x < 1.0f) && (flareSourceNdc.y > -1.0f) && (flareSourceNdc.y < 1.0f))
		{
			const auto distance = (Math::calculateDistance(flareSourceNdc, fvec2(0.0f)) / _renderBus->getLensFlareSensitivity());

			opacity = (1.0f - distance);
			opacity = clamp(opacity, 0.0f, 1.0f);
		}

		_renderBus->setLensFlareOpacity(opacity);
		_renderBus->setFlareSourcePosition(flareSourcePosition);
		_renderBus->setFlareSourceUv(flareSourceUv);
	}
}
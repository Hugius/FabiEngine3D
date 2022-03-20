#include "master_renderer.hpp"
#include "master_renderer.hpp"
#include "configuration.hpp"
#include "render_storage.hpp"
#include "tools.hpp"
#include <algorithm>

using std::make_unique;
using std::make_shared;
using std::min;
using std::max;
using std::clamp;

MasterRenderer::MasterRenderer()
{
	const auto viewportSize = Configuration::getInst().getDisplaySize();

	_skyEntityColorRenderer = make_unique<SkyEntityColorRenderer>();
	_terrainEntityColorRenderer = make_unique<TerrainEntityColorRenderer>();
	_terrainEntityDepthRenderer = make_unique<TerrainEntityDepthRenderer>();
	_waterEntityColorRenderer = make_unique<WaterEntityColorRenderer>();
	_waterEntityDepthRenderer = make_unique<WaterEntityDepthRenderer>();
	_modelEntityColorRenderer = make_unique<ModelEntityColorRenderer>();
	_modelEntityDepthRenderer = make_unique<ModelEntityDepthRenderer>();
	_modelEntityShadowRenderer = make_unique<ModelEntityShadowRenderer>();
	_quad3dEntityColorRenderer = make_unique<Quad3dEntityColorRenderer>();
	_quad3dEntityDepthRenderer = make_unique<Quad3dEntityDepthRenderer>();
	_quad3dEntityShadowRenderer = make_unique<Quad3dEntityShadowRenderer>();
	_quad2dEntityColorRenderer = make_unique<Quad2dEntityColorRenderer>();
	_antiAliasingRenderer = make_unique<AntiAliasingRenderer>();
	_aabbEntityColorRenderer = make_unique<AabbEntityColorRenderer>();
	_aabbEntityDepthRenderer = make_unique<AabbEntityDepthRenderer>();
	_bloomRenderer = make_unique<BloomRenderer>();
	_dofRenderer = make_unique<DofRenderer>();
	_lensFlareRenderer = make_unique<LensFlareRenderer>();
	_motionBlurRenderer = make_unique<MotionBlurRenderer>();
	_bloomBlurRendererHighQuality = make_unique<BlurRenderer>();
	_bloomBlurRendererLowQuality = make_unique<BlurRenderer>();
	_dofBlurRenderer = make_unique<BlurRenderer>();
	_motionBlurBlurRenderer = make_unique<BlurRenderer>();

	_renderSurface = make_shared<Quad2dEntity>("renderQuad");
	_renderSurface->setVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	_renderSurface->setCentered(true);

	_skyEntityColorShaderBuffer = make_shared<ShaderBuffer>("sky_entity_color_shader.vert", "sky_entity_color_shader.frag");
	_terrainEntityColorShaderBuffer = make_shared<ShaderBuffer>("terrain_entity_color_shader.vert", "terrain_entity_color_shader.frag");
	_terrainEntityDepthShaderBuffer = make_shared<ShaderBuffer>("terrain_entity_depth_shader.vert", "terrain_entity_depth_shader.frag");
	_waterEntityColorShaderBuffer = make_shared<ShaderBuffer>("water_entity_color_shader.vert", "water_entity_color_shader.frag");
	_waterEntityDepthShaderBuffer = make_shared<ShaderBuffer>("water_entity_depth_shader.vert", "water_entity_depth_shader.frag");
	_modelEntityColorShaderBuffer = make_shared<ShaderBuffer>("model_entity_color_shader.vert", "model_entity_color_shader.frag");
	_modelEntityDepthShaderBuffer = make_shared<ShaderBuffer>("model_entity_depth_shader.vert", "model_entity_depth_shader.frag");
	_modelEntityShadowShaderBuffer = make_shared<ShaderBuffer>("model_entity_shadow_shader.vert", "model_entity_shadow_shader.frag");
	_quad3dEntityColorShaderBuffer = make_shared<ShaderBuffer>("quad3d_entity_color_shader.vert", "quad3d_entity_color_shader.frag");
	_quad3dEntityDepthShaderBuffer = make_shared<ShaderBuffer>("quad3d_entity_depth_shader.vert", "quad3d_entity_depth_shader.frag");
	_quad3dEntityShadowShaderBuffer = make_shared<ShaderBuffer>("quad3d_entity_shadow_shader.vert", "quad3d_entity_shadow_shader.frag");
	_aabbEntityColorShaderBuffer = make_shared<ShaderBuffer>("aabb_entity_color_shader.vert", "aabb_entity_color_shader.frag");
	_aabbEntityDepthShaderBuffer = make_shared<ShaderBuffer>("aabb_entity_depth_shader.vert", "aabb_entity_depth_shader.frag");
	_quad2dEntityColorShaderBuffer = make_shared<ShaderBuffer>("quad2d_entity_color_shader.vert", "quad2d_entity_color_shader.frag");
	_antiAliasingShaderBuffer = make_shared<ShaderBuffer>("anti_aliasing_shader.vert", "anti_aliasing_shader.frag");
	_bloomShaderBuffer = make_shared<ShaderBuffer>("bloom_shader.vert", "bloom_shader.frag");
	_dofShaderBuffer = make_shared<ShaderBuffer>("dof_shader.vert", "dof_shader.frag");
	_lensFlareShaderBuffer = make_shared<ShaderBuffer>("lens_flare_shader.vert", "lens_flare_shader.frag");
	_motionBlurShaderBuffer = make_shared<ShaderBuffer>("motion_blur_shader.vert", "motion_blur_shader.frag");
	_blurShaderBuffer = make_shared<ShaderBuffer>("blur_shader.vert", "blur_shader.frag");

	_waterOpacityCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize);
	_worldDepthCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize);
	_worldColorCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 2, false);
	_antiAliasingCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_bloomCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_dofCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_lensFlareCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_motionBlurCaptureBuffer = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);

	_skyEntityColorRenderer->inject(_skyEntityColorShaderBuffer);
	_terrainEntityColorRenderer->inject(_terrainEntityColorShaderBuffer);
	_terrainEntityDepthRenderer->inject(_terrainEntityDepthShaderBuffer);
	_waterEntityColorRenderer->inject(_waterEntityColorShaderBuffer);
	_waterEntityDepthRenderer->inject(_waterEntityDepthShaderBuffer);
	_modelEntityColorRenderer->inject(_modelEntityColorShaderBuffer);
	_modelEntityDepthRenderer->inject(_modelEntityDepthShaderBuffer);
	_modelEntityShadowRenderer->inject(_modelEntityShadowShaderBuffer);
	_quad3dEntityColorRenderer->inject(_quad3dEntityColorShaderBuffer);
	_quad3dEntityDepthRenderer->inject(_quad3dEntityDepthShaderBuffer);
	_quad3dEntityShadowRenderer->inject(_quad3dEntityShadowShaderBuffer);
	_aabbEntityColorRenderer->inject(_aabbEntityColorShaderBuffer);
	_aabbEntityDepthRenderer->inject(_aabbEntityDepthShaderBuffer);
	_quad2dEntityColorRenderer->inject(_quad2dEntityColorShaderBuffer);
	_antiAliasingRenderer->inject(_antiAliasingShaderBuffer);
	_bloomRenderer->inject(_bloomShaderBuffer);
	_dofRenderer->inject(_dofShaderBuffer);
	_lensFlareRenderer->inject(_lensFlareShaderBuffer);
	_motionBlurRenderer->inject(_motionBlurShaderBuffer);
	_bloomBlurRendererHighQuality->inject(_blurShaderBuffer);
	_bloomBlurRendererHighQuality->inject(_bloomBlurHighQualityCaptureBuffer);
	_bloomBlurRendererLowQuality->inject(_blurShaderBuffer);
	_bloomBlurRendererLowQuality->inject(_bloomBlurLowQualityCaptureBuffer);
	_dofBlurRenderer->inject(_blurShaderBuffer);
	_dofBlurRenderer->inject(_dofBlurCaptureBuffer);
	_motionBlurBlurRenderer->inject(_blurShaderBuffer);
	_motionBlurBlurRenderer->inject(_motionBlurBlurCaptureBuffer);

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
	if(_renderStorage->isSkyExposureEnabled())
	{
		const auto pitch = max(0.0f, _camera->getPitch());
		const auto targetLightness = (((90.0f - pitch) / 90.0f) * _renderStorage->getSkyExposureIntensity());
		auto lightness = _renderStorage->getSkyExposureLightness();

		if(lightness > targetLightness)
		{
			lightness -= (_renderStorage->getSkyExposureSpeed() * 3.0f);

			if(lightness < targetLightness)
			{
				lightness = targetLightness;
			}
		}
		if(lightness < targetLightness)
		{
			lightness += _renderStorage->getSkyExposureSpeed();

			if(lightness > targetLightness)
			{
				lightness = targetLightness;
			}
		}

		_renderStorage->setSkyExposureLightness(lightness);
	}
}

void MasterRenderer::_updateShadows()
{
	if(_renderStorage->isShadowsEnabled())
	{
		if((_renderStorage->getShadowInterval() == 0) || (_timer->getPassedUpdateCount() % _renderStorage->getShadowInterval()) == 0)
		{
			if(_renderStorage->isShadowsFollowingCamera())
			{
				const auto cameraPosition = _camera->getPosition();
				const auto positionOffset = _renderStorage->getShadowPositionOffset();
				const auto lookatOffset = _renderStorage->getShadowLookatOffset();

				_renderStorage->setShadowPosition(fvec3((cameraPosition.x + positionOffset.x), (cameraPosition.y + positionOffset.y), (cameraPosition.z + positionOffset.z)));
				_renderStorage->setShadowLookat(fvec3((cameraPosition.x + lookatOffset.x), (cameraPosition.y + lookatOffset.y), (cameraPosition.z + lookatOffset.z)));
			}
			else
			{
				_renderStorage->setShadowPosition(_renderStorage->getShadowPositionOffset());
				_renderStorage->setShadowLookat(_renderStorage->getShadowLookatOffset());
			}

			const auto leftX = -(_renderStorage->getShadowSize() * 0.5f);
			const auto rightX = (_renderStorage->getShadowSize() * 0.5f);
			const auto bottomY = -(_renderStorage->getShadowSize() * 0.5f);
			const auto topY = (_renderStorage->getShadowSize() * 0.5f);
			const auto nearZ = 0.01f;
			const auto farZ = Math::calculateDistance(fvec3(_renderStorage->getShadowSize()), fvec3(0.0f));

			const auto viewMatrix = Math::createViewMatrix(_renderStorage->getShadowPosition(), _renderStorage->getShadowLookat(), fvec3(0.0f, 1.0f, 0.0f));
			const auto projectionMatrix = Math::createOrthographicProjectionMatrix(leftX, rightX, bottomY, topY, nearZ, farZ);

			_renderStorage->setShadowView(viewMatrix);
			_renderStorage->setShadowProjection(projectionMatrix);
		}
	}
}

void MasterRenderer::_updateMotionBlur()
{
	if(_renderStorage->isMotionBlurEnabled())
	{
		static auto lastYaw = _camera->getYaw();
		static auto lastPitch = _camera->getPitch();

		fvec2 difference;
		difference.x = fabsf(Math::calculateReferenceAngle(_camera->getYaw()) - Math::calculateReferenceAngle(lastYaw));
		difference.y = fabsf(Math::calculateReferenceAngle(_camera->getPitch()) - Math::calculateReferenceAngle(lastPitch));
		_renderStorage->setMotionBlurDifference(difference);

		lastYaw = _camera->getYaw();
		lastPitch = _camera->getPitch();
	}
}

void MasterRenderer::_updateLensFlare()
{
	if(_renderStorage->isLensFlareEnabled())
	{
		const auto flareSourcePosition = _renderStorage->getDirectionalLightingPosition();
		const auto flareSourceClip = (_camera->getProjection() * _camera->getView() * fvec4(flareSourcePosition.x, flareSourcePosition.y, flareSourcePosition.z, 1.0f));
		const auto flareSourceNdc = (fvec2(flareSourceClip.x, flareSourceClip.y) / flareSourceClip.w);
		const auto flareSourceUv = fvec2(((flareSourceNdc.x + 1.0f) * 0.5f), ((flareSourceNdc.y + 1.0f) * 0.5f));

		if(flareSourceClip.z < 1.0f)
		{
			return;
		}

		float opacity = 0.0f;
		if((flareSourceNdc.x > -1.0f) && (flareSourceNdc.x < 1.0f) && (flareSourceNdc.y > -1.0f) && (flareSourceNdc.y < 1.0f))
		{
			const auto distance = (Math::calculateDistance(flareSourceNdc, fvec2(0.0f)) / _renderStorage->getLensFlareSensitivity());

			opacity = (1.0f - distance);
			opacity = clamp(opacity, 0.0f, 1.0f);
		}

		_renderStorage->setLensFlareOpacity(opacity);
		_renderStorage->setFlareSourcePosition(flareSourcePosition);
		_renderStorage->setFlareSourceUv(flareSourceUv);
	}
}
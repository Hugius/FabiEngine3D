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

	_skyColorRenderer = make_unique<SkyColorRenderer>();
	_terrainColorRenderer = make_unique<TerrainColorRenderer>();
	_terrainDepthRenderer = make_unique<TerrainDepthRenderer>();
	_waterColorRenderer = make_unique<WaterColorRenderer>();
	_waterDepthRenderer = make_unique<WaterDepthRenderer>();
	_modelColorRenderer = make_unique<ModelColorRenderer>();
	_modelDepthRenderer = make_unique<ModelDepthRenderer>();
	_modelShadowRenderer = make_unique<ModelShadowRenderer>();
	_quad3dColorRenderer = make_unique<Quad3dColorRenderer>();
	_quad3dDepthRenderer = make_unique<Quad3dDepthRenderer>();
	_quad3dShadowRenderer = make_unique<Quad3dShadowRenderer>();
	_quad2dColorRenderer = make_unique<Quad2dColorRenderer>();
	_antiAliasingRenderer = make_unique<AntiAliasingRenderer>();
	_aabbColorRenderer = make_unique<AabbColorRenderer>();
	_aabbDepthRenderer = make_unique<AabbDepthRenderer>();
	_bloomRenderer = make_unique<BloomRenderer>();
	_dofRenderer = make_unique<DofRenderer>();
	_lensFlareRenderer = make_unique<LensFlareRenderer>();
	_motionBlurRenderer = make_unique<MotionBlurRenderer>();
	_bloomBlurRendererHighQuality = make_unique<BlurRenderer>();
	_bloomBlurRendererLowQuality = make_unique<BlurRenderer>();
	_dofBlurRenderer = make_unique<BlurRenderer>();
	_motionBlurBlurRenderer = make_unique<BlurRenderer>();

	_renderSurface = make_shared<Quad2d>("renderQuad");
	_renderSurface->setVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	_renderSurface->setCentered(true);

	_skyColorShaderBuffer = make_shared<ShaderBuffer>("sky_color_shader.vert", "sky_color_shader.frag");
	_terrainColorShaderBuffer = make_shared<ShaderBuffer>("terrain_color_shader.vert", "terrain_color_shader.frag");
	_terrainDepthShaderBuffer = make_shared<ShaderBuffer>("terrain_depth_shader.vert", "terrain_depth_shader.frag");
	_waterColorShaderBuffer = make_shared<ShaderBuffer>("water_color_shader.vert", "water_color_shader.frag");
	_waterDepthShaderBuffer = make_shared<ShaderBuffer>("water_depth_shader.vert", "water_depth_shader.frag");
	_modelColorShaderBuffer = make_shared<ShaderBuffer>("model_color_shader.vert", "model_color_shader.frag");
	_modelDepthShaderBuffer = make_shared<ShaderBuffer>("model_depth_shader.vert", "model_depth_shader.frag");
	_modelShadowShaderBuffer = make_shared<ShaderBuffer>("model_shadow_shader.vert", "model_shadow_shader.frag");
	_quad3dColorShaderBuffer = make_shared<ShaderBuffer>("quad3d_color_shader.vert", "quad3d_color_shader.frag");
	_quad3dDepthShaderBuffer = make_shared<ShaderBuffer>("quad3d_depth_shader.vert", "quad3d_depth_shader.frag");
	_quad3dShadowShaderBuffer = make_shared<ShaderBuffer>("quad3d_shadow_shader.vert", "quad3d_shadow_shader.frag");
	_aabbColorShaderBuffer = make_shared<ShaderBuffer>("aabb_color_shader.vert", "aabb_color_shader.frag");
	_aabbDepthShaderBuffer = make_shared<ShaderBuffer>("aabb_depth_shader.vert", "aabb_depth_shader.frag");
	_quad2dColorShaderBuffer = make_shared<ShaderBuffer>("quad2d_color_shader.vert", "quad2d_color_shader.frag");
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

	_skyColorRenderer->inject(_skyColorShaderBuffer);
	_terrainColorRenderer->inject(_terrainColorShaderBuffer);
	_terrainDepthRenderer->inject(_terrainDepthShaderBuffer);
	_waterColorRenderer->inject(_waterColorShaderBuffer);
	_waterDepthRenderer->inject(_waterDepthShaderBuffer);
	_modelColorRenderer->inject(_modelColorShaderBuffer);
	_modelDepthRenderer->inject(_modelDepthShaderBuffer);
	_modelShadowRenderer->inject(_modelShadowShaderBuffer);
	_quad3dColorRenderer->inject(_quad3dColorShaderBuffer);
	_quad3dDepthRenderer->inject(_quad3dDepthShaderBuffer);
	_quad3dShadowRenderer->inject(_quad3dShadowShaderBuffer);
	_aabbColorRenderer->inject(_aabbColorShaderBuffer);
	_aabbDepthRenderer->inject(_aabbDepthShaderBuffer);
	_quad2dColorRenderer->inject(_quad2dColorShaderBuffer);
	_antiAliasingRenderer->inject(_antiAliasingShaderBuffer);
	_bloomRenderer->inject(_bloomShaderBuffer);
	_dofRenderer->inject(_dofShaderBuffer);
	_lensFlareRenderer->inject(_lensFlareShaderBuffer);
	_motionBlurRenderer->inject(_motionBlurShaderBuffer);
	_bloomBlurRendererHighQuality->inject(_blurShaderBuffer);
	_bloomBlurRendererLowQuality->inject(_blurShaderBuffer);
	_dofBlurRenderer->inject(_blurShaderBuffer);
	_motionBlurBlurRenderer->inject(_blurShaderBuffer);

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
			const auto cameraPosition = _camera->getPosition();
			const auto positionOffset = _renderStorage->getShadowPositionOffset();
			const auto lookatOffset = _renderStorage->getShadowLookatOffset();

			auto position = positionOffset;
			auto lookat = lookatOffset;

			if(_renderStorage->isShadowsFollowingCameraX())
			{
				position.x += cameraPosition.x;
				lookat.x += cameraPosition.x;
			}
			if(_renderStorage->isShadowsFollowingCameraY())
			{
				position.y += cameraPosition.y;
				lookat.y += cameraPosition.y;
			}
			if(_renderStorage->isShadowsFollowingCameraZ())
			{
				position.z += cameraPosition.z;
				lookat.z += cameraPosition.z;
			}

			_renderStorage->setShadowPosition(position);
			_renderStorage->setShadowLookat(lookat);

			const auto leftX = -(_renderStorage->getShadowSize() * 0.5f);
			const auto rightX = (_renderStorage->getShadowSize() * 0.5f);
			const auto bottomY = -(_renderStorage->getShadowSize() * 0.5f);
			const auto topY = (_renderStorage->getShadowSize() * 0.5f);
			const auto nearZ = 0.01f;
			const auto farZ = Mathematics::calculateDistance(fvec3(_renderStorage->getShadowSize()), fvec3(0.0f));

			const auto viewMatrix = Mathematics::createViewMatrix(_renderStorage->getShadowPosition(), _renderStorage->getShadowLookat(), fvec3(0.0f, 1.0f, 0.0f));
			const auto projectionMatrix = Mathematics::createOrthographicProjectionMatrix(leftX, rightX, bottomY, topY, nearZ, farZ);

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
		difference.x = fabsf(Mathematics::calculateReferenceAngle(_camera->getYaw()) - Mathematics::calculateReferenceAngle(lastYaw));
		difference.y = fabsf(Mathematics::calculateReferenceAngle(_camera->getPitch()) - Mathematics::calculateReferenceAngle(lastPitch));
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
			const auto distance = (Mathematics::calculateDistance(flareSourceNdc, fvec2(0.0f)) / _renderStorage->getLensFlareSensitivity());

			opacity = (1.0f - distance);
			opacity = clamp(opacity, 0.0f, 1.0f);
		}

		_renderStorage->setLensFlareOpacity(opacity);
		_renderStorage->setFlareSourcePosition(flareSourcePosition);
		_renderStorage->setFlareSourceUv(flareSourceUv);
	}
}
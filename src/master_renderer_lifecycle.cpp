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
	const auto viewportSize = Config::getInst().getViewportSize();

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

	_waterOpacityCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize);
	_worldDepthCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize);
	_worldColorCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 2, false);
	_antiAliasingCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_bloomCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_dofCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_lensFlareCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);
	_motionBlurCaptor = make_shared<CaptureBuffer>(ivec2(0), viewportSize, 1, false);

	_skyEntityColorRenderer->inject(_skyEntityColorShader);
	_terrainEntityColorRenderer->inject(_terrainEntityColorShader);
	_terrainEntityDepthRenderer->inject(_terrainEntityDepthShader);
	_waterEntityColorRenderer->inject(_waterEntityColorShader);
	_waterEntityDepthRenderer->inject(_waterEntityDepthShader);
	_modelEntityColorRenderer->inject(_modelEntityColorShader);
	_modelEntityDepthRenderer->inject(_modelEntityDepthShader);
	_modelEntityShadowRenderer->inject(_modelEntityShadowShader);
	_quad3dEntityColorRenderer->inject(_quad3dEntityColorShader);
	_quad3dEntityDepthRenderer->inject(_quad3dEntityDepthShader);
	_quad3dEntityShadowRenderer->inject(_quad3dEntityShadowShader);
	_aabbEntityColorRenderer->inject(_aabbEntityColorShader);
	_aabbEntityDepthRenderer->inject(_aabbEntityDepthShader);
	_quad2dEntityColorRenderer->inject(_quad2dEntityColorShader);
	_antiAliasingRenderer->inject(_antiAliasingShader);
	_bloomRenderer->inject(_bloomShader);
	_dofRenderer->inject(_dofShader);
	_lensFlareRenderer->inject(_lensFlareShader);
	_motionBlurRenderer->inject(_motionBlurShader);
	_bloomBlurRendererHighQuality->inject(_blurShader);
	_bloomBlurRendererHighQuality->inject(_bloomBlurCaptorHighQuality);
	_bloomBlurRendererLowQuality->inject(_blurShader);
	_bloomBlurRendererLowQuality->inject(_bloomBlurCaptorLowQuality);
	_dofBlurRenderer->inject(_blurShader);
	_dofBlurRenderer->inject(_dofBlurCaptor);
	_motionBlurBlurRenderer->inject(_blurShader);
	_motionBlurBlurRenderer->inject(_motionBlurBlurCaptor);

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
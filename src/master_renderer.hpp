#pragma once

#include "sky_color_renderer.hpp"
#include "terrain_color_renderer.hpp"
#include "terrain_depth_renderer.hpp"
#include "water_color_renderer.hpp"
#include "water_depth_renderer.hpp"
#include "model_color_renderer.hpp"
#include "model_depth_renderer.hpp"
#include "model_shadow_renderer.hpp"
#include "quad3d_color_renderer.hpp"
#include "quad3d_depth_renderer.hpp"
#include "quad3d_shadow_renderer.hpp"
#include "aabb_color_renderer.hpp"
#include "quad2d_color_renderer.hpp"
#include "anti_aliasing_renderer.hpp"
#include "bloom_renderer.hpp"
#include "dof_renderer.hpp"
#include "lens_flare_renderer.hpp"
#include "motion_blur_renderer.hpp"
#include "blur_renderer.hpp"
#include "timer.hpp"
#include "camera.hpp"
#include "sky_manager.hpp"
#include "terrain_manager.hpp"
#include "water_manager.hpp"
#include "model_manager.hpp"
#include "quad3d_manager.hpp"
#include "text3d_manager.hpp"
#include "aabb_manager.hpp"
#include "pointlight_manager.hpp"
#include "spotlight_manager.hpp"
#include "captor_manager.hpp"
#include "quad2d_manager.hpp"
#include "text2d_manager.hpp"
#include "aabb_depth_renderer.hpp"

using std::unique_ptr;

class MasterRenderer final
{
public:
	MasterRenderer();

	void inject(shared_ptr<SkyManager> skyManager);
	void inject(shared_ptr<TerrainManager> terrainManager);
	void inject(shared_ptr<WaterManager> waterManager);
	void inject(shared_ptr<ModelManager> modelManager);
	void inject(shared_ptr<Quad3dManager> quad3dManager);
	void inject(shared_ptr<Text3dManager> text3dManager);
	void inject(shared_ptr<Quad2dManager> quad2dManager);
	void inject(shared_ptr<Text2dManager> text2dManager);
	void inject(shared_ptr<AabbManager> aabbManager);
	void inject(shared_ptr<PointlightManager> pointlightManager);
	void inject(shared_ptr<SpotlightManager> spotlightManager);
	void inject(shared_ptr<CaptorManager> captorManager);
	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void inject(shared_ptr<Timer> timer);
	void update();
	void renderLogo(shared_ptr<Quad2d> quad, const ivec2 & size);
	void render3d();
	void render2d();
	void reloadBloomBlurQuality();
	void reloadDofBlurQuality();
	void reloadMotionBlurBlurQuality();
	void reloadCubeReflectionQuality();
	void reloadPlanarReflectionQuality();
	void reloadWaterReflectionQuality();
	void reloadWaterRefractionQuality();
	void reloadShadowQuality();
	void setBackgroundColor(const fvec3 & color);
	void captureCubeReflections();
	void capturePlanarReflections();
	void captureWaterReflections();
	void captureWaterRefractions();
	void captureWaterEdges();
	void captureWorldDepth();
	void captureShadows();
	void captureAntiAliasing();
	void captureBloom();
	void captureDof();
	void captureLensFlare();
	void captureMotionBlur();

	const string getCpuName() const;
	const string getGpuName() const;
	const string getOpenglVersion() const;

private:
	void _updateSkyExposure();
	void _updateShadows();
	void _updateMotionBlur();
	void _updateLensFlare();
	void _renderSky();
	void _renderTerrain();
	void _renderWater();
	void _renderOpaqueModels();
	void _renderTransparentModels();
	void _renderOpaqueQuad3ds();
	void _renderTransparentQuad3ds();
	void _renderOpaqueText3ds();
	void _renderTransparentText3ds();
	void _renderAabbs();
	void _renderFinalScene();
	void _renderGUI();

	shared_ptr<Quad2d> _renderSurface = nullptr;
	shared_ptr<ShaderBuffer> _skyColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _terrainColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _terrainDepthShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _waterColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _waterDepthShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _modelColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _modelDepthShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _modelShadowShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _quad3dColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _quad3dDepthShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _quad3dShadowShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _quad2dColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _aabbColorShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _aabbDepthShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _antiAliasingShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _bloomShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _dofShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _lensFlareShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _motionBlurShaderBuffer = nullptr;
	shared_ptr<ShaderBuffer> _blurShaderBuffer = nullptr;
	shared_ptr<CaptureBuffer> _cubeReflectionCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _planarReflectionCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _waterReflectionCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _waterRefractionCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _waterOpacityCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _shadowCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _worldDepthCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _worldColorCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _antiAliasingCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _bloomCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _dofCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _lensFlareCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _motionBlurCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _bloomBlurHighQualityCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _bloomBlurLowQualityCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _dofBlurCaptureBuffer = nullptr;
	shared_ptr<CaptureBuffer> _motionBlurBlurCaptureBuffer = nullptr;
	shared_ptr<SkyManager> _skyManager = nullptr;
	shared_ptr<TerrainManager> _terrainManager = nullptr;
	shared_ptr<WaterManager> _waterManager = nullptr;
	shared_ptr<ModelManager> _modelManager = nullptr;
	shared_ptr<Quad3dManager> _quad3dManager = nullptr;
	shared_ptr<Text3dManager> _text3dManager = nullptr;
	shared_ptr<Quad2dManager> _quad2dManager = nullptr;
	shared_ptr<Text2dManager> _text2dManager = nullptr;
	shared_ptr<AabbManager> _aabbManager = nullptr;
	shared_ptr<PointlightManager> _pointlightManager = nullptr;
	shared_ptr<SpotlightManager> _spotlightManager = nullptr;
	shared_ptr<CaptorManager> _captorManager = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<Timer> _timer = nullptr;

	unique_ptr<SkyColorRenderer> _skyColorRenderer = nullptr;
	unique_ptr<TerrainColorRenderer> _terrainColorRenderer = nullptr;
	unique_ptr<TerrainDepthRenderer> _terrainDepthRenderer = nullptr;
	unique_ptr<WaterColorRenderer> _waterColorRenderer = nullptr;
	unique_ptr<WaterDepthRenderer> _waterDepthRenderer = nullptr;
	unique_ptr<ModelColorRenderer> _modelColorRenderer = nullptr;
	unique_ptr<ModelDepthRenderer> _modelDepthRenderer = nullptr;
	unique_ptr<ModelShadowRenderer> _modelShadowRenderer = nullptr;
	unique_ptr<Quad3dColorRenderer> _quad3dColorRenderer = nullptr;
	unique_ptr<Quad3dDepthRenderer> _quad3dDepthRenderer = nullptr;
	unique_ptr<Quad3dShadowRenderer> _quad3dShadowRenderer = nullptr;
	unique_ptr<Quad2dColorRenderer> _quad2dColorRenderer = nullptr;
	unique_ptr<AntiAliasingRenderer> _antiAliasingRenderer = nullptr;
	unique_ptr<AabbColorRenderer> _aabbColorRenderer = nullptr;
	unique_ptr<AabbDepthRenderer> _aabbDepthRenderer = nullptr;
	unique_ptr<BloomRenderer> _bloomRenderer = nullptr;
	unique_ptr<DofRenderer> _dofRenderer = nullptr;
	unique_ptr<LensFlareRenderer> _lensFlareRenderer = nullptr;
	unique_ptr<MotionBlurRenderer> _motionBlurRenderer = nullptr;
	unique_ptr<BlurRenderer> _bloomBlurRendererHighQuality = nullptr;
	unique_ptr<BlurRenderer> _bloomBlurRendererLowQuality = nullptr;
	unique_ptr<BlurRenderer> _dofBlurRenderer = nullptr;
	unique_ptr<BlurRenderer> _motionBlurBlurRenderer = nullptr;
};
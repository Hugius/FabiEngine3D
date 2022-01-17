#pragma once

#include "sky_entity_color_renderer.hpp"
#include "terrain_entity_color_renderer.hpp"
#include "terrain_entity_depth_renderer.hpp"
#include "water_entity_color_renderer.hpp"
#include "model_entity_color_renderer.hpp"
#include "model_entity_depth_renderer.hpp"
#include "model_entity_shadow_renderer.hpp"
#include "billboard_entity_color_renderer.hpp"
#include "billboard_entity_depth_renderer.hpp"
#include "billboard_entity_shadow_renderer.hpp"
#include "aabb_entity_color_renderer.hpp"
#include "quad2d_entity_color_renderer.hpp"
#include "anti_aliasing_renderer.hpp"
#include "bloom_renderer.hpp"
#include "dof_renderer.hpp"
#include "lens_flare_renderer.hpp"
#include "motion_blur_renderer.hpp"
#include "blur_renderer.hpp"
#include "timer.hpp"
#include "camera.hpp"
#include "shadow_generator.hpp"
#include "sky_entity_manager.hpp"
#include "terrain_entity_manager.hpp"
#include "water_entity_manager.hpp"
#include "model_entity_manager.hpp"
#include "billboard_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "pointlight_entity_manager.hpp"
#include "spotlight_entity_manager.hpp"
#include "reflection_entity_manager.hpp"
#include "quad2d_entity_manager.hpp"
#include "text2d_entity_manager.hpp"

class MasterRenderer final
{
public:
	MasterRenderer();

	void inject(shared_ptr<SkyEntityManager> skyEntityManager);
	void inject(shared_ptr<TerrainEntityManager> terrainEntityManager);
	void inject(shared_ptr<WaterEntityManager> waterEntityManager);
	void inject(shared_ptr<ModelEntityManager> modelEntityManager);
	void inject(shared_ptr<Quad3dEntityManager> quad3dEntityManager);
	void inject(shared_ptr<AabbEntityManager> aabbEntityManager);
	void inject(shared_ptr<Quad2dEntityManager> quad2dEntityManager);
	void inject(shared_ptr<Text2dEntityManager> text2dEntityManager);
	void inject(shared_ptr<PointlightEntityManager> pointlightEntityManager);
	void inject(shared_ptr<SpotlightEntityManager> spotlightEntityManager);
	void inject(shared_ptr<ReflectionEntityManager> reflectionEntityManager);
	void inject(shared_ptr<RenderBus> renderBus);
	void inject(shared_ptr<Camera> camera);
	void inject(shared_ptr<ShadowGenerator> shadowGenerator);
	void inject(shared_ptr<Timer> timer);
	void update();
	void renderLogo(shared_ptr<Quad2dEntity> logo, ivec2 viewport);
	void renderApplication();
	void reloadBloomBlurCaptureBuffer();
	void reloadDofBlurCaptureBuffer();
	void reloadMotionBlurBlurCaptureBuffer();
	void reloadCubeReflectionCaptureBuffer();
	void reloadPlanarReflectionCaptureBuffer();
	void reloadWaterReflectionCaptureBuffer();
	void reloadWaterRefractionCaptureBuffer();
	void reloadShadowCaptureBuffer();
	void setBackgroundColor(fvec3 color);

	const string getCpuName() const;
	const string getGpuName() const;
	const string getOpenglVersion() const;

private:
	void _updateMotionBlur();
	void _updateLensFlare();
	void _captureCubeReflections();
	void _capturePlanarReflections();
	void _captureWaterReflections();
	void _captureWaterRefractions();
	void _captureWorldDepth();
	void _captureShadows();
	void _captureAntiAliasing();
	void _captureBloom();
	void _captureDOF();
	void _captureLensFlare();
	void _captureMotionBlur();
	void _renderSkyEntity();
	void _renderTerrainEntity();
	void _renderWaterEntity();
	void _renderModelEntities();
	void _renderQuad3dEntities();
	void _renderAabbEntities();
	void _renderFinalSceneMap();
	void _renderGUI();
	void _renderCursor();

	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;

	SkyEntityColorRenderer _skyEntityColorRenderer;
	TerrainEntityColorRenderer _terrainEntityColorRenderer;
	TerrainEntityDepthRenderer _terrainEntityDepthRenderer;
	WaterEntityColorRenderer _waterEntityColorRenderer;
	ModelEntityColorRenderer _modelEntityColorRenderer;
	ModelEntityDepthRenderer _modelEntityDepthRenderer;
	ModelEntityShadowRenderer _modelEntityShadowRenderer;
	Quad3dEntityColorRenderer _quad3dEntityColorRenderer;
	Quad3dEntityDepthRenderer _quad3dEntityDepthRenderer;
	Quad3dEntityShadowRenderer _quad3dEntityShadowRenderer;
	AabbEntityColorRenderer _aabbEntityColorRenderer;
	Quad2dEntityColorRenderer _quad2dEntityColorRenderer;
	AntiAliasingRenderer _antiAliasingRenderer;
	BloomRenderer _bloomRenderer;
	DofRenderer _dofRenderer;
	LensFlareRenderer _lensFlareRenderer;
	MotionBlurRenderer _motionBlurRenderer;
	BlurRenderer _bloomBlurRendererHighQuality;
	BlurRenderer _bloomBlurRendererLowQuality;
	BlurRenderer _dofBlurRenderer;
	BlurRenderer _motionBlurBlurRenderer;

	shared_ptr<Quad2dEntity> _renderSurface = nullptr;

	shared_ptr<ShaderBuffer> _skyEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _terrainEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _terrainEntityDepthShader = nullptr;
	shared_ptr<ShaderBuffer> _waterEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _modelEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _modelEntityDepthShader = nullptr;
	shared_ptr<ShaderBuffer> _modelEntityShadowShader = nullptr;
	shared_ptr<ShaderBuffer> _quad3dEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _quad3dEntityDepthShader = nullptr;
	shared_ptr<ShaderBuffer> _quad3dEntityShadowShader = nullptr;
	shared_ptr<ShaderBuffer> _aabbEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _quad2dEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _antiAliasingShader = nullptr;
	shared_ptr<ShaderBuffer> _bloomShader = nullptr;
	shared_ptr<ShaderBuffer> _dofShader = nullptr;
	shared_ptr<ShaderBuffer> _lensFlareShader = nullptr;
	shared_ptr<ShaderBuffer> _motionBlurShader = nullptr;
	shared_ptr<ShaderBuffer> _blurShader = nullptr;

	shared_ptr<CaptureBuffer> _cubeReflectionCaptor = nullptr;
	shared_ptr<CaptureBuffer> _planarReflectionCaptor = nullptr;
	shared_ptr<CaptureBuffer> _waterReflectionCaptor = nullptr;
	shared_ptr<CaptureBuffer> _waterRefractionCaptor = nullptr;
	shared_ptr<CaptureBuffer> _shadowCaptor = nullptr;
	shared_ptr<CaptureBuffer> _worldDepthCaptor = nullptr;
	shared_ptr<CaptureBuffer> _worldColorCaptor = nullptr;
	shared_ptr<CaptureBuffer> _antiAliasingCaptor = nullptr;
	shared_ptr<CaptureBuffer> _bloomCaptor = nullptr;
	shared_ptr<CaptureBuffer> _dofCaptor = nullptr;
	shared_ptr<CaptureBuffer> _lensFlareCaptor = nullptr;
	shared_ptr<CaptureBuffer> _motionBlurCaptor = nullptr;
	shared_ptr<CaptureBuffer> _bloomBlurCaptorHighQuality = nullptr;
	shared_ptr<CaptureBuffer> _bloomBlurCaptorLowQuality = nullptr;
	shared_ptr<CaptureBuffer> _dofBlurCaptor = nullptr;
	shared_ptr<CaptureBuffer> _motionBlurBlurCaptor = nullptr;

	shared_ptr<SkyEntityManager> _skyEntityManager = nullptr;
	shared_ptr<TerrainEntityManager> _terrainEntityManager = nullptr;
	shared_ptr<WaterEntityManager> _waterEntityManager = nullptr;
	shared_ptr<ModelEntityManager> _modelEntityManager = nullptr;
	shared_ptr<Quad3dEntityManager> _quad3dEntityManager = nullptr;
	shared_ptr<AabbEntityManager> _aabbEntityManager = nullptr;
	shared_ptr<Quad2dEntityManager> _quad2dEntityManager = nullptr;
	shared_ptr<Text2dEntityManager> _text2dEntityManager = nullptr;
	shared_ptr<PointlightEntityManager> _pointlightEntityManager = nullptr;
	shared_ptr<SpotlightEntityManager> _spotlightEntityManager = nullptr;
	shared_ptr<ReflectionEntityManager> _reflectionEntityManager = nullptr;
	shared_ptr<RenderBus> _renderBus = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<ShadowGenerator> _shadowGenerator = nullptr;
	shared_ptr<Timer> _timer = nullptr;
};
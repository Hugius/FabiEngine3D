#pragma once

#include "capture_buffer.hpp"
#include "camera.hpp"
#include "entity_bus.hpp"
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
#include "image_entity_color_renderer.hpp"
#include "anti_aliasing_renderer.hpp"
#include "bloom_renderer.hpp"
#include "dof_renderer.hpp"
#include "lens_flare_renderer.hpp"
#include "motion_blur_renderer.hpp"
#include "blur_renderer.hpp"
#include "timer.hpp"
#include "texture_loader.hpp"
#include "shadow_generator.hpp"

class MasterRenderer final
{
public:
	MasterRenderer(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader, Camera& camera, ShadowGenerator& shadowGenerator);

	// VOID
	void update();
	void renderEngineLogo(shared_ptr<ImageEntity> entity, shared_ptr<TextEntity> text, ivec2 viewport);
	void renderWorld(EntityBus* entityBus);
	void reloadBloomBlurCaptureBuffer();
	void reloadDofBlurCaptureBuffer();
	void reloadMotionBlurBlurCaptureBuffer();
	void reloadCubeReflectionCaptureBuffer();
	void reloadPlanarReflectionCaptureBuffer();
	void reloadWaterReflectionCaptureBuffer();
	void reloadWaterRefractionCaptureBuffer();
	void reloadShadowCaptureBuffer();

private:
	// VOID
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
	void _renderBillboardEntities();
	void _renderAabbEntities();
	void _renderFinalWorldImage();
	void _renderGUI();
	void _renderCustomCursor();
	void _renderDebugScreens();

	// FLOAT
	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;

	// Miscellaneous
	Camera& _camera;
	Timer& _timer;
	RenderBus& _renderBus;
	TextureLoader& _textureLoader;
	ShadowGenerator& _shadowGenerator;
	SkyEntityColorRenderer _skyEntityColorRenderer;
	TerrainEntityColorRenderer _terrainEntityColorRenderer;
	TerrainEntityDepthRenderer _terrainEntityDepthRenderer;
	WaterEntityColorRenderer _waterEntityColorRenderer;
	ModelEntityColorRenderer _modelEntityColorRenderer;
	ModelEntityDepthRenderer _modelEntityDepthRenderer;
	ModelEntityShadowRenderer _modelEntityShadowRenderer;
	BillboardEntityColorRenderer _billboardEntityColorRenderer;
	BillboardEntityDepthRenderer _billboardEntityDepthRenderer;
	BillboardEntityShadowRenderer _billboardEntityShadowRenderer;
	AabbEntityColorRenderer _aabbEntityColorRenderer;
	ImageEntityColorRenderer _imageEntityColorRenderer;
	AntiAliasingRenderer _antiAliasingRenderer;
	BloomRenderer _bloomRenderer;
	DofRenderer _dofRenderer;
	LensFlareRenderer _lensFlareRenderer;
	MotionBlurRenderer _motionBlurRenderer;
	BlurRenderer _bloomBlurRendererHighQuality;
	BlurRenderer _bloomBlurRendererLowQuality;
	BlurRenderer _dofBlurRenderer;
	BlurRenderer _motionBlurBlurRenderer;
	CaptureBuffer _cubeReflectionCaptureBuffer;
	CaptureBuffer _planarReflectionCaptureBuffer;
	CaptureBuffer _waterReflectionCaptureBuffer;
	CaptureBuffer _waterRefractionCaptureBuffer;
	CaptureBuffer _shadowCaptureBuffer;
	CaptureBuffer _worldDepthCaptureBuffer;
	CaptureBuffer _worldColorCaptureBuffer;
	CaptureBuffer _antiAliasingCaptureBuffer;
	CaptureBuffer _bloomCaptureBuffer;
	CaptureBuffer _dofCaptureBuffer;
	CaptureBuffer _lensFlareCaptureBuffer;
	CaptureBuffer _motionBlurCaptureBuffer;
	shared_ptr<ImageEntity> _renderSurface = nullptr;
	EntityBus* _entityBus = nullptr;
};
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
#include "blur_type.hpp"
#include "texture_loader.hpp"

class MasterRenderer final
{
public:
	MasterRenderer(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader, Camera& camera);

	// Voids
	void update();
	void renderEngineLogo(shared_ptr<ImageEntity> entity, shared_ptr<TextEntity> text, Ivec2 viewport);
	void renderScene(EntityBus* entityBus);
	void reloadShadowCaptureBuffer();
	void reloadSceneReflectionCaptureBuffer();
	void reloadWaterReflectionCaptureBuffer();
	void reloadWaterRefractionCaptureBuffer();

private:
	// Update functions
	void _updateMotionBlur();
	void _updateLensFlare();

	// Pre-capturing functions
	void _captureEnvironmentReflections();
	void _captureSceneReflections();
	void _captureWaterReflections();
	void _captureWaterRefractions();
	void _captureSceneDepth();
	void _captureShadows();

	// Post-capturing functions
	void _captureAntiAliasing();
	void _captureBloom();
	void _captureDOF();
	void _captureLensFlare();
	void _captureMotionBlur();

	// Rendering functions
	void _renderSkyEntity();
	void _renderTerrainEntity();
	void _renderWaterEntity();
	void _renderModelEntities();
	void _renderBillboardEntities();
	void _renderAabbEntities();
	void _renderFinalSceneImage();
	void _renderGUI();
	void _renderCustomCursor();
	void _renderDebugScreens();

	// Instances
	Camera& _camera;
	Timer& _timer;
	RenderBus& _renderBus;
	TextureLoader& _textureLoader;
	EntityBus* _entityBus = nullptr;

	// Renderers
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
	BlurRenderer _dofBlurRenderer;
	BlurRenderer _motionBlurBlurRenderer;
	BlurRenderer _bloomBlurRendererHighQuality;
	BlurRenderer _bloomBlurRendererLowQuality;
	
	// CaptureBuffers
	CaptureBuffer _sceneReflectionCaptureBuffer;
	CaptureBuffer _waterReflectionCaptureBuffer;
	CaptureBuffer _waterRefractionCaptureBuffer;
	CaptureBuffer _shadowCaptureBuffer;
	CaptureBuffer _sceneDepthCaptureBuffer;
	CaptureBuffer _sceneColorCaptureBuffer;
	CaptureBuffer _antiAliasingCaptureBuffer;
	CaptureBuffer _bloomCaptureBuffer;
	CaptureBuffer _dofCaptureBuffer;
	CaptureBuffer _lensFlareCaptureBuffer;
	CaptureBuffer _motionBlurCaptureBuffer;

	// Surfaces
	shared_ptr<ImageEntity> _renderSurface = nullptr;

	// Miscellaneous
	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;
};
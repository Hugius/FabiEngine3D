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
#include "quad_entity_color_renderer.hpp"
#include "anti_aliasing_renderer.hpp"
#include "bloom_renderer.hpp"
#include "dof_renderer.hpp"
#include "lens_flare_renderer.hpp"
#include "motion_blur_renderer.hpp"
#include "blur_renderer.hpp"
#include "timer.hpp"
#include "image_loader.hpp"
#include "shadow_generator.hpp"

class MasterRenderer final
{
public:
	MasterRenderer(RenderBus& renderBus);

	void update(Camera& camera);
	void render(shared_ptr<QuadEntity> entity, ivec2 viewport);
	void render(Camera& camera, ShadowGenerator& shadowGenerator, Timer& timer, EntityBus& entityBus);
	void reloadBloomBlurCaptureBuffer();
	void reloadDofBlurCaptureBuffer();
	void reloadMotionBlurBlurCaptureBuffer();
	void reloadCubeReflectionCaptureBuffer();
	void reloadPlanarReflectionCaptureBuffer();
	void reloadWaterReflectionCaptureBuffer();
	void reloadWaterRefractionCaptureBuffer();
	void reloadShadowCaptureBuffer();

private:
	void _updateMotionBlur(Camera& camera);
	void _updateLensFlare();
	void _captureCubeReflections(ShadowGenerator& shadowGenerator, Camera& camera, EntityBus& entityBus);
	void _capturePlanarReflections(Camera& camera, EntityBus& entityBus);
	void _captureWaterReflections(Camera& camera, EntityBus& entityBus);
	void _captureWaterRefractions(Camera& camera, EntityBus& entityBus);
	void _captureWorldDepth(EntityBus& entityBus);
	void _captureShadows(EntityBus& entityBus);
	void _captureAntiAliasing();
	void _captureBloom();
	void _captureDOF();
	void _captureLensFlare();
	void _captureMotionBlur();
	void _renderSkyEntity(EntityBus& entityBus);
	void _renderTerrainEntity(EntityBus& entityBus);
	void _renderWaterEntity(EntityBus& entityBus);
	void _renderModelEntities(EntityBus& entityBus);
	void _renderBillboardEntities(EntityBus& entityBus);
	void _renderAabbEntities(EntityBus& entityBus);
	void _renderFinalSceneMap();
	void _renderDebugScreens();
	void _renderGUI(EntityBus& entityBus);
	void _renderCursor(EntityBus& entityBus);

	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;

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
	QuadEntityColorRenderer _quadEntityColorRenderer;
	AntiAliasingRenderer _antiAliasingRenderer;
	BloomRenderer _bloomRenderer;
	DofRenderer _dofRenderer;
	LensFlareRenderer _lensFlareRenderer;
	MotionBlurRenderer _motionBlurRenderer;
	BlurRenderer _bloomBlurRendererHighQuality;
	BlurRenderer _bloomBlurRendererLowQuality;
	BlurRenderer _dofBlurRenderer;
	BlurRenderer _motionBlurBlurRenderer;

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
	shared_ptr<QuadEntity> _renderQuad = nullptr;

	RenderBus& _renderBus;
};
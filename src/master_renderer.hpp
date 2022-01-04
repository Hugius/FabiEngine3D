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
	MasterRenderer();

	void update(RenderBus& renderBus, Camera& camera);
	void render(RenderBus& renderBus, shared_ptr<QuadEntity> entity, ivec2 viewport);
	void render(RenderBus& renderBus, Camera& camera, ShadowGenerator& shadowGenerator, Timer& timer, EntityBus& entityBus);
	void reloadBloomBlurCaptureBuffer(RenderBus& renderBus);
	void reloadDofBlurCaptureBuffer(RenderBus& renderBus);
	void reloadMotionBlurBlurCaptureBuffer(RenderBus& renderBus);
	void reloadCubeReflectionCaptureBuffer(RenderBus& renderBus);
	void reloadPlanarReflectionCaptureBuffer(RenderBus& renderBus);
	void reloadWaterReflectionCaptureBuffer(RenderBus& renderBus);
	void reloadWaterRefractionCaptureBuffer(RenderBus& renderBus);
	void reloadShadowCaptureBuffer(RenderBus& renderBus);
	void setBackgroundColor(fvec4 color);

	const string getCpuName() const;
	const string getGpuName() const;
	const string getOpenglVersion() const;

private:
	void _updateMotionBlur(RenderBus& renderBus, Camera& camera);
	void _updateLensFlare(RenderBus& renderBus);
	void _captureCubeReflections(RenderBus& renderBus, ShadowGenerator& shadowGenerator, Camera& camera, EntityBus& entityBus);
	void _capturePlanarReflections(RenderBus& renderBus, Camera& camera, EntityBus& entityBus);
	void _captureWaterReflections(RenderBus& renderBus, Camera& camera, EntityBus& entityBus);
	void _captureWaterRefractions(RenderBus& renderBus, Camera& camera, EntityBus& entityBus);
	void _captureWorldDepth(RenderBus& renderBus, EntityBus& entityBus);
	void _captureShadows(RenderBus& renderBus, EntityBus& entityBus);
	void _captureAntiAliasing(RenderBus& renderBus);
	void _captureBloom(RenderBus& renderBus);
	void _captureDOF(RenderBus& renderBus);
	void _captureLensFlare(RenderBus& renderBus);
	void _captureMotionBlur(RenderBus& renderBus);
	void _renderSkyEntity(RenderBus& renderBus, EntityBus& entityBus);
	void _renderTerrainEntity(RenderBus& renderBus, EntityBus& entityBus);
	void _renderWaterEntity(RenderBus& renderBus, EntityBus& entityBus);
	void _renderModelEntities(RenderBus& renderBus, EntityBus& entityBus);
	void _renderBillboardEntities(RenderBus& renderBus, EntityBus& entityBus);
	void _renderAabbEntities(RenderBus& renderBus, EntityBus& entityBus);
	void _renderFinalSceneMap(RenderBus& renderBus);
	void _renderDebugScreens(RenderBus& renderBus);
	void _renderGUI(RenderBus& renderBus, EntityBus& entityBus);
	void _renderCursor(RenderBus& renderBus, EntityBus& entityBus);

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

	shared_ptr<QuadEntity> _renderQuad = nullptr;

	shared_ptr<ShaderBuffer> _skyEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _terrainEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _terrainEntityDepthShader = nullptr;
	shared_ptr<ShaderBuffer> _waterEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _modelEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _modelEntityDepthShader = nullptr;
	shared_ptr<ShaderBuffer> _modelEntityShadowShader = nullptr;
	shared_ptr<ShaderBuffer> _billboardEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _billboardEntityDepthShader = nullptr;
	shared_ptr<ShaderBuffer> _billboardEntityShadowShader = nullptr;
	shared_ptr<ShaderBuffer> _aabbEntityColorShader = nullptr;
	shared_ptr<ShaderBuffer> _quadEntityColorShader = nullptr;
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
};
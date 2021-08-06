#pragma once

#include "render_framebuffer.hpp"
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
#include "lens_renderer.hpp"
#include "motion_blur_renderer.hpp"
#include "blur_renderer.hpp"
#include "timer.hpp"
#include "blur_type.hpp"
#include "texture_loader.hpp"

class MasterRenderer final
{
public:
	MasterRenderer(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader, Camera& camera);

	void update();
	void renderEngineLogo(shared_ptr<ImageEntity> entity, shared_ptr<TextEntity> text, Ivec2 viewport);
	void renderScene(EntityBus* entityBus);
	void reloadShadowFramebuffer();
	void reloadSceneReflectionFramebuffer();
	void reloadWaterReflectionFramebuffer();
	void reloadWaterRefractionFramebuffer();

private:
	// Update functions
	void _updateMotionBlur();
	void _updateLensEffects();

	// Pre-capturing functions
	void _captureSceneReflections();
	void _captureWaterReflections();
	void _captureWaterRefractions();
	void _captureSceneDepth();
	void _captureShadows();

	// Post-capturing functions
	void _captureAntiAliasing();
	void _captureBloom();
	void _captureDOF();
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
	LensRenderer _lensRenderer;
	MotionBlurRenderer _motionBlurRenderer;
	BlurRenderer _dofBlurRenderer;
	BlurRenderer _motionBlurBlurRenderer;
	BlurRenderer _bloomBlurRendererHighQuality;
	BlurRenderer _bloomBlurRendererLowQuality;
	
	// Framebuffers
	RenderFramebuffer _sceneReflectionFramebuffer;
	RenderFramebuffer _waterReflectionFramebuffer;
	RenderFramebuffer _waterRefractionFramebuffer;
	RenderFramebuffer _shadowFramebuffer;
	RenderFramebuffer _sceneDepthFramebuffer;
	RenderFramebuffer _sceneColorFramebuffer;
	RenderFramebuffer _antiAliasingFramebuffer;
	RenderFramebuffer _bloomFramebuffer;
	RenderFramebuffer _dofFramebuffer;
	RenderFramebuffer _lensFramebuffer;
	RenderFramebuffer _motionBlurFramebuffer;

	// Surfaces
	shared_ptr<ImageEntity> _renderSurface = nullptr;

	// Miscellaneous
	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;
};
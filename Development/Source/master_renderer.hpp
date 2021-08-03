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
#include "billboard_entity_color_renderer.hpp"
#include "billboard_entity_depth_renderer.hpp"
#include "aabb_entity_color_renderer.hpp"
#include "image_entity_color_renderer.hpp"
#include "post_renderer.hpp"
#include "blur_renderer.hpp"
#include "shadow_renderer.hpp"
#include "final_renderer.hpp"
#include "anti_aliasing_renderer.hpp"
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
	// Capturing functions
	void _captureSceneReflections();
	void _captureWaterReflections();
	void _captureWaterRefractions();
	void _captureSceneDepth();
	void _captureShadows();
	void _captureAntiAliasing();
	void _captureBloom();
	void _captureDofBlur();
	void _captureLensFlare();
	void _capturePostProcessing();
	void _captureMotionBlur();

	// Rendering functions
	void _renderSkyEntity();
	void _renderTerrainEntity();
	void _renderWaterEntity();
	void _renderModelEntities();
	void _renderBillboardEntities();
	void _renderAabbEntities();
	void _renderFinalSceneTexture();
	void _renderGUI();
	void _renderCustomCursor();
	void _renderDebugScreens();

	// Instances
	Camera& _camera;
	Timer& _timer;
	RenderBus& _renderBus;
	TextureLoader& _textureLoader;
	EntityBus* _entityBus = nullptr;

	// Final screen texture
	shared_ptr<ImageEntity> _finalSurface = nullptr;

	// Renderers
	SkyEntityColorRenderer _skyEntityColorRenderer;
	TerrainEntityColorRenderer _terrainEntityColorRenderer;
	TerrainEntityDepthRenderer    _terrainEntityDepthRenderer;
	WaterEntityColorRenderer      _waterEntityColorRenderer;
	ModelEntityColorRenderer      _modelEntityColorRenderer;
	ModelEntityDepthRenderer      _modelEntityDepthRenderer;
	BillboardEntityColorRenderer  _billboardEntityColorRenderer;
	BillboardEntityDepthRenderer  _billboardEntityDepthRenderer;
	AabbEntityColorRenderer       _aabbEntityColorRenderer;
	ImageEntityColorRenderer      _imageEntityColorRenderer;
	ShadowRenderer           _shadowRenderer;
	AntiAliasingRenderer	 _antiAliasingRenderer;
	BlurRenderer             _dofRenderer;
	BlurRenderer             _motionBlurRenderer;
	BlurRenderer             _bloomRendererHighQuality;
	BlurRenderer             _bloomRendererLowQuality;
	PostRenderer             _postProcessingRenderer;
	FinalRenderer            _finalRenderer;

	// Framebuffers
	RenderFramebuffer _sceneReflectionFramebuffer;
	RenderFramebuffer _waterReflectionFramebuffer;
	RenderFramebuffer _waterRefractionFramebuffer;
	RenderFramebuffer _sceneDepthFramebuffer;
	RenderFramebuffer _shadowFramebuffer;
	RenderFramebuffer _screenFramebuffer;
	RenderFramebuffer _antiAliasingFramebuffer;
	RenderFramebuffer _postProcessingFramebuffer;

	// Miscellaneous
	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;
};
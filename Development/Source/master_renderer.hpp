#pragma once

#include "render_framebuffer.hpp"
#include "camera.hpp"
#include "entity_bus.hpp"
#include "sky_entity_renderer.hpp"
#include "terrain_entity_renderer.hpp"
#include "water_entity_renderer.hpp"
#include "model_entity_renderer.hpp"
#include "billboard_entity_renderer.hpp"
#include "aabb_entity_renderer.hpp"
#include "image_entity_renderer.hpp"
#include "post_renderer.hpp"
#include "blur_renderer.hpp"
#include "shadow_renderer.hpp"
#include "final_renderer.hpp"
#include "depth_renderer.hpp"
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
	void loadShadowFramebuffer(int quality);
	void loadReflectionFramebuffer(int quality);
	void loadRefractionFramebuffer(int quality);

private:
	// Capturing functions
	void _captureSceneReflections();
	void _captureWaterReflections();
	void _captureWaterRefractions();
	void _captureShadows();
	void _captureBloom();
	void _captureSceneDepth();
	void _capturePostProcessing();
	void _captureDofBlur();
	void _captureMotionBlur();
	void _captureLensFlare();

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
	SkyEntityRenderer        _skyEntityRenderer;
	TerrainEntityRenderer    _terrainEntityRenderer;
	WaterEntityRenderer      _waterEntityRenderer;
	ModelEntityRenderer      _modelEntityRenderer;
	BillboardEntityRenderer	 _billboardEntityRenderer;
	AabbEntityRenderer       _aabbEntityRenderer;
	ImageEntityRenderer      _imageEntityRenderer;
	BlurRenderer             _dofRenderer;
	BlurRenderer             _motionBlurRenderer;
	BlurRenderer             _bloomRenderer;
	ShadowRenderer           _shadowRenderer;
	DepthRenderer            _depthRenderer;
	PostRenderer             _postRenderer;
	FinalRenderer            _finalRenderer;

	// Framebuffers
	RenderFramebuffer _screenFramebuffer;
	RenderFramebuffer _sceneReflectionFramebuffer;
	RenderFramebuffer _waterReflectionFramebuffer;
	RenderFramebuffer _waterRefractionFramebuffer;
	RenderFramebuffer _postProcessingFramebuffer;
	RenderFramebuffer _shadowFramebuffer;
	RenderFramebuffer _sceneDepthFramebuffer;

	// Miscellaneous
	float _cameraYawDifference = 0.0f;
	float _cameraPitchDifference = 0.0f;
};
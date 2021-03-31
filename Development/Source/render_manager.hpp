#pragma once

#include "render_framebuffer.hpp"
#include "camera_manager.hpp"
#include "entity_bus.hpp"
#include "sky_entity_renderer.hpp"
#include "terrain_entity_renderer.hpp"
#include "water_entity_renderer.hpp"
#include "model_entity_renderer.hpp"
#include "billboard_entity_renderer.hpp"
#include "aabb_entity_renderer.hpp"
#include "gui_entity_renderer.hpp"
#include "post_renderer.hpp"
#include "bloom_hdr_renderer.hpp"
#include "blur_renderer.hpp"
#include "shadow_renderer.hpp"
#include "final_renderer.hpp"
#include "depth_renderer.hpp"
#include "Timer.hpp"
#include "blur_type.hpp"
#include "texture_loader.hpp"

class RenderManager final
{
public:
	RenderManager(RenderBus& renderBus, Timer& timer, TextureLoader& textureLoader);
	~RenderManager() = default;

	void renderEngineLogo(shared_ptr<GuiEntity> entity, shared_ptr<TextEntity> text, Ivec2 viewport);
	void renderScene(EntityBus* entityBus, CameraManager& camera);
	void loadMsaaFramebuffer(int quality);
	void loadShadowFramebuffer(int quality);
	void loadReflectionFramebuffer(int quality);
	void loadRefractionFramebuffer(int quality);

private:
	// Timer for performance profiling
	Timer& _timer;

	// Renderbus
	RenderBus& _renderBus;

	// Texture loader for debug rendering text
	TextureLoader& _textureLoader;

	// Temp entitybus
	EntityBus* _entityBus = nullptr;

	// Final screen texture
	shared_ptr<GuiEntity> _finalSurface = nullptr;

	// Renderers
	SkyEntityRenderer        _skyEntityRenderer;
	TerrainEntityRenderer    _terrainEntityRenderer;
	WaterEntityRenderer      _waterEntityRenderer;
	ModelEntityRenderer      _modelEntityRenderer;
	BillboardEntityRenderer	 _billboardEntityRenderer;
	AabbEntityRenderer       _aabbEntityRenderer;
	GuiEntityRenderer        _guiEntityRenderer;
	BlurRenderer             _blurRenderer;
	BloomHdrRenderer         _bloomHdrRenderer;
	ShadowRenderer           _shadowRenderer;
	DepthRenderer            _depthRenderer;
	PostRenderer             _postRenderer;
	FinalRenderer            _finalRenderer;

	// Framebuffers
	RenderFramebuffer _screenFramebuffer;
	RenderFramebuffer _msaaFramebuffer;
	RenderFramebuffer _aaProcessorFramebuffer;
	RenderFramebuffer _sceneReflectionFramebuffer;
	RenderFramebuffer _sceneRefractionFramebuffer;
	RenderFramebuffer _bloomHdrFramebuffer;
	RenderFramebuffer _postProcessingFramebuffer;
	RenderFramebuffer _shadowFramebuffer;
	RenderFramebuffer _sceneDepthFramebuffer;

	// Capturing functions
	void _captureSceneReflections(CameraManager& camera);
	void _captureSceneRefractions();
	void _captureShadows();
	void _captureBloom();
	void _captureSceneDepth();
	void _capturePostProcessing();
	void _captureDofBlur();
	void _captureMotionBlur(CameraManager& camera);
	void _captureLensFlare();

	// Scene rendering functions
	void _renderSkyEntity();
	void _renderTerrainEntity();
	void _renderWaterEntity();
	void _renderModelEntities();
	void _renderBillboardEntities();
	void _renderAabbEntities();
	void _renderFinalSceneTexture();
	void _renderGuiEntities();
	void _renderTextEntities();
	void _renderCustomCursor();

	// Other
	void _renderDebugScreens();
};
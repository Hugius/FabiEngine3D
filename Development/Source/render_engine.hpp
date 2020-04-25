#pragma once

#include "opengl_framebuffer.hpp"
#include "camera_manager.hpp"
#include "entity_bus.hpp"
#include "sky_entity_renderer.hpp"
#include "terrain_entity_renderer.hpp"
#include "water_entity_renderer.hpp"
#include "game_entity_renderer.hpp"
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

enum BlurTypes
{
	BLUR_DOF,
	BLUR_BLOOM,
	BLUR_MOTION
};

class RenderEngine final
{
public:
	RenderEngine(ShaderBus& shaderBus, Timer& timer);
	~RenderEngine() = default;
	
	void renderEngineIntro(GuiEntity * entity, ivec2 viewport);
	void renderScene(EntityBus * entityBus, CameraManager & camera, ivec2 mousePos);

private:
	// Timer for performance profiling
	Timer& _timer;

	// Shaderbus
	ShaderBus& _shaderBus;

	// Temp entitybus
	EntityBus * _entityBus = nullptr;

	// Final screen texture
	GuiEntity _finalSurface;

	// Renderers
	SkyEntityRenderer        _skyEntityRenderer;
	TerrainEntityRenderer    _terrainEntityRenderer;
	WaterEntityRenderer      _waterEntityRenderer;
	GameEntityRenderer       _gameEntityRenderer;
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
	OpenGLFramebuffer _screenFramebuffer;
	OpenGLFramebuffer _msaaFramebuffer;
	OpenGLFramebuffer _aaProcessorFramebuffer;
	OpenGLFramebuffer _sceneReflectionFramebuffer;
	OpenGLFramebuffer _waterRefractionFramebuffer;
	OpenGLFramebuffer _shadowFramebuffer;
	OpenGLFramebuffer _bloomHdrFramebuffer;
	OpenGLFramebuffer _bloomDofAdditionFramebuffer;
	OpenGLFramebuffer _depthFramebuffer;

	// Capturing functions
	void _captureSceneReflections(CameraManager & camera);
	void _captureWaterRefractions();
	void _captureShadows();
	void _captureBloom();
	void _captureDepth();
	void _capturePostProcessing();
	void _captureDofBlur();
	void _captureMotionBlur(CameraManager & camera, ivec2 mousePos);

	// Scene rendering functions
	void _renderSkyEntity();
	void _renderTerrainEntity();
	void _renderWaterEntity();
	void _renderGameEntities();
	void _renderBillboardEntities();
	void _renderAabbEntities();
	void _renderFinalTexture();
	void _renderGuiEntities();
	void _renderTextEntities();

	// Other
	void _renderDebugScreens();
};
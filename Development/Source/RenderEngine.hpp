#pragma once

#include "Framebuffer.hpp"
#include "CameraManager.hpp"
#include "EntityBus.hpp"
#include "SkyEntityRenderer.hpp"
#include "TerrainEntityRenderer.hpp"
#include "WaterEntityRenderer.hpp"
#include "GameEntityRenderer.hpp"
#include "BillboardEntityRenderer.hpp"
#include "AabbEntityRenderer.hpp"
#include "GuiEntityRenderer.hpp"
#include "PostRenderer.hpp"
#include "BloomHdrRenderer.hpp"
#include "BlurRenderer.hpp"
#include "ShadowRenderer.hpp"
#include "FinalRenderer.hpp"
#include "DepthRenderer.hpp"
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
	Framebuffer _screenFramebuffer;
	Framebuffer _msaaFramebuffer;
	Framebuffer _aaProcessorFramebuffer;
	Framebuffer _ssrFramebuffer;
	Framebuffer _waterRefractionFramebuffer;
	Framebuffer _shadowFramebuffer;
	Framebuffer _bloomHdrFramebuffer;
	Framebuffer _bloomDofAdditionFramebuffer;
	Framebuffer _depthFramebuffer;

	// Capturing functions
	void _captureSSR(CameraManager & camera);
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
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
	Timer& p_timer;

	// Shaderbus
	ShaderBus& p_shaderBus;

	// Temp entitybus
	EntityBus * p_entityBus = nullptr;

	// Final screen texture
	GuiEntity p_finalSurface;

	// Renderers
	SkyEntityRenderer        p_skyEntityRenderer;
	TerrainEntityRenderer    p_terrainEntityRenderer;
	WaterEntityRenderer      p_waterEntityRenderer;
	GameEntityRenderer       p_gameEntityRenderer;
	BillboardEntityRenderer	 p_billboardEntityRenderer;
	AabbEntityRenderer       p_aabbEntityRenderer;
	GuiEntityRenderer        p_guiEntityRenderer;
	BlurRenderer             p_blurRenderer;
	BloomHdrRenderer         p_bloomHdrRenderer;
	ShadowRenderer           p_shadowRenderer;
	DepthRenderer            p_depthRenderer;
	PostRenderer             p_postRenderer;
	FinalRenderer            p_finalRenderer;

	// Framebuffers
	Framebuffer p_screenFramebuffer;
	Framebuffer p_msaaFramebuffer;
	Framebuffer p_aaProcessorFramebuffer;
	Framebuffer p_ssrFramebuffer;
	Framebuffer p_waterRefractionFramebuffer;
	Framebuffer p_shadowFramebuffer;
	Framebuffer p_bloomHdrFramebuffer;
	Framebuffer p_bloomDofAdditionFramebuffer;
	Framebuffer p_depthFramebuffer;

	// Capturing functions
	void p_captureSSR(CameraManager & camera);
	void p_captureWaterRefractions();
	void p_captureShadows();
	void p_captureBloom();
	void p_captureDepth();
	void p_capturePostProcessing();
	void p_captureDofBlur();
	void p_captureMotionBlur(CameraManager & camera, ivec2 mousePos);

	// Scene rendering functions
	void p_renderSkyEntity();
	void p_renderTerrainEntity();
	void p_renderWaterEntity();
	void p_renderGameEntities();
	void p_renderBillboardEntities();
	void p_renderAabbEntities();
	void p_renderFinalTexture();
	void p_renderGuiEntities();
	void p_renderTextEntities();

	// Other
	void p_renderDebugScreens();
};
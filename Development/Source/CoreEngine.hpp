#pragma once

#include "WoodEngine3D.hpp"
#include "OBJLoader.hpp"
#include "TextureLoader.hpp"
#include "AudioLoader.hpp"
#include "InputHandler.hpp"
#include "ShaderBus.hpp"
#include "WindowManager.hpp"
#include "CameraManager.hpp"
#include "RenderEngine.hpp"
#include "SkyEntityManager.hpp"
#include "TerrainEntityManager.hpp"
#include "WaterEntityManager.hpp"
#include "GameEntityManager.hpp"
#include "BillboardEntityManager.hpp"
#include "AabbEntityManager.hpp"
#include "LightEntityManager.hpp"
#include "GuiEntityManager.hpp"
#include "TextEntityManager.hpp"
#include "ShadowManager.hpp"
#include "MousePicker.hpp"
#include "ModelEditor.hpp"
#include "WorldEditor.hpp"
#include "CollisionResolver.hpp"
#include "Timer.hpp"
#include "AudioManager.hpp"
#include "AudioPlayer.hpp"

class CoreEngine
{
	friend class WoodEngine3D;
private:
	// Core
	CoreEngine(WoodEngine3D & we3d, EngineState engineState);
	virtual ~CoreEngine() = default;

	// Core instances
	OBJLoader              p_objLoader;
	TextureLoader          p_texLoader;
	AudioLoader			   p_audioLoader;
	InputHandler           p_inputHandler;
	ShaderBus			   p_shaderBus;
	WindowManager          p_windowManager;
	CameraManager          p_cameraManager;
	RenderEngine           p_renderEngine;
	SkyEntityManager       p_skyEntityManager;
	TerrainEntityManager   p_terrainEntityManager;
	WaterEntityManager     p_waterEntityManager;
	GameEntityManager      p_gameEntityManager;
	BillboardEntityManager p_billboardEntityManager;
	AabbEntityManager      p_aabbEntityManager;
	LightEntityManager     p_lightEntityManager;
	GuiEntityManager       p_guiEntityManager;
	TextEntityManager      p_textEntityManager;
	ShadowManager          p_shadowManager;
	MousePicker            p_mousePicker;
	ModelEditor            p_modelEditor;
	WorldEditor            p_worldEditor;
	CollisionDetector      p_collisionDetector;
	CollisionResolver      p_collisionResolver;
	Timer                  p_timer;
	AudioManager		   p_audioManager;
	AudioPlayer			   p_audioPlayer;
	
	// Core functions
	void p_start();
	void p_stop();
	void p_setupApplication();
	void p_updateApplication();
	void p_renderApplication();

	// Misc functions
	void p_displayIntroScene();
	void p_initWindow();
	void p_initGame();
	void p_initModelEditor();
	void p_initWorldEditor();
	void p_updateGame();
	void p_updateModelEditor();
	void p_updateWorldEditor();
	void p_updatePerformanceProfiler();

	// Other
	WoodEngine3D & p_we3d;

	bool p_isRunning = false;
	bool p_isPaused  = false;
	bool p_showStats = false;
	bool p_entitiesPaused = false;

	const EngineState p_engineState;
};
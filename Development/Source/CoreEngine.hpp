#pragma once

#include "FabiEngine3D.hpp"
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

enum class EngineState
{
	STATE_GUI,
	STATE_MODEL_EDITOR,
	STATE_WORLD_EDITOR,
	STATE_GAME
};

class CoreEngine
{
	friend class FabiEngine3D;
private:
	// Core
	CoreEngine(FabiEngine3D & fe3d);
	virtual ~CoreEngine();

	// Core instances
	WindowManager          _windowManager;
	OBJLoader              _objLoader;
	TextureLoader          _texLoader;
	AudioLoader			   _audioLoader;
	InputHandler           _inputHandler;
	ShaderBus			   _shaderBus;
	CameraManager          _cameraManager;
	RenderEngine           _renderEngine;
	SkyEntityManager       _skyEntityManager;
	TerrainEntityManager   _terrainEntityManager;
	WaterEntityManager     _waterEntityManager;
	GameEntityManager      _gameEntityManager;
	BillboardEntityManager _billboardEntityManager;
	AabbEntityManager      _aabbEntityManager;
	LightEntityManager     _lightEntityManager;
	GuiEntityManager       _guiEntityManager;
	TextEntityManager      _textEntityManager;
	ShadowManager          _shadowManager;
	MousePicker            _mousePicker;
	ModelEditor            _modelEditor;
	WorldEditor            _worldEditor;
	CollisionDetector      _collisionDetector;
	CollisionResolver      _collisionResolver;
	Timer                  _timer;
	AudioManager		   _audioManager;
	AudioPlayer			   _audioPlayer;
	
	// Core functions
	void _start();
	void _stop();
	void _setupApplication();
	void _updateApplication();
	void _renderApplication();

	// Misc functions
	void _updatePerformanceProfiler();

	// Engine interface instance
	FabiEngine3D & _fe3d;

	bool _isRunning = false;
	bool _showStats = false;

	EngineState _engineState;
};
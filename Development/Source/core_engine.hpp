#pragma once

#include "fabi_engine_3d.hpp"
#include "mesh_loader.hpp"
#include "texture_loader.hpp"
#include "audio_loader.hpp"
#include "input_handler.hpp"
#include "render_bus.hpp"
#include "window_manager.hpp"
#include "camera_manager.hpp"
#include "render_engine.hpp"
#include "sky_entity_manager.hpp"
#include "terrain_entity_manager.hpp"
#include "water_entity_manager.hpp"
#include "game_entity_manager.hpp"
#include "billboard_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "light_entity_manager.hpp"
#include "gui_entity_manager.hpp"
#include "text_entity_manager.hpp"
#include "shadow_manager.hpp"
#include "mouse_picker.hpp"
#include "model_editor.hpp"
#include "environment_editor.hpp"
#include "collision_resolver.hpp"
#include "Timer.hpp"
#include "audio_manager.hpp"
#include "audio_player.hpp"

class CoreEngine final
{
	friend class FabiEngine3D;

private:
	// Core
	CoreEngine(FabiEngine3D& fe3d);
	virtual ~CoreEngine();

	// Core instances
	WindowManager          _windowManager;
	MeshLoader             _meshLoader;
	TextureLoader          _textureLoader;
	AudioLoader			   _audioLoader;
	InputHandler           _inputHandler;
	RenderBus			   _renderBus;
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
	CollisionDetector      _collisionDetector;
	CollisionResolver      _collisionResolver;
	Timer                  _timer;
	AudioManager		   _audioManager;
	AudioPlayer			   _audioPlayer;
	
	// Core functions
	void _start();
	void _pause();
	void _resume();
	void _stop();
	void _setupApplication();
	void _updateApplication();
	void _renderApplication();

	// Miscellaneous functions
	void _updateWindowFading();

	// Engine interface instance
	FabiEngine3D & _fe3d;

	// Miscellaneous variable
	float _deltaTimeMS = 0.0f;
	bool _isPaused = false;
	bool _isRunning = false;
	bool _showStats = false;
};
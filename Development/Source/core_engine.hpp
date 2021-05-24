#pragma once

#include "fabi_engine_3d.hpp"
#include "mesh_loader.hpp"
#include "texture_loader.hpp"
#include "audio_loader.hpp"
#include "input_handler.hpp"
#include "render_bus.hpp"
#include "window_manager.hpp"
#include "camera_manager.hpp"
#include "render_manager.hpp"
#include "sky_entity_manager.hpp"
#include "terrain_entity_manager.hpp"
#include "water_entity_manager.hpp"
#include "model_entity_manager.hpp"
#include "billboard_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "light_entity_manager.hpp"
#include "image_entity_manager.hpp"
#include "text_entity_manager.hpp"
#include "shadow_manager.hpp"
#include "ray_caster.hpp"
#include "model_editor.hpp"
#include "environment_editor.hpp"
#include "collision_resolver.hpp"
#include "timer.hpp"
#include "audio_manager.hpp"
#include "audio_player.hpp"
#include "library_loader.hpp"

class CoreEngine final
{
	friend class FabiEngine3D;

private:
	// Core
	CoreEngine(FabiEngine3D& fe3d);
	virtual ~CoreEngine();

	// Core instances
	LibraryLoader		   _libraryLoader;
	WindowManager          _windowManager;
	MeshLoader             _meshLoader;
	TextureLoader          _textureLoader;
	AudioLoader			   _audioLoader;
	InputHandler           _inputHandler;
	RenderBus			   _renderBus;
	CameraManager          _cameraManager;
	RenderManager          _renderManager;
	SkyEntityManager       _skyEntityManager;
	TerrainEntityManager   _terrainEntityManager;
	WaterEntityManager     _waterEntityManager;
	ModelEntityManager      _modelEntityManager;
	BillboardEntityManager _billboardEntityManager;
	AabbEntityManager      _aabbEntityManager;
	LightEntityManager     _lightEntityManager;
	ImageEntityManager      _imageEntityManager;
	TextEntityManager      _textEntityManager;
	ShadowManager          _shadowManager;
	RayCaster              _rayCaster;
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
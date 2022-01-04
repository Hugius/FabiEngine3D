#pragma once

#include "fe3d.hpp"
#include "mesh_loader.hpp"
#include "image_loader.hpp"
#include "audio_loader.hpp"
#include "input_handler.hpp"
#include "render_bus.hpp"
#include "render_window.hpp"
#include "camera.hpp"
#include "master_renderer.hpp"
#include "sky_entity_manager.hpp"
#include "terrain_entity_manager.hpp"
#include "water_entity_manager.hpp"
#include "model_entity_manager.hpp"
#include "billboard_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "pointlight_entity_manager.hpp"
#include "spotlight_entity_manager.hpp"
#include "reflection_entity_manager.hpp"
#include "quad_entity_manager.hpp"
#include "text_entity_manager.hpp"
#include "shadow_generator.hpp"
#include "raycaster.hpp"
#include "camera_collision_handler.hpp"
#include "timer.hpp"
#include "sound2d_manager.hpp"
#include "sound3d_manager.hpp"
#include "sound2d_player.hpp"
#include "sound3d_player.hpp"
#include "library_loader.hpp"
#include "networking_server.hpp"
#include "networking_client.hpp"

class Core final
{
	friend class FabiEngine3D;

private:
	Core(FabiEngine3D& fe3d);

	void _start();
	void _prepare();
	void _update();
	void _render();
	void _pause();
	void _resume();
	void _stop();

	float _deltaTimeMS = 0.0f;

	bool _isPaused = false;
	bool _isRunning = false;

	FabiEngine3D& _fe3d;
	LibraryLoader _libraryLoader;
	MeshLoader _meshLoader;
	ImageLoader _imageLoader;
	AudioLoader _audioLoader;
	WaterEntityManager _waterEntityManager;
	AabbEntityManager _aabbEntityManager;
	PointlightEntityManager _pointlightEntityManager;
	SpotlightEntityManager _spotlightEntityManager;
	ReflectionEntityManager _reflectionEntityManager;
	Sound2dPlayer _sound2dPlayer;
	Sound3dPlayer _sound3dPlayer;
	NetworkingServer _networkingServer;
	NetworkingClient _networkingClient;
	RenderBus _renderBus;
	InputHandler _inputHandler;
	CameraCollisionHandler _cameraCollisionHandler;
	Timer _timer;
	RenderWindow _renderWindow;
	Sound2dManager _sound2dManager;
	Sound3dManager _sound3dManager;
	ShadowGenerator _shadowGenerator;
	Camera _camera;
	SkyEntityManager _skyEntityManager;
	TerrainEntityManager _terrainEntityManager;
	ModelEntityManager _modelEntityManager;
	BillboardEntityManager _billboardEntityManager;
	QuadEntityManager _quadEntityManager;
	TextEntityManager _textEntityManager;
	Raycaster _raycaster;
	MasterRenderer _masterRenderer;
};
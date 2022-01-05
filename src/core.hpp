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
#include "buffer_cache.hpp"

class Core final
{
public:
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

	shared_ptr<LibraryLoader> _libraryLoader = nullptr;
	shared_ptr<InputHandler> _inputHandler = nullptr;
	shared_ptr<MeshLoader> _meshLoader = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<AudioLoader> _audioLoader = nullptr;
	shared_ptr<SkyEntityManager> _skyEntityManager = nullptr;
	shared_ptr<TerrainEntityManager> _terrainEntityManager = nullptr;
	shared_ptr<WaterEntityManager> _waterEntityManager = nullptr;
	shared_ptr<ModelEntityManager> _modelEntityManager = nullptr;
	shared_ptr<BillboardEntityManager> _billboardEntityManager = nullptr;
	shared_ptr<AabbEntityManager> _aabbEntityManager = nullptr;
	shared_ptr<QuadEntityManager> _quadEntityManager = nullptr;
	shared_ptr<TextEntityManager> _textEntityManager = nullptr;
	shared_ptr<PointlightEntityManager> _pointlightEntityManager = nullptr;
	shared_ptr<SpotlightEntityManager> _spotlightEntityManager = nullptr;
	shared_ptr<ReflectionEntityManager> _reflectionEntityManager = nullptr;
	shared_ptr<RenderWindow> _renderWindow = nullptr;
	shared_ptr<MasterRenderer> _masterRenderer = nullptr;
	shared_ptr<BufferCache> _bufferCache = nullptr;
	shared_ptr<RenderBus> _renderBus = nullptr;
	shared_ptr<ShadowGenerator> _shadowGenerator = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<Raycaster> _raycaster = nullptr;
	shared_ptr<CameraCollisionDetector> _cameraCollisionDetector = nullptr;
	shared_ptr<CameraCollisionHandler> _cameraCollisionHandler = nullptr;
	shared_ptr<Sound2dManager> _sound2dManager = nullptr;
	shared_ptr<Sound3dManager> _sound3dManager = nullptr;
	shared_ptr<Sound2dPlayer> _sound2dPlayer = nullptr;
	shared_ptr<Sound3dPlayer> _sound3dPlayer = nullptr;
	shared_ptr<NetworkingServer> _networkingServer = nullptr;
	shared_ptr<NetworkingClient> _networkingClient = nullptr;
	shared_ptr<Timer> _timer = nullptr;
};
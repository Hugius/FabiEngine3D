#pragma once

#include "mesh_loader.hpp"
#include "image_loader.hpp"
#include "audio_loader.hpp"
#include "input_handler.hpp"
#include "render_storage.hpp"
#include "render_window.hpp"
#include "camera.hpp"
#include "master_renderer.hpp"
#include "sky_entity_manager.hpp"
#include "terrain_entity_manager.hpp"
#include "water_entity_manager.hpp"
#include "model_entity_manager.hpp"
#include "quad3d_entity_manager.hpp"
#include "text3d_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "pointlight_entity_manager.hpp"
#include "spotlight_entity_manager.hpp"
#include "reflection_entity_manager.hpp"
#include "quad2d_entity_manager.hpp"
#include "text2d_entity_manager.hpp"
#include "raycast_calculator.hpp"
#include "raycast_intersector.hpp"
#include "camera_collision_responder.hpp"
#include "timer.hpp"
#include "sound2d_manager.hpp"
#include "sound3d_manager.hpp"
#include "sound2d_player.hpp"
#include "sound3d_player.hpp"
#include "library_loader.hpp"
#include "networking_server.hpp"
#include "networking_client.hpp"
#include "vertex_buffer_cache.hpp"
#include "texture_buffer_cache.hpp"
#include "wave_buffer_cache.hpp"
#include "animation3d_manager.hpp"
#include "animation2d_manager.hpp"
#include "animation3d_player.hpp"
#include "animation2d_player.hpp"

class EngineController;

class EngineCore final
{
public:
	EngineCore();

	void inject(shared_ptr<EngineController> engineController);
	void start();
	void stop();

	const unordered_map<string, float> & getUpdateDeltaTimes() const;
	const unordered_map<string, float> & getRenderDeltaTimes() const;

	const shared_ptr<LibraryLoader> getLibraryLoader() const;
	const shared_ptr<InputHandler> getInputHandler() const;
	const shared_ptr<MeshLoader> getMeshLoader() const;
	const shared_ptr<ImageLoader> getImageLoader() const;
	const shared_ptr<AudioLoader> getAudioLoader() const;
	const shared_ptr<SkyEntityManager> getSkyEntityManager() const;
	const shared_ptr<TerrainEntityManager> getTerrainEntityManager() const;
	const shared_ptr<WaterEntityManager> getWaterEntityManager() const;
	const shared_ptr<ModelEntityManager> getModelEntityManager() const;
	const shared_ptr<Quad3dEntityManager> getQuad3dEntityManager() const;
	const shared_ptr<Text3dEntityManager> getText3dEntityManager() const;
	const shared_ptr<Quad2dEntityManager> getQuad2dEntityManager() const;
	const shared_ptr<Text2dEntityManager> getText2dEntityManager() const;
	const shared_ptr<AabbEntityManager> getAabbEntityManager() const;
	const shared_ptr<PointlightEntityManager> getPointlightEntityManager() const;
	const shared_ptr<SpotlightEntityManager> getSpotlightEntityManager() const;
	const shared_ptr<ReflectionEntityManager> getReflectionEntityManager() const;
	const shared_ptr<Animation3dManager> getAnimation3dManager() const;
	const shared_ptr<Animation2dManager> getAnimation2dManager() const;
	const shared_ptr<Sound3dManager> getSound3dManager() const;
	const shared_ptr<Sound2dManager> getSound2dManager() const;
	const shared_ptr<RenderWindow> getRenderWindow() const;
	const shared_ptr<MasterRenderer> getMasterRenderer() const;
	const shared_ptr<VertexBufferCache> getVertexBufferCache() const;
	const shared_ptr<TextureBufferCache> getTextureBufferCache() const;
	const shared_ptr<WaveBufferCache> getWaveBufferCache() const;
	const shared_ptr<RenderStorage> getRenderStorage() const;
	const shared_ptr<Camera> getCamera() const;
	const shared_ptr<RaycastCalculator> getRaycastCalculator() const;
	const shared_ptr<RaycastIntersector> getRaycastIntersector() const;
	const shared_ptr<CameraCollisionDetector> getCameraCollisionDetector() const;
	const shared_ptr<CameraCollisionResponder> getCameraCollisionResponder() const;
	const shared_ptr<Animation3dPlayer> getAnimation3dPlayer() const;
	const shared_ptr<Animation2dPlayer> getAnimation2dPlayer() const;
	const shared_ptr<Sound3dPlayer> getSound3dPlayer() const;
	const shared_ptr<Sound2dPlayer> getSound2dPlayer() const;
	const shared_ptr<NetworkingServer> getNetworkingServer() const;
	const shared_ptr<NetworkingClient> getNetworkingClient() const;
	const shared_ptr<Timer> getTimer() const;

	const float getTotalDeltaTime() const;

private:
	void _update();
	void _render();

	unordered_map<string, float> _updateDeltaTimes;
	unordered_map<string, float> _renderDeltaTimes;

	shared_ptr<LibraryLoader> _libraryLoader = nullptr;
	shared_ptr<Timer> _timer = nullptr;
	shared_ptr<InputHandler> _inputHandler = nullptr;
	shared_ptr<MeshLoader> _meshLoader = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<AudioLoader> _audioLoader = nullptr;
	shared_ptr<SkyEntityManager> _skyEntityManager = nullptr;
	shared_ptr<TerrainEntityManager> _terrainEntityManager = nullptr;
	shared_ptr<WaterEntityManager> _waterEntityManager = nullptr;
	shared_ptr<ModelEntityManager> _modelEntityManager = nullptr;
	shared_ptr<Quad3dEntityManager> _quad3dEntityManager = nullptr;
	shared_ptr<Text3dEntityManager> _text3dEntityManager = nullptr;
	shared_ptr<Quad2dEntityManager> _quad2dEntityManager = nullptr;
	shared_ptr<Text2dEntityManager> _text2dEntityManager = nullptr;
	shared_ptr<AabbEntityManager> _aabbEntityManager = nullptr;
	shared_ptr<PointlightEntityManager> _pointlightEntityManager = nullptr;
	shared_ptr<SpotlightEntityManager> _spotlightEntityManager = nullptr;
	shared_ptr<ReflectionEntityManager> _reflectionEntityManager = nullptr;
	shared_ptr<Animation3dManager> _animation3dManager = nullptr;
	shared_ptr<Animation2dManager> _animation2dManager = nullptr;
	shared_ptr<Sound3dManager> _sound3dManager = nullptr;
	shared_ptr<Sound2dManager> _sound2dManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<RaycastCalculator> _raycastCalculator = nullptr;
	shared_ptr<RaycastIntersector> _raycastIntersector = nullptr;
	shared_ptr<CameraCollisionDetector> _cameraCollisionDetector = nullptr;
	shared_ptr<CameraCollisionResponder> _cameraCollisionResponder = nullptr;
	shared_ptr<RenderWindow> _renderWindow = nullptr;
	shared_ptr<VertexBufferCache> _vertexBufferCache = nullptr;
	shared_ptr<TextureBufferCache> _textureBufferCache = nullptr;
	shared_ptr<WaveBufferCache> _waveBufferCache = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<MasterRenderer> _masterRenderer = nullptr;
	shared_ptr<Animation3dPlayer> _animation3dPlayer = nullptr;
	shared_ptr<Animation2dPlayer> _animation2dPlayer = nullptr;
	shared_ptr<Sound3dPlayer> _sound3dPlayer = nullptr;
	shared_ptr<Sound2dPlayer> _sound2dPlayer = nullptr;
	shared_ptr<NetworkingServer> _networkingServer = nullptr;
	shared_ptr<NetworkingClient> _networkingClient = nullptr;
	shared_ptr<EngineController> _engineController = nullptr;

	float _totalDeltaTime = 0.0f;

	bool _isPaused = false;
	bool _isRunning = false;
};
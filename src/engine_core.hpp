#pragma once

#include "mesh_loader.hpp"
#include "image_loader.hpp"
#include "audio_loader.hpp"
#include "input_handler.hpp"
#include "render_storage.hpp"
#include "render_window.hpp"
#include "camera.hpp"
#include "master_renderer.hpp"
#include "sky_manager.hpp"
#include "terrain_manager.hpp"
#include "water_manager.hpp"
#include "model_manager.hpp"
#include "quad3d_manager.hpp"
#include "text3d_manager.hpp"
#include "aabb_manager.hpp"
#include "pointlight_manager.hpp"
#include "spotlight_manager.hpp"
#include "captor_manager.hpp"
#include "quad2d_manager.hpp"
#include "text2d_manager.hpp"
#include "raycast_calculator.hpp"
#include "raycast_intersector.hpp"
#include "camera_collision_responder.hpp"
#include "timer.hpp"
#include "sound2d_manager.hpp"
#include "sound3d_manager.hpp"
#include "sound2d_player.hpp"
#include "sound3d_player.hpp"
#include "networking_helper.hpp"
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

	const shared_ptr<InputHandler> getInputHandler() const;
	const shared_ptr<MeshLoader> getMeshLoader() const;
	const shared_ptr<ImageLoader> getImageLoader() const;
	const shared_ptr<AudioLoader> getAudioLoader() const;
	const shared_ptr<SkyManager> getSkyManager() const;
	const shared_ptr<TerrainManager> getTerrainManager() const;
	const shared_ptr<WaterManager> getWaterManager() const;
	const shared_ptr<ModelManager> getModelManager() const;
	const shared_ptr<Quad3dManager> getQuad3dManager() const;
	const shared_ptr<Text3dManager> getText3dManager() const;
	const shared_ptr<AabbManager> getAabbManager() const;
	const shared_ptr<Quad2dManager> getQuad2dManager() const;
	const shared_ptr<Text2dManager> getText2dManager() const;
	const shared_ptr<PointlightManager> getPointlightManager() const;
	const shared_ptr<SpotlightManager> getSpotlightManager() const;
	const shared_ptr<CaptorManager> getCaptorManager() const;
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
	const shared_ptr<NetworkingHelper> getNetworkingHelper() const;
	const shared_ptr<NetworkingServer> getNetworkingServer() const;
	const shared_ptr<NetworkingClient> getNetworkingClient() const;
	const shared_ptr<Timer> getTimer() const;

	const float getTotalDeltaTime() const;

	const bool isRunning() const;

private:
	void _initialize();
	void _update();
	void _render();

	unordered_map<string, float> _updateDeltaTimes;
	unordered_map<string, float> _renderDeltaTimes;

	shared_ptr<Timer> _timer = nullptr;
	shared_ptr<InputHandler> _inputHandler = nullptr;
	shared_ptr<MeshLoader> _meshLoader = nullptr;
	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<AudioLoader> _audioLoader = nullptr;
	shared_ptr<SkyManager> _skyManager = nullptr;
	shared_ptr<TerrainManager> _terrainManager = nullptr;
	shared_ptr<WaterManager> _waterManager = nullptr;
	shared_ptr<ModelManager> _modelManager = nullptr;
	shared_ptr<Quad3dManager> _quad3dManager = nullptr;
	shared_ptr<Text3dManager> _text3dManager = nullptr;
	shared_ptr<AabbManager> _aabbManager = nullptr;
	shared_ptr<Quad2dManager> _quad2dManager = nullptr;
	shared_ptr<Text2dManager> _text2dManager = nullptr;
	shared_ptr<PointlightManager> _pointlightManager = nullptr;
	shared_ptr<SpotlightManager> _spotlightManager = nullptr;
	shared_ptr<CaptorManager> _captorManager = nullptr;
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
	shared_ptr<NetworkingHelper> _networkingHelper = nullptr;
	shared_ptr<NetworkingServer> _networkingServer = nullptr;
	shared_ptr<NetworkingClient> _networkingClient = nullptr;
	shared_ptr<EngineController> _engineController = nullptr;

	float _totalDeltaTime = 0.0f;

	bool _isRunning = false;
};
#pragma once

#include "render_storage.hpp"
#include "mesh_loader.hpp"
#include "timer.hpp"
#include "model.hpp"
#include "captor_manager.hpp"
#include "vertex_buffer_cache.hpp"
#include "camera.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelManager final
{
public:
	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void inject(shared_ptr<Timer> timer);
	void inject(shared_ptr<CaptorManager> captorManager);
	void inject(shared_ptr<MeshLoader> meshLoader);
	void inject(shared_ptr<VertexBufferCache> vertexBufferCache);
	void update();
	void createModel(const string & modelId, const string & meshPath);
	void deleteModel(const string & modelId);
	void deleteModels();

	const unordered_map<string, shared_ptr<Model>> & getModels() const;

	const shared_ptr<Model> getModel(const string & modelId) const;

	const bool isModelExisting(const string & modelId) const;
	const bool isModelsExisting() const;

private:
	static inline constexpr float CUBE_REFLECTION_OVERLAP_SPEED = 0.01f;
	static inline constexpr float CUBE_REFRACTION_OVERLAP_SPEED = 0.01f;

	static inline constexpr int CUBE_REFLECTION_OVERLAP_INTERVAL = 10;
	static inline constexpr int CUBE_REFRACTION_OVERLAP_INTERVAL = 10;

	unordered_map<string, shared_ptr<Model>> _models = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<Timer> _timer = nullptr;
	shared_ptr<CaptorManager> _captorManager = nullptr;
	shared_ptr<MeshLoader> _meshLoader = nullptr;
	shared_ptr<VertexBufferCache> _vertexBufferCache = nullptr;
};
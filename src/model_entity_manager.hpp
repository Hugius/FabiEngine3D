#pragma once

#include "base_entity_manager.hpp"
#include "render_storage.hpp"
#include "mesh_loader.hpp"
#include "timer.hpp"
#include "model_entity.hpp"
#include "reflection_entity_manager.hpp"
#include "vertex_buffer_cache.hpp"
#include "camera.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelEntityManager final : public BaseEntityManager
{
public:
	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void inject(shared_ptr<Timer> timer);
	void inject(shared_ptr<ReflectionEntityManager> reflectionManager);
	void inject(shared_ptr<MeshLoader> meshLoader);
	void inject(shared_ptr<VertexBufferCache> vertexBufferCache);
	void update();
	void createEntity(const string& id, const string& meshPath);
	void deleteEntity(const string& id);
	void deleteEntities();

	const bool isEntityExisting(const string& id) const;
	const bool isEntitiesExisting() const;

	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();
	shared_ptr<ModelEntity> getEntity(const string& id);

private:
	static inline constexpr float CUBE_REFLECTION_OVERLAP_SPEED = 0.01f;

	unordered_map<string, shared_ptr<ModelEntity>> _entities;

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
	shared_ptr<Timer> _timer = nullptr;
	shared_ptr<ReflectionEntityManager> _reflectionManager = nullptr;
	shared_ptr<MeshLoader> _meshLoader = nullptr;
	shared_ptr<VertexBufferCache> _vertexBufferCache = nullptr;
};
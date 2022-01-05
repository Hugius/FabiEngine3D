#pragma once

#include "render_bus.hpp"
#include "mesh_loader.hpp"
#include "timer.hpp"
#include "model_entity.hpp"
#include "reflection_entity_manager.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelEntityManager final
{
public:
	void inject(shared_ptr<RenderBus> renderBus);
	void inject(shared_ptr<Timer> timer);
	void inject(shared_ptr<ReflectionEntityManager> reflectionManager);
	void inject(shared_ptr<MeshLoader> meshLoader);
	void update();
	void createEntity(const string& ID, const string& meshPath);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();
	shared_ptr<ModelEntity> getEntity(const string& ID);

private:
	static inline const float CUBE_REFLECTION_OVERLAP_SPEED = 0.01f;

	unordered_map<string, shared_ptr<ModelEntity>> _entities;

	shared_ptr<RenderBus> _renderBus = nullptr;
	shared_ptr<Timer> _timer = nullptr;
	shared_ptr<ReflectionEntityManager> _reflectionManager = nullptr;
	shared_ptr<MeshLoader> _meshLoader = nullptr;
};
#pragma once

#include "render_bus.hpp"
#include "mesh_loader.hpp"
#include "timer.hpp"
#include "model_entity.hpp"
#include "reflection_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelEntityManager final
{
public:
	ModelEntityManager(MeshLoader& meshLoader, RenderBus& renderBus, Timer& timer);

	void update(const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities);
	void createEntity(const string& ID, const string& meshPath);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();
	shared_ptr<ModelEntity> getEntity(const string& ID);

private:
	static inline const float CUBE_REFLECTION_OVERLAP_SPEED = 0.01f;

	unordered_map<string, shared_ptr<ModelEntity>> _entities;
	MeshLoader& _meshLoader;
	RenderBus& _renderBus;
	Timer& _timer;
};
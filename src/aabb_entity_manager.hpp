#pragma once

#include "vertex_buffer.hpp"
#include "aabb_entity.hpp"
#include "model_entity.hpp"
#include "billboard_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class AabbEntityManager final
{
public:
	AabbEntityManager();

	void createEntity(const string& ID, bool isCentered);
	void update(const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities,
				const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<AabbEntity>>& getEntities();
	shared_ptr<AabbEntity> getEntity(const string& ID);

private:
	static inline constexpr float MIN_SIZE = 0.1f;

	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _standingMesh;
	unordered_map<string, shared_ptr<AabbEntity>> _entities;
};
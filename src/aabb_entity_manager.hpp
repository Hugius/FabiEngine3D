#pragma once

#include "render_buffer.hpp"
#include "aabb_entity.hpp"
#include "model_entity.hpp"
#include "billboard_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class AabbEntityManager final
{
public:
	AabbEntityManager();

	// VOID
	void createEntity(const string& ID);
	void update(const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities,
				const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities);
	void deleteEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<AabbEntity>>& getEntities();
	shared_ptr<AabbEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _renderBuffer;
	unordered_map<string, shared_ptr<AabbEntity>> _entities;
};
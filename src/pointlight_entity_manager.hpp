#pragma once

#include "pointlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class PointlightManager final
{
public:
	void update();
	void createEntity(const string & pointlightId);
	void deleteEntity(const string & pointlightId);
	void deleteEntities();

	const unordered_map<string, shared_ptr<PointlightEntity>> & getEntities() const;

	const shared_ptr<PointlightEntity> getEntity(const string & pointlightId) const;

	const int getMaxEntityCount() const;

	const bool isEntityExisting(const string & pointlightId) const;
	const bool isEntitiesExisting() const;

private:
	static inline constexpr int MAX_ENTITY_COUNT = 64;

	unordered_map<string, shared_ptr<PointlightEntity>> _entities = {};
};
#pragma once

#include "reflection_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class ReflectionEntityManager final
{
public:
	void update();
	void createEntity(const string& id);
	void deleteEntity(const string& id);
	void deleteEntities();

	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities() const;

	const shared_ptr<ReflectionEntity> getEntity(const string& id) const;

	const bool isEntityExisting(const string& id) const;
	const bool isEntitiesExisting() const;

private:
	unordered_map<string, shared_ptr<ReflectionEntity>> _entities = {};
};
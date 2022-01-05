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
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities();

	shared_ptr<ReflectionEntity> getEntity(const string& ID);

private:
	unordered_map<string, shared_ptr<ReflectionEntity>> _entities;
};
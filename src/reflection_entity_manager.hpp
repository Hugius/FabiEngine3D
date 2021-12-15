#pragma once

#include "reflection_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class ReflectionEntityManager final
{
public:
	// VOID
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities();
	shared_ptr<ReflectionEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	unordered_map<string, shared_ptr<ReflectionEntity>> _entities;
};
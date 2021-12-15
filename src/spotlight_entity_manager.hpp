#pragma once

#include "spotlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class SpotlightEntityManager final
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
	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();
	shared_ptr<SpotlightEntity> getEntity(const string& ID);

	// UNSIGNED INT
	static inline const unsigned int MAX_LIGHT_COUNT = 64;

private:
	// MISCELLANEOUS
	unordered_map<string, shared_ptr<SpotlightEntity>> _entities;
};
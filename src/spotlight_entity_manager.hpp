#pragma once

#include "spotlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class SpotlightEntityManager final
{
public:
	void update();
	void createEntity(const string& id);
	void deleteEntity(const string& id);
	void deleteEntities();

	const unsigned int getMaxEntityCount() const;

	const bool isEntityExisting(const string& id) const;
	const bool isEntitiesExisting() const;

	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();

	shared_ptr<SpotlightEntity> getEntity(const string& id);

private:
	unordered_map<string, shared_ptr<SpotlightEntity>> _entities;

	static inline constexpr unsigned int MAX_ENTITY_COUNT = 64;
};
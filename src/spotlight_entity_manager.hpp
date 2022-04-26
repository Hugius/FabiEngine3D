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
	void createEntity(const string & id);
	void deleteEntity(const string & id);
	void deleteEntities();

	const unordered_map<string, shared_ptr<SpotlightEntity>> & getEntities() const;

	const shared_ptr<SpotlightEntity> getEntity(const string & id) const;

	const int getMaxEntityCount() const;

	const bool isEntityExisting(const string & id) const;
	const bool isEntitiesExisting() const;

private:
	static inline constexpr int MAX_ENTITY_COUNT = 64;

	unordered_map<string, shared_ptr<SpotlightEntity>> _entities = {};
};
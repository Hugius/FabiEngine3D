#pragma once

#include "base_entity_manager.hpp"
#include "spotlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class SpotlightEntityManager final : public BaseEntityManager
{
public:
	void update();
	void createEntity(const string& id);
	void deleteEntity(const string& id);
	void deleteEntities();

	const bool isEntityExisting(const string& id) const;

	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();

	shared_ptr<SpotlightEntity> getEntity(const string& id);

	static inline constexpr unsigned int MAX_LIGHT_COUNT = 64;

private:
	unordered_map<string, shared_ptr<SpotlightEntity>> _entities;
};
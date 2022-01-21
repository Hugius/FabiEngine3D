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
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID) const;

	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();

	shared_ptr<SpotlightEntity> getEntity(const string& ID);

	static inline constexpr unsigned int MAX_LIGHT_COUNT = 64;

private:
	unordered_map<string, shared_ptr<SpotlightEntity>> _entities;
};
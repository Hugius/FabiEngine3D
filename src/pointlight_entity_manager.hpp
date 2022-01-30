#pragma once

#include "base_entity_manager.hpp"
#include "pointlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class PointlightEntityManager final : public BaseEntityManager
{
public:
	void update();
	void createEntity(const string& id);
	void deleteEntity(const string& id);
	void deleteEntities();

	const unsigned int getMaxEntityCount() const;

	const bool isEntityExisting(const string& id) const;

	const unordered_map<string, shared_ptr<PointlightEntity>>& getEntities();

	shared_ptr<PointlightEntity> getEntity(const string& id);

private:
	unordered_map<string, shared_ptr<PointlightEntity>> _entities;

	static inline constexpr unsigned int MAX_ENTITY_COUNT = 64;
};
#pragma once

#include "base_entity_manager.hpp"
#include "reflection_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class ReflectionEntityManager final : public BaseEntityManager
{
public:
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID) override;
	void deleteEntities() override;

	const bool isEntityExisting(const string& ID) const override;

	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities();

	shared_ptr<ReflectionEntity> getEntity(const string& ID);

private:
	unordered_map<string, shared_ptr<ReflectionEntity>> _entities;
};
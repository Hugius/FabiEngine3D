#pragma once

#include "water_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityManager final
{
public:
	void update();
	void createEntity(const string& id);
	void deleteEntity(const string& id);
	void deleteEntities();
	void loadMesh(const string& id);
	void selectEntity(const string& id);

	const bool isEntityExisting(const string& id) const;
	const bool isEntitiesExisting() const;

	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();

	shared_ptr<WaterEntity> getEntity(const string& id);
	shared_ptr<WaterEntity> getSelectedEntity();

private:
	void _loadMesh(shared_ptr<WaterEntity> entity, float size);

	string _selectedEntityId = "";

	unordered_map<string, shared_ptr<WaterEntity>> _entities;
};
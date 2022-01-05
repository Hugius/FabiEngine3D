#pragma once

#include "water_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityManager final
{
public:
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void loadMesh(const string& ID);
	void selectWater(const string& ID);

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();

	shared_ptr<WaterEntity> getEntity(const string& ID);
	shared_ptr<WaterEntity> getSelectedWater();

private:
	void _loadMesh(shared_ptr<WaterEntity> entity, float size);

	string _selectedID = "";

	static inline const float MAX_SIZE = 1024.0f;

	unordered_map<string, shared_ptr<WaterEntity>> _entities;
};
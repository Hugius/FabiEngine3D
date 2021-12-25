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

	static inline const unsigned int MAX_SIZE = 1024;

private:
	string _selectedID = "";

	unordered_map<string, shared_ptr<WaterEntity>> _entities;
};
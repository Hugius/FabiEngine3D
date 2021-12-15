#pragma once

#include "water_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityManager final
{
public:
	// VOID
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void loadMesh(const string& ID);
	void selectWater(const string& ID);

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();
	shared_ptr<WaterEntity> getEntity(const string& ID);
	shared_ptr<WaterEntity> getSelectedWater();

	// UNSIGNED INT
	static inline const unsigned int MAX_SIZE = 1024;

private:
	// STRING
	string _selectedID = "";

	// MISCELLANEOUS
	unordered_map<string, shared_ptr<WaterEntity>> _entities;
};
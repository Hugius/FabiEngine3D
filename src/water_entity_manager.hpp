#pragma once

#include "water_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterEntityManager final
{
public:
	void update();
	void createEntity(const string & id);
	void deleteEntity(const string & id);
	void deleteEntities();
	void loadVertexBuffer(const string & id);
	void selectEntity(const string & id);

	const unordered_map<string, shared_ptr<WaterEntity>> & getEntities() const;

	const shared_ptr<WaterEntity> getEntity(const string & id) const;
	const shared_ptr<WaterEntity> getSelectedEntity() const;

	const bool isEntityExisting(const string & id) const;
	const bool isEntitiesExisting() const;

private:
	void _loadVertexBuffer(shared_ptr<WaterEntity> entity, float size);

	unordered_map<string, shared_ptr<WaterEntity>> _entities = {};

	string _selectedEntityId = "";
};
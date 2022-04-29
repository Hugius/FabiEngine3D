#include "pointlight_entity_manager.hpp"

using std::make_shared;

const shared_ptr<Pointlight> PointlightManager::getEntity(const string & pointlightId) const
{
	auto iterator = _entities.find(pointlightId);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Pointlight>> & PointlightManager::getEntities() const
{
	return _entities;
}

void PointlightManager::createEntity(const string & pointlightId)
{
	if(isEntityExisting(pointlightId))
	{
		abort();
	}

	if(getEntities().size() == MAX_ENTITY_COUNT)
	{
		abort();
	}

	auto entity = make_shared<Pointlight>(pointlightId);

	_entities.insert({pointlightId, entity});
}

void PointlightManager::deleteEntity(const string & pointlightId)
{
	if(!isEntityExisting(pointlightId))
	{
		abort();
	}

	_entities.erase(pointlightId);
}

void PointlightManager::deleteEntities()
{
	_entities.clear();
}

const int PointlightManager::getMaxEntityCount() const
{
	return MAX_ENTITY_COUNT;
}

const bool PointlightManager::isEntityExisting(const string & pointlightId) const
{
	return (_entities.find(pointlightId) != _entities.end());
}

const bool PointlightManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void PointlightManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();
	}
}
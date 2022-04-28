#include "pointlight_entity_manager.hpp"

using std::make_shared;

const shared_ptr<PointlightEntity> PointlightEntityManager::getEntity(const string & pointlightId) const
{
	auto iterator = _entities.find(pointlightId);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<PointlightEntity>> & PointlightEntityManager::getEntities() const
{
	return _entities;
}

void PointlightEntityManager::createEntity(const string & pointlightId)
{
	if(isEntityExisting(pointlightId))
	{
		abort();
	}

	if(getEntities().size() == MAX_ENTITY_COUNT)
	{
		abort();
	}

	auto entity = make_shared<PointlightEntity>(pointlightId);

	_entities.insert({pointlightId, entity});
}

void PointlightEntityManager::deleteEntity(const string & pointlightId)
{
	if(!isEntityExisting(pointlightId))
	{
		abort();
	}

	_entities.erase(pointlightId);
}

void PointlightEntityManager::deleteEntities()
{
	_entities.clear();
}

const int PointlightEntityManager::getMaxEntityCount() const
{
	return MAX_ENTITY_COUNT;
}

const bool PointlightEntityManager::isEntityExisting(const string & pointlightId) const
{
	return (_entities.find(pointlightId) != _entities.end());
}

const bool PointlightEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void PointlightEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();
	}
}
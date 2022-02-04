#include "pointlight_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<PointlightEntity> PointlightEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<PointlightEntity>>& PointlightEntityManager::getEntities()
{
	return _entities;
}

void PointlightEntityManager::createEntity(const string& id)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	if(getEntities().size() == MAX_ENTITY_COUNT)
	{
		abort();
	}

	auto entity = make_shared<PointlightEntity>(id);

	_entities.insert(make_pair(id, entity));
}

void PointlightEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void PointlightEntityManager::deleteEntities()
{
	_entities.clear();
}

const unsigned int PointlightEntityManager::getMaxEntityCount() const
{
	return MAX_ENTITY_COUNT;
}

const bool PointlightEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

void PointlightEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTarget();
	}
}
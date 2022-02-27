#include "reflection_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<ReflectionEntity> ReflectionEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<ReflectionEntity>>& ReflectionEntityManager::getEntities()
{
	return _entities;
}

void ReflectionEntityManager::createEntity(const string& id)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto entity = make_shared<ReflectionEntity>(id);

	_entities.insert({id, entity});
}

void ReflectionEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTarget();
	}
}

void ReflectionEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void ReflectionEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ReflectionEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool ReflectionEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}
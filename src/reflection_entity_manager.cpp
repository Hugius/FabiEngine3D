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
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<ReflectionEntity>>& ReflectionEntityManager::getEntities()
{
	return _entities;
}

void ReflectionEntityManager::createEntity(const string& id)
{
	auto entity = make_shared<ReflectionEntity>(id);

	_entities.insert(make_pair(id, entity));
}

void ReflectionEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();
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
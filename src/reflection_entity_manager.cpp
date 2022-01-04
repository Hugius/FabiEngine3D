#include "reflection_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<ReflectionEntity> ReflectionEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("ReflectionEntityManager::getEntity");
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

void ReflectionEntityManager::createEntity(const string& ID)
{
	auto entity = make_shared<ReflectionEntity>(ID);

	_entities.insert(make_pair(ID, entity));
}

void ReflectionEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();
	}
}

void ReflectionEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("ReflectionEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void ReflectionEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ReflectionEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}
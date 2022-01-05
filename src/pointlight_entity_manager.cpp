#include "pointlight_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<PointlightEntity> PointlightEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("PointlightEntityManager::getEntity");
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

void PointlightEntityManager::createEntity(const string& ID)
{
	if(getEntities().size() == MAX_LIGHT_COUNT)
	{
		Logger::throwError("PointlightEntityManager::createEntity");
	}

	auto entity = make_shared<PointlightEntity>(ID);

	_entities.insert(make_pair(ID, entity));
}

void PointlightEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("PointlightEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void PointlightEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool PointlightEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}

void PointlightEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();
	}
}
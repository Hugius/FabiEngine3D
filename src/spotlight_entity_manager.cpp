#include "spotlight_entity_manager.hpp"

using std::make_shared;

const shared_ptr<SpotlightEntity> SpotlightEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<SpotlightEntity>> & SpotlightEntityManager::getEntities() const
{
	return _entities;
}

void SpotlightEntityManager::createEntity(const string & id)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	if(getEntities().size() == MAX_ENTITY_COUNT)
	{
		abort();
	}

	auto entity = make_shared<SpotlightEntity>(id);

	_entities.insert({id, entity});
}

void SpotlightEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateFront();
		}
	}
}

void SpotlightEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void SpotlightEntityManager::deleteEntities()
{
	_entities.clear();
}

const int SpotlightEntityManager::getMaxEntityCount() const
{
	return MAX_ENTITY_COUNT;
}

const bool SpotlightEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool SpotlightEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}
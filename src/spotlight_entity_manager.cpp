#include "spotlight_entity_manager.hpp"

using std::make_shared;

const shared_ptr<SpotlightEntity> SpotlightEntityManager::getEntity(const string & spotlightId) const
{
	auto iterator = _entities.find(spotlightId);

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

void SpotlightEntityManager::createEntity(const string & spotlightId)
{
	if(isEntityExisting(spotlightId))
	{
		abort();
	}

	if(getEntities().size() == MAX_ENTITY_COUNT)
	{
		abort();
	}

	auto entity = make_shared<SpotlightEntity>(spotlightId);

	_entities.insert({spotlightId, entity});
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

void SpotlightEntityManager::deleteEntity(const string & spotlightId)
{
	if(!isEntityExisting(spotlightId))
	{
		abort();
	}

	_entities.erase(spotlightId);
}

void SpotlightEntityManager::deleteEntities()
{
	_entities.clear();
}

const int SpotlightEntityManager::getMaxEntityCount() const
{
	return MAX_ENTITY_COUNT;
}

const bool SpotlightEntityManager::isEntityExisting(const string & spotlightId) const
{
	return (_entities.find(spotlightId) != _entities.end());
}

const bool SpotlightEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}
#include "spotlight_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<SpotlightEntity> SpotlightEntityManager::getEntity(const string& id)
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

const unordered_map<string, shared_ptr<SpotlightEntity>>& SpotlightEntityManager::getEntities()
{
	return _entities;
}

void SpotlightEntityManager::createEntity(const string& id)
{
	if(getEntities().size() == MAX_ENTITY_COUNT)
	{
		abort();
	}

	auto entity = make_shared<SpotlightEntity>(id);

	_entities.insert(make_pair(id, entity));
}

void SpotlightEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();

		if(entity->isVisible())
		{
			entity->updateFrontVector();
		}
	}
}

void SpotlightEntityManager::deleteEntity(const string& id)
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

const unsigned int SpotlightEntityManager::getMaxEntityCount() const
{
	return MAX_ENTITY_COUNT;
}

const bool SpotlightEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}
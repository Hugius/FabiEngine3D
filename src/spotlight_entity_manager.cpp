#include "spotlight_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<SpotlightEntity> SpotlightEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("SpotlightEntityManager::getEntity");
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

void SpotlightEntityManager::createEntity(const string& ID)
{
	if(getEntities().size() == MAX_LIGHT_COUNT)
	{
		Logger::throwError("SpotlightEntityManager::createEntity");
	}

	auto entity = make_shared<SpotlightEntity>(ID);

	_entities.insert(make_pair(ID, entity));
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

void SpotlightEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("SpotlightEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void SpotlightEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool SpotlightEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}
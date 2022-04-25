#include "captor_entity_manager.hpp"

using std::make_shared;

const shared_ptr<CaptorEntity> CaptorEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<CaptorEntity>> & CaptorEntityManager::getEntities() const
{
	return _entities;
}

void CaptorEntityManager::createEntity(const string & id)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto entity = make_shared<CaptorEntity>(id);

	_entities.insert({id, entity});
}

void CaptorEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();
	}
}

void CaptorEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void CaptorEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool CaptorEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool CaptorEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}
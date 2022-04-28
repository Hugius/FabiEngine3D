#include "captor_entity_manager.hpp"

using std::make_shared;

const shared_ptr<CaptorEntity> CaptorEntityManager::getEntity(const string & captorId) const
{
	auto iterator = _entities.find(captorId);

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

void CaptorEntityManager::createEntity(const string & captorId)
{
	if(isEntityExisting(captorId))
	{
		abort();
	}

	auto entity = make_shared<CaptorEntity>(captorId);

	_entities.insert({captorId, entity});
}

void CaptorEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();
	}
}

void CaptorEntityManager::deleteEntity(const string & captorId)
{
	if(!isEntityExisting(captorId))
	{
		abort();
	}

	_entities.erase(captorId);
}

void CaptorEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool CaptorEntityManager::isEntityExisting(const string & captorId) const
{
	return (_entities.find(captorId) != _entities.end());
}

const bool CaptorEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}
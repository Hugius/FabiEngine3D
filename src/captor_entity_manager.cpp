#include "captor_entity_manager.hpp"

using std::make_shared;

const shared_ptr<CaptorEntity> CaptorManager::getEntity(const string & captorId) const
{
	auto iterator = _entities.find(captorId);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<CaptorEntity>> & CaptorManager::getEntities() const
{
	return _entities;
}

void CaptorManager::createEntity(const string & captorId)
{
	if(isEntityExisting(captorId))
	{
		abort();
	}

	auto entity = make_shared<CaptorEntity>(captorId);

	_entities.insert({captorId, entity});
}

void CaptorManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();
	}
}

void CaptorManager::deleteEntity(const string & captorId)
{
	if(!isEntityExisting(captorId))
	{
		abort();
	}

	_entities.erase(captorId);
}

void CaptorManager::deleteEntities()
{
	_entities.clear();
}

const bool CaptorManager::isEntityExisting(const string & captorId) const
{
	return (_entities.find(captorId) != _entities.end());
}

const bool CaptorManager::isEntitiesExisting() const
{
	return !_entities.empty();
}
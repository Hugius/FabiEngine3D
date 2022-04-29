#include "quad2d_entity_manager.hpp"

using std::make_shared;

Quad2dManager::Quad2dManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

const shared_ptr<Quad2dEntity> Quad2dManager::getEntity(const string & quad2dId) const
{
	auto iterator = _entities.find(quad2dId);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Quad2dEntity>> & Quad2dManager::getEntities() const
{
	return _entities;
}

void Quad2dManager::createEntity(const string & quad2dId, bool isCentered)
{
	if(isEntityExisting(quad2dId))
	{
		abort();
	}

	auto entity = make_shared<Quad2dEntity>(quad2dId);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	entity->setCentered(isCentered);
	entity->setDepth(_renderStorage->getGuiDepth());

	_entities.insert({quad2dId, entity});

	_renderStorage->setGuiDepth(_renderStorage->getGuiDepth() + 1);
}

void Quad2dManager::deleteEntity(const string & quad2dId)
{
	if(!isEntityExisting(quad2dId))
	{
		abort();
	}

	_entities.erase(quad2dId);
}

void Quad2dManager::deleteEntities()
{
	_entities.clear();
}

const bool Quad2dManager::isEntityExisting(const string & quad2dId) const
{
	return (_entities.find(quad2dId) != _entities.end());
}

const bool Quad2dManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void Quad2dManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Quad2dManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}
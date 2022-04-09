#include "quad2d_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

Quad2dEntityManager::Quad2dEntityManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

const shared_ptr<Quad2dEntity> Quad2dEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Quad2dEntity>> & Quad2dEntityManager::getEntities() const
{
	return _entities;
}

void Quad2dEntityManager::createEntity(const string & id, bool isCentered)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto entity = make_shared<Quad2dEntity>(id);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	entity->setCentered(isCentered);
	entity->setDepth(_renderStorage->getGuiDepth());

	_entities.insert({id, entity});

	_renderStorage->setGuiDepth(_renderStorage->getGuiDepth() + 1);
}

void Quad2dEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void Quad2dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Quad2dEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool Quad2dEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void Quad2dEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Quad2dEntityManager::update()
{
	for(const auto & [key, entity] : _entities)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}
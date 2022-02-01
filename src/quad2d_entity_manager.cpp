#include "quad2d_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

Quad2dEntityManager::Quad2dEntityManager()
	:
	_centeredMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<Quad2dEntity> Quad2dEntityManager::getEntity(const string& id)
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

const unordered_map<string, shared_ptr<Quad2dEntity>>& Quad2dEntityManager::getEntities()
{
	return _entities;
}

void Quad2dEntityManager::createEntity(const string& id, bool isCentered)
{
	auto entity = make_shared<Quad2dEntity>(id);

	_entities.insert(make_pair(id, entity));

	entity->setMesh(isCentered ? _centeredMesh : _corneredMesh);
	entity->setCentered(isCentered);
	entity->setDepth(_renderBus->getGuiDepth());

	_renderBus->setGuiDepth(_renderBus->getGuiDepth() + 1);
}

void Quad2dEntityManager::deleteEntity(const string& id)
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

const bool Quad2dEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

void Quad2dEntityManager::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

void Quad2dEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}
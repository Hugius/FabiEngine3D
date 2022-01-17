#include "text_entity_manager.hpp"
#include "text_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

Text2dEntityManager::Text2dEntityManager()
	:
	_mesh(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<Text2dEntity> Text2dEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("Text2dEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<Text2dEntity>>& Text2dEntityManager::getEntities()
{
	return _entities;
}

void Text2dEntityManager::createEntity(const string& ID, bool isCentered)
{
	auto entity = make_shared<Text2dEntity>(ID);

	_entities.insert(make_pair(ID, entity));

	entity->setMesh(_mesh);
	entity->setCentered(isCentered);
	entity->setDepth(_renderBus->getGuiDepth());

	_renderBus->setGuiDepth(_renderBus->getGuiDepth() + 1);
}

void Text2dEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("Text2dEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void Text2dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Text2dEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}

void Text2dEntityManager::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

void Text2dEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();
		entity->updateCharacterEntities();
	}
}
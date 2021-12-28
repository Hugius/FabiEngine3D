#include "text_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

TextEntityManager::TextEntityManager(TextureLoader& textureLoader, RenderBus& renderBus)
	:
	_textureLoader(textureLoader),
	_renderBus(renderBus),
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<TextEntity> TextEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if (iterator == _entities.end())
	{
		Logger::throwError("TextEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<TextEntity>>& TextEntityManager::getEntities()
{
	return _entities;
}

void TextEntityManager::createEntity(const string& ID, bool isCentered)
{
	_entities.insert(make_pair(ID, make_shared<TextEntity>(ID)));
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _corneredRenderBuffer);
	getEntity(ID)->setCentered(isCentered);
	getEntity(ID)->setDepth(_renderBus.getGuiDepth());
	_renderBus.setGuiDepth(_renderBus.getGuiDepth() + 1);
}

void TextEntityManager::deleteEntity(const string& ID)
{
	if (!isEntityExisting(ID))
	{
		Logger::throwError("TextEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void TextEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool TextEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void TextEntityManager::update()
{
	for (const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();

		if (entity->isVisible())
		{
			entity->updateCharacterEntities();
		}
	}
}
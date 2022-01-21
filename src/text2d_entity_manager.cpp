#include "text2d_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

Text2dEntityManager::Text2dEntityManager()
	:
	_centeredMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
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

void Text2dEntityManager::createEntity(const string& ID, const string& fontMapPath, bool isCentered)
{
	auto entity = make_shared<Text2dEntity>(ID);

	_entities.insert(make_pair(ID, entity));

	auto texture = _textureBufferCache->get2dBuffer(fontMapPath);

	if(texture == nullptr)
	{
		texture = make_shared<TextureBuffer>(_imageLoader->loadImage(fontMapPath));

		_textureBufferCache->store2dBuffer(fontMapPath, texture);
	}

	entity->setMesh(isCentered ? _centeredMesh : _corneredMesh);
	entity->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	entity->setFontMapPath(fontMapPath);
	entity->setCentered(isCentered);
	entity->setContent("text");
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

		if(entity->isVisible())
		{
			entity->updateCharacterEntities();
		}
	}
}

void Text2dEntityManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void Text2dEntityManager::inject(shared_ptr<TextureBufferCache> textureBufferCache)
{
	_textureBufferCache = textureBufferCache;
}
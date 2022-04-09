#include "text2d_entity_manager.hpp"

using std::make_shared;

Text2dEntityManager::Text2dEntityManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

const shared_ptr<Text2dEntity> Text2dEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Text2dEntity>> & Text2dEntityManager::getEntities() const
{
	return _entities;
}

void Text2dEntityManager::createEntity(const string & id, const string & fontMapPath, bool isCentered)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto texture = _textureBufferCache->get2dBuffer(fontMapPath);

	if(texture == nullptr)
	{
		auto image = _imageLoader->loadImage(fontMapPath);

		if(image == nullptr)
		{
			return;
		}

		texture = make_shared<TextureBuffer>(image);

		_textureBufferCache->store2dBuffer(fontMapPath, texture);
	}

	auto entity = make_shared<Text2dEntity>(id);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	entity->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	entity->setFontMapPath(fontMapPath);
	entity->setCentered(isCentered);
	entity->setContent("text");
	entity->setDepth(_renderStorage->getGuiDepth());

	_entities.insert({id, entity});

	_renderStorage->setGuiDepth(_renderStorage->getGuiDepth() + 1);
}

void Text2dEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void Text2dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Text2dEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool Text2dEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void Text2dEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Text2dEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

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
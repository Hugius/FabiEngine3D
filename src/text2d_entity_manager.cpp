#include "text2d_entity_manager.hpp"

using std::make_shared;

Text2dEntityManager::Text2dEntityManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

const shared_ptr<Text2dEntity> Text2dEntityManager::getEntity(const string & text2dId) const
{
	auto iterator = _entities.find(text2dId);

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

void Text2dEntityManager::createEntity(const string & text2dId, const string & fontMapPath, bool isCentered)
{
	if(isEntityExisting(text2dId))
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

	auto entity = make_shared<Text2dEntity>(text2dId);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	entity->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	entity->setFontMapPath(fontMapPath);
	entity->setCentered(isCentered);
	entity->setContent("text");
	entity->setDepth(_renderStorage->getGuiDepth());

	_entities.insert({text2dId, entity});

	_renderStorage->setGuiDepth(_renderStorage->getGuiDepth() + 1);
}

void Text2dEntityManager::deleteEntity(const string & text2dId)
{
	if(!isEntityExisting(text2dId))
	{
		abort();
	}

	_entities.erase(text2dId);
}

void Text2dEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool Text2dEntityManager::isEntityExisting(const string & text2dId) const
{
	return (_entities.find(text2dId) != _entities.end());
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
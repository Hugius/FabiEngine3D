#include "text2d_manager.hpp"

using std::make_shared;

Text2dManager::Text2dManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

const shared_ptr<Text2d> Text2dManager::getText2d(const string & text2dId) const
{
	auto iterator = _text2ds.find(text2dId);

	if(iterator == _text2ds.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Text2d>> & Text2dManager::getText2ds() const
{
	return _text2ds;
}

void Text2dManager::createText2d(const string & text2dId, const string & fontMapPath, bool isCentered)
{
	if(isText2dExisting(text2dId))
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

	auto entity = make_shared<Text2d>(text2dId);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	entity->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	entity->setFontMapPath(fontMapPath);
	entity->setCentered(isCentered);
	entity->setContent("text");
	entity->setDepth(_renderStorage->getGuiDepth());

	_text2ds.insert({text2dId, entity});

	_renderStorage->setGuiDepth(_renderStorage->getGuiDepth() + 1);
}

void Text2dManager::deleteText2d(const string & text2dId)
{
	if(!isText2dExisting(text2dId))
	{
		abort();
	}

	_text2ds.erase(text2dId);
}

void Text2dManager::deleteText2ds()
{
	_text2ds.clear();
}

const bool Text2dManager::isText2dExisting(const string & text2dId) const
{
	return (_text2ds.find(text2dId) != _text2ds.end());
}

const bool Text2dManager::isText2dsExisting() const
{
	return !_text2ds.empty();
}

void Text2dManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Text2dManager::update()
{
	for(const auto & [entityId, entity] : _text2ds)
	{
		entity->updateTarget();

		if(entity->isVisible())
		{
			entity->updateCharacterEntities();
		}
	}
}

void Text2dManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void Text2dManager::inject(shared_ptr<TextureBufferCache> textureBufferCache)
{
	_textureBufferCache = textureBufferCache;
}
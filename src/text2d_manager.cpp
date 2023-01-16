#include "text2d_manager.hpp"

using std::make_shared;

const shared_ptr<Text2d> Text2dManager::getText2d(const string & text2dId) const
{
	const auto iterator = _text2ds.find(text2dId);

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
		const auto image = _imageLoader->loadImage(fontMapPath);

		if(image == nullptr)
		{
			return;
		}

		texture = make_shared<TextureBuffer>(image);

		_textureBufferCache->store2dBuffer(fontMapPath, texture);
	}

	const auto text2d = make_shared<Text2d>(text2dId);

	text2d->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	text2d->setFontMap(_textureBufferCache->get2dBuffer(fontMapPath));
	text2d->setFontMapPath(fontMapPath);
	text2d->setCentered(isCentered);
	text2d->setContent(DEFAULT_TEXT_CONTENT);
	text2d->setDepth(_renderStorage->getGuiDepth());

	_text2ds.insert({text2dId, text2d});

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

void Text2dManager::construct()
{
	_centeredVertexBuffer = make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true);
	_corneredVertexBuffer = make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false);
}

void Text2dManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Text2dManager::update()
{
	for(const auto & [text2dId, text2d] : _text2ds)
	{
		text2d->updateTarget();

		if(text2d->isVisible())
		{
			text2d->updateQuad2ds();
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
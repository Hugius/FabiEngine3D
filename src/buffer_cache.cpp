#include "buffer_cache.hpp"

void BufferCache::storeTextureBuffer(const string& filePath, shared_ptr<TextureBuffer> textureBuffer)
{
	auto cacheIterator = _textureBufferCache.find(filePath);

	if(cacheIterator != _textureBufferCache.end())
	{
		Logger::throwError("BufferCache::storeTextureBuffer");
	}

	_textureBufferCache.insert(make_pair(filePath, textureBuffer));
}

shared_ptr<TextureBuffer> BufferCache::getTextureBuffer(const string& filePath)
{
	auto cacheIterator = _textureBufferCache.find(filePath);

	if(cacheIterator != _textureBufferCache.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

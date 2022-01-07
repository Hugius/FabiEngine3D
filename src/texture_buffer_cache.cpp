#include "texture_buffer_cache.hpp"

#include "logger.hpp"

void TextureBufferCache::storeTextureBuffer(const string& filePath, shared_ptr<TextureBuffer> textureBuffer)
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		Logger::throwError("");
	}

	_cache.insert(make_pair(filePath, textureBuffer));
}

const shared_ptr<TextureBuffer> TextureBufferCache::getTextureBuffer(const string& filePath) const
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const map<string, shared_ptr<TextureBuffer>>& TextureBufferCache::getTextureBuffers() const
{
	return _cache;
}
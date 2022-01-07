#include "texture_buffer_cache.hpp"

#include "logger.hpp"

void TextureBufferCache::storeTextureBuffer(const string& ID, shared_ptr<TextureBuffer> textureBuffer)
{
	auto cacheIterator = _cache.find(ID);

	if(cacheIterator != _cache.end())
	{
		Logger::throwError("");
	}

	_cache.insert(make_pair(ID, textureBuffer));
}

const shared_ptr<TextureBuffer> TextureBufferCache::getTextureBuffer(const string& ID) const
{
	auto cacheIterator = _cache.find(ID);

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
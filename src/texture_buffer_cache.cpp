#include "texture_buffer_cache.hpp"

#include "logger.hpp"

void TextureBufferCache::store2dBuffer(const string& filePath, shared_ptr<TextureBuffer> buffer)
{
	auto cacheIterator = _2dBuffers.find(filePath);

	if(cacheIterator != _2dBuffers.end())
	{
		abort();
	}

	_2dBuffers.insert(make_pair(filePath, buffer));
}

void TextureBufferCache::store3dBuffer(const array<string, 6>& filePaths, shared_ptr<TextureBuffer> buffer)
{
	auto cacheIterator = _3dBuffers.find(filePaths);

	if(cacheIterator != _3dBuffers.end())
	{
		abort();
	}

	_3dBuffers.insert(make_pair(filePaths, buffer));
}

void TextureBufferCache::delete2dBuffer(const string& filePath)
{
	if(_2dBuffers.find(filePath) != _2dBuffers.end())
	{
		_2dBuffers.erase(filePath);
	}
}

void TextureBufferCache::delete3dBuffer(const array<string, 6>& filePaths)
{
	if(_3dBuffers.find(filePaths) != _3dBuffers.end())
	{
		_3dBuffers.erase(filePaths);
	}
}

void TextureBufferCache::clear2dBuffers()
{
	_2dBuffers.clear();
}

void TextureBufferCache::clear3dBuffers()
{
	_3dBuffers.clear();
}

const shared_ptr<TextureBuffer> TextureBufferCache::get2dBuffer(const string& filePath) const
{
	auto cacheIterator = _2dBuffers.find(filePath);

	if(cacheIterator != _2dBuffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const shared_ptr<TextureBuffer> TextureBufferCache::get3dBuffer(const array<string, 6>& filePaths) const
{
	auto cacheIterator = _3dBuffers.find(filePaths);

	if(cacheIterator != _3dBuffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const map<string, shared_ptr<TextureBuffer>>& TextureBufferCache::get2dBuffers() const
{
	return _2dBuffers;
}

const map<array<string, 6>, shared_ptr<TextureBuffer>>& TextureBufferCache::get3dBuffers() const
{
	return _3dBuffers;
}
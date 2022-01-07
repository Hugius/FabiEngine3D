#include "texture_buffer_cache.hpp"

#include "logger.hpp"

void TextureBufferCache::storeBuffer(const string& filePath, shared_ptr<TextureBuffer> buffer)
{
	auto cacheIterator = _2dBuffers.find(filePath);

	if(cacheIterator != _2dBuffers.end())
	{
		Logger::throwError("");
	}

	_2dBuffers.insert(make_pair(filePath, buffer));
}

void TextureBufferCache::storeBuffer(const array<string, 6>& filePaths, shared_ptr<TextureBuffer> buffer)
{
	auto cacheIterator = _3dBuffers.find(filePaths);

	if(cacheIterator != _3dBuffers.end())
	{
		Logger::throwError("");
	}

	_3dBuffers.insert(make_pair(filePaths, buffer));
}

void TextureBufferCache::deleteBuffer(const string& filePath)
{
	if(_2dBuffers.find(filePath) != _2dBuffers.end())
	{
		_2dBuffers.erase(filePath);
	}
}

void TextureBufferCache::deleteBuffer(const array<string, 6>& filePaths)
{
	if(_3dBuffers.find(filePaths) != _3dBuffers.end())
	{
		_3dBuffers.erase(filePaths);
	}
}

void TextureBufferCache::clear()
{
	_2dBuffers.clear();
	_3dBuffers.clear();
}

const shared_ptr<TextureBuffer> TextureBufferCache::getBuffer(const string& filePath) const
{
	auto cacheIterator = _2dBuffers.find(filePath);

	if(cacheIterator != _2dBuffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const shared_ptr<TextureBuffer> TextureBufferCache::getBuffer(const array<string, 6>& filePaths) const
{
	auto cacheIterator = _3dBuffers.find(filePaths);

	if(cacheIterator != _3dBuffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const vector<shared_ptr<TextureBuffer>> TextureBufferCache::getBuffers() const
{
	vector<shared_ptr<TextureBuffer>> result;

	for(const auto& [filePath, buffer] : _2dBuffers)
	{
		result.push_back(buffer);
	}

	for(const auto& [filePaths, buffer] : _3dBuffers)
	{
		result.push_back(buffer);
	}

	return result;
}
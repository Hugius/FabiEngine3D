#include "texture_buffer_cache.hpp"
#include "tools.hpp"

void TextureBufferCache::store2dBuffer(const string & filePath, shared_ptr<TextureBuffer> buffer)
{
	auto cacheIterator = _2dBuffers.find(filePath);

	if(cacheIterator != _2dBuffers.end())
	{
		abort();
	}

	_2dBuffers.insert({filePath, buffer});
}

void TextureBufferCache::store3dBuffer(const array<string, 6> & filePaths, shared_ptr<TextureBuffer> buffer)
{
	const auto key = Tools::mergeStrings({filePaths[0], filePaths[1], filePaths[2], filePaths[3], filePaths[4], filePaths[5]}, DELIMITER);

	auto cacheIterator = _3dBuffers.find(key);

	if(cacheIterator != _3dBuffers.end())
	{
		abort();
	}

	_3dBuffers.insert({key, buffer});
}

void TextureBufferCache::delete2dBuffer(const string & filePath)
{
	if(_2dBuffers.find(filePath) == _2dBuffers.end())
	{
		abort();
	}

	_2dBuffers.erase(filePath);
}

void TextureBufferCache::delete3dBuffer(const array<string, 6> & filePaths)
{
	const auto key = Tools::mergeStrings({filePaths[0], filePaths[1], filePaths[2], filePaths[3], filePaths[4], filePaths[5]}, DELIMITER);

	if(_3dBuffers.find(key) == _3dBuffers.end())
	{
		abort();
	}

	_3dBuffers.erase(key);
}

void TextureBufferCache::clear2dBuffers()
{
	_2dBuffers.clear();
}

void TextureBufferCache::clear3dBuffers()
{
	_3dBuffers.clear();
}

const shared_ptr<TextureBuffer> TextureBufferCache::get2dBuffer(const string & filePath) const
{
	auto cacheIterator = _2dBuffers.find(filePath);

	if(cacheIterator != _2dBuffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const shared_ptr<TextureBuffer> TextureBufferCache::get3dBuffer(const array<string, 6> & filePaths) const
{
	const auto key = Tools::mergeStrings({filePaths[0], filePaths[1], filePaths[2], filePaths[3], filePaths[4], filePaths[5]}, DELIMITER);

	auto cacheIterator = _3dBuffers.find(key);

	if(cacheIterator != _3dBuffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const unordered_map<string, shared_ptr<TextureBuffer>> & TextureBufferCache::get2dBuffers() const
{
	return _2dBuffers;
}

const unordered_map<string, shared_ptr<TextureBuffer>> & TextureBufferCache::get3dBuffers() const
{
	return _3dBuffers;
}

const vector<string> TextureBufferCache::get2dFilePaths() const
{
	vector<string> result;

	for(const auto & [key, buffer] : _2dBuffers)
	{
		result.push_back(key);
	}

	return result;
}

const vector<array<string, 6>> TextureBufferCache::get3dFilePaths() const
{
	vector<array<string, 6>> result;

	for(const auto & [key, buffer] : _3dBuffers)
	{
		const auto splitKey = Tools::splitStringIntoMultiple(key, DELIMITER);

		result.push_back({splitKey[0], splitKey[1], splitKey[2], splitKey[3], splitKey[4], splitKey[5]});
	}

	return result;
}
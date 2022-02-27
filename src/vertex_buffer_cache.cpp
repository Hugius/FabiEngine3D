#include "vertex_buffer_cache.hpp"
#include "tools.hpp"

void VertexBufferCache::storeBuffer(const string& filePath, const string& partId, shared_ptr<VertexBuffer> buffer)
{
	const auto key = Tools::mergeStrings(filePath, partId, DELIMITER);

	auto cacheIterator = _buffers.find(key);

	if(cacheIterator != _buffers.end())
	{
		abort();
	}

	_buffers.insert({key, buffer});
}

void VertexBufferCache::deleteBuffer(const string& filePath, const string& partId)
{
	const auto key = Tools::mergeStrings(filePath, partId, DELIMITER);

	if(_buffers.find(key) == _buffers.end())
	{
		abort();
	}

	_buffers.erase(key);
}

void VertexBufferCache::clearBuffers()
{
	_buffers.clear();
}

const shared_ptr<VertexBuffer> VertexBufferCache::getBuffer(const string& filePath, const string& partId) const
{
	const auto key = Tools::mergeStrings(filePath, partId, DELIMITER);

	auto cacheIterator = _buffers.find(key);

	if(cacheIterator != _buffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const unordered_map<string, shared_ptr<VertexBuffer>>& VertexBufferCache::getBuffers() const
{
	return _buffers;
}

const vector<string> VertexBufferCache::getFilePaths() const
{
	vector<string> result;

	for(const auto& [key, buffer] : _buffers)
	{
		const auto splitKey = Tools::splitStringIntoTwo(key, DELIMITER);

		result.push_back(splitKey.first);
	}

	return result;
}

const vector<string> VertexBufferCache::getPartIds(const string& filePath) const
{
	vector<string> result;

	for(const auto& [key, buffer] : _buffers)
	{
		const auto splitKey = Tools::splitStringIntoTwo(key, DELIMITER);

		if(filePath == splitKey.first)
		{
			result.push_back(splitKey.second);
		}
	}

	return result;
}
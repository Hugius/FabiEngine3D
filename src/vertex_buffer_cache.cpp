#include "vertex_buffer_cache.hpp"
#include "tools.hpp"

void VertexBufferCache::storeBuffer(const string & filePath, const string & partId, shared_ptr<VertexBuffer> buffer)
{
	const auto mergedId = Tools::mergeStrings(filePath, partId, DELIMITER);
	const auto cacheIterator = _buffers.find(mergedId);

	if(cacheIterator != _buffers.end())
	{
		abort();
	}

	_buffers.insert({mergedId, buffer});
}

void VertexBufferCache::deleteBuffer(const string & filePath, const string & partId)
{
	const auto mergedId = Tools::mergeStrings(filePath, partId, DELIMITER);

	if(_buffers.find(mergedId) == _buffers.end())
	{
		abort();
	}

	_buffers.erase(mergedId);
}

void VertexBufferCache::clearBuffers()
{
	_buffers.clear();
}

const shared_ptr<VertexBuffer> VertexBufferCache::getBuffer(const string & filePath, const string & partId) const
{
	const auto mergedId = Tools::mergeStrings(filePath, partId, DELIMITER);
	const auto cacheIterator = _buffers.find(mergedId);

	if(cacheIterator != _buffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const unordered_map<string, shared_ptr<VertexBuffer>> & VertexBufferCache::getBuffers() const
{
	return _buffers;
}

const vector<string> VertexBufferCache::getFilePaths() const
{
	vector<string> result = {};

	for(const auto & [mergedId, buffer] : _buffers)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		result.push_back(splitKey.first);
	}

	return result;
}

const vector<string> VertexBufferCache::getPartIds(const string & filePath) const
{
	vector<string> result = {};

	for(const auto & [mergedId, buffer] : _buffers)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);

		if(filePath == splitKey.first)
		{
			result.push_back(splitKey.second);
		}
	}

	return result;
}
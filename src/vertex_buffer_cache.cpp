#include "vertex_buffer_cache.hpp"
#include "tools.hpp"

void VertexBufferCache::storeBuffer(const string& filePath, const string& partId, shared_ptr<VertexBuffer> buffer)
{
	auto cacheIterator = _buffers.find(Tools::mergeStrings(filePath, partId, DELIMITER));

	if(cacheIterator != _buffers.end())
	{
		abort();
	}

	_buffers.insert(make_pair(Tools::mergeStrings(filePath, partId, DELIMITER), buffer));
}

void VertexBufferCache::deleteBuffer(const string& filePath, const string& partId)
{
	if(_buffers.find(Tools::mergeStrings(filePath, partId, DELIMITER)) != _buffers.end())
	{
		_buffers.erase(Tools::mergeStrings(filePath, partId, DELIMITER));
	}
}

void VertexBufferCache::clear()
{
	_buffers.clear();
}

const shared_ptr<VertexBuffer> VertexBufferCache::getBuffer(const string& filePath, const string& partId) const
{
	auto cacheIterator = _buffers.find(Tools::mergeStrings(filePath, partId, DELIMITER));

	if(cacheIterator != _buffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const vector<string> VertexBufferCache::getPartIds(const string& filePath) const
{
	vector<string> result;

	for(const auto& [key, buffer] : _buffers)
	{
		const auto splitKey = Tools::splitString(key, DELIMITER);

		if(filePath == splitKey.first)
		{
			result.push_back(splitKey.second);
		}
	}

	return result;
}
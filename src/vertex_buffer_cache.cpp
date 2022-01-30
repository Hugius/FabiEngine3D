#include "vertex_buffer_cache.hpp"

#include "logger.hpp"

void VertexBufferCache::storeBuffer(const string& filePath, const string& partId, shared_ptr<VertexBuffer> buffer)
{
	auto cacheIterator = _buffers.find(make_pair(filePath, partId));

	if(cacheIterator != _buffers.end())
	{
		abort();
	}

	_buffers.insert(make_pair(make_pair(filePath, partId), buffer));
}

void VertexBufferCache::deleteBuffer(const string& filePath, const string& partId)
{
	if(_buffers.find(make_pair(filePath, partId)) != _buffers.end())
	{
		_buffers.erase(make_pair(filePath, partId));
	}
}

void VertexBufferCache::clear()
{
	_buffers.clear();
}

const shared_ptr<VertexBuffer> VertexBufferCache::getBuffer(const string& filePath, const string& partId) const
{
	auto cacheIterator = _buffers.find(make_pair(filePath, partId));

	if(cacheIterator != _buffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const map<pair<string, string>, shared_ptr<VertexBuffer>> VertexBufferCache::getBuffers() const
{
	return _buffers;
}
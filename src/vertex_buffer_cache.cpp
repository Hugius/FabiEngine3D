#include "vertex_buffer_cache.hpp"

#include "logger.hpp"

void VertexBufferCache::storeBuffer(const string& ID, shared_ptr<VertexBuffer> buffer)
{
	auto cacheIterator = _cache.find(ID);

	if(cacheIterator != _cache.end())
	{
		Logger::throwError("");
	}

	_cache.insert(make_pair(ID, buffer));
}

const shared_ptr<VertexBuffer> VertexBufferCache::getBuffer(const string& ID) const
{
	auto cacheIterator = _cache.find(ID);

	if(cacheIterator != _cache.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const map<string, shared_ptr<VertexBuffer>>& VertexBufferCache::getBuffers() const
{
	return _cache;
}
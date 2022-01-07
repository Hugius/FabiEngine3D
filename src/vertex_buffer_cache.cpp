#include "vertex_buffer_cache.hpp"

#include "logger.hpp"

void VertexBufferCache::storeBuffer(const string& filePath, const string& partID, shared_ptr<VertexBuffer> buffer)
{
	auto cacheIterator = _buffers.find(make_pair(filePath, partID));

	if(cacheIterator != _buffers.end())
	{
		Logger::throwError("");
	}

	_buffers.insert(make_pair(make_pair(filePath, partID), buffer));
}

const shared_ptr<VertexBuffer> VertexBufferCache::getBuffer(const string& filePath, const string& partID) const
{
	auto cacheIterator = _buffers.find(make_pair(filePath, partID));

	if(cacheIterator != _buffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const vector<shared_ptr<VertexBuffer>> VertexBufferCache::getBuffers() const
{
	vector<shared_ptr<VertexBuffer>> result;

	for(const auto& [ID, buffer] : _buffers)
	{
		result.push_back(buffer);
	}

	return result;
}
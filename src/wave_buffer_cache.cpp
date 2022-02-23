#include "wave_buffer_cache.hpp"

void WaveBufferCache::storeBuffer(const string& filePath, shared_ptr<WaveBuffer> buffer)
{
	auto cacheIterator = _buffers.find(filePath);

	if(cacheIterator != _buffers.end())
	{
		abort();
	}

	_buffers.insert(make_pair(filePath, buffer));
}

void WaveBufferCache::deleteBuffer(const string& filePath)
{
	if(_buffers.find(filePath) == _buffers.end())
	{
		abort();
	}

	_buffers.erase(filePath);
}

void WaveBufferCache::clearBuffers()
{
	_buffers.clear();
}

const shared_ptr<WaveBuffer> WaveBufferCache::getBuffer(const string& filePath) const
{
	auto cacheIterator = _buffers.find(filePath);

	if(cacheIterator != _buffers.end())
	{
		return cacheIterator->second;
	}

	return nullptr;
}

const unordered_map<string, shared_ptr<WaveBuffer>>& WaveBufferCache::getBuffers() const
{
	return _buffers;
}

const vector<string> WaveBufferCache::getFilePaths() const
{
	vector<string> result;

	for(const auto& [key, buffer] : _buffers)
	{
		result.push_back(key);
	}

	return result;
}
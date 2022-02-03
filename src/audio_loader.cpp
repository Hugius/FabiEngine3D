#include "audio_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>
#include <future>
#include <set>
#include <fstream>

using std::reverse;
using std::transform;
using std::set;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::future;
using std::launch;

AudioLoader::~AudioLoader()
{
	for(const auto& element : _cache)
	{
		Mix_FreeChunk(element.second);
	}
}

void AudioLoader::cacheChunk(const string& filePath)
{
	loadChunk(filePath);
}

void AudioLoader::cacheChunks(const vector<string>& filePaths)
{
	vector<future<const char*>> threads;
	vector<bool> cacheStatuses;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		if(_cache.find(filePath) == _cache.end())
		{
			threads.push_back(async(launch::async, &AudioLoader::_loadWaveFile, this, filePath));
			cacheStatuses.push_back(false);
		}
		else
		{
			cacheStatuses.push_back(true);
		}
	}

	for(size_t i = 0; i < threads.size(); i++)
	{
		if(!cacheStatuses[i])
		{
			auto loadedData = threads[i].get();

			if(loadedData == nullptr)
			{
				Logger::throwWarning("Cannot load audio: \"", uniqueFilePaths[i], "\"");
				continue;
			}

			auto loadedChunk = _loadChunk(uniqueFilePaths[i], (unsigned char*)loadedData);

			if(loadedChunk != nullptr)
			{
				_throwLoadedMessage(uniqueFilePaths[i]);

				_cache.insert(make_pair(uniqueFilePaths[i], loadedChunk));
			}
		}
	}
}

Mix_Chunk* AudioLoader::loadChunk(const string& filePath)
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return cacheIterator->second;
	}

	auto data = _loadWaveFile(filePath);

	if(data == nullptr)
	{
		Logger::throwWarning("Cannot load audio: \"", filePath, "\"");
		return nullptr;
	}

	auto chunk = _loadChunk(filePath, (unsigned char*)data);

	if(chunk == nullptr)
	{
		return nullptr;
	}

	_throwLoadedMessage(filePath);

	_cache.insert(make_pair(filePath, chunk));

	return chunk;
}

void AudioLoader::clearChunkCache(const string& filePath)
{
	if(_cache.find(filePath) != _cache.end())
	{
		_cache.erase(filePath);
	}
}

void AudioLoader::clearChunksCache()
{
	_cache.clear();
}

Mix_Chunk* AudioLoader::_loadChunk(const string& filePath, unsigned char* data) const
{
	Mix_Chunk* chunk = Mix_QuickLoad_WAV(data);

	if(chunk == nullptr)
	{
		Logger::throwWarning("Cannot load audio: \"", filePath, "\"");
	}

	return chunk;
}

void AudioLoader::_throwLoadedMessage(const string& filePath)
{
	Logger::throwInfo("Loaded audio: \"" + filePath + "\"");
}

const char* AudioLoader::_loadWaveFile(const string& filePath) const
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto fullFilePath = string(rootPath + filePath);

	auto file = ifstream(fullFilePath, ios::binary);
	if(!file)
	{
		return nullptr;
	}

	file.seekg(0, ios::end);

	const auto dataSize = static_cast<unsigned int>(file.tellg());
	auto data = new char[dataSize];

	file.seekg(0, ios::beg);

	file.read(data, dataSize);

	file.close();

	return data;
}
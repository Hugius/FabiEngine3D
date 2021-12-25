#include "audio_loader.hpp"
#include "audio_loader.hpp"
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
	for(const auto& element : _chunkCache)
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
	vector<bool> threadStatuses;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		// Check if chunk is not already cached
		if(_chunkCache.find(filePath) == _chunkCache.end())
		{
			threads.push_back(async(launch::async, &AudioLoader::_loadWaveFile, this, filePath));
			threadStatuses.push_back(false);
		}
		else
		{
			threadStatuses.push_back(true);
		}
	}

	for(size_t i = 0; i < threads.size(); i++)
	{
		// Check if chunk is not processed yet
		if(!threadStatuses[i])
		{
			// Retrieve return value
			auto loadedData = threads[i].get();

			// Check if data loading failed
			if(loadedData == nullptr)
			{
				Logger::throwWarning("Cannot load audio: \"", uniqueFilePaths[i], "\"!");
			}
			else
			{
				// Load chunk file
				auto loadedChunk = _loadChunk(uniqueFilePaths[i], (unsigned char*)loadedData);

				// Check if chunk loading went well
				if(loadedChunk != nullptr)
				{
					// Logging
					_throwLoadedMessage(uniqueFilePaths[i]);

					// Cache chunk
					_chunkCache[uniqueFilePaths[i]] = loadedChunk;
				}
			}
		}
	}
}

Mix_Chunk* AudioLoader::loadChunk(const string& filePath)
{
	BEGIN:;
	auto cacheIterator = _chunkCache.find(filePath);

	if(cacheIterator != _chunkCache.end())
	{
		return cacheIterator->second;
	}

	auto data = _loadWaveFile(filePath);

	if(data == nullptr)
	{
		Logger::throwWarning("Cannot load audio: \"", filePath, "\"!");
		return nullptr;
	}
	else
	{
		// Load chunk file
		auto chunk = _loadChunk(filePath, (unsigned char*)data);

		// Check if chunk loading failed
		if(chunk == nullptr)
		{
			return nullptr;
		}
		else
		{
			// Logging
			_throwLoadedMessage(filePath);

			// Cache chunk
			_chunkCache.insert(make_pair(filePath, chunk));

			// Return cached chunk
			goto BEGIN;
		}
	}
}

void AudioLoader::clearChunkCache(const string& filePath)
{
	if(_chunkCache.find(filePath) != _chunkCache.end())
	{
		_chunkCache.erase(filePath);
	}
}

void AudioLoader::clearChunksCache()
{
	_chunkCache.clear();
}

Mix_Chunk* AudioLoader::_loadChunk(const string& filePath, unsigned char* data) const
{
	Mix_Chunk* chunk = Mix_QuickLoad_WAV(data);

	if(chunk == nullptr)
	{
		Logger::throwWarning("Cannot load audio: \"", filePath, "\"!");
	}

	return chunk;
}

void AudioLoader::_throwLoadedMessage(const string& filePath)
{
	Logger::throwInfo("Loaded audio: \"" + filePath + "\"");
}

const char* AudioLoader::_loadWaveFile(const string& filePath) const
{
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();
	auto fullFilePath = string(rootDirectoryPath + filePath);

	ifstream file(fullFilePath.c_str(), ios::binary);
	if(!file)
	{
		return nullptr;
	}

	file.seekg(0, ios::end);

	auto dataSize = (DWORD)file.tellg();

	auto data = new char[dataSize];

	file.seekg(0, ios::beg);

	file.read(data, dataSize);

	file.close();

	return data;
}
#include "audio_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>
#include <future>
#include <set>

AudioLoader::~AudioLoader()
{
	for (auto& element : _chunkCache)
	{
		Mix_FreeChunk(element.second);
	}
}

void AudioLoader::cacheChunksMultiThreaded(const vector<string>& filePaths)
{
	//// Temporary values
	//vector<std::future<Mix_Chunk*>> threads;

	//// Remove duplicates
	//auto tempFilePaths = std::set<string>(filePaths.begin(), filePaths.end());
	//auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	//// Start all loading threads
	//for (const auto& filePath : uniqueFilePaths)
	//{
	//	threads.push_back(std::async(std::launch::async, &AudioLoader::_loadChunk, this, filePath));
	//}

	//// Wait for all threads to finish
	//for (unsigned int i = 0; i < threads.size(); i++)
	//{
	//	auto objParts = threads[i].get();

	//	// Check if model loading went well
	//	if (!objParts.empty())
	//	{
	//		// Logging
	//		Logger::throwInfo("Loaded OBJ model: \"" + uniqueFilePaths[i] + "\"");

	//		// Cache model
	//		_objCache[uniqueFilePaths[i]] = objParts;
	//	}
	//}
}

Mix_Chunk* AudioLoader::getChunk(const string& filePath)
{
begin:
	auto iterator = _chunkCache.find(filePath);
	if (iterator == _chunkCache.end()) // Not in map (yet)
	{
		// Load chunk file
		auto chunk = _loadChunk(filePath);

		// Check chunk status
		if (chunk == nullptr)
		{
			return nullptr;
		}
		else
		{
			auto reversed(filePath); // Copy
			std::reverse(reversed.begin(), reversed.end()); // Reverse, cuz . must be last in path
			auto extension = filePath.substr(filePath.size() - reversed.find("."), reversed.find(".")); // Substring file extension
			std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper); // Convert to uppercase
			Logger::throwInfo("Loaded ", extension, " audio file: \"" + filePath + "\""); // Logging

			// Cache chunk
			_chunkCache.insert(std::make_pair(filePath, chunk));

			// Return cached chunk
			goto begin;
		}
	}

	return iterator->second;
}

Mix_Music* AudioLoader::getMusic(const string& filePath)
{
	auto iterator = _musicCache.find(filePath);

	// Check if audio music was loaded already, if not, load data and store in std::map
	if (iterator == _musicCache.end())
	{
		// Get application root directory
		string rootDir = Tools::getInst().getRootDirectory();

		// Load audio file
		Mix_Music* music = Mix_LoadMUS((rootDir + filePath).c_str());

		if (music == nullptr) // Could not load file
		{
			Logger::throwWarning("Could not load audio file \"", filePath, "\"");
			return nullptr;
		}
		else // Successfully loaded file
		{
			auto reversed(filePath); // Copy
			std::reverse(reversed.begin(), reversed.end()); // Reverse, cuz . must be last in path
			auto extension = filePath.substr(filePath.size() - reversed.find("."), reversed.find(".")); // Substring file extension
			std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper); // Convert to uppercase
			Logger::throwInfo("Loaded ", extension, " audio file: \"" + filePath + "\""); // Log loaded
			_musicCache.insert(std::make_pair(filePath, music)); // Insert new data
			return music;
		}
	}
	else
	{
		return iterator->second; // Return the corresponding OBJ parts
	}
}

void AudioLoader::clearChunkCache(const string& filePath)
{
	if (_chunkCache.find(filePath) != _chunkCache.end())
	{
		_chunkCache.erase(filePath);
	}
}

void AudioLoader::clearMusicCache(const string& filePath)
{
	if (_musicCache.find(filePath) != _musicCache.end())
	{
		_musicCache.erase(filePath);
	}
}

Mix_Chunk* AudioLoader::_loadChunk(const string& filePath)
{
	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();

	// Load audio file
	Mix_Chunk* chunk = Mix_LoadWAV((rootDir + filePath).c_str());
	if (chunk == nullptr)
	{
		Logger::throwWarning("Could not load audio file \"", filePath, "\"");
	}

	return chunk;
}

Mix_Music* AudioLoader::_loadMusic(const string& filePath)
{
	return nullptr;
}
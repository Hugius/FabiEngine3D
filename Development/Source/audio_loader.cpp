#include "audio_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>
#include <future>
#include <set>
#include <fstream>

AudioLoader::~AudioLoader()
{
	// Delete chunks
	for (auto& element : _chunkCache)
	{
		Mix_FreeChunk(element.second);
	}

	// Delete music
	for (auto& element : _musicCache)
	{
		Mix_FreeMusic(element.second);
	}
}

void AudioLoader::cacheChunksMultiThreaded(const vector<string>& filePaths)
{
	// Temporary values
	vector<std::future<char*>> threads;
	vector<bool> chunkStatuses;

	// Remove duplicates
	auto tempFilePaths = std::set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for (const auto& filePath : uniqueFilePaths)
	{
		// Check if chunk is not already cached
		if (_chunkCache.find(filePath) == _chunkCache.end())
		{
			threads.push_back(std::async(std::launch::async, &AudioLoader::_loadWaveFile, this, filePath));
			chunkStatuses.push_back(false);
		}
		else
		{
			chunkStatuses.push_back(true);
		}
	}

	// Wait for all threads to finish
	for (unsigned int i = 0; i < threads.size(); i++)
	{
		// Check if chunk is not processed yet
		if (!chunkStatuses[i])
		{
			// Retrieve raw WAV data
			auto data = threads[i].get();

			// Check data status
			if (data == nullptr)
			{
				Logger::throwWarning("Could not load audio file \"", uniqueFilePaths[i], "\"");
			}
			else
			{
				// Load chunk file
				auto chunk = _loadChunk(uniqueFilePaths[i], (unsigned char*)data);

				// Check chunk status
				if (chunk != nullptr)
				{
					// Logging
					_throwLoadedMessage(uniqueFilePaths[i]);

					// Cache chunk
					_chunkCache[uniqueFilePaths[i]] = chunk;
				}
			}
		}
	}
}

Mix_Chunk* AudioLoader::getChunkDataPointer(const string& filePath)
{
begin:
	auto iterator = _chunkCache.find(filePath);
	if (iterator == _chunkCache.end()) // Not in map (yet)
	{
		// Load raw WAV data
		auto data = _loadWaveFile(filePath);

		// Check data status
		if (data == nullptr)
		{
			Logger::throwWarning("Could not load audio file \"", filePath, "\"");
		}
		else
		{
			// Load chunk file
			auto chunk = _loadChunk(filePath, (unsigned char*)data);

			// Check chunk status
			if (chunk == nullptr)
			{
				return nullptr;
			}
			else
			{
				// Logging
				_throwLoadedMessage(filePath);

				// Cache chunk
				_chunkCache.insert(std::make_pair(filePath, chunk));

				// Return cached chunk
				goto begin;
			}
		}
	}

	return iterator->second;
}

Mix_Music* AudioLoader::getMusicDataPointer(const string& filePath)
{
begin:
	auto iterator = _musicCache.find(filePath);
	if (iterator == _musicCache.end()) // Not in map (yet)
	{
		// Get application root directory
		string rootDir = Tools::getInst().getRootDirectory();

		// Load audio file
		Mix_Music* music = Mix_LoadMUS((rootDir + filePath).c_str());

		// Check music status
		if (music == nullptr)
		{
			Logger::throwWarning("Could not load audio file \"", filePath, "\"");
			return nullptr;
		}
		else
		{
			// Logging
			_throwLoadedMessage(filePath);

			// Cache music
			_musicCache.insert(std::make_pair(filePath, music));

			// Return cached music
			goto begin;
		}
	}
	else
	{
		return iterator->second; // Return the corresponding mesh parts
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

Mix_Chunk* AudioLoader::_loadChunk(const string& filePath, unsigned char* data)
{
	// Load RAW audio data into an SDL chunk
	Mix_Chunk* chunk = Mix_QuickLoad_WAV(data);
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

void AudioLoader::_throwLoadedMessage(const string& filePath)
{
	auto reversed(filePath); // Copy
	std::reverse(reversed.begin(), reversed.end()); // Reverse, because . must be last in path
	auto extension = filePath.substr(filePath.size() - reversed.find("."), reversed.find(".")); // Substring file extension
	std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper); // Convert to uppercase
	Logger::throwInfo("Loaded ", extension, " audio file: \"" + filePath + "\""); // Log message
}

char* AudioLoader::_loadWaveFile(const std::string& filePath)
{
	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();
	auto fullFilePath = string(rootDir + filePath);

	// Open WAV file
	std::ifstream file(fullFilePath.c_str(), std::ios::binary);
	if (!file)
	{
		return nullptr;
	}

	// Go the end of file position
	file.seekg(0, std::ios::end);

	// Store the size of the whole file in bytes
	auto dataSize = (DWORD)file.tellg();

	// Allocate memory for the raw audio data
	auto data = new char[dataSize];       

	// Reset file position
	file.seekg(0, std::ios::beg);

	// Store the whole WAVE file data in the data array
	file.read(data, dataSize);

	// Close file reading
	file.close();

	// Return
	return data;
}
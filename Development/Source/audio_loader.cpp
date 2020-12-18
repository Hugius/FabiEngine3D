#include "audio_loader.hpp"
#include "logger.hpp"

#include <algorithm>

AudioLoader::~AudioLoader()
{
	for (auto& element : _chunkCache)
	{
		Mix_FreeChunk(element.second);
	}
}

Mix_Chunk* AudioLoader::getChunk(const string& filePath)
{
	auto iterator = _chunkCache.find(filePath);

	// Check if audio chunk was loaded already, if not, load data and store in std::map
	if (iterator == _chunkCache.end())
	{
		// Get application root directory
		char buffer[256]; size_t len = sizeof(buffer);
		GetModuleFileName(NULL, buffer, len);
		string rootDir = buffer;
		rootDir = rootDir.substr(0, rootDir.size() - string("bin\\FabiEngine3D.exe").size());
		
		// Load audio file
		Mix_Chunk* chunk = Mix_LoadWAV((rootDir + filePath).c_str());

		if (chunk == nullptr) // Could not load file
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
			_chunkCache.insert(std::make_pair(filePath, chunk)); // Insert new data
			return chunk;
		}
	}
	else
	{
		return iterator->second; // Return the corresponding OBJ parts
	}
}

Mix_Music* AudioLoader::getMusic(const string& filePath)
{
	auto iterator = _musicCache.find(filePath);

	// Check if audio music was loaded already, if not, load data and store in std::map
	if (iterator == _musicCache.end())
	{
		// Get application root directory
		char buffer[256]; size_t len = sizeof(buffer);
		GetModuleFileName(NULL, buffer, len);
		string rootDir = buffer;
		rootDir = rootDir.substr(0, rootDir.size() - string("bin\\FabiEngine3D.exe").size());

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
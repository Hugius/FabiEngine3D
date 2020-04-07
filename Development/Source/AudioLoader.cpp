#include <algorithm>

#include "AudioLoader.hpp"
#include "Logger.hpp"

AudioLoader::~AudioLoader()
{
	for (auto& element : _chunkMap)
	{
		Mix_FreeChunk(element.second);
	}
}

Mix_Chunk* AudioLoader::getChunk(const string& filePath)
{
	// Check if audio chunk was loaded already, if not, load data and store in std::map
	auto iterator = _chunkMap.find(filePath);

	if (iterator == _chunkMap.end())
	{
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());

		if (chunk == nullptr) // Could not load file
		{
			Logger::getInst().throwError("Could not load audio file \'", filePath, "\': " + string(SDL_GetError()));
		}
		else // Successfully loaded file
		{
			auto reversed(filePath); // Copy
			std::reverse(reversed.begin(), reversed.end()); // Reverse, cuz . must be last in path
			auto extension = filePath.substr(filePath.size() - reversed.find("."), reversed.find(".")); // Substring file extension
			std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper); // Convert to uppercase
			Logger::getInst().throwInfo("Loaded ", extension, " audio file: " + filePath); // Log loaded
			_chunkMap.insert(std::make_pair(filePath, chunk)); // Insert new data
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
	// Check if audio music was loaded already, if not, load data and store in std::map
	auto iterator = _musicMap.find(filePath);

	if (iterator == _musicMap.end())
	{
		Mix_Music* music = Mix_LoadMUS(filePath.c_str());

		if (music == nullptr) // Could not load file
		{
			Logger::getInst().throwError("Could not load audio file \'", filePath, "\': " + string(SDL_GetError()));
		}
		else // Successfully loaded file
		{
			auto reversed(filePath); // Copy
			std::reverse(reversed.begin(), reversed.end()); // Reverse, cuz . must be last in path
			auto extension = filePath.substr(filePath.size() - reversed.find("."), reversed.find(".")); // Substring file extension
			std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper); // Convert to uppercase
			Logger::getInst().throwInfo("Loaded ", extension, " audio file: " + filePath); // Log loaded
			_musicMap.insert(std::make_pair(filePath, music)); // Insert new data
			return music;
		}
	}
	else
	{
		return iterator->second; // Return the corresponding OBJ parts
	}
}

#include "audio_manager.hpp"
#include "logger.hpp"

#include <algorithm>

AudioManager::AudioManager(AudioLoader& audioLoader) :
	_audioLoader(audioLoader)
{

}

void AudioManager::deleteMusic()
{
	_musicList.clear();
}

void AudioManager::deleteAllChunks()
{
	_chunks.clear();
}

void AudioManager::addMusic(const string& fileName)
{
	_musicList.push_back(AudioMusic(_audioLoader.getMusic(fileName)));
}

void AudioManager::add2D(const std::string& ID, const std::string& fileName)
{
	_checkValidAdd(ID);
	_chunks.push_back(AudioChunk(ID, fileName, _audioLoader.getChunk(fileName)));
}

void AudioManager::add3D(const std::string& ID, const std::string& fileName, Vec3 position, float maxVolume, float maxDistance)
{
	_checkValidAdd(ID);
	_chunks.push_back(AudioChunk(ID, fileName, _audioLoader.getChunk(fileName), position, maxVolume, maxDistance));
}

void AudioManager::deleteChunk(const std::string& ID)
{
	auto index = _findIndex(ID);

	if (index == -1) // Does not exist
	{
		Logger::throwError("Tried to remove nonexisting audio chunk with ID \'", ID, "\'!");
	}
	else // Remove chunk
	{
		_chunks.erase(_chunks.begin() + index);
	}
}

bool AudioManager::isChunkExisting(const string& ID)
{
	return _findIndex(ID) != -1;
}

AudioChunk& AudioManager::getChunk(const std::string& ID)
{
	auto index = _findIndex(ID);

	if (index == -1)
	{
		Logger::throwError("Tried to get nonexisting audio chunk with ID \'", ID, "\'!");
	}
	else
	{
		return _chunks[index];
	}
}

std::vector<AudioChunk>& AudioManager::getChunks()
{
	return _chunks;
}

std::vector<AudioMusic>& AudioManager::getMusic()
{
	return _musicList;
}

void AudioManager::_checkValidAdd(const std::string& ID)
{
	if (_findIndex(ID) != -1) // Already exists
	{
		Logger::throwError("Audio chunk with ID \'", ID, "\' already exists!");
	}
	else if (ID == "") // Empty ID
	{
		Logger::throwError("Tried to create audio chunk with empty ID!");
	}
}

int AudioManager::_findIndex(const std::string& ID)
{
	for (size_t i = 0; i < _chunks.size(); i++)
	{
		if (_chunks[i].getID() == ID)
		{
			return i;
		}
	}

	return -1;
}
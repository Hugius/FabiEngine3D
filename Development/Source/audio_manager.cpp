#include "audio_manager.hpp"
#include "logger.hpp"

#include <algorithm>

AudioManager::AudioManager(AudioLoader& audioLoader)
	:
	_audioLoader(audioLoader)
{

}

void AudioManager::deleteAllMusic()
{
	_musicList.clear();
}

void AudioManager::deleteAllSounds()
{
	_soundList.clear();
}

void AudioManager::createMusic(const string& filename)
{
	// Load data
	auto dataPointer = _audioLoader.loadMusic(filename);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_musicList.push_back(Music(dataPointer));
	}
}

void AudioManager::createSound(const string& ID, const string& filename)
{
	if(_findIndex(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound::1");
	}
	else if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(filename);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_soundList.push_back(Sound(ID, filename, dataPointer));
	}
}

void AudioManager::deleteSound(const string& ID)
{
	auto index = _findIndex(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::deleteSound");
	}
	else
	{
		_soundList.erase(_soundList.begin() + index);
	}
}

bool AudioManager::isSoundExisting(const string& ID)
{
	return _findIndex(ID) != -1;
}

Sound& AudioManager::getSound(const string& ID)
{
	auto index = _findIndex(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::getSound");
	}
	else
	{
		return _soundList[index];
	}
}

vector<Sound>& AudioManager::getSounds()
{
	return _soundList;
}

vector<Music>& AudioManager::getMusic()
{
	return _musicList;
}

int AudioManager::_findIndex(const string& ID)
{
	for(size_t i = 0; i < _soundList.size(); i++)
	{
		if(_soundList[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
#include "audio_manager.hpp"
#include "logger.hpp"

#include <algorithm>

AudioManager::AudioManager(AudioLoader& audioLoader)
	:
	_audioLoader(audioLoader)
{

}

void AudioManager::deleteMusic()
{
	_musicList.clear();
}

void AudioManager::deleteAllSounds()
{
	_soundList.clear();
}

void AudioManager::createMusic(const string& filename)
{
	_musicList.push_back(Music(_audioLoader.getMusicDataPointer(filename)));
}

void AudioManager::createSound(const string& ID, const string& filename)
{
	if (_findIndex(ID) != -1)
	{
		Logger::throwError("Sound with ID \"", ID, "\" already exists!");
	}
	else if (ID.empty())
	{
		Logger::throwError("Tried to create sound with empty ID!");
	}

	_soundList.push_back(Sound(ID, filename, _audioLoader.getChunkDataPointer(filename)));
}

void AudioManager::deleteSound(const string& ID)
{
	auto index = _findIndex(ID);

	if (index == -1)
	{
		Logger::throwError("Tried to remove non-existing sound with ID \"", ID, "\"!");
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

	if (index == -1)
	{
		Logger::throwError("Tried to get non-existing sound with ID \"", ID, "\"!");
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
	for (size_t i = 0; i < _soundList.size(); i++)
	{
		if (_soundList[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
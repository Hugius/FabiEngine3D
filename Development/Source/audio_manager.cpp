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
	_sounds.clear();
}

void AudioManager::addMusic(const string& fileName)
{
	_musicList.push_back(Music(_audioLoader.getMusicDataPointer(fileName)));
}

void AudioManager::addSound(const string& ID, const string& fileName)
{
	if (_findIndex(ID) != -1)
	{
		Logger::throwError("Sound with ID \"", ID, "\" already exists!");
	}
	else if (ID == "")
	{
		Logger::throwError("Tried to create sound with empty ID!");
	}

	_sounds.push_back(Sound(ID, fileName, _audioLoader.getChunkDataPointer(fileName)));
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
		_sounds.erase(_sounds.begin() + index);
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
		return _sounds[index];
	}
}

vector<Sound>& AudioManager::getSounds()
{
	return _sounds;
}

vector<Music>& AudioManager::getMusic()
{
	return _musicList;
}

int AudioManager::_findIndex(const string& ID)
{
	for (size_t i = 0; i < _sounds.size(); i++)
	{
		if (_sounds[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
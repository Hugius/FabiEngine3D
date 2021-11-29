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

void AudioManager::deleteSounds2D()
{
	_soundList2D.clear();
}

void AudioManager::deleteSounds3D()
{
	_soundList3D.clear();
}

void AudioManager::deleteSound3D(const string& ID)
{
	auto index = _findSoundIndex3D(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::deleteSound3D");
	}
	else
	{
		_soundList3D.erase(_soundList3D.begin() + index);
	}
}

void AudioManager::createMusic(const string& fileName)
{
	// Load data
	auto dataPointer = _audioLoader.loadMusic(fileName);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_musicList.push_back(Music(dataPointer));
	}
}

void AudioManager::createSound2D(const string& ID, const string& fileName)
{
	if(_findSoundIndex2D(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound2D::1");
	}
	else if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound2D::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(fileName);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_soundList2D.push_back(Sound2D(ID, fileName, dataPointer));
	}
}

void AudioManager::createSound3D(const string& ID, const string& fileName)
{
	if(_findSoundIndex3D(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound3D::1");
	}
	else if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound3D::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(fileName);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_soundList3D.push_back(Sound3D(ID, fileName, dataPointer));
	}
}

void AudioManager::deleteSound2D(const string& ID)
{
	auto index = _findSoundIndex2D(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::deleteSound2D");
	}
	else
	{
		_soundList2D.erase(_soundList2D.begin() + index);
	}
}

const bool AudioManager::isSoundExisting2D(const string& ID) const
{
	return (_findSoundIndex2D(ID) != -1);
}

const bool AudioManager::isSoundExisting3D(const string& ID) const
{
	return (_findSoundIndex3D(ID) != -1);
}

Sound2D& AudioManager::getSound2D(const string& ID)
{
	auto index = _findSoundIndex2D(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::getSound2D");
	}
	else
	{
		return _soundList2D[index];
	}
}

vector<Sound2D>& AudioManager::getSounds2D()
{
	return _soundList2D;
}

vector<Sound3D>& AudioManager::getSounds3D()
{
	return _soundList3D;
}

vector<Music>& AudioManager::getMusic()
{
	return _musicList;
}

Sound3D& AudioManager::getSound3D(const string& ID)
{
	auto index = _findSoundIndex3D(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::getSound3D");
	}
	else
	{
		return _soundList3D[index];
	}
}

const int AudioManager::_findSoundIndex2D(const string& ID) const
{
	for(size_t i = 0; i < _soundList2D.size(); i++)
	{
		if(_soundList2D[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

const int AudioManager::_findSoundIndex3D(const string& ID) const
{
	for(size_t i = 0; i < _soundList3D.size(); i++)
	{
		if(_soundList3D[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
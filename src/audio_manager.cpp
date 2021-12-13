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

void AudioManager::deleteAllSound2d()
{
	_sound2dList.clear();
}

void AudioManager::deleteAllSound3d()
{
	_sound3dList.clear();
}

void AudioManager::deleteSound3d(const string& ID)
{
	auto index = _findSound3dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::deleteSound3d");
	}
	else
	{
		_sound3dList.erase(_sound3dList.begin() + index);
	}
}

void AudioManager::update()
{
	for (auto& sound : _sound3dList)
	{
		sound.updateTransformation();
	}
}

void AudioManager::createMusic(const string& audioPath)
{
	// Load data
	auto dataPointer = _audioLoader.loadMusic(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_musicList.push_back(Music(audioPath, dataPointer));
	}
}

void AudioManager::createSound2d(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSound2dIndex(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound2d::1");
	}
	if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound2d::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sound2dList.push_back(Sound2d(ID, audioPath, dataPointer));
	}
}

void AudioManager::createSound3d(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSound3dIndex(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound3d::1");
	}
	if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound3d::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sound3dList.push_back(Sound3d(ID, audioPath, dataPointer));
	}
}

void AudioManager::deleteSound2d(const string& ID)
{
	auto index = _findSound2dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::deleteSound2d");
	}
	else
	{
		_sound2dList.erase(_sound2dList.begin() + index);
	}
}

const bool AudioManager::isSound2dExisting(const string& ID) const
{
	return (_findSound2dIndex(ID) != -1);
}

const bool AudioManager::isSound3dExisting(const string& ID) const
{
	return (_findSound3dIndex(ID) != -1);
}

Sound2d& AudioManager::getSound2d(const string& ID)
{
	auto index = _findSound2dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::getSound2d");
	}
	else
	{
		return _sound2dList[index];
	}
}

vector<Sound2d>& AudioManager::getAllSound2d()
{
	return _sound2dList;
}

vector<Sound3d>& AudioManager::getAllSound3d()
{
	return _sound3dList;
}

vector<Music>& AudioManager::getAllMusic()
{
	return _musicList;
}

Sound3d& AudioManager::getSound3d(const string& ID)
{
	auto index = _findSound3dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("AudioManager::getSound3d");
	}
	else
	{
		return _sound3dList[index];
	}
}

const int AudioManager::_findSound2dIndex(const string& ID) const
{
	for(size_t i = 0; i < _sound2dList.size(); i++)
	{
		if(_sound2dList[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

const int AudioManager::_findSound3dIndex(const string& ID) const
{
	for(size_t i = 0; i < _sound3dList.size(); i++)
	{
		if(_sound3dList[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
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
	_musics.clear();
}

void AudioManager::deleteSounds2D()
{
	_sounds2D.clear();
}

void AudioManager::deleteSounds3D()
{
	_sounds3D.clear();
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
		_sounds3D.erase(_sounds3D.begin() + index);
	}
}

void AudioManager::update()
{
	for (auto& sound : _sounds3D)
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
		_musics.push_back(Music(audioPath, dataPointer));
	}
}

void AudioManager::createSound2D(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSoundIndex2D(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound2D::1");
	}
	if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound2D::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sounds2D.push_back(Sound2D(ID, audioPath, dataPointer));
	}
}

void AudioManager::createSound3D(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSoundIndex3D(ID) != -1)
	{
		Logger::throwError("AudioManager::createSound3D::1");
	}
	if(ID.empty())
	{
		Logger::throwError("AudioManager::createSound3D::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sounds3D.push_back(Sound3D(ID, audioPath, dataPointer));
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
		_sounds2D.erase(_sounds2D.begin() + index);
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
		return _sounds2D[index];
	}
}

vector<Sound2D>& AudioManager::getSounds2D()
{
	return _sounds2D;
}

vector<Sound3D>& AudioManager::getSounds3D()
{
	return _sounds3D;
}

vector<Music>& AudioManager::getMusics()
{
	return _musics;
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
		return _sounds3D[index];
	}
}

const int AudioManager::_findSoundIndex2D(const string& ID) const
{
	for(size_t i = 0; i < _sounds2D.size(); i++)
	{
		if(_sounds2D[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

const int AudioManager::_findSoundIndex3D(const string& ID) const
{
	for(size_t i = 0; i < _sounds3D.size(); i++)
	{
		if(_sounds3D[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
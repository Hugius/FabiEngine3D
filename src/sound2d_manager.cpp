#include "sound2d_manager.hpp"
#include "logger.hpp"

#include <algorithm>

Sound2dManager::Sound2dManager(AudioLoader& audioLoader)
	:
	_audioLoader(audioLoader)
{

}

void Sound2dManager::deleteSounds()
{
	_sounds.clear();
}

void Sound2dManager::deleteSound(const string& ID)
{
	auto index = _findSoundIndex(ID);

	if(index == -1)
	{
		Logger::throwError("Sound2dManager::deleteSound");
	}
	else
	{
		_sounds.erase(_sounds.begin() + index);
	}
}

void Sound2dManager::update()
{

}

void Sound2dManager::createSound(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSoundIndex(ID) != -1)
	{
		Logger::throwError("Sound2dManager::createSound::1");
	}
	if(ID.empty())
	{
		Logger::throwError("Sound2dManager::createSound::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sounds.push_back(Sound2d(ID, audioPath, dataPointer));
	}
}

const bool Sound2dManager::isSoundExisting(const string& ID) const
{
	return (_findSoundIndex(ID) != -1);
}

vector<Sound2d>& Sound2dManager::getSounds()
{
	return _sounds;
}

Sound2d& Sound2dManager::getSound(const string& ID)
{
	auto index = _findSoundIndex(ID);

	if(index == -1)
	{
		Logger::throwError("Sound2dManager::getSound");
	}
	else
	{
		return _sounds[index];
	}
}

const int Sound2dManager::_findSoundIndex(const string& ID) const
{
	for(size_t i = 0; i < _sounds.size(); i++)
	{
		if(_sounds[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
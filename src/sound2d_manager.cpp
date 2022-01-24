#include "sound2d_manager.hpp"
#include "logger.hpp"

#include <algorithm>

void Sound2dManager::deleteSounds()
{
	_sounds.clear();
}

void Sound2dManager::deleteSound(const string& id)
{
	auto index = _findSoundIndex(id);

	if(index == -1)
	{
		Logger::throwError("Sound2dManager::deleteSound");
	}
	else
	{
		_sounds.erase(_sounds.begin() + index);
	}
}

void Sound2dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound2dManager::update()
{

}

void Sound2dManager::createSound(const string& id, const string& audioPath)
{
	if(_findSoundIndex(id) != -1)
	{
		Logger::throwError("Sound2dManager::createSound::1");
	}
	if(id.empty())
	{
		Logger::throwError("Sound2dManager::createSound::2");
	}

	auto dataPointer = _audioLoader->loadChunk(audioPath);

	if(dataPointer != nullptr)
	{
		_sounds.push_back(Sound2d(id, audioPath, dataPointer));
	}
}

const bool Sound2dManager::isSoundExisting(const string& id) const
{
	return (_findSoundIndex(id) != -1);
}

vector<Sound2d>& Sound2dManager::getSounds()
{
	return _sounds;
}

Sound2d& Sound2dManager::getSound(const string& id)
{
	auto index = _findSoundIndex(id);

	if(index == -1)
	{
		Logger::throwError("Sound2dManager::getSound");
	}
	else
	{
		return _sounds[index];
	}
}

const int Sound2dManager::_findSoundIndex(const string& id) const
{
	for(size_t i = 0; i < _sounds.size(); i++)
	{
		if(_sounds[i].getID() == id)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
#include "sound3d_manager.hpp"
#include "logger.hpp"

#include <algorithm>

void Sound3dManager::deleteSounds()
{
	_sounds.clear();
}

void Sound3dManager::deleteSound(const string& id)
{
	auto index = _findSoundIndex(id);

	if(index == -1)
	{
		Logger::throwError("Sound3dManager::deleteSound");
	}
	else
	{
		_sounds.erase(_sounds.begin() + index);
	}
}

void Sound3dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound3dManager::update()
{
	for(auto& sound : _sounds)
	{
		sound.updateTransformation();
	}
}

void Sound3dManager::createSound(const string& id, const string& audioPath)
{
	if(_findSoundIndex(id) != -1)
	{
		Logger::throwError("Sound3dManager::createSound::1");
	}
	if(id.empty())
	{
		Logger::throwError("Sound3dManager::createSound::2");
	}

	auto dataPointer = _audioLoader->loadChunk(audioPath);

	if(dataPointer != nullptr)
	{
		_sounds.push_back(Sound3d(id, audioPath, dataPointer));
	}
}

const bool Sound3dManager::isSoundExisting(const string& id) const
{
	return (_findSoundIndex(id) != -1);
}

vector<Sound3d>& Sound3dManager::getSounds()
{
	return _sounds;
}

Sound3d& Sound3dManager::getSound(const string& id)
{
	auto index = _findSoundIndex(id);

	if(index == -1)
	{
		Logger::throwError("Sound3dManager::getSound");
	}

	return _sounds[index];
}

const int Sound3dManager::_findSoundIndex(const string& id) const
{
	for(size_t i = 0; i < _sounds.size(); i++)
	{
		if(_sounds[i].getId() == id)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
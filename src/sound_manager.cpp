#include "sound_manager.hpp"
#include "logger.hpp"

#include <algorithm>

SoundManager::SoundManager(AudioLoader& audioLoader)
	:
	_audioLoader(audioLoader)
{

}

void SoundManager::deleteAllSound2d()
{
	_sound2ds.clear();
}

void SoundManager::deleteAllSound3d()
{
	_sound3ds.clear();
}

void SoundManager::deleteSound3d(const string& ID)
{
	auto index = _findSound3dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("SoundManager::deleteSound3d");
	}
	else
	{
		_sound3ds.erase(_sound3ds.begin() + index);
	}
}

void SoundManager::update()
{
	for (auto& sound : _sound3ds)
	{
		sound.updateTransformation();
	}
}

void SoundManager::createSound2d(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSound2dIndex(ID) != -1)
	{
		Logger::throwError("SoundManager::createSound2d::1");
	}
	if(ID.empty())
	{
		Logger::throwError("SoundManager::createSound2d::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sound2ds.push_back(Sound2d(ID, audioPath, dataPointer));
	}
}

void SoundManager::createSound3d(const string& ID, const string& audioPath)
{
	// Check for errors
	if(_findSound3dIndex(ID) != -1)
	{
		Logger::throwError("SoundManager::createSound3d::1");
	}
	if(ID.empty())
	{
		Logger::throwError("SoundManager::createSound3d::2");
	}

	// Load data
	auto dataPointer = _audioLoader.loadChunk(audioPath);

	// Check if data loading went well
	if(dataPointer != nullptr)
	{
		_sound3ds.push_back(Sound3d(ID, audioPath, dataPointer));
	}
}

void SoundManager::deleteSound2d(const string& ID)
{
	auto index = _findSound2dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("SoundManager::deleteSound2d");
	}
	else
	{
		_sound2ds.erase(_sound2ds.begin() + index);
	}
}

const bool SoundManager::isSound2dExisting(const string& ID) const
{
	return (_findSound2dIndex(ID) != -1);
}

const bool SoundManager::isSound3dExisting(const string& ID) const
{
	return (_findSound3dIndex(ID) != -1);
}

Sound2d& SoundManager::getSound2d(const string& ID)
{
	auto index = _findSound2dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("SoundManager::getSound2d");
	}
	else
	{
		return _sound2ds[index];
	}
}

vector<Sound2d>& SoundManager::getAllSound2ds()
{
	return _sound2ds;
}

vector<Sound3d>& SoundManager::getAllSound3ds()
{
	return _sound3ds;
}

Sound3d& SoundManager::getSound3d(const string& ID)
{
	auto index = _findSound3dIndex(ID);

	if(index == -1)
	{
		Logger::throwError("SoundManager::getSound3d");
	}
	else
	{
		return _sound3ds[index];
	}
}

const int SoundManager::_findSound2dIndex(const string& ID) const
{
	for(size_t i = 0; i < _sound2ds.size(); i++)
	{
		if(_sound2ds[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

const int SoundManager::_findSound3dIndex(const string& ID) const
{
	for(size_t i = 0; i < _sound3ds.size(); i++)
	{
		if(_sound3ds[i].getID() == ID)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}
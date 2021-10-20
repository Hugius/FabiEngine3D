#include "fe3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::sound_create(const string& ID, const string& filePath)
{
	_core->_audioManager.createSound(ID, filePath);
}

void FabiEngine3D::sound_make3D(const string& ID, Vec3 position, float maxVolume, float maxDistance)
{
	_core->_audioManager.getSound(ID).make3D(position, maxVolume, maxDistance);
}

void FabiEngine3D::sound_delete(const string& ID)
{
	// Check if chunk exists
	if (_core->_audioManager.isSoundExisting(ID))
	{
		// Stop before deleting
		if (_core->_audioPlayer.isSoundStarted(_core->_audioManager.getSound(ID)))
		{
			_core->_audioPlayer.stopSound(_core->_audioManager.getSound(ID), 0);
		}
	}

	// Delete sound
	_core->_audioManager.deleteSound(ID);
}

void FabiEngine3D::sound_deleteAll()
{
	// Stop before deleting
	sound_stopAll();

	// Delete sounds
	_core->_audioManager.deleteAllSounds();
}

void FabiEngine3D::sound_play(const string& ID, int loops, int fadeMS, bool forcePlay)
{
	auto sound = _core->_audioManager.getSound(ID);

	if (!_core->_audioPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if (_core->_audioPlayer.isSoundStarted(sound) && !forcePlay)
	{
		Logger::throwWarning("Tried to play sound with ID \"", ID, "\": sound is already started!");
		return;
	}
	
	_core->_audioPlayer.playSound(sound, loops, fadeMS, forcePlay);
}

void FabiEngine3D::sound_pause(const string& ID)
{
	auto sound = _core->_audioManager.getSound(ID);

	if (!_core->_audioPlayer.isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if (_core->_audioPlayer.isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_audioPlayer.pauseSound(sound);
}

void FabiEngine3D::sound_pauseAll()
{
	_core->_audioPlayer.pauseAllSounds();
}

void FabiEngine3D::sound_resume(const string& ID)
{
	auto sound = _core->_audioManager.getSound(ID);

	if (!_core->_audioPlayer.isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_audioPlayer.resumeSound(sound);
}

void FabiEngine3D::sound_resumeAll()
{
	_core->_audioPlayer.resumeAllSounds();
}

void FabiEngine3D::sound_stop(const string& ID, int fadeMS)
{
	auto sound = _core->_audioManager.getSound(ID);

	if (!_core->_audioPlayer.isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_audioPlayer.stopSound(sound, fadeMS);
}

void FabiEngine3D::sound_stopAll()
{
	_core->_audioPlayer.stopAllSounds();
}

void FabiEngine3D::sound_setVolume(const string& ID, float volume)
{
	_core->_audioManager.getSound(ID).setVolume(volume);
}

void FabiEngine3D::sound_setPosition(const string& ID, Vec3 position)
{
	_core->_audioManager.getSound(ID).setPosition(position);
}

void FabiEngine3D::sound_move(const string& ID, Vec3 change)
{
	_core->_audioManager.getSound(ID).move(change);
}

void FabiEngine3D::sound_setMaxDistance(const string& ID, float maxDistance)
{
	_core->_audioManager.getSound(ID).setMaxDistance(maxDistance);
}

void FabiEngine3D::sound_setMaxVolume(const string& ID, float volume)
{
	_core->_audioManager.getSound(ID).setMaxVolume(volume);
}

const vector<string> FabiEngine3D::sound_getAllIDs()
{
	vector<string> IDs;

	for (auto chunk : _core->_audioManager.getSounds())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

const string& FabiEngine3D::sound_getFilePath(const string& ID)
{
	return _core->_audioManager.getSound(ID).getFilePath();
}

const Vec3 FabiEngine3D::sound_getPosition(const string& ID)
{
	return _core->_audioManager.getSound(ID).getPosition();
}

const float FabiEngine3D::sound_getMaxDistance(const string& ID)
{
	return _core->_audioManager.getSound(ID).getMaxDistance();
}

const bool FabiEngine3D::sound_isExisting(const string& ID)
{
	return _core->_audioManager.isSoundExisting(ID);
}

const bool FabiEngine3D::sound_isStarted(const string& ID)
{
	return _core->_audioPlayer.isSoundStarted(_core->_audioManager.getSound(ID));
}

const bool FabiEngine3D::sound_isPlaying(const string& ID)
{
	return _core->_audioPlayer.isSoundPlaying(_core->_audioManager.getSound(ID));
}

const bool FabiEngine3D::sound_isPaused(const string& ID)
{
	return _core->_audioPlayer.isSoundPaused(_core->_audioManager.getSound(ID));
}

const bool FabiEngine3D::sound_isLoaded(const string& ID)
{
	return (_core->_audioManager.getSound(ID).getDataPointer() != nullptr);
}

const bool FabiEngine3D::sound_is3D(const string& ID)
{
	return _core->_audioManager.getSound(ID).is3D();
}

const float FabiEngine3D::sound_getVolume(const string& ID)
{
	return _core->_audioManager.getSound(ID).getVolume();
}

const float FabiEngine3D::sound_getMaxVolume(const string& ID)
{
	return _core->_audioManager.getSound(ID).getMaxVolume();
}

const unsigned int FabiEngine3D::sound_getUsedChannelCount()
{
	return _core->_audioPlayer.getUsedChannelCount();
}

void FabiEngine3D::music_addToPlaylist(const string& filename)
{
	_core->_audioManager.createMusic(filename);
	_core->_audioPlayer.playMusic(_core->_audioManager.getMusic(), true);
}

void FabiEngine3D::music_clearPlaylist()
{
	// Stop before deleting
	if (_core->_audioPlayer.isMusicStarted())
	{
		_core->_audioPlayer.stopMusic();
	}

	// Delete music
	_core->_audioManager.deleteMusic();
}

void FabiEngine3D::music_pause()
{
	if (!_core->_audioPlayer.isMusicPlaying())
	{
		Logger::throwWarning("Tried to pause music playlist: music is not playing!");
		return;
	}
	if (_core->_audioPlayer.isMusicPaused())
	{
		Logger::throwWarning("Tried to pause music playlist: music is already paused!");
		return;
	}

	_core->_audioPlayer.pauseMusic();
}

void FabiEngine3D::music_resume()
{
	if (!_core->_audioPlayer.isMusicPaused())
	{
		Logger::throwWarning("Tried to resume music playlist: music is not paused!");
		return;
	}

	_core->_audioPlayer.resumeMusic();
}

void FabiEngine3D::music_setVolume(float volume)
{
	_core->_audioPlayer.setMusicVolume(volume);
}

const bool FabiEngine3D::music_isStarted()
{
	return _core->_audioPlayer.isMusicStarted();
}

const bool FabiEngine3D::music_isPlaying()
{
	return _core->_audioPlayer.isMusicPlaying();
}

const bool FabiEngine3D::music_isPaused()
{
	return _core->_audioPlayer.isMusicPaused();
}

const float FabiEngine3D::music_getVolume()
{
	return _core->_audioPlayer.getMusicVolume();
}
#include "fabi_engine_3d.hpp"
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
	_core->_audioPlayer.playSound(_core->_audioManager.getSound(ID), loops, fadeMS, forcePlay);
}

void FabiEngine3D::sound_pause(const string& ID)
{
	_core->_audioPlayer.pauseSound(_core->_audioManager.getSound(ID));
}

void FabiEngine3D::sound_pauseAll()
{
	_core->_audioPlayer.pauseAllSounds();
}

void FabiEngine3D::sound_resume(const string& ID)
{
	_core->_audioPlayer.resumeSound(_core->_audioManager.getSound(ID));
}

void FabiEngine3D::sound_resumeAll()
{
	_core->_audioPlayer.resumeAllSounds();
}

void FabiEngine3D::sound_stop(const string& ID, int fadeMS)
{
	_core->_audioPlayer.stopSound(_core->_audioManager.getSound(ID), fadeMS);
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

void FabiEngine3D::sound_move(const string& ID, Vec3 factor)
{
	_core->_audioManager.getSound(ID).move(factor);
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
	_core->_audioPlayer.stopMusic(true);

	// Delete music
	_core->_audioManager.deleteMusic();
}

void FabiEngine3D::music_pause()
{
	_core->_audioPlayer.pauseMusic();
}

void FabiEngine3D::music_resume()
{
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
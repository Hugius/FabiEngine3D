#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::soundEntity_deleteAll()
{
	soundEntity_stopAll();
	_core->_audioManager.deleteAllSounds();
}

void FabiEngine3D::soundEntity_stopAll()
{
	soundEntity_resumeAll();
	_core->_audioPlayer.stopAllSounds();
}

void FabiEngine3D::music_addToPlaylist(const string& fileName)
{
	_core->_audioManager.addMusic(fileName);
	_core->_audioPlayer.playMusic(_core->_audioManager.getMusic(), true);
}

void FabiEngine3D::music_pause()
{
	_core->_audioPlayer.pauseMusic();
}

void FabiEngine3D::music_resume()
{
	_core->_audioPlayer.resumeMusic();
}

bool FabiEngine3D::music_isPlaying()
{
	return _core->_audioPlayer.isMusicPlaying() && !_core->_audioPlayer.isMusicPaused();
}

bool FabiEngine3D::music_isPaused()
{
	return _core->_audioPlayer.isMusicPaused();
}

float FabiEngine3D::music_getVolume()
{
	return _core->_audioPlayer.getMusicVolume();
}

void FabiEngine3D::music_clearPlaylist()
{
	// Resume before stopping
	if (music_isPaused())
	{
		music_resume();
	}

	_core->_audioPlayer.stopMusic();
	_core->_audioManager.deleteMusic();
}

void FabiEngine3D::music_setVolume(float volume)
{
	_core->_audioPlayer.setMusicVolume(volume);
}

void FabiEngine3D::soundEntity_add(const string& ID, const string& fileName)
{
	_core->_audioManager.addSound(ID, fileName);
}

void FabiEngine3D::soundEntity_make3D(const string& ID, Vec3 position, float maxVolume, float maxDistance)
{
	_core->_audioManager.getSound(ID).make3D(position, maxVolume, maxDistance);
}

void FabiEngine3D::soundEntity_delete(const string& ID)
{
	// Check if chunk exists
	if (_core->_audioManager.isSoundExisting(ID))
	{
		// Check if chunk is playing
		if (_core->_audioPlayer.isSoundPlaying(_core->_audioManager.getSound(ID)))
		{
			// Resume playback if paused
			if (_core->_audioPlayer.isSoundPaused(_core->_audioManager.getSound(ID)))
			{
				_core->_audioPlayer.resumeSound(_core->_audioManager.getSound(ID));
			}

			// Stop playback
			_core->_audioPlayer.stopSound(_core->_audioManager.getSound(ID), 0);
		}
	}

	// Delete audio chunk
	_core->_audioManager.deleteSound(ID);
}

void FabiEngine3D::soundEntity_play(const string& ID, int loops)
{
	_core->_audioPlayer.playSound(_core->_audioManager.getSound(ID), loops);
}

void FabiEngine3D::soundEntity_pause(const string& ID)
{
	_core->_audioPlayer.pauseSound(_core->_audioManager.getSound(ID));
}

void FabiEngine3D::soundEntity_pauseAll()
{
	_core->_audioPlayer.pauseAllSounds();
}

void FabiEngine3D::soundEntity_resume(const string& ID)
{
	_core->_audioPlayer.resumeSound(_core->_audioManager.getSound(ID));
}

void FabiEngine3D::soundEntity_resumeAll()
{
	_core->_audioPlayer.resumeAllSounds();
}

void FabiEngine3D::soundEntity_stop(const string& ID, int fadeMillis)
{
	// Resume playback if paused
	if (_core->_audioPlayer.isSoundPaused(_core->_audioManager.getSound(ID)))
	{
		_core->_audioPlayer.resumeSound(_core->_audioManager.getSound(ID));
	}

	// Stop playback
	_core->_audioPlayer.stopSound(_core->_audioManager.getSound(ID), fadeMillis);
}

void FabiEngine3D::soundEntity_setVolume(const string& ID, float volume)
{
	_core->_audioManager.getSound(ID).setVolume(volume);
}

void FabiEngine3D::soundEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_audioManager.getSound(ID).setPosition(position);
}

void FabiEngine3D::soundEntity_move(const string& ID, Vec3 factor)
{
	_core->_audioManager.getSound(ID).translate(factor);
}

void FabiEngine3D::soundEntity_setMaxDistance(const string& ID, float maxDistance)
{
	_core->_audioManager.getSound(ID).setMaxDistance(maxDistance);
}

void FabiEngine3D::soundEntity_setMaxVolume(const string& ID, float volume)
{
	_core->_audioManager.getSound(ID).setMaxVolume(volume);
}

vector<string> FabiEngine3D::soundEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto chunk : _core->_audioManager.getSounds())
	{
		IDs.push_back(chunk.getID());
	}

	return IDs;
}

string FabiEngine3D::soundEntity_getFilePath(const string& ID)
{
	return _core->_audioManager.getSound(ID).getFilePath();
}

Vec3 FabiEngine3D::soundEntity_getPosition(const string& ID)
{
	return _core->_audioManager.getSound(ID).getPosition();
}

float FabiEngine3D::soundEntity_getMaxDistance(const string& ID)
{
	return _core->_audioManager.getSound(ID).getMaxDistance();
}

bool FabiEngine3D::soundEntity_isExisting(const string& ID)
{
	return _core->_audioManager.isSoundExisting(ID);
}

bool FabiEngine3D::soundEntity_isPlaying(const string& ID)
{
	auto chunk = _core->_audioManager.getSound(ID);

	return _core->_audioPlayer.isSoundPlaying(chunk) && !_core->_audioPlayer.isSoundPaused(chunk);
}

bool FabiEngine3D::soundEntity_isPaused(const string& ID)
{
	return _core->_audioPlayer.isSoundPaused(_core->_audioManager.getSound(ID));;
}

bool FabiEngine3D::soundEntity_isLoaded(const string& ID)
{
	return (_core->_audioManager.getSound(ID).getDataPointer() != nullptr);
}

bool FabiEngine3D::soundEntity_is3D(const string& ID)
{
	return _core->_audioManager.getSound(ID).is3D();
}

float FabiEngine3D::soundEntity_getVolume(const string& ID)
{
	return _core->_audioManager.getSound(ID).getVolume();
}

float FabiEngine3D::soundEntity_getMaxVolume(const string& ID)
{
	return _core->_audioManager.getSound(ID).getMaxVolume();
}

int FabiEngine3D::soundEntity_getUsedChannelCount()
{
	return _core->_audioPlayer.getUsedChannelCount();
}
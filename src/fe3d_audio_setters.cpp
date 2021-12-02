#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::music_addToPlaylist(const string& fileName)
{
	_core->_audioManager.createMusic(fileName);
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

void FabiEngine3D::sound2D_create(const string& ID, const string& filePath)
{
	_core->_audioManager.createSound2D(ID, filePath);
}

void FabiEngine3D::sound2D_delete(const string& ID)
{
	// Check if chunk exists
	if(_core->_audioManager.isSoundExisting2D(ID))
	{
		// Stop before deleting
		if(_core->_audioPlayer.isSoundStarted2D(_core->_audioManager.getSound2D(ID)))
		{
			_core->_audioPlayer.stopSound2D(_core->_audioManager.getSound2D(ID), 0);
		}
	}

	// Delete sound
	_core->_audioManager.deleteSound2D(ID);
}

void FabiEngine3D::sound2D_deleteAll()
{
	// Stop before deleting
	sound2D_stopAll();

	// Delete sounds
	_core->_audioManager.deleteSounds2D();
}

void FabiEngine3D::sound2D_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_audioManager.getSound2D(ID);

	if(!_core->_audioPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if(_core->_audioPlayer.isSoundStarted2D(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_audioPlayer.playSound2D(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound2D_pause(const string& ID)
{
	auto sound = _core->_audioManager.getSound2D(ID);

	if(!_core->_audioPlayer.isSoundPlaying2D(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->_audioPlayer.isSoundPaused2D(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_audioPlayer.pauseSound2D(sound);
}

void FabiEngine3D::sound2D_pauseAll()
{
	_core->_audioPlayer.pauseAllSounds2D(_core->_audioManager.getSounds2D());
}

void FabiEngine3D::sound2D_resume(const string& ID)
{
	auto sound = _core->_audioManager.getSound2D(ID);

	if(!_core->_audioPlayer.isSoundPaused2D(sound))
	{
		Logger::throwWarning("Tried to resume 2D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_audioPlayer.resumeSound2D(sound);
}

void FabiEngine3D::sound2D_resumeAll()
{
	_core->_audioPlayer.resumeAllSounds2D(_core->_audioManager.getSounds2D());
}

void FabiEngine3D::sound2D_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_audioManager.getSound2D(ID);

	if(!_core->_audioPlayer.isSoundStarted2D(sound))
	{
		Logger::throwWarning("Tried to stop 2D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_audioPlayer.stopSound2D(sound, fadeMS);
}

void FabiEngine3D::sound2D_stopAll()
{
	_core->_audioPlayer.stopAllSounds2D(_core->_audioManager.getSounds2D());
}

void FabiEngine3D::sound2D_setVolume(const string& ID, float volume)
{
	_core->_audioManager.getSound2D(ID).setVolume(volume);
}

void FabiEngine3D::sound3D_create(const string& ID, const string& filePath)
{
	_core->_audioManager.createSound3D(ID, filePath);
}

void FabiEngine3D::sound3D_delete(const string& ID)
{
	// Check if chunk exists
	if (_core->_audioManager.isSoundExisting3D(ID))
	{
		// Stop before deleting
		if (_core->_audioPlayer.isSoundStarted3D(_core->_audioManager.getSound3D(ID)))
		{
			_core->_audioPlayer.stopSound3D(_core->_audioManager.getSound3D(ID), 0);
		}
	}

	// Delete sound
	_core->_audioManager.deleteSound3D(ID);
}

void FabiEngine3D::sound3D_deleteAll()
{
	// Stop before deleting
	sound3D_stopAll();

	// Delete sounds
	_core->_audioManager.deleteSounds3D();
}

void FabiEngine3D::sound3D_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_audioManager.getSound3D(ID);

	if (!_core->_audioPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 3D sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if (_core->_audioPlayer.isSoundStarted3D(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 3D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_audioPlayer.playSound3D(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound3D_pause(const string& ID)
{
	auto sound = _core->_audioManager.getSound3D(ID);

	if (!_core->_audioPlayer.isSoundPlaying3D(sound))
	{
		Logger::throwWarning("Tried to pause 3D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if (_core->_audioPlayer.isSoundPaused3D(sound))
	{
		Logger::throwWarning("Tried to pause 3D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_audioPlayer.pauseSound3D(sound);
}

void FabiEngine3D::sound3D_pauseAll()
{
	_core->_audioPlayer.pauseAllSounds3D(_core->_audioManager.getSounds3D());
}

void FabiEngine3D::sound3D_resume(const string& ID)
{
	auto sound = _core->_audioManager.getSound3D(ID);

	if (!_core->_audioPlayer.isSoundPaused3D(sound))
	{
		Logger::throwWarning("Tried to resume 3D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_audioPlayer.resumeSound3D(sound);
}

void FabiEngine3D::sound3D_resumeAll()
{
	_core->_audioPlayer.resumeAllSounds3D(_core->_audioManager.getSounds3D());
}

void FabiEngine3D::sound3D_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_audioManager.getSound3D(ID);

	if (!_core->_audioPlayer.isSoundStarted3D(sound))
	{
		Logger::throwWarning("Tried to stop 3D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_audioPlayer.stopSound3D(sound, fadeMS);
}

void FabiEngine3D::sound3D_stopAll()
{
	_core->_audioPlayer.stopAllSounds3D(_core->_audioManager.getSounds3D());
}

void FabiEngine3D::sound3D_setPosition(const string& ID, fvec3 position)
{
	_core->_audioManager.getSound3D(ID).setPosition(position);
}

void FabiEngine3D::sound3D_move(const string& ID, fvec3 change)
{
	_core->_audioManager.getSound3D(ID).move(change);
}

void FabiEngine3D::sound3D_setMaxDistance(const string& ID, float maxDistance)
{
	_core->_audioManager.getSound3D(ID).setMaxDistance(maxDistance);
}

void FabiEngine3D::sound3D_setMaxVolume(const string& ID, float volume)
{
	_core->_audioManager.getSound3D(ID).setMaxVolume(volume);
}
#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::sound2d_create(const string& ID, const string& audioPath)
{
	_core->_sound2dManager.createSound(ID, audioPath);
}

void FabiEngine3D::sound2d_delete(const string& ID)
{
	// Check if chunk exists
	if(_core->_sound2dManager.isSoundExisting(ID))
	{
		// Stop before deleting
		if(_core->_sound2dPlayer.isSoundStarted(_core->_sound2dManager.getSound(ID)))
		{
			_core->_sound2dPlayer.stopSound(_core->_sound2dManager.getSound(ID), 0);
		}
	}

	// Delete sound
	_core->_sound2dManager.deleteSound(ID);
}

void FabiEngine3D::sound2d_deleteAll()
{
	// Stop before deleting
	sound2d_stopAll();

	// Delete sounds
	_core->_sound2dManager.deleteSounds();
}

void FabiEngine3D::sound2d_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_sound2dManager.getSound(ID);

	if(!_core->_sound2dPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if(_core->_sound2dPlayer.isSoundStarted(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_sound2dPlayer.playSound(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound2d_pause(const string& ID)
{
	auto sound = _core->_sound2dManager.getSound(ID);

	if(!_core->_sound2dPlayer.isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->_sound2dPlayer.isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_sound2dPlayer.pauseSound(sound);
}

void FabiEngine3D::sound2d_pauseAll()
{
	_core->_sound2dPlayer.pauseSounds(_core->_sound2dManager.getSounds());
}

void FabiEngine3D::sound2d_resume(const string& ID)
{
	auto sound = _core->_sound2dManager.getSound(ID);

	if(!_core->_sound2dPlayer.isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume 2D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_sound2dPlayer.resumeSound(sound);
}

void FabiEngine3D::sound2d_resumeAll()
{
	_core->_sound2dPlayer.resumeSounds(_core->_sound2dManager.getSounds());
}

void FabiEngine3D::sound2d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_sound2dManager.getSound(ID);

	if(!_core->_sound2dPlayer.isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop 2D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_sound2dPlayer.stopSound(sound, fadeMS);
}

void FabiEngine3D::sound2d_stopAll()
{
	_core->_sound2dPlayer.stopSounds(_core->_sound2dManager.getSounds());
}

void FabiEngine3D::sound2d_setVolume(const string& ID, float value)
{
	_core->_sound2dManager.getSound(ID).setVolume(value);
}
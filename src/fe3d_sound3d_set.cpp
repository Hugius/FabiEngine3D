#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::sound3d_create(const string& ID, const string& audioPath)
{
	_core->_sound3dManager.createSound(ID, audioPath);
}

void FabiEngine3D::sound3d_delete(const string& ID)
{
	// Check if chunk exists
	if(_core->_sound3dManager.isSoundExisting(ID))
	{
		// Stop before deleting
		if(_core->_sound3dPlayer.isSoundStarted(_core->_sound3dManager.getSound(ID)))
		{
			_core->_sound3dPlayer.stopSound(_core->_sound3dManager.getSound(ID), 0);
		}
	}

	// Delete sound
	_core->_sound3dManager.deleteSound(ID);
}

void FabiEngine3D::sound3d_deleteAll()
{
	// Stop before deleting
	sound3d_stopAll();

	// Delete sounds
	_core->_sound3dManager.deleteSounds();
}

void FabiEngine3D::sound3d_start(const string& ID, int playCount, unsigned int fadeMS, bool mustForce)
{
	auto sound = _core->_sound3dManager.getSound(ID);

	if(!_core->_sound3dPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play sound3D with ID \"", ID, "\": no sound channels available!");
		return;
	}
	if(_core->_sound3dPlayer.isSoundStarted(sound) && !mustForce)
	{
		Logger::throwWarning("Tried to play sound3D with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_sound3dPlayer.startSound(sound, playCount, fadeMS, mustForce);
}

void FabiEngine3D::sound3d_pause(const string& ID)
{
	auto sound = _core->_sound3dManager.getSound(ID);

	if(!_core->_sound3dPlayer.isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause sound3D with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->_sound3dPlayer.isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause sound3D with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_sound3dPlayer.pauseSound(sound);
}

void FabiEngine3D::sound3d_pauseAll()
{
	_core->_sound3dPlayer.pauseSounds(_core->_sound3dManager.getSounds());
}

void FabiEngine3D::sound3d_resume(const string& ID)
{
	auto sound = _core->_sound3dManager.getSound(ID);

	if(!_core->_sound3dPlayer.isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume sound3D with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_sound3dPlayer.resumeSound(sound);
}

void FabiEngine3D::sound3d_resumeAll()
{
	_core->_sound3dPlayer.resumeSounds(_core->_sound3dManager.getSounds());
}

void FabiEngine3D::sound3d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_sound3dManager.getSound(ID);

	if(!_core->_sound3dPlayer.isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop sound3D with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_sound3dPlayer.stopSound(sound, fadeMS);
}

void FabiEngine3D::sound3d_stopAll()
{
	_core->_sound3dPlayer.stopSounds(_core->_sound3dManager.getSounds());
}

void FabiEngine3D::sound3d_setPosition(const string& ID, fvec3 value)
{
	_core->_sound3dManager.getSound(ID).setPosition(value);
}

void FabiEngine3D::sound3d_move(const string& ID, fvec3 change)
{
	_core->_sound3dManager.getSound(ID).move(change);
}

void FabiEngine3D::sound3d_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_sound3dManager.getSound(ID).moveTo(target, speed);
}

void FabiEngine3D::sound3d_setMaxDistance(const string& ID, float value)
{
	_core->_sound3dManager.getSound(ID).setMaxDistance(value);
}

void FabiEngine3D::sound3d_setMaxVolume(const string& ID, float value)
{
	_core->_sound3dManager.getSound(ID).setMaxVolume(value);
}
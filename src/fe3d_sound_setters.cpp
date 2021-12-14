#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::sound2d_create(const string& ID, const string& audioPath)
{
	_core->_soundManager.createSound2d(ID, audioPath);
}

void FabiEngine3D::sound2d_delete(const string& ID)
{
	// Check if chunk exists
	if(_core->_soundManager.isSound2dExisting(ID))
	{
		// Stop before deleting
		if(_core->_soundPlayer.isSound2dStarted(_core->_soundManager.getSound2d(ID)))
		{
			_core->_soundPlayer.stopSound2d(_core->_soundManager.getSound2d(ID), 0);
		}
	}

	// Delete sound
	_core->_soundManager.deleteSound2d(ID);
}

void FabiEngine3D::sound2d_deleteAll()
{
	// Stop before deleting
	sound2d_stopAll();

	// Delete sounds
	_core->_soundManager.deleteAllSound2d();
}

void FabiEngine3D::sound2d_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_soundManager.getSound2d(ID);

	if(!_core->_soundPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if(_core->_soundPlayer.isSound2dStarted(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_soundPlayer.playSound2d(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound2d_pause(const string& ID)
{
	auto sound = _core->_soundManager.getSound2d(ID);

	if(!_core->_soundPlayer.isSound2dPlaying(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->_soundPlayer.isSound2dPaused(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_soundPlayer.pauseSound2d(sound);
}

void FabiEngine3D::sound2d_pauseAll()
{
	_core->_soundPlayer.pauseAllSound2d(_core->_soundManager.getAllSound2ds());
}

void FabiEngine3D::sound2d_resume(const string& ID)
{
	auto sound = _core->_soundManager.getSound2d(ID);

	if(!_core->_soundPlayer.isSound2dPaused(sound))
	{
		Logger::throwWarning("Tried to resume 2D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_soundPlayer.resumeSound2d(sound);
}

void FabiEngine3D::sound2d_resumeAll()
{
	_core->_soundPlayer.resumeAllSound2d(_core->_soundManager.getAllSound2ds());
}

void FabiEngine3D::sound2d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_soundManager.getSound2d(ID);

	if(!_core->_soundPlayer.isSound2dStarted(sound))
	{
		Logger::throwWarning("Tried to stop 2D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_soundPlayer.stopSound2d(sound, fadeMS);
}

void FabiEngine3D::sound2d_stopAll()
{
	_core->_soundPlayer.stopAllSound2d(_core->_soundManager.getAllSound2ds());
}

void FabiEngine3D::sound2d_setVolume(const string& ID, float value)
{
	_core->_soundManager.getSound2d(ID).setVolume(value);
}

void FabiEngine3D::sound3d_create(const string& ID, const string& audioPath)
{
	_core->_soundManager.createSound3d(ID, audioPath);
}

void FabiEngine3D::sound3d_delete(const string& ID)
{
	// Check if chunk exists
	if (_core->_soundManager.isSound3dExisting(ID))
	{
		// Stop before deleting
		if (_core->_soundPlayer.isSound3dStarted(_core->_soundManager.getSound3d(ID)))
		{
			_core->_soundPlayer.stopSound3d(_core->_soundManager.getSound3d(ID), 0);
		}
	}

	// Delete sound
	_core->_soundManager.deleteSound3d(ID);
}

void FabiEngine3D::sound3d_deleteAll()
{
	// Stop before deleting
	sound3d_stopAll();

	// Delete sounds
	_core->_soundManager.deleteAllSound3d();
}

void FabiEngine3D::sound3d_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_soundManager.getSound3d(ID);

	if (!_core->_soundPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 3D sound with ID \"", ID, "\": no sound channels available!");
		return;
	}
	if (_core->_soundPlayer.isSound3dStarted(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 3D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_soundPlayer.playSound3d(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound3d_pause(const string& ID)
{
	auto sound = _core->_soundManager.getSound3d(ID);

	if (!_core->_soundPlayer.isSound3dPlaying(sound))
	{
		Logger::throwWarning("Tried to pause 3D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if (_core->_soundPlayer.isSound3dPaused(sound))
	{
		Logger::throwWarning("Tried to pause 3D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_soundPlayer.pauseSound3d(sound);
}

void FabiEngine3D::sound3d_pauseAll()
{
	_core->_soundPlayer.pauseAllSound3d(_core->_soundManager.getAllSound3ds());
}

void FabiEngine3D::sound3d_resume(const string& ID)
{
	auto sound = _core->_soundManager.getSound3d(ID);

	if (!_core->_soundPlayer.isSound3dPaused(sound))
	{
		Logger::throwWarning("Tried to resume 3D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_soundPlayer.resumeSound3d(sound);
}

void FabiEngine3D::sound3d_resumeAll()
{
	_core->_soundPlayer.resumeAllSound3d(_core->_soundManager.getAllSound3ds());
}

void FabiEngine3D::sound3d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_soundManager.getSound3d(ID);

	if (!_core->_soundPlayer.isSound3dStarted(sound))
	{
		Logger::throwWarning("Tried to stop 3D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_soundPlayer.stopSound3d(sound, fadeMS);
}

void FabiEngine3D::sound3d_stopAll()
{
	_core->_soundPlayer.stopAllSound3d(_core->_soundManager.getAllSound3ds());
}

void FabiEngine3D::sound3d_setPosition(const string& ID, fvec3 value)
{
	_core->_soundManager.getSound3d(ID).setPosition(value);
}

void FabiEngine3D::sound3d_move(const string& ID, fvec3 change)
{
	_core->_soundManager.getSound3d(ID).move(change);
}

void FabiEngine3D::sound3d_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_soundManager.getSound3d(ID).moveTo(target, speed);
}

void FabiEngine3D::sound3d_setMaxDistance(const string& ID, float value)
{
	_core->_soundManager.getSound3d(ID).setMaxDistance(value);
}

void FabiEngine3D::sound3d_setMaxVolume(const string& ID, float value)
{
	_core->_soundManager.getSound3d(ID).setMaxVolume(value);
}
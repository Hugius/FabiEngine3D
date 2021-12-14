#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::sound2d_create(const string& ID, const string& audioPath)
{
	_core->_audioManager.createSound2d(ID, audioPath);
}

void FabiEngine3D::sound2d_delete(const string& ID)
{
	// Check if chunk exists
	if(_core->_audioManager.isSound2dExisting(ID))
	{
		// Stop before deleting
		if(_core->_audioPlayer.isSound2dStarted(_core->_audioManager.getSound2d(ID)))
		{
			_core->_audioPlayer.stopSound2d(_core->_audioManager.getSound2d(ID), 0);
		}
	}

	// Delete sound
	_core->_audioManager.deleteSound2d(ID);
}

void FabiEngine3D::sound2d_deleteAll()
{
	// Stop before deleting
	sound2d_stopAll();

	// Delete sounds
	_core->_audioManager.deleteAllSound2d();
}

void FabiEngine3D::sound2d_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_audioManager.getSound2d(ID);

	if(!_core->_audioPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if(_core->_audioPlayer.isSound2dStarted(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 2D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_audioPlayer.playSound2d(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound2d_pause(const string& ID)
{
	auto sound = _core->_audioManager.getSound2d(ID);

	if(!_core->_audioPlayer.isSound2dPlaying(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->_audioPlayer.isSound2dPaused(sound))
	{
		Logger::throwWarning("Tried to pause 2D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_audioPlayer.pauseSound2d(sound);
}

void FabiEngine3D::sound2d_pauseAll()
{
	_core->_audioPlayer.pauseAllSound2d(_core->_audioManager.getAllSound2d());
}

void FabiEngine3D::sound2d_resume(const string& ID)
{
	auto sound = _core->_audioManager.getSound2d(ID);

	if(!_core->_audioPlayer.isSound2dPaused(sound))
	{
		Logger::throwWarning("Tried to resume 2D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_audioPlayer.resumeSound2d(sound);
}

void FabiEngine3D::sound2d_resumeAll()
{
	_core->_audioPlayer.resumeAllSound2d(_core->_audioManager.getAllSound2d());
}

void FabiEngine3D::sound2d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_audioManager.getSound2d(ID);

	if(!_core->_audioPlayer.isSound2dStarted(sound))
	{
		Logger::throwWarning("Tried to stop 2D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_audioPlayer.stopSound2d(sound, fadeMS);
}

void FabiEngine3D::sound2d_stopAll()
{
	_core->_audioPlayer.stopAllSound2d(_core->_audioManager.getAllSound2d());
}

void FabiEngine3D::sound2d_setVolume(const string& ID, float value)
{
	_core->_audioManager.getSound2d(ID).setVolume(value);
}

void FabiEngine3D::sound3d_create(const string& ID, const string& audioPath)
{
	_core->_audioManager.createSound3d(ID, audioPath);
}

void FabiEngine3D::sound3d_delete(const string& ID)
{
	// Check if chunk exists
	if (_core->_audioManager.isSound3dExisting(ID))
	{
		// Stop before deleting
		if (_core->_audioPlayer.isSound3dStarted(_core->_audioManager.getSound3d(ID)))
		{
			_core->_audioPlayer.stopSound3d(_core->_audioManager.getSound3d(ID), 0);
		}
	}

	// Delete sound
	_core->_audioManager.deleteSound3d(ID);
}

void FabiEngine3D::sound3d_deleteAll()
{
	// Stop before deleting
	sound3d_stopAll();

	// Delete sounds
	_core->_audioManager.deleteAllSound3d();
}

void FabiEngine3D::sound3d_play(const string& ID, int loops, unsigned int fadeMS, bool mustForcePlay)
{
	auto sound = _core->_audioManager.getSound3d(ID);

	if (!_core->_audioPlayer.isChannelAvailable())
	{
		Logger::throwWarning("Tried to play 3D sound with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if (_core->_audioPlayer.isSound3dStarted(sound) && !mustForcePlay)
	{
		Logger::throwWarning("Tried to play 3D sound with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->_audioPlayer.playSound3d(sound, loops, fadeMS, mustForcePlay);
}

void FabiEngine3D::sound3d_pause(const string& ID)
{
	auto sound = _core->_audioManager.getSound3d(ID);

	if (!_core->_audioPlayer.isSound3dPlaying(sound))
	{
		Logger::throwWarning("Tried to pause 3D sound with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if (_core->_audioPlayer.isSound3dPaused(sound))
	{
		Logger::throwWarning("Tried to pause 3D sound with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->_audioPlayer.pauseSound3d(sound);
}

void FabiEngine3D::sound3d_pauseAll()
{
	_core->_audioPlayer.pauseAllSound3d(_core->_audioManager.getAllSound3d());
}

void FabiEngine3D::sound3d_resume(const string& ID)
{
	auto sound = _core->_audioManager.getSound3d(ID);

	if (!_core->_audioPlayer.isSound3dPaused(sound))
	{
		Logger::throwWarning("Tried to resume 3D sound with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->_audioPlayer.resumeSound3d(sound);
}

void FabiEngine3D::sound3d_resumeAll()
{
	_core->_audioPlayer.resumeAllSound3d(_core->_audioManager.getAllSound3d());
}

void FabiEngine3D::sound3d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->_audioManager.getSound3d(ID);

	if (!_core->_audioPlayer.isSound3dStarted(sound))
	{
		Logger::throwWarning("Tried to stop 3D sound with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->_audioPlayer.stopSound3d(sound, fadeMS);
}

void FabiEngine3D::sound3d_stopAll()
{
	_core->_audioPlayer.stopAllSound3d(_core->_audioManager.getAllSound3d());
}

void FabiEngine3D::sound3d_setPosition(const string& ID, fvec3 value)
{
	_core->_audioManager.getSound3d(ID).setPosition(value);
}

void FabiEngine3D::sound3d_move(const string& ID, fvec3 change)
{
	_core->_audioManager.getSound3d(ID).move(change);
}

void FabiEngine3D::sound3d_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->_audioManager.getSound3d(ID).moveTo(target, speed);
}

void FabiEngine3D::sound3d_setMaxDistance(const string& ID, float value)
{
	_core->_audioManager.getSound3d(ID).setMaxDistance(value);
}

void FabiEngine3D::sound3d_setMaxVolume(const string& ID, float value)
{
	_core->_audioManager.getSound3d(ID).setMaxVolume(value);
}
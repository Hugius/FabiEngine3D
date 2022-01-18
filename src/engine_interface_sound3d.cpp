#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound3d_create(const string& ID, const string& audioPath)
{
	_core->getSound3dManager()->createSound(ID, audioPath);
}

void EngineInterface::sound3d_delete(const string& ID)
{
	if(_core->getSound3dManager()->isSoundExisting(ID))
	{
		if(_core->getSound3dPlayer()->isSoundStarted(_core->getSound3dManager()->getSound(ID)))
		{
			_core->getSound3dPlayer()->stopSound(_core->getSound3dManager()->getSound(ID), 0);
		}
	}

	_core->getSound3dManager()->deleteSound(ID);
}

void EngineInterface::sound3d_deleteAll()
{
	sound3d_stopAll();

	_core->getSound3dManager()->deleteSounds();
}

void EngineInterface::sound3d_start(const string& ID, int playCount, unsigned int fadeMS, bool mustForce)
{
	auto sound = _core->getSound3dManager()->getSound(ID);

	if(!_core->getSound3dPlayer()->isChannelAvailable())
	{
		Logger::throwWarning("Tried to play sound3D with ID \"", ID, "\": no sound channels available!");
		return;
	}
	if(_core->getSound3dPlayer()->isSoundStarted(sound) && !mustForce)
	{
		Logger::throwWarning("Tried to play sound3D with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->getSound3dPlayer()->startSound(sound, playCount, fadeMS, mustForce);
}

void EngineInterface::sound3d_pause(const string& ID)
{
	auto sound = _core->getSound3dManager()->getSound(ID);

	if(!_core->getSound3dPlayer()->isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause sound3D with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->getSound3dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause sound3D with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->getSound3dPlayer()->pauseSound(sound);
}

void EngineInterface::sound3d_pauseAll()
{
	_core->getSound3dPlayer()->pauseSounds(_core->getSound3dManager()->getSounds());
}

void EngineInterface::sound3d_resume(const string& ID)
{
	auto sound = _core->getSound3dManager()->getSound(ID);

	if(!_core->getSound3dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume sound3D with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->getSound3dPlayer()->resumeSound(sound);
}

void EngineInterface::sound3d_resumeAll()
{
	_core->getSound3dPlayer()->resumeSounds(_core->getSound3dManager()->getSounds());
}

void EngineInterface::sound3d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->getSound3dManager()->getSound(ID);

	if(!_core->getSound3dPlayer()->isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop sound3D with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->getSound3dPlayer()->stopSound(sound, fadeMS);
}

void EngineInterface::sound3d_stopAll()
{
	_core->getSound3dPlayer()->stopSounds(_core->getSound3dManager()->getSounds());
}

void EngineInterface::sound3d_setPosition(const string& ID, fvec3 value)
{
	_core->getSound3dManager()->getSound(ID).setPosition(value);
}

void EngineInterface::sound3d_move(const string& ID, fvec3 change)
{
	_core->getSound3dManager()->getSound(ID).move(change);
}

void EngineInterface::sound3d_moveTo(const string& ID, fvec3 target, float speed)
{
	_core->getSound3dManager()->getSound(ID).moveTo(target, speed);
}

void EngineInterface::sound3d_setMaxDistance(const string& ID, float value)
{
	_core->getSound3dManager()->getSound(ID).setMaxDistance(value);
}

void EngineInterface::sound3d_setMaxVolume(const string& ID, float value)
{
	_core->getSound3dManager()->getSound(ID).setMaxVolume(value);
}

const vector<string> EngineInterface::sound3d_getIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->getSound3dManager()->getSounds())
	{
		result.push_back(chunk.getID());
	}

	return result;
}

const string& EngineInterface::sound3d_getAudioPath(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getAudioPath();
}

const bool EngineInterface::sound3d_isExisting(const string& ID) const
{
	return _core->getSound3dManager()->isSoundExisting(ID);
}

const bool EngineInterface::sound3d_isStarted(const string& ID) const
{
	return _core->getSound3dPlayer()->isSoundStarted(_core->getSound3dManager()->getSound(ID));
}

const bool EngineInterface::sound3d_isPlaying(const string& ID) const
{
	return _core->getSound3dPlayer()->isSoundPlaying(_core->getSound3dManager()->getSound(ID));
}

const bool EngineInterface::sound3d_isPaused(const string& ID) const
{
	return _core->getSound3dPlayer()->isSoundPaused(_core->getSound3dManager()->getSound(ID));
}

const float EngineInterface::sound3d_getVolume(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getVolume();
}

const float EngineInterface::sound3d_getMaxVolume(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getMaxVolume();
}

const fvec3 EngineInterface::sound3d_getPosition(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getPosition();
}

const float EngineInterface::sound3d_getMaxDistance(const string& ID) const
{
	return _core->getSound3dManager()->getSound(ID).getMaxDistance();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound3d_create(const string& id, const string& audioPath)
{
	_core->getSound3dManager()->createSound(id, audioPath);
}

void EngineInterface::sound3d_delete(const string& id)
{
	if(_core->getSound3dManager()->isSoundExisting(id))
	{
		if(_core->getSound3dPlayer()->isSoundStarted(_core->getSound3dManager()->getSound(id)))
		{
			_core->getSound3dPlayer()->stopSound(_core->getSound3dManager()->getSound(id), 0);
		}
	}

	_core->getSound3dManager()->deleteSound(id);
}

void EngineInterface::sound3d_deleteAll()
{
	sound3d_stopAll();

	_core->getSound3dManager()->deleteSounds();
}

void EngineInterface::sound3d_start(const string& id, int playCount, unsigned int fadeMS, bool mustForce)
{
	auto sound = _core->getSound3dManager()->getSound(id);

	if(!_core->getSound3dPlayer()->isChannelAvailable())
	{
		Logger::throwWarning("Tried to play sound3D with id \"", id, "\": no sound channels available!");
		return;
	}
	if(_core->getSound3dPlayer()->isSoundStarted(sound) && !mustForce)
	{
		Logger::throwWarning("Tried to play sound3D with id \"", id, "\": sound is already started!");
		return;
	}

	_core->getSound3dPlayer()->startSound(sound, playCount, fadeMS, mustForce);
}

void EngineInterface::sound3d_pause(const string& id)
{
	auto sound = _core->getSound3dManager()->getSound(id);

	if(!_core->getSound3dPlayer()->isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause sound3D with id \"", id, "\": sound is not playing!");
		return;
	}
	if(_core->getSound3dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause sound3D with id \"", id, "\": sound is already paused!");
		return;
	}

	_core->getSound3dPlayer()->pauseSound(sound);
}

void EngineInterface::sound3d_pauseAll()
{
	_core->getSound3dPlayer()->pauseSounds(_core->getSound3dManager()->getSounds());
}

void EngineInterface::sound3d_resume(const string& id)
{
	auto sound = _core->getSound3dManager()->getSound(id);

	if(!_core->getSound3dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume sound3D with id \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->getSound3dPlayer()->resumeSound(sound);
}

void EngineInterface::sound3d_resumeAll()
{
	_core->getSound3dPlayer()->resumeSounds(_core->getSound3dManager()->getSounds());
}

void EngineInterface::sound3d_stop(const string& id, unsigned int fadeMS)
{
	auto sound = _core->getSound3dManager()->getSound(id);

	if(!_core->getSound3dPlayer()->isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop sound3D with id \"", id, "\": sound is not started!");
		return;
	}

	_core->getSound3dPlayer()->stopSound(sound, fadeMS);
}

void EngineInterface::sound3d_stopAll()
{
	_core->getSound3dPlayer()->stopSounds(_core->getSound3dManager()->getSounds());
}

void EngineInterface::sound3d_setPosition(const string& id, const fvec3& value)
{
	_core->getSound3dManager()->getSound(id).setPosition(value);
}

void EngineInterface::sound3d_move(const string& id, const fvec3& change)
{
	_core->getSound3dManager()->getSound(id).move(change);
}

void EngineInterface::sound3d_moveTo(const string& id, const fvec3& target, float speed)
{
	_core->getSound3dManager()->getSound(id).moveTo(target, speed);
}

void EngineInterface::sound3d_setMaxDistance(const string& id, float value)
{
	_core->getSound3dManager()->getSound(id).setMaxDistance(value);
}

void EngineInterface::sound3d_setMaxVolume(const string& id, float value)
{
	_core->getSound3dManager()->getSound(id).setMaxVolume(value);
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

const string& EngineInterface::sound3d_getAudioPath(const string& id) const
{
	return _core->getSound3dManager()->getSound(id).getAudioPath();
}

const bool EngineInterface::sound3d_isExisting(const string& id) const
{
	return _core->getSound3dManager()->isSoundExisting(id);
}

const bool EngineInterface::sound3d_isStarted(const string& id) const
{
	return _core->getSound3dPlayer()->isSoundStarted(_core->getSound3dManager()->getSound(id));
}

const bool EngineInterface::sound3d_isPlaying(const string& id) const
{
	return _core->getSound3dPlayer()->isSoundPlaying(_core->getSound3dManager()->getSound(id));
}

const bool EngineInterface::sound3d_isPaused(const string& id) const
{
	return _core->getSound3dPlayer()->isSoundPaused(_core->getSound3dManager()->getSound(id));
}

const float EngineInterface::sound3d_getVolume(const string& id) const
{
	return _core->getSound3dManager()->getSound(id).getVolume();
}

const float EngineInterface::sound3d_getMaxVolume(const string& id) const
{
	return _core->getSound3dManager()->getSound(id).getMaxVolume();
}

const fvec3& EngineInterface::sound3d_getPosition(const string& id) const
{
	return _core->getSound3dManager()->getSound(id).getPosition();
}

const float EngineInterface::sound3d_getMaxDistance(const string& id) const
{
	return _core->getSound3dManager()->getSound(id).getMaxDistance();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound3d_create(const string & sound3dId, const string & audioPath)
{
	_core->getSound3dManager()->createSound(sound3dId, audioPath);
}

void EngineInterface::sound3d_delete(const string & sound3dId)
{
	for(int index = 0; index < _core->getSound3dPlayer()->getStartedSoundCount(sound3dId); index++)
	{
		sound3d_stop(sound3dId, index);
	}

	_core->getSound3dManager()->deleteSound(sound3dId);
}

void EngineInterface::sound3d_setPosition(const string & sound3dId, const fvec3 & value)
{
	_core->getSound3dManager()->getSound(sound3dId)->setPosition(value);
}

void EngineInterface::sound3d_move(const string & sound3dId, const fvec3 & change)
{
	_core->getSound3dManager()->getSound(sound3dId)->move(change);
}

void EngineInterface::sound3d_moveTo(const string & sound3dId, const fvec3 & target, float speed)
{
	_core->getSound3dManager()->getSound(sound3dId)->moveTo(target, speed);
}

void EngineInterface::sound3d_setMaxVolume(const string & sound3dId, float value)
{
	_core->getSound3dManager()->getSound(sound3dId)->setMaxVolume(value);
}

void EngineInterface::sound3d_setMaxDistance(const string & sound3dId, float value)
{
	_core->getSound3dManager()->getSound(sound3dId)->setMaxDistance(value);
}

void EngineInterface::sound3d_start(const string & sound3dId, int playCount)
{
	_core->getSound3dPlayer()->startSound(sound3dId, playCount);
}

void EngineInterface::sound3d_pause(const string & sound3dId, int index)
{
	_core->getSound3dPlayer()->pauseSound(sound3dId, index);
}

void EngineInterface::sound3d_resume(const string & sound3dId, int index)
{
	_core->getSound3dPlayer()->resumeSound(sound3dId, index);
}

void EngineInterface::sound3d_stop(const string & sound3dId, int index)
{
	_core->getSound3dPlayer()->stopSound(sound3dId, index);
}

const vector<string> EngineInterface::sound3d_getIds() const
{
	vector<string> result;

	for(const auto & [sound3dId, sound] : _core->getSound3dManager()->getSounds())
	{
		result.push_back(sound->getId());
	}

	return result;
}

const string & EngineInterface::sound3d_getAudioPath(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound(sound3dId)->getAudioPath();
}

const fvec3 & EngineInterface::sound3d_getPosition(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound(sound3dId)->getPosition();
}

const float EngineInterface::sound3d_getMaxDistance(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound(sound3dId)->getMaxDistance();
}

const float EngineInterface::sound3d_getMaxVolume(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound(sound3dId)->getMaxVolume();
}

const bool EngineInterface::sound3d_isExisting(const string & sound3dId) const
{
	return _core->getSound3dManager()->isSoundExisting(sound3dId);
}

const bool EngineInterface::sound3d_isStarted(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->isSoundStarted(sound3dId, index);
}

const bool EngineInterface::sound3d_isPaused(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->isSoundPaused(sound3dId, index);
}

const bool EngineInterface::sound3d_isDeviceConnected() const
{
	return _core->getSound3dPlayer()->isDeviceConnected();
}

const float EngineInterface::sound3d_getVolume(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSoundVolume(sound3dId, index);
}

const float EngineInterface::sound3d_getLeftIntensity(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSoundLeftIntensity(sound3dId, index);
}

const float EngineInterface::sound3d_getRightIntensity(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSoundRightIntensity(sound3dId, index);
}

const int EngineInterface::sound3d_getStartedCount(const string & sound3dId) const
{
	return _core->getSound3dPlayer()->getStartedSoundCount(sound3dId);
}

const int EngineInterface::sound3d_getTime(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSoundTime(sound3dId, index);
}
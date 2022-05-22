#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound3d_create(const string & sound3dId, const string & audioPath)
{
	_core->getSound3dManager()->createSound3d(sound3dId, audioPath);
}

void EngineInterface::sound3d_delete(const string & sound3dId)
{
	for(int index = 0; index < _core->getSound3dPlayer()->getStartedSound3dCount(sound3dId); index++)
	{
		sound3d_stop(sound3dId, index);
	}

	_core->getSound3dManager()->deleteSound3d(sound3dId);
}

void EngineInterface::sound3d_setPosition(const string & sound3dId, const fvec3 & value)
{
	_core->getSound3dManager()->getSound3d(sound3dId)->setPosition(value);
}

void EngineInterface::sound3d_move(const string & sound3dId, const fvec3 & change)
{
	_core->getSound3dManager()->getSound3d(sound3dId)->move(change);
}

void EngineInterface::sound3d_moveTo(const string & sound3dId, const fvec3 & target, float speed)
{
	_core->getSound3dManager()->getSound3d(sound3dId)->moveTo(target, speed);
}

void EngineInterface::sound3d_setMaxVolume(const string & sound3dId, float value)
{
	_core->getSound3dManager()->getSound3d(sound3dId)->setMaxVolume(value);
}

void EngineInterface::sound3d_setMaxDistance(const string & sound3dId, float value)
{
	_core->getSound3dManager()->getSound3d(sound3dId)->setMaxDistance(value);
}

void EngineInterface::sound3d_start(const string & sound3dId, int playCount, int startTime)
{
	_core->getSound3dPlayer()->startSound3d(sound3dId, playCount, startTime);
}

void EngineInterface::sound3d_pause(const string & sound3dId, int index)
{
	_core->getSound3dPlayer()->pauseSound3d(sound3dId, index);
}

void EngineInterface::sound3d_resume(const string & sound3dId, int index)
{
	_core->getSound3dPlayer()->resumeSound3d(sound3dId, index);
}

void EngineInterface::sound3d_stop(const string & sound3dId, int index)
{
	_core->getSound3dPlayer()->stopSound3d(sound3dId, index);
}

const vector<string> EngineInterface::sound3d_getIds() const
{
	vector<string> result = {};

	for(const auto & [sound3dId, sound3d] : _core->getSound3dManager()->getSound3ds())
	{
		result.push_back(sound3d->getId());
	}

	return result;
}

const string & EngineInterface::sound3d_getAudioPath(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound3d(sound3dId)->getAudioPath();
}

const fvec3 & EngineInterface::sound3d_getPosition(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound3d(sound3dId)->getPosition();
}

const float EngineInterface::sound3d_getMaxDistance(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound3d(sound3dId)->getMaxDistance();
}

const float EngineInterface::sound3d_getMaxVolume(const string & sound3dId) const
{
	return _core->getSound3dManager()->getSound3d(sound3dId)->getMaxVolume();
}

const bool EngineInterface::sound3d_isExisting(const string & sound3dId) const
{
	return _core->getSound3dManager()->isSound3dExisting(sound3dId);
}

const bool EngineInterface::sound3d_isStarted(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->isSound3dStarted(sound3dId, index);
}

const bool EngineInterface::sound3d_isPaused(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->isSound3dPaused(sound3dId, index);
}

const bool EngineInterface::sound3d_isDeviceConnected() const
{
	return _core->getSound3dPlayer()->isDeviceConnected();
}

const float EngineInterface::sound3d_getVolume(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSound3dVolume(sound3dId, index);
}

const float EngineInterface::sound3d_getLeftIntensity(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSound3dLeftIntensity(sound3dId, index);
}

const float EngineInterface::sound3d_getRightIntensity(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSound3dRightIntensity(sound3dId, index);
}

const int EngineInterface::sound3d_getStartedCount(const string & sound3dId) const
{
	return _core->getSound3dPlayer()->getStartedSound3dCount(sound3dId);
}

const int EngineInterface::sound3d_getCurrentTime(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSound3dCurrentTime(sound3dId, index);
}

const int EngineInterface::sound3d_getPlayCount(const string & sound3dId, int index) const
{
	return _core->getSound3dPlayer()->getSound3dPlayCount(sound3dId, index);
}
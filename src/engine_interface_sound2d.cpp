#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound2d_create(const string & sound2dId, const string & audioPath)
{
	_core->getSound2dManager()->createSound2d(sound2dId, audioPath);
}

void EngineInterface::sound2d_delete(const string & sound2dId)
{
	const auto startedSound2dCount = _core->getSound2dPlayer()->getStartedSound2dCount(sound2dId);

	for(int index = 0; index < startedSound2dCount; index++)
	{
		sound2d_stop(sound2dId, 0);
	}

	_core->getSound2dManager()->deleteSound2d(sound2dId);
}

void EngineInterface::sound2d_start(const string & sound2dId, int playCount, float startTime)
{
	_core->getSound2dPlayer()->startSound2d(sound2dId, playCount, startTime);
}

void EngineInterface::sound2d_pause(const string & sound2dId, int index)
{
	_core->getSound2dPlayer()->pauseSound2d(sound2dId, index);
}

void EngineInterface::sound2d_resume(const string & sound2dId, int index)
{
	_core->getSound2dPlayer()->resumeSound2d(sound2dId, index);
}

void EngineInterface::sound2d_stop(const string & sound2dId, int index)
{
	_core->getSound2dPlayer()->stopSound2d(sound2dId, index);
}

void EngineInterface::sound2d_setVolume(const string & sound2dId, int index, float value)
{
	_core->getSound2dPlayer()->setSound2dVolume(sound2dId, index, value);
}

void EngineInterface::sound2d_setLeftIntensity(const string & sound2dId, int index, float value)
{
	_core->getSound2dPlayer()->setSound2dLeftIntensity(sound2dId, index, value);
}

void EngineInterface::sound2d_setRightIntensity(const string & sound2dId, int index, float value)
{
	_core->getSound2dPlayer()->setSound2dRightIntensity(sound2dId, index, value);
}

const vector<string> EngineInterface::sound2d_getIds() const
{
	vector<string> result = {};

	for(const auto & [sound2dId, sound2d] : _core->getSound2dManager()->getSound2ds())
	{
		result.push_back(sound2d->getId());
	}

	return result;
}

const string & EngineInterface::sound2d_getAudioPath(const string & sound2dId) const
{
	return _core->getSound2dManager()->getSound2d(sound2dId)->getAudioPath();
}

const bool EngineInterface::sound2d_isExisting(const string & sound2dId) const
{
	return _core->getSound2dManager()->isSound2dExisting(sound2dId);
}

const bool EngineInterface::sound2d_isStarted(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->isSound2dStarted(sound2dId, index);
}

const bool EngineInterface::sound2d_isPaused(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->isSound2dPaused(sound2dId, index);
}

const bool EngineInterface::sound2d_isDeviceConnected() const
{
	return _core->getSound2dPlayer()->isDeviceConnected();
}

const float EngineInterface::sound2d_getVolume(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSound2dVolume(sound2dId, index);
}

const float EngineInterface::sound2d_getLeftIntensity(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSound2dLeftIntensity(sound2dId, index);
}

const float EngineInterface::sound2d_getRightIntensity(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSound2dRightIntensity(sound2dId, index);
}

const int EngineInterface::sound2d_getStartedCount(const string & sound2dId) const
{
	return _core->getSound2dPlayer()->getStartedSound2dCount(sound2dId);
}

const float EngineInterface::sound2d_getCurrentTime(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSound2dCurrentTime(sound2dId, index);
}

const int EngineInterface::sound2d_getPlayCount(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSound2dPlayCount(sound2dId, index);
}
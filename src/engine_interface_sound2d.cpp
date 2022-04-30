#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound2d_create(const string & sound2dId, const string & audioPath)
{
	_core->getSound2dManager()->createSound2d(sound2dId, audioPath);
}

void EngineInterface::sound2d_delete(const string & sound2dId)
{
	for(int index = 0; index < _core->getSound2dPlayer()->getStartedSoundCount(sound2dId); index++)
	{
		sound2d_stop(sound2dId, index);
	}

	_core->getSound2dManager()->deleteSound2d(sound2dId);
}

void EngineInterface::sound2d_start(const string & sound2dId, int playCount)
{
	_core->getSound2dPlayer()->startSound(sound2dId, playCount);
}

void EngineInterface::sound2d_pause(const string & sound2dId, int index)
{
	_core->getSound2dPlayer()->pauseSound(sound2dId, index);
}

void EngineInterface::sound2d_resume(const string & sound2dId, int index)
{
	_core->getSound2dPlayer()->resumeSound(sound2dId, index);
}

void EngineInterface::sound2d_stop(const string & sound2dId, int index)
{
	_core->getSound2dPlayer()->stopSound(sound2dId, index);
}

void EngineInterface::sound2d_setVolume(const string & sound2dId, int index, float value)
{
	_core->getSound2dPlayer()->setSoundVolume(sound2dId, index, value);
}

void EngineInterface::sound2d_setLeftIntensity(const string & sound2dId, int index, float value)
{
	_core->getSound2dPlayer()->setSoundLeftIntensity(sound2dId, index, value);
}

void EngineInterface::sound2d_setRightIntensity(const string & sound2dId, int index, float value)
{
	_core->getSound2dPlayer()->setSoundRightIntensity(sound2dId, index, value);
}

const vector<string> EngineInterface::sound2d_getIds() const
{
	vector<string> result;

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
	return _core->getSound2dPlayer()->isSoundPaused(sound2dId, index);
}

const bool EngineInterface::sound2d_isDeviceConnected() const
{
	return _core->getSound2dPlayer()->isDeviceConnected();
}

const float EngineInterface::sound2d_getVolume(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSoundVolume(sound2dId, index);
}

const float EngineInterface::sound2d_getLeftIntensity(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSoundLeftIntensity(sound2dId, index);
}

const float EngineInterface::sound2d_getRightIntensity(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSoundRightIntensity(sound2dId, index);
}

const int EngineInterface::sound2d_getStartedCount(const string & sound2dId) const
{
	return _core->getSound2dPlayer()->getStartedSoundCount(sound2dId);
}

const int EngineInterface::sound2d_getTime(const string & sound2dId, int index) const
{
	return _core->getSound2dPlayer()->getSoundTime(sound2dId, index);
}
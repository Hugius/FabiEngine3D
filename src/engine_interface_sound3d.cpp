#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound3d_create(const string & id, const string & audioPath)
{
	_core->getSound3dManager()->createSound(id, audioPath);
}

void EngineInterface::sound3d_delete(const string & id)
{
	for(unsigned int index = 0; index < _core->getSound3dPlayer()->getStartedSoundCount(id); index++)
	{
		sound3d_stop(id, index);
	}

	_core->getSound3dManager()->deleteSound(id);
}

void EngineInterface::sound3d_setPosition(const string & id, const fvec3 & value)
{
	_core->getSound3dManager()->getSound(id)->setPosition(value);
}

void EngineInterface::sound3d_move(const string & id, const fvec3 & change)
{
	_core->getSound3dManager()->getSound(id)->move(change);
}

void EngineInterface::sound3d_moveTo(const string & id, const fvec3 & target, float speed)
{
	_core->getSound3dManager()->getSound(id)->moveTo(target, speed);
}

void EngineInterface::sound3d_setMaxVolume(const string & id, float value)
{
	_core->getSound3dManager()->getSound(id)->setMaxVolume(value);
}

void EngineInterface::sound3d_setMaxDistance(const string & id, float value)
{
	_core->getSound3dManager()->getSound(id)->setMaxDistance(value);
}

void EngineInterface::sound3d_start(const string & id, int playCount)
{
	_core->getSound3dPlayer()->startSound(id, playCount);
}

void EngineInterface::sound3d_pause(const string & id, unsigned int index)
{
	_core->getSound3dPlayer()->pauseSound(id, index);
}

void EngineInterface::sound3d_resume(const string & id, unsigned int index)
{
	_core->getSound3dPlayer()->resumeSound(id, index);
}

void EngineInterface::sound3d_stop(const string & id, unsigned int index)
{
	_core->getSound3dPlayer()->stopSound(id, index);
}

const vector<string> EngineInterface::sound3d_getIds() const
{
	vector<string> result;

	for(const auto & [soundId, sound] : _core->getSound3dManager()->getSounds())
	{
		result.push_back(sound->getId());
	}

	return result;
}

const string & EngineInterface::sound3d_getAudioPath(const string & id) const
{
	return _core->getSound3dManager()->getSound(id)->getAudioPath();
}

const fvec3 & EngineInterface::sound3d_getPosition(const string & id) const
{
	return _core->getSound3dManager()->getSound(id)->getPosition();
}

const float EngineInterface::sound3d_getMaxDistance(const string & id) const
{
	return _core->getSound3dManager()->getSound(id)->getMaxDistance();
}

const float EngineInterface::sound3d_getMaxVolume(const string & id) const
{
	return _core->getSound3dManager()->getSound(id)->getMaxVolume();
}

const bool EngineInterface::sound3d_isExisting(const string & id) const
{
	return _core->getSound3dManager()->isSoundExisting(id);
}

const bool EngineInterface::sound3d_isStarted(const string & id, unsigned int index) const
{
	return _core->getSound3dPlayer()->isSoundStarted(id, index);
}

const bool EngineInterface::sound3d_isPaused(const string & id, unsigned int index) const
{
	return _core->getSound3dPlayer()->isSoundPaused(id, index);
}

const bool EngineInterface::sound3d_isDeviceConnected() const
{
	return _core->getSound3dPlayer()->isDeviceConnected();
}

const float EngineInterface::sound3d_getVolume(const string & id, unsigned int index) const
{
	return _core->getSound3dPlayer()->getSoundVolume(id, index);
}

const float EngineInterface::sound3d_getLeftIntensity(const string & id, unsigned int index) const
{
	return _core->getSound3dPlayer()->getSoundLeftIntensity(id, index);
}

const float EngineInterface::sound3d_getRightIntensity(const string & id, unsigned int index) const
{
	return _core->getSound3dPlayer()->getSoundRightIntensity(id, index);
}

const int EngineInterface::sound3d_getStartedCount(const string & id) const
{
	return _core->getSound3dPlayer()->getStartedSoundCount(id);
}

const int EngineInterface::sound3d_getTime(const string & id, unsigned int index) const
{
	return _core->getSound3dPlayer()->getSoundTime(id, index);
}
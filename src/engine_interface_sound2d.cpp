#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound2d_create(const string& id, const string& audioPath)
{
	_core->getSound2dManager()->createSound(id, audioPath);
}

void EngineInterface::sound2d_delete(const string& id)
{
	if(_core->getSound2dManager()->isSoundExisting(id))
	{
		if(_core->getSound2dPlayer()->isSoundStarted(_core->getSound2dManager()->getSound(id)))
		{
			_core->getSound2dPlayer()->stopSound(_core->getSound2dManager()->getSound(id), 0);
		}
	}

	_core->getSound2dManager()->deleteSound(id);
}

void EngineInterface::sound2d_start(const string& id, int playCount, unsigned int fadeMS, bool mustForce)
{
	_core->getSound2dPlayer()->startSound(_core->getSound2dManager()->getSound(id), playCount, fadeMS, mustForce);
}

void EngineInterface::sound2d_pause(const string& id)
{
	_core->getSound2dPlayer()->pauseSound(_core->getSound2dManager()->getSound(id));
}

void EngineInterface::sound2d_resume(const string& id)
{
	_core->getSound2dPlayer()->resumeSound(_core->getSound2dManager()->getSound(id));
}

void EngineInterface::sound2d_stop(const string& id, unsigned int fadeMS)
{
	_core->getSound2dPlayer()->stopSound(_core->getSound2dManager()->getSound(id), fadeMS);
}

void EngineInterface::sound2d_setVolume(const string& id, float value)
{
	_core->getSound2dManager()->getSound(id).setVolume(value);
}

const vector<string> EngineInterface::sound2d_getIds() const
{
	vector<string> result;

	for(const auto& chunk : _core->getSound2dManager()->getSounds())
	{
		result.push_back(chunk.getId());
	}

	return result;
}

const string& EngineInterface::sound2d_getAudioPath(const string& id) const
{
	return _core->getSound2dManager()->getSound(id).getAudioPath();
}

const bool EngineInterface::sound2d_isExisting(const string& id) const
{
	return _core->getSound2dManager()->isSoundExisting(id);
}

const bool EngineInterface::sound2d_isStarted(const string& id) const
{
	return _core->getSound2dPlayer()->isSoundStarted(_core->getSound2dManager()->getSound(id));
}

const bool EngineInterface::sound2d_isPaused(const string& id) const
{
	return _core->getSound2dPlayer()->isSoundPaused(_core->getSound2dManager()->getSound(id));
}

const float EngineInterface::sound2d_getVolume(const string& id) const
{
	return _core->getSound2dManager()->getSound(id).getVolume();
}
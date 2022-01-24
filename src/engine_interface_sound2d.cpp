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

void EngineInterface::sound2d_deleteAll()
{
	sound2d_stopAll();

	_core->getSound2dManager()->deleteSounds();
}

void EngineInterface::sound2d_start(const string& id, int playCount, unsigned int fadeMS, bool mustForce)
{
	auto sound = _core->getSound2dManager()->getSound(id);

	if(!_core->getSound2dPlayer()->isChannelAvailable())
	{
		Logger::throwWarning("Tried to play sound2D with id \"", id, "\": no audio channels available!");
		return;
	}
	if(_core->getSound2dPlayer()->isSoundStarted(sound) && !mustForce)
	{
		Logger::throwWarning("Tried to play sound2D with id \"", id, "\": sound is already started!");
		return;
	}

	_core->getSound2dPlayer()->startSound(sound, playCount, fadeMS, mustForce);
}

void EngineInterface::sound2d_pause(const string& id)
{
	auto sound = _core->getSound2dManager()->getSound(id);

	if(!_core->getSound2dPlayer()->isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause sound2D with id \"", id, "\": sound is not playing!");
		return;
	}
	if(_core->getSound2dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause sound2D with id \"", id, "\": sound is already paused!");
		return;
	}

	_core->getSound2dPlayer()->pauseSound(sound);
}

void EngineInterface::sound2d_pauseAll()
{
	_core->getSound2dPlayer()->pauseSounds(_core->getSound2dManager()->getSounds());
}

void EngineInterface::sound2d_resume(const string& id)
{
	auto sound = _core->getSound2dManager()->getSound(id);

	if(!_core->getSound2dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume sound2D with id \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->getSound2dPlayer()->resumeSound(sound);
}

void EngineInterface::sound2d_resumeAll()
{
	_core->getSound2dPlayer()->resumeSounds(_core->getSound2dManager()->getSounds());
}

void EngineInterface::sound2d_stop(const string& id, unsigned int fadeMS)
{
	auto sound = _core->getSound2dManager()->getSound(id);

	if(!_core->getSound2dPlayer()->isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop sound2D with id \"", id, "\": sound is not started!");
		return;
	}

	_core->getSound2dPlayer()->stopSound(sound, fadeMS);
}

void EngineInterface::sound2d_stopAll()
{
	_core->getSound2dPlayer()->stopSounds(_core->getSound2dManager()->getSounds());
}

void EngineInterface::sound2d_setVolume(const string& id, float value)
{
	_core->getSound2dManager()->getSound(id).setVolume(value);
}

const vector<string> EngineInterface::sound2d_getIDs() const
{
	vector<string> result;

	for(const auto& chunk : _core->getSound2dManager()->getSounds())
	{
		result.push_back(chunk.getID());
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

const bool EngineInterface::sound2d_isPlaying(const string& id) const
{
	return _core->getSound2dPlayer()->isSoundPlaying(_core->getSound2dManager()->getSound(id));
}

const bool EngineInterface::sound2d_isPaused(const string& id) const
{
	return _core->getSound2dPlayer()->isSoundPaused(_core->getSound2dManager()->getSound(id));
}

const float EngineInterface::sound2d_getVolume(const string& id) const
{
	return _core->getSound2dManager()->getSound(id).getVolume();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound2d_create(const string& ID, const string& audioPath)
{
	_core->getSound2dManager()->createSound(ID, audioPath);
}

void EngineInterface::sound2d_delete(const string& ID)
{
	if(_core->getSound2dManager()->isSoundExisting(ID))
	{
		if(_core->getSound2dPlayer()->isSoundStarted(_core->getSound2dManager()->getSound(ID)))
		{
			_core->getSound2dPlayer()->stopSound(_core->getSound2dManager()->getSound(ID), 0);
		}
	}

	_core->getSound2dManager()->deleteSound(ID);
}

void EngineInterface::sound2d_deleteAll()
{
	sound2d_stopAll();

	_core->getSound2dManager()->deleteSounds();
}

void EngineInterface::sound2d_start(const string& ID, int playCount, unsigned int fadeMS, bool mustForce)
{
	auto sound = _core->getSound2dManager()->getSound(ID);

	if(!_core->getSound2dPlayer()->isChannelAvailable())
	{
		Logger::throwWarning("Tried to play sound2D with ID \"", ID, "\": no audio channels available!");
		return;
	}
	if(_core->getSound2dPlayer()->isSoundStarted(sound) && !mustForce)
	{
		Logger::throwWarning("Tried to play sound2D with ID \"", ID, "\": sound is already started!");
		return;
	}

	_core->getSound2dPlayer()->startSound(sound, playCount, fadeMS, mustForce);
}

void EngineInterface::sound2d_pause(const string& ID)
{
	auto sound = _core->getSound2dManager()->getSound(ID);

	if(!_core->getSound2dPlayer()->isSoundPlaying(sound))
	{
		Logger::throwWarning("Tried to pause sound2D with ID \"", ID, "\": sound is not playing!");
		return;
	}
	if(_core->getSound2dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to pause sound2D with ID \"", ID, "\": sound is already paused!");
		return;
	}

	_core->getSound2dPlayer()->pauseSound(sound);
}

void EngineInterface::sound2d_pauseAll()
{
	_core->getSound2dPlayer()->pauseSounds(_core->getSound2dManager()->getSounds());
}

void EngineInterface::sound2d_resume(const string& ID)
{
	auto sound = _core->getSound2dManager()->getSound(ID);

	if(!_core->getSound2dPlayer()->isSoundPaused(sound))
	{
		Logger::throwWarning("Tried to resume sound2D with ID \"", sound.getID(), "\": sound is not paused!");
		return;
	}

	_core->getSound2dPlayer()->resumeSound(sound);
}

void EngineInterface::sound2d_resumeAll()
{
	_core->getSound2dPlayer()->resumeSounds(_core->getSound2dManager()->getSounds());
}

void EngineInterface::sound2d_stop(const string& ID, unsigned int fadeMS)
{
	auto sound = _core->getSound2dManager()->getSound(ID);

	if(!_core->getSound2dPlayer()->isSoundStarted(sound))
	{
		Logger::throwWarning("Tried to stop sound2D with ID \"", ID, "\": sound is not started!");
		return;
	}

	_core->getSound2dPlayer()->stopSound(sound, fadeMS);
}

void EngineInterface::sound2d_stopAll()
{
	_core->getSound2dPlayer()->stopSounds(_core->getSound2dManager()->getSounds());
}

void EngineInterface::sound2d_setVolume(const string& ID, float value)
{
	_core->getSound2dManager()->getSound(ID).setVolume(value);
}
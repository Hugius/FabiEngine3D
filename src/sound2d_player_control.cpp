#include "sound2d_player.hpp"

using std::make_shared;

void Sound2dPlayer::startSound(const string& id, int playCount)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(isSoundStarted(id))
	{
		abort();
	}
	if((playCount < -1) || (playCount == 0))
	{
		abort();
	}

	const auto channelIndex = _getFreeChannel();

	const auto newSound = make_shared<StartedSound2D>(id, channelIndex, _sound2dManager->getSound(id)->getWaveBuffer());

	newSound->setPlayCount(playCount);

	_startedSounds[channelIndex] = newSound;
}

void Sound2dPlayer::pauseSound(const string& id)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();
	}
	if(isSoundPaused(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds)
	{
		startedSound->pause();
	}
}

void Sound2dPlayer::resumeSound(const string& id)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();

	}
	if(!isSoundPaused(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds)
	{
		startedSound->resume();
	}
}

void Sound2dPlayer::stopSound(const string& id)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();
	}

	for(unsigned int i = 0; i < _startedSounds.size(); i++)
	{
		if(_startedSounds[i] != nullptr)
		{
			if(id == _startedSounds[i]->getSoundId())
			{
				_startedSounds[i] = nullptr;
			}
		}
	}
}
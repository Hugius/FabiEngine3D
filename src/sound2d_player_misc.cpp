#include "sound2d_player.hpp"

void Sound2dPlayer::inject(shared_ptr<Sound2dManager> sound2dManager)
{
	_sound2dManager = sound2dManager;
}

const unsigned int Sound2dPlayer::_getFreeChannel() const
{
	for(unsigned int i = 0; i < _startedSounds.size(); i++)
	{
		if(_startedSounds[i] == nullptr)
		{
			return i;
		}
	}

	abort();
}

const bool Sound2dPlayer::isChannelAvailable() const
{
	for(const auto& startedSound : _startedSounds)
	{
		if(startedSound == nullptr)
		{
			return true;
		}
	}

	return false;
}

const bool Sound2dPlayer::isSoundStarted(const string& id) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds)
	{
		if(startedSound != nullptr)
		{
			if(id == startedSound->getSoundId())
			{
				return true;
			}
		}
	}

	return false;
}

const bool Sound2dPlayer::isSoundPaused(const string& id) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds)
	{
		if(startedSound != nullptr)
		{
			if(id == startedSound->getSoundId())
			{
				return startedSound->isPaused();
			}
		}
	}

	abort();
}
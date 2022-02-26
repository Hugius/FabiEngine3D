#include "sound2d_player.hpp"

void Sound2dPlayer::inject(shared_ptr<Sound2dManager> sound2dManager)
{
	_sound2dManager = sound2dManager;
}

const bool Sound2dPlayer::isChannelAvailable() const
{
	return (_channelCounter < MAX_CHANNEL_COUNT);
}

const bool Sound2dPlayer::isSoundStarted(const string& id) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}

	return (_startedSounds.find(id) != _startedSounds.end());
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

	return _startedSounds.at(id)[0]->isPaused();
}
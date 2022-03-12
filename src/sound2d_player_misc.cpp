#include "sound2d_player.hpp"

void Sound2dPlayer::inject(shared_ptr<Sound2dManager> sound2dManager)
{
	_sound2dManager = sound2dManager;
}

const bool Sound2dPlayer::isDeviceConnected() const
{
	return (waveOutGetNumDevs() > 0);
}

void Sound2dPlayer::_terminateSounds()
{
	for(const auto& [key, startedSounds] : _startedSounds)
	{
		for(unsigned int index = 0; index < startedSounds.size(); index++)
		{
			delete[] _startedSounds.at(key)[index]->getHeader()->lpData;
			delete _startedSounds.at(key)[index]->getHeader();
		}
	}

	_startedSounds.clear();

	_channelCounter = 0;
}

void Sound2dPlayer::_processVolumeChange(unsigned int sampleCount, short* originalSamples, short* currentSamples, float volume)
{
	for(unsigned int i = 0; i < sampleCount; i++)
	{
		currentSamples[i] = static_cast<short>(static_cast<float>(originalSamples[i]) * volume);
	}
}

void Sound2dPlayer::_terminateSound(const string& id, unsigned int index)
{
	delete[] _startedSounds.at(id)[index]->getHeader()->lpData;
	delete _startedSounds.at(id)[index]->getHeader();

	_startedSounds.at(id).erase(_startedSounds.at(id).begin() + index);

	if(_startedSounds.at(id).empty())
	{
		_startedSounds.erase(id);
	}

	_channelCounter--;
}

const bool Sound2dPlayer::isChannelAvailable() const
{
	return (_channelCounter < MAX_CHANNEL_COUNT);
}

const bool Sound2dPlayer::isSoundStarted(const string& id, unsigned int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		return false;
	}

	return (index < _startedSounds.at(id).size());
}

const bool Sound2dPlayer::isSoundPaused(const string& id, unsigned int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->isPaused();
}

const float Sound2dPlayer::getSoundVolume(const string& id, unsigned int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getVolume();
}

const int Sound2dPlayer::getPlayCount(const string& id, unsigned int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getPlayCount();
}

const unsigned int Sound2dPlayer::getStartedSoundCount(const string& id) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		return 0;
	}

	return static_cast<unsigned int>(_startedSounds.at(id).size());
}
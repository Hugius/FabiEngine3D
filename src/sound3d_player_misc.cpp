#include "sound3d_player.hpp"

void Sound3dPlayer::inject(shared_ptr<Sound3dManager> sound3dManager)
{
	_sound3dManager = sound3dManager;
}

void Sound3dPlayer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const bool Sound3dPlayer::isDeviceConnected() const
{
	return (waveOutGetNumDevs() > 0);
}

const bool Sound3dPlayer::isChannelAvailable() const
{
	return (_channelCounter < MAX_CHANNEL_COUNT);
}

const bool Sound3dPlayer::isSoundStarted(const string& id, unsigned int index) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		return false;
	}

	return (index < _startedSounds.at(id).size());
}

const bool Sound3dPlayer::isSoundPaused(const string& id, unsigned int index) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->isPaused();
}

const float Sound3dPlayer::getSoundVolume(const string& id, unsigned int index) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getVolume();
}

const float Sound3dPlayer::getSoundLeftIntensity(const string& id, unsigned int index) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getLeftIntensity();
}

const float Sound3dPlayer::getSoundRightIntensity(const string& id, unsigned int index) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getRightIntensity();
}

const int Sound3dPlayer::getPlayCount(const string& id, unsigned int index) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getPlayCount();
}

const unsigned int Sound3dPlayer::getStartedSoundCount(const string& id) const
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		return 0;
	}

	return static_cast<unsigned int>(_startedSounds.at(id).size());
}


void Sound3dPlayer::_terminateSounds()
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

void Sound3dPlayer::_processVolumeChange(unsigned int sampleCount, short* originalSamples, short* currentSamples, float volume, float leftIntensity, float rightIntensity)
{
	for(unsigned int index = 0; index < sampleCount; index++)
	{
		if(((index + 1) % 2) == 0)
		{
			currentSamples[index] = static_cast<short>(static_cast<float>(originalSamples[index]) * volume * rightIntensity);
		}
		else
		{
			currentSamples[index] = static_cast<short>(static_cast<float>(originalSamples[index]) * volume * leftIntensity);
		}
	}
}

void Sound3dPlayer::_terminateSound(const string& id, unsigned int index)
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
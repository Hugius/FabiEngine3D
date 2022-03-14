#include "sound3d_player.hpp"

using std::future_status;
using std::chrono::seconds;

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
	for(const auto& [soundId, instances] : _startedSounds)
	{
		for(unsigned int instanceIndex = 0; instanceIndex < instances.size(); instanceIndex++)
		{
			_terminateSound(soundId, instanceIndex);
		}
	}
}

void Sound3dPlayer::_terminateSound(const string& id, unsigned int index)
{
	if(!_volumeThreadQueue.empty())
	{
		if((id == _volumeThreadQueue.front().first) && (index == _volumeThreadQueue.front().second))
		{
			while(true)
			{
				if(_volumeThread.wait_for(seconds(0)) == future_status::ready)
				{
					break;
				}
			}
		}
	}

	delete[] _startedSounds.at(id)[index]->getHeader()->lpData;
	delete _startedSounds.at(id)[index]->getHeader();

	_startedSounds.at(id).erase(_startedSounds.at(id).begin() + index);

	if(_startedSounds.at(id).empty())
	{
		_startedSounds.erase(id);
	}

	_channelCounter--;
}

void Sound3dPlayer::_updateSamplesVolume(unsigned int sampleCount, short* originalSamples, short* startedSamples, float volume, float leftIntensity, float rightIntensity)
{
	for(unsigned int sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++)
	{
		if(((sampleIndex + 1) % 2) == 0)
		{
			startedSamples[sampleIndex] = static_cast<short>(static_cast<float>(originalSamples[sampleIndex]) * volume * rightIntensity);
		}
		else
		{
			startedSamples[sampleIndex] = static_cast<short>(static_cast<float>(originalSamples[sampleIndex]) * volume * leftIntensity);
		}
	}
}
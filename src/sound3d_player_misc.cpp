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

const bool Sound3dPlayer::isSoundStarted(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}

	if(_startedSounds.find(sound3dId) == _startedSounds.end())
	{
		return false;
	}

	return (index < _startedSounds.at(sound3dId).size());
}

const bool Sound3dPlayer::isSoundPaused(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSounds.at(sound3dId)[index]->isPaused();
}

const float Sound3dPlayer::getSoundVolume(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSounds.at(sound3dId)[index]->getVolume();
}

const float Sound3dPlayer::getSoundLeftIntensity(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSounds.at(sound3dId)[index]->getLeftIntensity();
}

const float Sound3dPlayer::getSoundRightIntensity(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSounds.at(sound3dId)[index]->getRightIntensity();
}

const int Sound3dPlayer::getPlayCount(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSounds.at(sound3dId)[index]->getPlayCount();
}

const int Sound3dPlayer::getStartedSoundCount(const string & sound3dId) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}

	if(_startedSounds.find(sound3dId) == _startedSounds.end())
	{
		return 0;
	}

	return static_cast<int>(_startedSounds.at(sound3dId).size());
}


void Sound3dPlayer::_terminateSounds()
{
	for(const auto & [soundId, instances] : _startedSounds)
	{
		for(int instanceIndex = 0; instanceIndex < static_cast<int>(instances.size()); instanceIndex++)
		{
			_terminateSound(soundId, instanceIndex);
		}
	}
}

void Sound3dPlayer::_terminateSound(const string & sound3dId, int index)
{
	if(!_volumeThreadQueue.empty())
	{
		if((sound3dId == _volumeThreadQueue.front().first) && (index == _volumeThreadQueue.front().second))
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

	delete[] _startedSounds.at(sound3dId)[index]->getHeader()->lpData;
	delete _startedSounds.at(sound3dId)[index]->getHeader();

	_startedSounds.at(sound3dId).erase(_startedSounds.at(sound3dId).begin() + index);

	if(_startedSounds.at(sound3dId).empty())
	{
		_startedSounds.erase(sound3dId);
	}
}

void Sound3dPlayer::_updateSamplesVolume(int sampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity)
{
	for(int sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++)
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

const int Sound3dPlayer::getSoundTime(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	auto currentSoundTime = new MMTIME();
	currentSoundTime->wType = TIME_SAMPLES;

	waveOutGetPosition(_startedSounds.at(sound3dId)[index]->getHandle(), currentSoundTime, sizeof(MMTIME));

	const auto sampleIndex = currentSoundTime->u.sample;
	const auto sampleRate = _sound3dManager->getSound(sound3dId)->getWaveBuffer()->getFormat()->nSamplesPerSec;
	const auto result = static_cast<int>(static_cast<float>(sampleIndex) / static_cast<float>(sampleRate));

	delete currentSoundTime;

	return result;
}
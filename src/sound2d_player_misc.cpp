#include "sound2d_player.hpp"

using std::future_status;
using std::chrono::seconds;

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
	for(const auto & [soundId, instances] : _startedSounds)
	{
		for(int instanceIndex = 0; instanceIndex < static_cast<int>(instances.size()); instanceIndex++)
		{
			_terminateSound(soundId, instanceIndex);
		}
	}
}

void Sound2dPlayer::_updateSamplesVolume(int sampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity)
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

void Sound2dPlayer::_terminateSound(const string & id, int index)
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
}

const bool Sound2dPlayer::isSoundStarted(const string & id, int index) const
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

const bool Sound2dPlayer::isSoundPaused(const string & id, int index) const
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

const float Sound2dPlayer::getSoundVolume(const string & id, int index) const
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

const float Sound2dPlayer::getSoundLeftIntensity(const string & id, int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getLeftIntensity();
}

const float Sound2dPlayer::getSoundRightIntensity(const string & id, int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	return _startedSounds.at(id)[index]->getRightIntensity();
}

const int Sound2dPlayer::getPlayCount(const string & id, int index) const
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

const int Sound2dPlayer::getStartedSoundCount(const string & id) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		return 0;
	}

	return static_cast<int>(_startedSounds.at(id).size());
}

const int Sound2dPlayer::getSoundTime(const string & id, int index) const
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	auto currentSoundTime = new MMTIME();
	currentSoundTime->wType = TIME_SAMPLES;

	waveOutGetPosition(_startedSounds.at(id)[index]->getHandle(), currentSoundTime, sizeof(MMTIME));

	const auto sampleIndex = currentSoundTime->u.sample;
	const auto sampleRate = _sound2dManager->getSound(id)->getWaveBuffer()->getFormat()->nSamplesPerSec;
	const auto result = static_cast<int>(static_cast<float>(sampleIndex) / static_cast<float>(sampleRate));

	delete currentSoundTime;

	return result;
}
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

void Sound2dPlayer::_terminateSound2ds()
{
	for(const auto & [sound2dId, startedSound2ds] : _startedSound2ds)
	{
		for(int index = 0; index < static_cast<int>(startedSound2ds.size()); index++)
		{
			_terminateSound2d(sound2dId, index);
		}
	}
}

void Sound2dPlayer::_updateSamplesVolume(int originalSampleCount, int startedSampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity)
{
	const auto startIndex = (originalSampleCount - startedSampleCount);

	for(int index = startIndex; index < originalSampleCount; index++)
	{
		if(((index + 1) % 2) == 0)
		{
			startedSamples[index - startIndex] = static_cast<short>(static_cast<float>(originalSamples[index]) * volume * rightIntensity);
		}
		else
		{
			startedSamples[index - startIndex] = static_cast<short>(static_cast<float>(originalSamples[index]) * volume * leftIntensity);
		}
	}
}

void Sound2dPlayer::_terminateSound2d(const string & sound2dId, int index)
{
	if(!_volumeThreadQueue.empty())
	{
		if((sound2dId == _volumeThreadQueue.front().first) && (index == _volumeThreadQueue.front().second))
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

	delete[] _startedSound2ds.at(sound2dId)[index]->getHeader()->lpData;
	delete _startedSound2ds.at(sound2dId)[index]->getHeader();

	_startedSound2ds.at(sound2dId).erase(_startedSound2ds.at(sound2dId).begin() + index);

	if(_startedSound2ds.at(sound2dId).empty())
	{
		_startedSound2ds.erase(sound2dId);
	}
}

const bool Sound2dPlayer::isSound2dStarted(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(_startedSound2ds.find(sound2dId) == _startedSound2ds.end())
	{
		return false;
	}

	return (index < _startedSound2ds.at(sound2dId).size());
}

const bool Sound2dPlayer::isSound2dPaused(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	return _startedSound2ds.at(sound2dId)[index]->isPaused();
}

const float Sound2dPlayer::getSound2dVolume(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	return _startedSound2ds.at(sound2dId)[index]->getVolume();
}

const float Sound2dPlayer::getSound2dLeftIntensity(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	return _startedSound2ds.at(sound2dId)[index]->getLeftIntensity();
}

const float Sound2dPlayer::getSound2dRightIntensity(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	return _startedSound2ds.at(sound2dId)[index]->getRightIntensity();
}

const int Sound2dPlayer::getSound2dPlayCount(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	return _startedSound2ds.at(sound2dId)[index]->getPlayCount();
}

const int Sound2dPlayer::getStartedSound2dCount(const string & sound2dId) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(_startedSound2ds.find(sound2dId) == _startedSound2ds.end())
	{
		return 0;
	}

	return static_cast<int>(_startedSound2ds.at(sound2dId).size());
}

const int Sound2dPlayer::getSound2dCurrentMilliseconds(const string & sound2dId, int index) const
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	auto currentTime = new MMTIME();

	currentTime->wType = TIME_SAMPLES;

	waveOutGetPosition(_startedSound2ds.at(sound2dId)[index]->getHandle(), currentTime, sizeof(MMTIME));

	const auto sampleIndex = currentTime->u.sample;
	const auto sampleRate = _sound2dManager->getSound2d(sound2dId)->getWaveBuffer()->getFormat()->nSamplesPerSec;
	const auto result = (static_cast<int>(static_cast<float>(sampleIndex) / static_cast<float>(sampleRate)) * 1000);

	delete currentTime;

	return result;
}
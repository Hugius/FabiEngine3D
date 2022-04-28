#include "sound2d_player.hpp"
#include "logger.hpp"

using std::launch;
using std::future_status;
using std::chrono::seconds;

void Sound2dPlayer::update()
{
	vector<pair<string, int>> soundsToStop;

	for(auto & [soundId, instances] : _startedSounds)
	{
		for(int instanceIndex = 0; instanceIndex < static_cast<int>(instances.size()); instanceIndex++)
		{
			if((instances[instanceIndex]->getHeader()->dwFlags & WHDR_DONE) == WHDR_DONE)
			{
				if(instances[instanceIndex]->getPlayCount() != -1)
				{
					instances[instanceIndex]->setPlayCount(instances[instanceIndex]->getPlayCount() - 1);
				}

				if(instances[instanceIndex]->getPlayCount() == 0)
				{
					soundsToStop.push_back({soundId, instanceIndex});
				}
				else
				{
					instances[instanceIndex]->getHeader()->dwFlags = WHDR_PREPARED;

					const auto writeResult = waveOutWrite(instances[instanceIndex]->getHandle(), instances[instanceIndex]->getHeader(), sizeof(WAVEHDR));
					if(writeResult != MMSYSERR_NOERROR)
					{
						if(writeResult == MMSYSERR_NODRIVER)
						{
							_terminateSounds();

							return;
						}
						else
						{
							Logger::throwDebug(writeResult);

							abort();
						}
					}
				}
			}
		}
	}

	for(const auto & [sound2dId, index] : soundsToStop)
	{
		const auto unprepareResult = waveOutUnprepareHeader(_startedSounds.at(sound2dId)[index]->getHandle(), _startedSounds.at(sound2dId)[index]->getHeader(), sizeof(WAVEHDR));
		if(unprepareResult != MMSYSERR_NOERROR)
		{
			if(unprepareResult == MMSYSERR_NODRIVER)
			{
				_terminateSounds();

				return;
			}
			else
			{
				Logger::throwDebug(unprepareResult);

				abort();
			}
		}

		const auto closeResult = waveOutClose(_startedSounds.at(sound2dId)[index]->getHandle());
		if(closeResult != MMSYSERR_NOERROR)
		{
			if(closeResult == MMSYSERR_NODRIVER)
			{
				_terminateSounds();

				return;
			}
			else
			{
				Logger::throwDebug(closeResult);

				abort();
			}
		}

		_terminateSound(sound2dId, index);
	}

	if(_volumeThreadQueue.empty())
	{
		for(auto & [soundId, instances] : _startedSounds)
		{
			for(int instanceIndex = 0; instanceIndex < static_cast<int>(instances.size()); instanceIndex++)
			{
				_volumeThreadQueue.push_back({soundId, instanceIndex});
			}
		}
	}

	if(_volumeThread.valid() && (_volumeThread.wait_for(seconds(0)) == future_status::ready))
	{
		_volumeThreadQueue.erase(_volumeThreadQueue.begin());
		_volumeThread = {};
	}

	while(!_volumeThread.valid() && !_volumeThreadQueue.empty())
	{
		const auto soundId = _volumeThreadQueue.front().first;
		const auto instanceIndex = _volumeThreadQueue.front().second;

		if(!_sound2dManager->isSoundExisting(soundId))
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}
		if(_startedSounds.find(soundId) == _startedSounds.end())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}
		if(instanceIndex >= _startedSounds.at(soundId).size())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}

		const auto startedSound = _startedSounds.at(soundId)[instanceIndex];
		const auto originalSound = _sound2dManager->getSound(soundId);

		const auto sampleCount = (originalSound->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample = 2 bytes
		const auto originalSamples = reinterpret_cast<short *>(originalSound->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
		const auto startedSamples = reinterpret_cast<short *>(startedSound->getHeader()->lpData); // short = 2 bytes

		const auto volume = startedSound->getVolume();
		const auto leftIntensity = startedSound->getLeftIntensity();
		const auto rightIntensity = startedSound->getRightIntensity();

		_volumeThread = async(launch::async, &Sound2dPlayer::_updateSamplesVolume, this, sampleCount, originalSamples, startedSamples, volume, leftIntensity, rightIntensity);
	}
}
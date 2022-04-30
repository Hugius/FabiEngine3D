#include "sound2d_player.hpp"
#include "logger.hpp"

using std::launch;
using std::future_status;
using std::chrono::seconds;

void Sound2dPlayer::update()
{
	vector<pair<string, int>> sound2dsToStop;

	for(auto & [sound2dId, startedSound2ds] : _startedSound2ds)
	{
		for(int instanceIndex = 0; instanceIndex < static_cast<int>(startedSound2ds.size()); instanceIndex++)
		{
			if((startedSound2ds[instanceIndex]->getHeader()->dwFlags & WHDR_DONE) == WHDR_DONE)
			{
				if(startedSound2ds[instanceIndex]->getPlayCount() != -1)
				{
					startedSound2ds[instanceIndex]->setPlayCount(startedSound2ds[instanceIndex]->getPlayCount() - 1);
				}

				if(startedSound2ds[instanceIndex]->getPlayCount() == 0)
				{
					sound2dsToStop.push_back({sound2dId, instanceIndex});
				}
				else
				{
					startedSound2ds[instanceIndex]->getHeader()->dwFlags = WHDR_PREPARED;

					const auto writeResult = waveOutWrite(startedSound2ds[instanceIndex]->getHandle(), startedSound2ds[instanceIndex]->getHeader(), sizeof(WAVEHDR));
					if(writeResult != MMSYSERR_NOERROR)
					{
						if(writeResult == MMSYSERR_NODRIVER)
						{
							_terminateSound2ds();

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

	for(const auto & [sound2dId, index] : sound2dsToStop)
	{
		const auto unprepareResult = waveOutUnprepareHeader(_startedSound2ds.at(sound2dId)[index]->getHandle(), _startedSound2ds.at(sound2dId)[index]->getHeader(), sizeof(WAVEHDR));
		if(unprepareResult != MMSYSERR_NOERROR)
		{
			if(unprepareResult == MMSYSERR_NODRIVER)
			{
				_terminateSound2ds();

				return;
			}
			else
			{
				Logger::throwDebug(unprepareResult);

				abort();
			}
		}

		const auto closeResult = waveOutClose(_startedSound2ds.at(sound2dId)[index]->getHandle());
		if(closeResult != MMSYSERR_NOERROR)
		{
			if(closeResult == MMSYSERR_NODRIVER)
			{
				_terminateSound2ds();

				return;
			}
			else
			{
				Logger::throwDebug(closeResult);

				abort();
			}
		}

		_terminateSound2d(sound2dId, index);
	}

	if(_volumeThreadQueue.empty())
	{
		for(auto & [sound2dId, startedSound2ds] : _startedSound2ds)
		{
			for(int instanceIndex = 0; instanceIndex < static_cast<int>(startedSound2ds.size()); instanceIndex++)
			{
				_volumeThreadQueue.push_back({sound2dId, instanceIndex});
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
		const auto sound2dId = _volumeThreadQueue.front().first;
		const auto instanceIndex = _volumeThreadQueue.front().second;

		if(!_sound2dManager->isSound2dExisting(sound2dId))
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}
		if(_startedSound2ds.find(sound2dId) == _startedSound2ds.end())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}
		if(instanceIndex >= _startedSound2ds.at(sound2dId).size())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}

		const auto startedSound2d = _startedSound2ds.at(sound2dId)[instanceIndex];
		const auto originalSound2d = _sound2dManager->getSound2d(sound2dId);

		const auto sampleCount = (originalSound2d->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample = 2 bytes
		const auto originalSamples = reinterpret_cast<short *>(originalSound2d->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
		const auto startedSamples = reinterpret_cast<short *>(startedSound2d->getHeader()->lpData); // short = 2 bytes

		const auto volume = startedSound2d->getVolume();
		const auto leftIntensity = startedSound2d->getLeftIntensity();
		const auto rightIntensity = startedSound2d->getRightIntensity();

		_volumeThread = async(launch::async, &Sound2dPlayer::_updateSamplesVolume, this, sampleCount, originalSamples, startedSamples, volume, leftIntensity, rightIntensity);
	}
}
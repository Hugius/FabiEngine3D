#include "sound2d_player.hpp"
#include "logger.hpp"

using std::launch;
using std::future_status;
using std::chrono::seconds;

void Sound2dPlayer::update()
{
	unordered_map<string, vector<int>> sound2dsToStop = {};
	vector<pair<string, int>> sound2dsToStart = {};

	for(auto & [sound2dId, startedSound2ds] : _startedSound2ds)
	{
		for(int index = 0; index < static_cast<int>(startedSound2ds.size()); index++)
		{
			if(startedSound2ds[index]->getHeader()->dwFlags == (WHDR_PREPARED | WHDR_DONE))
			{
				if(startedSound2ds[index]->getPlayCount() != -1)
				{
					startedSound2ds[index]->setPlayCount(startedSound2ds[index]->getPlayCount() - 1);
				}

				if(startedSound2ds[index]->getPlayCount() == 0)
				{
					if(sound2dsToStop.find(sound2dId) == sound2dsToStop.end())
					{
						sound2dsToStop.insert({sound2dId, {}});
					}

					sound2dsToStop.at(sound2dId).push_back(index);
				}
				else
				{
					if(startedSound2ds[index]->getHeader()->dwBufferLength < _sound2dManager->getSound2d(sound2dId)->getWaveBuffer()->getHeader()->dwBufferLength)
					{
						if(sound2dsToStop.find(sound2dId) == sound2dsToStop.end())
						{
							sound2dsToStop.insert({sound2dId, {}});
						}

						sound2dsToStop.at(sound2dId).push_back(index);

						sound2dsToStart.push_back({sound2dId, startedSound2ds[index]->getPlayCount()});
					}
					else
					{
						startedSound2ds[index]->getHeader()->dwFlags = WHDR_PREPARED;

						const auto writeResult = waveOutWrite(startedSound2ds[index]->getHandle(), startedSound2ds[index]->getHeader(), sizeof(WAVEHDR));

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
	}

	for(auto & [sound2dId, indices] : sound2dsToStop)
	{
		sort(indices.begin(), indices.end());

		int totalTerminations = 0;

		for(auto & index : indices)
		{
			index -= totalTerminations;

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

			totalTerminations++;
		}
	}

	for(const auto & [sound2dId, playCount] : sound2dsToStart)
	{
		startSound2d(sound2dId, playCount, 0.0f);
	}

	if(_volumeThreadQueue.empty())
	{
		for(auto & [sound2dId, startedSound2ds] : _startedSound2ds)
		{
			for(int index = 0; index < static_cast<int>(startedSound2ds.size()); index++)
			{
				_volumeThreadQueue.push_back({sound2dId, index});
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
		const auto index = _volumeThreadQueue.front().second;

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

		if(index >= _startedSound2ds.at(sound2dId).size())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());

			continue;
		}

		const auto originalSound2d = _sound2dManager->getSound2d(sound2dId);
		const auto startedSound2d = _startedSound2ds.at(sound2dId)[index];
		const auto originalSampleCount = static_cast<int>(originalSound2d->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample (left OR right) = 2 bytes
		const auto startedSampleCount = static_cast<int>(startedSound2d->getHeader()->dwBufferLength / 2); // 1 sample (left OR right) = 2 bytes
		const auto originalSamples = reinterpret_cast<short *>(originalSound2d->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
		const auto startedSamples = reinterpret_cast<short *>(startedSound2d->getHeader()->lpData); // short = 2 bytes
		const auto volume = startedSound2d->getVolume();
		const auto leftIntensity = startedSound2d->getLeftIntensity();
		const auto rightIntensity = startedSound2d->getRightIntensity();

		_volumeThread = async(launch::async, &Sound2dPlayer::_updateSamplesVolume, this, originalSampleCount, startedSampleCount, originalSamples, startedSamples, volume, leftIntensity, rightIntensity);
	}
}
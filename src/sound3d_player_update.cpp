#include "sound3d_player.hpp"
#include "logger.hpp"

using std::launch;
using std::future_status;
using std::chrono::seconds;
using std::clamp;

void Sound3dPlayer::update()
{
	unordered_map<string, vector<int>> sound3dsToStop = {};
	vector<pair<string, int>> sound3dsToStart = {};

	for(auto & [sound3dId, startedSound3ds] : _startedSound3ds)
	{
		const auto sound3d = _sound3dManager->getSound3d(sound3dId);
		const auto cameraPosition = _camera->getPosition();
		const auto distance = Mathematics::calculateDistance(cameraPosition, sound3d->getPosition());
		const auto volume = (clamp((1.0f - (distance / sound3d->getMaxDistance())), 0.0f, 1.0f) * sound3d->getMaxVolume());
		const auto cameraDirection = _camera->getFront();
		const auto sound3dDirection = (cameraPosition - sound3d->getPosition());
		const auto rotationMatrix = Mathematics::createRotationMatrixY(Mathematics::convertToRadians(90.0f));
		const auto rotatedSound3dDirection = (rotationMatrix * fvec4(sound3dDirection.x, sound3dDirection.y, sound3dDirection.z, 1.0f));
		const auto normalizedSound3dDirection = Mathematics::normalize(fvec3(rotatedSound3dDirection.x, rotatedSound3dDirection.y, rotatedSound3dDirection.z));
		const auto dotProduct = Mathematics::calculateDotProduct(normalizedSound3dDirection, cameraDirection);
		const auto leftIntensity = ((dotProduct * 0.5f) + 0.5f);
		const auto rightIntensity = (1.0f - leftIntensity);

		for(int index = 0; index < static_cast<int>(startedSound3ds.size()); index++)
		{
			if(startedSound3ds[index]->getHeader()->dwFlags == (WHDR_PREPARED | WHDR_DONE))
			{
				if(startedSound3ds[index]->getPlayCount() != -1)
				{
					startedSound3ds[index]->setPlayCount(startedSound3ds[index]->getPlayCount() - 1);
				}

				if(startedSound3ds[index]->getPlayCount() == 0)
				{
					if(sound3dsToStop.find(sound3dId) == sound3dsToStop.end())
					{
						sound3dsToStop.insert({sound3dId, {}});
					}

					sound3dsToStop.at(sound3dId).push_back(index);
				}
				else
				{
					if(startedSound3ds[index]->getHeader()->dwBufferLength < _sound3dManager->getSound3d(sound3dId)->getWaveBuffer()->getHeader()->dwBufferLength)
					{
						if(sound3dsToStop.find(sound3dId) == sound3dsToStop.end())
						{
							sound3dsToStop.insert({sound3dId, {}});
						}

						sound3dsToStop.at(sound3dId).push_back(index);

						sound3dsToStart.push_back({sound3dId, startedSound3ds[index]->getPlayCount()});
					}
					else
					{
						startedSound3ds[index]->getHeader()->dwFlags = WHDR_PREPARED;

						const auto writeResult = waveOutWrite(startedSound3ds[index]->getHandle(), startedSound3ds[index]->getHeader(), sizeof(WAVEHDR));

						if(writeResult != MMSYSERR_NOERROR)
						{
							if(writeResult == MMSYSERR_NODRIVER)
							{
								_terminateSound3ds();

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

			startedSound3ds[index]->setVolume(volume);
			startedSound3ds[index]->setLeftIntensity(leftIntensity);
			startedSound3ds[index]->setRightIntensity(rightIntensity);
		}
	}

	for(auto & [sound3dId, indices] : sound3dsToStop)
	{
		sort(indices.begin(), indices.end());

		int totalTerminations = 0;

		for(auto & index : indices)
		{
			index -= totalTerminations;

			const auto unprepareResult = waveOutUnprepareHeader(_startedSound3ds.at(sound3dId)[index]->getHandle(), _startedSound3ds.at(sound3dId)[index]->getHeader(), sizeof(WAVEHDR));

			if(unprepareResult != MMSYSERR_NOERROR)
			{
				if(unprepareResult == MMSYSERR_NODRIVER)
				{
					_terminateSound3ds();

					return;
				}
				else
				{
					Logger::throwDebug(unprepareResult);

					abort();
				}
			}

			const auto closeResult = waveOutClose(_startedSound3ds.at(sound3dId)[index]->getHandle());

			if(closeResult != MMSYSERR_NOERROR)
			{
				if(closeResult == MMSYSERR_NODRIVER)
				{
					_terminateSound3ds();

					return;
				}
				else
				{
					Logger::throwDebug(closeResult);

					abort();
				}
			}

			_terminateSound3d(sound3dId, index);

			totalTerminations++;
		}
	}

	for(const auto & [sound3dId, playCount] : sound3dsToStart)
	{
		startSound3d(sound3dId, playCount, 0.0f);
	}

	if(_volumeThreadQueue.empty())
	{
		for(auto & [sound3dId, startedSound3ds] : _startedSound3ds)
		{
			for(int index = 0; index < static_cast<int>(startedSound3ds.size()); index++)
			{
				_volumeThreadQueue.push_back({sound3dId, index});
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
		const auto sound3dId = _volumeThreadQueue.front().first;
		const auto index = _volumeThreadQueue.front().second;

		if(!_sound3dManager->isSound3dExisting(sound3dId))
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());

			continue;
		}

		if(_startedSound3ds.find(sound3dId) == _startedSound3ds.end())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());

			continue;
		}

		if(index >= _startedSound3ds.at(sound3dId).size())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());

			continue;
		}

		const auto originalSound3d = _sound3dManager->getSound3d(sound3dId);
		const auto startedSound3d = _startedSound3ds.at(sound3dId)[index];
		const auto originalSampleCount = static_cast<int>(originalSound3d->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample (left OR right) = 2 bytes
		const auto startedSampleCount = static_cast<int>(startedSound3d->getHeader()->dwBufferLength / 2); // 1 sample (left OR right) = 2 bytes
		const auto originalSamples = reinterpret_cast<short *>(originalSound3d->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
		const auto startedSamples = reinterpret_cast<short *>(startedSound3d->getHeader()->lpData); // short = 2 bytes
		const auto volume = startedSound3d->getVolume();
		const auto leftIntensity = startedSound3d->getLeftIntensity();
		const auto rightIntensity = startedSound3d->getRightIntensity();

		_volumeThread = async(launch::async, &Sound3dPlayer::_updateSamplesVolume, this, originalSampleCount, startedSampleCount, originalSamples, startedSamples, volume, leftIntensity, rightIntensity);
	}
}
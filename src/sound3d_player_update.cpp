#include "sound3d_player.hpp"
#include "logger.hpp"

using std::launch;
using std::future_status;
using std::chrono::seconds;
using std::clamp;

void Sound3dPlayer::update()
{
	vector<pair<string, int>> sound3dsToStop;

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

		for(int instanceIndex = 0; instanceIndex < static_cast<int>(startedSound3ds.size()); instanceIndex++)
		{
			if((startedSound3ds[instanceIndex]->getHeader()->dwFlags & WHDR_DONE) == WHDR_DONE)
			{
				if(startedSound3ds[instanceIndex]->getPlayCount() != -1)
				{
					startedSound3ds[instanceIndex]->setPlayCount(startedSound3ds[instanceIndex]->getPlayCount() - 1);
				}

				if(startedSound3ds[instanceIndex]->getPlayCount() == 0)
				{
					sound3dsToStop.push_back({sound3dId, instanceIndex});
				}
				else
				{
					startedSound3ds[instanceIndex]->getHeader()->dwFlags = WHDR_PREPARED;

					const auto writeResult = waveOutWrite(startedSound3ds[instanceIndex]->getHandle(), startedSound3ds[instanceIndex]->getHeader(), sizeof(WAVEHDR));
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

			startedSound3ds[instanceIndex]->setVolume(volume);
			startedSound3ds[instanceIndex]->setLeftIntensity(leftIntensity);
			startedSound3ds[instanceIndex]->setRightIntensity(rightIntensity);
		}
	}

	for(const auto & [sound3dId, index] : sound3dsToStop)
	{
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
	}

	if(_volumeThreadQueue.empty())
	{
		for(auto & [sound3dId, startedSound3ds] : _startedSound3ds)
		{
			for(int instanceIndex = 0; instanceIndex < static_cast<int>(startedSound3ds.size()); instanceIndex++)
			{
				_volumeThreadQueue.push_back({sound3dId, instanceIndex});
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
		const auto instanceIndex = _volumeThreadQueue.front().second;

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
		if(instanceIndex >= _startedSound3ds.at(sound3dId).size())
		{
			_volumeThreadQueue.erase(_volumeThreadQueue.begin());
			continue;
		}

		const auto startedSound3d = _startedSound3ds.at(sound3dId)[instanceIndex];
		const auto originalSound3d = _sound3dManager->getSound3d(sound3dId);

		const auto sampleCount = (originalSound3d->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample = 2 bytes
		const auto originalSamples = reinterpret_cast<short *>(originalSound3d->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
		const auto startedSamples = reinterpret_cast<short *>(startedSound3d->getHeader()->lpData); // short = 2 bytes

		const auto volume = startedSound3d->getVolume();
		const auto leftIntensity = startedSound3d->getLeftIntensity();
		const auto rightIntensity = startedSound3d->getRightIntensity();

		_volumeThread = async(launch::async, &Sound3dPlayer::_updateSamplesVolume, this, sampleCount, originalSamples, startedSamples, volume, leftIntensity, rightIntensity);
	}
}
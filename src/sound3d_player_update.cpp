#include "sound3d_player.hpp"
#include "logger.hpp"

using std::launch;
using std::future_status;
using std::chrono::seconds;
using std::clamp;

void Sound3dPlayer::update()
{
	vector<pair<string, int>> sound3dsToStop;

	for(auto & [sound3dId, instances] : _startedSound3ds)
	{
		const auto sound3d = _sound3dManager->getSound3d(sound3dId);
		const auto cameraPosition = _camera->getPosition();
		const auto distance = Mathematics::calculateDistance(cameraPosition, sound3d->getPosition());
		const auto volume = (clamp((1.0f - (distance / sound3d->getMaxDistance())), 0.0f, 1.0f) * sound3d->getMaxVolume());
		const auto cameraDirection = _camera->getFront();
		const auto soundDirection = (cameraPosition - sound3d->getPosition());
		const auto rotationMatrix = Mathematics::createRotationMatrixY(Mathematics::convertToRadians(90.0f));
		const auto rotatedSoundDirection = (rotationMatrix * fvec4(soundDirection.x, soundDirection.y, soundDirection.z, 1.0f));
		const auto normalizedSoundDirection = Mathematics::normalize(fvec3(rotatedSoundDirection.x, rotatedSoundDirection.y, rotatedSoundDirection.z));
		const auto dotProduct = Mathematics::calculateDotProduct(normalizedSoundDirection, cameraDirection);
		const auto leftIntensity = ((dotProduct * 0.5f) + 0.5f);
		const auto rightIntensity = (1.0f - leftIntensity);

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
					sound3dsToStop.push_back({sound3dId, instanceIndex});
				}
				else
				{
					instances[instanceIndex]->getHeader()->dwFlags = WHDR_PREPARED;

					const auto writeResult = waveOutWrite(instances[instanceIndex]->getHandle(), instances[instanceIndex]->getHeader(), sizeof(WAVEHDR));
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

			instances[instanceIndex]->setVolume(volume);
			instances[instanceIndex]->setLeftIntensity(leftIntensity);
			instances[instanceIndex]->setRightIntensity(rightIntensity);
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
		for(auto & [sound3dId, instances] : _startedSound3ds)
		{
			for(int instanceIndex = 0; instanceIndex < static_cast<int>(instances.size()); instanceIndex++)
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

		const auto startedSound = _startedSound3ds.at(sound3dId)[instanceIndex];
		const auto originalSound = _sound3dManager->getSound3d(sound3dId);

		const auto sampleCount = (originalSound->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample = 2 bytes
		const auto originalSamples = reinterpret_cast<short *>(originalSound->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
		const auto startedSamples = reinterpret_cast<short *>(startedSound->getHeader()->lpData); // short = 2 bytes

		const auto volume = startedSound->getVolume();
		const auto leftIntensity = startedSound->getLeftIntensity();
		const auto rightIntensity = startedSound->getRightIntensity();

		_volumeThread = async(launch::async, &Sound3dPlayer::_updateSamplesVolume, this, sampleCount, originalSamples, startedSamples, volume, leftIntensity, rightIntensity);
	}
}
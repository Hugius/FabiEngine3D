#include "sound3d_player.hpp"
#include "logger.hpp"

#include <thread>

using std::thread;
using std::pair;
using std::clamp;

void Sound3dPlayer::update()
{
	vector<pair<string, unsigned int>> soundsToStop;

	for(auto& [soundId, instances] : _startedSounds)
	{
		const auto sound = _sound3dManager->getSound(soundId);
		const auto cameraPosition = _camera->getPosition();
		const auto distance = Math::calculateDistance(cameraPosition, sound->getPosition());
		const auto volume = (clamp((1.0f - (distance / sound->getMaxDistance())), 0.0f, 1.0f) * sound->getMaxVolume());
		const auto cameraDirection = _camera->getFront();
		const auto soundDirection = (cameraPosition - sound->getPosition());
		const auto rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(90.0f));
		const auto rotatedSoundDirection = (rotationMatrix * fvec4(soundDirection.x, soundDirection.y, soundDirection.z, 1.0f));
		const auto normalizedSoundDirection = Math::normalize(fvec3(rotatedSoundDirection.x, rotatedSoundDirection.y, rotatedSoundDirection.z));
		const auto dotProduct = Math::calculateDotProduct(normalizedSoundDirection, cameraDirection);
		const auto leftIntensity = ((dotProduct * 0.5f) + 0.5f);
		const auto rightIntensity = (1.0f - leftIntensity);

		for(unsigned int instanceIndex = 0; instanceIndex < instances.size(); instanceIndex++)
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

			auto currentSoundTime = new MMTIME();
			currentSoundTime->wType = TIME_SAMPLES;
			waveOutGetPosition(instances[instanceIndex]->getHandle(), currentSoundTime, sizeof(MMTIME));

			const auto sampleCount = (sound->getWaveBuffer()->getHeader()->dwBufferLength / 2); // 1 sample = 2 bytes
			const auto currentSampleIndex = ((currentSoundTime->u.sample * 2) % sampleCount); // Looped audio stacks position
			const auto nextSampleIndex = min((currentSampleIndex + 10000), (sampleCount - 1)); // Cannot go out of range
			const auto originalSamples = reinterpret_cast<short*>(sound->getWaveBuffer()->getHeader()->lpData); // short = 2 bytes
			const auto currentSamples = reinterpret_cast<short*>(instances[instanceIndex]->getHeader()->lpData); // short = 2 bytes

			for(unsigned int sampleIndex = currentSampleIndex; sampleIndex < nextSampleIndex; sampleIndex++)
			{
				// Stereo: LRLRLR...
				if(((sampleIndex + 1) % 2) == 0)
				{
					currentSamples[sampleIndex] = static_cast<short>(static_cast<float>(originalSamples[sampleIndex]) * volume * rightIntensity);
				}
				else
				{
					currentSamples[sampleIndex] = static_cast<short>(static_cast<float>(originalSamples[sampleIndex]) * volume * leftIntensity);
				}
			}

			instances[instanceIndex]->setVolume(volume);
			instances[instanceIndex]->setLeftIntensity(leftIntensity);
			instances[instanceIndex]->setRightIntensity(rightIntensity);
		}
	}

	for(const auto& [id, index] : soundsToStop)
	{
		const auto unprepareResult = waveOutUnprepareHeader(_startedSounds.at(id)[index]->getHandle(), _startedSounds.at(id)[index]->getHeader(), sizeof(WAVEHDR));
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

		const auto closeResult = waveOutClose(_startedSounds.at(id)[index]->getHandle());
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

		_terminateSound(id, index);
	}
}
#include "sound3d_player.hpp"
#include "logger.hpp"

using std::clamp;

void Sound3dPlayer::update()
{
	vector<string> soundsToStop;

	for(auto& [key, startedSounds] : _startedSounds)
	{
		const auto sound = _sound3dManager->getSound(key);
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

		for(unsigned int index = 0; index < startedSounds.size(); index++)
		{
			startedSounds[index]->setVolume(volume);
			startedSounds[index]->setLeftIntensity(leftIntensity);
			startedSounds[index]->setRightIntensity(rightIntensity);

			const auto waveBuffer = _sound3dManager->getSound(key)->getWaveBuffer();

			auto originalSamples = reinterpret_cast<short*>(waveBuffer->getHeader()->lpData);
			auto currentSamples = reinterpret_cast<short*>(startedSounds[index]->getHeader()->lpData);
			auto sampleCount = (startedSounds[index]->getHeader()->dwBufferLength / 2);

			for(unsigned int i = 0; i < sampleCount; i++)
			{
				if(((i + 1) % 2) == 0)
				{
					currentSamples[i] = static_cast<short>(static_cast<float>(originalSamples[i]) * volume * rightIntensity);
				}
				else
				{
					currentSamples[i] = static_cast<short>(static_cast<float>(originalSamples[i]) * volume * leftIntensity);
				}
			}
		}
	}

	for(auto& [key, startedSounds] : _startedSounds)
	{
		for(unsigned int index = 0; index < startedSounds.size(); index++)
		{
			if(startedSounds[index]->getHeader()->dwFlags &= WHDR_DONE)
			{
				if(startedSounds[index]->getPlayCount() != -1)
				{
					startedSounds[index]->setPlayCount(startedSounds[index]->getPlayCount() - 1);
				}

				if(startedSounds[index]->getPlayCount() == 0)
				{
					startedSounds.erase(startedSounds.begin() + index);

					if(startedSounds.empty())
					{
						soundsToStop.push_back(key);
					}

					index--;
				}
				else
				{
					if(waveOutGetNumDevs() > 0)
					{
						startedSounds[index]->getHeader()->dwFlags = WHDR_PREPARED;

						const auto writeResult = waveOutWrite(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(WAVEHDR));

						if(writeResult != MMSYSERR_NOERROR)
						{
							Logger::throwDebug(writeResult);
							abort();
						}
					}
				}
			}
		}
	}

	for(const auto& key : soundsToStop)
	{
		_startedSounds.erase(key);
	}

	if(waveOutGetNumDevs() == 0)
	{
		for(const auto& [key, startedSounds] : _startedSounds)
		{
			for(unsigned int index = 0; index < startedSounds.size(); index++)
			{
				delete _startedSounds.at(key)[index]->getHeader();
			}
		}

		_startedSounds.clear();

		_channelCounter = 0;
	}
}
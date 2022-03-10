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
					const auto unprepareResult = waveOutUnprepareHeader(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(WAVEHDR));
					if((unprepareResult != MMSYSERR_NOERROR) && (unprepareResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(unprepareResult);
						abort();
					}

					const auto prepareResult = waveOutPrepareHeader(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(WAVEHDR));
					if((prepareResult != MMSYSERR_NOERROR) && (prepareResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(prepareResult);
						abort();
					}

					const auto writeResult = waveOutWrite(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(WAVEHDR));
					if((writeResult != MMSYSERR_NOERROR) && (writeResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(writeResult);
						abort();
					}
				}
			}
			else
			{
				if(startedSounds[index]->isPaused())
				{
					const auto pauseResult = waveOutPause(startedSounds[index]->getHandle());

					if((pauseResult != MMSYSERR_NOERROR) && (pauseResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(pauseResult);
						abort();
					}
				}
				else
				{
					const auto restartResult = waveOutRestart(startedSounds[index]->getHandle());

					if((restartResult != MMSYSERR_NOERROR) && (restartResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(restartResult);
						abort();
					}
				}

				const auto leftVolumeIntegral = static_cast<unsigned short>(startedSounds[index]->getVolume() * startedSounds[index]->getLeftIntensity() * static_cast<float>(USHRT_MAX));
				const auto rightVolumeIntegral = static_cast<unsigned short>(startedSounds[index]->getVolume() * startedSounds[index]->getRightIntensity() * static_cast<float>(USHRT_MAX));
				const auto volumeResult = waveOutSetVolume(startedSounds[index]->getHandle(), MAKELONG(leftVolumeIntegral, rightVolumeIntegral));
				if((volumeResult != MMSYSERR_NOERROR) && (volumeResult != MMSYSERR_NODRIVER) && (volumeResult != MMSYSERR_NOTSUPPORTED))
				{
					Logger::throwDebug(volumeResult);
					abort();
				}

				const auto speedIntegral = static_cast<unsigned short>(startedSounds[index]->getSpeed());
				const auto speedFraction = static_cast<unsigned short>(fmodf(startedSounds[index]->getSpeed(), 1.0f) * static_cast<float>(USHRT_MAX));
				const auto speedResult = waveOutSetPlaybackRate(startedSounds[index]->getHandle(), MAKELONG(speedFraction, speedIntegral));
				if((speedResult != MMSYSERR_NOERROR) && (speedResult != MMSYSERR_NODRIVER) && (speedResult != MMSYSERR_NOTSUPPORTED))
				{
					Logger::throwDebug(speedResult);
					abort();
				}

				const auto pitchIntegral = static_cast<unsigned short>(startedSounds[index]->getPitch());
				const auto pitchFraction = static_cast<unsigned short>(fmodf(startedSounds[index]->getPitch(), 1.0f) * static_cast<float>(USHRT_MAX));
				const auto pitchResult = waveOutSetPitch(startedSounds[index]->getHandle(), MAKELONG(pitchFraction, pitchIntegral));
				if((pitchResult != MMSYSERR_NOERROR) && (pitchResult != MMSYSERR_NODRIVER) && (pitchResult != MMSYSERR_NOTSUPPORTED))
				{
					Logger::throwDebug(pitchResult);
					abort();
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
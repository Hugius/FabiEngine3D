#include "sound3d_player.hpp"
#include "logger.hpp"

#include <thread>

using std::thread;
using std::pair;
using std::clamp;

void Sound3dPlayer::update()
{
	vector<pair<string, unsigned int>> soundsToStop;

	for(auto& [id, startedSounds] : _startedSounds)
	{
		const auto sound = _sound3dManager->getSound(id);
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

			const auto sampleCount = (_startedSounds.at(id)[index]->getHeader()->dwBufferLength / 2);
			const auto originalSamples = reinterpret_cast<short*>(_sound3dManager->getSound(id)->getWaveBuffer()->getHeader()->lpData);
			const auto currentSamples = reinterpret_cast<short*>(_startedSounds.at(id)[index]->getHeader()->lpData);

			thread(&Sound3dPlayer::_processVolumeChange, this, sampleCount, originalSamples, currentSamples, volume, leftIntensity, rightIntensity).detach();

			if((startedSounds[index]->getHeader()->dwFlags & WHDR_DONE) == WHDR_DONE)
			{
				if(startedSounds[index]->getPlayCount() != -1)
				{
					startedSounds[index]->setPlayCount(startedSounds[index]->getPlayCount() - 1);
				}

				if(startedSounds[index]->getPlayCount() == 0)
				{
					soundsToStop.push_back({id, index});
				}
				else
				{
					startedSounds[index]->getHeader()->dwFlags = WHDR_PREPARED;

					const auto writeResult = waveOutWrite(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(WAVEHDR));

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
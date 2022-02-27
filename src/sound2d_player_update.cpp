#include "sound2d_player.hpp"
#include "logger.hpp"

void Sound2dPlayer::update()
{
	vector<string> soundsToStop;

	for(auto& [key, startedSounds] : _startedSounds)
	{
		for(unsigned int i = 0; i < startedSounds.size(); i++)
		{
			if(startedSounds[i]->getHeader()->dwFlags &= WHDR_DONE)
			{
				if(startedSounds[i]->getPlayCount() != -1)
				{
					startedSounds[i]->setPlayCount(startedSounds[i]->getPlayCount() - 1);
				}

				if(startedSounds[i]->getPlayCount() == 0)
				{
					startedSounds.erase(startedSounds.begin() + i);

					if(startedSounds.empty())
					{
						soundsToStop.push_back(key);
					}

					i--;
				}
				else
				{
					const auto writeResult = waveOutWrite(startedSounds[i]->getHandle(), startedSounds[i]->getHeader(), sizeof(*startedSounds[i]->getHeader()));

					if((writeResult != MMSYSERR_NOERROR) && (writeResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(writeResult);
						abort();
					}
				}
			}
			else
			{
				if(startedSounds[i]->isPaused())
				{
					const auto pauseResult = waveOutPause(startedSounds[i]->getHandle());

					if((pauseResult != MMSYSERR_NOERROR) && (pauseResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(pauseResult);
						abort();
					}
				}
				else
				{
					const auto restartResult = waveOutRestart(startedSounds[i]->getHandle());

					if((restartResult != MMSYSERR_NOERROR) && (restartResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(restartResult);
						abort();
					}
				}

				const auto volumeIntegral = static_cast<unsigned short>(startedSounds[i]->getVolume() * static_cast<float>(USHRT_MAX));
				const auto volumeResult = waveOutSetVolume(startedSounds[i]->getHandle(), MAKELONG(volumeIntegral, volumeIntegral));
				if((volumeResult != MMSYSERR_NOERROR) && (volumeResult != MMSYSERR_NODRIVER) && (volumeResult != MMSYSERR_NOTSUPPORTED))
				{
					Logger::throwDebug(volumeResult);
					abort();
				}

				const auto speedIntegral = static_cast<unsigned short>(startedSounds[i]->getSpeed());
				const auto speedFraction = static_cast<unsigned short>(fmodf(startedSounds[i]->getSpeed(), 1.0f) * static_cast<float>(USHRT_MAX));
				const auto speedResult = waveOutSetPlaybackRate(startedSounds[i]->getHandle(), MAKELONG(speedFraction, speedIntegral));
				if((speedResult != MMSYSERR_NOERROR) && (speedResult != MMSYSERR_NODRIVER) && (speedResult != MMSYSERR_NOTSUPPORTED))
				{
					Logger::throwDebug(speedResult);
					abort();
				}

				const auto pitchIntegral = static_cast<unsigned short>(startedSounds[i]->getPitch());
				const auto pitchFraction = static_cast<unsigned short>(fmodf(startedSounds[i]->getPitch(), 1.0f) * static_cast<float>(USHRT_MAX));
				const auto pitchResult = waveOutSetPitch(startedSounds[i]->getHandle(), MAKELONG(pitchFraction, pitchIntegral));
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
			for(unsigned int i = 0; i < startedSounds.size(); i++)
			{
				stopSound(key, i);
			}
		}
	}
}
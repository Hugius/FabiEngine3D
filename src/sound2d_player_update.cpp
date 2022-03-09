#include "sound2d_player.hpp"
#include "logger.hpp"

void Sound2dPlayer::update()
{
	vector<string> soundsToStop;

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
					const auto unprepareResult = waveOutUnprepareHeader(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(*startedSounds[index]->getHeader()));
					if((unprepareResult != MMSYSERR_NOERROR) && (unprepareResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(unprepareResult);
						abort();
					}

					const auto prepareResult = waveOutPrepareHeader(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(*startedSounds[index]->getHeader()));
					if((prepareResult != MMSYSERR_NOERROR) && (prepareResult != MMSYSERR_NODRIVER))
					{
						Logger::throwDebug(prepareResult);
						abort();
					}

					const auto writeResult = waveOutWrite(startedSounds[index]->getHandle(), startedSounds[index]->getHeader(), sizeof(*startedSounds[index]->getHeader()));
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

				const auto volumeIntegral = static_cast<unsigned short>(startedSounds[index]->getVolume() * static_cast<float>(USHRT_MAX));
				const auto volumeResult = waveOutSetVolume(startedSounds[index]->getHandle(), MAKELONG(volumeIntegral, volumeIntegral));
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
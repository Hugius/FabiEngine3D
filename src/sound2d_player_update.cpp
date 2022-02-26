#include "sound2d_player.hpp"
#include <iostream>
void Sound2dPlayer::update()
{
	vector<string> soundsToStop;

	for(auto& [key, startedSounds] : _startedSounds)
	{
		for(unsigned int i = 0; i < startedSounds.size(); i++)
		{
			if(startedSounds[i]->getHeader()->dwFlags &= WHDR_DONE)
			{
				if(startedSounds[i]->getPlayCount() == -1)
				{
					waveOutWrite(startedSounds[i]->getHandle(), startedSounds[i]->getHeader(), sizeof(*startedSounds[i]->getHeader()));
				}
				else
				{
					startedSounds[i]->setPlayCount(startedSounds[i]->getPlayCount() - 1);

					if(startedSounds[i]->getPlayCount() == 0)
					{
						startedSounds.erase(startedSounds.begin() + i);

						i--;
					}
					else
					{
						waveOutWrite(startedSounds[i]->getHandle(), startedSounds[i]->getHeader(), sizeof(*startedSounds[i]->getHeader()));
					}
				}
			}
			else
			{
				if(startedSounds[i]->isPaused())
				{
					waveOutPause(startedSounds[i]->getHandle());
				}
				else
				{
					waveOutRestart(startedSounds[i]->getHandle());
				}

				const auto volume = static_cast<unsigned short>(startedSounds[i]->getVolume() * static_cast<float>(USHRT_MAX));
				waveOutSetVolume(startedSounds[i]->getHandle(), MAKELONG(volume, volume));

				const auto speedIntegral = static_cast<unsigned short>(startedSounds[i]->getSpeed());
				const auto speedFraction = static_cast<unsigned short>(fmodf(startedSounds[i]->getSpeed(), 1.0f) * static_cast<float>(USHRT_MAX));
				waveOutSetPlaybackRate(startedSounds[i]->getHandle(), MAKELONG(speedFraction, speedIntegral));

				const auto pitchIntegral = static_cast<unsigned short>(startedSounds[i]->getPitch());
				const auto pitchFraction = static_cast<unsigned short>(fmodf(startedSounds[i]->getPitch(), 1.0f) * static_cast<float>(USHRT_MAX));
				waveOutSetPitch(startedSounds[i]->getHandle(), MAKELONG(pitchFraction, pitchIntegral));
			}
		}

		if(startedSounds.empty())
		{
			soundsToStop.push_back(key);
		}
	}

	for(const auto& key : soundsToStop)
	{
		_startedSounds.erase(key);
	}
}
#include "sound2d_player.hpp"

void Sound2dPlayer::update()
{
	vector<string> soundsToStop;

	for(auto& [key, startedSounds] : _startedSounds)
	{
		for(unsigned int i = 0; i < startedSounds.size(); i++)
		{
			if(startedSounds[i]->getHeader()->dwFlags == WHDR_DONE)
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
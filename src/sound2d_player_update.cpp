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
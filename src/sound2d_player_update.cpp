#include "sound2d_player.hpp"
#include "logger.hpp"

using std::pair;

void Sound2dPlayer::update()
{
	vector<pair<string, unsigned int>> soundsToStop;

	for(auto& [id, startedSounds] : _startedSounds)
	{
		for(unsigned int index = 0; index < startedSounds.size(); index++)
		{
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
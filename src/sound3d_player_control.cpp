#include "sound3d_player.hpp"
#include "logger.hpp"

using std::make_shared;

void Sound3dPlayer::startSound(const string & sound3dId, int playCount)
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newSound = make_shared<StartedSound3D>();

	const auto waveBuffer = _sound3dManager->getSound(sound3dId)->getWaveBuffer();

	HWAVEOUT handle = nullptr;

	const auto openResult = waveOutOpen(&handle, WAVE_MAPPER, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);
	if(openResult != MMSYSERR_NOERROR)
	{
		if(openResult == MMSYSERR_BADDEVICEID)
		{
			_terminateSounds();

			return;
		}
		else
		{
			Logger::throwDebug(openResult);

			abort();
		}
	}

	auto header = new WAVEHDR();
	header->dwBufferLength = waveBuffer->getHeader()->dwBufferLength;
	header->lpData = new char[header->dwBufferLength];
	header->dwFlags = 0;

	for(int index = 0; index < static_cast<int>(header->dwBufferLength); index++)
	{
		header->lpData[index] = waveBuffer->getHeader()->lpData[index];
	}

	const auto prepareResult = waveOutPrepareHeader(handle, header, sizeof(WAVEHDR));
	if(prepareResult != MMSYSERR_NOERROR)
	{
		if(prepareResult == MMSYSERR_NODRIVER)
		{
			_terminateSounds();

			return;
		}
		else
		{
			Logger::throwDebug(prepareResult);

			abort();
		}
	}

	const auto writeResult = waveOutWrite(handle, header, sizeof(WAVEHDR));
	if(writeResult != MMSYSERR_NOERROR)
	{
		if(writeResult == MMSYSERR_NODRIVER)
		{
			_terminateSounds();

			return;
		}
		else if(writeResult == MMSYSERR_NOMEM)
		{
			const auto unprepareResult = waveOutUnprepareHeader(handle, header, sizeof(WAVEHDR));
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

			const auto closeResult = waveOutClose(handle);
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

			return;
		}
		else
		{
			Logger::throwDebug(writeResult);

			abort();
		}
	}

	newSound->setHeader(header);
	newSound->setHandle(handle);
	newSound->setPlayCount(playCount);

	if(_startedSounds.find(sound3dId) == _startedSounds.end())
	{
		_startedSounds.insert({sound3dId, {}});
	}

	_startedSounds.at(sound3dId).push_back(newSound);
}

void Sound3dPlayer::pauseSound(const string & sound3dId, int index)
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}
	if(isSoundPaused(sound3dId, index))
	{
		abort();
	}

	_startedSounds.at(sound3dId)[index]->setPaused(true);

	const auto pauseResult = waveOutPause(_startedSounds.at(sound3dId)[index]->getHandle());

	if(pauseResult != MMSYSERR_NOERROR)
	{
		if(pauseResult == MMSYSERR_NODRIVER)
		{
			_terminateSounds();

			return;
		}
		else
		{
			Logger::throwDebug(pauseResult);

			abort();
		}
	}
}

void Sound3dPlayer::resumeSound(const string & sound3dId, int index)
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}
	if(!isSoundPaused(sound3dId, index))
	{
		abort();
	}

	_startedSounds.at(sound3dId)[index]->setPaused(false);

	const auto restartResult = waveOutRestart(_startedSounds.at(sound3dId)[index]->getHandle());

	if(restartResult != MMSYSERR_NOERROR)
	{
		if(restartResult == MMSYSERR_NODRIVER)
		{
			_terminateSounds();

			return;
		}
		else
		{
			Logger::throwDebug(restartResult);

			abort();
		}
	}
}

void Sound3dPlayer::stopSound(const string & sound3dId, int index)
{
	if(!_sound3dManager->isSoundExisting(sound3dId))
	{
		abort();
	}
	if(!isSoundStarted(sound3dId, index))
	{
		abort();
	}

	const auto resetResult = waveOutReset(_startedSounds.at(sound3dId)[index]->getHandle());
	if(resetResult != MMSYSERR_NOERROR)
	{
		if(resetResult == MMSYSERR_NODRIVER)
		{
			_terminateSounds();

			return;
		}
		else
		{
			Logger::throwDebug(resetResult);

			abort();
		}
	}

	const auto unprepareResult = waveOutUnprepareHeader(_startedSounds.at(sound3dId)[index]->getHandle(), _startedSounds.at(sound3dId)[index]->getHeader(), sizeof(WAVEHDR));
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

	const auto closeResult = waveOutClose(_startedSounds.at(sound3dId)[index]->getHandle());
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

	_terminateSound(sound3dId, index);
}
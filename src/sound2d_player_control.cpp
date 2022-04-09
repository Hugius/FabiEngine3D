#include "sound2d_player.hpp"
#include "logger.hpp"

using std::make_shared;

void Sound2dPlayer::startSound(const string & id, int playCount)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	const auto newSound = make_shared<StartedSound2D>();

	const auto waveBuffer = _sound2dManager->getSound(id)->getWaveBuffer();

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

	for(unsigned int index = 0; index < header->dwBufferLength; index++)
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

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		_startedSounds.insert({id, {}});
	}

	_startedSounds.at(id).push_back(newSound);
}

void Sound2dPlayer::pauseSound(const string & id, unsigned int index)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}
	if(isSoundPaused(id, index))
	{
		abort();
	}

	_startedSounds.at(id)[index]->setPaused(true);

	const auto pauseResult = waveOutPause(_startedSounds.at(id)[index]->getHandle());

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

void Sound2dPlayer::resumeSound(const string & id, unsigned int index)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}
	if(!isSoundPaused(id, index))
	{
		abort();
	}

	_startedSounds.at(id)[index]->setPaused(false);

	const auto restartResult = waveOutRestart(_startedSounds.at(id)[index]->getHandle());

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

void Sound2dPlayer::stopSound(const string & id, unsigned int index)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	const auto resetResult = waveOutReset(_startedSounds.at(id)[index]->getHandle());
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

void Sound2dPlayer::setSoundVolume(const string & id, unsigned int index, float value)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	_startedSounds.at(id)[index]->setVolume(value);
}

void Sound2dPlayer::setSoundLeftIntensity(const string & id, unsigned int index, float value)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	_startedSounds.at(id)[index]->setLeftIntensity(value);
}

void Sound2dPlayer::setSoundRightIntensity(const string & id, unsigned int index, float value)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}

	_startedSounds.at(id)[index]->setRightIntensity(value);
}
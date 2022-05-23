#include "sound2d_player.hpp"
#include "logger.hpp"

using std::make_shared;

void Sound2dPlayer::startSound2d(const string & sound2dId, int playCount, float startTime)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	if((startTime < 0.0f) || (startTime >= 1.0f))
	{
		abort();
	}

	const auto newSound2d = make_shared<StartedSound2D>();
	const auto waveBuffer = _sound2dManager->getSound2d(sound2dId)->getWaveBuffer();
	const auto originalByteCount = static_cast<int>(waveBuffer->getHeader()->dwBufferLength);
	const auto startIndex = static_cast<int>(static_cast<float>(originalByteCount) * startTime);

	HWAVEOUT handle = nullptr;

	const auto openResult = waveOutOpen(&handle, WAVE_MAPPER, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);

	if(openResult != MMSYSERR_NOERROR)
	{
		if(openResult == MMSYSERR_BADDEVICEID)
		{
			_terminateSound2ds();

			return;
		}
		else
		{
			Logger::throwDebug(openResult);

			abort();
		}
	}

	const auto header = new WAVEHDR();

	header->dwBufferLength = (originalByteCount - startIndex);
	header->lpData = new char[header->dwBufferLength];
	header->dwFlags = 0;

	for(int index = startIndex; index < originalByteCount; index++)
	{
		header->lpData[index - startIndex] = waveBuffer->getHeader()->lpData[index];
	}

	const auto prepareResult = waveOutPrepareHeader(handle, header, sizeof(WAVEHDR));

	if(prepareResult != MMSYSERR_NOERROR)
	{
		if(prepareResult == MMSYSERR_NODRIVER)
		{
			_terminateSound2ds();

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
			_terminateSound2ds();

			return;
		}
		else if(writeResult == MMSYSERR_NOMEM)
		{
			const auto unprepareResult = waveOutUnprepareHeader(handle, header, sizeof(WAVEHDR));

			if(unprepareResult != MMSYSERR_NOERROR)
			{
				if(unprepareResult == MMSYSERR_NODRIVER)
				{
					_terminateSound2ds();

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
					_terminateSound2ds();

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

	newSound2d->setHeader(header);
	newSound2d->setHandle(handle);
	newSound2d->setPlayCount(playCount);

	if(_startedSound2ds.find(sound2dId) == _startedSound2ds.end())
	{
		_startedSound2ds.insert({sound2dId, {}});
	}

	_startedSound2ds.at(sound2dId).push_back(newSound2d);
}

void Sound2dPlayer::pauseSound2d(const string & sound2dId, int index)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	if(isSound2dPaused(sound2dId, index))
	{
		abort();
	}

	_startedSound2ds.at(sound2dId)[index]->setPaused(true);

	const auto pauseResult = waveOutPause(_startedSound2ds.at(sound2dId)[index]->getHandle());

	if(pauseResult != MMSYSERR_NOERROR)
	{
		if(pauseResult == MMSYSERR_NODRIVER)
		{
			_terminateSound2ds();

			return;
		}
		else
		{
			Logger::throwDebug(pauseResult);

			abort();
		}
	}
}

void Sound2dPlayer::resumeSound2d(const string & sound2dId, int index)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	if(!isSound2dPaused(sound2dId, index))
	{
		abort();
	}

	_startedSound2ds.at(sound2dId)[index]->setPaused(false);

	const auto restartResult = waveOutRestart(_startedSound2ds.at(sound2dId)[index]->getHandle());

	if(restartResult != MMSYSERR_NOERROR)
	{
		if(restartResult == MMSYSERR_NODRIVER)
		{
			_terminateSound2ds();

			return;
		}
		else
		{
			Logger::throwDebug(restartResult);

			abort();
		}
	}
}

void Sound2dPlayer::stopSound2d(const string & sound2dId, int index)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	const auto resetResult = waveOutReset(_startedSound2ds.at(sound2dId)[index]->getHandle());

	if(resetResult != MMSYSERR_NOERROR)
	{
		if(resetResult == MMSYSERR_NODRIVER)
		{
			_terminateSound2ds();

			return;
		}
		else
		{
			Logger::throwDebug(resetResult);

			abort();
		}
	}

	const auto unprepareResult = waveOutUnprepareHeader(_startedSound2ds.at(sound2dId)[index]->getHandle(), _startedSound2ds.at(sound2dId)[index]->getHeader(), sizeof(WAVEHDR));

	if(unprepareResult != MMSYSERR_NOERROR)
	{
		if(unprepareResult == MMSYSERR_NODRIVER)
		{
			_terminateSound2ds();

			return;
		}
		else
		{
			Logger::throwDebug(unprepareResult);

			abort();
		}
	}

	const auto closeResult = waveOutClose(_startedSound2ds.at(sound2dId)[index]->getHandle());

	if(closeResult != MMSYSERR_NOERROR)
	{
		if(closeResult == MMSYSERR_NODRIVER)
		{
			_terminateSound2ds();

			return;
		}
		else
		{
			Logger::throwDebug(closeResult);

			abort();
		}
	}

	_terminateSound2d(sound2dId, index);
}

void Sound2dPlayer::setSound2dVolume(const string & sound2dId, int index, float value)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	_startedSound2ds.at(sound2dId)[index]->setVolume(value);
}

void Sound2dPlayer::setSound2dLeftIntensity(const string & sound2dId, int index, float value)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	_startedSound2ds.at(sound2dId)[index]->setLeftIntensity(value);
}

void Sound2dPlayer::setSound2dRightIntensity(const string & sound2dId, int index, float value)
{
	if(!_sound2dManager->isSound2dExisting(sound2dId))
	{
		abort();
	}

	if(!isSound2dStarted(sound2dId, index))
	{
		abort();
	}

	_startedSound2ds.at(sound2dId)[index]->setRightIntensity(value);
}
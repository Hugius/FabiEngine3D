#include "sound3d_player.hpp"
#include "logger.hpp"

using std::make_shared;

void Sound3dPlayer::startSound3d(const string & sound3dId, int playCount, int startMilliseconds)
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}

	if(startMilliseconds < 0)
	{
		abort();
	}

	const auto newSound3d = make_shared<StartedSound3D>();
	const auto waveBuffer = _sound3dManager->getSound3d(sound3dId)->getWaveBuffer();
	const auto originalByteCount = static_cast<int>(waveBuffer->getHeader()->dwBufferLength);
	const auto startIndex = static_cast<int>(((waveBuffer->getFormat()->nSamplesPerSec / 1000) * startMilliseconds) * 2);

	if(startIndex >= originalByteCount)
	{
		abort();
	}

	HWAVEOUT handle = nullptr;

	const auto openResult = waveOutOpen(&handle, WAVE_MAPPER, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);

	if(openResult != MMSYSERR_NOERROR)
	{
		if(openResult == MMSYSERR_BADDEVICEID)
		{
			_terminateSound3ds();

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
			_terminateSound3ds();

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
			_terminateSound3ds();

			return;
		}
		else if(writeResult == MMSYSERR_NOMEM)
		{
			const auto unprepareResult = waveOutUnprepareHeader(handle, header, sizeof(WAVEHDR));

			if(unprepareResult != MMSYSERR_NOERROR)
			{
				if(unprepareResult == MMSYSERR_NODRIVER)
				{
					_terminateSound3ds();

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
					_terminateSound3ds();

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

	newSound3d->setHeader(header);
	newSound3d->setHandle(handle);
	newSound3d->setPlayCount(playCount);

	if(_startedSound3ds.find(sound3dId) == _startedSound3ds.end())
	{
		_startedSound3ds.insert({sound3dId, {}});
	}

	_startedSound3ds.at(sound3dId).push_back(newSound3d);
}

void Sound3dPlayer::pauseSound3d(const string & sound3dId, int index)
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	if(isSound3dPaused(sound3dId, index))
	{
		abort();
	}

	_startedSound3ds.at(sound3dId)[index]->setPaused(true);

	const auto pauseResult = waveOutPause(_startedSound3ds.at(sound3dId)[index]->getHandle());

	if(pauseResult != MMSYSERR_NOERROR)
	{
		if(pauseResult == MMSYSERR_NODRIVER)
		{
			_terminateSound3ds();

			return;
		}
		else
		{
			Logger::throwDebug(pauseResult);

			abort();
		}
	}
}

void Sound3dPlayer::resumeSound3d(const string & sound3dId, int index)
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	if(!isSound3dPaused(sound3dId, index))
	{
		abort();
	}

	_startedSound3ds.at(sound3dId)[index]->setPaused(false);

	const auto restartResult = waveOutRestart(_startedSound3ds.at(sound3dId)[index]->getHandle());

	if(restartResult != MMSYSERR_NOERROR)
	{
		if(restartResult == MMSYSERR_NODRIVER)
		{
			_terminateSound3ds();

			return;
		}
		else
		{
			Logger::throwDebug(restartResult);

			abort();
		}
	}
}

void Sound3dPlayer::stopSound3d(const string & sound3dId, int index)
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	const auto resetResult = waveOutReset(_startedSound3ds.at(sound3dId)[index]->getHandle());

	if(resetResult != MMSYSERR_NOERROR)
	{
		if(resetResult == MMSYSERR_NODRIVER)
		{
			_terminateSound3ds();

			return;
		}
		else
		{
			Logger::throwDebug(resetResult);

			abort();
		}
	}

	const auto unprepareResult = waveOutUnprepareHeader(_startedSound3ds.at(sound3dId)[index]->getHandle(), _startedSound3ds.at(sound3dId)[index]->getHeader(), sizeof(WAVEHDR));

	if(unprepareResult != MMSYSERR_NOERROR)
	{
		if(unprepareResult == MMSYSERR_NODRIVER)
		{
			_terminateSound3ds();

			return;
		}
		else
		{
			Logger::throwDebug(unprepareResult);

			abort();
		}
	}

	const auto closeResult = waveOutClose(_startedSound3ds.at(sound3dId)[index]->getHandle());

	if(closeResult != MMSYSERR_NOERROR)
	{
		if(closeResult == MMSYSERR_NODRIVER)
		{
			_terminateSound3ds();

			return;
		}
		else
		{
			Logger::throwDebug(closeResult);

			abort();
		}
	}

	_terminateSound3d(sound3dId, index);
}
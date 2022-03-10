#include "sound3d_player.hpp"
#include "logger.hpp"

using std::make_shared;

void Sound3dPlayer::startSound(const string& id, int playCount)
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isChannelAvailable())
	{
		abort();
	}
	if((playCount == 0) || (playCount < -1))
	{
		abort();
	}
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	const auto newSound = make_shared<StartedSound3D>();

	const auto waveBuffer = _sound3dManager->getSound(id)->getWaveBuffer();

	HWAVEOUT handle = nullptr;
	PWAVEHDR header = new WAVEHDR(*waveBuffer->getHeader());

	const auto openResult = waveOutOpen(&handle, WAVE_MAPPER, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);
	if(openResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(openResult);
		abort();
	}

	const auto prepareResult = waveOutPrepareHeader(handle, header, sizeof(*header));
	if(prepareResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(prepareResult);
		abort();
	}

	const auto writeResult = waveOutWrite(handle, header, sizeof(*header));
	if(writeResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(writeResult);
		abort();
	}

	newSound->setHandle(handle);
	newSound->setHeader(header);
	newSound->setPlayCount(playCount);

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		_startedSounds.insert({id, {}});
	}

	_startedSounds.at(id).push_back(newSound);

	_channelCounter++;
}

void Sound3dPlayer::pauseSound(const string& id, unsigned int index)
{
	if(!_sound3dManager->isSoundExisting(id))
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
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	_startedSounds.at(id)[index]->setPaused(true);
}

void Sound3dPlayer::resumeSound(const string& id, unsigned int index)
{
	if(!_sound3dManager->isSoundExisting(id))
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
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	_startedSounds.at(id)[index]->setPaused(false);
}

void Sound3dPlayer::stopSound(const string& id, unsigned int index)
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	const auto resetResult = waveOutReset(_startedSounds.at(id)[index]->getHandle());
	if(resetResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(resetResult);
		abort();
	}

	const auto unprepareResult = waveOutUnprepareHeader(_startedSounds.at(id)[index]->getHandle(), _startedSounds.at(id)[index]->getHeader(), sizeof(*_startedSounds.at(id)[index]->getHeader()));
	if(unprepareResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(unprepareResult);
		abort();
	}

	const auto closeResult = waveOutClose(_startedSounds.at(id)[index]->getHandle());
	if(closeResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(closeResult);
		abort();
	}

	delete _startedSounds.at(id)[index]->getHeader();

	_startedSounds.at(id).erase(_startedSounds.at(id).begin() + index);

	if(_startedSounds.at(id).empty())
	{
		_startedSounds.erase(id);
	}

	_channelCounter--;
}

void Sound3dPlayer::setSoundSpeed(const string& id, unsigned int index, float value)
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	_startedSounds.at(id)[index]->setSpeed(value);
}

void Sound3dPlayer::setSoundPitch(const string& id, unsigned int index, float value)
{
	if(!_sound3dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id, index))
	{
		abort();
	}
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	_startedSounds.at(id)[index]->setPitch(value);
}
#include "sound2d_player.hpp"
#include "logger.hpp"

using std::make_shared;

void Sound2dPlayer::startSound(const string& id, int playCount)
{
	if(!_sound2dManager->isSoundExisting(id))
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

	const auto newSound = make_shared<StartedSound2D>();

	const auto waveBuffer = _sound2dManager->getSound(id)->getWaveBuffer();

	HWAVEOUT handle = nullptr;

	const auto openResult = waveOutOpen(&handle, WAVE_MAPPER, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);
	if(openResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(openResult);
		abort();
	}

	auto header = new WAVEHDR();
	header->dwBufferLength = waveBuffer->getHeader()->dwBufferLength;
	header->lpData = new char[header->dwBufferLength];
	for(unsigned int i = 0; i < header->dwBufferLength; i++)
	{
		header->lpData[i] = waveBuffer->getHeader()->lpData[i];
	}

	const auto prepareResult = waveOutPrepareHeader(handle, header, sizeof(WAVEHDR));
	if(prepareResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(prepareResult);
		abort();
	}

	const auto writeResult = waveOutWrite(handle, header, sizeof(WAVEHDR));
	if(writeResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(writeResult);
		abort();
	}

	newSound->setHeader(header);
	newSound->setHandle(handle);
	newSound->setPlayCount(playCount);

	if(_startedSounds.find(id) == _startedSounds.end())
	{
		_startedSounds.insert({id, {}});
	}

	_startedSounds.at(id).push_back(newSound);

	_channelCounter++;
}

void Sound2dPlayer::pauseSound(const string& id, unsigned int index)
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
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	_startedSounds.at(id)[index]->setPaused(true);

	const auto pauseResult = waveOutPause(_startedSounds.at(id)[index]->getHandle());

	if(pauseResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(pauseResult);
		abort();
	}
}

void Sound2dPlayer::resumeSound(const string& id, unsigned int index)
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
	if(waveOutGetNumDevs() == 0)
	{
		return;
	}

	_startedSounds.at(id)[index]->setPaused(false);

	const auto restartResult = waveOutRestart(_startedSounds.at(id)[index]->getHandle());

	if(restartResult != MMSYSERR_NOERROR)
	{
		Logger::throwDebug(restartResult);
		abort();
	}
}

void Sound2dPlayer::stopSound(const string& id, unsigned int index)
{
	if(!_sound2dManager->isSoundExisting(id))
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

	const auto unprepareResult = waveOutUnprepareHeader(_startedSounds.at(id)[index]->getHandle(), _startedSounds.at(id)[index]->getHeader(), sizeof(WAVEHDR));
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

void Sound2dPlayer::setSoundVolume(const string& id, unsigned int index, float value)
{
	if(!_sound2dManager->isSoundExisting(id))
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

	_startedSounds.at(id)[index]->setVolume(value);

	const auto waveBuffer = _sound2dManager->getSound(id)->getWaveBuffer();

	auto originalSamples = reinterpret_cast<short*>(waveBuffer->getHeader()->lpData);
	auto currentSamples = reinterpret_cast<short*>(_startedSounds.at(id)[index]->getHeader()->lpData);
	auto sampleCount = (_startedSounds.at(id)[index]->getHeader()->dwBufferLength / 2);

	for(unsigned int i = 0; i < sampleCount; i++)
	{
		currentSamples[i] = static_cast<short>(static_cast<float>(originalSamples[i]) * _startedSounds.at(id)[index]->getVolume());
	}
}

void Sound2dPlayer::setSoundSpeed(const string& id, unsigned int index, float value)
{
	if(!_sound2dManager->isSoundExisting(id))
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

void Sound2dPlayer::setSoundPitch(const string& id, unsigned int index, float value)
{
	if(!_sound2dManager->isSoundExisting(id))
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
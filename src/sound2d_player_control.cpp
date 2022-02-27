#include "sound2d_player.hpp"

using std::make_shared;

void Sound2dPlayer::startSound(const string& id, int playCount)
{
	if(!isChannelAvailable())
	{
		return;
	}
	if(playCount == 0)
	{
		return;
	}
	if(playCount < -1)
	{
		abort();
	}
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}

	const auto newSound = make_shared<StartedSound2D>();

	const auto waveBuffer = _sound2dManager->getSound(id)->getWaveBuffer();

	HWAVEOUT handle = nullptr;
	PWAVEHDR header = new WAVEHDR(*waveBuffer->getHeader());

	waveOutOpen(&handle, WAVE_MAPPER, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);
	waveOutPrepareHeader(handle, header, sizeof(*header));
	waveOutWrite(handle, header, sizeof(*header));

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

	_startedSounds.at(id)[index]->setPaused(true);
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

	_startedSounds.at(id)[index]->setPaused(false);
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

	const auto startedSound = _startedSounds.at(id)[index];

	waveOutReset(startedSound->getHandle());

	waveOutUnprepareHeader(startedSound->getHandle(), startedSound->getHeader(), sizeof(*startedSound->getHeader()));

	waveOutClose(startedSound->getHandle());

	delete startedSound->getHeader();

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

	_startedSounds.at(id)[index]->setVolume(value);
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

	_startedSounds.at(id)[index]->setPitch(value);
}
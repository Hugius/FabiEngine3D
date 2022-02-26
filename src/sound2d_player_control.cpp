#include "sound2d_player.hpp"

using std::make_shared;

void Sound2dPlayer::startSound(const string& id, int playCount)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(isSoundStarted(id))
	{
		abort();
	}
	if((playCount < -1) || (playCount == 0))
	{
		abort();
	}
	if(!isChannelAvailable())
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

	if(!isSoundStarted(id))
	{
		_startedSounds.insert({id, {}});
	}

	_startedSounds.at(id).push_back(newSound);

	_channelCounter++;
}

void Sound2dPlayer::pauseSound(const string& id)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();
	}
	if(isSoundPaused(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds.at(id))
	{
		startedSound->setPaused(true);
	}
}

void Sound2dPlayer::resumeSound(const string& id)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();

	}
	if(!isSoundPaused(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds.at(id))
	{
		startedSound->setPaused(false);
	}
}

void Sound2dPlayer::stopSound(const string& id)
{
	if(!_sound2dManager->isSoundExisting(id))
	{
		abort();
	}
	if(!isSoundStarted(id))
	{
		abort();
	}

	for(const auto& startedSound : _startedSounds.at(id))
	{
		waveOutReset(startedSound->getHandle());

		waveOutUnprepareHeader(startedSound->getHandle(), startedSound->getHeader(), sizeof(*startedSound->getHeader()));

		waveOutClose(startedSound->getHandle());

		delete startedSound->getHeader();

		_channelCounter--;
	}

	_startedSounds.erase(id);
}
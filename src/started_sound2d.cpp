#include "started_sound2d.hpp"

StartedSound2D::StartedSound2D(const string& soundId, unsigned int channelIndex, shared_ptr<WaveBuffer> waveBuffer)
	:
	_soundId(soundId),
	_channelIndex(channelIndex)
{
	_header = new WAVEHDR(*waveBuffer->getHeader());

	waveOutOpen(&_handle, channelIndex, waveBuffer->getFormat(), 0, 0, CALLBACK_NULL);

	waveOutPrepareHeader(_handle, _header, sizeof(*_header));

	waveOutWrite(_handle, _header, sizeof(*_header));
}

StartedSound2D::~StartedSound2D()
{

	waveOutUnprepareHeader(_handle, _header, sizeof(*_header));

	waveOutClose(_handle);

	delete _header;
}

void StartedSound2D::pause()
{
	if(_isPaused)
	{
		abort();
	}

	waveOutPause(_handle);
}

void StartedSound2D::resume()
{
	if(!_isPaused)
	{
		abort();
	}

	waveOutRestart(_handle);
}

void StartedSound2D::setPlayCount(int value)
{
	_playCount = value;
}

const string& StartedSound2D::getSoundId() const
{
	return _soundId;
}

const int StartedSound2D::getPlayCount() const
{
	return _playCount;
}

const bool StartedSound2D::isPaused() const
{
	return _isPaused;
}

const unsigned int StartedSound2D::getChannelIndex() const
{
	return _channelIndex;
}
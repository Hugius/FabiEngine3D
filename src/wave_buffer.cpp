#include "wave_buffer.hpp"

WaveBuffer::WaveBuffer(shared_ptr<Audio> audio)
{
	_format = new WAVEFORMATEX();
	_format->wFormatTag = WAVE_FORMAT_PCM;
	_format->nChannels = (audio->getChannelFormat() == ChannelFormat::MONO ? 1 : 2);
	_format->wBitsPerSample = audio->getBitsPerSample();
	_format->nSamplesPerSec = audio->getSampleRate();
	_format->nBlockAlign = ((_format->nChannels * _format->wBitsPerSample) / 8);
	_format->nAvgBytesPerSec = (_format->nSamplesPerSec * _format->nBlockAlign);
	_format->cbSize = 0;

	waveOutOpen(&_handle, 0, _format, 0, 0, CALLBACK_NULL);

	_header = new WAVEHDR();
	_header->lpData = const_cast<char*>(reinterpret_cast<const char*>(audio->getSamples()));
	_header->dwBufferLength = audio->getSampleCount();
	_header->dwFlags = 0;
	_header->dwLoops = 0;

	waveOutPrepareHeader(_handle, _header, sizeof(*_header));
}

WaveBuffer::~WaveBuffer()
{
	waveOutUnprepareHeader(_handle, _header, sizeof(*_header));

	delete _header;

	waveOutClose(_handle);

	delete _format;
}

const HWAVEOUT WaveBuffer::getHandle() const
{
	return _handle;
}

const PWAVEHDR WaveBuffer::getHeader() const
{
	return _header;
}

const PWAVEFORMATEX WaveBuffer::getFormat() const
{
	return _format;
}
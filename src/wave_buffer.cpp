#include "wave_buffer.hpp"

WaveBuffer::WaveBuffer(shared_ptr<Audio> audio)
{
	_format = new WAVEFORMATEX();
	_format->wFormatTag = WAVE_FORMAT_PCM;
	_format->nChannels = (audio->getChannelFormat() == ChannelFormat::MONO ? 1 : 2);
	_format->nSamplesPerSec = audio->getSampleRate();
	_format->nAvgBytesPerSec = audio->getByteRate();
	_format->nBlockAlign = audio->getBytesPerBlock();
	_format->wBitsPerSample = audio->getBitsPerSample();

	_header = new WAVEHDR();
	_header->lpData = const_cast<char*>(reinterpret_cast<const char*>(audio->getSamples()));
	_header->dwBufferLength = audio->getSampleCount();
}

WaveBuffer::~WaveBuffer()
{
	delete _format;

	delete _header;
}

const PWAVEFORMATEX WaveBuffer::getFormat() const
{
	return _format;
}

const PWAVEHDR WaveBuffer::getHeader() const
{
	return _header;
}
#include "audio.hpp"

#include <stdlib.h>

Audio::Audio(unsigned char* samples, unsigned int sampleCount, unsigned int sampleRate, unsigned int bitsPerSample, ChannelFormat channelFormat)
	:
	_samples(samples),
	_sampleCount(sampleCount),
	_sampleRate(sampleRate),
	_bitsPerSample(bitsPerSample),
	_channelFormat(channelFormat)
{
	if(_samples == nullptr)
	{
		abort();
	}
}

Audio::~Audio()
{
	delete[] _samples;
}

const unsigned char* Audio::getSamples() const
{
	return _samples;
}

const unsigned int Audio::getBitsPerSample() const
{
	return _bitsPerSample;
}

const unsigned int Audio::getSampleCount() const
{
	return _sampleCount;
}

const unsigned int Audio::getSampleRate() const
{
	return _sampleRate;
}

const ChannelFormat Audio::getChannelFormat() const
{
	return _channelFormat;
}
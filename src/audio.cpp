#include "audio.hpp"

#include <stdlib.h>

Audio::Audio(unsigned char * samples, unsigned int sampleCount, unsigned int channelCount, unsigned int sampleRate, unsigned int byteRate, unsigned int bytesPerBlock, unsigned int bitsPerSample)
	:
	_samples(samples),
	_sampleCount(sampleCount),
	_channelCount(channelCount),
	_sampleRate(sampleRate),
	_byteRate(byteRate),
	_bytesPerBlock(bytesPerBlock),
	_bitsPerSample(bitsPerSample)
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

const unsigned char * Audio::getSamples() const
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

const unsigned int Audio::getByteRate() const
{
	return _byteRate;
}

const unsigned int Audio::getBytesPerBlock() const
{
	return _bytesPerBlock;
}

const unsigned int Audio::getSampleRate() const
{
	return _sampleRate;
}

const unsigned int Audio::getChannelCount() const
{
	return _channelCount;
}
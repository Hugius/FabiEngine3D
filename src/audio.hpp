#pragma once

#include "channel_format.hpp"

class Audio final
{
public:
	Audio(unsigned char* samples, unsigned int sampleCount, ChannelFormat channelFormat, unsigned int sampleRate, unsigned int byteRate, unsigned int bytesPerBlock, unsigned int bitsPerSample);
	~Audio();

	const unsigned char* getSamples() const;

	const unsigned int getSampleCount() const;
	const unsigned int getByteRate() const;
	const unsigned int getBytesPerBlock() const;
	const unsigned int getSampleRate() const;
	const unsigned int getBitsPerSample() const;

	const ChannelFormat getChannelFormat() const;

private:
	const unsigned char* _samples;

	const unsigned int _sampleCount;
	const unsigned int _sampleRate;
	const unsigned int _byteRate;
	const unsigned int _bytesPerBlock;
	const unsigned int _bitsPerSample;

	const ChannelFormat _channelFormat;
};
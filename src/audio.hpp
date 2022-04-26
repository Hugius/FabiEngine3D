#pragma once

class Audio final
{
public:
	Audio(unsigned char * samples, unsigned int sampleCount, unsigned int channelCount, unsigned int sampleRate, unsigned int byteRate, unsigned int bytesPerBlock, unsigned int bitsPerSample);
	~Audio();

	const unsigned char * getSamples() const;

	const int getSampleCount() const;
	const int getByteRate() const;
	const int getBytesPerBlock() const;
	const int getSampleRate() const;
	const int getBitsPerSample() const;
	const int getChannelCount() const;

private:
	const unsigned char * _samples;

	const int _sampleCount;
	const int _sampleRate;
	const int _byteRate;
	const int _bytesPerBlock;
	const int _bitsPerSample;
	const int _channelCount;
};
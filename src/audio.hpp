#pragma once

class Audio final
{
public:
	Audio(unsigned char * samples, int sampleCount, int channelCount, int sampleRate, int byteRate, int bytesPerBlock, int bitsPerSample);
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
#pragma once

#include "wave_buffer.hpp"

#include <windows.h>
#include <string>

using std::string;

class StartedSound2D final
{
public:
	StartedSound2D(const string& soundId, unsigned int channelIndex, shared_ptr<WaveBuffer> waveBuffer);
	~StartedSound2D();

	void pause();
	void resume();
	void setPlayCount(int value);

	const string& getSoundId() const;

	const int getPlayCount() const;

	const unsigned int getChannelIndex() const;

	const bool isPaused() const;

private:
	const string _soundId;
	const unsigned int _channelIndex;

	int _playCount = 0;

	bool _isPaused = false;

	HWAVEOUT _handle = nullptr;

	PWAVEHDR _header = nullptr;
};
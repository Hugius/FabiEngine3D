#pragma once

#include "wave_buffer.hpp"

#include <windows.h>
#include <string>

using std::string;

class StartedSound2D final
{
public:
	void setPaused(bool value);
	void setPlayCount(int value);
	void setVolume(float value);
	void setSpeed(float value);
	void setPitch(float value);
	void setHeader(PWAVEHDR value);
	void setHandle(HWAVEOUT value);

	const PWAVEHDR getHeader() const;
	const HWAVEOUT getHandle() const;

	const float getVolume() const;
	const float getSpeed() const;
	const float getPitch() const;

	const int getPlayCount() const;

	const bool isPaused() const;

private:
	int _playCount = 0;

	float _volume = 1.0f;
	float _speed = 1.0f;
	float _pitch = 1.0f;

	bool _isPaused = false;

	PWAVEHDR _header = nullptr;
	HWAVEOUT _handle = nullptr;
};
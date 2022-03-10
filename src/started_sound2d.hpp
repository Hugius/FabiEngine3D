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
	void setHandle(HWAVEOUT value);
	void setHeader(PWAVEHDR value);

	const HWAVEOUT getHandle() const;
	const PWAVEHDR getHeader() const;

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

	HWAVEOUT _handle = nullptr;

	PWAVEHDR _header = nullptr;
};
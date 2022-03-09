#pragma once

#include "wave_buffer.hpp"

#include <windows.h>
#include <string>

using std::string;

class StartedSound3D final
{
public:
	void setPaused(bool value);
	void setPlayCount(int value);
	void setLeftIntensity(float value);
	void setRightIntensity(float value);
	void setVolume(float value);
	void setSpeed(float value);
	void setHandle(HWAVEOUT value);
	void setHeader(PWAVEHDR value);

	const HWAVEOUT getHandle() const;
	const PWAVEHDR getHeader() const;

	const float getLeftIntensity() const;
	const float getRightIntensity() const;
	const float getVolume() const;
	const float getSpeed() const;

	const int getPlayCount() const;

	const bool isPaused() const;

private:
	int _playCount = 0;

	float _leftIntensity = 0.0f;
	float _rightIntensity = 0.0f;
	float _volume = 1.0f;
	float _speed = 1.0f;

	bool _isPaused = false;

	HWAVEOUT _handle = nullptr;

	PWAVEHDR _header = nullptr;
};
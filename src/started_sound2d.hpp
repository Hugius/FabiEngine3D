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
	void setLeftIntensity(float value);
	void setRightIntensity(float value);
	void setHeader(PWAVEHDR value);
	void setHandle(HWAVEOUT value);

	const PWAVEHDR getHeader() const;
	const HWAVEOUT getHandle() const;

	const float getLeftIntensity() const;
	const float getRightIntensity() const;
	const float getVolume() const;

	const int getPlayCount() const;

	const bool isPaused() const;

private:
	int _playCount = 0;

	float _leftIntensity = 0.0f;
	float _rightIntensity = 0.0f;
	float _volume = 1.0f;

	bool _isPaused = false;

	PWAVEHDR _header = nullptr;
	HWAVEOUT _handle = nullptr;
};
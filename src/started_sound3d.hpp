#pragma once

#include "wave_buffer.hpp"

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
	void setHandle(HWAVEOUT value);
	void setHeader(PWAVEHDR value);

	const float getLeftIntensity() const;
	const float getRightIntensity() const;
	const float getVolume() const;

	const int getPlayCount() const;

	const bool isPaused() const;

	const HWAVEOUT getHandle() const;
	const PWAVEHDR getHeader() const;

private:
	float _leftIntensity = 1.0f;
	float _rightIntensity = 1.0f;
	float _volume = 1.0f;

	int _playCount = 0;

	bool _isPaused = false;

	HWAVEOUT _handle = nullptr;
	PWAVEHDR _header = nullptr;
};
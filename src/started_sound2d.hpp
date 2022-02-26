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
	void setHandle(HWAVEOUT value);
	void setHeader(PWAVEHDR value);

	const int getPlayCount() const;

	const bool isPaused() const;

	const HWAVEOUT getHandle() const;
	const PWAVEHDR getHeader() const;

private:
	int _playCount = 0;

	bool _isPaused = false;

	HWAVEOUT _handle = nullptr;

	PWAVEHDR _header = nullptr;
};
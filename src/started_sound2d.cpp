#include "started_sound2d.hpp"

void StartedSound2D::setPaused(bool value)
{
	waveOutPause(_handle);

	_isPaused = value;
}

void StartedSound2D::setPlayCount(int value)
{
	_playCount = value;
}

void StartedSound2D::setHandle(HWAVEOUT value)
{
	_handle = value;
}

void StartedSound2D::setHeader(PWAVEHDR value)
{
	_header = value;
}

const int StartedSound2D::getPlayCount() const
{
	return _playCount;
}

const bool StartedSound2D::isPaused() const
{
	return _isPaused;
}

const HWAVEOUT StartedSound2D::getHandle() const
{
	return _handle;
}

const PWAVEHDR StartedSound2D::getHeader() const
{
	return _header;
}
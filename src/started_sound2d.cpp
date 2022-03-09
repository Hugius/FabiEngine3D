#include "started_sound2d.hpp"

#include <algorithm>

using std::clamp;

void StartedSound2D::setSampleIndex(unsigned int value)
{
	_sampleIndex = value;
}

void StartedSound2D::setPaused(bool value)
{
	_isPaused = value;
}

void StartedSound2D::setPlayCount(int value)
{
	_playCount = value;
}

void StartedSound2D::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

void StartedSound2D::setSpeed(float value)
{
	_speed = max(0.0f, value);
}

void StartedSound2D::setHandle(HWAVEOUT value)
{
	_handle = value;
}

void StartedSound2D::setHeader(PWAVEHDR value)
{
	_header = value;
}

const float StartedSound2D::getVolume() const
{
	return _volume;
}

const float StartedSound2D::getSpeed() const
{
	return _speed;
}

const unsigned int StartedSound2D::getSampleIndex() const
{
	return _sampleIndex;
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
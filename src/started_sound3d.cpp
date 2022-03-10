#include "started_sound3d.hpp"

#include <algorithm>

using std::clamp;

void StartedSound3D::setPaused(bool value)
{
	_isPaused = value;
}

void StartedSound3D::setPlayCount(int value)
{
	_playCount = value;
}

void StartedSound3D::setLeftIntensity(float value)
{
	_leftIntensity = clamp(value, 0.0f, 1.0f);
}

void StartedSound3D::setRightIntensity(float value)
{
	_rightIntensity = clamp(value, 0.0f, 1.0f);
}

void StartedSound3D::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

void StartedSound3D::setSpeed(float value)
{
	_speed = max(0.0f, value);
}

void StartedSound3D::setPitch(float value)
{
	_pitch = max(0.0f, value);
}

void StartedSound3D::setHandle(HWAVEOUT value)
{
	_handle = value;
}

void StartedSound3D::setHeader(PWAVEHDR value)
{
	_header = value;
}

const float StartedSound3D::getVolume() const
{
	return _volume;
}

const float StartedSound3D::getSpeed() const
{
	return _speed;
}

const float StartedSound3D::getPitch() const
{
	return _pitch;
}

const int StartedSound3D::getPlayCount() const
{
	return _playCount;
}

const bool StartedSound3D::isPaused() const
{
	return _isPaused;
}

const HWAVEOUT StartedSound3D::getHandle() const
{
	return _handle;
}

const PWAVEHDR StartedSound3D::getHeader() const
{
	return _header;
}

const float StartedSound3D::getLeftIntensity() const
{
	return _leftIntensity;
}

const float StartedSound3D::getRightIntensity() const
{
	return _rightIntensity;
}
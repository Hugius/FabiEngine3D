#include "sound_3d.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Sound3D::setPosition(fvec3 value)
{
	_position = value;
}

void Sound3D::move(fvec3 value)
{
	_position += value;
}

void Sound3D::setMaxVolume(float value)
{
	_maxVolume = clamp(value, 0.0f, 1.0f);
}

void Sound3D::setMaxDistance(float value)
{
	_maxDistance = max(0.0f, value);
}

const fvec3 Sound3D::getPosition() const
{
	return _position;
}

const float Sound3D::getMaxDistance() const
{
	return _maxDistance;
}

const float Sound3D::getMaxVolume() const
{
	return _maxVolume;
}
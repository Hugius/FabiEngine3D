#include "sound3d.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Sound3d::updateTransformation()
{
	if (_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		// Correct position
		if (fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if (fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
		if (fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}
}

void Sound3d::setPosition(fvec3 value)
{
	_position = value;
	_positionTarget = value;
}

void Sound3d::move(fvec3 value)
{
	_position += value;
	_positionTarget += value;
}

void Sound3d::moveTo(fvec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Sound3d::setMaxVolume(float value)
{
	_maxVolume = clamp(value, 0.0f, 1.0f);
}

void Sound3d::setMaxDistance(float value)
{
	_maxDistance = max(0.0f, value);
}

const fvec3 Sound3d::getPosition() const
{
	return _position;
}

const float Sound3d::getMaxDistance() const
{
	return _maxDistance;
}

const float Sound3d::getMaxVolume() const
{
	return _maxVolume;
}
#include "spotlight_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void SpotlightEntity::updateTransformation()
{
	if (_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalizeVector(_positionTarget - _position);
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

void SpotlightEntity::setPosition(Vec3 value)
{
	_position = value;
	_positionTarget = value;
}

void SpotlightEntity::move(Vec3 value)
{
	_position += value;
	_positionTarget += value;
}

void SpotlightEntity::moveTo(Vec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void SpotlightEntity::setFront(Vec3 value)
{
	_front = Vec3(clamp(value.x, -1.0f, 1.0f), clamp(value.y, -1.0f, 1.0f), clamp(value.z, -1.0f, 1.0f));;
}

void SpotlightEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void SpotlightEntity::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void SpotlightEntity::setAngle(float value)
{
	_angle = Math::limitAngle(value);
}

void SpotlightEntity::setDistance(float value)
{
	_distance = max(0.0f, value);
}

const Vec3 SpotlightEntity::getPosition()
{
	return _position;
}

const Vec3 SpotlightEntity::getFront()
{
	return _front;
}

const Vec3 SpotlightEntity::getColor()
{
	return _color;
}

const float SpotlightEntity::getIntensity()
{
	return _intensity;
}

const float SpotlightEntity::getAngle()
{
	return _angle;
}

const float SpotlightEntity::getDistance()
{
	return _distance;
}
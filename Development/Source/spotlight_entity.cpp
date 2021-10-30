#include "spotlight_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void SpotlightEntity::updateTransformation()
{
	if(_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		// Correct position
		if(fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if(fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}
}

void SpotlightEntity::updateFrontVector()
{
	_frontVector.x = (cos(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_frontVector.y = sin(Math::convertToRadians(_pitch));
	_frontVector.z = (sin(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_frontVector = Math::normalize(_frontVector);
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

void SpotlightEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void SpotlightEntity::setYaw(float value)
{
	_yaw = Math::limitAngle(value);
}

void SpotlightEntity::setPitch(float value)
{
	_pitch = Math::limitAngle(value);
}

void SpotlightEntity::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void SpotlightEntity::setAngle(float value)
{
	_angle = clamp(value, 0.0f, 45.0f);
}

void SpotlightEntity::setDistance(float value)
{
	_distance = max(0.0f, value);
}

const Vec3 SpotlightEntity::getPosition()
{
	return _position;
}

const Vec3 SpotlightEntity::getFrontVector()
{
	return _frontVector;
}

const Vec3 SpotlightEntity::getColor()
{
	return _color;
}

const float SpotlightEntity::getYaw()
{
	return _yaw;
}

const float SpotlightEntity::getPitch()
{
	return _pitch;
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
#include "spotlight_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void SpotlightEntity::updateTarget()
{
	if(_position != _positionTarget)
	{
		auto speedMultiplier = Mathematics::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

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

void SpotlightEntity::updateFront()
{
	_front.x = (cos(Mathematics::convertToRadians(_yaw)) * cos(Mathematics::convertToRadians(_pitch)));
	_front.y = sin(Mathematics::convertToRadians(_pitch));
	_front.z = (sin(Mathematics::convertToRadians(_yaw)) * cos(Mathematics::convertToRadians(_pitch)));
	_front = Mathematics::normalize(_front);
}

void SpotlightEntity::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void SpotlightEntity::move(const fvec3 & value)
{
	_position += value;
	_positionTarget += value;
}

void SpotlightEntity::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void SpotlightEntity::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void SpotlightEntity::setYaw(float value)
{
	_yaw = Mathematics::limitAngle(value);
}

void SpotlightEntity::setPitch(float value)
{
	_pitch = Mathematics::limitAngle(value);
}

void SpotlightEntity::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void SpotlightEntity::setAngle(float value)
{
	_angle = clamp(value, 0.0f, MAX_ANGLE);
}

void SpotlightEntity::setDistance(float value)
{
	_distance = max(0.0f, value);
}

const fvec3 & SpotlightEntity::getPosition() const
{
	return _position;
}

const fvec3 & SpotlightEntity::getFront() const
{
	return _front;
}

const fvec3 & SpotlightEntity::getColor() const
{
	return _color;
}

const float SpotlightEntity::getYaw() const
{
	return _yaw;
}

const float SpotlightEntity::getPitch() const
{
	return _pitch;
}

const float SpotlightEntity::getIntensity() const
{
	return _intensity;
}

const float SpotlightEntity::getAngle() const
{
	return _angle;
}

const float SpotlightEntity::getDistance() const
{
	return _distance;
}
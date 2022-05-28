#include "spotlight.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Spotlight::Spotlight(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Spotlight::updateTarget()
{
	if(_position != _positionTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_positionTarget - _position);

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

void Spotlight::updateFront()
{
	_front.x = (cos(Mathematics::convertToRadians(_yaw)) * cos(Mathematics::convertToRadians(_pitch)));
	_front.y = sin(Mathematics::convertToRadians(_pitch));
	_front.z = (sin(Mathematics::convertToRadians(_yaw)) * cos(Mathematics::convertToRadians(_pitch)));
	_front = Mathematics::normalize(_front);
}

void Spotlight::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Spotlight::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Spotlight::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Spotlight::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Spotlight::setYaw(float value)
{
	_yaw = Mathematics::limitAngle(value);
}

void Spotlight::setPitch(float value)
{
	_pitch = Mathematics::limitAngle(value);
}

void Spotlight::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void Spotlight::setAngle(float value)
{
	_angle = clamp(value, 0.0f, 45.0f);
}

void Spotlight::setDistance(float value)
{
	_distance = max(0.0f, value);
}

void Spotlight::setVisible(bool value)
{
	_isVisible = value;
}

const string & Spotlight::getId() const
{
	return _id;
}

const fvec3 & Spotlight::getPosition() const
{
	return _position;
}

const fvec3 & Spotlight::getFront() const
{
	return _front;
}

const fvec3 & Spotlight::getColor() const
{
	return _color;
}

const float Spotlight::getYaw() const
{
	return _yaw;
}

const float Spotlight::getPitch() const
{
	return _pitch;
}

const float Spotlight::getIntensity() const
{
	return _intensity;
}

const float Spotlight::getAngle() const
{
	return _angle;
}

const float Spotlight::getDistance() const
{
	return _distance;
}

const bool Spotlight::isVisible() const
{
	return _isVisible;
}
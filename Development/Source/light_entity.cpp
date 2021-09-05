#include "light_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void LightEntity::updateTransformation()
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

void LightEntity::setPosition(Vec3 value)
{
	_position = value;
	_positionTarget = value;
}

void LightEntity::move(Vec3 value)
{
	_position += value;
	_positionTarget += value;
}

void LightEntity::moveTo(Vec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void LightEntity::setRadius(Vec3 value)
{
	_radius = Vec3(max(0.0f, value.r), max(0.0f, value.g), max(0.0f, value.b));
}

void LightEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void LightEntity::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void LightEntity::setShape(LightShape value)
{
	_shape = value;
}

const Vec3 LightEntity::getPosition()
{
	return _position;
}

const Vec3 LightEntity::getRadius()
{
	return _radius;
}

const Vec3 LightEntity::getColor()
{
	return _color;
}

const float LightEntity::getIntensity()
{
	return _intensity;
}

const LightShape LightEntity::getShape()
{
	return _shape;
}
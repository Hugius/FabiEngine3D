#include "pointlight_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void PointlightEntity::updateTransformation()
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

void PointlightEntity::setPosition(Vec3 value)
{
	_position = value;
	_positionTarget = value;
}

void PointlightEntity::move(Vec3 value)
{
	_position += value;
	_positionTarget += value;
}

void PointlightEntity::moveTo(Vec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void PointlightEntity::setRadius(Vec3 value)
{
	_radius = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void PointlightEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void PointlightEntity::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void PointlightEntity::setShape(PointlightShape value)
{
	_shape = value;
}

const Vec3 PointlightEntity::getPosition()
{
	return _position;
}

const Vec3 PointlightEntity::getRadius()
{
	return _radius;
}

const Vec3 PointlightEntity::getColor()
{
	return _color;
}

const float PointlightEntity::getIntensity()
{
	return _intensity;
}

const PointlightShape PointlightEntity::getShape()
{
	return _shape;
}
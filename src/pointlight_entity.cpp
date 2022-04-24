#include "pointlight_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void PointlightEntity::updateTarget()
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

void PointlightEntity::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void PointlightEntity::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void PointlightEntity::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void PointlightEntity::setRadius(const fvec3 & value)
{
	_radius = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void PointlightEntity::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void PointlightEntity::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void PointlightEntity::setShape(PointlightType value)
{
	_shape = value;
}

const fvec3 & PointlightEntity::getPosition() const
{
	return _position;
}

const fvec3 & PointlightEntity::getRadius() const
{
	return _radius;
}

const fvec3 & PointlightEntity::getColor() const
{
	return _color;
}

const float PointlightEntity::getIntensity() const
{
	return _intensity;
}

const PointlightType PointlightEntity::getShape() const
{
	return _shape;
}
#include "pointlight.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Pointlight::Pointlight(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Pointlight::updateTarget()
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

void Pointlight::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Pointlight::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Pointlight::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Pointlight::setRadius(const fvec3 & value)
{
	_radius = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Pointlight::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Pointlight::setIntensity(float value)
{
	_intensity = max(0.0f, value);
}

void Pointlight::setShape(PointlightType value)
{
	_shape = value;
}

void Pointlight::setVisible(bool value)
{
	_isVisible = value;
}

const string & Pointlight::getId() const
{
	return _id;
}

const fvec3 & Pointlight::getPosition() const
{
	return _position;
}

const fvec3 & Pointlight::getRadius() const
{
	return _radius;
}

const fvec3 & Pointlight::getColor() const
{
	return _color;
}

const float Pointlight::getIntensity() const
{
	return _intensity;
}

const bool Pointlight::isVisible() const
{
	return _isVisible;
}

const PointlightType Pointlight::getShape() const
{
	return _shape;
}
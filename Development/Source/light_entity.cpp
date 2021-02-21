#include "light_entity.hpp"

void LightEntity::setPosition(Vec3 value)
{
	_position = value;
}

void LightEntity::translate(Vec3 value)
{
	_position += value;
}

void LightEntity::setColor(Vec3 value)
{
	_color = value;
}

void LightEntity::setIntensity(float value)
{
	_intensity = value;
}

void LightEntity::setDistanceFactor(float value)
{
	_distanceFactor = value;
}

const Vec3 LightEntity::getPosition() const
{
	return _position;
}

const Vec3 LightEntity::getColor() const
{
	return _color;
}

const float LightEntity::getIntensity() const
{
	return _intensity;
}

const float LightEntity::getDistanceFactor() const
{
	return _distanceFactor;
}

#include "light_entity.hpp"

void LightEntity::setPosition(Vec3 position)
{
	_position = position;
}

void LightEntity::setColor(Vec3 color)
{
	_color = color;
}

void LightEntity::setIntensity(float intensity)
{
	_intensity = intensity;
}

void LightEntity::setDistanceFactor(float distance)
{
	_distanceFactor = distance;
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

#include "light_entity.hpp"

void LightEntity::setPosition(vec3 position)
{
	_position = position;
}

void LightEntity::setColor(vec3 color)
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

const vec3 LightEntity::getPosition() const
{
	return _position;
}

const vec3 LightEntity::getColor() const
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

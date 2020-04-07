#include "LightEntity.hpp"

void LightEntity::setPosition(vec3 position)
{
	_position = position;
}

void LightEntity::setColor(vec3 color)
{
	_color = color;
}

void LightEntity::setStrength(float strength)
{
	_strength = strength;
}

const vec3 LightEntity::getPosition() const
{
	return _position;
}

const vec3 LightEntity::getColor() const
{
	return _color;
}

const float LightEntity::getStrength() const
{
	return _strength;
}
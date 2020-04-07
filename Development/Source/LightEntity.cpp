#include <WE3D/LightEntity.hpp>

void LightEntity::setPosition(vec3 position)
{
	p_position = position;
}

void LightEntity::setColor(vec3 color)
{
	p_color = color;
}

void LightEntity::setStrength(float strength)
{
	p_strength = strength;
}

const vec3 LightEntity::getPosition() const
{
	return p_position;
}

const vec3 LightEntity::getColor() const
{
	return p_color;
}

const float LightEntity::getStrength() const
{
	return p_strength;
}
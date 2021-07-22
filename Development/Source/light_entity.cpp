#include "light_entity.hpp"

#include <algorithm>

void LightEntity::setPosition(Vec3 value)
{
	_position = value;
}

void LightEntity::move(Vec3 value)
{
	_position += value;
}

void LightEntity::setColor(Vec3 value)
{
	_color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void LightEntity::setIntensity(float value)
{
	_intensity = std::max(0.0f, value);
}

void LightEntity::setDistanceFactor(float value)
{
	_distanceFactor = std::max(0.0f, value);
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

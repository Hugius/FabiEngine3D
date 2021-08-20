#include "reflection_entity.hpp"

void ReflectionEntity::setPosition(Vec3 value)
{
	_position = value;
}

void ReflectionEntity::move(Vec3 value)
{
	_position += value;
}

void ReflectionEntity::setEnvironmentMap(TextureID value)
{
	_environmentMap = value;
}

const Vec3 ReflectionEntity::getPosition()
{
	return _position;
}

const TextureID ReflectionEntity::getEnvironmentMap()
{
	return _environmentMap;
}
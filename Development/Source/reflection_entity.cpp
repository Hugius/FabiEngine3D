#include "reflection_entity.hpp"
#include "logger.hpp"

void ReflectionEntity::capture()
{
	_mustCapture = true;
}

void ReflectionEntity::setPosition(Vec3 value)
{
	_position = value;
}

void ReflectionEntity::move(Vec3 value)
{
	_position += value;
}

void ReflectionEntity::setCubeMap(TextureID value)
{
	_cubeMap = value;
}

const Vec3 ReflectionEntity::getPosition()
{
	return _position;
}

const bool ReflectionEntity::mustCapture()
{
	bool temp = _mustCapture;
	_mustCapture = false;
	return temp;
}

const TextureID ReflectionEntity::getCubeMap()
{
	return _cubeMap;
}
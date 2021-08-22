#include "reflection_entity.hpp"
#include "logger.hpp"

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

CaptureBuffer& ReflectionEntity::getCaptureBuffer(unsigned int index)
{
	if (index > 5)
	{
		Logger::throwError("ReflectionEntity::getCaptureBuffer");
	}

	return _captureBuffers[index];
}

const Vec3 ReflectionEntity::getPosition()
{
	return _position;
}

const TextureID ReflectionEntity::getEnvironmentMap()
{
	return _environmentMap;
}
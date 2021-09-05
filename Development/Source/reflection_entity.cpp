#include "reflection_entity.hpp"
#include "logger.hpp"

void ReflectionEntity::updateTransformation()
{
	if (_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalizeVector(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		// Correct position
		if (fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if (fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
		if (fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}
}

void ReflectionEntity::capture()
{
	_mustCapture = true;
}

void ReflectionEntity::setCaptured()
{
	_mustCapture = false;
}

void ReflectionEntity::setPosition(Vec3 value)
{
	_position = value;
	_positionTarget = value;
}

void ReflectionEntity::move(Vec3 value)
{
	_position += value;
	_positionTarget += value;
}

void ReflectionEntity::moveTo(Vec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
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
	return _mustCapture;
}

const TextureID ReflectionEntity::getCubeMap()
{
	return _cubeMap;
}
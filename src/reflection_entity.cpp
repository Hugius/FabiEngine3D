#include "reflection_entity.hpp"
#include "logger.hpp"

void ReflectionEntity::updateTarget()
{
	if(_position != _positionTarget)
	{
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		if(fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if(fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
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

void ReflectionEntity::setPosition(const fvec3& value)
{
	_position = value;
	_positionTarget = value;
}

void ReflectionEntity::move(const fvec3& value)
{
	_position += value;
	_positionTarget += value;
}

void ReflectionEntity::moveTo(const fvec3& target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void ReflectionEntity::setCubeMap(shared_ptr<TextureBuffer> value)
{
	_cubeMap = value;
}

void ReflectionEntity::setExceptionModelId(const string& id)
{
	_exceptionModelId = id;
}

const string& ReflectionEntity::getExceptionModelId() const
{
	return _exceptionModelId;
}

const fvec3& ReflectionEntity::getPosition() const
{
	return _position;
}

const bool ReflectionEntity::mustCapture() const
{
	return _mustCapture;
}

const shared_ptr<TextureBuffer> ReflectionEntity::getCubeMap() const
{
	return _cubeMap;
}
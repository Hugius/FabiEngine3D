#include "reflection_entity.hpp"

void ReflectionEntity::updateTarget()
{
	if(_position != _positionTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_positionTarget - _position);
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

void ReflectionEntity::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void ReflectionEntity::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void ReflectionEntity::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void ReflectionEntity::setCubeMap(shared_ptr<TextureBuffer> value)
{
	_cubeTextureBuffer = value;
}

void ReflectionEntity::setExceptionEntityId(const string & id)
{
	_exceptionEntityId = id;
}

const string & ReflectionEntity::getExceptionEntityId() const
{
	return _exceptionEntityId;
}

const fvec3 & ReflectionEntity::getPosition() const
{
	return _position;
}

const bool ReflectionEntity::mustCapture() const
{
	return _mustCapture;
}

const shared_ptr<TextureBuffer> ReflectionEntity::getCubeTextureBuffer() const
{
	return _cubeTextureBuffer;
}
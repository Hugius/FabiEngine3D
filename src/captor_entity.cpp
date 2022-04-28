#include "captor_entity.hpp"

void CaptorEntity::updateTarget()
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

void CaptorEntity::capture()
{
	_mustCapture = true;
}

void CaptorEntity::setCaptured()
{
	_mustCapture = false;
}

void CaptorEntity::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void CaptorEntity::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void CaptorEntity::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void CaptorEntity::setCubeMap(shared_ptr<TextureBuffer> value)
{
	_cubeTextureBuffer = value;
}

void CaptorEntity::setExceptionId(const string & id)
{
	_exceptionId = id;
}

const string & CaptorEntity::getExceptionId() const
{
	return _exceptionId;
}

const fvec3 & CaptorEntity::getPosition() const
{
	return _position;
}

const bool CaptorEntity::mustCapture() const
{
	return _mustCapture;
}

const shared_ptr<TextureBuffer> CaptorEntity::getCubeTextureBuffer() const
{
	return _cubeTextureBuffer;
}
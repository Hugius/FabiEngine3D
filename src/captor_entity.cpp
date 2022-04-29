#include "captor_entity.hpp"

Captor::Captor(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Captor::updateTarget()
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

void Captor::capture()
{
	_mustCapture = true;
}

void Captor::setCaptured()
{
	_mustCapture = false;
}

void Captor::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Captor::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Captor::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Captor::setCubeMap(shared_ptr<TextureBuffer> value)
{
	_cubeTextureBuffer = value;
}

void Captor::setExceptionId(const string & id)
{
	_exceptionId = id;
}

const string & Captor::getExceptionId() const
{
	return _exceptionId;
}

const fvec3 & Captor::getPosition() const
{
	return _position;
}

const bool Captor::mustCapture() const
{
	return _mustCapture;
}

const shared_ptr<TextureBuffer> Captor::getCubeTextureBuffer() const
{
	return _cubeTextureBuffer;
}
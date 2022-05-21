#include "captor.hpp"

using std::clamp;

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
	_mustCaptureReflections = true;
	_mustCaptureRefractions = true;
}

void Captor::setReflectionsCaptured()
{
	_mustCaptureReflections = false;
}

void Captor::setRefractionsCaptured()
{
	_mustCaptureRefractions = false;
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

void Captor::setReflectionCubeMap(shared_ptr<TextureBuffer> value)
{
	_reflectionTextureBuffer = value;
}

void Captor::setRefractionCubeMap(shared_ptr<TextureBuffer> value)
{
	_refractionTextureBuffer = value;
}

void Captor::setExceptionId(const string & value)
{
	_exceptionId = value;
}

void Captor::setReflectionQuality(int value)
{
	_reflectionQuality = clamp(value, 128, 1024);
}

void Captor::setRefractionQuality(int value)
{
	_refractionQuality = clamp(value, 128, 1024);
}

const string & Captor::getId() const
{
	return _id;
}

const string & Captor::getExceptionId() const
{
	return _exceptionId;
}

const fvec3 & Captor::getPosition() const
{
	return _position;
}

const int Captor::getReflectionQuality() const
{
	return _reflectionQuality;
}

const int Captor::getRefractionQuality() const
{
	return _refractionQuality;
}

const bool Captor::mustCaptureReflections() const
{
	return _mustCaptureReflections;
}

const bool Captor::mustCaptureRefractions() const
{
	return _mustCaptureRefractions;
}

const shared_ptr<TextureBuffer> Captor::getReflectionTextureBuffer() const
{
	return _reflectionTextureBuffer;
}

const shared_ptr<TextureBuffer> Captor::getRefractionTextureBuffer() const
{
	return _refractionTextureBuffer;
}
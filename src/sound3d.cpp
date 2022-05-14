#include "sound3d.hpp"

#include <algorithm>

using std::clamp;
using std::max;

Sound3d::Sound3d(const string & id)
	:
	_id(id)
{
	if(_id.empty())
	{
		abort();
	}
}

void Sound3d::updateTarget()
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

void Sound3d::setWaveBuffer(shared_ptr<WaveBuffer> value)
{
	_waveBuffer = value;
}

void Sound3d::setAudioPath(const string & value)
{
	_audioPath = value;
}

void Sound3d::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Sound3d::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Sound3d::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Sound3d::setMaxVolume(float value)
{
	_maxVolume = clamp(value, 0.0f, 1.0f);
}

void Sound3d::setMaxDistance(float value)
{
	_maxDistance = max(0.0f, value);
}

const shared_ptr<WaveBuffer> Sound3d::getWaveBuffer() const
{
	return _waveBuffer;
}

const string & Sound3d::getId() const
{
	return _id;
}

const string & Sound3d::getAudioPath() const
{
	return _audioPath;
}

const fvec3 & Sound3d::getPosition() const
{
	return _position;
}

const float Sound3d::getMaxDistance() const
{
	return _maxDistance;
}

const float Sound3d::getMaxVolume() const
{
	return _maxVolume;
}
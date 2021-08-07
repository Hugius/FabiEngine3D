#include "sound.hpp"

#include <algorithm>

using std::clamp;

Sound::Sound(const string& ID, const string& filePath, Mix_Chunk* dataPointer)
	:
	_ID(ID),
	_filePath(filePath),
	_dataPointer(dataPointer)
{

}

const string& Sound::getID() const
{
	return _ID;
}

const string& Sound::getFilePath() const
{
	return _filePath;
}

Mix_Chunk* Sound::getDataPointer() const
{
	return _dataPointer;
}

void Sound::make3D(Vec3 position, float maxVolume, float maxDistance)
{
	_is3D = true;

	setPosition(position);
	setMaxVolume(maxVolume);
	setMaxDistance(maxDistance);
}

void Sound::setPosition(Vec3 value)
{
	if (_is3D)
	{
		_position = value;
	}
}

void Sound::move(Vec3 value)
{
	if (_is3D)
	{
		_position += value;
	}
}

void Sound::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

void Sound::setMaxVolume(float value)
{
	if (_is3D)
	{
		_maxVolume = clamp(value, 0.0f, 1.0f);
	}
}

void Sound::setMaxDistance(float value)
{
	if (_is3D)
	{
		_maxDistance = value;
	}
}

Vec3 Sound::getPosition() const
{
	return _position;
}

float Sound::getMaxDistance() const
{
	return _maxDistance;
}

float Sound::getVolume() const
{
	return _volume;
}

float Sound::getMaxVolume() const
{
	return _maxVolume;
}

bool Sound::is3D() const
{
	return _is3D;
}
#include "SkyEntity.hpp"

void SkyEntity::setRotationMatrix(const mat4 & val)
{
	_rotationMatrix = val;
}

void SkyEntity::setDayCubeMap(GLuint val)
{
	_dayCubeMap = val;
}

void SkyEntity::setNightCubeMap(GLuint val)
{
	_nightCubeMap = val;
}

void SkyEntity::setMixValue(float val)
{
	_mixValue = val;
}

void SkyEntity::setDayAmbStrength(float val)
{
	_dayAmbStrength = val;
}

void SkyEntity::setNightAmbStrength(float val)
{
	_nightAmbStrength = val;
}

void SkyEntity::setDayDirStrength(float val)
{
	_dayDirStrength = val;
}

void SkyEntity::setNightDirStrength(float val)
{
	_nightDirStrength = val;
}

void SkyEntity::setRotationSpeed(float val)
{
	_rotationSpeed = val;
}

void SkyEntity::setDayTime()
{
	_dayTime = true;
}

void SkyEntity::setNightTime()
{
	_dayTime = false;
}

const mat4 & SkyEntity::getRotationMatrix() const
{
	return _rotationMatrix;
}

const GLuint SkyEntity::getDayCubeMap() const
{
	return _dayCubeMap;
}

const GLuint SkyEntity::getNightCubeMap() const
{
	return _nightCubeMap;
}

const float SkyEntity::getMixValue() const
{
	return _mixValue;
}

const float SkyEntity::getAmbStrength() const
{
	if (_dayTime)
	{
		return _dayAmbStrength;
	}
	else
	{
		return _nightAmbStrength;
	}
}

const float SkyEntity::getDirStrength() const
{
	if (_dayTime)
	{
		return _dayDirStrength;
	}
	else
	{
		return _nightDirStrength;
	}
}

const float SkyEntity::getRotationSpeed() const
{
	return _rotationSpeed;
}

const bool SkyEntity::isDayTime() const
{
	return _dayTime;
}

const bool SkyEntity::isNightTime() const
{
	return !_dayTime;
}

const GLuint SkyEntity::getCurrentCubeMap() const
{
	if (_mixValue > 0.5f) // Night
	{
		return _nightCubeMap;
	}
	else // Day
	{
		return _dayCubeMap;
	}
}
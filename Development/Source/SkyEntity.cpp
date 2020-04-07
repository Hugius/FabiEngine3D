#include <WE3D/SkyEntity.hpp>

void SkyEntity::setRotationMatrix(const mat4 & val)
{
	p_rotationMatrix = val;
}

void SkyEntity::setDayCubeMap(GLuint val)
{
	p_dayCubeMap = val;
}

void SkyEntity::setNightCubeMap(GLuint val)
{
	p_nightCubeMap = val;
}

void SkyEntity::setMixValue(float val)
{
	p_mixValue = val;
}

void SkyEntity::setDayAmbStrength(float val)
{
	p_dayAmbStrength = val;
}

void SkyEntity::setNightAmbStrength(float val)
{
	p_nightAmbStrength = val;
}

void SkyEntity::setDayDirStrength(float val)
{
	p_dayDirStrength = val;
}

void SkyEntity::setNightDirStrength(float val)
{
	p_nightDirStrength = val;
}

void SkyEntity::setRotationSpeed(float val)
{
	p_rotationSpeed = val;
}

void SkyEntity::setDayTime()
{
	p_dayTime = true;
}

void SkyEntity::setNightTime()
{
	p_dayTime = false;
}

const mat4 & SkyEntity::getRotationMatrix() const
{
	return p_rotationMatrix;
}

const GLuint SkyEntity::getDayCubeMap() const
{
	return p_dayCubeMap;
}

const GLuint SkyEntity::getNightCubeMap() const
{
	return p_nightCubeMap;
}

const float SkyEntity::getMixValue() const
{
	return p_mixValue;
}

const float SkyEntity::getAmbStrength() const
{
	if (p_dayTime)
	{
		return p_dayAmbStrength;
	}
	else
	{
		return p_nightAmbStrength;
	}
}

const float SkyEntity::getDirStrength() const
{
	if (p_dayTime)
	{
		return p_dayDirStrength;
	}
	else
	{
		return p_nightDirStrength;
	}
}

const float SkyEntity::getRotationSpeed() const
{
	return p_rotationSpeed;
}

const bool SkyEntity::isDayTime() const
{
	return p_dayTime;
}

const bool SkyEntity::isNightTime() const
{
	return !p_dayTime;
}

const GLuint SkyEntity::getCurrentCubeMap() const
{
	if (p_mixValue > 0.5f) // Night
	{
		return p_nightCubeMap;
	}
	else // Day
	{
		return p_dayCubeMap;
	}
}
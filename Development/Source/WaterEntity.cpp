#pragma once
#include <WE3D/WaterEntity.hpp>

void WaterEntity::setColor(vec3 val)
{
	p_color = val;
}

void WaterEntity::setDudvMap(GLuint val)
{
	p_dudvMap = val;
}

void WaterEntity::setNormalMap(GLuint val)
{
	p_normalMap = val;
}

void WaterEntity::setWaveValue(float val)
{
	p_waveValue = val;
}

void WaterEntity::setTileRepeat(float val)
{
	p_tileRepeat = val;
}

void WaterEntity::setWavingSpeed(float val)
{
	p_wavingSpeed = val;
}

void WaterEntity::setTimeX(float val)
{
	p_timeX = val;
}

void WaterEntity::setTimeZ(float val)
{
	p_timeZ = val;
}

void WaterEntity::setShininess(float val)
{
	p_shininess = val;
}

void WaterEntity::setWaving(bool val)
{
	p_waving = val;
}

void WaterEntity::setRippling(bool val)
{
	p_rippling = val;
}

void WaterEntity::setSurfaceHeight(float val)
{
	p_surfaceHeight = val;
}

void WaterEntity::setTransparency(float val)
{
	p_transparency = val;
}

const vec3 WaterEntity::getColor() const
{
	return p_color;
}

const GLuint WaterEntity::getDudvMap() const
{
	return p_dudvMap;
}

const GLuint WaterEntity::getNormalMap() const
{
	return p_normalMap;
}

const float WaterEntity::getWaveValue() const
{
	return p_waveValue;
}

const float WaterEntity::getTileRepeat() const
{
	return p_tileRepeat;
}

const float WaterEntity::getWavingSpeed() const
{
	return p_wavingSpeed;
}

const float WaterEntity::getTimeX() const
{
	return p_timeX;
}

const float WaterEntity::getTimeZ() const
{
	return p_timeZ;
}

const float WaterEntity::getShininess() const
{
	return p_shininess;
}

const float WaterEntity::getSurfaceHeight() const
{
	return p_surfaceHeight;
}

const float WaterEntity::getTransparency() const
{
	return p_transparency;
}

const bool WaterEntity::isWaving() const
{
	return p_waving;
}

const bool WaterEntity::isRippling() const
{
	return p_rippling;
}

#pragma once

#include "water_entity.hpp"

void WaterEntity::setPosition(vec3 val)
{
	_position = val;
}

void WaterEntity::setColor(vec3 val)
{
	_color = val;
}

void WaterEntity::setDudvMap(GLuint val)
{
	_dudvMap = val;
}

void WaterEntity::setNormalMap(GLuint val)
{
	_normalMap = val;
}

void WaterEntity::setDisplacementMap(GLuint val)
{
	_displacementMap = val;
}

void WaterEntity::setRippleOffset(float val)
{
	_rippleOffset = val;
}

void WaterEntity::setUvRepeat(float val)
{
	_uvRepeat = val;
}

void WaterEntity::setSpeed(float val)
{
	_speed = val;
}

void WaterEntity::setWaveOffset(float val)
{
	_waveOffset = val;
}

void WaterEntity::setWaveHeightFactor(float val)
{
	_waveHeightFactor = val;
}

void WaterEntity::setSpecularLightingFactor(float val)
{
	_specularLightingFactor = val;
}

void WaterEntity::setSpecularLightingIntensity(float val)
{
	_specularLightingIntensity = val;
}

void WaterEntity::setWaving(bool val)
{
	_waving = val;
}

void WaterEntity::setRippling(bool val)
{
	_rippling = val;
}

void WaterEntity::setSpecular(bool val)
{
	_specular = val;
}

void WaterEntity::setReflective(bool val)
{
	_reflective = val;
}

void WaterEntity::setRefractive(bool val)
{
	_refractive = val;
}

void WaterEntity::setSize(float val)
{
	_size = val;
}

void WaterEntity::setTransparency(float val)
{
	_transparency = val;
}

const vec3 WaterEntity::getPosition() const
{
	return _position;
}

const vec3 WaterEntity::getColor() const
{
	return _color;
}

const GLuint WaterEntity::getDudvMap() const
{
	return _dudvMap;
}

const GLuint WaterEntity::getNormalMap() const
{
	return _normalMap;
}

const GLuint WaterEntity::getDisplacementMap() const
{
	return _displacementMap;
}

const float WaterEntity::getRippleOffset() const
{
	return _rippleOffset;
}

const float WaterEntity::getUvRepeat() const
{
	return _uvRepeat;
}

const float WaterEntity::getSpeed() const
{
	return _speed;
}

const float WaterEntity::getWaveOffset() const
{
	return _waveOffset;
}

const float WaterEntity::getWaveHeightFactor() const
{
	return _waveHeightFactor;
}

const float WaterEntity::getSpecularLightingFactor() const
{
	return _specularLightingFactor;
}

const float WaterEntity::getSpecularLightingIntensity() const
{
	return _specularLightingIntensity;
}

const float WaterEntity::getSize() const
{
	return _size;
}

const float WaterEntity::getTransparency() const
{
	return _transparency;
}

const bool WaterEntity::isWaving() const
{
	return _waving;
}

const bool WaterEntity::isRippling() const
{
	return _rippling;
}

const bool WaterEntity::isSpecular() const
{
	return _specular;;
}

const bool WaterEntity::isReflective() const
{
	return _reflective;
}

const bool WaterEntity::isRefractive() const
{
	return _refractive;
}
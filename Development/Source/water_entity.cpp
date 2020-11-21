#pragma once

#include "water_entity.hpp"

void WaterEntity::setPosition(Vec3 val)
{
	_position = val;
}

void WaterEntity::setColor(Vec3 val)
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

void WaterEntity::setDudvMapPath(const string& val)
{
	_dudvMapPath = val;
}

void WaterEntity::setNormalMapPath(const string& val)
{
	_normalMapPath = val;
}

void WaterEntity::setDisplacementMapPath(const string& val)
{
	_displacementMapPath = val;
}

void WaterEntity::setRippleOffset(Vec2 val)
{
	_rippleOffset = val;
}

void WaterEntity::setUvRepeat(float val)
{
	_uvRepeat = val;
}

void WaterEntity::setSpeed(Vec2 val)
{
	_speed = val;
}

void WaterEntity::setWaveOffset(Vec2 val)
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
	_isWaving = val;
}

void WaterEntity::setRippling(bool val)
{
	_isRippling = val;
}

void WaterEntity::setSpecularLighted(bool val)
{
	_isSpecularLighted = val;
}

void WaterEntity::setReflective(bool val)
{
	_isReflective = val;
}

void WaterEntity::setRefractive(bool val)
{
	_isRefractive = val;
}

void WaterEntity::setSimplifiedOglBuffer(OpenGLBuffer* buffer)
{
	_simplifiedOglBuffer = buffer;
}

void WaterEntity::setSize(float val)
{
	_size = val;
}

void WaterEntity::setTransparency(float val)
{
	_transparency = val;
}

const Vec3 WaterEntity::getPosition() const
{
	return _position;
}

const Vec3 WaterEntity::getColor() const
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

const string& WaterEntity::getDudvMapPath() const
{
	return _dudvMapPath;
}

const string& WaterEntity::getNormalMapPath() const
{
	return _normalMapPath;
}

const string& WaterEntity::getDisplacementMapPath() const
{
	return _displacementMapPath;
}

const Vec2 WaterEntity::getRippleOffset() const
{
	return _rippleOffset;
}

const float WaterEntity::getUvRepeat() const
{
	return _uvRepeat;
}

const Vec2 WaterEntity::getSpeed() const
{
	return _speed;
}

const Vec2 WaterEntity::getWaveOffset() const
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
	return _isWaving;
}

const bool WaterEntity::isRippling() const
{
	return _isRippling;
}

const bool WaterEntity::isSpecularLighted() const
{
	return _isSpecularLighted;;
}

const bool WaterEntity::isReflective() const
{
	return _isReflective;
}

const bool WaterEntity::isRefractive() const
{
	return _isRefractive;
}

const OpenGLBuffer* WaterEntity::getSimplifiedOglBuffer() const
{
	return _simplifiedOglBuffer;
}
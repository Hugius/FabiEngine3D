#include "water_entity.hpp"

#include <algorithm>

void WaterEntity::setPosition(Vec3 value)
{
	_position = value;
}

void WaterEntity::setColor(Vec3 value)
{
	_color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void WaterEntity::setDudvMap(GLuint value)
{
	_dudvMap = value;
}

void WaterEntity::setNormalMap(GLuint value)
{
	_normalMap = value;
}

void WaterEntity::setDisplacementMap(GLuint value)
{
	_displacementMap = value;
}

void WaterEntity::setDudvMapPath(const string& value)
{
	_dudvMapPath = value;
}

void WaterEntity::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void WaterEntity::setDisplacementMapPath(const string& value)
{
	_displacementMapPath = value;
}

void WaterEntity::setRippleOffset(Vec2 value)
{
	_rippleOffset = value;
}

void WaterEntity::setUvRepeat(float value)
{
	_uvRepeat = std::max(0.0f, value);
}

void WaterEntity::setQuality(WaterQuality quality)
{
	_quality = quality;
}

void WaterEntity::setSpeed(Vec2 value)
{
	_speed = value;
}

void WaterEntity::setWaveOffset(Vec2 value)
{
	_waveOffset = value;
}

void WaterEntity::setWaveHeight(float value)
{
	_waveHeight = std::max(0.0f, value);
}

void WaterEntity::setSpecularLightingFactor(float value)
{
	_specularLightingFactor = std::max(0.0f, value);
}

void WaterEntity::setSpecularLightingIntensity(float value)
{
	_specularLightingIntensity = std::max(0.0f, value);
}

void WaterEntity::setWaving(bool value)
{
	_isWaving = value;
}

void WaterEntity::setRippling(bool value)
{
	_isRippling = value;
}

void WaterEntity::setSpecularLighted(bool value)
{
	_isSpecularLighted = value;
}

void WaterEntity::setReflective(bool value)
{
	_isReflective = value;
}

void WaterEntity::setRefractive(bool value)
{
	_isRefractive = value;
}

void WaterEntity::setSimplifiedRenderBuffer(RenderBuffer* buffer)
{
	_simplifiedRenderBuffer = buffer;
}

void WaterEntity::setSize(float value)
{
	_size = std::max(0.0f, value);
}

void WaterEntity::setTransparency(float value)
{
	_transparency = std::max(0.0f, value);
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

const WaterQuality WaterEntity::getQuality() const
{
	return _quality;
}

const Vec2 WaterEntity::getSpeed() const
{
	return _speed;
}

const Vec2 WaterEntity::getWaveOffset() const
{
	return _waveOffset;
}

const float WaterEntity::getWaveHeight() const
{
	return _waveHeight;
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
	return _isSpecularLighted;
}

const bool WaterEntity::isReflective() const
{
	return _isReflective;
}

const bool WaterEntity::isRefractive() const
{
	return _isRefractive;
}

const bool WaterEntity::hasDudvMap() const
{
	return (_dudvMap != 0);
}

const bool WaterEntity::hasNormalMap() const
{
	return (_normalMap != 0);
}

const bool WaterEntity::hasDisplacementMap() const
{
	return (_displacementMap != 0);
}

const RenderBuffer* WaterEntity::getSimplifiedRenderBuffer() const
{
	return _simplifiedRenderBuffer;
}
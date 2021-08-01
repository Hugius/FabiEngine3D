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

void WaterEntity::setDudvMap(TextureID value)
{
	_dudvMap = value;
}

void WaterEntity::setNormalMap(TextureID value)
{
	_normalMap = value;
}

void WaterEntity::setDisplacementMap(TextureID value)
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

void WaterEntity::setLowQualityRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_lowQualityRenderBuffer = value;
}

void WaterEntity::setHighQualityRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_highQualityRenderBuffer = value;
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

void WaterEntity::setWireFramed(bool value)
{
	_isWireFramed = value;
}

void WaterEntity::setSize(float value)
{
	_size = std::max(0.0f, value);
}

void WaterEntity::setTransparency(float value)
{
	_transparency = std::max(0.0f, value);
}

const Vec3 WaterEntity::getPosition()
{
	return _position;
}

const Vec3 WaterEntity::getColor()
{
	return _color;
}

const TextureID WaterEntity::getDudvMap()
{
	return _dudvMap;
}

const TextureID WaterEntity::getNormalMap()
{
	return _normalMap;
}

const TextureID WaterEntity::getDisplacementMap()
{
	return _displacementMap;
}

const string& WaterEntity::getDudvMapPath()
{
	return _dudvMapPath;
}

const string& WaterEntity::getNormalMapPath()
{
	return _normalMapPath;
}

const string& WaterEntity::getDisplacementMapPath()
{
	return _displacementMapPath;
}

const Vec2 WaterEntity::getRippleOffset()
{
	return _rippleOffset;
}

const float WaterEntity::getUvRepeat()
{
	return _uvRepeat;
}

const shared_ptr<RenderBuffer> WaterEntity::getLowQualityRenderBuffer()
{
	return _lowQualityRenderBuffer;
}

const shared_ptr<RenderBuffer> WaterEntity::getHighQualityRenderBuffer()
{
	return _highQualityRenderBuffer;
}

const WaterQuality WaterEntity::getQuality()
{
	return _quality;
}

const Vec2 WaterEntity::getSpeed()
{
	return _speed;
}

const Vec2 WaterEntity::getWaveOffset()
{
	return _waveOffset;
}

const float WaterEntity::getWaveHeight()
{
	return _waveHeight;
}

const float WaterEntity::getSpecularLightingFactor()
{
	return _specularLightingFactor;
}

const float WaterEntity::getSpecularLightingIntensity()
{
	return _specularLightingIntensity;
}

const float WaterEntity::getSize()
{
	return _size;
}

const float WaterEntity::getTransparency()
{
	return _transparency;
}

const bool WaterEntity::isWaving()
{
	return _isWaving;
}

const bool WaterEntity::isRippling()
{
	return _isRippling;
}

const bool WaterEntity::isSpecularLighted()
{
	return _isSpecularLighted;
}

const bool WaterEntity::isReflective()
{
	return _isReflective;
}

const bool WaterEntity::isRefractive()
{
	return _isRefractive;
}

const bool WaterEntity::isWireFramed()
{
	return _isWireFramed;
}

const bool WaterEntity::hasLowQualityRenderBuffer()
{
	return (_lowQualityRenderBuffer != nullptr);
}

const bool WaterEntity::hasHighQualityRenderBuffer()
{
	return (_highQualityRenderBuffer != nullptr);
}

const bool WaterEntity::hasDudvMap()
{
	return (_dudvMap != 0);
}

const bool WaterEntity::hasNormalMap()
{
	return (_normalMap != 0);
}

const bool WaterEntity::hasDisplacementMap()
{
	return (_displacementMap != 0);
}
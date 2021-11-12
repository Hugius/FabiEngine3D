#include "water_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void WaterEntity::setHeight(float value)
{
	_height = value;
}

void WaterEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
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

void WaterEntity::setTextureRepeat(float value)
{
	_textureRepeat = max(0.0f, value);
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
	_waveHeight = max(0.0f, value);
}

void WaterEntity::setSpecularShininess(float value)
{
	_specularShininess = max(0.0f, value);
}

void WaterEntity::setSpecularIntensity(float value)
{
	_specularIntensity = max(0.0f, value);
}

void WaterEntity::setSpecular(bool value)
{
	_isSpecular = value;
}

void WaterEntity::setReflective(bool value)
{
	_isReflective = value;
}

void WaterEntity::setRefractive(bool value)
{
	_isRefractive = value;
}

void WaterEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void WaterEntity::setSize(float value)
{
	_size = max(0.0f, value);
}

void WaterEntity::setTransparency(float value)
{
	_transparency = max(0.0f, value);
}

const float WaterEntity::getHeight() const
{
	return _height;
}

const Vec3 WaterEntity::getColor() const
{
	return _color;
}

const TextureID WaterEntity::getDudvMap() const
{
	return _dudvMap;
}

const TextureID WaterEntity::getNormalMap() const
{
	return _normalMap;
}

const TextureID WaterEntity::getDisplacementMap() const
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

const float WaterEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const shared_ptr<RenderBuffer> WaterEntity::getLowQualityRenderBuffer() const
{
	return _lowQualityRenderBuffer;
}

const shared_ptr<RenderBuffer> WaterEntity::getHighQualityRenderBuffer() const
{
	return _highQualityRenderBuffer;
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

const float WaterEntity::getSpecularShininess() const
{
	return _specularShininess;
}

const float WaterEntity::getSpecularIntensity() const
{
	return _specularIntensity;
}

const float WaterEntity::getSize() const
{
	return _size;
}

const float WaterEntity::getTransparency() const
{
	return _transparency;
}

const bool WaterEntity::isSpecular() const
{
	return _isSpecular;
}

const bool WaterEntity::isReflective() const
{
	return _isReflective;
}

const bool WaterEntity::isRefractive() const
{
	return _isRefractive;
}

const bool WaterEntity::isWireframed() const
{
	return _isWireframed;
}

const bool WaterEntity::hasLowQualityRenderBuffer() const
{
	return (_lowQualityRenderBuffer != nullptr);
}

const bool WaterEntity::hasHighQualityRenderBuffer() const
{
	return (_highQualityRenderBuffer != nullptr);
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
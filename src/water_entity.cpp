#include "water_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void WaterEntity::setHeight(float value)
{
	_height = value;
}

void WaterEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void WaterEntity::setDudvMap(shared_ptr<TextureBuffer> value)
{
	_dudvMap = value;
}

void WaterEntity::setNormalMap(shared_ptr<TextureBuffer> value)
{
	_normalMap = value;
}

void WaterEntity::setDisplacementMap(shared_ptr<TextureBuffer> value)
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

void WaterEntity::setRippleOffset(fvec2 value)
{
	_rippleOffset = value;
}

void WaterEntity::setTextureRepeat(float value)
{
	_textureRepeat = max(0.0f, value);
}

void WaterEntity::setLowQualityVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_lowQualityVertexBuffer = value;
}

void WaterEntity::setHighQualityVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_highQualityVertexBuffer = value;
}

void WaterEntity::setQuality(WaterQuality quality)
{
	_quality = quality;
}

void WaterEntity::setSpeed(fvec2 value)
{
	_speed = value;
}

void WaterEntity::setWaveOffset(fvec2 value)
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

void WaterEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
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

const fvec3 WaterEntity::getColor() const
{
	return _color;
}

const shared_ptr<TextureBuffer> WaterEntity::getDudvMap() const
{
	return _dudvMap;
}

const shared_ptr<TextureBuffer> WaterEntity::getNormalMap() const
{
	return _normalMap;
}

const shared_ptr<TextureBuffer> WaterEntity::getDisplacementMap() const
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

const fvec2 WaterEntity::getRippleOffset() const
{
	return _rippleOffset;
}

const float WaterEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const shared_ptr<VertexBuffer> WaterEntity::getLowQualityVertexBuffer() const
{
	return _lowQualityVertexBuffer;
}

const shared_ptr<VertexBuffer> WaterEntity::getHighQualityVertexBuffer() const
{
	return _highQualityVertexBuffer;
}

const WaterQuality WaterEntity::getQuality() const
{
	return _quality;
}

const fvec2 WaterEntity::getSpeed() const
{
	return _speed;
}

const fvec2 WaterEntity::getWaveOffset() const
{
	return _waveOffset;
}

const fvec3 WaterEntity::getWireframeColor() const
{
	return _wireframeColor;
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

const bool WaterEntity::hasLowQualityVertexBuffer() const
{
	return (_lowQualityVertexBuffer != nullptr);
}

const bool WaterEntity::hasHighQualityVertexBuffer() const
{
	return (_highQualityVertexBuffer != nullptr);
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
#include "water_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void WaterEntity::setHeight(float value)
{
	_height = value;
}

void WaterEntity::setColor(const fvec3& value)
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

void WaterEntity::setRippleOffset(const fvec2& value)
{
	_rippleOffset = value;
}

void WaterEntity::setTextureRepeat(float value)
{
	_textureRepeat = max(0.0f, value);
}

void WaterEntity::setLowQualityMesh(shared_ptr<VertexBuffer> value)
{
	_lowQualityMesh = value;
}

void WaterEntity::setHighQualityMesh(shared_ptr<VertexBuffer> value)
{
	_highQualityMesh = value;
}

void WaterEntity::setQuality(WaterQuality quality)
{
	_quality = quality;
}

void WaterEntity::setRippleSpeed(const fvec2& value)
{
	_rippleSpeed = value;
}

void WaterEntity::setWaveSpeed(const fvec2& value)
{
	_waveSpeed = value;
}

void WaterEntity::setWaveOffset(const fvec2& value)
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

void WaterEntity::setWireframeColor(const fvec3& value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void WaterEntity::setSize(float value)
{
	_size = max(0.0f, value);
}

void WaterEntity::setMaxDepth(float value)
{
	_maxDepth = max(0.0f, value);
}

void WaterEntity::setEdged(bool value)
{
	_isEdged = value;
}

const float WaterEntity::getHeight() const
{
	return _height;
}

const fvec3& WaterEntity::getColor() const
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

const fvec2& WaterEntity::getRippleOffset() const
{
	return _rippleOffset;
}

const float WaterEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const shared_ptr<VertexBuffer> WaterEntity::getLowQualityMesh() const
{
	return _lowQualityMesh;
}

const shared_ptr<VertexBuffer> WaterEntity::getHighQualityMesh() const
{
	return _highQualityMesh;
}

const WaterQuality WaterEntity::getQuality() const
{
	return _quality;
}

const fvec2& WaterEntity::getRippleSpeed() const
{
	return _rippleSpeed;
}

const fvec2& WaterEntity::getWaveOffset() const
{
	return _waveOffset;
}

const fvec2& WaterEntity::getWaveSpeed() const
{
	return _waveSpeed;
}

const fvec3& WaterEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const float WaterEntity::getWaveHeight() const
{
	return _waveHeight;
}

const float WaterEntity::getMaxDepth() const
{
	return _maxDepth;
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

const bool WaterEntity::isEdged() const
{
	return _isEdged;
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
#include "water.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Water::Water(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Water::setHeight(float value)
{
	_height = value;
}

void Water::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Water::setDudvMap(shared_ptr<TextureBuffer> value)
{
	_dudvTextureBuffer = value;
}

void Water::setNormalMap(shared_ptr<TextureBuffer> value)
{
	_normalTextureBuffer = value;
}

void Water::setHeightMap(shared_ptr<TextureBuffer> value)
{
	_heightTextureBuffer = value;
}

void Water::setDudvMapPath(const string & value)
{
	_dudvMapPath = value;
}

void Water::setNormalMapPath(const string & value)
{
	_normalMapPath = value;
}

void Water::setHeightMapPath(const string & value)
{
	_heightMapPath = value;
}

void Water::setRippleOffset(const fvec2 & value)
{
	_rippleOffset = value;
}

void Water::setTextureRepeat(int value)
{
	_textureRepeat = max(1, value);
}

void Water::setLowQualityVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_lowQualityVertexBuffer = value;
}

void Water::setHighQualityVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_highQualityVertexBuffer = value;
}

void Water::setRippleSpeed(const fvec2 & value)
{
	_rippleSpeed = value;
}

void Water::setWaveSpeed(const fvec2 & value)
{
	_waveSpeed = value;
}

void Water::setWaveOffset(const fvec2 & value)
{
	_waveOffset = value;
}

void Water::setWaveHeight(float value)
{
	_waveHeight = max(0.0f, value);
}

void Water::setSpecularShininess(float value)
{
	_specularShininess = max(0.0f, value);
}

void Water::setSpecularIntensity(float value)
{
	_specularIntensity = max(0.0f, value);
}

void Water::setSpecular(bool value)
{
	_isSpecular = value;
}

void Water::setReflective(bool value)
{
	_isReflective = value;
}

void Water::setRefractive(bool value)
{
	_isRefractive = value;
}

void Water::setWireframed(bool value)
{
	_isWireframed = value;
}

void Water::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Water::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void Water::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void Water::setVisible(bool value)
{
	_isVisible = value;
}

void Water::setSize(float value)
{
	_size = clamp(value, 0.0f, MAX_SIZE);
}

void Water::setMaxDepth(float value)
{
	_maxDepth = max(0.0f, value);
}

void Water::setEdged(bool value)
{
	_isEdged = value;
}

const float Water::getHeight() const
{
	return _height;
}

const fvec3 & Water::getColor() const
{
	return _color;
}

const shared_ptr<TextureBuffer> Water::getDudvTextureBuffer() const
{
	return _dudvTextureBuffer;
}

const shared_ptr<TextureBuffer> Water::getNormalTextureBuffer() const
{
	return _normalTextureBuffer;
}

const shared_ptr<TextureBuffer> Water::getHeightTextureBuffer() const
{
	return _heightTextureBuffer;
}

const string & Water::getId() const
{
	return _id;
}

const string & Water::getDudvMapPath() const
{
	return _dudvMapPath;
}

const string & Water::getNormalMapPath() const
{
	return _normalMapPath;
}

const string & Water::getHeightMapPath() const
{
	return _heightMapPath;
}

const fvec2 & Water::getRippleOffset() const
{
	return _rippleOffset;
}

const int Water::getTextureRepeat() const
{
	return _textureRepeat;
}

const shared_ptr<VertexBuffer> Water::getLowQualityVertexBuffer() const
{
	return _lowQualityVertexBuffer;
}

const shared_ptr<VertexBuffer> Water::getHighQualityVertexBuffer() const
{
	return _highQualityVertexBuffer;
}

const fvec2 & Water::getRippleSpeed() const
{
	return _rippleSpeed;
}

const fvec2 & Water::getWaveOffset() const
{
	return _waveOffset;
}

const fvec2 & Water::getWaveSpeed() const
{
	return _waveSpeed;
}

const fvec3 & Water::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Water::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Water::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const float Water::getWaveHeight() const
{
	return _waveHeight;
}

const float Water::getMaxDepth() const
{
	return _maxDepth;
}

const float Water::getSpecularShininess() const
{
	return _specularShininess;
}

const float Water::getSpecularIntensity() const
{
	return _specularIntensity;
}

const float Water::getSize() const
{
	return _size;
}

const bool Water::isEdged() const
{
	return _isEdged;
}

const bool Water::isVisible() const
{
	return _isVisible;
}

const bool Water::isSpecular() const
{
	return _isSpecular;
}

const bool Water::isReflective() const
{
	return _isReflective;
}

const bool Water::isRefractive() const
{
	return _isRefractive;
}

const bool Water::isWireframed() const
{
	return _isWireframed;
}
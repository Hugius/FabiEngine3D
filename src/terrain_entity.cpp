#include "terrain_entity.hpp"

using std::max;
using std::clamp;

void TerrainEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void TerrainEntity::setPixels(const vector<float> & value)
{
	_pixels = value;
}

void TerrainEntity::setHeightMapPath(const string & value)
{
	_heightMapPath = value;
}

void TerrainEntity::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseTextureBuffer = value;
}

void TerrainEntity::setDiffuseMapPath(const string & value)
{
	_diffuseMapPath = value;
}

void TerrainEntity::setNormalMap(shared_ptr<TextureBuffer> value)
{
	_normalTextureBuffer = value;
}

void TerrainEntity::setNormalMapPath(const string & value)
{
	_normalMapPath = value;
}

void TerrainEntity::setBlendMap(shared_ptr<TextureBuffer> value)
{
	_blendTextureBuffer = value;
}

void TerrainEntity::setBlendMapPath(const string & value)
{
	_blendMapPath = value;
}

void TerrainEntity::setRedDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_redDiffuseTextureBuffer = value;
}

void TerrainEntity::setRedDiffuseMapPath(const string & value)
{
	_redDiffuseMapPath = value;
}

void TerrainEntity::setGreenDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_greenDiffuseTextureBuffer = value;
}

void TerrainEntity::setGreenDiffuseMapPath(const string & value)
{
	_greenDiffuseMapPath = value;
}

void TerrainEntity::setBlueDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_blueDiffuseTextureBuffer = value;
}

void TerrainEntity::setBlueDiffuseMapPath(const string & value)
{
	_blueDiffuseMapPath = value;
}

void TerrainEntity::setRedNormalMap(shared_ptr<TextureBuffer> value)
{
	_redNormalTextureBuffer = value;
}

void TerrainEntity::setRedNormalMapPath(const string & value)
{
	_redNormalMapPath = value;
}

void TerrainEntity::setGreenNormalMap(shared_ptr<TextureBuffer> value)
{
	_greenNormalTextureBuffer = value;
}

void TerrainEntity::setGreenNormalMapPath(const string & value)
{
	_greenNormalMapPath = value;
}

void TerrainEntity::setBlueNormalMap(shared_ptr<TextureBuffer> value)
{
	_blueNormalTextureBuffer = value;
}

void TerrainEntity::setBlueNormalMapPath(const string & filePath)
{
	_blueNormalMapPath = filePath;
}

void TerrainEntity::setTextureRepeat(unsigned int value)
{
	_textureRepeat = max(unsigned int(1), value);
}

void TerrainEntity::setRedTextureRepeat(unsigned int value)
{
	_redTextureRepeat = max(unsigned int(1), value);
}

void TerrainEntity::setGreenTextureRepeat(unsigned int value)
{
	_greenTextureRepeat = max(unsigned int(1), value);
}

void TerrainEntity::setBlueTextureRepeat(unsigned int value)
{
	_blueTextureRepeat = max(unsigned int(1), value);
}

void TerrainEntity::setSize(float value)
{
	_size = max(0.0f, value);
}

void TerrainEntity::setMaxHeight(float value)
{
	_maxHeight = max(0.0f, value);
}

void TerrainEntity::setSpecular(bool value)
{
	_isSpecular = value;
}

void TerrainEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void TerrainEntity::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void TerrainEntity::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void TerrainEntity::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void TerrainEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void TerrainEntity::setSpecularShininess(float value)
{
	_specularShininess = max(0.0f, value);
}

void TerrainEntity::setSpecularIntensity(float value)
{
	_specularIntensity = max(0.0f, value);
}

const shared_ptr<TextureBuffer> TerrainEntity::getDiffuseTextureBuffer() const
{
	return _diffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getNormalTextureBuffer() const
{
	return _normalTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getBlendTextureBuffer() const
{
	return _blendTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getRedDiffuseTextureBuffer() const
{
	return _redDiffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getGreenDiffuseTextureBuffer() const
{
	return _greenDiffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getBlueDiffuseTextureBuffer() const
{
	return _blueDiffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getRedNormalTextureBuffer() const
{
	return _redNormalTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getGreenNormalTextureBuffer() const
{
	return _greenNormalTextureBuffer;
}

const shared_ptr<TextureBuffer> TerrainEntity::getBlueNormalTextureBuffer() const
{
	return _blueNormalTextureBuffer;
}

const string & TerrainEntity::getHeightMapPath() const
{
	return _heightMapPath;
}

const string & TerrainEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string & TerrainEntity::getNormalMapPath() const
{
	return _normalMapPath;
}

const string & TerrainEntity::getBlendMapPath() const
{
	return _blendMapPath;
}

const string & TerrainEntity::getRedDiffuseMapPath() const
{
	return _redDiffuseMapPath;
}

const string & TerrainEntity::getGreenDiffuseMapPath() const
{
	return _greenDiffuseMapPath;
}

const string & TerrainEntity::getBlueDiffuseMapPath() const
{
	return _blueDiffuseMapPath;
}

const string & TerrainEntity::getRedNormalMapPath() const
{
	return _redNormalMapPath;
}

const string & TerrainEntity::getGreenNormalMapPath() const
{
	return _greenNormalMapPath;
}

const string & TerrainEntity::getBlueNormalMapPath() const
{
	return _blueNormalMapPath;
}

const fvec3 & TerrainEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & TerrainEntity::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & TerrainEntity::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const unsigned int TerrainEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const unsigned int TerrainEntity::getRedTextureRepeat() const
{
	return _redTextureRepeat;
}

const unsigned int TerrainEntity::getGreenTextureRepeat() const
{
	return _greenTextureRepeat;
}

const unsigned int TerrainEntity::getBlueTextureRepeat() const
{
	return _blueTextureRepeat;
}

const float TerrainEntity::getSize() const
{
	return _size;
}

const float TerrainEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float TerrainEntity::getLightness() const
{
	return _lightness;
}

const float TerrainEntity::getSpecularShininess() const
{
	return _specularShininess;
}

const float TerrainEntity::getSpecularIntensity() const
{
	return _specularIntensity;
}

const shared_ptr<VertexBuffer> TerrainEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const vector<float> & TerrainEntity::getPixels() const
{
	return _pixels;
}

const bool TerrainEntity::isSpecular() const
{
	return _isSpecular;
}

const bool TerrainEntity::isWireframed() const
{
	return _isWireframed;
}
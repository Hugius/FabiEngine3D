#include "terrain_entity.hpp"

using std::max;
using std::clamp;

Terrain::Terrain(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Terrain::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Terrain::setPixels(const vector<float> & value)
{
	_pixels = value;
}

void Terrain::setHeightMapPath(const string & value)
{
	_heightMapPath = value;
}

void Terrain::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseTextureBuffer = value;
}

void Terrain::setDiffuseMapPath(const string & value)
{
	_diffuseMapPath = value;
}

void Terrain::setNormalMap(shared_ptr<TextureBuffer> value)
{
	_normalTextureBuffer = value;
}

void Terrain::setNormalMapPath(const string & value)
{
	_normalMapPath = value;
}

void Terrain::setBlendMap(shared_ptr<TextureBuffer> value)
{
	_blendTextureBuffer = value;
}

void Terrain::setBlendMapPath(const string & value)
{
	_blendMapPath = value;
}

void Terrain::setRedDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_redDiffuseTextureBuffer = value;
}

void Terrain::setRedDiffuseMapPath(const string & value)
{
	_redDiffuseMapPath = value;
}

void Terrain::setGreenDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_greenDiffuseTextureBuffer = value;
}

void Terrain::setGreenDiffuseMapPath(const string & value)
{
	_greenDiffuseMapPath = value;
}

void Terrain::setBlueDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_blueDiffuseTextureBuffer = value;
}

void Terrain::setBlueDiffuseMapPath(const string & value)
{
	_blueDiffuseMapPath = value;
}

void Terrain::setRedNormalMap(shared_ptr<TextureBuffer> value)
{
	_redNormalTextureBuffer = value;
}

void Terrain::setRedNormalMapPath(const string & value)
{
	_redNormalMapPath = value;
}

void Terrain::setGreenNormalMap(shared_ptr<TextureBuffer> value)
{
	_greenNormalTextureBuffer = value;
}

void Terrain::setGreenNormalMapPath(const string & value)
{
	_greenNormalMapPath = value;
}

void Terrain::setBlueNormalMap(shared_ptr<TextureBuffer> value)
{
	_blueNormalTextureBuffer = value;
}

void Terrain::setBlueNormalMapPath(const string & filePath)
{
	_blueNormalMapPath = filePath;
}

void Terrain::setTextureRepeat(int value)
{
	_textureRepeat = max(1, value);
}

void Terrain::setRedTextureRepeat(int value)
{
	_redTextureRepeat = max(1, value);
}

void Terrain::setGreenTextureRepeat(int value)
{
	_greenTextureRepeat = max(1, value);
}

void Terrain::setBlueTextureRepeat(int value)
{
	_blueTextureRepeat = max(1, value);
}

void Terrain::setSize(float value)
{
	_size = max(0.0f, value);
}

void Terrain::setMaxHeight(float value)
{
	_maxHeight = max(0.0f, value);
}

void Terrain::setSpecular(bool value)
{
	_isSpecular = value;
}

void Terrain::setWireframed(bool value)
{
	_isWireframed = value;
}

void Terrain::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Terrain::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Terrain::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void Terrain::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void Terrain::setVisible(bool value)
{
	_isVisible = value;
}

void Terrain::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void Terrain::setSpecularShininess(float value)
{
	_specularShininess = max(0.0f, value);
}

void Terrain::setSpecularIntensity(float value)
{
	_specularIntensity = max(0.0f, value);
}

const shared_ptr<TextureBuffer> Terrain::getDiffuseTextureBuffer() const
{
	return _diffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getNormalTextureBuffer() const
{
	return _normalTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getBlendTextureBuffer() const
{
	return _blendTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getRedDiffuseTextureBuffer() const
{
	return _redDiffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getGreenDiffuseTextureBuffer() const
{
	return _greenDiffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getBlueDiffuseTextureBuffer() const
{
	return _blueDiffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getRedNormalTextureBuffer() const
{
	return _redNormalTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getGreenNormalTextureBuffer() const
{
	return _greenNormalTextureBuffer;
}

const shared_ptr<TextureBuffer> Terrain::getBlueNormalTextureBuffer() const
{
	return _blueNormalTextureBuffer;
}

const string & Terrain::getHeightMapPath() const
{
	return _heightMapPath;
}

const string & Terrain::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string & Terrain::getNormalMapPath() const
{
	return _normalMapPath;
}

const string & Terrain::getBlendMapPath() const
{
	return _blendMapPath;
}

const string & Terrain::getRedDiffuseMapPath() const
{
	return _redDiffuseMapPath;
}

const string & Terrain::getGreenDiffuseMapPath() const
{
	return _greenDiffuseMapPath;
}

const string & Terrain::getBlueDiffuseMapPath() const
{
	return _blueDiffuseMapPath;
}

const string & Terrain::getRedNormalMapPath() const
{
	return _redNormalMapPath;
}

const string & Terrain::getGreenNormalMapPath() const
{
	return _greenNormalMapPath;
}

const string & Terrain::getBlueNormalMapPath() const
{
	return _blueNormalMapPath;
}

const fvec3 & Terrain::getColor() const
{
	return _color;
}

const fvec3 & Terrain::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Terrain::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Terrain::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const int Terrain::getTextureRepeat() const
{
	return _textureRepeat;
}

const int Terrain::getRedTextureRepeat() const
{
	return _redTextureRepeat;
}

const int Terrain::getGreenTextureRepeat() const
{
	return _greenTextureRepeat;
}

const int Terrain::getBlueTextureRepeat() const
{
	return _blueTextureRepeat;
}

const float Terrain::getSize() const
{
	return _size;
}

const float Terrain::getMaxHeight() const
{
	return _maxHeight;
}

const float Terrain::getLightness() const
{
	return _lightness;
}

const float Terrain::getSpecularShininess() const
{
	return _specularShininess;
}

const float Terrain::getSpecularIntensity() const
{
	return _specularIntensity;
}

const shared_ptr<VertexBuffer> Terrain::getVertexBuffer() const
{
	return _vertexBuffer;
}

const vector<float> & Terrain::getPixels() const
{
	return _pixels;
}

const bool Terrain::isSpecular() const
{
	return _isSpecular;
}

const bool Terrain::isWireframed() const
{
	return _isWireframed;
}
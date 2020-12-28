#include "terrain_entity.hpp"

void TerrainEntity::setPixelColors(const vector<float>& value)
{
	_pixelColors = value;
}

void TerrainEntity::setHeightMapPath(const string& value)
{
	_heightMapPath = value;
}

void TerrainEntity::setDiffuseMap(GLuint value)
{
	_diffuseMap = value;
}

void TerrainEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void TerrainEntity::setNormalMap(GLuint value)
{
	_normalMap = value;
}

void TerrainEntity::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void TerrainEntity::setBlendMap(GLuint value)
{
	_blendMap = value;
}

void TerrainEntity::setBlendMapPath(const string& value)
{
	_blendMapPath = value;
}

void TerrainEntity::setBlendMapR(GLuint value)
{
	_blendMapR = value;
}

void TerrainEntity::setBlendMapPathR(const string& value)
{
	_blendMapPathR = value;
}

void TerrainEntity::setBlendMapG(GLuint value)
{
	_blendMapG = value;
}

void TerrainEntity::setBlendMapPathG(const string& value)
{
	_blendMapPathG = value;
}

void TerrainEntity::setBlendMapB(GLuint value)
{
	_blendMapB = value;
}

void TerrainEntity::setBlendMapPathB(const string& value)
{
	_blendMapPathB = value;
}

void TerrainEntity::setNormalMapR(GLuint value)
{
	_normalMapR = value;
}

void TerrainEntity::setNormalMapPathR(const string& value)
{
	_normalMapPathR = value;
}

void TerrainEntity::setNormalMapG(GLuint value)
{
	_normalMapG = value;
}

void TerrainEntity::setNormalMapPathG(const string& value)
{
	_normalMapPathG = value;
}

void TerrainEntity::setNormalMapB(GLuint value)
{
	_normalMapB = value;
}

void TerrainEntity::setNormalMapPathB(const string& filePath)
{
	_normalMapPathB = filePath;
}

void TerrainEntity::setUvRepeat(float value)
{
	_uvRepeat = value;
}

void TerrainEntity::setBlendRepeatR(float value)
{
	_blendRepeatR = value;
}

void TerrainEntity::setBlendRepeatG(float value)
{
	_blendRepeatG = value;
}

void TerrainEntity::setBlendRepeatB(float value)
{
	_blendRepeatB = value;
}

void TerrainEntity::setSize(float value)
{
	_size = value;
}

void TerrainEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void TerrainEntity::setSpecularLighted(bool value)
{
	_isSpecularLighted = value;
}

void TerrainEntity::setNormalMapped(bool value)
{
	_isNormalMapped = value;
}

void TerrainEntity::setNormalMappedR(bool value)
{
	_isNormalMappedR = value;
}

void TerrainEntity::setNormalMappedG(bool value)
{
	_isNormalMappedG = value;
}

void TerrainEntity::setNormalMappedB(bool value)
{
	_isNormalMappedB = value;
}

void TerrainEntity::setBlendMapped(bool value)
{
	_isBlendMapped = value;
}

void TerrainEntity::setLightness(float value)
{
	_lightness = value;
}

void TerrainEntity::setSpecularLightingFactor(float value)
{
	_specularLightingFactor = value;
}

void TerrainEntity::setSpecularLightingIntensity(float value)
{
	_specularLightingIntensity = value;
}

const GLuint TerrainEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const GLuint TerrainEntity::getNormalMap() const
{
	return _normalMap;
}

const GLuint TerrainEntity::getBlendMap() const
{
	return _blendMap;
}

const GLuint TerrainEntity::getBlendMapR() const
{
	return _blendMapR;
}

const GLuint TerrainEntity::getBlendMapG() const
{
	return _blendMapG;
}

const GLuint TerrainEntity::getBlendMapB() const
{
	return _blendMapB;
}

const GLuint TerrainEntity::getNormalMapR() const
{
	return _normalMapR;
}

const GLuint TerrainEntity::getNormalMapG() const
{
	return _normalMapG;
}

const GLuint TerrainEntity::getNormalMapB() const
{
	return _normalMapB;
}

const string& TerrainEntity::getHeightMapPath() const
{
	return _heightMapPath;
}

const string& TerrainEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& TerrainEntity::getNormalMapPath() const
{
	return _normalMapPath;
}

const string& TerrainEntity::getBlendMapPath() const
{
	return _blendMapPath;
}

const string& TerrainEntity::getBlendMapPathR() const
{
	return _blendMapPathR;
}

const string& TerrainEntity::getBlendMapPathG() const
{
	return _blendMapPathG;
}

const string& TerrainEntity::getBlendMapPathB() const
{
	return _blendMapPathB;
}

const string& TerrainEntity::getNormalMapPathR() const
{
	return _normalMapPathR;
}

const string& TerrainEntity::getNormalMapPathG() const
{
	return _normalMapPathG;
}

const string& TerrainEntity::getNormalMapPathB() const
{
	return _normalMapPathB;
}

vector<Vec3>& TerrainEntity::getVertices()
{
	return _vertices;
}

vector<Vec2>& TerrainEntity::getUvCoords()
{
	return _uvCoords;
}

vector<Vec3>& TerrainEntity::getNormals()
{
	return _normals;
}

const float TerrainEntity::getUvRepeat() const
{
	return _uvRepeat;
}

const float TerrainEntity::getBlendRepeatR() const
{
	return _blendRepeatR;
}

const float TerrainEntity::getBlendRepeatG() const
{
	return _blendRepeatG;
}

const float TerrainEntity::getBlendRepeatB() const
{
	return _blendRepeatB;
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

const float TerrainEntity::getSpecularLightingFactor() const
{
	return _specularLightingFactor;
}

const float TerrainEntity::getSpecularLightingIntensity() const
{
	return _specularLightingIntensity;
}

const vector<float>& TerrainEntity::getPixelColors() const
{
	return _pixelColors;
}

const bool TerrainEntity::isSpecularLighted() const
{
	return _isSpecularLighted;
}

const bool TerrainEntity::isNormalMapped() const
{
	return _isNormalMapped;
}

const bool TerrainEntity::isNormalMappedR() const
{
	return _isNormalMappedR;
}

const bool TerrainEntity::isNormalMappedG() const
{
	return _isNormalMappedG;
}

const bool TerrainEntity::isNormalMappedB() const
{
	return _isNormalMappedB;
}

const bool TerrainEntity::isBlendMapped() const
{
	return _isBlendMapped;
}
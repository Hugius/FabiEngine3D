#include "terrain_entity.hpp"

void TerrainEntity::setPixelValues(const vector<float>& value)
{
	_pixelValues = value;
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

void TerrainEntity::setDiffuseMapR(GLuint value)
{
	_diffuseMapR = value;
}

void TerrainEntity::setDiffuseMapPathR(const string& value)
{
	_diffuseMapPathR = value;
}

void TerrainEntity::setDiffuseMapG(GLuint value)
{
	_diffuseMapG = value;
}

void TerrainEntity::setDiffuseMapPathG(const string& value)
{
	_diffuseMapPathG = value;
}

void TerrainEntity::setDiffuseMapB(GLuint value)
{
	_diffuseMapB = value;
}

void TerrainEntity::setDiffuseMapPathB(const string& value)
{
	_diffuseMapPathB = value;
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
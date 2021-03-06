#include "terrain_entity.hpp"

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

const GLuint TerrainEntity::getDiffuseMapR() const
{
	return _diffuseMapR;
}

const GLuint TerrainEntity::getDiffuseMapG() const
{
	return _diffuseMapG;
}

const GLuint TerrainEntity::getDiffuseMapB() const
{
	return _diffuseMapB;
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

const string& TerrainEntity::getDiffuseMapPathR() const
{
	return _diffuseMapPathR;
}

const string& TerrainEntity::getDiffuseMapPathG() const
{
	return _diffuseMapPathG;
}

const string& TerrainEntity::getDiffuseMapPathB() const
{
	return _diffuseMapPathB;
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

const vector<float>& TerrainEntity::getPixelValues() const
{
	return _pixelValues;
}

const bool TerrainEntity::isSpecularLighted() const
{
	return _isSpecularLighted;
}

const bool TerrainEntity::hasDiffuseMap() const
{
	return (_diffuseMap != 0);
}

const bool TerrainEntity::hasNormalMap() const
{
	return (_normalMap != 0);
}

const bool TerrainEntity::hasBlendMap() const
{
	return (_blendMap != 0);
}

const bool TerrainEntity::hasDiffuseMapR() const
{
	return (_diffuseMapR != 0);
}

const bool TerrainEntity::hasDiffuseMapG() const
{
	return (_diffuseMapG != 0);
}

const bool TerrainEntity::hasDiffuseMapB() const
{
	return (_diffuseMapB != 0);
}

const bool TerrainEntity::hasNormalMapR() const
{
	return (_normalMapR != 0);
}

const bool TerrainEntity::hasNormalMapG() const
{
	return (_normalMapG != 0);
}

const bool TerrainEntity::hasNormalMapB() const
{
	return (_normalMapB != 0);
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
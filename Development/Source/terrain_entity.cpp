#include "terrain_entity.hpp"

void TerrainEntity::setPixelColors(vector<float>& val)
{
	_pixelColors = val;
}

void TerrainEntity::setHeightMapPath(const string& path)
{
	_heightMapPath = path;
}

void TerrainEntity::setDiffuseMap(GLuint val)
{
	_diffuseMap = val;
}

void TerrainEntity::setDiffuseMapPath(const string& path)
{
	_diffuseMapPath = path;
}

void TerrainEntity::setBlendMap(GLuint val)
{
	_blendMap = val;
}

void TerrainEntity::setBlendMapPath(const string& path)
{
	_blendMapPath = path;
}

void TerrainEntity::setBlendMapR(GLuint val)
{
	_blendMapR = val;
}

void TerrainEntity::setBlendMapPathR(const string& path)
{
	_blendMapPathR = path;
}

void TerrainEntity::setBlendMapG(GLuint val)
{
	_blendMapG = val;
}

void TerrainEntity::setBlendMapPathG(const string& path)
{
	_blendMapPathG = path;
}

void TerrainEntity::setBlendMapB(GLuint val)
{
	_blendMapB = val;
}

void TerrainEntity::setBlendMapPathB(const string& path)
{
	_blendMapPathB = path;
}

void TerrainEntity::setUvRepeat(float val)
{
	_uvRepeat = val;
}

void TerrainEntity::setBlendRepeatR(float val)
{
	_blendRepeatR = val;
}

void TerrainEntity::setBlendRepeatG(float val)
{
	_blendRepeatG = val;
}

void TerrainEntity::setBlendRepeatB(float val)
{
	_blendRepeatB = val;
}

void TerrainEntity::setSize(float val)
{
	_size = val;
}

void TerrainEntity::setMaxHeight(float val)
{
	_maxHeight = val;
}

void TerrainEntity::setBlendMapped(bool val)
{
	_isBlendMapped = val;
}

void TerrainEntity::setLightness(float val)
{
	_lightness = val;
}

const GLuint TerrainEntity::getDiffuseMap() const
{
	return _diffuseMap;
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

const string& TerrainEntity::getHeightMapPath() const
{
	return _heightMapPath;
}

const string& TerrainEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
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

const vector<float>& TerrainEntity::getPixelColors() const
{
	return _pixelColors;
}

const bool TerrainEntity::isBlendMapped() const
{
	return _isBlendMapped;
}
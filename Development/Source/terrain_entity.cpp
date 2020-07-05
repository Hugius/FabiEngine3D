#include "terrain_entity.hpp"

void TerrainEntity::setPixelColors(vector<float>& val)
{
	_pixelColors = val;
}

void TerrainEntity::setDiffuseMap(GLuint val)
{
	_diffuseMap = val;
}

void TerrainEntity::setBlendMap(GLuint val)
{
	_blendMap = val;
}

void TerrainEntity::setBlendMapR(GLuint val)
{
	_blendMapR = val;
}

void TerrainEntity::setBlendMapG(GLuint val)
{
	_blendMapG = val;
}

void TerrainEntity::setBlendMapB(GLuint val)
{
	_blendMapB = val;
}

void TerrainEntity::setBlendRepeat(float val)
{
	_blendRepeat = val;
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
	_blendMapped = val;
}

void TerrainEntity::setBrightness(float val)
{
	_brightness = val;
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

const float TerrainEntity::getBlendRepeat() const
{
	return _blendRepeat;
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

const float TerrainEntity::getBrightness() const
{
	return _brightness;
}

const vector<float>& TerrainEntity::getPixelColors() const
{
	return _pixelColors;
}

const bool TerrainEntity::isBlendMapped() const
{
	return _blendMapped;
}
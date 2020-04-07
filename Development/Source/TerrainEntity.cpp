#include <WE3D/TerrainEntity.hpp>

void TerrainEntity::setPixelColors(vector<float>& val)
{
	p_pixelColors = val;
}

void TerrainEntity::setDiffuseMap(GLuint val)
{
	p_diffuseMap = val;
}

void TerrainEntity::setBlendMap(GLuint val)
{
	p_blendMap = val;
}

void TerrainEntity::setBlendMapR(GLuint val)
{
	p_blendMapR = val;
}

void TerrainEntity::setBlendMapG(GLuint val)
{
	p_blendMapG = val;
}

void TerrainEntity::setBlendMapB(GLuint val)
{
	p_blendMapB = val;
}

void TerrainEntity::setBlendRepeat(float val)
{
	p_blendRepeat = val;
}

void TerrainEntity::setBlendRepeatR(float val)
{
	p_blendRepeatR = val;
}

void TerrainEntity::setBlendRepeatG(float val)
{
	p_blendRepeatG = val;
}

void TerrainEntity::setBlendRepeatB(float val)
{
	p_blendRepeatB = val;
}

void TerrainEntity::setSize(float val)
{
	p_size = val;
}

void TerrainEntity::setHeight(float val)
{
	p_height = val;
}

void TerrainEntity::setBlendMapped(bool val)
{
	p_blendMapped = val;
}

const GLuint TerrainEntity::getDiffuseMap() const
{
	return p_diffuseMap;
}

const GLuint TerrainEntity::getBlendMap() const
{
	return p_blendMap;
}

const GLuint TerrainEntity::getBlendMapR() const
{
	return p_blendMapR;
}

const GLuint TerrainEntity::getBlendMapG() const
{
	return p_blendMapG;
}

const GLuint TerrainEntity::getBlendMapB() const
{
	return p_blendMapB;
}

const float TerrainEntity::getBlendRepeat() const
{
	return p_blendRepeat;
}

const float TerrainEntity::getBlendRepeatR() const
{
	return p_blendRepeatR;
}

const float TerrainEntity::getBlendRepeatG() const
{
	return p_blendRepeatG;
}

const float TerrainEntity::getBlendRepeatB() const
{
	return p_blendRepeatB;
}

const float TerrainEntity::getSize() const
{
	return p_size;
}

const float TerrainEntity::getHeight() const
{
	return p_height;
}

const vector<float>& TerrainEntity::getPixelColors() const
{
	return p_pixelColors;
}

const bool TerrainEntity::isBlendMapped() const
{
	return p_blendMapped;
}
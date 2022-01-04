#include "terrain_entity.hpp"

const shared_ptr<TextureBuffer> TerrainEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getNormalMap() const
{
	return _normalMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getBlendMap() const
{
	return _blendMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getRedDiffuseMap() const
{
	return _redDiffuseMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getGreenDiffuseMap() const
{
	return _greenDiffuseMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getBlueDiffuseMap() const
{
	return _blueDiffuseMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getRedNormalMap() const
{
	return _redNormalMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getGreenNormalMap() const
{
	return _greenNormalMap;
}

const shared_ptr<TextureBuffer> TerrainEntity::getBlueNormalMap() const
{
	return _blueNormalMap;
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

const string& TerrainEntity::getRedDiffuseMapPath() const
{
	return _redDiffuseMapPath;
}

const string& TerrainEntity::getGreenDiffuseMapPath() const
{
	return _greenDiffuseMapPath;
}

const string& TerrainEntity::getBlueDiffuseMapPath() const
{
	return _blueDiffuseMapPath;
}

const string& TerrainEntity::getRedNormalMapPath() const
{
	return _redNormalMapPath;
}

const string& TerrainEntity::getGreenNormalMapPath() const
{
	return _greenNormalMapPath;
}

const string& TerrainEntity::getBlueNormalMapPath() const
{
	return _blueNormalMapPath;
}

const fvec3 TerrainEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const float TerrainEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const float TerrainEntity::getRedTextureRepeat() const
{
	return _redTextureRepeat;
}

const float TerrainEntity::getGreenTextureRepeat() const
{
	return _greenTextureRepeat;
}

const float TerrainEntity::getBlueTextureRepeat() const
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

const shared_ptr<VertexBuffer> TerrainEntity::getMesh() const
{
	return _mesh;
}

const vector<float>& TerrainEntity::getPixels() const
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

const bool TerrainEntity::hasVertexBuffer() const
{
	return (_mesh != nullptr);
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

const bool TerrainEntity::hasRedDiffuseMap() const
{
	return (_redDiffuseMap != 0);
}

const bool TerrainEntity::hasGreenDiffuseMap() const
{
	return (_greenDiffuseMap != 0);
}

const bool TerrainEntity::hasBlueDiffuseMap() const
{
	return (_blueDiffuseMap != 0);
}

const bool TerrainEntity::hasRedNormalMap() const
{
	return (_redNormalMap != 0);
}

const bool TerrainEntity::hasGreenNormalMap() const
{
	return (_greenNormalMap != 0);
}

const bool TerrainEntity::hasBlueNormalMap() const
{
	return (_blueNormalMap != 0);
}
#include "terrain_entity.hpp"

const TextureID TerrainEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const TextureID TerrainEntity::getNormalMap() const
{
	return _normalMap;
}

const TextureID TerrainEntity::getBlendMap() const
{
	return _blendMap;
}

const TextureID TerrainEntity::getDiffuseMapR() const
{
	return _diffuseMapR;
}

const TextureID TerrainEntity::getDiffuseMapG() const
{
	return _diffuseMapG;
}

const TextureID TerrainEntity::getDiffuseMapB() const
{
	return _diffuseMapB;
}

const TextureID TerrainEntity::getNormalMapR() const
{
	return _normalMapR;
}

const TextureID TerrainEntity::getNormalMapG() const
{
	return _normalMapG;
}

const TextureID TerrainEntity::getNormalMapB() const
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

const vector<fvec3>& TerrainEntity::getVertices() const
{
	return _vertices;
}

const vector<fvec2>& TerrainEntity::getUvCoords() const
{
	return _uvCoords;
}

const fvec3 TerrainEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const vector<fvec3>& TerrainEntity::getNormals() const
{
	return _normals;
}

const float TerrainEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const float TerrainEntity::getRedRepeat() const
{
	return _redRepeat;
}

const float TerrainEntity::getGreenRepeat() const
{
	return _greenRepeat;
}

const float TerrainEntity::getBlueRepeat() const
{
	return _blueRepeat;
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

const shared_ptr<RenderBuffer> TerrainEntity::getRenderBuffer() const
{
	return _renderBuffer;
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

const bool TerrainEntity::hasRenderBuffer() const
{
	return (_renderBuffer != nullptr);
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
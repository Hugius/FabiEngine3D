#include "terrain_entity.hpp"

const TextureID TerrainEntity::getDiffuseMap()
{
	return _diffuseMap;
}

const TextureID TerrainEntity::getNormalMap()
{
	return _normalMap;
}

const TextureID TerrainEntity::getBlendMap()
{
	return _blendMap;
}

const TextureID TerrainEntity::getDiffuseMapR()
{
	return _diffuseMapR;
}

const TextureID TerrainEntity::getDiffuseMapG()
{
	return _diffuseMapG;
}

const TextureID TerrainEntity::getDiffuseMapB()
{
	return _diffuseMapB;
}

const TextureID TerrainEntity::getNormalMapR()
{
	return _normalMapR;
}

const TextureID TerrainEntity::getNormalMapG()
{
	return _normalMapG;
}

const TextureID TerrainEntity::getNormalMapB()
{
	return _normalMapB;
}

const string& TerrainEntity::getHeightMapPath()
{
	return _heightMapPath;
}

const string& TerrainEntity::getDiffuseMapPath()
{
	return _diffuseMapPath;
}

const string& TerrainEntity::getNormalMapPath()
{
	return _normalMapPath;
}

const string& TerrainEntity::getBlendMapPath()
{
	return _blendMapPath;
}

const string& TerrainEntity::getDiffuseMapPathR()
{
	return _diffuseMapPathR;
}

const string& TerrainEntity::getDiffuseMapPathG()
{
	return _diffuseMapPathG;
}

const string& TerrainEntity::getDiffuseMapPathB()
{
	return _diffuseMapPathB;
}

const string& TerrainEntity::getNormalMapPathR()
{
	return _normalMapPathR;
}

const string& TerrainEntity::getNormalMapPathG()
{
	return _normalMapPathG;
}

const string& TerrainEntity::getNormalMapPathB()
{
	return _normalMapPathB;
}

const vector<Vec3>& TerrainEntity::getVertices()
{
	return _vertices;
}

const vector<Vec2>& TerrainEntity::getUvCoords()
{
	return _uvCoords;
}

const vector<Vec3>& TerrainEntity::getNormals()
{
	return _normals;
}

const float TerrainEntity::getUvRepeat()
{
	return _uvRepeat;
}

const float TerrainEntity::getBlendRepeatR()
{
	return _blendRepeatR;
}

const float TerrainEntity::getBlendRepeatG()
{
	return _blendRepeatG;
}

const float TerrainEntity::getBlendRepeatB()
{
	return _blendRepeatB;
}

const float TerrainEntity::getSize()
{
	return _size;
}

const float TerrainEntity::getMaxHeight()
{
	return _maxHeight;
}

const float TerrainEntity::getLightness()
{
	return _lightness;
}

const float TerrainEntity::getSpecularLightingFactor()
{
	return _specularLightingFactor;
}

const float TerrainEntity::getSpecularLightingIntensity()
{
	return _specularLightingIntensity;
}

const shared_ptr<RenderBuffer> TerrainEntity::getRenderBuffer()
{
	return _renderBuffer;
}

const vector<float>& TerrainEntity::getPixelValues()
{
	return _pixelValues;
}

const bool TerrainEntity::isVisible()
{
	return _isVisible;
}

const bool TerrainEntity::isSpecularLighted()
{
	return _isSpecularLighted;
}

const bool TerrainEntity::isWireFramed()
{
	return _isWireFramed;
}

const bool TerrainEntity::hasRenderBuffer()
{
	return (_renderBuffer != nullptr);
}

const bool TerrainEntity::hasDiffuseMap()
{
	return (_diffuseMap != 0);
}

const bool TerrainEntity::hasNormalMap()
{
	return (_normalMap != 0);
}

const bool TerrainEntity::hasBlendMap()
{
	return (_blendMap != 0);
}

const bool TerrainEntity::hasDiffuseMapR()
{
	return (_diffuseMapR != 0);
}

const bool TerrainEntity::hasDiffuseMapG()
{
	return (_diffuseMapG != 0);
}

const bool TerrainEntity::hasDiffuseMapB()
{
	return (_diffuseMapB != 0);
}

const bool TerrainEntity::hasNormalMapR()
{
	return (_normalMapR != 0);
}

const bool TerrainEntity::hasNormalMapG()
{
	return (_normalMapG != 0);
}

const bool TerrainEntity::hasNormalMapB()
{
	return (_normalMapB != 0);
}
#include "terrain_entity.hpp"

using std::max;

void TerrainEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void TerrainEntity::setPixelValues(const vector<float>& value)
{
	_pixelValues = value;
}

void TerrainEntity::setVertices(const vector<Vec3> value)
{
	_vertices = value;
}

void TerrainEntity::setUvCoords(const vector<Vec2> value)
{
	_uvCoords = value;
}

void TerrainEntity::setNormals(const vector<Vec3> value)
{
	_normals = value;
}

void TerrainEntity::setHeightMapPath(const string& value)
{
	_heightMapPath = value;
}

void TerrainEntity::setDiffuseMap(TextureID value)
{
	_diffuseMap = value;
}

void TerrainEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void TerrainEntity::setNormalMap(TextureID value)
{
	_normalMap = value;
}

void TerrainEntity::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void TerrainEntity::setBlendMap(TextureID value)
{
	_blendMap = value;
}

void TerrainEntity::setBlendMapPath(const string& value)
{
	_blendMapPath = value;
}

void TerrainEntity::setDiffuseMapR(TextureID value)
{
	_diffuseMapR = value;
}

void TerrainEntity::setDiffuseMapPathR(const string& value)
{
	_diffuseMapPathR = value;
}

void TerrainEntity::setDiffuseMapG(TextureID value)
{
	_diffuseMapG = value;
}

void TerrainEntity::setDiffuseMapPathG(const string& value)
{
	_diffuseMapPathG = value;
}

void TerrainEntity::setDiffuseMapB(TextureID value)
{
	_diffuseMapB = value;
}

void TerrainEntity::setDiffuseMapPathB(const string& value)
{
	_diffuseMapPathB = value;
}

void TerrainEntity::setNormalMapR(TextureID value)
{
	_normalMapR = value;
}

void TerrainEntity::setNormalMapPathR(const string& value)
{
	_normalMapPathR = value;
}

void TerrainEntity::setNormalMapG(TextureID value)
{
	_normalMapG = value;
}

void TerrainEntity::setNormalMapPathG(const string& value)
{
	_normalMapPathG = value;
}

void TerrainEntity::setNormalMapB(TextureID value)
{
	_normalMapB = value;
}

void TerrainEntity::setNormalMapPathB(const string& filePath)
{
	_normalMapPathB = filePath;
}

void TerrainEntity::setUvRepeat(float value)
{
	_uvRepeat = max(0.0f, value);
}

void TerrainEntity::setBlendRepeatR(float value)
{
	_blendRepeatR = max(0.0f, value);
}

void TerrainEntity::setBlendRepeatG(float value)
{
	_blendRepeatG = max(0.0f, value);
}

void TerrainEntity::setBlendRepeatB(float value)
{
	_blendRepeatB = max(0.0f, value);
}

void TerrainEntity::setSize(float value)
{
	_size = max(0.0f, value);
}

void TerrainEntity::setMaxHeight(float value)
{
	_maxHeight = max(0.0f, value);
}

void TerrainEntity::setSpecular(bool value)
{
	_isSpecular = value;
}

void TerrainEntity::setWireFramed(bool value)
{
	_isWireFramed = value;
}

void TerrainEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void TerrainEntity::setSpecularShininess(float value)
{
	_specularShininess = max(0.0f, value);
}

void TerrainEntity::setSpecularIntensity(float value)
{
	_specularIntensity = max(0.0f, value);
}
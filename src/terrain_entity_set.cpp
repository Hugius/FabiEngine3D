#include "terrain_entity.hpp"

using std::max;
using std::clamp;

TerrainEntity::TerrainEntity(const string& ID, const string& heightMapPath)
	:
	BaseEntity(ID),
	_heightMapPath(heightMapPath)
{

}

void TerrainEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void TerrainEntity::setPixels(const vector<float>& value)
{
	_pixels = value;
}

void TerrainEntity::setVertices(const vector<fvec3> value)
{
	_vertices = value;
}

void TerrainEntity::setUvCoords(const vector<fvec2> value)
{
	_uvCoords = value;
}

void TerrainEntity::setNormals(const vector<fvec3> value)
{
	_normals = value;
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

void TerrainEntity::setRedDiffuseMap(TextureID value)
{
	_redDiffuseMap = value;
}

void TerrainEntity::setRedDiffuseMapPath(const string& value)
{
	_redDiffuseMapPath = value;
}

void TerrainEntity::setGreenDiffuseMap(TextureID value)
{
	_greenDiffuseMap = value;
}

void TerrainEntity::setGreenDiffuseMapPath(const string& value)
{
	_greenDiffuseMapPath = value;
}

void TerrainEntity::setBlueDiffuseMap(TextureID value)
{
	_blueDiffuseMap = value;
}

void TerrainEntity::setBlueDiffuseMapPath(const string& value)
{
	_blueDiffuseMapPath = value;
}

void TerrainEntity::setRedNormalMap(TextureID value)
{
	_redNormalMap = value;
}

void TerrainEntity::setRedNormalMapPath(const string& value)
{
	_redNormalMapPath = value;
}

void TerrainEntity::setGreenNormalMap(TextureID value)
{
	_greenNormalMap = value;
}

void TerrainEntity::setGreenNormalMapPath(const string& value)
{
	_greenNormalMapPath = value;
}

void TerrainEntity::setBlueNormalMap(TextureID value)
{
	_blueNormalMap = value;
}

void TerrainEntity::setBlueNormalMapPath(const string& filePath)
{
	_blueNormalMapPath = filePath;
}

void TerrainEntity::setTextureRepeat(float value)
{
	_textureRepeat = max(0.0f, value);
}

void TerrainEntity::setRedTextureRepeat(float value)
{
	_redTextureRepeat = max(0.0f, value);
}

void TerrainEntity::setGreenTextureRepeat(float value)
{
	_greenTextureRepeat = max(0.0f, value);
}

void TerrainEntity::setBlueTextureRepeat(float value)
{
	_blueTextureRepeat = max(0.0f, value);
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

void TerrainEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void TerrainEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
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
#include "terrain_entity.hpp"

using std::max;
using std::clamp;

void TerrainEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void TerrainEntity::setPixels(const vector<float>& value)
{
	_pixels = value;
}

void TerrainEntity::setHeightMapPath(const string& value)
{
	_heightMapPath = value;
}

void TerrainEntity::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseMap = value;
}

void TerrainEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void TerrainEntity::setNormalMap(shared_ptr<TextureBuffer> value)
{
	_normalMap = value;
}

void TerrainEntity::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void TerrainEntity::setBlendMap(shared_ptr<TextureBuffer> value)
{
	_blendMap = value;
}

void TerrainEntity::setBlendMapPath(const string& value)
{
	_blendMapPath = value;
}

void TerrainEntity::setRedDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_redDiffuseMap = value;
}

void TerrainEntity::setRedDiffuseMapPath(const string& value)
{
	_redDiffuseMapPath = value;
}

void TerrainEntity::setGreenDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_greenDiffuseMap = value;
}

void TerrainEntity::setGreenDiffuseMapPath(const string& value)
{
	_greenDiffuseMapPath = value;
}

void TerrainEntity::setBlueDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_blueDiffuseMap = value;
}

void TerrainEntity::setBlueDiffuseMapPath(const string& value)
{
	_blueDiffuseMapPath = value;
}

void TerrainEntity::setRedNormalMap(shared_ptr<TextureBuffer> value)
{
	_redNormalMap = value;
}

void TerrainEntity::setRedNormalMapPath(const string& value)
{
	_redNormalMapPath = value;
}

void TerrainEntity::setGreenNormalMap(shared_ptr<TextureBuffer> value)
{
	_greenNormalMap = value;
}

void TerrainEntity::setGreenNormalMapPath(const string& value)
{
	_greenNormalMapPath = value;
}

void TerrainEntity::setBlueNormalMap(shared_ptr<TextureBuffer> value)
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
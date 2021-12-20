#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TerrainEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// VOID
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setPixels(const vector<float>& value);
	void setVertices(const vector<fvec3> value);
	void setNormals(const vector<fvec3> value);
	void setUvCoords(const vector<fvec2> value);
	void setHeightMapPath(const string& value);
	void setDiffuseMap(TextureID value);
	void setDiffuseMapPath(const string& value);
	void setNormalMap(TextureID value);
	void setNormalMapPath(const string& value);
	void setBlendMap(TextureID value);
	void setBlendMapPath(const string& value);
	void setRedDiffuseMap(TextureID value);
	void setRedDiffuseMapPath(const string& value);
	void setGreenDiffuseMap(TextureID value);
	void setGreenDiffuseMapPath(const string& value);
	void setBlueDiffuseMap(TextureID value);
	void setBlueDiffuseMapPath(const string& value);
	void setRedNormalMap(TextureID value);
	void setRedNormalMapPath(const string& value);
	void setGreenNormalMap(TextureID value);
	void setGreenNormalMapPath(const string& value);
	void setBlueNormalMap(TextureID value);
	void setBlueNormalMapPath(const string& value);
	void setTextureRepeat(float value);
	void setRedTextureRepeat(float value);
	void setGreenTextureRepeat(float value);
	void setBlueTextureRepeat(float value);
	void setSize(float value);
	void setMaxHeight(float value);
	void setLightness(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setSpecular(bool value);
	void setWireframed(bool value);
	void setWireframeColor(fvec3 value);

	// STRING
	const string& getHeightMapPath() const;
	const string& getDiffuseMapPath() const;
	const string& getNormalMapPath() const;
	const string& getBlendMapPath() const;
	const string& getRedDiffuseMapPath() const;
	const string& getGreenDiffuseMapPath() const;
	const string& getBlueDiffuseMapPath() const;
	const string& getRedNormalMapPath() const;
	const string& getGreenNormalMapPath() const;
	const string& getBlueNormalMapPath() const;

	// FVEC3
	const vector<fvec3>& getVertices() const;
	const vector<fvec3>& getNormals() const;
	const fvec3 getWireframeColor() const;

	// FVEC2
	const vector<fvec2>& getUvCoords() const;

	// FLOAT
	const vector<float>& getPixels() const;
	const float getTextureRepeat() const;
	const float getRedTextureRepeat() const;
	const float getGreenTextureRepeat() const;
	const float getBlueTextureRepeat() const;
	const float getSize() const;
	const float getMaxHeight() const;
	const float getLightness() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;

	// BOOL
	const bool isSpecular() const;
	const bool isWireframed() const;
	const bool hasRenderBuffer() const;
	const bool hasDiffuseMap() const;
	const bool hasNormalMap() const;
	const bool hasBlendMap() const;
	const bool hasRedDiffuseMap() const;
	const bool hasGreenDiffuseMap() const;
	const bool hasBlueDiffuseMap() const;
	const bool hasRedNormalMap() const;
	const bool hasGreenNormalMap() const;
	const bool hasBlueNormalMap() const;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getDiffuseMap() const;
	const TextureID getNormalMap() const;
	const TextureID getBlendMap() const;
	const TextureID getRedDiffuseMap() const;
	const TextureID getGreenDiffuseMap() const;
	const TextureID getBlueDiffuseMap() const;
	const TextureID getRedNormalMap() const;
	const TextureID getGreenNormalMap() const;
	const TextureID getBlueNormalMap() const;

private:
	// STRING
	string _heightMapPath = "";
	string _diffuseMapPath = "";
	string _normalMapPath = "";
	string _blendMapPath = "";
	string _redDiffuseMapPath = "";
	string _greenDiffuseMapPath = "";
	string _blueDiffuseMapPath = "";
	string _redNormalMapPath = "";
	string _greenNormalMapPath = "";
	string _blueNormalMapPath = "";

	// FVEC3
	vector<fvec3> _vertices;
	vector<fvec3> _normals;
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	// FVEC2
	vector<fvec2> _uvCoords;

	// FLOAT
	vector<float> _pixels;
	float _redTextureRepeat = 1.0f;
	float _greenTextureRepeat = 1.0f;
	float _blueTextureRepeat = 1.0f;
	float _textureRepeat = 1.0f;
	float _maxHeight = 1.0f;
	float _size = 0.0f;
	float _lightness = 1.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;

	// BOOL
	bool _isSpecular = false;
	bool _isWireframed = false;

	// MISCELLANEOUS
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
	TextureID _normalMap = 0;
	TextureID _blendMap = 0;
	TextureID _redDiffuseMap = 0;
	TextureID _greenDiffuseMap = 0;
	TextureID _blueDiffuseMap = 0;
	TextureID _redNormalMap = 0;
	TextureID _greenNormalMap = 0;
	TextureID _blueNormalMap = 0;
};
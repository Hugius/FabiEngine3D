#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TerrainEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setMesh(shared_ptr<VertexBuffer> value);
	void setPixels(const vector<float>& value);
	void setHeightMapPath(const string& value);
	void setDiffuseMap(shared_ptr<TextureBuffer> value);
	void setDiffuseMapPath(const string& value);
	void setNormalMap(shared_ptr<TextureBuffer> value);
	void setNormalMapPath(const string& value);
	void setBlendMap(shared_ptr<TextureBuffer> value);
	void setBlendMapPath(const string& value);
	void setRedDiffuseMap(shared_ptr<TextureBuffer> value);
	void setRedDiffuseMapPath(const string& value);
	void setGreenDiffuseMap(shared_ptr<TextureBuffer> value);
	void setGreenDiffuseMapPath(const string& value);
	void setBlueDiffuseMap(shared_ptr<TextureBuffer> value);
	void setBlueDiffuseMapPath(const string& value);
	void setRedNormalMap(shared_ptr<TextureBuffer> value);
	void setRedNormalMapPath(const string& value);
	void setGreenNormalMap(shared_ptr<TextureBuffer> value);
	void setGreenNormalMapPath(const string& value);
	void setBlueNormalMap(shared_ptr<TextureBuffer> value);
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

	const fvec3 getWireframeColor() const;

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

	const bool isSpecular() const;
	const bool isWireframed() const;
	const bool hasDiffuseMap() const;
	const bool hasNormalMap() const;
	const bool hasBlendMap() const;
	const bool hasRedDiffuseMap() const;
	const bool hasGreenDiffuseMap() const;
	const bool hasBlueDiffuseMap() const;
	const bool hasRedNormalMap() const;
	const bool hasGreenNormalMap() const;
	const bool hasBlueNormalMap() const;

	const shared_ptr<VertexBuffer> getMesh() const;
	const shared_ptr<TextureBuffer> getDiffuseMap() const;
	const shared_ptr<TextureBuffer> getNormalMap() const;
	const shared_ptr<TextureBuffer> getBlendMap() const;
	const shared_ptr<TextureBuffer> getRedDiffuseMap() const;
	const shared_ptr<TextureBuffer> getGreenDiffuseMap() const;
	const shared_ptr<TextureBuffer> getBlueDiffuseMap() const;
	const shared_ptr<TextureBuffer> getRedNormalMap() const;
	const shared_ptr<TextureBuffer> getGreenNormalMap() const;
	const shared_ptr<TextureBuffer> getBlueNormalMap() const;

private:
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

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

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

	bool _isSpecular = false;
	bool _isWireframed = false;

	shared_ptr<VertexBuffer> _mesh = nullptr;
	shared_ptr<TextureBuffer> _diffuseMap = nullptr;
	shared_ptr<TextureBuffer> _normalMap = nullptr;
	shared_ptr<TextureBuffer> _blendMap = nullptr;
	shared_ptr<TextureBuffer> _redDiffuseMap = nullptr;
	shared_ptr<TextureBuffer> _greenDiffuseMap = nullptr;
	shared_ptr<TextureBuffer> _blueDiffuseMap = nullptr;
	shared_ptr<TextureBuffer> _redNormalMap = nullptr;
	shared_ptr<TextureBuffer> _greenNormalMap = nullptr;
	shared_ptr<TextureBuffer> _blueNormalMap = nullptr;
};
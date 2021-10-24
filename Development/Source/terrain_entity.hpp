#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TerrainEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setPixelValues(const vector<float>& value);
	void setVertices(const vector<Vec3> value);
	void setNormals(const vector<Vec3> value);
	void setUvCoords(const vector<Vec2> value);
	void setHeightMapPath(const string& value);
	void setDiffuseMap(TextureID value);
	void setDiffuseMapPath(const string& value);
	void setNormalMap(TextureID value);
	void setNormalMapPath(const string& value);
	void setBlendMap(TextureID value);
	void setBlendMapPath(const string& value);
	void setDiffuseMapR(TextureID value);
	void setDiffuseMapPathR(const string& value);
	void setDiffuseMapG(TextureID value);
	void setDiffuseMapPathG(const string& value);
	void setDiffuseMapB(TextureID value);
	void setDiffuseMapPathB(const string& value);
	void setNormalMapR(TextureID value);
	void setNormalMapPathR(const string& value);
	void setNormalMapG(TextureID value);
	void setNormalMapPathG(const string& value);
	void setNormalMapB(TextureID value);
	void setNormalMapPathB(const string& value);
	void setTextureRepeat(float value);
	void setRedRepeat(float value);
	void setGreenRepeat(float value);
	void setBlueRepeat(float value);
	void setSize(float value);
	void setMaxHeight(float value);
	void setLightness(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setSpecular(bool value);
	void setWireFramed(bool value);

	// Strings
	const string& getHeightMapPath();
	const string& getDiffuseMapPath();
	const string& getNormalMapPath();
	const string& getBlendMapPath();
	const string& getDiffuseMapPathR();
	const string& getDiffuseMapPathG();
	const string& getDiffuseMapPathB();
	const string& getNormalMapPathR();
	const string& getNormalMapPathG();
	const string& getNormalMapPathB();

	// Vectors
	const vector<Vec3>& getVertices();
	const vector<Vec3>& getNormals();
	const vector<Vec2>& getUvCoords();

	// Decimals
	const vector<float>& getPixelValues();
	const float getTextureRepeat();
	const float getRedRepeat();
	const float getGreenRepeat();
	const float getBlueRepeat();
	const float getSize();
	const float getMaxHeight();
	const float getLightness();
	const float getSpecularShininess();
	const float getSpecularIntensity();

	// Booleans
	const bool isSpecular();
	const bool isWireFramed();
	const bool hasRenderBuffer();
	const bool hasDiffuseMap();
	const bool hasNormalMap();
	const bool hasBlendMap();
	const bool hasDiffuseMapR();
	const bool hasDiffuseMapG();
	const bool hasDiffuseMapB();
	const bool hasNormalMapR();
	const bool hasNormalMapG();
	const bool hasNormalMapB();

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer();
	const TextureID getDiffuseMap();
	const TextureID getNormalMap();
	const TextureID getBlendMap();
	const TextureID getDiffuseMapR();
	const TextureID getDiffuseMapG();
	const TextureID getDiffuseMapB();
	const TextureID getNormalMapR();
	const TextureID getNormalMapG();
	const TextureID getNormalMapB();

private:
	// Strings
	string _heightMapPath = "";
	string _diffuseMapPath = "";
	string _normalMapPath = "";
	string _blendMapPath = "";
	string _diffuseMapPathR = "";
	string _diffuseMapPathG = "";
	string _diffuseMapPathB = "";
	string _normalMapPathR = "";
	string _normalMapPathG = "";
	string _normalMapPathB = "";

	// Vectors
	vector<Vec3> _vertices;
	vector<Vec3> _normals;
	vector<Vec2> _uvCoords;

	// Decimals
	vector<float> _pixelValues;
	float _redRepeat = 1.0f;
	float _greenRepeat = 1.0f;
	float _blueRepeat = 1.0f;
	float _textureRepeat = 1.0f;
	float _maxHeight = 1.0f;
	float _size = 0.0f;
	float _lightness = 1.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;

	// Booleans
	bool _isSpecular = false;
	bool _isWireFramed = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
	TextureID _normalMap = 0;
	TextureID _blendMap = 0;
	TextureID _diffuseMapR = 0;
	TextureID _diffuseMapG = 0;
	TextureID _diffuseMapB = 0;
	TextureID _normalMapR = 0;
	TextureID _normalMapG = 0;
	TextureID _normalMapB = 0;
};
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
	void setUvCoords(const vector<Vec2> value);
	void setNormals(const vector<Vec3> value);
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
	void setBlendRepeatR(float value);
	void setBlendRepeatG(float value);
	void setBlendRepeatB(float value);
	void setUvRepeat(float value);
	void setSize(float value);
	void setMaxHeight(float value);
	void setLightness(float value);
	void setSpecularLightingFactor(float value);
	void setSpecularLightingIntensity(float value);
	void setSpecularLighted(bool value);
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
	const vector<Vec2>& getUvCoords();
	const vector<Vec3>& getNormals();

	// Floats
	const vector<float>& getPixelValues();
	const float getBlendRepeatR();
	const float getBlendRepeatG();
	const float getBlendRepeatB();
	const float getUvRepeat();
	const float getSize();
	const float getMaxHeight();
	const float getLightness();
	const float getSpecularLightingFactor();
	const float getSpecularLightingIntensity();

	// Booleans
	const bool isSpecularLighted();
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
	// Vectors
	vector<Vec3> _vertices;
	vector<Vec3> _normals;
	vector<Vec2> _uvCoords;

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

	// Floats
	vector<float> _pixelValues;
	float _blendRepeatR = 1.0f;
	float _blendRepeatG = 1.0f;
	float _blendRepeatB = 1.0f;
	float _uvRepeat = 1.0f;
	float _maxHeight = 1.0f;
	float _size = 0.0f;
	float _lightness = 1.0f;
	float _specularLightingFactor = 1.0f;
	float _specularLightingIntensity = 0.0f;

	// Booleans
	bool _isSpecularLighted = false;
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
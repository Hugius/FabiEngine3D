#pragma once

#include "base_entity.hpp"

class TerrainEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Setters
	void setPixelValues(const vector<float>& value);
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

	// Textures
	const TextureID getDiffuseMap()  const;
	const TextureID getNormalMap()   const;
	const TextureID getBlendMap()    const;
	const TextureID getDiffuseMapR() const;
	const TextureID getDiffuseMapG() const;
	const TextureID getDiffuseMapB() const;
	const TextureID getNormalMapR()  const;
	const TextureID getNormalMapG()  const;
	const TextureID getNormalMapB()  const;

	// Texture paths
	const string& getHeightMapPath()   const;
	const string& getDiffuseMapPath()  const;
	const string& getNormalMapPath()   const;
	const string& getBlendMapPath()    const;
	const string& getDiffuseMapPathR() const;
	const string& getDiffuseMapPathG() const;
	const string& getDiffuseMapPathB() const;
	const string& getNormalMapPathR()  const;
	const string& getNormalMapPathG()  const;
	const string& getNormalMapPathB()  const;

	// Vectors
	vector<Vec3>& getVertices();
	vector<Vec2>& getUvCoords();
	vector<Vec3>& getNormals();

	// Floats
	const float getBlendRepeatR() const;
	const float getBlendRepeatG() const;
	const float getBlendRepeatB() const;
	const float getUvRepeat()     const;
	const float getSize()         const;
	const float getMaxHeight()    const;
	const float getLightness()    const;
	const float getSpecularLightingFactor() const;
	const float getSpecularLightingIntensity() const;

	// Booleans
	const bool isSpecularLighted() const;
	const bool isWireFramed()	   const;
	const bool hasDiffuseMap()	   const;
	const bool hasNormalMap()	   const;
	const bool hasBlendMap()	   const;
	const bool hasDiffuseMapR()	   const;
	const bool hasDiffuseMapG()	   const;
	const bool hasDiffuseMapB()	   const;
	const bool hasNormalMapR()	   const;
	const bool hasNormalMapG()	   const;
	const bool hasNormalMapB()	   const;

	// Miscellaneous
	const vector<float>& getPixelValues() const;

private:
	vector<float> _pixelValues;
	vector<Vec3> _vertices;
	vector<Vec2> _uvCoords;
	vector<Vec3> _normals;

	TextureID _diffuseMap = 0;
	TextureID _normalMap  = 0;
	TextureID _blendMap   = 0;
	TextureID _diffuseMapR  = 0;
	TextureID _diffuseMapG  = 0;
	TextureID _diffuseMapB  = 0;
	TextureID _normalMapR = 0;
	TextureID _normalMapG = 0;
	TextureID _normalMapB = 0;

	string _heightMapPath  = "";
	string _diffuseMapPath = "";
	string _normalMapPath  = "";
	string _blendMapPath   = "";
	string _diffuseMapPathR  = "";
	string _diffuseMapPathG  = "";
	string _diffuseMapPathB  = "";
	string _normalMapPathR = "";
	string _normalMapPathG = "";
	string _normalMapPathB = "";

	float _blendRepeatR = 1.0f;
	float _blendRepeatG = 1.0f;
	float _blendRepeatB = 1.0f;
	float _uvRepeat		= 1.0f;
	float _maxHeight    = 1.0f;
	float _size         = 0.0f;
	float _lightness    = 1.0f;
	float _specularLightingFactor = 1.0f;
	float _specularLightingIntensity = 0.0f;

	bool _isSpecularLighted = false;
	bool _isWireFramed = false;
};
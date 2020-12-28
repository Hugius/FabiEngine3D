#pragma once

#include "base_entity.hpp"

class TerrainEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~TerrainEntity() = default;

	// Setters
	void setPixelColors(const vector<float>& value);
	void setHeightMapPath(const string& value);
	void setDiffuseMap(GLuint value);
	void setDiffuseMapPath(const string& value);
	void setNormalMap(GLuint value);
	void setNormalMapPath(const string& value);
	void setBlendMap(GLuint value);
	void setBlendMapPath(const string& value);
	void setBlendMapR(GLuint value);
	void setBlendMapPathR(const string& value);
	void setBlendMapG(GLuint value);
	void setBlendMapPathG(const string& value);
	void setBlendMapB(GLuint value);
	void setBlendMapPathB(const string& value);
	void setNormalMapR(GLuint value);
	void setNormalMapPathR(const string& value);
	void setNormalMapG(GLuint value);
	void setNormalMapPathG(const string& value);
	void setNormalMapB(GLuint value);
	void setNormalMapPathB(const string& value);
	void setBlendRepeatR(float value);
	void setBlendRepeatG(float value);
	void setBlendRepeatB(float value);
	void setUvRepeat(float value);
	void setSize(float value);
	void setMaxHeight(float value);
	void setBlendMapped(bool value);
	void setNormalMapped(bool value);
	void setNormalMappedR(bool value);
	void setNormalMappedG(bool value);
	void setNormalMappedB(bool value);
	void setSpecularLighted(bool value);
	void setLightness(float value);
	void setSpecularLightingFactor(float value);
	void setSpecularLightingIntensity(float value);

	// Textures
	const GLuint getDiffuseMap() const;
	const GLuint getNormalMap()  const;
	const GLuint getBlendMap()   const;
	const GLuint getBlendMapR()  const;
	const GLuint getBlendMapG()  const;
	const GLuint getBlendMapB()  const;
	const GLuint getNormalMapR() const;
	const GLuint getNormalMapG() const;
	const GLuint getNormalMapB() const;

	// Texture paths
	const string& getHeightMapPath()  const;
	const string& getDiffuseMapPath() const;
	const string& getNormalMapPath()  const;
	const string& getBlendMapPath()   const;
	const string& getBlendMapPathR()  const;
	const string& getBlendMapPathG()  const;
	const string& getBlendMapPathB()  const;
	const string& getNormalMapPathR() const;
	const string& getNormalMapPathG() const;
	const string& getNormalMapPathB() const;

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

	// Other
	const vector<float>& getPixelColors() const;
	const bool isBlendMapped()			  const;
	const bool isNormalMapped()			  const;
	const bool isNormalMappedR()		  const;
	const bool isNormalMappedG()		  const;
	const bool isNormalMappedB()		  const;
	const bool isSpecularLighted()		  const;

private:
	vector<float> _pixelColors;
	vector<Vec3> _vertices;
	vector<Vec2> _uvCoords;
	vector<Vec3> _normals;

	GLuint _diffuseMap = 0;
	GLuint _normalMap  = 0;
	GLuint _blendMap   = 0;
	GLuint _blendMapR  = 0;
	GLuint _blendMapG  = 0;
	GLuint _blendMapB  = 0;
	GLuint _normalMapR = 0;
	GLuint _normalMapG = 0;
	GLuint _normalMapB = 0;

	string _heightMapPath  = "";
	string _diffuseMapPath = "";
	string _normalMapPath  = "";
	string _blendMapPath   = "";
	string _blendMapPathR  = "";
	string _blendMapPathG  = "";
	string _blendMapPathB  = "";
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

	bool _isBlendMapped     = false;
	bool _isNormalMapped    = false;
	bool _isNormalMappedR   = false;
	bool _isNormalMappedG   = false;
	bool _isNormalMappedB   = false;
	bool _isSpecularLighted = false;
};
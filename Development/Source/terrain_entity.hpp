#pragma once

#include "base_entity.hpp"

class TerrainEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~TerrainEntity() = default;

	// Setters
	void setPixelColors(const vector<float>& val);
	void setHeightMapPath(const string& filePath);
	void setDiffuseMap(GLuint val);
	void setDiffuseMapPath(const string& filePath);
	void setBlendMap(GLuint val);
	void setBlendMapPath(const string& filePath);
	void setBlendMapR(GLuint val);
	void setBlendMapPathR(const string& filePath);
	void setBlendMapG(GLuint val);
	void setBlendMapPathG(const string& filePath);
	void setBlendMapB(GLuint val);
	void setBlendMapPathB(const string& filePath);
	void setBlendRepeatR(float val);
	void setBlendRepeatG(float val);
	void setBlendRepeatB(float val);
	void setUvRepeat(float val);
	void setSize(float val);
	void setMaxHeight(float val);
	void setSpecularLighted(bool val);
	void setBlendMapped(bool val);
	void setLightness(float val);
	void setSpecularLightingIntensity(float val);

	// Textures
	const GLuint getDiffuseMap() const;
	const GLuint getBlendMap()   const;
	const GLuint getBlendMapR()  const;
	const GLuint getBlendMapG()  const;
	const GLuint getBlendMapB()  const;

	// Texture paths
	const string& getHeightMapPath()  const;
	const string& getDiffuseMapPath() const;
	const string& getBlendMapPath()   const;
	const string& getBlendMapPathR()  const;
	const string& getBlendMapPathG()  const;
	const string& getBlendMapPathB()  const;

	// Repeats
	const float getBlendRepeatR() const;
	const float getBlendRepeatG() const;
	const float getBlendRepeatB() const;
	const float getUvRepeat()     const;
	const float getSize()         const;
	const float getMaxHeight()    const;
	const float getLightness()    const;
	const float getSpecularLightingIntensity() const;

	// Other
	const vector<float>& getPixelColors() const;
	const bool isSpecularLighted()		  const;
	const bool isBlendMapped()			  const;

private:
	vector<float> _pixelColors;
	vector<Vec3> _vertices;
	vector<Vec2> _uvCoords;
	vector<Vec3> _normals;

	GLuint _diffuseMap = 0;
	GLuint _blendMap   = 0;
	GLuint _blendMapR  = 0;
	GLuint _blendMapG  = 0;
	GLuint _blendMapB  = 0;

	string _heightMapPath  = "";
	string _diffuseMapPath = "";
	string _blendMapPath   = "";
	string _blendMapPathR  = "";
	string _blendMapPathG  = "";
	string _blendMapPathB  = "";

	float _blendRepeatR = 1.0f;
	float _blendRepeatG = 1.0f;
	float _blendRepeatB = 1.0f;
	float _uvRepeat		= 1.0f;
	float _maxHeight    = 1.0f;
	float _size         = 0.0f;
	float _lightness    = 1.0f;
	float _specularLightingIntensity = 0.0f;

	bool _isSpecularLighted = false;
	bool _isBlendMapped = false;
};
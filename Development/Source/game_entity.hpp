#pragma once

#include "base_entity.hpp"

class GameEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~GameEntity() = default;
	
	// Setters
	void updateModelMatrix();
	void setDiffuseMap(GLuint val);
	void setLightMap(GLuint val);
	void setReflectionMap(GLuint val);
	void setNormalMap(GLuint val);
	void addDiffuseMap(GLuint val);
	void addLightMap(GLuint val);
	void addReflectionMap(GLuint val);
	void addNormalMap(GLuint val);
	void setOriginalTranslation(Vec3 val);
	void setTranslation(Vec3 val);
	void setOriginalRotation(Vec3 val);
	void setRotation(Vec3 val);
	void setOriginalScaling(Vec3 val);
	void setScaling(Vec3 val);
	void translate(Vec3 val);
	void rotate(Vec3 val);
	void scale(Vec3 val);
	void setColor(Vec3 val);
	void setObjPath(const string& val);
	void setDiffuseMapPath(const string& val);
	void setLightMapPath(const string& val);
	void setReflectionMapPath(const string& val);
	void setNormalMapPath(const string& val);
	void setLodEntityID(const string& val);
	void addDiffuseMapPath(string val);
	void addLightMapPath(string val);
	void addReflectionMapPath(string val);
	void addNormalMapPath(string val);
	void setOriginalLightness(float val);
	void setLightness(float val);
	void setSpecularFactor(float val);
	void setSpecularIntensity(float val);
	void setMaxY(float val);
	void setAlpha(float val);
	void setUvRepeat(float val);
	void setTransparent(bool val);
	void setFaceCulled(bool val);
	void setLightMapped(bool val);
	void setNormalMapped(bool val);
	void setSkyReflective(bool val);
	void setSceneReflective(bool val);
	void setSpecularLighted(bool val);
	void setShadowed(bool val);
	void setCameraStatic(bool val);
	void setDepthMapIncluded(bool val);
	void setLevelOfDetailed(bool val);
	void clearDiffuseMaps();
	void clearLightMaps();
	void clearReflectionMaps();
	void clearNormalMaps();
	
	// Getters
	const Matrix44& getModelMatrix() const;
	const GLuint getDiffuseMap(int index) const;
	const GLuint getLightMap(int index) const;
	const GLuint getReflectionMap(int index) const;
	const GLuint getNormalMap(int index) const;
	const Vec3 getOriginalTranslation() const;
	const Vec3 getTranslation() const;
	const Vec3 getOriginalRotation() const;
	const Vec3 getRotation() const;
	const Vec3 getOriginalScaling() const;
	const Vec3 getScaling() const;
	const Vec3 getColor() const;
	const string& getObjPath() const;
	const string& getDiffuseMapPath() const;
	const string& getLightMapPath() const;
	const string& getReflectionMapPath() const;
	const string& getNormalMapPath() const;
	const string& getLodEntityID() const;
	const vector<string>& getDiffuseMapPaths();
	const vector<string>& getLightMapPaths();
	const vector<string>& getReflectionMapPaths();
	const vector<string>& getNormalMapPaths();
	const float getOriginalLightness() const;
	const float getLightness() const;
	const float getSpecularFactor() const;
	const float getSpecularIntensity() const;
	const float getAlpha() const;
	const float getUvRepeat() const;
	const float getMaxY() const;
	const bool isTransparent() const;
	const bool isFaceCulled() const;
	const bool isLightMapped() const;
	const bool isNormalMapped() const;
	const bool isSkyReflective() const;
	const bool isSceneReflective() const;
	const bool isSpecularLighted() const;
	const bool isShadowed() const;
	const bool hasDiffuseMap() const;
	const bool hasLightMap() const;
	const bool hasReflectionMap() const;
	const bool hasNormalMap() const;
	const bool isCameraStatic() const;
	const bool isDepthMapIncluded() const;
	const bool isLevelOfDetailed() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	string _objPath = "";
	string _diffuseMapPath = "";
	string _lightMapPath = "";
	string _reflectionMapPath = "";
	string _normalMapPath = "";
	string _lodEntityID = "";

	vector<string> _diffuseMapPaths;
	vector<string> _lightMapPaths;
	vector<string> _reflectionMapPaths;
	vector<string> _normalMapPaths;

	Vec3 _originalTranslation = Vec3(0.0f);
	Vec3 _originalRotation = Vec3(0.0f);
	Vec3 _originalScaling = Vec3(0.0f);
	Vec3 _translation = Vec3(0.0f);
	Vec3 _rotation = Vec3(0.0f);
	Vec3 _scaling = Vec3(1.0f);
	Vec3 _color = Vec3(1.0f);

	vector<GLuint> _diffuseMaps;
	vector<GLuint> _lightMaps;
	vector<GLuint> _reflectionMaps;
	vector<GLuint> _normalMaps;

	float _originalLightness = 1.0f;
	float _lightness = 1.0f;
	float _specularFactor = 1.0f;
	float _specularIntensity = 1.0f;
	float _alpha = 1.0f;
	float _uvRepeat = 1.0f;
	float _maxY = (std::numeric_limits<float>::max)();

	bool _isCameraStatic	 = false;
	bool _isTransparent      = false;
	bool _isFaceCulled       = false;
	bool _isLightMapped      = false;
	bool _isNormalMapped	 = false;
	bool _isSkyReflective    = false;
	bool _isSceneReflective  = false;
	bool _isSpecularLighted  = false;
	bool _isShadowed         = true;
	bool _isDepthMapIncluded = true;
	bool _isLevelOfDetailed  = false;
};
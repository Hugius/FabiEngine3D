#pragma once

#include "base_entity.hpp"

class ModelEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	
	// Setters
	void addPart(const string& value);
	void updateModelMatrix();
	void setDiffuseMap(GLuint value);
	void setLightMap(GLuint value);
	void setReflectionMap(GLuint value);
	void setNormalMap(GLuint value);
	void addDiffuseMap(GLuint value);
	void addLightMap(GLuint value);
	void addReflectionMap(GLuint value);
	void addNormalMap(GLuint value);
	void setOriginalTranslation(Vec3 value);
	void setOriginalRotation(Vec3 value);
	void setOriginalScaling(Vec3 value);
	void setTranslation(Vec3 value, const string& partID = "");
	void setRotation(Vec3 value, const string& partID = "");
	void setRotationOrigin(Vec3 value, const string& partID = "");
	void setScaling(Vec3 value, const string& partID = "");
	void translate(Vec3 value, const string& partID = "");
	void rotate(Vec3 value, const string& partID = "");
	void scale(Vec3 value, const string& partID = "");
	void setColor(Vec3 value, const string& partID = "");
	void setMeshPath(const string& value);
	void setDiffuseMapPath(const string& value);
	void setLightMapPath(const string& value);
	void setReflectionMapPath(const string& value);
	void setNormalMapPath(const string& value);
	void setLodEntityID(const string& value);
	void addDiffuseMapPath(string value);
	void addLightMapPath(string value);
	void addReflectionMapPath(string value);
	void addNormalMapPath(string value);
	void setLightness(float value);
	void setSpecularFactor(float value);
	void setSpecularIntensity(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setAlpha(float value);
	void setUvRepeat(float value);
	void setTransparent(bool value);
	void setFaceCulled(bool value);
	void setLightMapped(bool value);
	void setNormalMapped(bool value);
	void setSkyReflective(bool value);
	void setSceneReflective(bool value);
	void setSpecularLighted(bool value);
	void setShadowed(bool value);
	void setCameraStatic(bool value);
	void setDepthMapIncluded(bool value);
	void setLevelOfDetailed(bool value);
	void setWireframed(bool value);
	void clearDiffuseMaps();
	void clearLightMaps();
	void clearReflectionMaps();
	void clearNormalMaps();
	
	// Getters
	const Matrix44& getModelMatrix(unsigned int index);
	const GLuint getDiffuseMap(unsigned int index) const;
	const GLuint getLightMap(unsigned int index) const;
	const GLuint getReflectionMap(unsigned int index) const;
	const GLuint getNormalMap(unsigned int index) const;
	const Vec3 getColor(unsigned int index);
	const Vec3 getOriginalTranslation() const;
	const Vec3 getOriginalRotation() const;
	const Vec3 getOriginalScaling() const;
	const Vec3 getTranslation(const string& partID = "");
	const Vec3 getRotation(const string& partID = "");
	const Vec3 getRotationOrigin(const string& partID = "");
	const Vec3 getScaling(const string& partID = "");
	const Vec3 getColor(const string& partID = "");
	const string& getMeshPath() const;
	const string& getDiffuseMapPath() const;
	const string& getLightMapPath() const;
	const string& getReflectionMapPath() const;
	const string& getNormalMapPath() const;
	const string& getLodEntityID() const;
	const vector<string>& getDiffuseMapPaths() const;
	const vector<string>& getLightMapPaths() const;
	const vector<string>& getReflectionMapPaths() const;
	const vector<string>& getNormalMapPaths() const;
	const vector<string>& getPartIDs() const;
	const float getLightness() const;
	const float getSpecularFactor() const;
	const float getSpecularIntensity() const;
	const float getAlpha() const;
	const float getUvRepeat() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
	const bool isTransparent() const;
	const bool isFaceCulled() const;
	const bool isLightMapped() const;
	const bool isNormalMapped() const;
	const bool isSkyReflective() const;
	const bool isSceneReflective() const;
	const bool isSpecularLighted() const;
	const bool isShadowed() const;
	const bool isCameraStatic() const;
	const bool isDepthMapIncluded() const;
	const bool isLevelOfDetailed() const;
	const bool isWireframed() const;
	const bool hasDiffuseMap() const;
	const bool hasLightMap() const;
	const bool hasReflectionMap() const;
	const bool hasNormalMap() const;

private:
	unsigned int _getPartIndex(string partID);
	Vec3 _calculateAverageValue(vector<Vec3> elements);

	vector<string> _partIDs;
	vector<Matrix44> _modelMatrices;
	vector<string> _diffuseMapPaths;
	vector<string> _lightMapPaths;
	vector<string> _reflectionMapPaths;
	vector<string> _normalMapPaths;
	vector<Vec3> _translations;
	vector<Vec3> _rotations;
	vector<Vec3> _rotationOrigins;
	vector<Vec3> _scalings;
	vector<Vec3> _colors;
	vector<GLuint> _diffuseMaps;
	vector<GLuint> _lightMaps;
	vector<GLuint> _reflectionMaps;
	vector<GLuint> _normalMaps;

	string _meshPath = "";
	string _diffuseMapPath = "";
	string _lightMapPath = "";
	string _reflectionMapPath = "";
	string _normalMapPath = "";
	string _lodEntityID = "";

	Vec3 _baseTranslation = Vec3(0.0f);
	Vec3 _baseRotation = Vec3(0.0f);
	Vec3 _baseRotationOrigin = Vec3(0.0f);
	Vec3 _baseScaling = Vec3(1.0f);
	Vec3 _originalTranslation = Vec3(0.0f);
	Vec3 _originalRotation = Vec3(0.0f);
	Vec3 _originalScaling = Vec3(1.0f);

	float _lightness = 1.0f;
	float _specularFactor = 1.0f;
	float _specularIntensity = 1.0f;
	float _alpha = 1.0f;
	float _uvRepeat = 1.0f;
	float _minHeight = -(std::numeric_limits<float>::max)();
	float _maxHeight = (std::numeric_limits<float>::max)();

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
	bool _wireframed		 = false;
};
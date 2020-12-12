#pragma once

#include "base_entity.hpp"

class GameEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~GameEntity() = default;
	
	// Setters
	void addPart(const string& val);
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
	void setOriginalRotation(Vec3 val);
	void setOriginalScaling(Vec3 val);
	void setTranslation(Vec3 val, const string& partName = "");
	void setRotation(Vec3 val, const string& partName = "");
	void setRotationOrigin(Vec3 val, const string& partName = "");
	void setScaling(Vec3 val, const string& partName = "");
	void translate(Vec3 val, const string& partName = "");
	void rotate(Vec3 val, const string& partName = "");
	void scale(Vec3 val, const string& partName = "");
	void setColor(Vec3 val, const string& partName = "");
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
	void setWireframed(bool val);
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
	const Vec3 getTranslation(const string& partName = "");
	const Vec3 getRotation(const string& partName = "");
	const Vec3 getRotationOrigin(const string& partName = "");
	const Vec3 getScaling(const string& partName = "");
	const Vec3 getColor(const string& partName = "");
	const string& getObjPath() const;
	const string& getDiffuseMapPath() const;
	const string& getLightMapPath() const;
	const string& getReflectionMapPath() const;
	const string& getNormalMapPath() const;
	const string& getLodEntityID() const;
	const vector<string>& getDiffuseMapPaths() const;
	const vector<string>& getLightMapPaths() const;
	const vector<string>& getReflectionMapPaths() const;
	const vector<string>& getNormalMapPaths() const;
	const vector<string>& getPartNames() const;
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
	const bool isWireframed() const;

private:
	unsigned int _getPartIndex(string partName);
	Vec3 _calculateAverage(vector<Vec3> elements);

	vector<string> _partNames;
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

	string _objPath = "";
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
	bool _wireframed		 = false;
};
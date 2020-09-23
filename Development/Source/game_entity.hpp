#pragma once

#include "base_entity.hpp"

#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

class GameEntity final : public BaseEntity
{
public:
	GameEntity()  = default;
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
	void setOriginalTranslation(vec3 val);
	void setTranslation(vec3 val);
	void setOriginalRotation(vec3 val);
	void setRotation(vec3 val);
	void setOriginalScaling(vec3 val);
	void setScaling(vec3 val);
	void translate(vec3 val);
	void rotate(vec3 val);
	void scale(vec3 val);
	void setColor(vec3 val);
	void setObjPath(const string& val);
	void setDiffuseMapPath(const string& val);
	void setLightMapPath(const string& val);
	void setReflectionMapPath(const string& val);
	void setNormalMapPath(const string& val);
	void setLodEntityID(const string& val);
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
	
	// Getters
	const mat4& getModelMatrix() const;
	const GLuint getDiffuseMap(int index) const;
	const GLuint getLightMap(int index) const;
	const GLuint getReflectionMap(int index) const;
	const GLuint getNormalMap(int index) const;
	const vec3 getOriginalTranslation() const;
	const vec3 getTranslation() const;
	const vec3 getOriginalRotation() const;
	const vec3 getRotation() const;
	const vec3 getOriginalScaling() const;
	const vec3 getScaling() const;
	const vec3 getColor() const;
	const string& getObjPath() const;
	const string& getDiffuseMapPath() const;
	const string& getLightMapPath() const;
	const string& getReflectionMapPath() const;
	const string& getNormalMapPath() const;
	const string& getLodEntityID() const;
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
	mat4 _modelMatrix = mat4(1.0f);

	string _objPath = "";
	string _diffuseMapPath = "";
	string _lightMapPath = "";
	string _reflectionMapPath = "";
	string _normalMapPath = "";
	string _lodEntityID = "";

	vec3 _originalTranslation = vec3(0.0f);
	vec3 _originalRotation = vec3(0.0f);
	vec3 _originalScaling = vec3(0.0f);
	vec3 _translation = vec3(0.0f);
	vec3 _rotation = vec3(0.0f);
	vec3 _scaling = vec3(1.0f);
	vec3 _color = vec3(1.0f);

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
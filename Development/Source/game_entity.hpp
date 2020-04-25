#pragma once

#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "base_entity.hpp"

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
	void addDiffuseMap(GLuint val);
	void addLightMap(GLuint val);
	void addReflectionMap(GLuint val);
	void setTranslation(vec3 val);
	void setRotation(vec3 val);
	void setScaling(vec3 val);
	void translate(vec3 val, float delta);
	void rotate(vec3 val, float delta);
	void scale(vec3 val, float delta);
	void setColor(vec3 val);
	void setModelName(const string & val);
	void setTransparent(bool val);
	void setFaceCulled(bool val);
	void setLightMapped(bool val);
	void setSkyReflective(bool val);
	void setSceneReflective(bool val);
	void setSpecular(bool val);
	void setShadowed(bool val);
	void setMaxY(float val);
	void setAlpha(float val);
	void setUvRepeat(float val);
	
	// Getters
	const mat4 & getModelMatrix() const;
	const GLuint getDiffuseMap(int index) const;
	const GLuint getLightMap(int index) const;
	const GLuint getReflectionMap(int index) const;
	const vec3 getTranslation() const;
	const vec3 getRotation() const;
	const vec3 getScaling() const;
	const vec3 getColor() const;
	const string & getModelName() const;
	const bool isTransparent() const;
	const bool isFaceCulled() const;
	const bool isLightMapped() const;
	const bool isSkyReflective() const;
	const bool isSceneReflective() const;
	const bool isSpecular() const;
	const bool isShadowed() const;
	const bool hasTexture() const;
	const float getMaxY() const;
	const float getAlpha() const;
	const float getUvRepeat() const;

private:
	mat4 _modelMatrix = mat4(1.0f);

	string _modelName = "";

	vec3 _translation = vec3(0.0f);
	vec3 _rotation    = vec3(0.0f);
	vec3 _scaling     = vec3(1.0f);
	vec3 _color       = vec3(1.0f);

	vector<GLuint> _diffuseMaps;
	vector<GLuint> _lightMaps;
	vector<GLuint> _reflectionMaps;

	bool _isTransparent      = false;
	bool _isFaceCulled       = false;
	bool _isLightMapped      = false;
	bool _isSkyReflective    = false;
	bool _isSceneReflective = false;
	bool _isSpecular         = false;
	bool _isShadowed         = true;

	float _alpha = 1.0f;
	float _uvRepeat = 1.0f;
	float _maxY = (std::numeric_limits<float>::max)();
};
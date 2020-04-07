#pragma once

#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "Entity.hpp"

class GameEntity final : public Entity
{
public:
	GameEntity()  = default;
	~GameEntity() = default;

	// Setters
	void updateModelMatrix();
	void addDiffuseMap(GLuint val);
	void addLightmap(GLuint val);
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
	void setScreenReflective(bool val);
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
	const bool isScreenReflective() const;
	const bool isSpecular() const;
	const bool isShadowed() const;
	const float getMaxY() const;
	const float getAlpha() const;
	const float getUvRepeat() const;

private:
	mat4 p_modelMatrix = mat4(1.0f);

	string p_modelName = "";

	vec3 p_translation = vec3(0.0f);
	vec3 p_rotation    = vec3(0.0f);
	vec3 p_scaling     = vec3(1.0f);
	vec3 p_color       = vec3(1.0f);

	vector<GLuint> p_diffuseMaps;
	vector<GLuint> p_lightMaps;
	vector<GLuint> p_reflectionMaps;

	bool p_isTransparent      = false;
	bool p_isFaceCulled       = false;
	bool p_isLightMapped      = false;
	bool p_isSkyReflective    = false;
	bool p_isScreenReflective = false;
	bool p_isSpecular         = false;
	bool p_isShadowed         = true;

	float p_alpha = 1.0f;
	float p_uvRepeat = 1.0f;
	float p_maxY = (std::numeric_limits<float>::max)();
};
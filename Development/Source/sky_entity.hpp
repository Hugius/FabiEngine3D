#pragma once

#include "base_entity.hpp"

#include <GLM\\glm.hpp>
#include <array>

using std::array;
using glm::mat4;

class SkyEntity final : public BaseEntity
{
public:
	SkyEntity()  = default;
	~SkyEntity() = default;

	void setDiffuseMapPaths(const array<string, 6>& val);
	void setRotationMatrix(const mat4& val);
	void setColor(vec3 val);
	void setCubeMap(GLuint val);
	void setLightness(float val);
	void setRotationSpeed(float val);

	const array<string, 6>& getDiffuseMapPaths() const;
	const mat4& getRotationMatrix()				 const;
	const vec3 getColor()						 const;
	const GLuint getCubeMap()					 const;
	const float getLightness()					 const;
	const float getRotationSpeed()				 const;

private:
	array<string, 6> _diffuseMapPaths = {"", "", "", "", "", ""};

	mat4 _rotationMatrix = mat4(1.0f);

	vec3 _color = vec3(1.0f);

	GLuint _cubeMap   = 0;

	float _lightness		= 1.0f;
	float _rotationSpeed    = 0.0f;
};
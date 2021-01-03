#pragma once

#include "base_entity.hpp"
#include "direction.hpp"

#include <array>

using std::array;

class SkyEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~SkyEntity() = default;

	void updateRotationMatrix();
	void setDiffuseMapPaths(const array<string, 6>& value);
	void setColor(Vec3 value);
	void setCubeMap(GLuint value);
	void setOriginalLightness(float value);
	void setLightness(float value);
	void setRotationSpeed(float value);
	void rotateAllDirections(bool value);

	const array<string, 6>& getDiffuseMapPaths() const;
	const Matrix44& getRotationMatrix()			 const;
	const Vec3 getColor()						 const;
	const GLuint getCubeMap()					 const;
	const float getOriginalLightness()			 const;
	const float getLightness()					 const;
	const float getRotationSpeed()				 const;

private:
	array<string, 6> _diffuseMapPaths = {"", "", "", "", "", ""};

	Matrix44 _rotationMatrix = Matrix44(1.0f);

	Vec3 _color = Vec3(1.0f);

	GLuint _cubeMap = 0;

	bool _rotateAllDirections = false;

	float _originalLightness = 1.0f;
	float _lightness		 = 1.0f;
	float _rotationSpeed     = 0.0f;
	float _rotation			 = 0.0f;
};
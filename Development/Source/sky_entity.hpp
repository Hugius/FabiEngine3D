#pragma once

#include "base_entity.hpp"

#include "mathematics.hpp"
#include <array>

using std::array;


class SkyEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~SkyEntity() = default;

	void updateRotationMatrix();
	void setDiffuseMapPaths(const array<string, 6>& val);
	void setColor(Vec3 val);
	void setCubeMap(GLuint val);
	void setOriginalLightness(float val);
	void setLightness(float val);
	void setRotationSpeed(float val);

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

	float _originalLightness = 1.0f;
	float _lightness		 = 1.0f;
	float _rotationSpeed     = 0.0f;
	float _rotation			 = 0.0f;
};
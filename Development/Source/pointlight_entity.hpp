#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"
#include "pointlight_shape.hpp"

class PointlightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateTransformation();
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void moveTo(Vec3 target, float speed);
	void setRadius(Vec3 value);
	void setColor(Vec3 value);
	void setIntensity(float value);
	void setShape(PointlightShape value);

	// Vectors
	const Vec3 getPosition();
	const Vec3 getColor();
	const Vec3 getRadius();

	// Floats
	const float getIntensity();

	// Miscellaneous
	const PointlightShape getShape();

private:
	// Vectors
	Vec3 _position = Vec3(0.0f);
	Vec3 _positionTarget = Vec3(0.0f);
	Vec3 _radius = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);

	// Floats
	float _positionTargetSpeed = 0.0f;
	float _intensity = 1.0f;

	// Miscellaneous
	PointlightShape _shape = PointlightShape::CIRCLE;
};
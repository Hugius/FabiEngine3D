#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"
#include "light_shape.hpp"

class LightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void setVisible(bool value);
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void setRadius(Vec3 value);
	void setColor(Vec3 value);
	void setIntensity(float value);
	void setShape(LightShape value);

	// Vectors
	const Vec3 getPosition();
	const Vec3 getColor();
	const Vec3 getRadius();

	// Floats
	const float getIntensity();

	// Booleans
	const bool isVisible();

	// Miscellaneous
	const LightShape getShape();

private:
	// Vectors
	Vec3 _position = Vec3(0.0f);
	Vec3 _radius = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);

	// Floats
	float _intensity = 1.0f;

	// Booleans
	bool _isVisible = true;

	// Miscellaneous
	LightShape _shape = LightShape::CIRCLE;
};
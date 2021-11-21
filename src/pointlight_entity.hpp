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
	void setPosition(fvec3 value);
	void move(fvec3 value);
	void moveTo(fvec3 target, float speed);
	void setRadius(fvec3 value);
	void setColor(fvec3 value);
	void setIntensity(float value);
	void setShape(PointlightShape value);

	// Vectors
	const fvec3 getPosition() const;
	const fvec3 getColor() const;
	const fvec3 getRadius() const;

	// Decimals
	const float getIntensity() const;

	// Miscellaneous
	const PointlightShape getShape() const;

private:
	// Vectors
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _radius = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);

	// Decimals
	float _positionTargetSpeed = 0.0f;
	float _intensity = 1.0f;

	// Miscellaneous
	PointlightShape _shape = PointlightShape::CIRCLE;
};
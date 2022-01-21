#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"
#include "pointlight_shape.hpp"

class PointlightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void updateTransformation();
	void setPosition(const fvec3& value);
	void move(const fvec3& value);
	void moveTo(const fvec3& target, float speed);
	void setRadius(const fvec3& value);
	void setColor(const fvec3& value);
	void setIntensity(float value);
	void setShape(PointlightShape value);

	const fvec3& getPosition() const;
	const fvec3& getColor() const;
	const fvec3& getRadius() const;

	const float getIntensity() const;

	const PointlightShape getShape() const;

private:
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _radius = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);

	float _positionTargetSpeed = 0.0f;
	float _intensity = 1.0f;

	PointlightShape _shape = PointlightShape::CIRCLE;
};
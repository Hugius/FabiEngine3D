#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"

class SpotlightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateTransformation();
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void moveTo(Vec3 target, float speed);
	void setFront(Vec3 value);
	void setColor(Vec3 value);
	void setIntensity(float value);
	void setAngle(float value);
	void setDistance(float value);

	// Vectors
	const Vec3 getPosition();
	const Vec3 getFront();
	const Vec3 getColor();

	// Floats
	const float getIntensity();
	const float getAngle();
	const float getDistance();

private:
	// Vectors
	Vec3 _position = Vec3(0.0f);
	Vec3 _positionTarget = Vec3(0.0f);
	Vec3 _front = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);

	// Floats
	float _positionTargetSpeed = 0.0f;
	float _intensity = 1.0f;
	float _angle = 1.0f;
	float _distance = 1.0f;
};
#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"

class SpotlightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateTransformation();
	void updateFrontVector();
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void moveTo(Vec3 target, float speed);
	void setColor(Vec3 value);
	void setYaw(float value);
	void setPitch(float value);
	void setIntensity(float value);
	void setAngle(float value);
	void setDistance(float value);

	// Vectors
	const Vec3 getPosition();
	const Vec3 getFrontVector();
	const Vec3 getColor();

	// Floats
	const float getYaw();
	const float getPitch();
	const float getIntensity();
	const float getAngle();
	const float getDistance();

private:
	// Vectors
	Vec3 _position = Vec3(0.0f);
	Vec3 _positionTarget = Vec3(0.0f);
	Vec3 _frontVector = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);

	// Floats
	float _positionTargetSpeed = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _intensity = 1.0f;
	float _angle = 1.0f;
	float _distance = 1.0f;
};
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
	void setPosition(fvec3 value);
	void move(fvec3 value);
	void moveTo(fvec3 target, float speed);
	void setColor(fvec3 value);
	void setYaw(float value);
	void setPitch(float value);
	void setIntensity(float value);
	void setAngle(float value);
	void setDistance(float value);

	// Vectors
	const fvec3 getPosition() const;
	const fvec3 getFrontVector() const;
	const fvec3 getColor() const;

	// Decimals
	const float getYaw() const;
	const float getPitch() const;
	const float getIntensity() const;
	const float getAngle() const;
	const float getDistance() const;

private:
	// Vectors
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _frontVector = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);

	// Decimals
	static inline const float MAX_ANGLE = 45.0f;
	float _positionTargetSpeed = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _intensity = 1.0f;
	float _angle = 0.0f;
	float _distance = 0.0f;
};
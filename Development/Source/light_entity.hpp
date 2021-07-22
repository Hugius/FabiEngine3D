#pragma once

#include "base_entity.hpp"

class LightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setPosition(Vec3 value);
	void move(Vec3 value);
	void setColor(Vec3 value);
	void setIntensity(float value);
	void setDistanceFactor(float value);

	const Vec3 getPosition() const;
	const Vec3 getColor() const;
	const float getIntensity() const;
	const float getDistanceFactor() const;

private:
	Vec3 _position = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);

	float _intensity = 1.0f;
	float _distanceFactor = 1.0f;
};
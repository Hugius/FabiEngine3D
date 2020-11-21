#pragma once

#include "base_entity.hpp"

class LightEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~LightEntity() = default;

	void setPosition(Vec3 position);
	void setColor(Vec3 color);
	void setIntensity(float intensity);
	void setDistanceFactor(float distance);

	const Vec3 getPosition() const;
	const Vec3 getColor() const;
	const float getIntensity() const;
	const float getDistanceFactor() const;

private:
	Vec3 _position = Vec3(0.0f);
	Vec3 _color    = Vec3(1.0f);

	float _intensity = 1.0f;
	float _distanceFactor = 1.0f;
};
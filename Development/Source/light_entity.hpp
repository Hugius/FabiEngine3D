#pragma once

#include "base_entity.hpp"

class LightEntity final : public BaseEntity
{
public:
	LightEntity() = default;
	~LightEntity() = default;

	void setPosition(vec3 position);
	void setColor(vec3 color);
	void setIntensity(float intensity);
	void setDistanceFactor(float distance);

	const vec3 getPosition() const;
	const vec3 getColor() const;
	const float getIntensity() const;
	const float getDistanceFactor() const;

private:
	vec3 _position = vec3(0.0f);
	vec3 _color    = vec3(1.0f);

	float _intensity = 1.0f;
	float _distanceFactor = 1.0f;
};
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

	const vec3 getPosition() const;
	const vec3 getColor() const;
	const float getIntensity() const;

private:
	vec3 _position = vec3(0.0f);
	vec3 _color    = vec3(0.0f);

	float _intensity;
};
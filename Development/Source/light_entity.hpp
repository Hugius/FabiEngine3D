#pragma once
#include "base_entity.hpp"

class LightEntity final : public BaseEntity
{
public:
	LightEntity() = default;
	~LightEntity() = default;

	void setPosition(vec3 position);
	void setColor(vec3 color);
	void setStrength(float strength);

	const vec3 getPosition() const;
	const vec3 getColor() const;
	const float getStrength() const;

private:
	vec3 _position = vec3(0.0f);
	vec3 _color    = vec3(0.0f);

	float _strength;
};
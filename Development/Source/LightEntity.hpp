#pragma once
#include "Entity.hpp"

class LightEntity final : public Entity
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
	vec3 p_position = vec3(0.0f);
	vec3 p_color    = vec3(0.0f);

	float p_strength;
};
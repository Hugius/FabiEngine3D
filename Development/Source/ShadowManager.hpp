#pragma once

#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "ShaderBus.hpp"

class ShadowManager final
{
public:
	ShadowManager() = default;
	~ShadowManager() = default;
	
	void loadShadows(vec3 eye, vec3 center, float size, float reach);
	void update(ShaderBus& shaderBus);

private:
	mat4 p_createLightSpaceMatrix();

	vec3 p_eye = vec3(0.0f);
	vec3 p_center = vec3(0.0f);

	float p_size = 0.0f;
	float p_reach = 0.0f;
};
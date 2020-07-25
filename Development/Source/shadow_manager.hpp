#pragma once

#include "shader_bus.hpp"

#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

class ShadowManager final
{
public:
	ShadowManager() = default;
	~ShadowManager() = default;
	
	void loadShadows(vec3 eye, vec3 center, float size, float reach);
	void update(ShaderBus& shaderBus);

private:
	mat4 _createLightSpaceMatrix();

	vec3 _eye = vec3(0.0f);
	vec3 _center = vec3(0.0f);

	float _size = 0.0f;
	float _reach = 0.0f;
};
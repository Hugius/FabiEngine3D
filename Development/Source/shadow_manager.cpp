#include "shadow_manager.hpp"
#include "shader_bus.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>

void ShadowManager::loadShadows(vec3 eye, vec3 center, float size, float reach)
{
	_eye    = eye;
	_center = center;
	_size   = size;
	_reach  = reach;
}

void ShadowManager::update(ShaderBus& shaderBus)
{
	shaderBus.setShadowMatrix(_createLightSpaceMatrix());
}

mat4 ShadowManager::_createLightSpaceMatrix()
{
	glEnable(GL_DEPTH_CLAMP_NV);

	// Matrix generation
	mat4 lightView = glm::lookAt(_eye, _center, vec3(0.0f, 1.0f, 0.0f));
	mat4 lightProj = glm::ortho(-_size, _size, -_size, _size, 1.0f, _reach);
	return lightProj * lightView;
}
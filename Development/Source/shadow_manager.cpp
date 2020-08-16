#include "shadow_manager.hpp"
#include "render_bus.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>

void ShadowManager::loadShadows(vec3 eye, vec3 center, float size, float reach)
{
	_eye    = eye;
	_center = center;
	_size   = size;
	_reach  = reach;
}

void ShadowManager::update(RenderBus& renderBus)
{
	renderBus.setShadowMatrix(_createLightSpaceMatrix());
	renderBus.setShadowEyePosition(_eye);
	renderBus.setShadowAreaCenter(_center);
	renderBus.setShadowAreaSize(_size);
	renderBus.setShadowAreaReach(_reach);
}

mat4 ShadowManager::_createLightSpaceMatrix()
{
	glEnable(GL_DEPTH_CLAMP_NV);

	// Matrix generation
	mat4 lightView = glm::lookAt(_eye, _center, vec3(0.0f, 1.0f, 0.0f));
	mat4 lightProj = glm::ortho(-_size / 2.0f, _size / 2.0f, -_size / 2.0f, _size / 2.0f, 0.1f, _reach);
	return lightProj * lightView;
}
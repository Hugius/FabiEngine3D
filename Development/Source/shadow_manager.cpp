#include "shadow_manager.hpp"
#include "render_bus.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>
#include <iostream>

void ShadowManager::loadShadows(vec3 eye, vec3 center, float size, float reach, bool isFollowingCamera)
{
	_eye    = eye;
	_center = center;
	_size   = size;
	_reach  = reach;
	_isFollowingCamera = isFollowingCamera;
}

void ShadowManager::update(RenderBus& renderBus)
{
	if (_isFollowingCamera)
	{
		// Updated values
		vec3 cameraPos = renderBus.getCameraPosition();
		vec3 newEye	   = vec3(cameraPos.x, 0.0f, cameraPos.z) + _eye;
		vec3 newCenter = vec3(cameraPos.x, 0.0f, cameraPos.z) + _center;

		// Apply
		renderBus.setShadowEyePosition(newEye);
		renderBus.setShadowAreaCenter(newCenter);
		renderBus.setShadowAreaSize(_size);
		renderBus.setShadowAreaReach(_reach);
		renderBus.setShadowMatrix(_createLightSpaceMatrix(newEye, newCenter, _size, _reach));
	}
	else
	{
		renderBus.setShadowEyePosition(_eye);
		renderBus.setShadowAreaCenter(_center);
		renderBus.setShadowAreaSize(_size);
		renderBus.setShadowAreaReach(_reach);
		renderBus.setShadowMatrix(_createLightSpaceMatrix(_eye, _center, _size, _reach));
	}
}

mat4 ShadowManager::_createLightSpaceMatrix(vec3 eye, vec3 center, float size, float reach)
{
	glEnable(GL_DEPTH_CLAMP_NV);

	// Matrix generation
	mat4 lightView = glm::lookAt(eye, center, vec3(0.0f, 1.0f, 0.0f));
	mat4 lightProj = glm::ortho(-size / 2.0f, size / 2.0f, -size / 2.0f, size / 2.0f, 0.1f, reach);

	return lightProj * lightView;
}

vec3 ShadowManager::getEye()
{
	return _eye;
}

vec3 ShadowManager::getCenter()
{
	return _center;
}

float ShadowManager::getSize()
{
	return _size;
}

float ShadowManager::getReach()
{
	return _reach;
}

bool ShadowManager::isFollowingCamera()
{
	return _isFollowingCamera;
}
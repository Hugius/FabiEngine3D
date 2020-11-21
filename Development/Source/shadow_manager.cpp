#include "shadow_manager.hpp"
#include "render_bus.hpp"

void ShadowManager::loadShadows(Vec3 eye, Vec3 center, float size, float reach, bool isFollowingCamera, int interval)
{
	_eye    = eye;
	_center = center;
	_size   = size;
	_reach  = reach;
	_isFollowingCamera = isFollowingCamera;
	_interval = interval;
}

void ShadowManager::update(RenderBus& renderBus)
{
	if (_isFollowingCamera)
	{
		static int passedFrames = 0;
		if (passedFrames >= _interval)
		{
			passedFrames = 0;

			// Updated values
			Vec3 cameraPos = renderBus.getCameraPosition();
			Vec3 newEye = Vec3(cameraPos.x, 0.0f, cameraPos.z) + _eye;
			Vec3 newCenter = Vec3(cameraPos.x, 0.0f, cameraPos.z) + _center;

			// Apply
			renderBus.setShadowEyePosition(newEye);
			renderBus.setShadowAreaCenter(newCenter);
			renderBus.setShadowAreaSize(_size);
			renderBus.setShadowAreaReach(_reach);
			renderBus.setShadowMatrix(_createLightSpaceMatrix(newEye, newCenter, _size, _reach));
		}
		else
		{
			passedFrames++;
		}
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

Matrix44 ShadowManager::_createLightSpaceMatrix(Vec3 eye, Vec3 center, float size, float reach)
{
	glEnable(GL_DEPTH_CLAMP_NV);

	// Matrix generation
	Matrix44 lightView = Matrix44::createView(eye, center, Vec3(0.0f, 1.0f, 0.0f));
	Matrix44 lightProj = Matrix44::createOrtho(-size / 2.0f, size / 2.0f, -size / 2.0f, size / 2.0f, 0.1f, reach);

	return lightProj * lightView;
}

Vec3 ShadowManager::getEye()
{
	return _eye;
}

Vec3 ShadowManager::getCenter()
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

int ShadowManager::getInterval()
{
	return _interval;
}
#pragma once

#include "render_bus.hpp"

class ShadowManager final
{
public:
	ShadowManager() = default;
	~ShadowManager() = default;
	
	void loadShadows(Vec3 eye, Vec3 center, float size, float reach, bool followingCamera, int interval);
	void update(RenderBus& renderBus);

	Vec3 getEye();
	Vec3 getCenter();
	float getSize();
	float getReach();
	bool isFollowingCamera();
	int getInterval();

private:
	Matrix44 _createLightSpaceMatrix(Vec3 eye, Vec3 center, float size, float reach);

	Vec3 _eye = Vec3(0.0f);
	Vec3 _center = Vec3(0.0f);

	float _size = 0.0f;
	float _reach = 0.0f;

	int _interval = 0;
	int _passedFrames = 0;

	bool _isFollowingCamera = false;
};
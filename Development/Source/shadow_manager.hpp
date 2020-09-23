#pragma once

#include "render_bus.hpp"

#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

class ShadowManager final
{
public:
	ShadowManager() = default;
	~ShadowManager() = default;
	
	void loadShadows(vec3 eye, vec3 center, float size, float reach, bool followingCamera, int interval);
	void update(RenderBus& renderBus);

	vec3 getEye();
	vec3 getCenter();
	float getSize();
	float getReach();
	bool isFollowingCamera();
	int getInterval();

private:
	mat4 _createLightSpaceMatrix(vec3 eye, vec3 center, float size, float reach);

	vec3 _eye = vec3(0.0f);
	vec3 _center = vec3(0.0f);

	float _size = 0.0f;
	float _reach = 0.0f;

	int _interval = 0;

	bool _isFollowingCamera = false;
};
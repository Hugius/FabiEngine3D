#pragma once

#include "render_bus.hpp"

class ShadowGenerator final
{
public:
	ShadowGenerator();
	
	// Voids
	void loadShadows(Vec3 eye, Vec3 center, float size, float reach, bool followingCamera, unsigned int interval);
	void unloadShadows();
	void update(RenderBus& renderBus);
	void updateMatrix(RenderBus& renderBus);

	// Vectors
	Vec3 getEye();
	Vec3 getCenter();

	// Floats
	float getSize();
	float getReach();

	// Integers
	int getInterval();

	// Booleans
	bool isFollowingCamera();

private:
	// Matrices
	Matrix44 _createLightSpaceMatrix(Vec3 eye, Vec3 center, float size, float reach);

	// Vectors
	Vec3 _eye = Vec3(0.0f);
	Vec3 _center = Vec3(0.0f);

	// Floats
	static inline const float DEFAULT_NEAR_Z = 0.01f;
	float _size = 0.0f;
	float _reach = 0.0f;

	// Integers
	unsigned int _interval = 0;
	unsigned int _passedFrames = 0;

	// Booleans
	bool _isFollowingCamera = false;
};
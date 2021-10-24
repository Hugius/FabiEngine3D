#pragma once

#include "render_bus.hpp"

class ShadowGenerator final
{
public:
	ShadowGenerator(RenderBus& renderBus);
	
	// Voids
	void update();
	void updateMatrix();
	void setInterval(unsigned int value);
	void setFollowingCamera(bool value);

	// Integers
	const unsigned int getInterval() const;

	// Booleans
	const bool isFollowingCamera() const;

private:
	// Matrices
	Matrix44 _createLightSpaceMatrix();

	// Decimals
	static inline const float NEAR_Z = 0.01f;

	// Integers
	unsigned int _interval = 0;
	unsigned int _passedFrames = 0;

	// Booleans
	bool _isFollowingCamera = false;

	// Miscellaneous
	RenderBus& _renderBus;
};
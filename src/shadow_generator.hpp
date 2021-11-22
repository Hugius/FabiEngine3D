#pragma once

#include "render_bus.hpp"

class ShadowGenerator final
{
public:
	ShadowGenerator(RenderBus& renderBus);

	// VOID
	void update();
	void updateMatrix();
	void setInterval(unsigned int value);
	void setFollowingCamera(bool value);

	// UNSIGNED INT
	const unsigned int getInterval() const;

	// BOOL
	const bool isFollowingCamera() const;

private:
	// MAT44
	const mat44 _createLightSpaceMatrix() const;

	// FLOAT
	static inline const float NEAR_DISTANCE = 0.01f;

	// UNSIGNED INT
	unsigned int _interval = 0;
	unsigned int _passedFrames = 0;

	// BOOL
	bool _isFollowingCamera = false;

	// MISCELLANEOUS
	RenderBus& _renderBus;
};
#pragma once

#include "render_bus.hpp"

class ShadowGenerator final
{
public:
	ShadowGenerator(RenderBus& renderBus);

	// VOID
	void update();
	void generate();
	void setEyePosition(fvec3 value);
	void setCenterPosition(fvec3 value);
	void setAreaSize(float value);
	void setAreaReach(float value);
	void setLightness(float value);
	void setQuality(unsigned int value);
	void setInterval(unsigned int value);
	void setFollowingCamera(bool value);

	// FVEC3
	const fvec3 getEyePosition() const;
	const fvec3 getCenterPosition() const;

	// FLOAT
	const float getAreaSize() const;
	const float getAreaReach() const;
	const float getLightness() const;

	// UNSIGNED INT
	const unsigned int getQuality() const;
	const unsigned int getInterval() const;

	// BOOL
	const bool isFollowingCamera() const;

private:
	// MAT44
	const mat44 _createShadowMatrix(fvec3 eyePosition, fvec3 centerPosition, float areaSize, float areaReach) const;

	// FVEC3
	fvec3 _eyePosition = fvec3(0.0f);
	fvec3 _centerPosition = fvec3(0.0f);

	// FLOAT
	static inline const float NEAR_DISTANCE = 0.01f;
	float _areaSize = 0.0f;
	float _areaReach = 0.0f;
	float _lightness = 0.0f;

	// UNSIGNED INT
	unsigned int _quality = 0;
	unsigned int _interval = 0;
	unsigned int _passedFrames = 0;

	// BOOL
	bool _isFollowingCamera = false;

	// MISCELLANEOUS
	RenderBus& _renderBus;
};
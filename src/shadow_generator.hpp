#pragma once

#include "render_bus.hpp"

class ShadowGenerator final
{
public:
	void inject(shared_ptr<RenderBus> renderBus);
	void update();
	void generate();
	void setEyePosition(const fvec3& value);
	void setCenterPosition(const fvec3& value);
	void setSize(float value);
	void setReach(float value);
	void setLightness(float value);
	void setQuality(unsigned int value);
	void setInterval(unsigned int value);
	void setEnabled(bool value);
	void setFollowingCamera(bool value);

	const fvec3& getEyePosition() const;
	const fvec3& getCenterPosition() const;

	const float getSize() const;
	const float getReach() const;
	const float getLightness() const;

	const unsigned int getQuality() const;
	const unsigned int getInterval() const;

	const bool isEnabled();
	const bool isFollowingCamera() const;

private:
	const mat44 _createShadowMatrix(const fvec3& eyePosition, const fvec3& centerPosition, float size, float reach) const;

	fvec3 _eyePosition = fvec3(0.0f);
	fvec3 _centerPosition = fvec3(0.0f);

	static inline constexpr float NEAR_DISTANCE = 0.01f;
	float _size = 0.0f;
	float _reach = 0.0f;
	float _lightness = 0.0f;

	unsigned int _quality = 0;
	unsigned int _interval = 0;
	unsigned int _passedFrames = 0;

	bool _isEnabled = false;
	bool _isFollowingCamera = false;

	shared_ptr<RenderBus> _renderBus = nullptr;
};
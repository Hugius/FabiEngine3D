#pragma once

#include "render_window.hpp"

#include <memory>

using std::shared_ptr;

class Camera final
{
public:
	Camera();

	void inject(shared_ptr<RenderWindow> renderWindow);
	void reset();
	void update();
	void calculateMatrices();
	void move(const fvec3 & change);
	void moveTo(const fvec3 & target, float speed);
	void setPosition(const fvec3 & value);
	void setThirdPersonLookat(const fvec3 & value);
	void setThirdPersonDistance(float value);
	void setAspectRatio(float value);
	void setFov(float value);
	void setCursorSensitivity(float value);
	void setYaw(float value);
	void setPitch(float value);
	void setFirstPersonYaw(float value);
	void setFirstPersonPitch(float value);
	void setThirdPersonYaw(float value);
	void setThirdPersonPitch(float value);
	void setMinFirstPersonPitch(float value);
	void setMaxFirstPersonPitch(float value);
	void setMinThirdPersonPitch(float value);
	void setMaxThirdPersonPitch(float value);
	void followRightXZ(float speed);
	void followFrontXYZ(float speed);
	void followFrontXZ(float speed);
	void setFirstPersonEnabled(bool value);
	void setThirdPersonEnabled(bool value);
	void setNear(float value);
	void setFar(float value);
	void invertUp();

	const mat44 & getView() const;
	const mat44 & getProjection() const;

	const fvec3 & getRight() const;
	const fvec3 & getUp() const;
	const fvec3 & getFront() const;
	const fvec3 & getPosition() const;
	const fvec3 & getThirdPersonLookat() const;

	const float getFov() const;
	const float getAspectRatio() const;
	const float getYaw() const;
	const float getPitch() const;
	const float getFirstPersonYaw() const;
	const float getFirstPersonPitch() const;
	const float getMinFirstPersonPitch() const;
	const float getMaxFirstPersonPitch() const;
	const float getThirdPersonYaw() const;
	const float getThirdPersonPitch() const;
	const float getMinThirdPersonPitch() const;
	const float getMaxThirdPersonPitch() const;
	const float getThirdPersonDistance() const;
	const float getNear() const;
	const float getFar() const;
	const float getCursorSensitivity() const;

	const bool isThirdPersonEnabled() const;
	const bool isFirstPersonEnabled() const;

private:
	static inline const fvec3 POSITIVE_UP = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 NEGATIVE_UP = fvec3(0.0f, -1.0f, 0.0f);

	static inline constexpr float DEFAULT_NEAR = 0.1f;
	static inline constexpr float DEFAULT_FAR = 10000.0f;
	static inline constexpr float DEFAULT_CURSOR_SENSITIVITY = 0.01f;
	static inline constexpr float DEFAULT_FOV = 90.0f;
	static inline constexpr float MAX_FOV = 150.0f;
	static inline constexpr float MIN_PITCH = -89.0f;
	static inline constexpr float MAX_PITCH = 89.0f;
	static inline constexpr float MIN_THIRD_PERSON_DISTANCE = 0.01f;
	static inline constexpr float MAX_ACCELERATION = 10.0f;
	static inline constexpr float ACCELERATION_RESISTANCE = 0.75f;

	shared_ptr<RenderWindow> _renderWindow = nullptr;

	mat44 _view = mat44(1.0f);
	mat44 _projection = mat44(1.0f);

	fvec3 _right = fvec3(0.0f);
	fvec3 _up = fvec3(0.0f);
	fvec3 _front = fvec3(0.0f);
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _thirdPersonLookat = fvec3(0.0f);

	float _near = 0.0f;
	float _far = 0.0f;
	float _aspectRatio = 0.0f;
	float _fov = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _firstPersonYaw = 0.0f;
	float _firstPersonPitch = 0.0f;
	float _firstPersonYawAcceleration = 0.0f;
	float _firstPersonPitchAcceleration = 0.0f;
	float _minFirstPersonPitch = 0.0f;
	float _maxFirstPersonPitch = 0.0f;
	float _thirdPersonYaw = 0.0f;
	float _thirdPersonPitch = 0.0f;
	float _thirdPersonDistance = 0.0f;
	float _thirdPersonYawAcceleration = 0.0f;
	float _thirdPersonPitchAcceleration = 0.0f;
	float _minThirdPersonPitch = 0.0f;
	float _maxThirdPersonPitch = 0.0f;
	float _cursorSensitivity = 0.0f;
	float _positionTargetSpeed = 0.0f;

	bool _isThirdPersonEnabled = false;
	bool _isFirstPersonEnabled = false;
	bool _mustCenterCursor = false;
	bool _isUpInverted = false;
};
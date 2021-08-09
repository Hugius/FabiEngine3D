#pragma once

#include "render_bus.hpp"
#include "window.hpp"

using std::numeric_limits;

class Camera final
{
public:
	Camera(RenderBus& renderBus, Window& window);

	void reset();
	void update(Ivec2 lastCursorPosition);
	void updateMatrices();
	void move(Vec3 value);
	void setPosition(Vec3 value);
	void setThirdPersonLookat(Vec3 value);
	void setThirdPersonDistance(float value);
	void setFOV(float value);
	void setMouseSensitivity(float value);
	void setYaw(float value);
	void setPitch(float value);
	void setMinFirstPersonPitch(float value);
	void setMaxFirstPersonPitch(float value);
	void setMinThirdPersonPitch(float value);
	void setMaxThirdPersonPitch(float value);
	void setNearZ(float value);
	void setFarZ(float value);
	void moveFollowX(float value);
	void moveFollowZY(float value);
	void moveFollowZ(float value);
	void enableFirstPersonView(float initialYaw, float initialPitch);
	void disableFirstPersonView();
	void enableThirdPersonView(float initialYaw, float initialPitch);
	void disableThirdPersonView();
	void notifyCursorCenter();

	const Matrix44& getViewMatrix();
	const Matrix44& getProjectionMatrix();
	const Vec3 getPosition();
	const Vec3 getFront();
	const Vec3 getThirdPersonLookat();
	const float getFOV();
	const float getAspectRatio();
	const float getYaw();
	const float getPitch();
	const float getFirstPersonYaw();
	const float getFirstPersonPitch();
	const float getThirdPersonYaw();
	const float getThirdPersonPitch();
	const float getThirdPersonDistance();
	const float getNearZ();
	const float getFarZ();
	const float getMouseSensitivity();
	const float getMouseOffset();
	const bool isThirdPersonViewEnabled();
	const bool isFirstPersonViewEnabled();

private:
	// Instances
	RenderBus& _renderBus;
	Window& _window;

	// Matrices
	Matrix44 _viewMatrix = Matrix44(1.0f);
	Matrix44 _projectionMatrix = Matrix44(1.0f);

	// Vectors
	static inline const Vec3 UP_VECTOR = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 _right = Vec3(0.0f);
	Vec3 _front = Vec3(0.0f);
	Vec3 _position = Vec3(0.0f);
	Vec3 _thirdPersonLookat = Vec3(0.0f);

	// Floats
	static inline const float DEFAULT_FOV_ANGLE = 90.0f;
	static inline const float DEFAULT_NEAR_Z = 0.01f;
	static inline const float DEFAULT_FAR_Z = 3000.0f;
	static inline const float DEFAULT_MOUSE_SENSITIVITY = 0.01f;
	static inline const float MIN_PITCH_ANGLE = -89.0f;
	static inline const float MAX_PITCH_ANGLE = 89.0f;
	static inline const float MIN_THIRD_PERSON_DISTANCE = 0.01f;
	static inline const float MAX_THIRD_PERSON_DISTANCE = numeric_limits<float>::max();
	static inline const float MAX_ACCELERATION = 10.0f;
	const float _aspectRatio;
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
	float _nearZ = 0.0f;
	float _farZ = 0.0f;
	float _mouseSensitivity = 0.0f;
	float _mouseOffset = 0.0f;

	// Booleans
	bool _isThirdPersonViewEnabled = false;
	bool _isFirstPersonViewEnabled = false;
	bool _mustCenterCursor = false;
	bool _cursorIsBeingCentered = false;
};
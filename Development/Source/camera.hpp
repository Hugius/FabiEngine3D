#pragma once

#include "render_bus.hpp"
#include "window.hpp"

class Camera final
{
public:
	Camera(RenderBus& renderBus, Window& window);

	void reset();

	// Update
	void update(Ivec2 lastCursorPosition);
	void updateMatrices();

	// Setters
	void setPosition(Vec3 value);
	void setLookatPosition(Vec3 value);
	void setFOV(float value);
	void setMouseSensitivity(float value);
	void setYaw(float value);
	void setPitch(float value);
	void setNearZ(float value);
	void setFarZ(float value);
	void setMaxPitch(float value);

	// Other
	void enableLookatView();
	void disableLookatView();
	void enableFirstPersonView();
	void disableFirstPersonView();
	void translateFollowX(float speed);
	void translateFollowZY(float speed);
	void translateFollowZ(float speed);
	void translate(Vec3 translation);
	void lockYaw();
	void unlockYaw();
	void lockPitch();
	void unlockPitch();
	void notifyCursorCenter();

	// Getters
	const Matrix44 & getViewMatrix()        const;
	const Matrix44 & getProjectionMatrix()  const;
	const Vec3   getPosition()              const;
	const Vec3   getFront()                 const;
	const Vec3   getLookatPosition()        const;
	const float  getFOV()					const;
	const float  getAspectRatio()			const;
	const float  getYaw()                   const;
	const float  getPitch()                 const;
	const float  getNearZ()                 const;
	const float  getFarZ()                  const;
	const float  getMouseSensitivity()      const;
	const float  getMouseOffset()           const;
	const float  getMaxPitch()				const;
	const bool   isLookatViewEnabled()		const;
	const bool   isFirstPersonViewEnabled() const;

private:
	// Instances
	RenderBus& _renderBus;
	Window& _window;

	// Matrices
	Matrix44 _viewMatrix = Matrix44(1.0f);
	Matrix44 _projectionMatrix = Matrix44(1.0f);

	// Vectors
	static inline const Vec3 UP = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 _right = Vec3(0.0f);
	Vec3 _front = Vec3(0.0f);
	Vec3 _position = Vec3(0.0f);
	Vec3 _lookatPosition = Vec3(0.0f);

	// Floats
	static inline const float MAX_YAW_ACCELERATION = 15.0f;
	static inline const float MAX_PITCH_ACCELERATION = 15.0f;
	float _fov = 0.0f;
	float _aspectRatio = 0.0f;
	float _yawAcceleration = 0.0f;
	float _pitchAcceleration = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _nearZ = 0.0f;
	float _farZ = 0.0f;
	float _mouseSensitivity = 0.01f;
	float _mouseOffset = 0.0f;
	float _maxPitch = 0.0f;

	// Booleans
	bool _isLookatViewEabled	   = false;
	bool _isFirstPersonViewEnabled = false;
	bool _isYawLocked			   = false;
	bool _isPitchLocked			   = false;
	bool _mustCenterCursor         = false;
	bool _cursorIsBeingCentered	   = false;
};
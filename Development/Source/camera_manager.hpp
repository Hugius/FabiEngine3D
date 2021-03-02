#pragma once

#include "render_bus.hpp"
#include "window_manager.hpp"

class CameraManager final
{
public:
	CameraManager(RenderBus& renderBus, WindowManager& windowManager);
	~CameraManager() = default;

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
	void enableFreeMovement();
	void disableFreeMovement();
	void translateFollowX(float speed);
	void translateFollowZY(float speed);
	void translateFollowZ(float speed);
	void translate(Vec3 translation);
	void invertYaw();
	void invertPitch();
	void center();

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
	const bool   isFreeMovementEnabled()	const;

private:
	// Instances
	RenderBus& _renderBus;
	WindowManager& _windowManager;

	// Matrices
	Matrix44 _viewMatrix = Matrix44(1.0f);
	Matrix44 _projectionMatrix = Matrix44(1.0f);

	// Vectors
	const Vec3 _up = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 _right = Vec3(0.0f);
	Vec3 _front = Vec3(0.0f);
	Vec3 _position = Vec3(0.0f);
	Vec3 _lookatPosition = Vec3(0.0f);

	// Floats
	const float _maxYawAcceleration = 15.0f;
	const float _maxPitchAcceleration = 15.0f;
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
	bool _isLookatViewEabled		   = false;
	bool _isFirstPersonViewEnabled = false;
	bool _isFreeMovementEnabled    = true;
	bool _mustCenter               = false;
};
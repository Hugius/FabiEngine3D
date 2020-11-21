#pragma once

#include "window_manager.hpp"
#include "render_bus.hpp"

class CameraManager final
{
public:
	CameraManager(RenderBus& renderBus);
	~CameraManager() = default;

	void reset();

	// Update
	void update(WindowManager & windowManager);
	void updateMatrices();

	// Setters
	void setPosition(Vec3 val);
	void setFOV(float val);
	void setMouseSensitivity(float val);
	void setYaw(float val);
	void setPitch(float val);
	void setNearZ(float val);
	void setFarZ(float val);

	// Other
	void enableLookat(Vec3 position);
	void disableLookat();
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
	const Vec3   getLookat()                const;
	const float  getFOV()					const;
	const float  getAspectRatio()			const;
	const float  getYaw()                   const;
	const float  getPitch()                 const;
	const float  getNearZ()                 const;
	const float  getFarZ()                  const;
	const float  getMouseSensitivity()      const;
	const float  getMouseOffset()           const;
	const bool   isLookatEnabled()			const;
	const bool   isFirstPersonViewEnabled() const;
	const bool   isFreeMovementEnabled()	const;

private:
	RenderBus& _renderBus;

	// Matrices
	Matrix44 _viewMatrix = Matrix44(1.0f);
	Matrix44 _projectionMatrix = Matrix44(1.0f);

	// Vectors
	const Vec3 _up = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 _right = Vec3(0.0f);
	Vec3 _front = Vec3(0.0f);
	Vec3 _position = Vec3(0.0f);
	Vec3 _lookat = Vec3(0.0f);

	// Floats
	float _fov = 0.0f;
	float _aspectRatio = 0.0f;
	float _yawAcceleration = 0.0f;
	float _pitchAcceleration = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _nearZ = 0.0f;
	float _farZ = 0.0f;
	float _mouseSensitivity = 0.0f;
	float _mouseOffset = 0.0f;

	// Booleans
	bool _isLookatEabled		   = false;
	bool _isFirstPersonViewEnabled = false;
	bool _isFreeMovementEnabled    = true;
	bool _mustCenter               = false;
};
#pragma once

#include "window_manager.hpp"
#include "render_bus.hpp"

#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

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
	void setPosition(vec3 val);
	void setFOV(float val);
	void setMouseSensitivity(float val);
	void setYaw(float val);
	void setPitch(float val);
	void setNearZ(float val);
	void setFarZ(float val);

	// Other
	void enableLookat(vec3 position);
	void disableLookat();
	void enableFirstPersonView();
	void disableFirstPersonView();
	void enableFreeMovement();
	void disableFreeMovement();
	void translateFollowX(float speed);
	void translateFollowZY(float speed);
	void translateFollowZ(float speed);
	void translate(vec3 translation);
	void invertYaw();
	void invertPitch();
	void center();

	// Getters
	const mat4 & getViewMatrix()            const;
	const mat4 & getProjectionMatrix()      const;
	const vec3   getPosition()              const;
	const vec3   getFront()                 const;
	const vec3   getLookat()                const;
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
	mat4 _viewMatrix = mat4(1.0f);
	mat4 _projectionMatrix = mat4(1.0f);

	// Vectors
	vec3 _up = vec3(0.0f);
	vec3 _right = vec3(0.0f);
	vec3 _front = vec3(0.0f);
	vec3 _position = vec3(0.0f);
	vec3 _lookat = vec3(0.0f);

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
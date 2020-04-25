#pragma once

#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "window_manager.hpp"
#include "shader_bus.hpp"

class CameraManager final
{
public:
	CameraManager(ShaderBus& shaderBus);
	~CameraManager() = default;

	// Update
	void update(WindowManager & windowManager, float delta);
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
	void translateFollowX(float speed, float delta);
	void translateFollowZY(float speed, float delta);
	void translateFollowZ(float speed, float delta);
	void translate(vec3 translation, float delta);
	void invertYaw();
	void invertPitch();
	void center();

	// Getters
	const mat4 & getViewMatrix()            const;
	const mat4 & getProjectionMatrix()      const;
	const vec3   getPosition()              const;
	const vec3   getFront()                 const;
	const float  getYaw()                   const;
	const float  getPitch()                 const;
	const float  getMouseOffset()           const;
	const float  getFOV()					const;
	const bool   isFirstPersonViewEnabled() const;

private:
	ShaderBus& _shaderBus;

	// Matrices
	mat4 _viewMatrix = mat4(1.0f);
	mat4 _projectionMatrix = mat4(1.0f);

	// Vectors
	vec3 _up = vec3(0.0f);
	vec3 _right = vec3(0.0f);
	vec3 _front = vec3(0.0f);
	vec3 _pos = vec3(0.0f);
	vec3 _lookat = vec3(0.0f);

	// Floats
	float _fov = 0.0f;
	float _aspectRatio = 0.0f;
	float _pitch = 0.0f;
	float _yaw = 0.0f;
	float _nearZ = 0.0f;
	float _farZ = 0.0f;
	float _mouseSensitivity = 0.0f;
	float _mouseOffset = 0.0f;

	// Booleans
	bool _lookatEabled = false;
	bool _firstPersonViewEnabled = false;
	bool _freeMovementEnabled    = true;
	bool _mustCenter             = false;
};
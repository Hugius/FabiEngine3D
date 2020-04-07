#pragma once

#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "WindowManager.hpp"
#include "ShaderBus.hpp"

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
	const bool   isFirstPersonViewEnabled() const;

private:
	ShaderBus& p_shaderBus;

	// Matrices
	mat4 p_viewMatrix = mat4(1.0f);
	mat4 p_projectionMatrix = mat4(1.0f);

	// Vectors
	vec3 p_up = vec3(0.0f);
	vec3 p_right = vec3(0.0f);
	vec3 p_front = vec3(0.0f);
	vec3 p_pos = vec3(0.0f);

	// Floats
	float p_fov = 0.0f;
	float p_aspectRatio = 0.0f;
	float p_pitch = 0.0f;
	float p_yaw = 0.0f;
	float p_nearZ = 0.0f;
	float p_farZ = 0.0f;
	float p_mouseSensitivity = 0.0f;
	float p_mouseOffset = 0.0f;

	// Booleans
	bool p_firstPersonViewEnabled = false;
	bool p_freeMovementEnabled    = true;
	bool p_mustCenter             = false;
};
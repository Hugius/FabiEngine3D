#include "camera_manager.hpp"
#include "configuration.hpp"
#include "shader_bus.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>
#include <algorithm>

CameraManager::CameraManager(ShaderBus& shaderBus) :
	_shaderBus(shaderBus)
{
	_aspectRatio = float(Config::getInst().getWindowWidth()) / float(Config::getInst().getWindowHeight());
}

void CameraManager::reset()
{
	// Matrices
	_viewMatrix = mat4(1.0f);
	_projectionMatrix = mat4(1.0f);

	// Vectors
	_up = vec3(0.0f);
	_right = vec3(0.0f);
	_front = vec3(0.0f);
	_pos = vec3(0.0f);
	_lookat = vec3(0.0f);

	// Floats
	_fov = 0.0f;
	_pitch = 0.0f;
	_yaw = 0.0f;
	_nearZ = 0.0f;
	_farZ = 0.0f;
	_mouseSensitivity = 0.0f;
	_mouseOffset = 0.0f;

	// Booleans
	_lookatEabled = false;
	_firstPersonViewEnabled = false;
	_freeMovementEnabled = true;
	_mustCenter = false;
}

void CameraManager::update(WindowManager & windowManager)
{
	// Variables
	ivec2 currentMousePos = windowManager.getMousePos();
	static ivec2 lastMousePos = currentMousePos;

	if (_firstPersonViewEnabled)
	{
		// Variable
		int left = Config::getInst().getVpPos().x;
		int right = Config::getInst().getVpPos().x + Config::getInst().getVpSize().x;
		int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y);
		int top = Config::getInst().getWindowSize().y - Config::getInst().getVpPos().y;
		
		// Reset mouse position if going out of screen (horizontal)
		if (currentMousePos.x < left)
		{
			windowManager.setMousePos({ right, currentMousePos.y });
			lastMousePos.x = right;
			return;
		}
		else if (currentMousePos.x > right)
		{
			windowManager.setMousePos({ left, currentMousePos.y });
			lastMousePos.x = left;
			return;
		}

		// Reset mouse position if going out of screen (vertical)
		if (currentMousePos.y < bottom)
		{
			windowManager.setMousePos({ currentMousePos.x, top});
			lastMousePos.y = top;
			return;
		}
		else if (currentMousePos.y > top)
		{
			windowManager.setMousePos({ currentMousePos.x, bottom });
			lastMousePos.y = bottom;
			return;
		}

		// Offset between current and last mouse pos
		float xOffset = static_cast<float>(currentMousePos.x - lastMousePos.x);
		float yOffset = static_cast<float>(lastMousePos.y - currentMousePos.y);

		// Applying mouse sensitivity
		xOffset *= (_mouseSensitivity) / 100.0f;
		yOffset *= (_mouseSensitivity) / 100.0f;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Calculate pitch & yaw
		_pitch += yOffset;
		_yaw = std::fmod((_yaw + xOffset), 360.0f); // Can't be higher than 360 degrees

		// So the player cannot unnaturally vertically turn its head 
		_pitch = std::clamp(_pitch, -89.0f, 89.0f);
	}

	// Limit yaw
	if (_yaw < 0.0f)
	{
		_yaw = 360.0f - fabsf(_yaw);
	}
	_yaw = std::fmod(_yaw, 360.0f);

	// Update matrices
	updateMatrices();

	// Set last mouse position
	lastMousePos = currentMousePos;
}

void CameraManager::updateMatrices()
{
	// Normal front vector
	_front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	_front.y = sin(glm::radians(_pitch));
	_front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
	_front = glm::normalize(_front);

	// Lookat front vector
	if(_lookatEabled)
	{
		_front = _lookat;
		_front = glm::normalize(_front - _pos);
	}

	// Calculate the view matrix input
	_right = glm::normalize(glm::cross(_front, vec3(0.0f, 1.0f, 0.0f)));
	_up    = glm::normalize(glm::cross(_right, _front));

	// Projection matrix
	_projectionMatrix = glm::perspective(glm::radians(_fov), _aspectRatio, _nearZ, _farZ);

	// View matrix
	_viewMatrix[0][0] =  _right.x;
	_viewMatrix[1][0] =  _right.y;
	_viewMatrix[2][0] =  _right.z;
	_viewMatrix[0][1] =  _up.x;
	_viewMatrix[1][1] =  _up.y;
	_viewMatrix[2][1] =  _up.z;
	_viewMatrix[0][2] = -_front.x;
	_viewMatrix[1][2] = -_front.y;
	_viewMatrix[2][2] = -_front.z;
	_viewMatrix[3][0] = -glm::dot(_right, _pos);
	_viewMatrix[3][1] = -glm::dot(_up, _pos);
	_viewMatrix[3][2] =  glm::dot(_front, _pos);
	
	// Update shaderbus
	_shaderBus.setCameraYaw(_yaw);
	_shaderBus.setCameraPitch(_pitch);
	_shaderBus.setCameraPosition(_pos);
	_shaderBus.setViewMatrix(_viewMatrix);
	_shaderBus.setProjectionMatrix(_projectionMatrix);
	_shaderBus.setNearZ(_nearZ);
	_shaderBus.setFarZ(_farZ);
}

void CameraManager::translateFollowX(float speed) // Side movement
{ 
	if (_freeMovementEnabled)
	{
		_pos += _right * (speed / 100.0f);
	}
}

void CameraManager::translateFollowZ(float speed) // Forward movement
{
	if (_freeMovementEnabled)
	{
		vec3 tempFront = _front;
		tempFront.x = cos(glm::radians(_yaw));
		tempFront.z = sin(glm::radians(_yaw));
		_pos.x += tempFront.x * (speed / 100.0f);
		_pos.z += tempFront.z * (speed / 100.0f);
	}
}

void CameraManager::translateFollowZY(float speed) // Forward movement
{
	if (_freeMovementEnabled)
	{
		_pos.x += _front.x * (speed / 100.0f);
		_pos.y += _front.y * (speed / 100.0f);
		_pos.z += _front.z * (speed / 100.0f);
	}
}

void CameraManager::enableLookat(vec3 position)
{
	_lookatEabled = true;
	_lookat = position;
}

void CameraManager::disableLookat()
{
	_lookatEabled = false;
}

void CameraManager::enableFirstPersonView()
{
	_firstPersonViewEnabled = true;
}

void CameraManager::disableFirstPersonView()
{
	_firstPersonViewEnabled = false;
}

void CameraManager::enableFreeMovement()
{
	_freeMovementEnabled = true;
}

void CameraManager::disableFreeMovement()
{
	_freeMovementEnabled = false;
}

void CameraManager::setFOV(float val)
{
	_viewMatrix[3][2] = glm::dot(_front, _pos);
	_fov = val;
}

void CameraManager::setMouseSensitivity(float speed)
{
	_mouseSensitivity = speed;
}

void CameraManager::setYaw(float val)
{
	_yaw = val;
	_yaw = std::fmod(_yaw, 360.0f);
}

void CameraManager::setPitch(float val)
{
	_pitch = val;
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);
}

void CameraManager::setNearZ(float val)
{
	_nearZ = val;
}

void CameraManager::setFarZ(float val)
{
	_farZ = val;
}

const vec3 CameraManager::getPosition() const
{
	return _pos;
}

const vec3 CameraManager::getFront() const
{
	return _front;
}

const vec3 CameraManager::getLookat() const
{
	return _lookat;
}

const float CameraManager::getYaw() const
{
	return _yaw;
}

const float CameraManager::getPitch() const
{
	return _pitch;
}

const float CameraManager::getMouseOffset() const
{
	return _mouseOffset;
}

const float CameraManager::getFOV() const
{
	return _fov;
}

const bool CameraManager::isFirstPersonViewEnabled() const
{
	return _firstPersonViewEnabled;
}

const bool CameraManager::isLookatEnabled() const
{
	return _lookatEabled;
}

void CameraManager::translate(vec3 translation)
{
	if (_freeMovementEnabled)
	{
		_pos += translation;
	}
}

void CameraManager::setPosition(vec3 val)
{
	if (_freeMovementEnabled)
	{
		_pos = val;
	}
}

void CameraManager::invertYaw()
{
	_yaw = -_yaw;
}

void CameraManager::invertPitch()
{
	_pitch = -_pitch;
}

void CameraManager::center()
{
	_mustCenter = true;
}

const mat4 & CameraManager::getViewMatrix() const
{
	return _viewMatrix;
}

const mat4 & CameraManager::getProjectionMatrix() const
{
	return _projectionMatrix;
}

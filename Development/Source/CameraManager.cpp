#include <GLM/gtc/matrix_transform.hpp>
#include <algorithm>

#include "CameraManager.hpp"
#include "Configuration.hpp"
#include "ShaderBus.hpp"

CameraManager::CameraManager(ShaderBus& shaderBus) :
	_shaderBus(shaderBus)
{
	_aspectRatio = float(Config::getInst().getWindowWidth()) / float(Config::getInst().getWindowHeight());
}

void CameraManager::update(WindowManager & windowManager, float delta)
{
	if (_firstPersonViewEnabled)
	{
		// Get mouse position
		ivec2 mousePos;
		if (_mustCenter)
		{
			mousePos = Config::getInst().getWindowSize() / 2;
			_mustCenter = false;
		}
		else
		{
			mousePos = windowManager.getMousePos();
		}

		// Reset mouse position in the middle of the screen
		windowManager.setMousePos(ivec2(Config::getInst().getWindowWidth() / 2, Config::getInst().getWindowHeight() / 2));

		// Offset between current and last mouse pos
		float xoffset = float(mousePos.x)                              - float(Config::getInst().getWindowWidth() / 2);
		float yoffset = float(Config::getInst().getWindowHeight() / 2) - float(mousePos.y);

		// Applying mouse sensitivity
		xoffset *= (_mouseSensitivity * delta) / 100.0f;
		yoffset *= (_mouseSensitivity * delta) / 100.0f;

		// Calculate overall mouse offset
		_mouseOffset = (xoffset + yoffset) / 2.0f;

		// Calculate pitch & yaw
		_pitch += yoffset;
		_yaw = std::fmod((_yaw + xoffset), 360.0f); // Can't be higher than 360 degrees

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
}

void CameraManager::updateMatrices()
{
	// Front vector(look direction)
	_front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	_front.y = sin(glm::radians(_pitch));
	_front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));

	// Calculate the view matrix input
	_front = glm::normalize(_front);
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
	_shaderBus.setCameraPos(_pos);
	_shaderBus.setViewMatrix(_viewMatrix);
	_shaderBus.setProjectionMatrix(_projectionMatrix);
	_shaderBus.setNearZ(_nearZ);
	_shaderBus.setFarZ(_farZ);
}

void CameraManager::translateFollowX(float speed, float delta) // Side movement
{ 
	if (_freeMovementEnabled)
	{
		_pos += _right * ((speed * delta) / 100.0f);
	}
}

void CameraManager::translateFollowZ(float speed, float delta) // Forward movement
{
	if (_freeMovementEnabled)
	{
		vec3 tempFront = _front;
		tempFront.x = cos(glm::radians(_yaw));
		tempFront.z = sin(glm::radians(_yaw));
		_pos.x += tempFront.x * ((speed * delta) / 100.0f);
		_pos.z += tempFront.z * ((speed * delta) / 100.0f);
	}
}

void CameraManager::translateFollowZY(float speed, float delta) // Forward movement
{
	if (_freeMovementEnabled)
	{
		_pos.x += _front.x * ((speed * delta) / 100.0f);
		_pos.y += _front.y * ((speed * delta) / 100.0f);
		_pos.z += _front.z * ((speed * delta) / 100.0f);
	}
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

const bool CameraManager::isFirstPersonViewEnabled() const
{
	return _firstPersonViewEnabled;
}

void CameraManager::translate(vec3 translation, float delta)
{
	if (_freeMovementEnabled)
	{
		_pos += translation * delta;
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

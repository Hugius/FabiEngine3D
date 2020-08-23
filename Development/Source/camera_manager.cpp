#include "camera_manager.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>
#include <algorithm>

CameraManager::CameraManager(RenderBus& renderBus) :
	_renderBus(renderBus)
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
	_isLookatEabled = false;
	_isFirstPersonViewEnabled = false;
	_isFreeMovementEnabled = true;
	_mustCenter = false;
}

void CameraManager::update(WindowManager & windowManager)
{
	// Variables
	ivec2 currentMousePos = windowManager.getMousePos();
	static ivec2 lastMousePos = currentMousePos;

	if (_isFirstPersonViewEnabled)
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

		// Calculate yaw & pitch
		_yawAcceleration += xOffset;
		_pitchAcceleration += yOffset;
	}

	// Update yaw & pitch movements
	_yaw += _yawAcceleration;
	_pitch += _pitchAcceleration;
	_yawAcceleration *= 0.75f;
	_pitchAcceleration *= 0.75f;

	// Limit yaw
	if (_yaw < 0.0f)
	{
		_yaw = 360.0f - fabsf(_yaw);
	}
	_yaw = std::fmod(_yaw, 360.0f);

	// Limit pitch
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);

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
	if(_isLookatEabled)
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
	
	// Update renderbus
	_renderBus.setCameraYaw(_yaw);
	_renderBus.setCameraPitch(_pitch);
	_renderBus.setCameraPosition(_pos);
	_renderBus.setViewMatrix(_viewMatrix);
	_renderBus.setProjectionMatrix(_projectionMatrix);
	_renderBus.setNearZ(_nearZ);
	_renderBus.setFarZ(_farZ);
}

void CameraManager::translateFollowX(float speed) // Side movement
{ 
	if (_isFreeMovementEnabled)
	{
		_pos += _right * (speed / 100.0f);
	}
}

void CameraManager::translateFollowZ(float speed) // Forward movement
{
	if (_isFreeMovementEnabled)
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
	if (_isFreeMovementEnabled)
	{
		_pos.x += _front.x * (speed / 100.0f);
		_pos.y += _front.y * (speed / 100.0f);
		_pos.z += _front.z * (speed / 100.0f);
	}
}

void CameraManager::enableLookat(vec3 position)
{
	_isLookatEabled = true;
	_lookat = position;
}

void CameraManager::disableLookat()
{
	_isLookatEabled = false;
}

void CameraManager::enableFirstPersonView(float mouseSensitivity)
{
	_isFirstPersonViewEnabled = true;
	_mouseSensitivity = mouseSensitivity;
}

void CameraManager::disableFirstPersonView()
{
	_isFirstPersonViewEnabled = false;
}

void CameraManager::enableFreeMovement()
{
	_isFreeMovementEnabled = true;
}

void CameraManager::disableFreeMovement()
{
	_isFreeMovementEnabled = false;
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

const float CameraManager::getNearZ() const
{
	return _nearZ;
}

const float CameraManager::getFarZ() const
{
	return _farZ;
}

const float CameraManager::getMouseSensitivity() const
{
	return _mouseSensitivity;
}

const float CameraManager::getMouseOffset() const
{
	return _mouseOffset;
}

const float CameraManager::getFOV() const
{
	return _fov;
}

const float CameraManager::getAspectRatio() const
{
	return _aspectRatio;
}

const bool CameraManager::isFirstPersonViewEnabled() const
{
	return _isFirstPersonViewEnabled;
}

const bool CameraManager::isFreeMovementEnabled() const
{
	return _isFreeMovementEnabled;
}

const bool CameraManager::isLookatEnabled() const
{
	return _isLookatEabled;
}

void CameraManager::translate(vec3 translation)
{
	if (_isFreeMovementEnabled)
	{
		_pos += translation;
	}
}

void CameraManager::setPosition(vec3 val)
{
	if (_isFreeMovementEnabled)
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

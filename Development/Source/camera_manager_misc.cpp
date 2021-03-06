#include "camera_manager.hpp"
#include "configuration.hpp"

#include <algorithm>

void CameraManager::translateFollowX(float speed) // Side movement
{ 
	if (_isFreeMovementEnabled)
	{
		_position += (_right * speed);
	}
}

void CameraManager::translateFollowZ(float speed) // Forward movement
{
	if (_isFreeMovementEnabled)
	{
		Vec3 tempFront = _front;
		tempFront.x = cos(Math::degreesToRadians(_yaw));
		tempFront.z = sin(Math::degreesToRadians(_yaw));
		_position.x += (tempFront.x * speed);
		_position.z += (tempFront.z * speed);
	}
}

void CameraManager::translateFollowZY(float speed) // Forward movement
{
	if (_isFreeMovementEnabled)
	{
		_position.x += (_front.x * speed);
		_position.y += (_front.y * speed);
		_position.z += (_front.z * speed);
	}
}

void CameraManager::enableLookatView()
{
	_isLookatViewEabled = true;
}

void CameraManager::disableLookatView()
{
	_isLookatViewEabled = false;
}

void CameraManager::enableFirstPersonView()
{
	// Only center first time
	if (!_isFirstPersonViewEnabled)
	{
		_mustCenter = true;
	}

	_isFirstPersonViewEnabled = true;
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

void CameraManager::setFOV(float value)
{
	_viewMatrix.m[3][2] = _front.dot(_position);
	_fov = value;
}

void CameraManager::setMouseSensitivity(float speed)
{
	_mouseSensitivity = speed;
}

void CameraManager::setYaw(float value)
{
	_yaw = value;
	_yaw = std::fmodf(_yaw, 360.0f);
}

void CameraManager::setPitch(float value)
{
	_pitch = value;
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);
}

void CameraManager::setNearZ(float value)
{
	_nearZ = value;
}

void CameraManager::setFarZ(float value)
{
	_farZ = value;
}

void CameraManager::setMaxPitch(float value)
{
	_maxPitch = value;
}

const Vec3 CameraManager::getPosition() const
{
	return _position;
}

const Vec3 CameraManager::getFront() const
{
	return _front;
}

const Vec3 CameraManager::getLookatPosition() const
{
	return _lookatPosition;
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

const float CameraManager::getMaxPitch() const
{
	return _maxPitch;
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

const bool CameraManager::isLookatViewEnabled() const
{
	return _isLookatViewEabled;
}

void CameraManager::translate(Vec3 translation)
{
	if (_isFreeMovementEnabled)
	{
		_position += translation;
	}
}

void CameraManager::setPosition(Vec3 value)
{
	if (_isFreeMovementEnabled)
	{
		_position = value;
	}
}

void CameraManager::setLookatPosition(Vec3 value)
{
	_lookatPosition = value;
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

const Matrix44 & CameraManager::getViewMatrix() const
{
	return _viewMatrix;
}

const Matrix44 & CameraManager::getProjectionMatrix() const
{
	return _projectionMatrix;
}
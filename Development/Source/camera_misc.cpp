#include "camera.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

void Camera::translateFollowX(float value)
{ 
	_position += (_right * value);
}

void Camera::translateFollowZ(float value)
{
	Vec3 tempFront = _front;
	tempFront.x = cos(Math::degreesToRadians(_yaw));
	tempFront.z = sin(Math::degreesToRadians(_yaw));
	_position.x += (tempFront.x * value);
	_position.z += (tempFront.z * value);
}

void Camera::translateFollowZY(float value)
{
	_position.x += (_front.x * value);
	_position.y += (_front.y * value);
	_position.z += (_front.z * value);
}

void Camera::enableFirstPersonView(float initialYaw, float initialPitch)
{
	if (_isThirdPersonViewEnabled)
	{
		Logger::throwWarning("Tried to enable first person view: third person view already enabled!");
	}
	else if (_isFirstPersonViewEnabled)
	{
		Logger::throwWarning("Tried to enable first person view: already enabled!");
	}
	else
	{
		_firstPersonYaw = initialYaw;
		_firstPersonPitch = initialPitch;
		_mustCenterCursor = true;
		_isFirstPersonViewEnabled = true;
	}
}

void Camera::disableFirstPersonView()
{
	if (_isFirstPersonViewEnabled)
	{
		_isFirstPersonViewEnabled = false;
	}
	else
	{
		Logger::throwWarning("Tried to disable first person view: not enabled!");
	}
}

void Camera::enableThirdPersonView(float initialYaw, float initialPitch, float initialDistance)
{
	if (_isFirstPersonViewEnabled)
	{
		Logger::throwWarning("Tried to enable third person view: first person view already enabled!");
	}
	else if (_isThirdPersonViewEnabled)
	{
		Logger::throwWarning("Tried to enable third person view: already enabled!");
	}
	else
	{
		_thirdPersonYaw = initialYaw;
		_thirdPersonPitch = initialPitch;
		_thirdPersonDistance = initialDistance;
		_mustCenterCursor = true;
		_isThirdPersonViewEnabled = true;
	}
}

void Camera::disableThirdPersonView()
{
	if (_isThirdPersonViewEnabled)
	{
		_isThirdPersonViewEnabled = false;
	}
	else
	{
		Logger::throwWarning("Tried to disable third person view: not enabled!");
	}
}

void Camera::setFOV(float value)
{
	_viewMatrix.m[3][2] = _front.dot(_position);
	_fov = value;
}

void Camera::setMouseSensitivity(float speed)
{
	_mouseSensitivity = speed;
}

void Camera::setYaw(float value)
{
	_yaw = value;
	_yaw = std::fmodf(_yaw, 360.0f);
}

void Camera::setPitch(float value)
{
	_pitch = value;
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);
}

void Camera::setNearZ(float value)
{
	_nearZ = value;
}

void Camera::setFarZ(float value)
{
	_farZ = value;
}

void Camera::setMinFirstPersonPitch(float value)
{
	_minFirstPersonPitch = value;
}

void Camera::setMaxFirstPersonPitch(float value)
{
	_maxFirstPersonPitch = value;
}

void Camera::setMinThirdPersonPitch(float value)
{
	_minThirdPersonPitch = value;
}

void Camera::setMaxThirdPersonPitch(float value)
{
	_maxThirdPersonPitch = value;
}

void Camera::setMinThirdPersonDistance(float value)
{
	_minThirdPersonDistance = value;
}

void Camera::setMaxThirdPersonDistance(float value)
{
	_maxThirdPersonDistance = value;
}

const Vec3 Camera::getPosition()
{
	return _position;
}

const Vec3 Camera::getFront()
{
	return _front;
}

const float Camera::getFirstPersonYaw()
{
	return _yaw;
}

const float Camera::getFirstPersonPitch()
{
	return _pitch;
}

const float Camera::getNearZ()
{
	return _nearZ;
}

const float Camera::getFarZ()
{
	return _farZ;
}

const float Camera::getMouseSensitivity()
{
	return _mouseSensitivity;
}

const float Camera::getMouseOffset()
{
	return _mouseOffset;
}

const float Camera::getThirdPersonYaw()
{
	return _thirdPersonYaw;
}

const float Camera::getThirdPersonPitch()
{
	return _thirdPersonPitch;
}

const float Camera::getThirdPersonDistance()
{
	return _thirdPersonDistance;
}

const float Camera::getFOV()
{
	return _fov;
}

const float Camera::getAspectRatio()
{
	return _aspectRatio;
}

const float Camera::getYaw()
{
	return _yaw;
}

const float Camera::getPitch()
{
	return _pitch;
}

const bool Camera::isFirstPersonViewEnabled()
{
	return _isFirstPersonViewEnabled;
}

const bool Camera::isThirdPersonViewEnabled()
{
	return _isThirdPersonViewEnabled;
}

void Camera::translate(Vec3 value)
{
	_position += value;
}

void Camera::setPosition(Vec3 value)
{
	_position = value;
}

void Camera::setThirdPersonLookat(Vec3 value)
{
	_thirdPersonLookat = value;
}

void Camera::notifyCursorCenter()
{
	_cursorIsBeingCentered = true;
}

const Matrix44& Camera::getViewMatrix()
{
	return _viewMatrix;
}

const Matrix44& Camera::getProjectionMatrix()
{
	return _projectionMatrix;
}
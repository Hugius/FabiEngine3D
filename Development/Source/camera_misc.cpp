#include "camera.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

void Camera::translateFollowX(float speed)
{ 
	_position += (_right * speed);
}

void Camera::translateFollowZ(float speed)
{
	Vec3 tempFront = _front;
	tempFront.x = cos(Math::degreesToRadians(_yaw));
	tempFront.z = sin(Math::degreesToRadians(_yaw));
	_position.x += (tempFront.x * speed);
	_position.z += (tempFront.z * speed);
}

void Camera::translateFollowZY(float speed)
{
	_position.x += (_front.x * speed);
	_position.y += (_front.y * speed);
	_position.z += (_front.z * speed);
}

void Camera::enableFirstPersonView()
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

void Camera::enableThirdPersonView()
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

void Camera::setMaxPitch(float value)
{
	_maxPitch = value;
}

void Camera::setThirdPersonDistance(float value)
{
	_thirdPersonDistance = value;
}

const Vec3 Camera::getPosition()
{
	return _position;
}

const Vec3 Camera::getFront()
{
	return _front;
}

const Vec3 Camera::getLookatPosition()
{
	return _lookatPosition;
}

const float Camera::getYaw()
{
	return _yaw;
}

const float Camera::getPitch()
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

const float Camera::getMaxPitch()
{
	return _maxPitch;
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

const bool Camera::isFirstPersonViewEnabled()
{
	return _isFirstPersonViewEnabled;
}

const bool Camera::isLookatViewEnabled()
{
	return _isThirdPersonViewEnabled;
}

void Camera::translate(Vec3 translation)
{
	_position += translation;
}

void Camera::setPosition(Vec3 value)
{
	_position = value;
}

void Camera::setLookatPosition(Vec3 value)
{
	_lookatPosition = value;
}

void Camera::lockYaw()
{
	_isYawLocked = true;
}

void Camera::unlockYaw()
{
	_isYawLocked = false;
}

void Camera::lockPitch()
{
	_isPitchLocked = true;
}

void Camera::unlockPitch()
{
	_isPitchLocked = false;
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
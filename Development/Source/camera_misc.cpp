#include "camera.hpp"
#include "configuration.hpp"

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

void Camera::enableLookatView()
{
	if (!_isFirstPersonViewEnabled)
	{
		_isLookatViewEabled = true;
	}
}

void Camera::disableLookatView()
{
	_isLookatViewEabled = false;
}

void Camera::enableFirstPersonView()
{
	if (!_isLookatViewEabled)
	{
		// Only center first time
		if (!_isFirstPersonViewEnabled)
		{
			_mustCenterCursor = true;
		}

		_isFirstPersonViewEnabled = true;
	}
}

void Camera::disableFirstPersonView()
{
	_isFirstPersonViewEnabled = false;
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

const Vec3 Camera::getPosition() const
{
	return _position;
}

const Vec3 Camera::getFront() const
{
	return _front;
}

const Vec3 Camera::getLookatPosition() const
{
	return _lookatPosition;
}

const float Camera::getYaw() const
{
	return _yaw;
}

const float Camera::getPitch() const
{
	return _pitch;
}

const float Camera::getNearZ() const
{
	return _nearZ;
}

const float Camera::getFarZ() const
{
	return _farZ;
}

const float Camera::getMouseSensitivity() const
{
	return _mouseSensitivity;
}

const float Camera::getMouseOffset() const
{
	return _mouseOffset;
}

const float Camera::getMaxPitch() const
{
	return _maxPitch;
}

const float Camera::getFOV() const
{
	return _fov;
}

const float Camera::getAspectRatio() const
{
	return _aspectRatio;
}

const bool Camera::isFirstPersonViewEnabled() const
{
	return _isFirstPersonViewEnabled;
}

const bool Camera::isLookatViewEnabled() const
{
	return _isLookatViewEabled;
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

const Matrix44 & Camera::getViewMatrix() const
{
	return _viewMatrix;
}

const Matrix44 & Camera::getProjectionMatrix() const
{
	return _projectionMatrix;
}
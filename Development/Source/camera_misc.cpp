#include "camera.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void Camera::moveFollowX(float value)
{ 
	_position += (_rightVector * value);
}

void Camera::moveFollowZ(float value)
{
	Vec3 tempFront = _frontVector;
	tempFront.x = cos(Math::degreesToRadians(_yaw));
	tempFront.z = sin(Math::degreesToRadians(_yaw));
	_position.x += (tempFront.x * value);
	_position.z += (tempFront.z * value);
}

void Camera::moveFollowZY(float value)
{
	_position.x += (_frontVector.x * value);
	_position.y += (_frontVector.y * value);
	_position.z += (_frontVector.z * value);
}

void Camera::enableFirstPersonView(float initialYaw, float initialPitch)
{
	if (_isThirdPersonViewEnabled)
	{
		Logger::throwError("Camera::enableFirstPersonView::1");
	}
	if (_isFirstPersonViewEnabled)
	{
		Logger::throwError("Camera::enableFirstPersonView::2");
	}

	_firstPersonYaw = initialYaw;
	_firstPersonPitch = initialPitch;
	_mustCenterCursor = true;
	_isFirstPersonViewEnabled = true;
}

void Camera::disableFirstPersonView()
{
	if (!_isFirstPersonViewEnabled)
	{
		Logger::throwError("Camera::disableFirstPersonView");
	}

	_isFirstPersonViewEnabled = false;
}

void Camera::enableThirdPersonView(float initialYaw, float initialPitch)
{
	if (_isFirstPersonViewEnabled)
	{
		Logger::throwError("Camera::enableThirdPersonView::1");
	}
	if (_isThirdPersonViewEnabled)
	{
		Logger::throwError("Camera::enableThirdPersonView::2");
	}

	_thirdPersonYaw = initialYaw;
	_thirdPersonPitch = initialPitch;
	_mustCenterCursor = true;
	_isThirdPersonViewEnabled = true;
}

void Camera::disableThirdPersonView()
{
	if (!_isThirdPersonViewEnabled)
	{
		Logger::throwError("Camera::disableThirdPersonView");
	}

	_isThirdPersonViewEnabled = false;
}

void Camera::setFOV(float value)
{
	_viewMatrix.m[3][2] = _frontVector.dot(_position);
	_fov = value;
}

void Camera::setMouseSensitivity(float speed)
{
	_mouseSensitivity = speed;
}

void Camera::setYaw(float value)
{
	_yaw = value;
	_yaw = fmodf(_yaw, 360.0f);
}

void Camera::setPitch(float value)
{
	_pitch = value;
	_pitch = clamp(_pitch, -89.0f, 89.0f);
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

void Camera::setThirdPersonDistance(float value)
{
	_thirdPersonDistance = value;
}

void Camera::setAspectRatio(float value)
{
	_aspectRatio = value;
}

const Vec3 Camera::getPosition()
{
	return _position;
}

const Vec3 Camera::getFrontVector()
{
	return _frontVector;
}

const Vec3 Camera::getThirdPersonLookat()
{
	return _thirdPersonLookat;
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

void Camera::move(Vec3 value)
{
	_position += value;
}

void Camera::setUpVector(Vec3 value)
{
	_upVector = value;
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

const Vec3 Camera::getUpVector()
{
	return _upVector;
}
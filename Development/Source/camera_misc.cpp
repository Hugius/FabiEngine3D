#include "camera.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Camera::moveFollowX(float value)
{ 
	_position += (_rightVector * value);
}

void Camera::moveFollowZ(float value)
{
	Vec3 tempFront = _frontVector;
	tempFront.x = cos(Math::convertToRadians(_yaw));
	tempFront.z = sin(Math::convertToRadians(_yaw));
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

	_firstPersonYaw = Math::limitAngle(initialYaw);
	_firstPersonPitch = clamp(clamp(initialPitch, _minFirstPersonPitch, _maxFirstPersonPitch), MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
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

	_thirdPersonYaw = Math::limitAngle(initialYaw);
	_thirdPersonPitch = clamp(clamp(initialPitch, _minThirdPersonPitch, _maxThirdPersonPitch), MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
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
	_fov = max(0.0f, value);
}

void Camera::setCursorSensitivity(float value)
{
	_cursorSensitivity = max(0.0f, value);
}

void Camera::setYaw(float value)
{
	_yaw = Math::limitAngle(value);
}

void Camera::setPitch(float value)
{
	_pitch = clamp(value, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
}

void Camera::setNearZ(float value)
{
	_nearZ = max(0.0f, value);
}

void Camera::setFarZ(float value)
{
	_farZ = max(0.0f, value);
}

void Camera::setMinFirstPersonPitch(float value)
{
	_minFirstPersonPitch = clamp(value, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
}

void Camera::setMaxFirstPersonPitch(float value)
{
	_maxFirstPersonPitch = clamp(value, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
}

void Camera::setMinThirdPersonPitch(float value)
{
	_minThirdPersonPitch = clamp(value, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
}

void Camera::setMaxThirdPersonPitch(float value)
{
	_maxThirdPersonPitch = clamp(value, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
}

void Camera::setThirdPersonDistance(float value)
{
	_thirdPersonDistance = max(0.0f, value);
}

void Camera::setAspectRatio(float value)
{
	_aspectRatio = max(0.0f, value);
}

const Vec3 Camera::getPosition()
{
	return _position;
}

const Vec3 Camera::getFrontVector()
{
	return _frontVector;
}

const Vec3 Camera::getRightVector()
{
	return _rightVector;
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

const float Camera::getCursorSensitivity()
{
	return _cursorSensitivity;
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
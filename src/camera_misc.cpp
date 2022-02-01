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
	fvec3 tempFront = _frontVector;
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

void Camera::setFirstPersonViewEnabled(bool value)
{
	_mustCenterCursor = value;
	_isFirstPersonViewEnabled = value;
}

void Camera::setThirdPersonViewEnabled(bool value)
{
	_mustCenterCursor = value;
	_isThirdPersonViewEnabled = value;
}

void Camera::setFOV(float value)
{
	_fov = clamp(value, 0.0f, MAX_FOV_ANGLE);
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

void Camera::setFirstPersonYaw(float value)
{
	_firstPersonYaw = Math::limitAngle(value);
}

void Camera::setFirstPersonPitch(float value)
{
	_firstPersonPitch = clamp(clamp(value, _minFirstPersonPitch, _maxFirstPersonPitch), MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
}

void Camera::setThirdPersonYaw(float value)
{
	_thirdPersonYaw = Math::limitAngle(value);
}

void Camera::setThirdPersonPitch(float value)
{
	_thirdPersonPitch = clamp(clamp(value, _minThirdPersonPitch, _maxThirdPersonPitch), MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
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
	_thirdPersonDistance = max(value, MIN_THIRD_PERSON_DISTANCE);
}

void Camera::setAspectRatio(float value)
{
	_aspectRatio = max(0.0f, value);
}

const fvec3& Camera::getPosition() const
{
	return _position;
}

const fvec3& Camera::getFrontVector() const
{
	return _frontVector;
}

const fvec3& Camera::getRightVector() const
{
	return _rightVector;
}

const fvec3& Camera::getThirdPersonLookat() const
{
	return _thirdPersonLookat;
}

const float Camera::getFirstPersonYaw() const
{
	return _yaw;
}

const float Camera::getFirstPersonPitch() const
{
	return _pitch;
}

const float Camera::getMinFirstPersonPitch() const
{
	return _minFirstPersonPitch;
}

const float Camera::getMaxFirstPersonPitch() const
{
	return _maxFirstPersonPitch;
}

const float Camera::getNearDistance() const
{
	return NEAR_DISTANCE;
}

const float Camera::getFarDistance() const
{
	return FAR_DISTANCE;
}

const float Camera::getCursorSensitivity() const
{
	return _cursorSensitivity;
}

const float Camera::getThirdPersonYaw() const
{
	return _thirdPersonYaw;
}

const float Camera::getThirdPersonPitch() const
{
	return _thirdPersonPitch;
}

const float Camera::getMinThirdPersonPitch() const
{
	return _minThirdPersonPitch;
}

const float Camera::getMaxThirdPersonPitch() const
{
	return _maxThirdPersonPitch;
}

const float Camera::getThirdPersonDistance() const
{
	return _thirdPersonDistance;
}

const float Camera::getFOV() const
{
	return _fov;
}

const float Camera::getAspectRatio() const
{
	return _aspectRatio;
}

const float Camera::getYaw() const
{
	return _yaw;
}

const float Camera::getPitch() const
{
	return _pitch;
}

const bool Camera::isFirstPersonViewEnabled() const
{
	return _isFirstPersonViewEnabled;
}

const bool Camera::isThirdPersonViewEnabled() const
{
	return _isThirdPersonViewEnabled;
}

void Camera::move(const fvec3& value)
{
	_position += value;
}

void Camera::setPosition(const fvec3& value)
{
	_position = value;
}

void Camera::setThirdPersonLookat(const fvec3& value)
{
	_thirdPersonLookat = value;
}

void Camera::notifyCursorCenter()
{
	_cursorIsBeingCentered = true;
}

const mat44& Camera::getViewMatrix() const
{
	return _viewMatrix;
}

const mat44& Camera::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const fvec3& Camera::getUpVector() const
{
	return _upVector;
}

void Camera::updateMatrices()
{
	_upVector = DEFAULT_UP_VECTOR;

	_frontVector.x = (cos(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_frontVector.y = sin(Math::convertToRadians(_pitch));
	_frontVector.z = (sin(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_frontVector = Math::normalize(_frontVector);

	_rightVector = Math::calculateCrossProduct(_frontVector, _upVector);
	_rightVector = Math::normalize(_rightVector);

	_viewMatrix = Math::createViewMatrix(_position, (_position + _frontVector), _upVector);

	_projectionMatrix = Math::createPerspectiveProjectionMatrix(Math::convertToRadians(_fov), _aspectRatio, NEAR_DISTANCE, FAR_DISTANCE);

	_renderBus->setCameraUpVector(_upVector);
	_renderBus->setCameraFrontVector(_frontVector);
	_renderBus->setCameraRightVector(_rightVector);
	_renderBus->setCameraViewMatrix(_viewMatrix);
	_renderBus->setCameraProjectionMatrix(_projectionMatrix);
}
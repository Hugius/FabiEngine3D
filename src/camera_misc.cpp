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

void Camera::enableFirstPersonView(float initialYaw, float initialPitch)
{
	if(_isThirdPersonViewEnabled)
	{
		Logger::throwError("Camera::enableFirstPersonView::1");
	}
	if(_isFirstPersonViewEnabled)
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
	if(!_isFirstPersonViewEnabled)
	{
		Logger::throwError("Camera::disableFirstPersonView");
	}

	_isFirstPersonViewEnabled = false;
}

void Camera::enableThirdPersonView(float initialYaw, float initialPitch)
{
	if(_isFirstPersonViewEnabled)
	{
		Logger::throwError("Camera::enableThirdPersonView::1");
	}
	if(_isThirdPersonViewEnabled)
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
	if(!_isThirdPersonViewEnabled)
	{
		Logger::throwError("Camera::disableThirdPersonView");
	}

	_isThirdPersonViewEnabled = false;
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

const fvec3 Camera::getPosition() const
{
	return _position;
}

const fvec3 Camera::getFrontVector() const
{
	return _frontVector;
}

const fvec3 Camera::getRightVector() const
{
	return _rightVector;
}

const fvec3 Camera::getThirdPersonLookat() const
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
	return _nearDistance;
}

const float Camera::getFarDistance() const
{
	return _farDistance;
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

void Camera::move(fvec3 value)
{
	_position += value;
}

void Camera::invertUpVector()
{
	_upVector *= -1.0f;
}

void Camera::setPosition(fvec3 value)
{
	_position = value;
}

void Camera::setThirdPersonLookat(fvec3 value)
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

const fvec3 Camera::getUpVector() const
{
	return _upVector;
}

void Camera::updateMatrices()
{
	_frontVector.x = (cos(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_frontVector.y = sin(Math::convertToRadians(_pitch));
	_frontVector.z = (sin(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_frontVector = Math::normalize(_frontVector);

	_rightVector = Math::calculateCrossProduct(_frontVector, _upVector);
	_rightVector = Math::normalize(_rightVector);

	_viewMatrix = Math::createViewMatrix(_position, (_position + _frontVector), _upVector);

	_projectionMatrix = Math::createPerspectiveProjectionMatrix(Math::convertToRadians(_fov), _aspectRatio, _nearDistance, _farDistance);

	_renderBus.setCameraYaw(_yaw);
	_renderBus.setCameraPitch(_pitch);
	_renderBus.setCameraFront(_frontVector);
	_renderBus.setCameraPosition(_position);
	_renderBus.setViewMatrix(_viewMatrix);
	_renderBus.setProjectionMatrix(_projectionMatrix);
	_renderBus.setNearDistance(_nearDistance);
	_renderBus.setFarDistance(_farDistance);
}
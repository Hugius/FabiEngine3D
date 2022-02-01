#include "camera.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Camera::moveFollowX(float value)
{
	_position += (_right * value);
}

void Camera::moveFollowZ(float value)
{
	fvec3 tempFront = _front;
	tempFront.x = cos(Math::convertToRadians(_yaw));
	tempFront.z = sin(Math::convertToRadians(_yaw));
	_position.x += (tempFront.x * value);
	_position.z += (tempFront.z * value);
}

void Camera::moveFollowZY(float value)
{
	_position.x += (_front.x * value);
	_position.y += (_front.y * value);
	_position.z += (_front.z * value);
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

const fvec3& Camera::getFront() const
{
	return _front;
}

const fvec3& Camera::getRight() const
{
	return _right;
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

const float Camera::getNear() const
{
	return DEFAULT_NEAR_DISTANCE;
}

const float Camera::getFar() const
{
	return DEFAULT_FAR_DISTANCE;
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

const mat44& Camera::getView() const
{
	return _view;
}

const mat44& Camera::getProjection() const
{
	return _projection;
}

const fvec3& Camera::getUp() const
{
	return _up;
}

void Camera::updateMatrices()
{
	_up = DEFAULT_UP;

	_front.x = (cos(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_front.y = sin(Math::convertToRadians(_pitch));
	_front.z = (sin(Math::convertToRadians(_yaw)) * cos(Math::convertToRadians(_pitch)));
	_front = Math::normalize(_front);

	_right = Math::calculateCrossProduct(_front, _up);
	_right = Math::normalize(_right);

	_view = Math::createViewMatrix(_position, (_position + _front), _up);

	_projection = Math::createPerspectiveProjectionMatrix(Math::convertToRadians(_fov), _aspectRatio, _near, _far);

	_renderBus->setCameraUp(_up);
	_renderBus->setCameraFront(_front);
	_renderBus->setCameraRight(_right);
	_renderBus->setCameraView(_view);
	_renderBus->setCameraProjection(_projection);
}
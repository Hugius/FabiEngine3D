#include "camera.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Camera::followRightXZ(float speed)
{
	_position.x += (_right.x * speed);
	_position.z += (_right.z * speed);
}

void Camera::followFrontXZ(float speed)
{
	fvec3 tempFront = _front;
	tempFront.x = cos(Mathematics::convertToRadians(_yaw));
	tempFront.z = sin(Mathematics::convertToRadians(_yaw));

	_position.x += (tempFront.x * speed);
	_position.z += (tempFront.z * speed);
}

void Camera::followFrontXYZ(float speed)
{
	_position.x += (_front.x * speed);
	_position.y += (_front.y * speed);
	_position.z += (_front.z * speed);
}

void Camera::setFirstPersonEnabled(bool value)
{
	_mustCenterCursor = value;
	_isFirstPersonEnabled = value;
}

void Camera::setThirdPersonEnabled(bool value)
{
	_mustCenterCursor = value;
	_isThirdPersonEnabled = value;
}

void Camera::setFov(float value)
{
	_fov = clamp(value, 0.0f, MAX_FOV);
}

void Camera::setCursorSensitivity(float value)
{
	_cursorSensitivity = max(0.0f, value);
}

void Camera::setYaw(float value)
{
	_yaw = Mathematics::limitAngle(value);
}

void Camera::setPitch(float value)
{
	_pitch = clamp(value, MIN_PITCH, MAX_PITCH);
}

void Camera::setFirstPersonYaw(float value)
{
	_firstPersonYaw = Mathematics::limitAngle(value);
}

void Camera::setFirstPersonPitch(float value)
{
	_firstPersonPitch = clamp(clamp(value, _minFirstPersonPitch, _maxFirstPersonPitch), MIN_PITCH, MAX_PITCH);
}

void Camera::setThirdPersonYaw(float value)
{
	_thirdPersonYaw = Mathematics::limitAngle(value);
}

void Camera::setThirdPersonPitch(float value)
{
	_thirdPersonPitch = clamp(clamp(value, _minThirdPersonPitch, _maxThirdPersonPitch), MIN_PITCH, MAX_PITCH);
}

void Camera::setMinFirstPersonPitch(float value)
{
	_minFirstPersonPitch = clamp(value, MIN_PITCH, MAX_PITCH);
}

void Camera::setMaxFirstPersonPitch(float value)
{
	_maxFirstPersonPitch = clamp(value, MIN_PITCH, MAX_PITCH);
}

void Camera::setMinThirdPersonPitch(float value)
{
	_minThirdPersonPitch = clamp(value, MIN_PITCH, MAX_PITCH);
}

void Camera::setMaxThirdPersonPitch(float value)
{
	_maxThirdPersonPitch = clamp(value, MIN_PITCH, MAX_PITCH);
}

void Camera::setThirdPersonDistance(float value)
{
	_thirdPersonDistance = max(MIN_THIRD_PERSON_DISTANCE, value);
}

void Camera::setAspectRatio(float value)
{
	_aspectRatio = max(0.0f, value);
}

const fvec3 & Camera::getPosition() const
{
	return _position;
}

const fvec3 & Camera::getFront() const
{
	return _front;
}

const fvec3 & Camera::getRight() const
{
	return _right;
}

const fvec3 & Camera::getThirdPersonLookat() const
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
	return DEFAULT_NEAR;
}

const float Camera::getFar() const
{
	return DEFAULT_FAR;
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

const float Camera::getFov() const
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

const bool Camera::isFirstPersonEnabled() const
{
	return _isFirstPersonEnabled;
}

const bool Camera::isThirdPersonEnabled() const
{
	return _isThirdPersonEnabled;
}

void Camera::move(const fvec3 & speed)
{
	_position += speed;
}

void Camera::setPosition(const fvec3 & value)
{
	_position = value;
}

void Camera::setThirdPersonLookat(const fvec3 & value)
{
	_thirdPersonLookat = value;
}

void Camera::notifyCursorCenter()
{
	_isCursorBeingCentered = true;
}

void Camera::invertUp()
{
	_isUpInverted = !_isUpInverted;
}

const mat44 & Camera::getView() const
{
	return _view;
}

const mat44 & Camera::getProjection() const
{
	return _projection;
}

const fvec3 & Camera::getUp() const
{
	return _up;
}

void Camera::updateMatrices()
{
	if(_isUpInverted)
	{
		_up = INVERTED_UP;
	}
	else
	{
		_up = DEFAULT_UP;
	}

	_front.x = (cos(Mathematics::convertToRadians(_yaw)) * cos(Mathematics::convertToRadians(_pitch)));
	_front.y = sin(Mathematics::convertToRadians(_pitch));
	_front.z = (sin(Mathematics::convertToRadians(_yaw)) * cos(Mathematics::convertToRadians(_pitch)));
	_front = Mathematics::normalize(_front);

	_right = Mathematics::calculateCrossProduct(_front, _up);
	_right = Mathematics::normalize(_right);

	_view = Mathematics::createViewMatrix(_position, (_position + _front), _up);

	_projection = Mathematics::createPerspectiveProjectionMatrix(Mathematics::convertToRadians(_fov), _aspectRatio, _near, _far);
}
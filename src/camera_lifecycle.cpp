#include "camera.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

Camera::Camera()
{
	reset();
}

void Camera::inject(shared_ptr<RenderWindow> renderWindow)
{
	_renderWindow = renderWindow;
}

void Camera::reset()
{
	_view = fmat44(1.0f);
	_projection = fmat44(1.0f);
	_up = fvec3(0.0f);
	_front = fvec3(0.0f);
	_right = fvec3(0.0f);
	_position = fvec3(0.0f);
	_thirdPersonLookat = fvec3(0.0f);
	_aspectRatio = Tools::getDisplayAspectRatio();
	_fov = DEFAULT_FOV;
	_cursorSensitivity = DEFAULT_CURSOR_SENSITIVITY;
	_minFirstPersonPitch = MIN_PITCH;
	_maxFirstPersonPitch = MAX_PITCH;
	_minThirdPersonPitch = MIN_PITCH;
	_maxThirdPersonPitch = MAX_PITCH;
	_near = DEFAULT_NEAR;
	_far = DEFAULT_FAR;
	_yaw = 0.0f;
	_pitch = 0.0f;
	_firstPersonYaw = 0.0f;
	_firstPersonPitch = 0.0f;
	_thirdPersonYaw = 0.0f;
	_thirdPersonPitch = 0.0f;
	_firstPersonYawAcceleration = 0.0f;
	_firstPersonPitchAcceleration = 0.0f;
	_thirdPersonYawAcceleration = 0.0f;
	_thirdPersonPitchAcceleration = 0.0f;
	_thirdPersonDistance = 0.0f;
	_accelerationResistance = 0.0f;
	_isFirstPersonEnabled = false;
	_isThirdPersonEnabled = false;
	_mustCenterCursor = false;
}

void Camera::update()
{
	const auto currentCursorPosition = Tools::getCursorPosition();
	const auto centerCursorPosition = Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));

	if(_position != _positionTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_positionTarget - _position);

		_position += (speedMultiplier * _positionTargetSpeed);

		if(fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}

		if(fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}

		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}

	if(_isFirstPersonEnabled && !_mustCenterCursor)
	{
		auto xOffset = static_cast<float>(currentCursorPosition.x - centerCursorPosition.x);
		auto yOffset = static_cast<float>(currentCursorPosition.y - centerCursorPosition.y);

		xOffset *= _cursorSensitivity;
		yOffset *= _cursorSensitivity;

		_firstPersonYawAcceleration += xOffset;
		_firstPersonYaw += _firstPersonYawAcceleration;
		_firstPersonYawAcceleration *= _accelerationResistance;
		_firstPersonPitchAcceleration += yOffset;
		_firstPersonPitch += _firstPersonPitchAcceleration;
		_firstPersonPitchAcceleration *= _accelerationResistance;
		_firstPersonYaw = Mathematics::limitAngle(_firstPersonYaw);
		_firstPersonPitch = clamp(clamp(_firstPersonPitch, _minFirstPersonPitch, _maxFirstPersonPitch), MIN_PITCH, MAX_PITCH);
		_yaw = _firstPersonYaw;
		_pitch = _firstPersonPitch;

		Tools::setCursorPosition(centerCursorPosition);
	}
	else
	{
		_firstPersonYawAcceleration = 0.0f;
		_firstPersonPitchAcceleration = 0.0f;
	}

	if(_isThirdPersonEnabled && !_mustCenterCursor)
	{
		auto xOffset = static_cast<float>(currentCursorPosition.x - centerCursorPosition.x);
		auto yOffset = static_cast<float>(currentCursorPosition.y - centerCursorPosition.y);

		xOffset *= _cursorSensitivity;
		yOffset *= _cursorSensitivity;

		_thirdPersonYawAcceleration += xOffset;
		_thirdPersonYaw -= _thirdPersonYawAcceleration;
		_thirdPersonYawAcceleration *= _accelerationResistance;
		_thirdPersonPitchAcceleration += yOffset;
		_thirdPersonPitch -= _thirdPersonPitchAcceleration;
		_thirdPersonPitchAcceleration *= _accelerationResistance;
		_thirdPersonYaw = Mathematics::limitAngle(_thirdPersonYaw);
		_thirdPersonPitch = clamp(clamp(_thirdPersonPitch, _minThirdPersonPitch, _maxThirdPersonPitch), MIN_PITCH, MAX_PITCH);

		const auto xMultiplier = cos(Mathematics::convertToRadians(_thirdPersonPitch)) * sin(Mathematics::convertToRadians(_thirdPersonYaw));
		const auto yMultiplier = sin(Mathematics::convertToRadians(_thirdPersonPitch));
		const auto zMultiplier = cos(Mathematics::convertToRadians(_thirdPersonPitch)) * cos(Mathematics::convertToRadians(_thirdPersonYaw));

		_position.x = (_thirdPersonLookat.x + (_thirdPersonDistance * xMultiplier));
		_position.y = (_thirdPersonLookat.y + (_thirdPersonDistance * yMultiplier));
		_position.z = (_thirdPersonLookat.z + (_thirdPersonDistance * zMultiplier));

		_yaw = (Mathematics::convertToDegrees(atan2f((_position.z - _thirdPersonLookat.z), (_position.x - _thirdPersonLookat.x))) + 180.0f);
		_pitch = -_thirdPersonPitch;

		Tools::setCursorPosition(centerCursorPosition);
	}
	else
	{
		_thirdPersonYawAcceleration = 0.0f;
		_thirdPersonPitchAcceleration = 0.0f;
	}

	if(_mustCenterCursor)
	{
		Tools::setCursorPosition(centerCursorPosition);

		_mustCenterCursor = false;
	}

	_yaw = Mathematics::limitAngle(_yaw);
	_pitch = clamp(_pitch, MIN_PITCH, MAX_PITCH);

	calculateMatrices();
}
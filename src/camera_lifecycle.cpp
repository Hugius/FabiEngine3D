#include "camera.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Camera::Camera()
{
	reset();
}

void Camera::reset()
{
	_viewMatrix = mat44(1.0f);
	_projectionMatrix = mat44(1.0f);

	_upVector = DEFAULT_UP_VECTOR;
	_frontVector = fvec3(0.0f);
	_rightVector = fvec3(0.0f);
	_position = fvec3(0.0f);
	_thirdPersonLookat = fvec3(0.0f);

	_aspectRatio = static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y);
	_fov = DEFAULT_FOV_ANGLE;
	_nearDistance = NEAR_DISTANCE;
	_farDistance = FAR_DISTANCE;
	_cursorSensitivity = DEFAULT_CURSOR_SENSITIVITY;
	_minFirstPersonPitch = MIN_PITCH_ANGLE;
	_maxFirstPersonPitch = MAX_PITCH_ANGLE;
	_minThirdPersonPitch = MIN_PITCH_ANGLE;
	_maxThirdPersonPitch = MAX_PITCH_ANGLE;
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

	_isFirstPersonViewEnabled = false;
	_isThirdPersonViewEnabled = false;
	_mustCenterCursor = false;
	_cursorIsBeingCentered = false;
}

void Camera::update(RenderBus& renderBus, RenderWindow& renderWindow, ivec2 lastCursorPosition)
{
	const auto currentCursorPosition = renderWindow.getCursorPosition();
	const auto left = Config::getInst().getViewportPosition().x;
	const auto bottom = Config::getInst().getWindowSize().y - (Config::getInst().getViewportPosition().y + Config::getInst().getViewportSize().y);
	const auto xMiddle = left + (Config::getInst().getViewportSize().x / 2);
	const auto yMiddle = bottom + (Config::getInst().getViewportSize().y / 2);

	if(_mustCenterCursor)
	{
		renderWindow.setCursorPosition({xMiddle, yMiddle});
		_mustCenterCursor = false;
		_cursorIsBeingCentered = true;
	}

	if(_cursorIsBeingCentered)
	{
		if(currentCursorPosition == ivec2(xMiddle, yMiddle) || currentCursorPosition != lastCursorPosition)
		{
			_cursorIsBeingCentered = false;
		}
	}

	if(_isFirstPersonViewEnabled && !_cursorIsBeingCentered)
	{
		float xOffset = static_cast<float>(currentCursorPosition.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currentCursorPosition.y);

		xOffset *= _cursorSensitivity;
		yOffset *= _cursorSensitivity;

		_firstPersonYawAcceleration += xOffset;
		_firstPersonYawAcceleration = clamp(_firstPersonYawAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonYaw += _firstPersonYawAcceleration;
		_firstPersonYawAcceleration *= 0.75f;

		_firstPersonPitchAcceleration += yOffset;
		_firstPersonPitchAcceleration = clamp(_firstPersonPitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonPitch += _firstPersonPitchAcceleration;
		_firstPersonPitch = clamp(_firstPersonPitch, _minFirstPersonPitch, _maxFirstPersonPitch);
		_firstPersonPitchAcceleration *= 0.75f;

		_firstPersonYaw = Math::limitAngle(_firstPersonYaw);
		_firstPersonPitch = clamp(_firstPersonPitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

		_yaw = _firstPersonYaw;
		_pitch = _firstPersonPitch;

		renderWindow.setCursorPosition({xMiddle, yMiddle});
	}
	else
	{
		_firstPersonYawAcceleration = 0.0f;
		_firstPersonPitchAcceleration = 0.0f;
	}

	if(_isThirdPersonViewEnabled && !_cursorIsBeingCentered)
	{
		float xOffset = static_cast<float>(currentCursorPosition.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currentCursorPosition.y);

		xOffset *= _cursorSensitivity;
		yOffset *= _cursorSensitivity;

		_thirdPersonYawAcceleration += xOffset;
		_thirdPersonYawAcceleration = clamp(_thirdPersonYawAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonYaw -= _thirdPersonYawAcceleration;
		_thirdPersonYaw = Math::limitAngle(_thirdPersonYaw);
		_thirdPersonYawAcceleration *= 0.75f;

		_thirdPersonPitchAcceleration += yOffset;
		_thirdPersonPitchAcceleration = clamp(_thirdPersonPitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonPitch -= _thirdPersonPitchAcceleration;
		_thirdPersonPitch = clamp(_thirdPersonPitch, _minThirdPersonPitch, _maxThirdPersonPitch);
		_thirdPersonPitch = clamp(_thirdPersonPitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
		_thirdPersonPitchAcceleration *= 0.75f;

		_thirdPersonDistance = max(MIN_THIRD_PERSON_DISTANCE, _thirdPersonDistance);

		float xMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * sin(Math::convertToRadians(_thirdPersonYaw));
		float yMultiplier = sin(Math::convertToRadians(_thirdPersonPitch));
		float zMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * cos(Math::convertToRadians(_thirdPersonYaw));

		_thirdPersonDistance = max(0.0f, _thirdPersonDistance);

		_position.x = _thirdPersonLookat.x + (_thirdPersonDistance * xMultiplier);
		_position.y = _thirdPersonLookat.y + (_thirdPersonDistance * yMultiplier);
		_position.z = _thirdPersonLookat.z + (_thirdPersonDistance * zMultiplier);

		_yaw = Math::convertToDegrees(atan2f(_position.z - _thirdPersonLookat.z, _position.x - _thirdPersonLookat.x)) + 180.0f;
		_pitch = -(_thirdPersonPitch);

		renderWindow.setCursorPosition({xMiddle, yMiddle});
	}
	else
	{
		_thirdPersonYawAcceleration = 0.0f;
		_thirdPersonPitchAcceleration = 0.0f;
	}

	_yaw = Math::limitAngle(_yaw);
	_pitch = clamp(_pitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

	updateMatrices(renderBus);
}
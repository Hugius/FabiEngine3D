#include "camera.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Camera::Camera()
{
	reset();
}

void Camera::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

void Camera::inject(shared_ptr<RenderWindow> renderWindow)
{
	_renderWindow = renderWindow;
}

void Camera::reset()
{
	_view = mat44(1.0f);
	_projection = mat44(1.0f);

	_up = fvec3(0.0f);
	_front = fvec3(0.0f);
	_right = fvec3(0.0f);
	_position = fvec3(0.0f);
	_thirdPersonLookat = fvec3(0.0f);

	_aspectRatio = static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y);
	_fov = DEFAULT_FOV_ANGLE;
	_cursorSensitivity = DEFAULT_CURSOR_SENSITIVITY;
	_minFirstPersonPitch = MIN_PITCH_ANGLE;
	_maxFirstPersonPitch = MAX_PITCH_ANGLE;
	_minThirdPersonPitch = MIN_PITCH_ANGLE;
	_maxThirdPersonPitch = MAX_PITCH_ANGLE;
	_near = DEFAULT_NEAR_DISTANCE;
	_far = DEFAULT_FAR_DISTANCE;
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

void Camera::update(const ivec2& lastCursorPosition)
{
	const auto currentCursorPosition = _renderWindow->getCursorPosition();
	const auto left = Config::getInst().getViewportPosition().x;
	const auto bottom = Config::getInst().getWindowSize().y - (Config::getInst().getViewportPosition().y + Config::getInst().getViewportSize().y);
	const auto xMiddle = left + (Config::getInst().getViewportSize().x / 2);
	const auto yMiddle = bottom + (Config::getInst().getViewportSize().y / 2);

	if(_mustCenterCursor)
	{
		_renderWindow->setCursorPosition({xMiddle, yMiddle});
		_mustCenterCursor = false;
		_cursorIsBeingCentered = true;
	}

	if(_cursorIsBeingCentered)
	{
		if((currentCursorPosition == ivec2(xMiddle, yMiddle)) || (currentCursorPosition != lastCursorPosition))
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
		_firstPersonYawAcceleration *= ACCELERATION_RESISTANCE;

		_firstPersonPitchAcceleration += yOffset;
		_firstPersonPitchAcceleration = clamp(_firstPersonPitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonPitch += _firstPersonPitchAcceleration;
		_firstPersonPitchAcceleration *= ACCELERATION_RESISTANCE;

		_firstPersonYaw = Math::limitAngle(_firstPersonYaw);
		_firstPersonPitch = clamp(clamp(_firstPersonPitch, _minFirstPersonPitch, _maxFirstPersonPitch), MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

		_yaw = _firstPersonYaw;
		_pitch = _firstPersonPitch;

		_renderWindow->setCursorPosition({xMiddle, yMiddle});
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
		_thirdPersonYawAcceleration *= ACCELERATION_RESISTANCE;

		_thirdPersonPitchAcceleration += yOffset;
		_thirdPersonPitchAcceleration = clamp(_thirdPersonPitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonPitch -= _thirdPersonPitchAcceleration;
		_thirdPersonPitchAcceleration *= ACCELERATION_RESISTANCE;

		_thirdPersonYaw = Math::limitAngle(_thirdPersonYaw);
		_thirdPersonPitch = clamp(clamp(_thirdPersonPitch, _minThirdPersonPitch, _maxThirdPersonPitch), MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

		const auto xMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * sin(Math::convertToRadians(_thirdPersonYaw));
		const auto yMultiplier = sin(Math::convertToRadians(_thirdPersonPitch));
		const auto zMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * cos(Math::convertToRadians(_thirdPersonYaw));

		_position.x = _thirdPersonLookat.x + (_thirdPersonDistance * xMultiplier);
		_position.y = _thirdPersonLookat.y + (_thirdPersonDistance * yMultiplier);
		_position.z = _thirdPersonLookat.z + (_thirdPersonDistance * zMultiplier);

		_yaw = Math::convertToDegrees(atan2f(_position.z - _thirdPersonLookat.z, _position.x - _thirdPersonLookat.x)) + 180.0f;
		_pitch = -_thirdPersonPitch;

		_renderWindow->setCursorPosition({xMiddle, yMiddle});
	}
	else
	{
		_thirdPersonYawAcceleration = 0.0f;
		_thirdPersonPitchAcceleration = 0.0f;
	}

	_yaw = Math::limitAngle(_yaw);
	_pitch = clamp(_pitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

	_renderBus->setCameraYaw(_yaw);
	_renderBus->setCameraPitch(_pitch);
	_renderBus->setCameraPosition(_position);
	_renderBus->setCameraNear(_near);
	_renderBus->setCameraFar(_far);
}
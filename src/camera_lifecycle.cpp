#include "camera.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <algorithm>

using std::max;
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
	_view = mat44(1.0f);
	_projection = mat44(1.0f);

	_up = fvec3(0.0f);
	_front = fvec3(0.0f);
	_right = fvec3(0.0f);
	_position = fvec3(0.0f);
	_thirdPersonLookat = fvec3(0.0f);

	_aspectRatio = static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y);
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

	_isFirstPersonEnabled = false;
	_isThirdPersonEnabled = false;
	_mustCenterCursor = false;
	_isCursorBeingCentered = false;
}

void Camera::update(const ivec2& lastCursorPosition)
{
	const auto currentCursorPosition = _renderWindow->getCursorPosition();
	const auto middle = Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));

	if(_mustCenterCursor)
	{
		_renderWindow->setCursorPosition(middle);
		_mustCenterCursor = false;
		_isCursorBeingCentered = true;
	}

	if(_isCursorBeingCentered)
	{
		if((currentCursorPosition == middle) || (currentCursorPosition != lastCursorPosition))
		{
			_isCursorBeingCentered = false;
		}
	}

	if(_isFirstPersonEnabled && !_isCursorBeingCentered)
	{
		auto xOffset = static_cast<float>(currentCursorPosition.x - middle.x);
		auto yOffset = static_cast<float>(currentCursorPosition.y - middle.y);

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
		_firstPersonPitch = clamp(clamp(_firstPersonPitch, _minFirstPersonPitch, _maxFirstPersonPitch), MIN_PITCH, MAX_PITCH);

		_yaw = _firstPersonYaw;
		_pitch = _firstPersonPitch;

		_renderWindow->setCursorPosition(middle);
	}
	else
	{
		_firstPersonYawAcceleration = 0.0f;
		_firstPersonPitchAcceleration = 0.0f;
	}

	if(_isThirdPersonEnabled && !_isCursorBeingCentered)
	{
		auto xOffset = static_cast<float>(currentCursorPosition.x - middle.x);
		auto yOffset = static_cast<float>(currentCursorPosition.y - middle.y);

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
		_thirdPersonPitch = clamp(clamp(_thirdPersonPitch, _minThirdPersonPitch, _maxThirdPersonPitch), MIN_PITCH, MAX_PITCH);

		const auto xMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * sin(Math::convertToRadians(_thirdPersonYaw));
		const auto yMultiplier = sin(Math::convertToRadians(_thirdPersonPitch));
		const auto zMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * cos(Math::convertToRadians(_thirdPersonYaw));

		_position.x = (_thirdPersonLookat.x + (_thirdPersonDistance * xMultiplier));
		_position.y = (_thirdPersonLookat.y + (_thirdPersonDistance * yMultiplier));
		_position.z = (_thirdPersonLookat.z + (_thirdPersonDistance * zMultiplier));

		_yaw = (Math::convertToDegrees(atan2f((_position.z - _thirdPersonLookat.z), (_position.x - _thirdPersonLookat.x))) + 180.0f);
		_pitch = -_thirdPersonPitch;

		_renderWindow->setCursorPosition(middle);
	}
	else
	{
		_thirdPersonYawAcceleration = 0.0f;
		_thirdPersonPitchAcceleration = 0.0f;
	}

	_yaw = Math::limitAngle(_yaw);
	_pitch = clamp(_pitch, MIN_PITCH, MAX_PITCH);
}
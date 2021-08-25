#include "camera.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Camera::Camera(RenderBus& renderBus, Window& window)
	:
	_renderBus(renderBus),
	_window(window)
{
	reset();
}

void Camera::reset()
{
	// Matrices
	_viewMatrix = Matrix44(1.0f);
	_projectionMatrix = Matrix44(1.0f);

	// Vectors
	_upVector = DEFAULT_UP_VECTOR;
	_frontVector = Vec3(0.0f);
	_rightVector = Vec3(0.0f);
	_position = Vec3(0.0f);
	_thirdPersonLookat = Vec3(0.0f);

	// Floats
	_aspectRatio = static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y);
	_fov = DEFAULT_FOV_ANGLE;
	_nearZ = DEFAULT_NEAR_Z;
	_farZ = DEFAULT_FAR_Z;
	_mouseSensitivity = DEFAULT_MOUSE_SENSITIVITY;
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
	_mouseOffset = 0.0f;

	// Booleans
	_isFirstPersonViewEnabled = false;
	_isThirdPersonViewEnabled = false;
	_mustCenterCursor = false;
	_cursorIsBeingCentered = false;
}

void Camera::update(Ivec2 lastCursorPosition)
{
	// Temporary values
	Ivec2 currenCursorPosition = _window.getCursorPosition();
	const int left = Config::getInst().getVpPos().x;
	const int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y);
	const int xMiddle = left + (Config::getInst().getVpSize().x / 2);
	const int yMiddle = bottom + (Config::getInst().getVpSize().y / 2);

	// Update cursor centering
	if (_mustCenterCursor)
	{
		_window.setCursorPosition({ xMiddle, yMiddle });
		_mustCenterCursor = false;
		_cursorIsBeingCentered = true;
	}

	// Check if cursor reached center or cursor moved
	if (_cursorIsBeingCentered)
	{
		if (currenCursorPosition == Ivec2(xMiddle, yMiddle) || currenCursorPosition != lastCursorPosition)
		{
			_cursorIsBeingCentered = false;
		}
	}

	// Update first person camera
	if (_isFirstPersonViewEnabled && !_cursorIsBeingCentered)
	{
		// Offset between current mouse position & middle of the screen
		float xOffset = static_cast<float>(currenCursorPosition.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currenCursorPosition.y);

		// Applying mouse sensitivity
		xOffset *= _mouseSensitivity;
		yOffset *= _mouseSensitivity;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Update yaw
		_firstPersonYawAcceleration += xOffset;
		_firstPersonYawAcceleration = clamp(_firstPersonYawAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonYaw += _firstPersonYawAcceleration;
		_firstPersonYawAcceleration *= 0.75f;

		// Update pitch
		_firstPersonPitchAcceleration += yOffset;
		_firstPersonPitchAcceleration = clamp(_firstPersonPitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonPitch += _firstPersonPitchAcceleration;
		_firstPersonPitch = clamp(_firstPersonPitch, _minFirstPersonPitch, _maxFirstPersonPitch);
		_firstPersonPitchAcceleration *= 0.75f;

		// Limit view angles
		_firstPersonYaw = fmodf(_firstPersonYaw, 360.0f);
		_firstPersonPitch = clamp(_firstPersonPitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

		// Set view angles
		_yaw = _firstPersonYaw;
		_pitch = _firstPersonPitch;

		// Spawn mouse in middle of screen
		_window.setCursorPosition({ xMiddle, yMiddle });
	}
	else
	{
		_firstPersonYawAcceleration = 0.0f;
		_firstPersonPitchAcceleration = 0.0f;
	}

	// Update third person camera
	if (_isThirdPersonViewEnabled && !_cursorIsBeingCentered)
	{
		// Offset between current mouse position & middle of the screen
		float xOffset = static_cast<float>(currenCursorPosition.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currenCursorPosition.y);

		// Applying mouse sensitivity
		xOffset *= _mouseSensitivity;
		yOffset *= _mouseSensitivity;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Update yaw
		_thirdPersonYawAcceleration += xOffset;
		_thirdPersonYawAcceleration = clamp(_thirdPersonYawAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonYaw -= _thirdPersonYawAcceleration;
		_thirdPersonYaw = fmodf(_thirdPersonYaw, 360.0f);
		_thirdPersonYawAcceleration *= 0.75f;
		
		// Update pitch
		_thirdPersonPitchAcceleration += yOffset;
		_thirdPersonPitchAcceleration = clamp(_thirdPersonPitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonPitch -= _thirdPersonPitchAcceleration;
		_thirdPersonPitch = clamp(_thirdPersonPitch, _minThirdPersonPitch, _maxThirdPersonPitch);
		_thirdPersonPitch = clamp(_thirdPersonPitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
		_thirdPersonPitchAcceleration *= 0.75f;

		// Update distance
		_thirdPersonDistance = clamp(_thirdPersonDistance, MIN_THIRD_PERSON_DISTANCE, MAX_THIRD_PERSON_DISTANCE);

		// Calculate position multipliers
		float xMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * sin(Math::convertToRadians(_thirdPersonYaw));
		float yMultiplier = sin(Math::convertToRadians(_thirdPersonPitch));
		float zMultiplier = cos(Math::convertToRadians(_thirdPersonPitch)) * cos(Math::convertToRadians(_thirdPersonYaw));

		// Limit view distance
		_thirdPersonDistance = max(0.0f, _thirdPersonDistance);
		
		// Calculate camera position
		_position.x = _thirdPersonLookat.x + (_thirdPersonDistance * xMultiplier);
		_position.y = _thirdPersonLookat.y + (_thirdPersonDistance * yMultiplier);
		_position.z = _thirdPersonLookat.z + (_thirdPersonDistance * zMultiplier);

		// Set view angles
		_yaw = Math::convertToDegrees(atan2f(_position.z - _thirdPersonLookat.z, _position.x - _thirdPersonLookat.x)) + 180.0f;
		_pitch = -(_thirdPersonPitch);

		// Spawn mouse in middle of screen
		_window.setCursorPosition({ xMiddle, yMiddle });
	}
	else
	{
		_thirdPersonYawAcceleration = 0.0f;
		_thirdPersonPitchAcceleration = 0.0f;
	}

	// Limit view angles
	_yaw = fmodf(_yaw, 360.0f);
	_pitch = clamp(_pitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

	// Update matrices
	updateMatrices();
}

void Camera::updateMatrices()
{
	// Lookat front vector
	_frontVector.x = cos(Math::convertToRadians(_pitch)) * cos(Math::convertToRadians(_yaw));
	_frontVector.y = sin(Math::convertToRadians(_pitch));
	_frontVector.z = cos(Math::convertToRadians(_pitch)) * sin(Math::convertToRadians(_yaw));
	_frontVector.normalize();

	// Calculate the view matrix input
	_rightVector = _frontVector.cross(_upVector);
	_rightVector.normalize();

	// View matrix
	_viewMatrix = Matrix44::createView(_position, _position + _frontVector, _upVector);

	// Projection matrix
	_projectionMatrix = Matrix44::createProjection(Math::convertToRadians(_fov), _aspectRatio, _nearZ, _farZ);

	// Update renderbus
	_renderBus.setCameraYaw(_yaw);
	_renderBus.setCameraPitch(_pitch);
	_renderBus.setCameraFront(_frontVector);
	_renderBus.setCameraPosition(_position);
	_renderBus.setViewMatrix(_viewMatrix);
	_renderBus.setProjectionMatrix(_projectionMatrix);
	_renderBus.setNearZ(_nearZ);
	_renderBus.setFarZ(_farZ);
}
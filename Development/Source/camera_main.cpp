#include "camera.hpp"
#include "configuration.hpp"

#include <algorithm>
#include <iostream>

Camera::Camera(RenderBus& renderBus, Window& window) :
	_renderBus(renderBus),
	_window(window),
	_aspectRatio(static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y))
{
	//reset();
}

void Camera::reset()
{
	// Matrices
	_viewMatrix = Matrix44(1.0f);
	_projectionMatrix = Matrix44(1.0f);

	// Vectors
	_position = Vec3(0.0f);
	_thirdPersonLookat = Vec3(0.0f);
	_right = Vec3(0.0f);
	_front = Vec3(0.0f);

	// Floats
	_fov = DEFAULT_FOV_ANGLE;
	_nearZ = DEFAULT_NEAR_Z;
	_farZ = DEFAULT_FAR_Z;
	_mouseSensitivity = DEFAULT_MOUSE_SENSITIVITY;
	_minFirstPersonPitch = MIN_PITCH_ANGLE;
	_maxFirstPersonPitch = MAX_PITCH_ANGLE;
	_minThirdPersonPitch = MIN_PITCH_ANGLE;
	_maxThirdPersonPitch = MAX_PITCH_ANGLE;
	_minThirdPersonDistance = MIN_THIRD_PERSON_DISTANCE;
	_maxThirdPersonDistance = MAX_THIRD_PERSON_DISTANCE;
	_yaw = 0.0f;
	_pitch = 0.0f;
	_firstPersonYaw = 0.0f;
	_firstPersonPitch = 0.0f;
	_thirdPersonYaw = 0.0f;
	_thirdPersonPitch = 0.0f;
	_yawAcceleration = 0.0f;
	_pitchAcceleration = 0.0f;
	_mouseOffset = 0.0f;
	_thirdPersonDistance = 0.0f;

	// Booleans
	_isFirstPersonViewEnabled = false;
	_isThirdPersonViewEnabled = false;
	_mustCenterCursor = false;
	_cursorIsBeingCentered = false;
}

void Camera::update(Ivec2 lastCursorPosition, int mouseWheelDirection)
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
		_yawAcceleration += xOffset;
		_yawAcceleration = std::clamp(_yawAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonYaw += _yawAcceleration;
		_yawAcceleration *= 0.75f;

		// Update pitch
		_pitchAcceleration += yOffset;
		_pitchAcceleration = std::clamp(_pitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_firstPersonPitch += _pitchAcceleration;
		_firstPersonPitch = std::clamp(_firstPersonPitch, _minFirstPersonPitch, _maxFirstPersonPitch);
		_pitchAcceleration *= 0.75f;

		// Limit view angles
		_firstPersonYaw = std::fmodf(_firstPersonYaw, 360.0f);
		_firstPersonPitch = std::clamp(_firstPersonPitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

		// Set view angles
		_yaw = _firstPersonYaw;
		_pitch = _firstPersonPitch;

		// Spawn mouse in middle of screen
		_window.setCursorPosition({ xMiddle, yMiddle });
	}

	// Update third person camera
	if (_isThirdPersonViewEnabled && !_cursorIsBeingCentered)
	{
		// Offset between current mouse position & middle of the screen
		float xOffset = static_cast<float>(currenCursorPosition.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currenCursorPosition.y);
		float scrollOffset = static_cast<float>(mouseWheelDirection);

		// Applying mouse sensitivity
		xOffset *= _mouseSensitivity;
		yOffset *= _mouseSensitivity;
		scrollOffset *= _mouseSensitivity;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Update yaw
		_yawAcceleration += xOffset;
		_yawAcceleration = std::clamp(_yawAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonYaw -= _yawAcceleration;
		_thirdPersonYaw = std::fmodf(_thirdPersonYaw, 360.0f);
		_yawAcceleration *= 0.75f;
		
		// Update pitch
		_pitchAcceleration += yOffset;
		_pitchAcceleration = std::clamp(_pitchAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonPitch -= _pitchAcceleration;
		_thirdPersonPitch = std::clamp(_thirdPersonPitch, _minThirdPersonPitch, _maxThirdPersonPitch);
		_thirdPersonPitch = std::clamp(_thirdPersonPitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);
		_pitchAcceleration *= 0.75f;

		// Update distance
		_distanceAcceleration += (scrollOffset * 5.0f);
		_distanceAcceleration = std::clamp(_distanceAcceleration, -MAX_ACCELERATION, MAX_ACCELERATION);
		_thirdPersonDistance -= _distanceAcceleration;
		_thirdPersonDistance = std::clamp(_thirdPersonDistance, _minThirdPersonDistance, _maxThirdPersonDistance);
		_thirdPersonDistance = std::clamp(_thirdPersonDistance, MIN_THIRD_PERSON_DISTANCE, MAX_THIRD_PERSON_DISTANCE);
		_distanceAcceleration *= 0.75f;

		// Calculate position multipliers
		float xMultiplier = cos(Math::degreesToRadians(_thirdPersonPitch)) * sin(Math::degreesToRadians(_thirdPersonYaw));
		float yMultiplier = sin(Math::degreesToRadians(_thirdPersonPitch));
		float zMultiplier = cos(Math::degreesToRadians(_thirdPersonPitch)) * cos(Math::degreesToRadians(_thirdPersonYaw));

		// Limit view distance
		_thirdPersonDistance = std::max(0.0f, _thirdPersonDistance);
		
		// Calculate camera position
		_position.x = _thirdPersonLookat.x + (_thirdPersonDistance * xMultiplier);
		_position.y = _thirdPersonLookat.y + (_thirdPersonDistance * yMultiplier);
		_position.z = _thirdPersonLookat.z + (_thirdPersonDistance * zMultiplier);

		// Set view angles
		_yaw = Math::radiansToDegrees(atan2f(_position.z - _thirdPersonLookat.z, _position.x - _thirdPersonLookat.x)) + 180.0f;
		_pitch = -(_thirdPersonPitch);

		// Spawn mouse in middle of screen
		_window.setCursorPosition({ xMiddle, yMiddle });
	}

	// Limit view angles
	_yaw = std::fmodf(_yaw, 360.0f);
	_pitch = std::clamp(_pitch, MIN_PITCH_ANGLE, MAX_PITCH_ANGLE);

	// Update matrices
	updateMatrices();
}

void Camera::updateMatrices()
{
	// Lookat front vector
	_front.x = cos(Math::degreesToRadians(_pitch)) * cos(Math::degreesToRadians(_yaw));
	_front.y = sin(Math::degreesToRadians(_pitch));
	_front.z = cos(Math::degreesToRadians(_pitch)) * sin(Math::degreesToRadians(_yaw));
	_front.normalize();

	// Calculate the view matrix input
	_right = _front.cross(UP_VECTOR);
	_right.normalize();

	// View matrix
	_viewMatrix = Matrix44::createView(_position, _position + _front, UP_VECTOR);

	// Projection matrix
	_projectionMatrix = Matrix44::createProjection(Math::degreesToRadians(_fov), _aspectRatio, _nearZ, _farZ);

	// Update renderbus
	_renderBus.setCameraYaw(_yaw);
	_renderBus.setCameraPitch(_pitch);
	_renderBus.setCameraFront(_front);
	_renderBus.setCameraPosition(_position);
	_renderBus.setViewMatrix(_viewMatrix);
	_renderBus.setProjectionMatrix(_projectionMatrix);
	_renderBus.setNearZ(_nearZ);
	_renderBus.setFarZ(_farZ);
}
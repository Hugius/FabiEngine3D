#include "camera.hpp"
#include "configuration.hpp"

#include <algorithm>
#include <iostream>

Camera::Camera(RenderBus& renderBus, Window& window) :
	_renderBus(renderBus),
	_window(window)
{
	_aspectRatio = static_cast<float>(Config::getInst().getWindowSize().x) / static_cast<float>(Config::getInst().getWindowSize().y);
}

void Camera::reset()
{
	// Matrices
	_viewMatrix = Matrix44(1.0f);
	_projectionMatrix = Matrix44(1.0f);

	// Vectors
	_right = Vec3(0.0f);
	_front = Vec3(0.0f);
	_position = Vec3(0.0f);
	_lookatPosition = Vec3(0.0f);

	// Floats
	_fov = 0.0f;
	_yawAcceleration = 0.0f;
	_pitchAcceleration = 0.0f;
	_yaw = 0.0f;
	_pitch = 0.0f;
	_nearZ = 0.0f;
	_farZ = 0.0f;
	_mouseSensitivity = 0.01f;
	_mouseOffset = 0.0f;
	_maxPitch = 90.0f;

	// Booleans
	_isThirdPersonViewEnabled = false;
	_isFirstPersonViewEnabled = false;
	_isYawLocked = false;
	_isPitchLocked = false;
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
		if (!_isYawLocked)
		{
			_yawAcceleration += xOffset;
			_yawAcceleration = std::clamp(_yawAcceleration, -MAX_YAW_ACCELERATION, MAX_YAW_ACCELERATION);
			_yaw += _yawAcceleration;
			_yawAcceleration *= 0.75f;
		}

		// Update pitch
		if (!_isPitchLocked)
		{
			_pitchAcceleration += yOffset;
			_pitchAcceleration = std::clamp(_pitchAcceleration, -MAX_PITCH_ACCELERATION, MAX_PITCH_ACCELERATION);
			_pitch += _pitchAcceleration;
			_pitchAcceleration *= 0.75f;
		}

		// Spawn mouse in middle of screen
		_window.setCursorPosition({ xMiddle, yMiddle });
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

		// Update horizontal angle
		if (!_isYawLocked)
		{
			_thirdPersonHorizontalAngle += xOffset;
		}

		// Update vertical angle
		if (!_isPitchLocked)
		{
			_thirdPersonVerticalAngle -= yOffset;
		}

		// Limit angles
		_thirdPersonHorizontalAngle = std::fmodf(_thirdPersonHorizontalAngle, 360.0f);
		_thirdPersonVerticalAngle = std::clamp(_thirdPersonVerticalAngle, -90.0f, 90.0f);

		// Calculate position multipliers
		float xMultiplier = cos(Math::degreesToRadians(_thirdPersonVerticalAngle) * sin(Math::degreesToRadians(_thirdPersonHorizontalAngle)));
		float yMultiplier = sin(Math::degreesToRadians(_thirdPersonVerticalAngle));
		float zMultiplier = cos(Math::degreesToRadians(_thirdPersonHorizontalAngle)) * cos(Math::degreesToRadians(_thirdPersonVerticalAngle));
		
		// Calculate camera position
		_position.x = (_thirdPersonDistance * xMultiplier);
		_position.y = (_thirdPersonDistance * yMultiplier);
		_position.z = (_thirdPersonDistance * zMultiplier);

		// Calculate yaw
		_yaw = Math::radiansToDegrees(atan2f(_position.z, _position.x)) + 180.0f;

		// Calculate pitch
		_pitch = sin(Math::degreesToRadians(_thirdPersonVerticalAngle)) * -90.0f;

		// Spawn mouse in middle of screen
		_window.setCursorPosition({ xMiddle, yMiddle });
	}

	// Limit yaw
	_yaw = std::fmodf(_yaw, 360.0f);

	// Limit pitch
	_pitch = std::clamp(_pitch, -(_maxPitch - 1.0f), (_maxPitch - 1.0f));

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
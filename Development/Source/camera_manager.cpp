#include "camera_manager.hpp"
#include "configuration.hpp"

#include <algorithm>
#include <iostream>

CameraManager::CameraManager(RenderBus& renderBus, WindowManager& windowManager) :
	_renderBus(renderBus),
	_windowManager(windowManager)
{
	_aspectRatio = static_cast<float>(Config::getInst().getWindowWidth()) / static_cast<float>(Config::getInst().getWindowHeight());
}

void CameraManager::reset()
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
	_mouseSensitivity = 1.0f;
	_mouseOffset = 0.0f;
	_maxPitch = 90.0f;

	// Booleans
	_isLookatViewEabled = false;
	_isFirstPersonViewEnabled = false;
	_isFreeMovementEnabled = true;
	_mustCenter = false;
}

void CameraManager::update(Ivec2 lastCursorPosition)
{
	// Temporary values
	Ivec2 currenCursorPosition = _windowManager.getCursorPos();
	const int left = Config::getInst().getVpPos().x;
	const int right = Config::getInst().getVpPos().x + Config::getInst().getVpSize().x;
	const int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y);
	const int top = Config::getInst().getWindowSize().y - Config::getInst().getVpPos().y;
	const int xMiddle = left + (Config::getInst().getVpSize().x / 2);
	const int yMiddle = bottom + (Config::getInst().getVpSize().y / 2);

	// Update cursor centering
	if (_mustCenter)
	{
		// Check if cursor reached center or cursor is moving
		if (currenCursorPosition == Ivec2(xMiddle, yMiddle) || currenCursorPosition != lastCursorPosition)
		{
			_mustCenter = false;
		}
		else // Spawn mouse in middle of screen
		{
			_windowManager.setCursorPos({ xMiddle, yMiddle });
		}

	}

	// Only if first person camera is enabled & not centering
	if (_isFirstPersonViewEnabled && !_mustCenter)
	{
		// Offset between current mouse position & middle of the screen
		float xOffset = static_cast<float>(currenCursorPosition.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currenCursorPosition.y);

		// Applying mouse sensitivity
		xOffset *= _mouseSensitivity;
		yOffset *= _mouseSensitivity;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Calculate yaw & pitch
		_yawAcceleration += xOffset;
		_pitchAcceleration += yOffset;

		// Spawn mouse in middle of screen
		_windowManager.setCursorPos({ xMiddle, yMiddle });
	}

	// Update yaw & pitch movements
	_yawAcceleration = std::clamp(_yawAcceleration, -_maxYawAcceleration, _maxYawAcceleration);
	_pitchAcceleration = std::clamp(_pitchAcceleration, -_maxPitchAcceleration, _maxPitchAcceleration);
	_yaw += _yawAcceleration;
	_pitch += _pitchAcceleration;
	_yawAcceleration *= 0.75f;
	_pitchAcceleration *= 0.75f;

	// Limit yaw
	_yaw = std::fmodf(_yaw, 360.0f);

	// Limit pitch
	_pitch = std::clamp(_pitch, -(_maxPitch - 1.0f), (_maxPitch - 1.0f));

	// Update matrices
	updateMatrices();
}

void CameraManager::updateMatrices()
{
	// Clamp the camera position
	_position.x = std::clamp(_position.x, -_farZ, _farZ);
	_position.y = std::clamp(_position.y, -_farZ, _farZ);
	_position.z = std::clamp(_position.z, -_farZ, _farZ);

	// Lookat front vector
	if(_isLookatViewEabled)
	{
		Vec3 offset = Vec3(0.00001f); // Small offset, otherwise screen goes black in certain circumstances
		_front = (_lookatPosition + offset) - _position;
		_front.normalize();
	}
	else // First person front vector
	{
		_front.x = cos(Math::degreesToRadians(_pitch)) * cos(Math::degreesToRadians(_yaw));
		_front.y = sin(Math::degreesToRadians(_pitch));
		_front.z = cos(Math::degreesToRadians(_pitch)) * sin(Math::degreesToRadians(_yaw));
		_front.normalize();
	}

	// Calculate the view matrix input
	_right = _front.cross(_up);
	_right.normalize();
	
	// View matrix
	_viewMatrix = Matrix44::createView(_position, _position + _front, _up);

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

void CameraManager::translateFollowX(float speed) // Side movement
{ 
	if (_isFreeMovementEnabled)
	{
		_position += (_right * speed);
	}
}

void CameraManager::translateFollowZ(float speed) // Forward movement
{
	if (_isFreeMovementEnabled)
	{
		Vec3 tempFront = _front;
		tempFront.x = cos(Math::degreesToRadians(_yaw));
		tempFront.z = sin(Math::degreesToRadians(_yaw));
		_position.x += (tempFront.x * speed);
		_position.z += (tempFront.z * speed);
	}
}

void CameraManager::translateFollowZY(float speed) // Forward movement
{
	if (_isFreeMovementEnabled)
	{
		_position.x += (_front.x * speed);
		_position.y += (_front.y * speed);
		_position.z += (_front.z * speed);
	}
}

void CameraManager::enableLookatView()
{
	_isLookatViewEabled = true;
}

void CameraManager::disableLookatView()
{
	_isLookatViewEabled = false;
}

void CameraManager::enableFirstPersonView()
{
	// Only center first time
	if (!_isFirstPersonViewEnabled)
	{
		_mustCenter = true;
	}

	_isFirstPersonViewEnabled = true;
}

void CameraManager::disableFirstPersonView()
{
	_isFirstPersonViewEnabled = false;
}

void CameraManager::enableFreeMovement()
{
	_isFreeMovementEnabled = true;
}

void CameraManager::disableFreeMovement()
{
	_isFreeMovementEnabled = false;
}

void CameraManager::setFOV(float value)
{
	_viewMatrix.m[3][2] = _front.dot(_position);
	_fov = value;
}

void CameraManager::setMouseSensitivity(float speed)
{
	_mouseSensitivity = speed;
}

void CameraManager::setYaw(float value)
{
	_yaw = value;
	_yaw = std::fmodf(_yaw, 360.0f);
}

void CameraManager::setPitch(float value)
{
	_pitch = value;
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);
}

void CameraManager::setNearZ(float value)
{
	_nearZ = value;
}

void CameraManager::setFarZ(float value)
{
	_farZ = value;
}

void CameraManager::setMaxPitch(float value)
{
	_maxPitch = value;
}

const Vec3 CameraManager::getPosition() const
{
	return _position;
}

const Vec3 CameraManager::getFront() const
{
	return _front;
}

const Vec3 CameraManager::getLookatPosition() const
{
	return _lookatPosition;
}

const float CameraManager::getYaw() const
{
	return _yaw;
}

const float CameraManager::getPitch() const
{
	return _pitch;
}

const float CameraManager::getNearZ() const
{
	return _nearZ;
}

const float CameraManager::getFarZ() const
{
	return _farZ;
}

const float CameraManager::getMouseSensitivity() const
{
	return _mouseSensitivity;
}

const float CameraManager::getMouseOffset() const
{
	return _mouseOffset;
}

const float CameraManager::getMaxPitch() const
{
	return _maxPitch;
}

const float CameraManager::getFOV() const
{
	return _fov;
}

const float CameraManager::getAspectRatio() const
{
	return _aspectRatio;
}

const bool CameraManager::isFirstPersonViewEnabled() const
{
	return _isFirstPersonViewEnabled;
}

const bool CameraManager::isFreeMovementEnabled() const
{
	return _isFreeMovementEnabled;
}

const bool CameraManager::isLookatViewEnabled() const
{
	return _isLookatViewEabled;
}

void CameraManager::translate(Vec3 translation)
{
	if (_isFreeMovementEnabled)
	{
		_position += translation;
	}
}

void CameraManager::setPosition(Vec3 value)
{
	if (_isFreeMovementEnabled)
	{
		_position = value;
	}
}

void CameraManager::setLookatPosition(Vec3 value)
{
	_lookatPosition = value;
}

void CameraManager::invertYaw()
{
	_yaw = -_yaw;
}

void CameraManager::invertPitch()
{
	_pitch = -_pitch;
}

void CameraManager::center()
{
	_mustCenter = true;
}

const Matrix44 & CameraManager::getViewMatrix() const
{
	return _viewMatrix;
}

const Matrix44 & CameraManager::getProjectionMatrix() const
{
	return _projectionMatrix;
}
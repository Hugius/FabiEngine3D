#include "camera_manager.hpp"
#include "configuration.hpp"

#include <algorithm>
#include <iostream>

CameraManager::CameraManager(RenderBus& renderBus) :
	_renderBus(renderBus)
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

	// Booleans
	_isLookatEabled = false;
	_isFirstPersonViewEnabled = false;
	_isFreeMovementEnabled = true;
	_mustCenter = false;
}

void CameraManager::update(WindowManager & windowManager)
{
	// Temporary values
	Ivec2 currentMousePos = windowManager.getMousePos();
	const int left = Config::getInst().getVpPos().x;
	const int right = Config::getInst().getVpPos().x + Config::getInst().getVpSize().x;
	const int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y);
	const int top = Config::getInst().getWindowSize().y - Config::getInst().getVpPos().y;
	const int xMiddle = Config::getInst().getWindowSize().x / 2;
	const int yMiddle = Config::getInst().getWindowSize().y / 2;

	// Only if first person camera is enabled & not centering
	if (_isFirstPersonViewEnabled && !_mustCenter)
	{
		// Offset between current and last mouse pos
		float xOffset = static_cast<float>(currentMousePos.x - xMiddle);
		float yOffset = static_cast<float>(yMiddle - currentMousePos.y);

		// Applying mouse sensitivity
		xOffset *= (_mouseSensitivity) / 100.0f;
		yOffset *= (_mouseSensitivity) / 100.0f;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Calculate yaw & pitch
		_yawAcceleration += xOffset;
		_pitchAcceleration += yOffset;

		// Spawn mouse in middle of screen
		windowManager.setMousePos({ xMiddle, yMiddle });
	}

	// Spawn mouse in middle of screen
	if (_mustCenter)
	{
		windowManager.setMousePos({ xMiddle, yMiddle });
		_mustCenter = false;
	}

	// Update yaw & pitch movements
	_yaw += _yawAcceleration;
	_pitch += _pitchAcceleration;
	_yawAcceleration *= 0.75f;
	_pitchAcceleration *= 0.75f;

	// Limit yaw
	if (_yaw < 0.0f)
	{
		_yaw = 360.0f - fabsf(_yaw);
	}
	_yaw = std::fmod(_yaw, 360.0f);

	// Limit pitch
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);

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
	if(_isLookatEabled)
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

void CameraManager::enableLookat()
{
	_isLookatEabled = true;
}

void CameraManager::disableLookat()
{
	_isLookatEabled = false;
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

void CameraManager::setFOV(float val)
{
	_viewMatrix.m[3][2] = _front.dot(_position);
	_fov = val;
}

void CameraManager::setMouseSensitivity(float speed)
{
	_mouseSensitivity = speed;
}

void CameraManager::setYaw(float val)
{
	_yaw = val;
	_yaw = std::fmod(_yaw, 360.0f);
}

void CameraManager::setPitch(float val)
{
	_pitch = val;
	_pitch = std::clamp(_pitch, -89.0f, 89.0f);
}

void CameraManager::setNearZ(float val)
{
	_nearZ = val;
}

void CameraManager::setFarZ(float val)
{
	_farZ = val;
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

const bool CameraManager::isLookatEnabled() const
{
	return _isLookatEabled;
}

void CameraManager::translate(Vec3 translation)
{
	if (_isFreeMovementEnabled)
	{
		_position += translation;
	}
}

void CameraManager::setPosition(Vec3 val)
{
	if (_isFreeMovementEnabled)
	{
		_position = val;
	}
}

void CameraManager::setLookatPosition(Vec3 val)
{
	_lookatPosition = val;
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

#include "camera_manager.hpp"
#include "configuration.hpp"

#include <algorithm>

CameraManager::CameraManager(RenderBus& renderBus) :
	_renderBus(renderBus)
{
	_aspectRatio = float(Config::getInst().getWindowWidth()) / float(Config::getInst().getWindowHeight());
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
	_lookat = Vec3(0.0f);

	// Floats
	_fov = 0.0f;
	_pitch = 0.0f;
	_yaw = 0.0f;
	_nearZ = 0.0f;
	_farZ = 0.0f;
	_mouseOffset = 0.0f;

	// Booleans
	_isLookatEabled = false;
	_isFirstPersonViewEnabled = false;
	_isFreeMovementEnabled = true;
	_mustCenter = false;
}

void CameraManager::update(WindowManager & windowManager)
{
	// Variables
	Ivec2 currentMousePos = windowManager.getMousePos();
	static Ivec2 lastMousePos = currentMousePos;

	if (_isFirstPersonViewEnabled && !_mustCenter)
	{
		// Variable
		int left = Config::getInst().getVpPos().x;
		int right = Config::getInst().getVpPos().x + Config::getInst().getVpSize().x;
		int bottom = Config::getInst().getWindowSize().y - (Config::getInst().getVpPos().y + Config::getInst().getVpSize().y);
		int top = Config::getInst().getWindowSize().y - Config::getInst().getVpPos().y;
		
		// Reset mouse position if going out of screen (horizontal)
		if (currentMousePos.x < left)
		{
			windowManager.setMousePos({ right, currentMousePos.y });
			lastMousePos.x = right;
			return;
		}
		else if (currentMousePos.x > right)
		{
			windowManager.setMousePos({ left, currentMousePos.y });
			lastMousePos.x = left;
			return;
		}

		// Reset mouse position if going out of screen (vertical)
		if (currentMousePos.y < bottom)
		{
			windowManager.setMousePos({ currentMousePos.x, top});
			lastMousePos.y = top;
			return;
		}
		else if (currentMousePos.y > top)
		{
			windowManager.setMousePos({ currentMousePos.x, bottom });
			lastMousePos.y = bottom;
			return;
		}

		// Offset between current and last mouse pos
		float xOffset = static_cast<float>(currentMousePos.x - lastMousePos.x);
		float yOffset = static_cast<float>(lastMousePos.y - currentMousePos.y);

		// Applying mouse sensitivity
		xOffset *= (_mouseSensitivity) / 100.0f;
		yOffset *= (_mouseSensitivity) / 100.0f;

		// Calculate overall mouse offset
		_mouseOffset = (xOffset + yOffset) / 2.0f;

		// Calculate yaw & pitch
		_yawAcceleration += xOffset;
		_pitchAcceleration += yOffset;
	}
	else
	{
		_mustCenter = false;
	}

	// Update yaw & pitch movements
	_yaw += _yawAcceleration;
	_pitch += _pitchAcceleration;
	_yawAcceleration *= 0.7f;
	_pitchAcceleration *= 0.7f;

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

	// Set last mouse position
	lastMousePos = currentMousePos;
}

void CameraManager::updateMatrices()
{
	// Lookat front vector
	if(_isLookatEabled)
	{
		Vec3 offset = Vec3(0.00001f); // Small offset, otherwise screen goes black in certain circumstances
		_front = (_lookat + offset) - _position;
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

void CameraManager::enableLookat(Vec3 position)
{
	_isLookatEabled = true;
	_lookat = position;
}

void CameraManager::disableLookat()
{
	_isLookatEabled = false;
}

void CameraManager::enableFirstPersonView()
{
	_mustCenter = true;
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

const Vec3 CameraManager::getLookat() const
{
	return _lookat;
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

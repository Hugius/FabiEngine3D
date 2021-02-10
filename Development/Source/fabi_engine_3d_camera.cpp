#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::camera_load(float fov, float nearZ, float farZ, Vec3 startPosition, float yaw, float pitch)
{
	_core->_cameraManager.reset();
	_core->_cameraManager.setPosition(startPosition);
	_core->_cameraManager.setFOV(fov);
	_core->_cameraManager.setYaw(yaw);
	_core->_cameraManager.setPitch(pitch);
	_core->_cameraManager.setNearZ(nearZ);
	_core->_cameraManager.setFarZ(farZ);
}

void FabiEngine3D::camera_enableLookatView()
{
	_core->_cameraManager.enableLookatView();
}

void FabiEngine3D::camera_disableLookatView()
{
	_core->_cameraManager.disableLookatView();
}

void FabiEngine3D::camera_enableFirstPersonView()
{
	_core->_cameraManager.enableFirstPersonView();
}

void FabiEngine3D::camera_disableFirstPersonView()
{
	_core->_cameraManager.disableFirstPersonView();
}

void FabiEngine3D::camera_enableFreeMovement()
{
	_core->_cameraManager.enableFreeMovement();
}

void FabiEngine3D::camera_disableFreeMovement()
{
	_core->_cameraManager.disableFreeMovement();
}

void FabiEngine3D::camera_translateFollowX(float speed)
{
	_core->_cameraManager.translateFollowX(speed);
}

void FabiEngine3D::camera_translateFollowZY(float speed)
{
	_core->_cameraManager.translateFollowZY(speed);
}

void FabiEngine3D::camera_translateFollowZ(float speed)
{
	_core->_cameraManager.translateFollowZ(speed);
}

void FabiEngine3D::camera_translate(Vec3 translation)
{
	_core->_cameraManager.translate(translation);
}

void FabiEngine3D::camera_setPosition(Vec3 position)
{
	_core->_cameraManager.setPosition(position);
}

void FabiEngine3D::camera_setLookatPosition(Vec3 position)
{
	_core->_cameraManager.setLookatPosition(position);
}

void FabiEngine3D::camera_invertYaw()
{
	_core->_cameraManager.invertYaw();
}

void FabiEngine3D::camera_invertPitch()
{
	_core->_cameraManager.invertPitch();
}

void FabiEngine3D::camera_setFOV(float fov)
{
	_core->_cameraManager.setFOV(fov);
}

void FabiEngine3D::camera_setMouseSensitivity(float speed)
{
	_core->_cameraManager.setMouseSensitivity(speed);
}

void FabiEngine3D::camera_setYaw(float yaw)
{
	_core->_cameraManager.setYaw(yaw);
}

void FabiEngine3D::camera_setPitch(float pitch)
{
	_core->_cameraManager.setPitch(pitch);
}

void FabiEngine3D::camera_setNearDistance(float nearZ)
{
	_core->_cameraManager.setNearZ(nearZ);
}

void FabiEngine3D::camera_setFarDistance(float farZ)
{
	_core->_cameraManager.setFarZ(farZ);
}

void FabiEngine3D::camera_setMaxPitch(float pitch)
{
	_core->_cameraManager.setMaxPitch(pitch);
}

void FabiEngine3D::camera_center()
{
	_core->_cameraManager.center();
}

float FabiEngine3D::camera_getYaw()
{
	return _core->_cameraManager.getYaw();
}

float FabiEngine3D::camera_getPitch()
{
	return _core->_cameraManager.getPitch();
}

float FabiEngine3D::camera_getNearDistance()
{
	return _core->_cameraManager.getNearZ();
}

float FabiEngine3D::camera_getFarDistance()
{
	return _core->_cameraManager.getFarZ();
}

float FabiEngine3D::camera_getMouseOffset()
{
	return _core->_cameraManager.getMouseOffset();
}

float FabiEngine3D::camera_getMaxPitch()
{
	return _core->_cameraManager.getMaxPitch();
}

float FabiEngine3D::camera_getFOV()
{
	return _core->_cameraManager.getFOV();
}

float FabiEngine3D::getAspectRatio()
{
	return _core->_cameraManager.getAspectRatio();
}

float FabiEngine3D::camera_getMouseSensitivity()
{
	return _core->_cameraManager.getMouseSensitivity();
}

Vec3 FabiEngine3D::camera_getPosition()
{
	return _core->_cameraManager.getPosition();
}

Vec3 FabiEngine3D::camera_getLookatPosition()
{
	return _core->_cameraManager.getLookatPosition();
}

bool FabiEngine3D::camera_isLookatViewEnabled()
{
	return _core->_cameraManager.isLookatViewEnabled();
}

bool FabiEngine3D::camera_isFirstPersonViewEnabled()
{
	return _core->_cameraManager.isFirstPersonViewEnabled();
}

bool FabiEngine3D::camera_isFreeMovementEnabled()
{
	return _core->_cameraManager.isFreeMovementEnabled();
}

#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::camera_load(float fov, float nearZ, float farZ, vec3 startPos, float yaw, float pitch)
{
	_core->_cameraManager.reset();
	_core->_cameraManager.setPosition(startPos);
	_core->_cameraManager.setFOV(fov);
	_core->_cameraManager.setYaw(yaw);
	_core->_cameraManager.setPitch(pitch);
	_core->_cameraManager.setNearZ(nearZ);
	_core->_cameraManager.setFarZ(farZ);
}

void FabiEngine3D::camera_enableLookat(vec3 position)
{
	_core->_cameraManager.enableLookat(position);
}

void FabiEngine3D::camera_disableLookat()
{
	_core->_cameraManager.disableLookat();
}

void FabiEngine3D::camera_enableFirstPersonView(float mouseSensitivity)
{
	_core->_cameraManager.enableFirstPersonView();
	_core->_cameraManager.setMouseSensitivity(mouseSensitivity);
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

void FabiEngine3D::camera_translate(vec3 translation)
{
	_core->_cameraManager.translate(translation);
}

void FabiEngine3D::camera_setPosition(vec3 pos)
{
	_core->_cameraManager.setPosition(pos);
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

void FabiEngine3D::camera_setSensitivity(float speed)
{
	_core->_cameraManager.setMouseSensitivity(speed);
}

void FabiEngine3D::camera_setYaw(float val)
{
	_core->_cameraManager.setYaw(val);
}

void FabiEngine3D::camera_setPitch(float val)
{
	_core->_cameraManager.setPitch(val);
}

void FabiEngine3D::camera_setNearDistance(float val)
{
	_core->_cameraManager.setNearZ(val);
}

void FabiEngine3D::camera_setFarDistance(float val)
{
	_core->_cameraManager.setFarZ(val);
}

float FabiEngine3D::camera_getYaw()
{
	return _core->_cameraManager.getYaw();
}

float FabiEngine3D::camera_getPitch()
{
	return _core->_cameraManager.getPitch();
}

float FabiEngine3D::camera_getMouseOffset()
{
	return _core->_cameraManager.getMouseOffset();
}

float FabiEngine3D::camera_getFOV()
{
	return _core->_cameraManager.getFOV();
}

vec3 FabiEngine3D::camera_getPos()
{
	return _core->_cameraManager.getPosition();
}

vec3 FabiEngine3D::camera_getFront()
{
	return _core->_cameraManager.getFront();
}

bool FabiEngine3D::camera_isFirstPersonViewEnabled()
{
	return _core->_cameraManager.isFirstPersonViewEnabled();
}
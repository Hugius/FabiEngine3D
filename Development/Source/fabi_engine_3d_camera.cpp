#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::camera_reset()
{
	_core->_camera.reset();
}

void FabiEngine3D::camera_enableFirstPersonView(float initialYaw, float initialPitch)
{
	_core->_camera.enableFirstPersonView(initialYaw, initialPitch);
}

void FabiEngine3D::camera_disableFirstPersonView()
{
	_core->_camera.disableFirstPersonView();
}

void FabiEngine3D::camera_enableThirdPersonView(float initialYaw, float initialPitch, float initialDistance)
{
	_core->_camera.enableThirdPersonView(initialYaw, initialPitch, initialDistance);
}

void FabiEngine3D::camera_disableThirdPersonView()
{
	_core->_camera.disableThirdPersonView();
}

void FabiEngine3D::camera_moveFollowX(float speed)
{
	_core->_camera.moveFollowX(speed);
}

void FabiEngine3D::camera_moveFollowZY(float speed)
{
	_core->_camera.moveFollowZY(speed);
}

void FabiEngine3D::camera_moveFollowZ(float speed)
{
	_core->_camera.moveFollowZ(speed);
}

void FabiEngine3D::camera_move(Vec3 speed)
{
	_core->_camera.move(speed);
}

void FabiEngine3D::camera_setPosition(Vec3 position)
{
	_core->_camera.setPosition(position);
}

void FabiEngine3D::camera_setThirdPersonLookat(Vec3 position)
{
	_core->_camera.setThirdPersonLookat(position);
}

void FabiEngine3D::camera_setFOV(float angle)
{
	_core->_camera.setFOV(angle);
}

void FabiEngine3D::camera_setMouseSensitivity(float speed)
{
	_core->_camera.setMouseSensitivity(speed);
}

void FabiEngine3D::camera_setYaw(float angle)
{
	_core->_camera.setYaw(angle);
}

void FabiEngine3D::camera_setPitch(float angle)
{
	_core->_camera.setPitch(angle);
}

void FabiEngine3D::camera_setNearZ(float distance)
{
	_core->_camera.setNearZ(distance);
}

void FabiEngine3D::camera_setFarZ(float distance)
{
	_core->_camera.setFarZ(distance);
}

void FabiEngine3D::camera_setMinFirstPersonPitch(float angle)
{
	_core->_camera.setMinFirstPersonPitch(angle);
}

void FabiEngine3D::camera_setMaxFirstPersonPitch(float angle)
{
	_core->_camera.setMaxFirstPersonPitch(angle);
}

void FabiEngine3D::camera_setMinThirdPersonPitch(float angle)
{
	_core->_camera.setMinThirdPersonPitch(angle);
}

void FabiEngine3D::camera_setMaxThirdPersonPitch(float angle)
{
	_core->_camera.setMaxThirdPersonPitch(angle);
}

void FabiEngine3D::camera_setThirdPersonDistance(float distance)
{
	_core->_camera.setThirdPersonDistance(distance);
}

const float FabiEngine3D::camera_getYaw()
{
	return _core->_camera.getYaw();
}

const float FabiEngine3D::camera_getPitch()
{
	return _core->_camera.getPitch();
}

const float FabiEngine3D::camera_getFirstPersonYaw()
{
	return _core->_camera.getFirstPersonYaw();
}

const float FabiEngine3D::camera_getFirstPersonPitch()
{
	return _core->_camera.getFirstPersonPitch();
}

const float FabiEngine3D::camera_getThirdPersonYaw()
{
	return _core->_camera.getThirdPersonYaw();
}

const float FabiEngine3D::camera_getThirdPersonPitch()
{
	return _core->_camera.getThirdPersonPitch();
}

const float FabiEngine3D::camera_getThirdPersonDistance()
{
	return _core->_camera.getThirdPersonDistance();
}

const float FabiEngine3D::camera_getNearDistance()
{
	return _core->_camera.getNearZ();
}

const float FabiEngine3D::camera_getFarDistance()
{
	return _core->_camera.getFarZ();
}

const float FabiEngine3D::camera_getMouseOffset()
{
	return _core->_camera.getMouseOffset();
}

const float FabiEngine3D::camera_getFOV()
{
	return _core->_camera.getFOV();
}

const float FabiEngine3D::getAspectRatio()
{
	return _core->_camera.getAspectRatio();
}

const float FabiEngine3D::camera_getMouseSensitivity()
{
	return _core->_camera.getMouseSensitivity();
}

const Vec3 FabiEngine3D::camera_getPosition()
{
	return _core->_camera.getPosition();
}

const Vec3 FabiEngine3D::camera_getThirdPersonLookat()
{
	return _core->_camera.getThirdPersonLookat();
}

const bool FabiEngine3D::camera_isThirdPersonViewEnabled()
{
	return _core->_camera.isThirdPersonViewEnabled();
}

const bool FabiEngine3D::camera_isFirstPersonViewEnabled()
{
	return _core->_camera.isFirstPersonViewEnabled();
}
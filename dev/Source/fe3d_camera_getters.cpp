#include "fe3d.hpp"
#include "core_engine.hpp"

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
	return _core->_camera.getNearDistance();
}

const float FabiEngine3D::camera_getFarDistance()
{
	return _core->_camera.getFarDistance();
}

const float FabiEngine3D::camera_getFOV()
{
	return _core->_camera.getFOV();
}

const float FabiEngine3D::camera_getAspectRatio()
{
	return _core->_camera.getAspectRatio();
}

const float FabiEngine3D::camera_getCursorSensitivity()
{
	return _core->_camera.getCursorSensitivity();
}

const Vec3 FabiEngine3D::camera_getPosition()
{
	return _core->_camera.getPosition();
}

const Vec3 FabiEngine3D::camera_getUpVector()
{
	return _core->_camera.getUpVector();
}

const Vec3 FabiEngine3D::camera_getFrontVector()
{
	return _core->_camera.getFrontVector();
}

const Vec3 FabiEngine3D::camera_getRightVector()
{
	return _core->_camera.getRightVector();
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
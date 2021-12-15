#include "fe3d.hpp"
#include "core.hpp"

const float FabiEngine3D::camera_getYaw() const
{
	return _core->_camera.getYaw();
}

const float FabiEngine3D::camera_getPitch() const
{
	return _core->_camera.getPitch();
}

const float FabiEngine3D::camera_getFirstPersonYaw() const
{
	return _core->_camera.getFirstPersonYaw();
}

const float FabiEngine3D::camera_getFirstPersonPitch() const
{
	return _core->_camera.getFirstPersonPitch();
}

const float FabiEngine3D::camera_getThirdPersonYaw() const
{
	return _core->_camera.getThirdPersonYaw();
}

const float FabiEngine3D::camera_getThirdPersonPitch() const
{
	return _core->_camera.getThirdPersonPitch();
}

const float FabiEngine3D::camera_getThirdPersonDistance() const
{
	return _core->_camera.getThirdPersonDistance();
}

const float FabiEngine3D::camera_getNearDistance() const
{
	return _core->_camera.getNearDistance();
}

const float FabiEngine3D::camera_getFarDistance() const
{
	return _core->_camera.getFarDistance();
}

const float FabiEngine3D::camera_getFOV() const
{
	return _core->_camera.getFOV();
}

const float FabiEngine3D::camera_getCursorSensitivity() const
{
	return _core->_camera.getCursorSensitivity();
}

const fvec3 FabiEngine3D::camera_getPosition() const
{
	return _core->_camera.getPosition();
}

const fvec3 FabiEngine3D::camera_getUpVector() const
{
	return _core->_camera.getUpVector();
}

const fvec3 FabiEngine3D::camera_getFrontVector() const
{
	return _core->_camera.getFrontVector();
}

const fvec3 FabiEngine3D::camera_getRightVector() const
{
	return _core->_camera.getRightVector();
}

const fvec3 FabiEngine3D::camera_getThirdPersonLookat() const
{
	return _core->_camera.getThirdPersonLookat();
}

const bool FabiEngine3D::camera_isThirdPersonViewEnabled() const
{
	return _core->_camera.isThirdPersonViewEnabled();
}

const bool FabiEngine3D::camera_isFirstPersonViewEnabled() const
{
	return _core->_camera.isFirstPersonViewEnabled();
}
#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::camera_reset()
{
	_core->_camera.reset();
}

void FabiEngine3D::camera_enableFirstPersonView(float initialYaw, float initialPitch)
{
	if(_core->_camera.isThirdPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable first person view: third person view currently enabled!");
		return;
	}
	if(_core->_camera.isFirstPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable first person view: already enabled!");
		return;
	}

	_core->_camera.enableFirstPersonView(initialYaw, initialPitch);
}

void FabiEngine3D::camera_disableFirstPersonView()
{
	if(!_core->_camera.isFirstPersonViewEnabled())
	{
		Logger::throwWarning("Tried to disable first person view: not enabled!");
		return;
	}

	_core->_camera.disableFirstPersonView();
}

void FabiEngine3D::camera_enableThirdPersonView(float initialYaw, float initialPitch)
{
	if(_core->_camera.isFirstPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable third person view: first person view currently enabled!");
		return;
	}
	if(_core->_camera.isThirdPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable third person view: already enabled!");
		return;
	}

	_core->_camera.enableThirdPersonView(initialYaw, initialPitch);
}

void FabiEngine3D::camera_disableThirdPersonView()
{
	if(!_core->_camera.isThirdPersonViewEnabled())
	{
		Logger::throwWarning("Tried to disable third person view: not enabled!");
		return;
	}

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

void FabiEngine3D::camera_move(fvec3 speed)
{
	_core->_camera.move(speed);
}

void FabiEngine3D::camera_setPosition(fvec3 value)
{
	_core->_camera.setPosition(value);
}

void FabiEngine3D::camera_setThirdPersonLookat(fvec3 value)
{
	_core->_camera.setThirdPersonLookat(value);
}

void FabiEngine3D::camera_setFOV(float value)
{
	_core->_camera.setFOV(value);
}

void FabiEngine3D::camera_setCursorSensitivity(float value)
{
	_core->_camera.setCursorSensitivity(value);
}

void FabiEngine3D::camera_setYaw(float value)
{
	_core->_camera.setYaw(value);
}

void FabiEngine3D::camera_setPitch(float value)
{
	_core->_camera.setPitch(value);
}

void FabiEngine3D::camera_setMinFirstPersonPitch(float value)
{
	_core->_camera.setMinFirstPersonPitch(value);
}

void FabiEngine3D::camera_setMaxFirstPersonPitch(float value)
{
	_core->_camera.setMaxFirstPersonPitch(value);
}

void FabiEngine3D::camera_setMinThirdPersonPitch(float value)
{
	_core->_camera.setMinThirdPersonPitch(value);
}

void FabiEngine3D::camera_setMaxThirdPersonPitch(float value)
{
	_core->_camera.setMaxThirdPersonPitch(value);
}

void FabiEngine3D::camera_setThirdPersonDistance(float value)
{
	_core->_camera.setThirdPersonDistance(value);
}
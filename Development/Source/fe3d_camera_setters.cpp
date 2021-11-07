#include "fe3d.hpp"
#include "core_engine.hpp"

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

void FabiEngine3D::camera_setCursorSensitivity(float speed)
{
	_core->_camera.setCursorSensitivity(speed);
}

void FabiEngine3D::camera_setYaw(float angle)
{
	_core->_camera.setYaw(angle);
}

void FabiEngine3D::camera_setPitch(float angle)
{
	_core->_camera.setPitch(angle);
}

void FabiEngine3D::camera_setNearDistance(float distance)
{
	_core->_camera.setNearDistance(distance);
}

void FabiEngine3D::camera_setFarDistance(float distance)
{
	_core->_camera.setFarDistance(distance);
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
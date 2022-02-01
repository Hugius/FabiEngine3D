#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::camera_reset()
{
	_core->getCamera()->reset();
}

void EngineInterface::camera_setFirstPersonViewEnabled(bool value)
{
	_core->getCamera()->setFirstPersonViewEnabled(value);
}

void EngineInterface::camera_setThirdPersonViewEnabled(bool value)
{
	_core->getCamera()->setThirdPersonViewEnabled(value);
}

void EngineInterface::camera_moveFollowX(float speed)
{
	_core->getCamera()->moveFollowX(speed);
}

void EngineInterface::camera_moveFollowZY(float speed)
{
	_core->getCamera()->moveFollowZY(speed);
}

void EngineInterface::camera_moveFollowZ(float speed)
{
	_core->getCamera()->moveFollowZ(speed);
}

void EngineInterface::camera_move(const fvec3& speed)
{
	_core->getCamera()->move(speed);
}

void EngineInterface::camera_setPosition(const fvec3& value)
{
	_core->getCamera()->setPosition(value);
}

void EngineInterface::camera_setThirdPersonLookat(const fvec3& value)
{
	_core->getCamera()->setThirdPersonLookat(value);
}

void EngineInterface::camera_setFOV(float value)
{
	_core->getCamera()->setFOV(value);
}

void EngineInterface::camera_setCursorSensitivity(float value)
{
	_core->getCamera()->setCursorSensitivity(value);
}

void EngineInterface::camera_setYaw(float value)
{
	_core->getCamera()->setYaw(value);
}

void EngineInterface::camera_setPitch(float value)
{
	_core->getCamera()->setPitch(value);
}

void EngineInterface::camera_setFirstPersonYaw(float value)
{
	_core->getCamera()->setFirstPersonYaw(value);
}

void EngineInterface::camera_setFirstPersonPitch(float value)
{
	_core->getCamera()->setFirstPersonPitch(value);
}

void EngineInterface::camera_setThirdPersonYaw(float value)
{
	_core->getCamera()->setThirdPersonYaw(value);
}

void EngineInterface::camera_setThirdPersonPitch(float value)
{
	_core->getCamera()->setThirdPersonPitch(value);
}

void EngineInterface::camera_setMinFirstPersonPitch(float value)
{
	_core->getCamera()->setMinFirstPersonPitch(value);
}

void EngineInterface::camera_setMaxFirstPersonPitch(float value)
{
	_core->getCamera()->setMaxFirstPersonPitch(value);
}

void EngineInterface::camera_setMinThirdPersonPitch(float value)
{
	_core->getCamera()->setMinThirdPersonPitch(value);
}

void EngineInterface::camera_setMaxThirdPersonPitch(float value)
{
	_core->getCamera()->setMaxThirdPersonPitch(value);
}

void EngineInterface::camera_setThirdPersonDistance(float value)
{
	_core->getCamera()->setThirdPersonDistance(value);
}

const float EngineInterface::camera_getYaw() const
{
	return _core->getCamera()->getYaw();
}

const float EngineInterface::camera_getPitch() const
{
	return _core->getCamera()->getPitch();
}

const float EngineInterface::camera_getFirstPersonYaw() const
{
	return _core->getCamera()->getFirstPersonYaw();
}

const float EngineInterface::camera_getFirstPersonPitch() const
{
	return _core->getCamera()->getFirstPersonPitch();
}

const float EngineInterface::camera_getMinFirstPersonPitch() const
{
	return _core->getCamera()->getMinFirstPersonPitch();
}

const float EngineInterface::camera_getMaxFirstPersonPitch() const
{
	return _core->getCamera()->getMaxFirstPersonPitch();
}

const float EngineInterface::camera_getThirdPersonYaw() const
{
	return _core->getCamera()->getThirdPersonYaw();
}

const float EngineInterface::camera_getThirdPersonPitch() const
{
	return _core->getCamera()->getThirdPersonPitch();
}

const float EngineInterface::camera_getMinThirdPersonPitch() const
{
	return _core->getCamera()->getMinThirdPersonPitch();
}

const float EngineInterface::camera_getMaxThirdPersonPitch() const
{
	return _core->getCamera()->getMaxFirstPersonPitch();
}

const float EngineInterface::camera_getThirdPersonDistance() const
{
	return _core->getCamera()->getThirdPersonDistance();
}

const float EngineInterface::camera_getNear() const
{
	return _core->getCamera()->getNear();
}

const float EngineInterface::camera_getFar() const
{
	return _core->getCamera()->getFar();
}

const float EngineInterface::camera_getFOV() const
{
	return _core->getCamera()->getFOV();
}

const float EngineInterface::camera_getCursorSensitivity() const
{
	return _core->getCamera()->getCursorSensitivity();
}

const fvec3& EngineInterface::camera_getPosition() const
{
	return _core->getCamera()->getPosition();
}

const fvec3& EngineInterface::camera_getUp() const
{
	return _core->getCamera()->getUp();
}

const fvec3& EngineInterface::camera_getFront() const
{
	return _core->getCamera()->getFront();
}

const fvec3& EngineInterface::camera_getRight() const
{
	return _core->getCamera()->getRight();
}

const fvec3& EngineInterface::camera_getThirdPersonLookat() const
{
	return _core->getCamera()->getThirdPersonLookat();
}

const bool EngineInterface::camera_isThirdPersonViewEnabled() const
{
	return _core->getCamera()->isThirdPersonViewEnabled();
}

const bool EngineInterface::camera_isFirstPersonViewEnabled() const
{
	return _core->getCamera()->isFirstPersonViewEnabled();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::camera_reset()
{
	_core->getCamera()->reset();
}

void EngineInterface::camera_setFirstPersonEnabled(bool value)
{
	_core->getCamera()->setFirstPersonEnabled(value);
}

void EngineInterface::camera_setThirdPersonEnabled(bool value)
{
	_core->getCamera()->setThirdPersonEnabled(value);
}

void EngineInterface::camera_move(const fvec3 & speed)
{
	_core->getCamera()->move(speed);
}

void EngineInterface::camera_moveTo(const fvec3 & target, float speed)
{
	_core->getCamera()->moveTo(target, speed);
}

void EngineInterface::camera_setPosition(const fvec3 & value)
{
	_core->getCamera()->setPosition(value);
}

void EngineInterface::camera_setThirdPersonLookat(const fvec3 & value)
{
	_core->getCamera()->setThirdPersonLookat(value);
}

void EngineInterface::camera_setFov(float value)
{
	_core->getCamera()->setFov(value);
}

void EngineInterface::camera_setCursorSensitivity(float value)
{
	_core->getCamera()->setCursorSensitivity(value);
}

void EngineInterface::camera_setAccelerationResistence(float value)
{
	_core->getCamera()->setAccelerationResistence(value);
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

void EngineInterface::camera_setNear(float value)
{
	_core->getCamera()->setNear(value);
}

void EngineInterface::camera_setFar(float value)
{
	_core->getCamera()->setFar(value);
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

const float EngineInterface::camera_getAccelerationResistence() const
{
	return _core->getCamera()->getAccelerationResistence();
}

const float EngineInterface::camera_getNear() const
{
	return _core->getCamera()->getNear();
}

const float EngineInterface::camera_getFar() const
{
	return _core->getCamera()->getFar();
}

const float EngineInterface::camera_getFov() const
{
	return _core->getCamera()->getFov();
}

const float EngineInterface::camera_getCursorSensitivity() const
{
	return _core->getCamera()->getCursorSensitivity();
}

const fvec3 & EngineInterface::camera_getPosition() const
{
	return _core->getCamera()->getPosition();
}

const fvec3 & EngineInterface::camera_getUp() const
{
	return _core->getCamera()->getUp();
}

const fvec3 & EngineInterface::camera_getFront() const
{
	return _core->getCamera()->getFront();
}

const fvec3 & EngineInterface::camera_getFrontWithoutPitch() const
{
	return _core->getCamera()->getFrontWithoutPitch();
}

const fvec3 & EngineInterface::camera_getRight() const
{
	return _core->getCamera()->getRight();
}

const fvec3 & EngineInterface::camera_getThirdPersonLookat() const
{
	return _core->getCamera()->getThirdPersonLookat();
}

const bool EngineInterface::camera_isThirdPersonEnabled() const
{
	return _core->getCamera()->isThirdPersonEnabled();
}

const bool EngineInterface::camera_isFirstPersonEnabled() const
{
	return _core->getCamera()->isFirstPersonEnabled();
}
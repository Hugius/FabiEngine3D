#include "engine_interface.hpp"
#include "engine_core.hpp"

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

const float EngineInterface::camera_getNearDistance() const
{
	return _core->getCamera()->getNearDistance();
}

const float EngineInterface::camera_getFarDistance() const
{
	return _core->getCamera()->getFarDistance();
}

const float EngineInterface::camera_getFOV() const
{
	return _core->getCamera()->getFOV();
}

const float EngineInterface::camera_getCursorSensitivity() const
{
	return _core->getCamera()->getCursorSensitivity();
}

const fvec3 EngineInterface::camera_getPosition() const
{
	return _core->getCamera()->getPosition();
}

const fvec3 EngineInterface::camera_getUpVector() const
{
	return _core->getCamera()->getUpVector();
}

const fvec3 EngineInterface::camera_getFrontVector() const
{
	return _core->getCamera()->getFrontVector();
}

const fvec3 EngineInterface::camera_getRightVector() const
{
	return _core->getCamera()->getRightVector();
}

const fvec3 EngineInterface::camera_getThirdPersonLookat() const
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
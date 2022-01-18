#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::camera_reset()
{
	_core->getCamera()->reset();
}

void EngineInterface::camera_enableFirstPersonView(float initialYaw, float initialPitch)
{
	if(_core->getCamera()->isThirdPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable first person view: third person view currently enabled!");
		return;
	}
	if(_core->getCamera()->isFirstPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable first person view: already enabled!");
		return;
	}

	_core->getCamera()->enableFirstPersonView(initialYaw, initialPitch);
}

void EngineInterface::camera_disableFirstPersonView()
{
	if(!_core->getCamera()->isFirstPersonViewEnabled())
	{
		Logger::throwWarning("Tried to disable first person view: not enabled!");
		return;
	}

	_core->getCamera()->disableFirstPersonView();
}

void EngineInterface::camera_enableThirdPersonView(float initialYaw, float initialPitch)
{
	if(_core->getCamera()->isFirstPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable third person view: first person view currently enabled!");
		return;
	}
	if(_core->getCamera()->isThirdPersonViewEnabled())
	{
		Logger::throwWarning("Tried to enable third person view: already enabled!");
		return;
	}

	_core->getCamera()->enableThirdPersonView(initialYaw, initialPitch);
}

void EngineInterface::camera_disableThirdPersonView()
{
	if(!_core->getCamera()->isThirdPersonViewEnabled())
	{
		Logger::throwWarning("Tried to disable third person view: not enabled!");
		return;
	}

	_core->getCamera()->disableThirdPersonView();
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

void EngineInterface::camera_move(fvec3 speed)
{
	_core->getCamera()->move(speed);
}

void EngineInterface::camera_setPosition(fvec3 value)
{
	_core->getCamera()->setPosition(value);
}

void EngineInterface::camera_setThirdPersonLookat(fvec3 value)
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
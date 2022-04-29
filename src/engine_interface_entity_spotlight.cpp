#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::spotlight_create(const string & spotlightId)
{
	_core->getSpotlightManager()->createSpotlight(spotlightId);
}

void EngineInterface::spotlight_delete(const string & spotlightId)
{
	_core->getSpotlightManager()->deleteSpotlight(spotlightId);
}

void EngineInterface::spotlight_setVisible(const string & spotlightId, bool value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setVisible(value);
}

void EngineInterface::spotlight_setPosition(const string & spotlightId, const fvec3 & value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setPosition(value);
}

void EngineInterface::spotlight_move(const string & spotlightId, const fvec3 & change)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->move(change);
}

void EngineInterface::spotlight_moveTo(const string & spotlightId, const fvec3 & target, float speed)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->moveTo(target, speed);
}

void EngineInterface::spotlight_setColor(const string & spotlightId, const fvec3 & value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setColor(value);
}

void EngineInterface::spotlight_setYaw(const string & spotlightId, float value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setYaw(value);
}

void EngineInterface::spotlight_setPitch(const string & spotlightId, float value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setPitch(value);
}

void EngineInterface::spotlight_setIntensity(const string & spotlightId, float value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setIntensity(value);
}

void EngineInterface::spotlight_setAngle(const string & spotlightId, float value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setAngle(value);
}

void EngineInterface::spotlight_setDistance(const string & spotlightId, float value)
{
	_core->getSpotlightManager()->getSpotlight(spotlightId)->setDistance(value);
}

const vector<string> EngineInterface::spotlight_getIds() const
{
	vector<string> result;

	for(const auto & [spotlightId, spotlight] : _core->getSpotlightManager()->getSpotlights())
	{
		result.push_back(spotlight->getId());
	}

	return result;
}

const fvec3 & EngineInterface::spotlight_getPosition(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getPosition();
}

const fvec3 & EngineInterface::spotlight_getFront(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getFront();
}

const fvec3 & EngineInterface::spotlight_getColor(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getColor();
}

const float EngineInterface::spotlight_getYaw(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getYaw();
}

const float EngineInterface::spotlight_getPitch(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getPitch();
}

const float EngineInterface::spotlight_getIntensity(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getIntensity();
}

const float EngineInterface::spotlight_getAngle(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getAngle();
}

const float EngineInterface::spotlight_getDistance(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->getDistance();
}

const int EngineInterface::spotlight_getMaxEntityCount() const
{
	return _core->getSpotlightManager()->getMaxSpotlightCount();
}

const bool EngineInterface::spotlight_isExisting(const string & spotlightId) const
{
	return _core->getSpotlightManager()->isSpotlightExisting(spotlightId);
}

const bool EngineInterface::spotlight_isVisible(const string & spotlightId) const
{
	return _core->getSpotlightManager()->getSpotlight(spotlightId)->isVisible();
}
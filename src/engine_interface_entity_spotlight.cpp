#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::spotlight_create(const string & spotlightId)
{
	_core->getSpotlightEntityManager()->createEntity(spotlightId);
}

void EngineInterface::spotlight_delete(const string & spotlightId)
{
	_core->getSpotlightEntityManager()->deleteEntity(spotlightId);
}

void EngineInterface::spotlight_setVisible(const string & spotlightId, bool value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setVisible(value);
}

void EngineInterface::spotlight_setPosition(const string & spotlightId, const fvec3 & value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setPosition(value);
}

void EngineInterface::spotlight_move(const string & spotlightId, const fvec3 & change)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->move(change);
}

void EngineInterface::spotlight_moveTo(const string & spotlightId, const fvec3 & target, float speed)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->moveTo(target, speed);
}

void EngineInterface::spotlight_setColor(const string & spotlightId, const fvec3 & value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setColor(value);
}

void EngineInterface::spotlight_setYaw(const string & spotlightId, float value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setYaw(value);
}

void EngineInterface::spotlight_setPitch(const string & spotlightId, float value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setPitch(value);
}

void EngineInterface::spotlight_setIntensity(const string & spotlightId, float value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setIntensity(value);
}

void EngineInterface::spotlight_setAngle(const string & spotlightId, float value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setAngle(value);
}

void EngineInterface::spotlight_setDistance(const string & spotlightId, float value)
{
	_core->getSpotlightEntityManager()->getEntity(spotlightId)->setDistance(value);
}

const vector<string> EngineInterface::spotlight_getIds() const
{
	vector<string> result;

	for(const auto & [spotlightId, entity] : _core->getSpotlightEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const fvec3 & EngineInterface::spotlight_getPosition(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getPosition();
}

const fvec3 & EngineInterface::spotlight_getFront(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getFront();
}

const fvec3 & EngineInterface::spotlight_getColor(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getColor();
}

const float EngineInterface::spotlight_getYaw(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getYaw();
}

const float EngineInterface::spotlight_getPitch(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getPitch();
}

const float EngineInterface::spotlight_getIntensity(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getIntensity();
}

const float EngineInterface::spotlight_getAngle(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getAngle();
}

const float EngineInterface::spotlight_getDistance(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->getDistance();
}

const int EngineInterface::spotlight_getMaxEntityCount() const
{
	return _core->getSpotlightEntityManager()->getMaxEntityCount();
}

const bool EngineInterface::spotlight_isExisting(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->isEntityExisting(spotlightId);
}

const bool EngineInterface::spotlight_isVisible(const string & spotlightId) const
{
	return _core->getSpotlightEntityManager()->getEntity(spotlightId)->isVisible();
}
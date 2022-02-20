#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::spotlight_create(const string& id)
{
	_core->getSpotlightEntityManager()->createEntity(id);
}

void EngineInterface::spotlight_delete(const string& id)
{
	_core->getSpotlightEntityManager()->deleteEntity(id);
}

void EngineInterface::spotlight_setVisible(const string& id, bool value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::spotlight_setPosition(const string& id, const fvec3& value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::spotlight_move(const string& id, const fvec3& change)
{
	_core->getSpotlightEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::spotlight_moveTo(const string& id, const fvec3& target, float speed)
{
	_core->getSpotlightEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::spotlight_setColor(const string& id, const fvec3& value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::spotlight_setYaw(const string& id, float value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setYaw(value);
}

void EngineInterface::spotlight_setPitch(const string& id, float value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setPitch(value);
}

void EngineInterface::spotlight_setIntensity(const string& id, float value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setIntensity(value);
}

void EngineInterface::spotlight_setAngle(const string& id, float value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setAngle(value);
}

void EngineInterface::spotlight_setDistance(const string& id, float value)
{
	_core->getSpotlightEntityManager()->getEntity(id)->setDistance(value);
}

const vector<string> EngineInterface::spotlight_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getSpotlightEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const fvec3& EngineInterface::spotlight_getPosition(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getPosition();
}

const fvec3& EngineInterface::spotlight_getFront(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getFront();
}

const fvec3& EngineInterface::spotlight_getColor(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getColor();
}

const float EngineInterface::spotlight_getYaw(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getYaw();
}

const float EngineInterface::spotlight_getPitch(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getPitch();
}

const float EngineInterface::spotlight_getIntensity(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getIntensity();
}

const float EngineInterface::spotlight_getAngle(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getAngle();
}

const float EngineInterface::spotlight_getDistance(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->getDistance();
}

const unsigned int EngineInterface::spotlight_getMaxEntityCount() const
{
	return _core->getSpotlightEntityManager()->getMaxEntityCount();
}

const bool EngineInterface::spotlight_isExisting(const string& id) const
{
	return _core->getSpotlightEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::spotlight_isVisible(const string& id) const
{
	return _core->getSpotlightEntityManager()->getEntity(id)->isVisible();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

const vector<string> EngineInterface::spotlight_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getSpotlightEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const fvec3 EngineInterface::spotlight_getPosition(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getPosition();
}

const fvec3 EngineInterface::spotlight_getFrontVector(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getFrontVector();
}

const fvec3 EngineInterface::spotlight_getColor(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getColor();
}

const float EngineInterface::spotlight_getYaw(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getYaw();
}

const float EngineInterface::spotlight_getPitch(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getPitch();
}

const float EngineInterface::spotlight_getIntensity(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getIntensity();
}

const float EngineInterface::spotlight_getAngle(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getAngle();
}

const float EngineInterface::spotlight_getDistance(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->getDistance();
}

const bool EngineInterface::spotlight_isExisting(const string& ID) const
{
	return _core->getSpotlightEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::spotlight_isVisible(const string& ID) const
{
	return _core->getSpotlightEntityManager()->getEntity(ID)->isVisible();
}
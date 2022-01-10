#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::pointlight_isExisting(const string& ID) const
{
	return _core->getPointlightEntityManager()->isEntityExisting(ID);
}

const  bool EngineInterface::pointlight_isVisible(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->isVisible();
}

const PointlightShape EngineInterface::pointlight_getShape(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getShape();
}

const fvec3 EngineInterface::pointlight_getPosition(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getPosition();
}

const fvec3 EngineInterface::pointlight_getRadius(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getRadius();
}

const fvec3 EngineInterface::pointlight_getColor(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getColor();
}

const float EngineInterface::pointlight_getIntensity(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getIntensity();
}

const vector<string> EngineInterface::pointlight_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getPointlightEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

const vector<string> EngineInterface::reflection_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getReflectionEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const fvec3 EngineInterface::reflection_getPosition(const string& ID) const
{
	return _core->getReflectionEntityManager()->getEntity(ID)->getPosition();
}

const bool EngineInterface::reflection_isExisting(const string& ID) const
{
	return _core->getReflectionEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::reflection_isVisible(const string& ID) const
{
	return _core->getReflectionEntityManager()->getEntity(ID)->isVisible();
}
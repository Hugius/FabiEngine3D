#include "fe3d.hpp"
#include "core_engine.hpp"

const vector<string> FabiEngine3D::reflection_getAllIDs() const
{
	vector<string> result;

	for(const auto& [keyID, entity] : _core->_reflectionEntityManager.getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const fvec3 FabiEngine3D::reflection_getPosition(const string& ID) const
{
	return _core->_reflectionEntityManager.getEntity(ID)->getPosition();
}

const bool FabiEngine3D::reflection_isExisting(const string& ID) const
{
	return _core->_reflectionEntityManager.isExisting(ID);
}

const bool FabiEngine3D::reflection_isVisible(const string& ID) const
{
	return _core->_reflectionEntityManager.getEntity(ID)->isVisible();
}
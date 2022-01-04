#include "fe3d.hpp"
#include "core.hpp"

const vector<string> FabiEngine3D::reflection_getIDs() const
{
	vector<string> result;

	for (const auto& [key, entity] : _core->_reflectionEntityManager.getEntities())
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
	return _core->_reflectionEntityManager.isEntityExisting(ID);
}

const bool FabiEngine3D::reflection_isVisible(const string& ID) const
{
	return _core->_reflectionEntityManager.getEntity(ID)->isVisible();
}
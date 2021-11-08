#include "fe3d.hpp"
#include "core_engine.hpp"

const vector<string> FabiEngine3D::reflectionEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_reflectionEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const Vec3 FabiEngine3D::reflectionEntity_getPosition(const string& ID) const
{
	return _core->_reflectionEntityManager.getEntity(ID)->getPosition();
}

const bool FabiEngine3D::reflectionEntity_isExisting(const string& ID) const
{
	return _core->_reflectionEntityManager.isExisting(ID);
}

const bool FabiEngine3D::reflectionEntity_isVisible(const string& ID) const
{
	return _core->_reflectionEntityManager.getEntity(ID)->isVisible();
}
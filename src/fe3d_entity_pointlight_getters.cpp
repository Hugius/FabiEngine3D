#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::pointlightEntity_isExisting(const string& ID) const
{
	return _core->_pointlightEntityManager.isExisting(ID);
}

const  bool FabiEngine3D::pointlightEntity_isVisible(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->isVisible();
}

const PointlightShape FabiEngine3D::pointlightEntity_getShape(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getShape();
}

const Vec3 FabiEngine3D::pointlightEntity_getPosition(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::pointlightEntity_getRadius(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getRadius();
}

const Vec3 FabiEngine3D::pointlightEntity_getColor(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::pointlightEntity_getIntensity(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getIntensity();
}

const vector<string> FabiEngine3D::pointlightEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_pointlightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}
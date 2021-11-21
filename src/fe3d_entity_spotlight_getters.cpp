#include "fe3d.hpp"
#include "core_engine.hpp"

const vector<string> FabiEngine3D::spotlight_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_spotlightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const Vec3 FabiEngine3D::spotlight_getPosition(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::spotlight_getColor(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::spotlight_getYaw(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getYaw();
}

const float FabiEngine3D::spotlight_getPitch(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getPitch();
}

const float FabiEngine3D::spotlight_getIntensity(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getIntensity();
}

const float FabiEngine3D::spotlight_getAngle(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getAngle();
}

const float FabiEngine3D::spotlight_getDistance(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->getDistance();
}

const bool FabiEngine3D::spotlight_isExisting(const string& ID) const
{
	return _core->_spotlightEntityManager.isExisting(ID);
}

const bool FabiEngine3D::spotlight_isVisible(const string& ID) const
{
	return _core->_spotlightEntityManager.getEntity(ID)->isVisible();
}
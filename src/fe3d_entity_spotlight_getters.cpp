#include "fe3d.hpp"
#include "core_engine.hpp"

const vector<string> FabiEngine3D::spotlightEntity_getAllIDs()
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_spotlightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const Vec3 FabiEngine3D::spotlightEntity_getPosition(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getPosition();
}

const Vec3 FabiEngine3D::spotlightEntity_getColor(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::spotlightEntity_getYaw(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getYaw();
}

const float FabiEngine3D::spotlightEntity_getPitch(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getPitch();
}

const float FabiEngine3D::spotlightEntity_getIntensity(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getIntensity();
}

const float FabiEngine3D::spotlightEntity_getAngle(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getAngle();
}

const float FabiEngine3D::spotlightEntity_getDistance(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->getDistance();
}

const bool FabiEngine3D::spotlightEntity_isExisting(const string& ID)
{
	return _core->_spotlightEntityManager.isExisting(ID);
}

const bool FabiEngine3D::spotlightEntity_isVisible(const string& ID)
{
	return _core->_spotlightEntityManager.getEntity(ID)->isVisible();
}
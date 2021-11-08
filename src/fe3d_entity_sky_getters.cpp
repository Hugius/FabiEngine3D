#include "fe3d.hpp"
#include "core_engine.hpp"

const string FabiEngine3D::skyEntity_getSelectedID() const
{
	if(_core->_skyEntityManager.getSelectedMainSky() != nullptr)
	{
		return _core->_skyEntityManager.getSelectedMainSky()->getID();
	}
	else
	{
		return "";
	}
}

const string FabiEngine3D::skyEntity_getMixID() const
{
	if(_core->_skyEntityManager.getSelectedMixSky() != nullptr)
	{
		return _core->_skyEntityManager.getSelectedMixSky()->getID();
	}
	else
	{
		return "";
	}
}

const vector<string> FabiEngine3D::skyEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_skyEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const array<string, 6>& FabiEngine3D::skyEntity_getDiffuseMapPaths(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
}

const float FabiEngine3D::skyEntity_getLightness(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getLightness();
}

const float FabiEngine3D::skyEntity_getOriginalLightness(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getOriginalLightness();
}

const float FabiEngine3D::skyEntity_getRotationSpeed(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getRotationSpeed();
}

const float FabiEngine3D::skyEntity_getMixValue() const
{
	return _core->_renderBus.getSkyMixValue();
}

const Vec3 FabiEngine3D::skyEntity_getColor(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::skyEntity_isExisting(const string& ID) const
{
	return _core->_skyEntityManager.isExisting(ID);
}

const bool FabiEngine3D::skyEntity_isVisible(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::skyEntity_isWireFramed(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->isWireFramed();
}

const bool FabiEngine3D::skyEntity_hasDiffuseMapRight(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths()[0].empty();
}

const bool FabiEngine3D::skyEntity_hasDiffuseMapLeft(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths()[1].empty();
}

const bool FabiEngine3D::skyEntity_hasDiffuseMapTop(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths()[2].empty();
}

const bool FabiEngine3D::skyEntity_hasDiffuseMapBottom(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths()[3].empty();
}

const bool FabiEngine3D::skyEntity_hasDiffuseMapBack(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths()[4].empty();
}

const bool FabiEngine3D::skyEntity_hasDiffuseMapFront(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths()[5].empty();
}
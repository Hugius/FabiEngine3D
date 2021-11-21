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

const Vec3 FabiEngine3D::skyEntity_getWireframeColor(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getWireframeColor();
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

const array<string, 6>& FabiEngine3D::skyEntity_getCubeMapPaths(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
}

const string& FabiEngine3D::skyEntity_getCubeMapRight(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[0];
}

const string& FabiEngine3D::skyEntity_getCubeMapLeft(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[1];
}

const string& FabiEngine3D::skyEntity_getCubeMapTop(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[2];
}

const string& FabiEngine3D::skyEntity_getCubeMapBottom(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[3];
}

const string& FabiEngine3D::skyEntity_getCubeMapBack(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[4];
}

const string& FabiEngine3D::skyEntity_getCubeMapFront(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[5];
}

const float FabiEngine3D::skyEntity_getLightness(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getLightness();
}

const float FabiEngine3D::skyEntity_getInitialLightness(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getInitialLightness();
}

const float FabiEngine3D::skyEntity_getRotation(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getRotation();
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

const bool FabiEngine3D::skyEntity_isWireframed(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::skyEntity_hasCubeMapRight(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[0].empty();
}

const bool FabiEngine3D::skyEntity_hasCubeMapLeft(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[1].empty();
}

const bool FabiEngine3D::skyEntity_hasCubeMapTop(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[2].empty();
}

const bool FabiEngine3D::skyEntity_hasCubeMapBottom(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[3].empty();
}

const bool FabiEngine3D::skyEntity_hasCubeMapBack(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[4].empty();
}

const bool FabiEngine3D::skyEntity_hasCubeMapFront(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[5].empty();
}
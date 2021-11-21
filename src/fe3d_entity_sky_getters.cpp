#include "fe3d.hpp"
#include "core_engine.hpp"

const string FabiEngine3D::sky_getSelectedID() const
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

const string FabiEngine3D::sky_getMixID() const
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

const Vec3 FabiEngine3D::sky_getWireframeColor(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getWireframeColor();
}

const vector<string> FabiEngine3D::sky_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_skyEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const array<string, 6>& FabiEngine3D::sky_getCubeMapPaths(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
}

const string& FabiEngine3D::sky_getCubeMapRight(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[0];
}

const string& FabiEngine3D::sky_getCubeMapLeft(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[1];
}

const string& FabiEngine3D::sky_getCubeMapTop(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[2];
}

const string& FabiEngine3D::sky_getCubeMapBottom(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[3];
}

const string& FabiEngine3D::sky_getCubeMapBack(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[4];
}

const string& FabiEngine3D::sky_getCubeMapFront(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[5];
}

const float FabiEngine3D::sky_getLightness(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getLightness();
}

const float FabiEngine3D::sky_getInitialLightness(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getInitialLightness();
}

const float FabiEngine3D::sky_getRotation(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::sky_getMixValue() const
{
	return _core->_renderBus.getSkyMixValue();
}

const Vec3 FabiEngine3D::sky_getColor(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::sky_isExisting(const string& ID) const
{
	return _core->_skyEntityManager.isExisting(ID);
}

const bool FabiEngine3D::sky_isVisible(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::sky_isWireframed(const string& ID) const
{
	return _core->_skyEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::sky_hasCubeMapRight(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[0].empty();
}

const bool FabiEngine3D::sky_hasCubeMapLeft(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[1].empty();
}

const bool FabiEngine3D::sky_hasCubeMapTop(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[2].empty();
}

const bool FabiEngine3D::sky_hasCubeMapBottom(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[3].empty();
}

const bool FabiEngine3D::sky_hasCubeMapBack(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[4].empty();
}

const bool FabiEngine3D::sky_hasCubeMapFront(const string& ID) const
{
	return !_core->_skyEntityManager.getEntity(ID)->getCubeMapPaths()[5].empty();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

const string EngineInterface::sky_getSelectedID() const
{
	if(_core->getSkyEntityManager()->getSelectedMainSky() != nullptr)
	{
		return _core->getSkyEntityManager()->getSelectedMainSky()->getID();
	}
	else
	{
		return "";
	}
}

const string EngineInterface::sky_getMixID() const
{
	if(_core->getSkyEntityManager()->getSelectedMixSky() != nullptr)
	{
		return _core->getSkyEntityManager()->getSelectedMixSky()->getID();
	}
	else
	{
		return "";
	}
}

const fvec3 EngineInterface::sky_getWireframeColor(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::sky_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getSkyEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const array<string, 6>& EngineInterface::sky_getCubeMapPaths(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
}

const string& EngineInterface::sky_getRightCubeMap(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[0];
}

const string& EngineInterface::sky_getLeftCubeMap(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[1];
}

const string& EngineInterface::sky_getTopCubeMap(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[2];
}

const string& EngineInterface::sky_getBottomCubeMap(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[3];
}

const string& EngineInterface::sky_getBackCubeMap(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[4];
}

const string& EngineInterface::sky_getFrontCubeMap(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[5];
}

const float EngineInterface::sky_getLightness(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::sky_getInitialLightness(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getInitialLightness();
}

const float EngineInterface::sky_getRotation(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getRotation();
}

const float EngineInterface::sky_getMixValue() const
{
	return _core->getRenderBus()->getSkyMixValue();
}

const fvec3 EngineInterface::sky_getColor(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::sky_isExisting(const string& ID) const
{
	return _core->getSkyEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::sky_isVisible(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::sky_isWireframed(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::sky_hasRightCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[0].empty();
}

const bool EngineInterface::sky_hasLeftCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[1].empty();
}

const bool EngineInterface::sky_hasTopCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[2].empty();
}

const bool EngineInterface::sky_hasBottomCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[3].empty();
}

const bool EngineInterface::sky_hasBackCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[4].empty();
}

const bool EngineInterface::sky_hasFrontCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[5].empty();
}
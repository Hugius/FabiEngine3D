#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::water_isExisting(const string& ID) const
{
	return _core->getWaterEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::water_isVisible(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::water_isSpecular(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->isSpecular();
}

const bool EngineInterface::water_isReflective(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->isReflective();
}

const bool EngineInterface::water_isRefractive(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->isRefractive();
}

const bool EngineInterface::water_isWireframed(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::water_hasDudvMap(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->hasDudvMap();
}

const bool EngineInterface::water_hasNormalMap(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->hasNormalMap();
}

const bool EngineInterface::water_hasDisplacementMap(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->hasDisplacementMap();
}

const string EngineInterface::water_getSelectedID() const
{
	if(_core->getWaterEntityManager()->getSelectedWater() != nullptr)
	{
		return _core->getWaterEntityManager()->getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

const fvec3 EngineInterface::water_getWireframeColor(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::water_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getWaterEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const float EngineInterface::water_getSize(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getSize();
}

const float EngineInterface::water_getTextureRepeat(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getTextureRepeat();
}

const fvec2 EngineInterface::water_getSpeed(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getSpeed();
}

const float EngineInterface::water_getWaveHeight(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getWaveHeight();
}

const float EngineInterface::water_getSpecularShininess(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getSpecularShininess();
}

const float EngineInterface::water_getSpecularIntensity(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getSpecularIntensity();
}

const float EngineInterface::water_getTransparency(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getTransparency();
}

const WaterQuality EngineInterface::water_getQuality(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getQuality();
}

const string& EngineInterface::water_getDudvMapPath(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getDudvMapPath();
}

const string& EngineInterface::water_getNormalMapPath(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getNormalMapPath();
}

const string& EngineInterface::water_getDisplacementMapPath(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getDisplacementMapPath();
}

const float EngineInterface::water_getHeight(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getHeight();
}

const fvec3 EngineInterface::water_getColor(const string& ID) const
{
	return _core->getWaterEntityManager()->getEntity(ID)->getColor();
}
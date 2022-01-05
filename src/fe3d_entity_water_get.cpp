#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::water_isExisting(const string& ID) const
{
	return _core->_waterEntityManager->isEntityExisting(ID);
}

const bool FabiEngine3D::water_isVisible(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->isVisible();
}

const bool FabiEngine3D::water_isSpecular(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->isSpecular();
}

const bool FabiEngine3D::water_isReflective(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->isReflective();
}

const bool FabiEngine3D::water_isRefractive(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->isRefractive();
}

const bool FabiEngine3D::water_isWireframed(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::water_hasDudvMap(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->hasDudvMap();
}

const bool FabiEngine3D::water_hasNormalMap(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::water_hasDisplacementMap(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->hasDisplacementMap();
}

const string FabiEngine3D::water_getSelectedID() const
{
	if(_core->_waterEntityManager->getSelectedWater() != nullptr)
	{
		return _core->_waterEntityManager->getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

const fvec3 FabiEngine3D::water_getWireframeColor(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getWireframeColor();
}

const vector<string> FabiEngine3D::water_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->_waterEntityManager->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const float FabiEngine3D::water_getSize(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getSize();
}

const float FabiEngine3D::water_getTextureRepeat(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getTextureRepeat();
}

const fvec2 FabiEngine3D::water_getSpeed(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getSpeed();
}

const float FabiEngine3D::water_getWaveHeight(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getWaveHeight();
}

const float FabiEngine3D::water_getSpecularShininess(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getSpecularShininess();
}

const float FabiEngine3D::water_getSpecularIntensity(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getSpecularIntensity();
}

const float FabiEngine3D::water_getTransparency(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getTransparency();
}

const WaterQuality FabiEngine3D::water_getQuality(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getQuality();
}

const string& FabiEngine3D::water_getDudvMapPath(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getDudvMapPath();
}

const string& FabiEngine3D::water_getNormalMapPath(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::water_getDisplacementMapPath(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getDisplacementMapPath();
}

const float FabiEngine3D::water_getHeight(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getHeight();
}

const fvec3 FabiEngine3D::water_getColor(const string& ID) const
{
	return _core->_waterEntityManager->getEntity(ID)->getColor();
}
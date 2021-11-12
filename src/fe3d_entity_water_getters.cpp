#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::waterEntity_isExisting(const string& ID) const
{
	return _core->_waterEntityManager.isExisting(ID);
}

const bool FabiEngine3D::waterEntity_isVisible(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::waterEntity_isSpecular(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->isSpecular();
}

const bool FabiEngine3D::waterEntity_isReflective(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->isReflective();
}

const bool FabiEngine3D::waterEntity_isRefractive(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->isRefractive();
}

const bool FabiEngine3D::waterEntity_isWireframed(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::waterEntity_hasDudvMap(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->hasDudvMap();
}

const bool FabiEngine3D::waterEntity_hasNormalMap(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::waterEntity_hasDisplacementMap(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->hasDisplacementMap();
}

const string FabiEngine3D::waterEntity_getSelectedID() const
{
	if(_core->_waterEntityManager.getSelectedWater() != nullptr)
	{
		return _core->_waterEntityManager.getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

const vector<string> FabiEngine3D::waterEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_waterEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const float FabiEngine3D::waterEntity_getSize(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getSize();
}

const float FabiEngine3D::waterEntity_getTextureRepeat(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getTextureRepeat();
}

const Vec2 FabiEngine3D::waterEntity_getSpeed(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getSpeed();
}

const float FabiEngine3D::waterEntity_getWaveHeight(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getWaveHeight();
}

const float FabiEngine3D::waterEntity_getSpecularShininess(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getSpecularShininess();
}

const float FabiEngine3D::waterEntity_getSpecularIntensity(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getSpecularIntensity();
}

const float FabiEngine3D::waterEntity_getTransparency(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getTransparency();
}

const WaterQuality FabiEngine3D::waterEntity_getQuality(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getQuality();
}

const string& FabiEngine3D::waterEntity_getDudvMapPath(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getDudvMapPath();
}

const string& FabiEngine3D::waterEntity_getNormalMapPath(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::waterEntity_getDisplacementMapPath(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getDisplacementMapPath();
}

const float FabiEngine3D::waterEntity_getHeight(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getHeight();
}

const Vec3 FabiEngine3D::waterEntity_getColor(const string& ID) const
{
	return _core->_waterEntityManager.getEntity(ID)->getColor();
}
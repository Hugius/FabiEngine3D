#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::terrainEntity_isExisting(const string& ID)
{
	return _core->_terrainEntityManager.isExisting(ID);
}

const bool FabiEngine3D::terrainEntity_isVisible(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::terrainEntity_isSpecular(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isSpecular();
}

const bool FabiEngine3D::terrainEntity_isWireFramed(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isWireFramed();
}

const float FabiEngine3D::terrainEntity_getSize(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSize();
}

const float FabiEngine3D::terrainEntity_getMaxHeight(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::terrainEntity_getTextureRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getTextureRepeat();
}

const bool FabiEngine3D::terrainEntity_isInside(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.isInside(ID, x, z);
}

const bool FabiEngine3D::terrainEntity_hasBlendMap(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasBlendMap();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMap(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMapR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapR();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMapG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapG();
}

const bool FabiEngine3D::terrainEntity_hasDiffuseMapB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapB();
}

const bool FabiEngine3D::terrainEntity_hasNormalMap(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::terrainEntity_hasNormalMapR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapR();
}

const bool FabiEngine3D::terrainEntity_hasNormalMapG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapG();
}

const bool FabiEngine3D::terrainEntity_hasNormalMapB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapB();
}

const float FabiEngine3D::terrainEntity_getPixelHeight(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.getPixelHeight(ID, x, z);
}

const float FabiEngine3D::terrainEntity_getSpecularShininess(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularShininess();
}

const float FabiEngine3D::terrainEntity_getSpecularIntensity(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularIntensity();
}

const string& FabiEngine3D::terrainEntity_getSelectedID()
{
	if(_core->_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		return _core->_terrainEntityManager.getSelectedTerrain()->getID();
	}
	else
	{
		return "";
	}
}

const vector<string> FabiEngine3D::terrainEntity_getAllIDs()
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPath();
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathR();
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathG();
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathB();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathR();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathG();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathB();
}

const float FabiEngine3D::terrainEntity_getRedRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getRedRepeat();
}

const float FabiEngine3D::terrainEntity_getGreenRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getGreenRepeat();
}

const float FabiEngine3D::terrainEntity_getBlueRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlueRepeat();
}

const float FabiEngine3D::terrainEntity_getLightness(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getLightness();
}

const string& FabiEngine3D::terrainEntity_getHeightMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getHeightMapPath();
}
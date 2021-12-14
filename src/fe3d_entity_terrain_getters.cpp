#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::terrain_isExisting(const string& ID) const
{
	return _core->_terrainEntityManager.isExisting(ID);
}

const bool FabiEngine3D::terrain_isVisible(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::terrain_isSpecular(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->isSpecular();
}

const bool FabiEngine3D::terrain_isWireframed(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->isWireframed();
}

const float FabiEngine3D::terrain_getSize(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getSize();
}

const float FabiEngine3D::terrain_getMaxHeight(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::terrain_getTextureRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getTextureRepeat();
}

const bool FabiEngine3D::terrain_isInside(const string& ID, float x, float z) const
{
	return _core->_terrainEntityManager.isInside(ID, x, z);
}

const bool FabiEngine3D::terrain_hasBlendMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasBlendMap();
}

const bool FabiEngine3D::terrain_hasDiffuseMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::terrain_hasDiffuseMapR(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapR();
}

const bool FabiEngine3D::terrain_hasDiffuseMapG(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapG();
}

const bool FabiEngine3D::terrain_hasDiffuseMapB(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasDiffuseMapB();
}

const bool FabiEngine3D::terrain_hasNormalMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::terrain_hasNormalMapR(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapR();
}

const bool FabiEngine3D::terrain_hasNormalMapG(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapG();
}

const bool FabiEngine3D::terrain_hasNormalMapB(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMapB();
}

const float FabiEngine3D::terrain_getPixelHeight(const string& ID, float x, float z) const
{
	return _core->_terrainEntityManager.getPixelHeight(ID, x, z);
}

const float FabiEngine3D::terrain_getSpecularShininess(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularShininess();
}

const float FabiEngine3D::terrain_getSpecularIntensity(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularIntensity();
}

const string FabiEngine3D::terrain_getSelectedID() const
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

const vector<string> FabiEngine3D::terrain_getAllIDs() const
{
	vector<string> result;

	for(const auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& FabiEngine3D::terrain_getDiffuseMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::terrain_getNormalMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::terrain_getBlendMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPath();
}

const string& FabiEngine3D::terrain_getDiffuseMapPathR(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathR();
}

const string& FabiEngine3D::terrain_getDiffuseMapPathG(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathG();
}

const string& FabiEngine3D::terrain_getDiffuseMapPathB(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathB();
}

const string& FabiEngine3D::terrain_getNormalMapPathR(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathR();
}

const string& FabiEngine3D::terrain_getNormalMapPathG(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathG();
}

const string& FabiEngine3D::terrain_getNormalMapPathB(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathB();
}

const fvec3 FabiEngine3D::terrain_getWireframeColor(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getWireframeColor();
}

const float FabiEngine3D::terrain_getRedRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getRedRepeat();
}

const float FabiEngine3D::terrain_getGreenRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getGreenRepeat();
}

const float FabiEngine3D::terrain_getBlueRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlueRepeat();
}

const float FabiEngine3D::terrain_getLightness(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getLightness();
}

const string& FabiEngine3D::terrain_getHeightMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getHeightMapPath();
}
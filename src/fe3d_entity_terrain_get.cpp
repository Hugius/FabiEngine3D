#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::terrain_isExisting(const string& ID) const
{
	return _core->_terrainEntityManager.isEntityExisting(ID);
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

const bool FabiEngine3D::terrain_hasRedDiffuseMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasRedDiffuseMap();
}

const bool FabiEngine3D::terrain_hasGreenDiffuseMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasGreenDiffuseMap();
}

const bool FabiEngine3D::terrain_hasBlueDiffuseMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasBlueDiffuseMap();
}

const bool FabiEngine3D::terrain_hasNormalMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::terrain_hasRedNormalMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasRedNormalMap();
}

const bool FabiEngine3D::terrain_hasGreenNormalMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasGreenNormalMap();
}

const bool FabiEngine3D::terrain_hasBlueNormalMap(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->hasBlueNormalMap();
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

const vector<string> FabiEngine3D::terrain_getIDs() const
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

const string& FabiEngine3D::terrain_getRedDiffuseMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getRedDiffuseMapPath();
}

const string& FabiEngine3D::terrain_getGreenDiffuseMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getGreenDiffuseMapPath();
}

const string& FabiEngine3D::terrain_getBlueDiffuseMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlueDiffuseMapPath();
}

const string& FabiEngine3D::terrain_getRedNormalMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getRedNormalMapPath();
}

const string& FabiEngine3D::terrain_getGreenNormalMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getGreenNormalMapPath();
}

const string& FabiEngine3D::terrain_getBlueNormalMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlueNormalMapPath();
}

const fvec3 FabiEngine3D::terrain_getWireframeColor(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getWireframeColor();
}

const float FabiEngine3D::terrain_getRedTextureRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getRedTextureRepeat();
}

const float FabiEngine3D::terrain_getGreenTextureRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getGreenTextureRepeat();
}

const float FabiEngine3D::terrain_getBlueTextureRepeat(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlueTextureRepeat();
}

const float FabiEngine3D::terrain_getLightness(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getLightness();
}

const string& FabiEngine3D::terrain_getHeightMapPath(const string& ID) const
{
	return _core->_terrainEntityManager.getEntity(ID)->getHeightMapPath();
}
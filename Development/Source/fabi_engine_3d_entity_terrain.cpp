#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::terrainEntity_add(const string& ID, const string& heightmapName, const string& textureName, vec3 pos, float size, float maxHeight, float uvRepeat, float lightness)
{
	_core->_terrainEntityManager.addTerrainEntity(ID, heightmapName, textureName, pos, size, maxHeight, uvRepeat, lightness);
}

void FabiEngine3D::terrainEntity_delete(const string& ID)
{
	// Unselect terrain if selected
	if (ID == terrainEntity_getSelectedID())
	{
		_core->_terrainEntityManager.selectTerrain("");
	}

	_core->_terrainEntityManager.deleteEntity(ID, EntityType::TERRAIN);
}

void FabiEngine3D::terrainEntity_hide(const string& ID)
{
	_core->_terrainEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::terrainEntity_show(const string& ID)
{
	_core->_terrainEntityManager.getEntity(ID)->setEnabled(true);
}

bool FabiEngine3D::terrainEntity_isExisting(const string& ID)
{
	return _core->_terrainEntityManager.isExisting(ID);
}

float FabiEngine3D::terrainEntity_getSize(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSize();
}

float FabiEngine3D::terrainEntity_getMaxHeight(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getMaxHeight();
}

bool FabiEngine3D::terrainEntity_isInside(float x, float z)
{
	return _core->_terrainEntityManager.isInside(x, z);
}

vec3 FabiEngine3D::terrainEntity_getMousePoint()
{
	return _core->_mousePicker.getTerrainPoint();
}

float FabiEngine3D::terrainEntity_getPixelHeight(float x, float z)
{
	return _core->_terrainEntityManager.getPixelHeight(x, z);
}

string FabiEngine3D::terrainEntity_getSelectedID()
{
	if (_core->_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		return _core->_terrainEntityManager.getSelectedTerrain()->getID();
	}
	else
	{
		return "";
	}
}

void FabiEngine3D::terrainEntity_select(const string& ID)
{
	_core->_terrainEntityManager.selectTerrain(ID);
}

void FabiEngine3D::terrainEntity_addBlending
(
	const string& ID, const string blendmapName, const string blendmapNameR,
	const string blendmapNameG, const string blendmapNameB,
	float blendRepeatR, float blendRepeatG, float blendRepeatB
)
{
	_core->_terrainEntityManager.addBlendingToTerrain(ID, blendmapName, blendmapNameR, blendmapNameG, blendmapNameB, blendRepeatR, blendRepeatG, blendRepeatB);
}
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::terrainEntity_add(const string& ID)
{
	_core->_terrainEntityManager.addTerrain(ID);
}

void FabiEngine3D::terrainEntity_setHeightmap(const string& ID, const string& heightMapPath)
{
	auto& pixelColors = _core->_texLoader.getHeightMap(heightMapPath);
	_core->_terrainEntityManager.getEntity(ID)->setHeightMapPath(heightMapPath);
	_core->_terrainEntityManager.getEntity(ID)->setPixelColors(pixelColors);
	_core->_terrainEntityManager.getEntity(ID)->setSize(static_cast<float>(sqrt(pixelColors.size())));
	_core->_terrainEntityManager.generateModel(ID);
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
	_core->_terrainEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::terrainEntity_show(const string& ID)
{
	_core->_terrainEntityManager.getEntity(ID)->setVisible(true);
}

bool FabiEngine3D::terrainEntity_isExisting(const string& ID)
{
	return _core->_terrainEntityManager.isExisting(ID);
}

bool FabiEngine3D::terrainEntity_isVisible(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::terrainEntity_isSpecularLighted(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isSpecularLighted();
}

bool FabiEngine3D::terrainEntity_isBlendMapped(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isBlendMapped();
}

float FabiEngine3D::terrainEntity_getSize(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSize();
}

float FabiEngine3D::terrainEntity_getMaxHeight(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getMaxHeight();
}

float FabiEngine3D::terrainEntity_getUvRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getUvRepeat();
}

bool FabiEngine3D::terrainEntity_isInside(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.isInside(ID, x, z);
}

vec3 FabiEngine3D::terrainEntity_getMousePoint()
{
	return _core->_mousePicker.getTerrainPoint();
}

bool FabiEngine3D::terrainEntity_isValidMousePoint()
{
	return _core->_mousePicker.isValidTerrainPoint();
}

float FabiEngine3D::terrainEntity_getPixelHeight(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.getPixelHeight(ID, x, z);
}

float FabiEngine3D::terrainEntity_getSpecularLightingIntensity(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularLightingIntensity();
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

const string& FabiEngine3D::terrainEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPath();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPathR();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPathG();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPathB();
}

float FabiEngine3D::terrainEntity_getBlendRepeatR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatR();
}

float FabiEngine3D::terrainEntity_getBlendRepeatG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatG();
}

float FabiEngine3D::terrainEntity_getBlendRepeatB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatB();
}

float FabiEngine3D::terrainEntity_getLightness(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getLightness();
}

const string& FabiEngine3D::terrainEntity_getHeightMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getHeightMapPath();
}

void FabiEngine3D::terrainEntity_select(const string& ID)
{
	_core->_terrainEntityManager.selectTerrain(ID);
}

void FabiEngine3D::terrainEntity_setMaxHeight(const string& ID, float height)
{
	_core->_terrainEntityManager.getEntity(ID)->setMaxHeight(height);
	_core->_terrainEntityManager.generateModel(ID);
}

void FabiEngine3D::terrainEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setUvRepeat(repeat);
	_core->_terrainEntityManager.generateModel(ID);
}

void FabiEngine3D::terrainEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendMap(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMap(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapPath(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendMapR(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapR(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapPathR(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendMapG(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapG(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapPathG(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendMapB(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapB(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapPathB(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendRepeatR(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatR(repeat);
}

void FabiEngine3D::terrainEntity_setBlendRepeatG(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatG(repeat);
}

void FabiEngine3D::terrainEntity_setBlendRepeatB(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatB(repeat);
}

void FabiEngine3D::terrainEntity_setSpecularLightingIntensity(const string& ID, float intensity)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLightingIntensity(intensity);
}

void FabiEngine3D::terrainEntity_setLightness(const string& ID, float lightness)
{
	_core->_terrainEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::terrainEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}

void FabiEngine3D::terrainEntity_setBlendMapped(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapped(enabled);
}
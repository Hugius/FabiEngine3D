#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::waterEntity_add(const string& ID)
{
	_core->_waterEntityManager.addWaterEntity(ID);
	_core->_waterEntityManager.generateModel(ID);
}

void FabiEngine3D::waterEntity_deleteAll()
{
	// For every WATER entity
	for (auto& entity : _core->_waterEntityManager.getEntities())
	{
		waterEntity_delete(entity->getID());
	}
}

void FabiEngine3D::waterEntity_delete(const string& ID)
{
	// Unselect water if selected
	if (ID == waterEntity_getSelectedID())
	{
		_core->_waterEntityManager.selectWater("");
	}

	_core->_waterEntityManager.deleteEntity(ID);
}

void FabiEngine3D::waterEntity_hide(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::waterEntity_show(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setVisible(true);
}

bool FabiEngine3D::waterEntity_isExisting(const string& ID)
{
	return _core->_waterEntityManager.isExisting(ID);
}

bool FabiEngine3D::waterEntity_isVisible(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::waterEntity_isWaving(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isWaving();
}

bool FabiEngine3D::waterEntity_isRippling(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isRippling();
}

bool FabiEngine3D::waterEntity_isSpecularLighted(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isSpecularLighted();
}

bool FabiEngine3D::waterEntity_isReflective(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isReflective();
}

bool FabiEngine3D::waterEntity_isRefractive(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isRefractive();
}

void FabiEngine3D::waterEntity_select(const string& ID)
{
	_core->_waterEntityManager.selectWater(ID);
}

void FabiEngine3D::waterEntity_setPosition(const string& ID, Vec3 position)
{
	_core->_waterEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::waterEntity_setSize(const string& ID, float size)
{
	_core->_waterEntityManager.getEntity(ID)->setSize(size);
	_core->_waterEntityManager.generateModel(ID);
}

void FabiEngine3D::waterEntity_setWaving(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setWaving(enabled);
}

void FabiEngine3D::waterEntity_setRippling(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setRippling(enabled);
}

void FabiEngine3D::waterEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}

void FabiEngine3D::waterEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_waterEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

void FabiEngine3D::waterEntity_setReflective(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setReflective(enabled);
}

void FabiEngine3D::waterEntity_setRefractive(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setRefractive(enabled);
}

void FabiEngine3D::waterEntity_setDudvMap(const string& ID, const string& texturePath)
{
	_core->_waterEntityManager.getEntity(ID)->setDudvMap(_core->_texLoader.getTexture(texturePath, false, false));
	_core->_waterEntityManager.getEntity(ID)->setDudvMapPath(texturePath);
}

void FabiEngine3D::waterEntity_setNormalMap(const string& ID, const string& texturePath)
{
	_core->_waterEntityManager.getEntity(ID)->setNormalMap(_core->_texLoader.getTexture(texturePath, false, false));
	_core->_waterEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
}

void FabiEngine3D::waterEntity_setDisplacementMap(const string& ID, const string& texturePath)
{
	_core->_waterEntityManager.getEntity(ID)->setDisplacementMap(_core->_texLoader.getTexture(texturePath, false, false));
	_core->_waterEntityManager.getEntity(ID)->setDisplacementMapPath(texturePath);
}

void FabiEngine3D::waterEntity_setWaveHeightFactor(const string& ID, float factor)
{
	_core->_waterEntityManager.getEntity(ID)->setWaveHeightFactor(factor);
}

void FabiEngine3D::waterEntity_setSpecularLightingFactor(const string& ID, float factor)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecularLightingFactor(factor);
}

void FabiEngine3D::waterEntity_setSpecularLightingIntensity(const string& ID, float intensity)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecularLightingIntensity(intensity);
}

void FabiEngine3D::waterEntity_setSpeed(const string& ID, Vec2 speed)
{
	_core->_waterEntityManager.getEntity(ID)->setSpeed(speed);
}

void FabiEngine3D::waterEntity_setColor(const string& ID, Vec3 color)
{
	_core->_waterEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::waterEntity_setTransparency(const string& ID, float transparency)
{
	_core->_waterEntityManager.getEntity(ID)->setTransparency(transparency);
}

string FabiEngine3D::waterEntity_getSelectedID()
{
	if (_core->_waterEntityManager.getSelectedWater() != nullptr)
	{
		return _core->_waterEntityManager.getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

vector<string> FabiEngine3D::waterEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto entity : _core->_waterEntityManager.getEntities()) // Loop over WATER entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

float FabiEngine3D::waterEntity_getSize(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSize();
}

float FabiEngine3D::waterEntity_getUvRepeat(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getUvRepeat();
}

Vec2 FabiEngine3D::waterEntity_getSpeed(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSpeed();
}

float FabiEngine3D::waterEntity_getWaveHeightFactor(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getWaveHeightFactor();
}

float FabiEngine3D::waterEntity_getSpecularLightingFactor(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSpecularLightingFactor();
}

float FabiEngine3D::waterEntity_getSpecularLightingIntensity(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSpecularLightingIntensity();
}

float FabiEngine3D::waterEntity_getTransparency(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getTransparency();
}

const string& FabiEngine3D::waterEntity_getDudvMapPath(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getDudvMapPath();
}

const string& FabiEngine3D::waterEntity_getNormalMapPath(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::waterEntity_getDisplacementMapPath(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getDisplacementMapPath();
}

Vec3 FabiEngine3D::waterEntity_getPosition(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getPosition();
}

Vec3 FabiEngine3D::waterEntity_getColor(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getColor();
}
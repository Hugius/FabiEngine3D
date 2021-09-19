#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::waterEntity_create(const string& ID)
{
	_core->_waterEntityManager.createEntity(ID);
}

void FabiEngine3D::waterEntity_deleteAll()
{
	// For every water entity
	for (const auto& [keyID, entity] : _core->_waterEntityManager.getEntities())
	{
		waterEntity_delete(entity->getID());
	}

	// Unselect water
	_core->_waterEntityManager.selectWater("");
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

void FabiEngine3D::waterEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_waterEntityManager.getEntity(ID)->setVisible(isVisible);
}

const bool FabiEngine3D::waterEntity_isExisting(const string& ID)
{
	return _core->_waterEntityManager.isExisting(ID);
}

const bool FabiEngine3D::waterEntity_isVisible(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::waterEntity_isSpecularLighted(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isSpecularLighted();
}

const bool FabiEngine3D::waterEntity_isReflective(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isReflective();
}

const bool FabiEngine3D::waterEntity_isRefractive(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isRefractive();
}

const bool FabiEngine3D::waterEntity_isWireFramed(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->isWireFramed();
}

const bool FabiEngine3D::waterEntity_hasDudvMap(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->hasDudvMap();
}

const bool FabiEngine3D::waterEntity_hasNormalMap(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->hasNormalMap();
}

const bool FabiEngine3D::waterEntity_hasDisplacementMap(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->hasDisplacementMap();
}

void FabiEngine3D::waterEntity_select(const string& ID)
{
	_core->_waterEntityManager.selectWater(ID);
}

void FabiEngine3D::waterEntity_setHeight(const string& ID, float height)
{
	_core->_waterEntityManager.getEntity(ID)->setHeight(height);
}

void FabiEngine3D::waterEntity_setSize(const string& ID, float size)
{
	if (size > WaterEntityManager::MAX_SIZE)
	{
		Logger::throwWarning("Tried to set size of water with ID \"" + ID + "\": too high!");
		return;
	}

	_core->_waterEntityManager.getEntity(ID)->setSize(size);
	_core->_waterEntityManager.loadMesh(ID);
}

void FabiEngine3D::waterEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}

void FabiEngine3D::waterEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_waterEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

void FabiEngine3D::waterEntity_setQuality(const string& ID, WaterQuality quality)
{
	_core->_waterEntityManager.getEntity(ID)->setQuality(quality);
}

void FabiEngine3D::waterEntity_setReflective(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setReflective(enabled);
}

void FabiEngine3D::waterEntity_setRefractive(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setRefractive(enabled);
}

void FabiEngine3D::waterEntity_setWireFramed(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setWireFramed(enabled);
}

void FabiEngine3D::waterEntity_setDudvMap(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_waterEntityManager.getEntity(ID)->setDudvMap(0);
		_core->_waterEntityManager.getEntity(ID)->setDudvMapPath("");
	}
	else
	{
		_core->_waterEntityManager.getEntity(ID)->setDudvMap(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_waterEntityManager.getEntity(ID)->setDudvMapPath(texturePath);
	}
}

void FabiEngine3D::waterEntity_setNormalMap(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_waterEntityManager.getEntity(ID)->setNormalMap(0);
		_core->_waterEntityManager.getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		_core->_waterEntityManager.getEntity(ID)->setNormalMap(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_waterEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
	}
}

void FabiEngine3D::waterEntity_setDisplacementMap(const string& ID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMap(0);
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMapPath("");
	}
	else
	{
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMap(_core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMapPath(texturePath);
	}
}

void FabiEngine3D::waterEntity_setWaveHeight(const string& ID, float height)
{
	_core->_waterEntityManager.getEntity(ID)->setWaveHeight(height);
}

void FabiEngine3D::waterEntity_setSpecularShininess(const string& ID, float shininess)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecularShininess(shininess);
}

void FabiEngine3D::waterEntity_setSpecularIntensity(const string& ID, float intensity)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecularIntensity(intensity);
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

const string FabiEngine3D::waterEntity_getSelectedID()
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

const vector<string> FabiEngine3D::waterEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_waterEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const float FabiEngine3D::waterEntity_getSize(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSize();
}

const float FabiEngine3D::waterEntity_getUvRepeat(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getUvRepeat();
}

const Vec2 FabiEngine3D::waterEntity_getSpeed(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSpeed();
}

const float FabiEngine3D::waterEntity_getWaveHeight(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getWaveHeight();
}

const float FabiEngine3D::waterEntity_getSpecularShininess(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSpecularShininess();
}

const float FabiEngine3D::waterEntity_getSpecularIntensity(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSpecularIntensity();
}

const float FabiEngine3D::waterEntity_getTransparency(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getTransparency();
}

const WaterQuality FabiEngine3D::waterEntity_getQuality(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getQuality();
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

const float FabiEngine3D::waterEntity_getHeight(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getHeight();
}

const Vec3 FabiEngine3D::waterEntity_getColor(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getColor();
}
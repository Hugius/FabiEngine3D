#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::waterEntity_create(const string& ID)
{
	_core->_waterEntityManager.createEntity(ID);
}

void FabiEngine3D::waterEntity_deleteAll()
{
	// For every water entity
	for(const auto& [keyID, entity] : _core->_waterEntityManager.getEntities())
	{
		waterEntity_delete(entity->getID());
	}

	// Unselect water
	_core->_waterEntityManager.selectWater("");
}

void FabiEngine3D::waterEntity_delete(const string& ID)
{
	// Unselect water if selected
	if(ID == waterEntity_getSelectedID())
	{
		_core->_waterEntityManager.selectWater("");
	}

	_core->_waterEntityManager.deleteEntity(ID);
}

void FabiEngine3D::waterEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_waterEntityManager.getEntity(ID)->setVisible(isVisible);
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
	if(size > WaterEntityManager::MAX_SIZE)
	{
		Logger::throwWarning("Tried to set size of water with ID \"" + ID + "\": too high!");
		return;
	}

	_core->_waterEntityManager.getEntity(ID)->setSize(size);
	_core->_waterEntityManager.loadMesh(ID);
}

void FabiEngine3D::waterEntity_setSpecular(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setSpecular(enabled);
}

void FabiEngine3D::waterEntity_setTextureRepeat(const string& ID, float repeat)
{
	_core->_waterEntityManager.getEntity(ID)->setTextureRepeat(repeat);
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

void FabiEngine3D::waterEntity_setWireframed(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setWireframed(enabled);
}

void FabiEngine3D::waterEntity_setDudvMap(const string& ID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_waterEntityManager.getEntity(ID)->setDudvMap(0);
		_core->_waterEntityManager.getEntity(ID)->setDudvMapPath("");
	}
	else
	{
		_core->_waterEntityManager.getEntity(ID)->setDudvMap(_core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_waterEntityManager.getEntity(ID)->setDudvMapPath(texturePath);
	}
}

void FabiEngine3D::waterEntity_setNormalMap(const string& ID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_waterEntityManager.getEntity(ID)->setNormalMap(0);
		_core->_waterEntityManager.getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		_core->_waterEntityManager.getEntity(ID)->setNormalMap(_core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_waterEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
	}
}

void FabiEngine3D::waterEntity_setDisplacementMap(const string& ID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMap(0);
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMapPath("");
	}
	else
	{
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMap(_core->_textureLoader.loadTexture2D(texturePath, true, true));
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
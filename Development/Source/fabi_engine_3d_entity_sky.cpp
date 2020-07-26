#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::skyEntity_add(const string& ID, const vector<string> texturePaths)
{
	_core->_skyEntityManager.addSkyEntity(ID, _core->_texLoader, texturePaths);
}

void FabiEngine3D::skyEntity_delete(const string& ID)
{
	// Unselect sky if selected
	if (ID == skyEntity_getSelectedID())
	{
		_core->_skyEntityManager.selectSky("");
	}

	_core->_skyEntityManager.deleteEntity(ID, EntityType::SKY);
}

void FabiEngine3D::skyEntity_hide(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::skyEntity_show(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::skyEntity_select(const string& ID)
{
	_core->_skyEntityManager.selectSky(ID);
}

void FabiEngine3D::skyEntity_setLightness(const string& ID, float lightness)
{
	_core->_skyEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::skyEntity_setRotationSpeed(const string& ID, float speed)
{
	_core->_skyEntityManager.getEntity(ID)->setRotationSpeed(speed);
}

void FabiEngine3D::skyEntity_setColor(const string& ID, vec3 color)
{
	_core->_skyEntityManager.getEntity(ID)->setColor(color);
}

string FabiEngine3D::skyEntity_getSelectedID()
{
	if (_core->_skyEntityManager.getSelectedSky() != nullptr)
	{
		return _core->_skyEntityManager.getSelectedSky()->getID();
	}
	else
	{
		return "";
	}
}

float FabiEngine3D::skyEntity_getLightness(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->getLightness();
}

float FabiEngine3D::skyEntity_getRotationSpeed(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->getRotationSpeed();
}

vec3 FabiEngine3D::skyEntity_getColor(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->getColor();
}

bool FabiEngine3D::skyEntity_isExisting(const string& ID)
{
	return _core->_skyEntityManager.isExisting(ID);
}

bool FabiEngine3D::skyEntity_isVisible(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->isVisible();
}

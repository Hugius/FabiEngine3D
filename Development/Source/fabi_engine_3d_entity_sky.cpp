#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::skyEntity_add(const string& ID, const vector<string> texturePaths)
{
	_core->_skyEntityManager.addSkyEntity(ID, _core->_texLoader, texturePaths);
}

void FabiEngine3D::skyEntity_addNightCubemap(const string& ID, const string& textureDirectoryPath)
{
	//_core->_skyEntityManager.getEntity(ID)->setNightCubeMap(_core->_texLoader.getCubeMap(textureDirectoryPath));
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
	_core->_skyEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::skyEntity_show(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::skyEntity_select(const string& ID)
{
	_core->_skyEntityManager.selectSky(ID);
}

void FabiEngine3D::skyEntity_setBrightness(const string& ID, float brightness)
{
	_core->_skyEntityManager.getEntity(ID)->setBrightness(brightness);
}

void FabiEngine3D::skyEntity_setRotationSpeed(const string& ID, float speed)
{
	_core->_skyEntityManager.getEntity(ID)->setRotationSpeed(speed);
}

void FabiEngine3D::skyEntity_setColor(const string& ID, vec3 color)
{
	_core->_skyEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::skyEntity_setDayTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setDayTime();
	_core->_skyEntityManager.getEntity(ID)->setMixValue(0.0f);
}

void FabiEngine3D::skyEntity_setNightTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setNightTime();
	_core->_skyEntityManager.getEntity(ID)->setMixValue(1.0f);
}

void FabiEngine3D::skyEntity_fadeDayTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setDayTime();
}

void FabiEngine3D::skyEntity_fadeNightTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setNightTime();
}

bool FabiEngine3D::skyEntity_isDayTime(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->isDayTime();
}

bool FabiEngine3D::skyEntity_isNightTime(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->isNightTime();
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

bool FabiEngine3D::skyEntity_isExisting(const string& ID)
{
	return _core->_skyEntityManager.isExisting(ID);
}
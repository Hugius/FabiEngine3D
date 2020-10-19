#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::skyEntity_add(const string& ID)
{
	_core->_skyEntityManager.addSkyEntity(ID);
}

void FabiEngine3D::skyEntity_setDiffuseMaps(const string& ID, const array<string, 6>& texturePaths)
{
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapRight(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[0] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapLeft(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[1] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapTop(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[2] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapBottom(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[3] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapFront(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[4] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapBack(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[5] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_texLoader.getCubeMap(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
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
	_core->_skyEntityManager.getEntity(ID)->setOriginalLightness(lightness);
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

vector<string> FabiEngine3D::skyEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto entity : _core->_skyEntityManager.getEntities()) // Loop over SKY entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const array<string, 6>& FabiEngine3D::skyEntity_getDiffuseMapPaths(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
}

float FabiEngine3D::skyEntity_getLightness(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->getLightness();
}

float FabiEngine3D::skyEntity_getOriginalLightness(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->getOriginalLightness();
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
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::skyEntity_add(const string& ID)
{
	_core->_skyEntityManager.addSkyEntity(ID);
}

void FabiEngine3D::skyEntity_deleteAll()
{
	// For every sky entity
	for (auto& [keyID, entity] : _core->_skyEntityManager.getEntities())
	{
		skyEntity_delete(entity->getID());
	}
}

void FabiEngine3D::skyEntity_setDiffuseMaps(const string& ID, const array<string, 6>& texturePaths)
{
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapRight(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[0] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapLeft(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[1] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapTop(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[2] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapBottom(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[3] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapBack(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[4] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapFront(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[5] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.getTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_delete(const string& ID)
{
	// Unselect sky if selected
	if (ID == skyEntity_getSelectedID())
	{
		_core->_skyEntityManager.selectMainSky("");
	}

	_core->_skyEntityManager.deleteEntity(ID);
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
	_core->_skyEntityManager.selectMainSky(ID);
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

void FabiEngine3D::skyEntity_setColor(const string& ID, Vec3 color)
{
	_core->_skyEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::skyEntity_setMixValue(float mixValue)
{
	_core->_renderBus.setSkyMixValue(mixValue);
}

void FabiEngine3D::skyEntity_mixWithSelected(const string& ID)
{
	_core->_skyEntityManager.selectMixSky(ID);
}

string FabiEngine3D::skyEntity_getSelectedID()
{
	if (_core->_skyEntityManager.getSelectedMainSky() != nullptr)
	{
		return _core->_skyEntityManager.getSelectedMainSky()->getID();
	}
	else
	{
		return "";
	}
}

vector<string> FabiEngine3D::skyEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_skyEntityManager.getEntities())
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

float FabiEngine3D::skyEntity_getMixValue()
{
	return _core->_renderBus.getSkyMixValue();
}

Vec3 FabiEngine3D::skyEntity_getColor(const string& ID)
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
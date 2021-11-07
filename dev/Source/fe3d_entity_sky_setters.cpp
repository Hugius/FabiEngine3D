#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::skyEntity_create(const string& ID)
{
	_core->_skyEntityManager.createEntity(ID);
}

void FabiEngine3D::skyEntity_deleteAll()
{
	for(const auto& [keyID, entity] : _core->_skyEntityManager.getEntities())
	{
		skyEntity_delete(entity->getID());
	}
}

void FabiEngine3D::skyEntity_setDiffuseMaps(const string& ID, const array<string, 6>& texturePaths)
{
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapRight(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[0] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapLeft(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[1] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapTop(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[2] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapBottom(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[3] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapBack(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[4] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setDiffuseMapFront(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getDiffuseMapPaths();
	texturePaths[5] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setDiffuseMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_delete(const string& ID)
{
	// Unselect sky if selected
	if(ID == skyEntity_getSelectedID())
	{
		_core->_skyEntityManager.selectMainSky("");
	}

	_core->_skyEntityManager.deleteEntity(ID);
}

void FabiEngine3D::skyEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_skyEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::skyEntity_selectMainSky(const string& ID)
{
	_core->_skyEntityManager.selectMainSky(ID);
}

void FabiEngine3D::skyEntity_setLightness(const string& ID, float lightness)
{
	_core->_skyEntityManager.getEntity(ID)->setLightness(lightness);
	_core->_skyEntityManager.getEntity(ID)->setOriginalLightness(lightness);
}

void FabiEngine3D::skyEntity_setMixValue(float mixValue)
{
	_core->_renderBus.setSkyMixValue(mixValue);
}

void FabiEngine3D::skyEntity_setRotationSpeed(const string& ID, float speed)
{
	_core->_skyEntityManager.getEntity(ID)->setRotationSpeed(speed);
}

void FabiEngine3D::skyEntity_setColor(const string& ID, Vec3 color)
{
	_core->_skyEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::skyEntity_setWireFramed(const string& ID, bool enabled)
{
	_core->_skyEntityManager.getEntity(ID)->setWireFramed(enabled);
}

void FabiEngine3D::skyEntity_selectMixSky(const string& ID)
{
	_core->_skyEntityManager.selectMixSky(ID);
}
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

void FabiEngine3D::skyEntity_setCubeMaps(const string& ID, const array<string, 6>& texturePaths)
{
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setCubeMapRight(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[0] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setCubeMapLeft(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[1] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setCubeMapTop(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[2] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setCubeMapBottom(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[3] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setCubeMapBack(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[4] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::skyEntity_setCubeMapFront(const string& ID, const string& texturePath)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[5] = texturePath;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.loadTexture3D(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
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
	_core->_skyEntityManager.getEntity(ID)->setInitialLightness(lightness);
}

void FabiEngine3D::skyEntity_setMixValue(float mixValue)
{
	_core->_renderBus.setSkyMixValue(mixValue);
}

void FabiEngine3D::skyEntity_setRotation(const string& ID, float rotation)
{
	_core->_skyEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::skyEntity_setColor(const string& ID, Vec3 color)
{
	_core->_skyEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::skyEntity_setWireframed(const string& ID, bool enabled)
{
	_core->_skyEntityManager.getEntity(ID)->setWireframed(enabled);
}

void FabiEngine3D::skyEntity_selectMixSky(const string& ID)
{
	_core->_skyEntityManager.selectMixSky(ID);
}
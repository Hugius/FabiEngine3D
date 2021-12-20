#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::sky_create(const string& ID)
{
	_core->_skyEntityManager.createEntity(ID);
}

void FabiEngine3D::sky_deleteAll()
{
	for(const auto& [keyID, entity] : _core->_skyEntityManager.getEntities())
	{
		sky_delete(entity->getID());
	}
}

void FabiEngine3D::sky_setCubeMaps(const string& ID, const array<string, 6>& value)
{
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(value));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(value);
}

void FabiEngine3D::sky_setRightCubeMap(const string& ID, const string& value)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[0] = value;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::sky_setLeftCubeMap(const string& ID, const string& value)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[1] = value;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::sky_setTopCubeMap(const string& ID, const string& value)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[2] = value;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::sky_setBottomCubeMap(const string& ID, const string& value)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[3] = value;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::sky_setBackCubeMap(const string& ID, const string& value)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[4] = value;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::sky_setFrontCubeMap(const string& ID, const string& value)
{
	auto texturePaths = _core->_skyEntityManager.getEntity(ID)->getCubeMapPaths();
	texturePaths[5] = value;
	_core->_skyEntityManager.getEntity(ID)->setCubeMap(_core->_textureLoader.load3dTexture(texturePaths));
	_core->_skyEntityManager.getEntity(ID)->setCubeMapPaths(texturePaths);
}

void FabiEngine3D::sky_delete(const string& ID)
{
	// Unselect sky if selected
	if(ID == sky_getSelectedID())
	{
		_core->_skyEntityManager.selectMainSky("");
	}

	_core->_skyEntityManager.deleteEntity(ID);
}

void FabiEngine3D::sky_setVisible(const string& ID, bool value)
{
	_core->_skyEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::sky_selectMainSky(const string& ID)
{
	_core->_skyEntityManager.selectMainSky(ID);
}

void FabiEngine3D::sky_setLightness(const string& ID, float value)
{
	_core->_skyEntityManager.getEntity(ID)->setLightness(value);
	_core->_skyEntityManager.getEntity(ID)->setInitialLightness(value);
}

void FabiEngine3D::sky_setMixValue(float value)
{
	_core->_renderBus.setSkyMixValue(value);
}

void FabiEngine3D::sky_setRotation(const string& ID, float value)
{
	_core->_skyEntityManager.getEntity(ID)->setRotation(value);
}

void FabiEngine3D::sky_setColor(const string& ID, fvec3 value)
{
	_core->_skyEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::sky_setWireframed(const string& ID, bool value)
{
	_core->_skyEntityManager.getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::sky_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_skyEntityManager.getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::sky_selectMixSky(const string& ID)
{
	_core->_skyEntityManager.selectMixSky(ID);
}
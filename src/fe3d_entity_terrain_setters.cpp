#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::terrain_create(const string& ID, const string& value)
{
	_core->_terrainEntityManager.createEntity(ID, value);
}

void FabiEngine3D::terrain_deleteAll()
{
	// For every terrain entity
	for(const auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		terrain_delete(entity->getID());
	}

	// Unselect terrain
	_core->_terrainEntityManager.selectTerrain("");
}

void FabiEngine3D::terrain_delete(const string& ID)
{
	// Unselect terrain if selected
	if(ID == terrain_getSelectedID())
	{
		_core->_terrainEntityManager.selectTerrain("");
	}

	_core->_terrainEntityManager.deleteEntity(ID);
}

void FabiEngine3D::terrain_setVisible(const string& ID, bool value)
{
	_core->_terrainEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::terrain_select(const string& ID)
{
	_core->_terrainEntityManager.selectTerrain(ID);
}

void FabiEngine3D::terrain_setMaxHeight(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setMaxHeight(value);
	_core->_terrainEntityManager.loadMesh(ID);
}

void FabiEngine3D::terrain_setTextureRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setTextureRepeat(value);
}

void FabiEngine3D::terrain_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMap(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPath(value);
	}
}

void FabiEngine3D::terrain_setNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMap(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMap(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPath(value);
	}
}

void FabiEngine3D::terrain_setBlendMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setBlendMap(0);
		_core->_terrainEntityManager.getEntity(ID)->setBlendMapPath("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setBlendMap(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setBlendMapPath(value);
	}
}

void FabiEngine3D::terrain_setDiffuseMapR(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapR(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathR("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapR(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathR(value);
	}
}

void FabiEngine3D::terrain_setDiffuseMapG(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapG(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathG("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapG(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathG(value);
	}
}

void FabiEngine3D::terrain_setDiffuseMapB(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapB(0);
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathB("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapB(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathB(value);
	}
}

void FabiEngine3D::terrain_setNormalMapR(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapR(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathR("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapR(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathR(value);
	}
}

void FabiEngine3D::terrain_setNormalMapG(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapG(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathG("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapG(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathG(value);
	}
}

void FabiEngine3D::terrain_setNormalMapB(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapB(0);
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathB("");
	}
	else
	{
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapB(_core->_textureLoader.loadTexture2D(value, true, true));
		_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathB(value);
	}
}

void FabiEngine3D::terrain_setRedRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setRedRepeat(value);
}

void FabiEngine3D::terrain_setGreenRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setGreenRepeat(value);
}

void FabiEngine3D::terrain_setBlueRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlueRepeat(value);
}

void FabiEngine3D::terrain_setSpecularShininess(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularShininess(value);
}

void FabiEngine3D::terrain_setSpecularIntensity(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularIntensity(value);
}

void FabiEngine3D::terrain_setLightness(const string& ID, float value)
{
	_core->_terrainEntityManager.getEntity(ID)->setLightness(value);
}

void FabiEngine3D::terrain_setSpecular(const string& ID, bool value)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecular(value);
}

void FabiEngine3D::terrain_setWireframed(const string& ID, bool value)
{
	_core->_terrainEntityManager.getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::terrain_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_terrainEntityManager.getEntity(ID)->setWireframeColor(value);
}
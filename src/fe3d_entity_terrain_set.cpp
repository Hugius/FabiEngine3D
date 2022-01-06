#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::terrain_create(const string& ID, const string& heightMapPath)
{
	_core->_terrainEntityManager->createEntity(ID, heightMapPath);
}

void FabiEngine3D::terrain_deleteAll()
{
	for(const auto& [key, entity] : _core->_terrainEntityManager->getEntities())
	{
		terrain_delete(entity->getID());
	}

	_core->_terrainEntityManager->selectTerrain("");
}

void FabiEngine3D::terrain_delete(const string& ID)
{
	_core->_terrainEntityManager->deleteEntity(ID);
}

void FabiEngine3D::terrain_setVisible(const string& ID, bool value)
{
	_core->_terrainEntityManager->getEntity(ID)->setVisible(value);
}

void FabiEngine3D::terrain_select(const string& ID)
{
	_core->_terrainEntityManager->selectTerrain(ID);
}

void FabiEngine3D::terrain_setMaxHeight(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setMaxHeight(value);
	_core->_terrainEntityManager->loadMesh(ID);
}

void FabiEngine3D::terrain_setTextureRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setTextureRepeat(value);
}

void FabiEngine3D::terrain_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setDiffuseMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setDiffuseMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void FabiEngine3D::terrain_setNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setNormalMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setNormalMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setNormalMapPath(value);
	}
}

void FabiEngine3D::terrain_setBlendMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setBlendMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setBlendMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setBlendMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setBlendMapPath(value);
	}
}

void FabiEngine3D::terrain_setRedDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setRedDiffuseMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setRedDiffuseMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setRedDiffuseMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setRedDiffuseMapPath(value);
	}
}

void FabiEngine3D::terrain_setGreenDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setGreenDiffuseMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setGreenDiffuseMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setGreenDiffuseMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setGreenDiffuseMapPath(value);
	}
}

void FabiEngine3D::terrain_setBlueDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setBlueDiffuseMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setBlueDiffuseMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setBlueDiffuseMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setBlueDiffuseMapPath(value);
	}
}

void FabiEngine3D::terrain_setRedNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setRedNormalMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setRedNormalMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setRedNormalMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setRedNormalMapPath(value);
	}
}

void FabiEngine3D::terrain_setGreenNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setGreenNormalMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setGreenNormalMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setGreenNormalMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setGreenNormalMapPath(value);
	}
}

void FabiEngine3D::terrain_setBlueNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_terrainEntityManager->getEntity(ID)->setBlueNormalMap(0);
		_core->_terrainEntityManager->getEntity(ID)->setBlueNormalMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true);
		texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());
		_core->_terrainEntityManager->getEntity(ID)->setBlueNormalMap(texture);
		_core->_terrainEntityManager->getEntity(ID)->setBlueNormalMapPath(value);
	}
}

void FabiEngine3D::terrain_setRedTextureRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setRedTextureRepeat(value);
}

void FabiEngine3D::terrain_setGreenTextureRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setGreenTextureRepeat(value);
}

void FabiEngine3D::terrain_setBlueTextureRepeat(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setBlueTextureRepeat(value);
}

void FabiEngine3D::terrain_setSpecularShininess(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setSpecularShininess(value);
}

void FabiEngine3D::terrain_setSpecularIntensity(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setSpecularIntensity(value);
}

void FabiEngine3D::terrain_setLightness(const string& ID, float value)
{
	_core->_terrainEntityManager->getEntity(ID)->setLightness(value);
}

void FabiEngine3D::terrain_setSpecular(const string& ID, bool value)
{
	_core->_terrainEntityManager->getEntity(ID)->setSpecular(value);
}

void FabiEngine3D::terrain_setWireframed(const string& ID, bool value)
{
	_core->_terrainEntityManager->getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::terrain_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_terrainEntityManager->getEntity(ID)->setWireframeColor(value);
}
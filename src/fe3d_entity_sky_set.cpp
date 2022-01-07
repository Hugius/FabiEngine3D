#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::sky_create(const string& ID)
{
	_core->_skyEntityManager->createEntity(ID);
}

void FabiEngine3D::sky_deleteAll()
{
	for(const auto& [key, entity] : _core->_skyEntityManager->getEntities())
	{
		sky_delete(entity->getID());
	}
}

void FabiEngine3D::sky_setCubeMaps(const string& ID, const array<string, 6>& value)
{
	array<shared_ptr<Image>, 6> images;
	for(unsigned int i = 0; i < 6; i++)
	{
		if(value[i].empty())
		{
			images[i] = nullptr;
		}
		else
		{
			images[i] = _core->_imageLoader->loadImage(value[i]);
		}
	}

	for(const auto& image : images)
	{
		if(image != nullptr)
		{
			image->flipY();
		}
	}

	//auto texture = _core->_textureBufferCache->getTextureBuffer(value);

	//if(texture == nullptr)
	//{
	//	texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value));
	//	texture->loadMipMapping();
	//	texture->loadAnisotropicFiltering(_core->_renderBus->getAnisotropicFilteringQuality());

	//	_core->_textureBufferCache->storeTextureBuffer(value, texture);
	//}

	_core->_skyEntityManager->getEntity(ID)->setCubeMap(make_shared<TextureBuffer>(images));
	_core->_skyEntityManager->getEntity(ID)->setCubeMapPaths(value);

	for(const auto& image : images)
	{
		if(image != nullptr)
		{
			image->flipY();
		}
	}
}

void FabiEngine3D::sky_setRightCubeMap(const string& ID, const string& value)
{
	auto paths = _core->_skyEntityManager->getEntity(ID)->getCubeMapPaths();
	paths[0] = value;

	sky_setCubeMaps(ID, paths);
}

void FabiEngine3D::sky_setLeftCubeMap(const string& ID, const string& value)
{
	auto paths = _core->_skyEntityManager->getEntity(ID)->getCubeMapPaths();
	paths[1] = value;

	sky_setCubeMaps(ID, paths);
}

void FabiEngine3D::sky_setTopCubeMap(const string& ID, const string& value)
{
	auto paths = _core->_skyEntityManager->getEntity(ID)->getCubeMapPaths();
	paths[2] = value;

	sky_setCubeMaps(ID, paths);
}

void FabiEngine3D::sky_setBottomCubeMap(const string& ID, const string& value)
{
	auto paths = _core->_skyEntityManager->getEntity(ID)->getCubeMapPaths();
	paths[3] = value;

	sky_setCubeMaps(ID, paths);
}

void FabiEngine3D::sky_setBackCubeMap(const string& ID, const string& value)
{
	auto paths = _core->_skyEntityManager->getEntity(ID)->getCubeMapPaths();
	paths[4] = value;

	sky_setCubeMaps(ID, paths);
}

void FabiEngine3D::sky_setFrontCubeMap(const string& ID, const string& value)
{
	auto paths = _core->_skyEntityManager->getEntity(ID)->getCubeMapPaths();
	paths[5] = value;

	sky_setCubeMaps(ID, paths);
}

void FabiEngine3D::sky_delete(const string& ID)
{
	_core->_skyEntityManager->deleteEntity(ID);
}

void FabiEngine3D::sky_setVisible(const string& ID, bool value)
{
	_core->_skyEntityManager->getEntity(ID)->setVisible(value);
}

void FabiEngine3D::sky_selectMainSky(const string& ID)
{
	_core->_skyEntityManager->selectMainSky(ID);
}

void FabiEngine3D::sky_setLightness(const string& ID, float value)
{
	_core->_skyEntityManager->getEntity(ID)->setLightness(value);
	_core->_skyEntityManager->getEntity(ID)->setInitialLightness(value);
}

void FabiEngine3D::sky_setMixValue(float value)
{
	_core->_renderBus->setSkyMixValue(value);
}

void FabiEngine3D::sky_setRotation(const string& ID, float value)
{
	_core->_skyEntityManager->getEntity(ID)->setRotation(value);
}

void FabiEngine3D::sky_setColor(const string& ID, fvec3 value)
{
	_core->_skyEntityManager->getEntity(ID)->setColor(value);
}

void FabiEngine3D::sky_setWireframed(const string& ID, bool value)
{
	_core->_skyEntityManager->getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::sky_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_skyEntityManager->getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::sky_selectMixSky(const string& ID)
{
	_core->_skyEntityManager->selectMixSky(ID);
}
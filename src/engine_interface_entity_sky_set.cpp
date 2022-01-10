#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sky_create(const string& ID)
{
	_core->getSkyEntityManager()->createEntity(ID);
}

void EngineInterface::sky_deleteAll()
{
	for(const auto& [key, entity] : _core->getSkyEntityManager()->getEntities())
	{
		sky_delete(entity->getID());
	}
}

void EngineInterface::sky_setCubeMaps(const string& ID, const array<string, 6>& value)
{
	auto texture = _core->getTextureBufferCache()->get3dBuffer(value);

	if(texture == nullptr)
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
				images[i] = _core->getImageLoader()->loadImage(value[i]);
			}
		}

		for(const auto& image : images)
		{
			if(image != nullptr)
			{
				image->flipY();
			}
		}

		texture = make_shared<TextureBuffer>(images);

		for(const auto& image : images)
		{
			if(image != nullptr)
			{
				image->flipY();
			}
		}

		_core->getTextureBufferCache()->store3dBuffer(value, texture);
	}

	_core->getSkyEntityManager()->getEntity(ID)->setCubeMap(texture);
	_core->getSkyEntityManager()->getEntity(ID)->setCubeMapPaths(value);
}

void EngineInterface::sky_setRightCubeMap(const string& ID, const string& value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
	paths[0] = value;

	sky_setCubeMaps(ID, paths);
}

void EngineInterface::sky_setLeftCubeMap(const string& ID, const string& value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
	paths[1] = value;

	sky_setCubeMaps(ID, paths);
}

void EngineInterface::sky_setTopCubeMap(const string& ID, const string& value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
	paths[2] = value;

	sky_setCubeMaps(ID, paths);
}

void EngineInterface::sky_setBottomCubeMap(const string& ID, const string& value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
	paths[3] = value;

	sky_setCubeMaps(ID, paths);
}

void EngineInterface::sky_setBackCubeMap(const string& ID, const string& value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
	paths[4] = value;

	sky_setCubeMaps(ID, paths);
}

void EngineInterface::sky_setFrontCubeMap(const string& ID, const string& value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
	paths[5] = value;

	sky_setCubeMaps(ID, paths);
}

void EngineInterface::sky_delete(const string& ID)
{
	_core->getSkyEntityManager()->deleteEntity(ID);
}

void EngineInterface::sky_setVisible(const string& ID, bool value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::sky_selectMainSky(const string& ID)
{
	_core->getSkyEntityManager()->selectMainSky(ID);
}

void EngineInterface::sky_setLightness(const string& ID, float value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setLightness(value);
	_core->getSkyEntityManager()->getEntity(ID)->setInitialLightness(value);
}

void EngineInterface::sky_setMixValue(float value)
{
	_core->getRenderBus()->setSkyMixValue(value);
}

void EngineInterface::sky_setRotation(const string& ID, float value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::sky_setColor(const string& ID, fvec3 value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::sky_setWireframed(const string& ID, bool value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::sky_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::sky_selectMixSky(const string& ID)
{
	_core->getSkyEntityManager()->selectMixSky(ID);
}
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

void EngineInterface::sky_select(const string& ID)
{
	_core->getSkyEntityManager()->selectEntity(ID);
}

void EngineInterface::sky_setLightness(const string& ID, float value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setLightness(value);
}

void EngineInterface::sky_setRotation(const string& ID, float value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::sky_setColor(const string& ID, const fvec3& value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::sky_setWireframed(const string& ID, bool value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::sky_setWireframeColor(const string& ID, const fvec3& value)
{
	_core->getSkyEntityManager()->getEntity(ID)->setWireframeColor(value);
}

const string EngineInterface::sky_getSelectedID() const
{
	if(_core->getSkyEntityManager()->getSelectedEntity() == nullptr)
	{
		return "";
	}

	return _core->getSkyEntityManager()->getSelectedEntity()->getID();
}

const fvec3& EngineInterface::sky_getWireframeColor(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::sky_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getSkyEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const array<string, 6>& EngineInterface::sky_getCubeMapPaths(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths();
}

const string& EngineInterface::sky_getRightCubeMapPath(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[0];
}

const string& EngineInterface::sky_getLeftCubeMapPath(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[1];
}

const string& EngineInterface::sky_getTopCubeMapPath(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[2];
}

const string& EngineInterface::sky_getBottomCubeMapPath(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[3];
}

const string& EngineInterface::sky_getBackCubeMapPath(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[4];
}

const string& EngineInterface::sky_getFrontCubeMapPath(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[5];
}

const float EngineInterface::sky_getLightness(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::sky_getRotation(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getRotation();
}

const fvec3& EngineInterface::sky_getColor(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::sky_isExisting(const string& ID) const
{
	return _core->getSkyEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::sky_isVisible(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::sky_isWireframed(const string& ID) const
{
	return _core->getSkyEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::sky_hasRightCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[0].empty();
}

const bool EngineInterface::sky_hasLeftCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[1].empty();
}

const bool EngineInterface::sky_hasTopCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[2].empty();
}

const bool EngineInterface::sky_hasBottomCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[3].empty();
}

const bool EngineInterface::sky_hasBackCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[4].empty();
}

const bool EngineInterface::sky_hasFrontCubeMap(const string& ID) const
{
	return !_core->getSkyEntityManager()->getEntity(ID)->getCubeMapPaths()[5].empty();
}
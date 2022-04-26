#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sky_create(const string & id)
{
	_core->getSkyEntityManager()->createEntity(id);
}

void EngineInterface::sky_setCubeMaps(const string & id, const array<string, 6> & value)
{
	auto texture = _core->getTextureBufferCache()->get3dBuffer(value);

	if(texture == nullptr)
	{
		array<shared_ptr<Image>, 6> images;
		for(int index = 0; index < 6; index++)
		{
			if(value[index].empty())
			{
				images[index] = nullptr;
			}
			else
			{
				images[index] = _core->getImageLoader()->loadImage(value[index]);
			}
		}

		for(const auto & image : images)
		{
			if(image != nullptr)
			{
				image->flipY();
			}
		}

		texture = make_shared<TextureBuffer>(images);

		for(const auto & image : images)
		{
			if(image != nullptr)
			{
				image->flipY();
			}
		}

		_core->getTextureBufferCache()->store3dBuffer(value, texture);
	}

	_core->getSkyEntityManager()->getEntity(id)->setCubeMap(texture);
	_core->getSkyEntityManager()->getEntity(id)->setCubeMapPaths(value);
}

void EngineInterface::sky_setRightCubeMap(const string & id, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
	paths[0] = value;

	sky_setCubeMaps(id, paths);
}

void EngineInterface::sky_setLeftCubeMap(const string & id, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
	paths[1] = value;

	sky_setCubeMaps(id, paths);
}

void EngineInterface::sky_setTopCubeMap(const string & id, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
	paths[2] = value;

	sky_setCubeMaps(id, paths);
}

void EngineInterface::sky_setBottomCubeMap(const string & id, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
	paths[3] = value;

	sky_setCubeMaps(id, paths);
}

void EngineInterface::sky_setBackCubeMap(const string & id, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
	paths[4] = value;

	sky_setCubeMaps(id, paths);
}

void EngineInterface::sky_setFrontCubeMap(const string & id, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
	paths[5] = value;

	sky_setCubeMaps(id, paths);
}

void EngineInterface::sky_delete(const string & id)
{
	_core->getSkyEntityManager()->deleteEntity(id);
}

void EngineInterface::sky_setVisible(const string & id, bool value)
{
	_core->getSkyEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::sky_select(const string & id)
{
	_core->getSkyEntityManager()->selectEntity(id);
}

void EngineInterface::sky_setLightness(const string & id, float value)
{
	_core->getSkyEntityManager()->getEntity(id)->setLightness(value);
}

void EngineInterface::sky_setRotation(const string & id, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(id)->setRotation(value);
}

void EngineInterface::sky_rotate(const string & id, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(id)->rotate(value);
}

void EngineInterface::sky_rotateTo(const string & id, const fvec3 & target, float speed)
{
	_core->getSkyEntityManager()->getEntity(id)->rotateTo(target, speed);
}

void EngineInterface::sky_setColor(const string & id, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::sky_setWireframed(const string & id, bool value)
{
	_core->getSkyEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::sky_setWireframeColor(const string & id, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::sky_setRotationOrder(const string & id, DirectionOrderType value)
{
	_core->getSkyEntityManager()->getEntity(id)->setRotationOrder(value);
}

const string EngineInterface::sky_getSelectedId() const
{
	if(_core->getSkyEntityManager()->getSelectedEntity() == nullptr)
	{
		return "";
	}

	return _core->getSkyEntityManager()->getSelectedEntity()->getId();
}

const fvec3 & EngineInterface::sky_getWireframeColor(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getWireframeColor();
}

const vector<string> EngineInterface::sky_getIds() const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getSkyEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const array<string, 6> & EngineInterface::sky_getCubeMapPaths(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths();
}

const string & EngineInterface::sky_getRightCubeMapPath(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[0];
}

const string & EngineInterface::sky_getLeftCubeMapPath(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[1];
}

const string & EngineInterface::sky_getTopCubeMapPath(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[2];
}

const string & EngineInterface::sky_getBottomCubeMapPath(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[3];
}

const string & EngineInterface::sky_getBackCubeMapPath(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[4];
}

const string & EngineInterface::sky_getFrontCubeMapPath(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[5];
}

const float EngineInterface::sky_getLightness(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getLightness();
}

const fvec3 & EngineInterface::sky_getRotation(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getRotation();
}

const fvec3 & EngineInterface::sky_getColor(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getColor();
}

const bool EngineInterface::sky_isExisting(const string & id) const
{
	return _core->getSkyEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::sky_isVisible(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::sky_isWireframed(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->isWireframed();
}

const bool EngineInterface::sky_hasRightCubeMap(const string & id) const
{
	return ((_core->getSkyEntityManager()->getEntity(id)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[0].empty());
}

const bool EngineInterface::sky_hasLeftCubeMap(const string & id) const
{
	return ((_core->getSkyEntityManager()->getEntity(id)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[1].empty());
}

const bool EngineInterface::sky_hasTopCubeMap(const string & id) const
{
	return ((_core->getSkyEntityManager()->getEntity(id)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[2].empty());
}

const bool EngineInterface::sky_hasBottomCubeMap(const string & id) const
{
	return ((_core->getSkyEntityManager()->getEntity(id)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[3].empty());
}

const bool EngineInterface::sky_hasBackCubeMap(const string & id) const
{
	return ((_core->getSkyEntityManager()->getEntity(id)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[4].empty());
}

const bool EngineInterface::sky_hasFrontCubeMap(const string & id) const
{
	return ((_core->getSkyEntityManager()->getEntity(id)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(id)->getCubeMapPaths()[5].empty());
}

const DirectionOrderType EngineInterface::sky_getRotationOrder(const string & id) const
{
	return _core->getSkyEntityManager()->getEntity(id)->getRotationOrder();
}
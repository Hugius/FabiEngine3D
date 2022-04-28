#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sky_create(const string & skyId)
{
	_core->getSkyEntityManager()->createEntity(skyId);
}

void EngineInterface::sky_setCubeMaps(const string & skyId, const array<string, 6> & value)
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

	_core->getSkyEntityManager()->getEntity(skyId)->setCubeMap(texture);
	_core->getSkyEntityManager()->getEntity(skyId)->setCubeMapPaths(value);
}

void EngineInterface::sky_setRightCubeMap(const string & skyId, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
	paths[0] = value;

	sky_setCubeMaps(skyId, paths);
}

void EngineInterface::sky_setLeftCubeMap(const string & skyId, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
	paths[1] = value;

	sky_setCubeMaps(skyId, paths);
}

void EngineInterface::sky_setTopCubeMap(const string & skyId, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
	paths[2] = value;

	sky_setCubeMaps(skyId, paths);
}

void EngineInterface::sky_setBottomCubeMap(const string & skyId, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
	paths[3] = value;

	sky_setCubeMaps(skyId, paths);
}

void EngineInterface::sky_setBackCubeMap(const string & skyId, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
	paths[4] = value;

	sky_setCubeMaps(skyId, paths);
}

void EngineInterface::sky_setFrontCubeMap(const string & skyId, const string & value)
{
	auto paths = _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
	paths[5] = value;

	sky_setCubeMaps(skyId, paths);
}

void EngineInterface::sky_delete(const string & skyId)
{
	_core->getSkyEntityManager()->deleteEntity(skyId);
}

void EngineInterface::sky_setVisible(const string & skyId, bool value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setVisible(value);
}

void EngineInterface::sky_select(const string & skyId)
{
	_core->getSkyEntityManager()->selectEntity(skyId);
}

void EngineInterface::sky_setLightness(const string & skyId, float value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setLightness(value);
}

void EngineInterface::sky_setRotation(const string & skyId, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setRotation(value);
}

void EngineInterface::sky_rotate(const string & skyId, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->rotate(value);
}

void EngineInterface::sky_rotateTo(const string & skyId, const fvec3 & target, float speed)
{
	_core->getSkyEntityManager()->getEntity(skyId)->rotateTo(target, speed);
}

void EngineInterface::sky_setColor(const string & skyId, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setColor(value);
}

void EngineInterface::sky_setWireframed(const string & skyId, bool value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setWireframed(value);
}

void EngineInterface::sky_setWireframeColor(const string & skyId, const fvec3 & value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setWireframeColor(value);
}

void EngineInterface::sky_setRotationOrder(const string & skyId, DirectionOrderType value)
{
	_core->getSkyEntityManager()->getEntity(skyId)->setRotationOrder(value);
}

const string EngineInterface::sky_getSelectedId() const
{
	if(_core->getSkyEntityManager()->getSelectedEntity() == nullptr)
	{
		return "";
	}

	return _core->getSkyEntityManager()->getSelectedEntity()->getId();
}

const fvec3 & EngineInterface::sky_getWireframeColor(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getWireframeColor();
}

const vector<string> EngineInterface::sky_getIds() const
{
	vector<string> result;

	for(const auto & [skyId, entity] : _core->getSkyEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const array<string, 6> & EngineInterface::sky_getCubeMapPaths(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths();
}

const string & EngineInterface::sky_getRightCubeMapPath(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[0];
}

const string & EngineInterface::sky_getLeftCubeMapPath(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[1];
}

const string & EngineInterface::sky_getTopCubeMapPath(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[2];
}

const string & EngineInterface::sky_getBottomCubeMapPath(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[3];
}

const string & EngineInterface::sky_getBackCubeMapPath(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[4];
}

const string & EngineInterface::sky_getFrontCubeMapPath(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[5];
}

const float EngineInterface::sky_getLightness(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getLightness();
}

const fvec3 & EngineInterface::sky_getRotation(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getRotation();
}

const fvec3 & EngineInterface::sky_getColor(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getColor();
}

const bool EngineInterface::sky_isExisting(const string & skyId) const
{
	return _core->getSkyEntityManager()->isEntityExisting(skyId);
}

const bool EngineInterface::sky_isVisible(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->isVisible();
}

const bool EngineInterface::sky_isWireframed(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->isWireframed();
}

const bool EngineInterface::sky_hasRightCubeMap(const string & skyId) const
{
	return ((_core->getSkyEntityManager()->getEntity(skyId)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[0].empty());
}

const bool EngineInterface::sky_hasLeftCubeMap(const string & skyId) const
{
	return ((_core->getSkyEntityManager()->getEntity(skyId)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[1].empty());
}

const bool EngineInterface::sky_hasTopCubeMap(const string & skyId) const
{
	return ((_core->getSkyEntityManager()->getEntity(skyId)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[2].empty());
}

const bool EngineInterface::sky_hasBottomCubeMap(const string & skyId) const
{
	return ((_core->getSkyEntityManager()->getEntity(skyId)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[3].empty());
}

const bool EngineInterface::sky_hasBackCubeMap(const string & skyId) const
{
	return ((_core->getSkyEntityManager()->getEntity(skyId)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[4].empty());
}

const bool EngineInterface::sky_hasFrontCubeMap(const string & skyId) const
{
	return ((_core->getSkyEntityManager()->getEntity(skyId)->getCubeTextureBuffer() != nullptr) && !_core->getSkyEntityManager()->getEntity(skyId)->getCubeMapPaths()[5].empty());
}

const DirectionOrderType EngineInterface::sky_getRotationOrder(const string & skyId) const
{
	return _core->getSkyEntityManager()->getEntity(skyId)->getRotationOrder();
}
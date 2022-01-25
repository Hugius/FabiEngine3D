#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad3d_create(const string& id, bool isCentered)
{
	_core->getQuad3dEntityManager()->createEntity(id, isCentered);
}

void EngineInterface::quad3d_deleteAll()
{
	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		quad3d_delete(entity->getId());
	}
}

void EngineInterface::quad3d_delete(const string& id)
{
	for(const auto& aabbId : aabb_getChildIds(id, AabbParentEntityType::QUAD3D))
	{
		_core->getAabbEntityManager()->deleteEntity(aabbId);
	}

	_core->getQuad3dEntityManager()->deleteEntity(id);
}

void EngineInterface::quad3d_setVisible(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::quad3d_move(const string& id, const fvec3& change)
{
	_core->getQuad3dEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::quad3d_rotate(const string& id, const fvec3& change)
{
	_core->getQuad3dEntityManager()->getEntity(id)->rotate(change);
}

void EngineInterface::quad3d_scale(const string& id, const fvec2& change)
{
	_core->getQuad3dEntityManager()->getEntity(id)->scale(change);
}

void EngineInterface::quad3d_moveTo(const string& id, const fvec3& target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::quad3d_rotateTo(const string& id, const fvec3& target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(id)->rotateTo(target, speed);
}

void EngineInterface::quad3d_scaleTo(const string& id, const fvec2& target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(id)->scaleTo(target, speed);
}

void EngineInterface::quad3d_setPosition(const string& id, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::quad3d_setRotation(const string& id, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setRotation(value);
}

void EngineInterface::quad3d_setSize(const string& id, const fvec2& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setSize(value);
}

void EngineInterface::quad3d_setColor(const string& id, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::quad3d_setWireframeColor(const string& id, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::quad3d_setUvMultiplier(const string& id, const fvec2& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setUvMultiplier(value);
}

void EngineInterface::quad3d_setUvOffset(const string& id, const fvec2& value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setUvOffset(value);
}

void EngineInterface::quad3d_setDiffuseMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getQuad3dEntityManager()->getEntity(id)->setDiffuseMap(nullptr);
		_core->getQuad3dEntityManager()->getEntity(id)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getQuad3dEntityManager()->getEntity(id)->setDiffuseMap(texture);
		_core->getQuad3dEntityManager()->getEntity(id)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad3d_setEmissionMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getQuad3dEntityManager()->getEntity(id)->setEmissionMap(nullptr);
		_core->getQuad3dEntityManager()->getEntity(id)->setEmissionMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getQuad3dEntityManager()->getEntity(id)->setEmissionMap(texture);
		_core->getQuad3dEntityManager()->getEntity(id)->setEmissionMapPath(value);
	}
}

void EngineInterface::quad3d_setWireframed(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::quad3d_setFrozen(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setFrozen(value);
}

void EngineInterface::quad3d_setFacingCameraX(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setFacingCameraX(value);
}

void EngineInterface::quad3d_setFacingCameraY(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setFacingCameraY(value);
}

void EngineInterface::quad3d_setDepthMapIncluded(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setDepthMapIncluded(value);
}

void EngineInterface::quad3d_setShadowed(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setShadowed(value);
}

void EngineInterface::quad3d_setReflected(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setReflected(value);
}

void EngineInterface::quad3d_setBright(const string& id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setBright(value);
}

void EngineInterface::quad3d_setMinHeight(const string& id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setMinHeight(value);
}

void EngineInterface::quad3d_setMaxHeight(const string& id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setMaxHeight(value);
}

void EngineInterface::quad3d_setLightness(const string& id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setLightness(value);
}

void EngineInterface::quad3d_setOpacity(const string& id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setOpacity(value);
}

void EngineInterface::quad3d_setTextureRepeat(const string& id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setTextureRepeat(value);
}

void EngineInterface::quad3d_setEmissionIntensity(const string& id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setEmissionIntensity(value);
}

const float EngineInterface::quad3d_getLightness(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getLightness();
}

const float EngineInterface::quad3d_getMinHeight(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getMinHeight();
}

const float EngineInterface::quad3d_getMaxHeight(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getMaxHeight();
}

const float EngineInterface::quad3d_getOpacity(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getOpacity();
}

const float EngineInterface::quad3d_getTextureRepeat(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getTextureRepeat();
}

const float EngineInterface::quad3d_getEmissionIntensity(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getEmissionIntensity();
}

const bool EngineInterface::quad3d_isExisting(const string& id) const
{
	return _core->getQuad3dEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::quad3d_isVisible(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isVisible();
}

const fvec3& EngineInterface::quad3d_getPosition(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getPosition();
}

const fvec3& EngineInterface::quad3d_getRotation(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getRotation();
}

const fvec2& EngineInterface::quad3d_getSize(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getSize();
}

const fvec2& EngineInterface::quad3d_getUvMultiplier(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getUvMultiplier();
}

const fvec2& EngineInterface::quad3d_getUvOffset(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getUvOffset();
}

const fvec3& EngineInterface::quad3d_getColor(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getColor();
}

const fvec3& EngineInterface::quad3d_getWireframeColor(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getWireframeColor();
}

const vector<string> EngineInterface::quad3d_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const bool EngineInterface::quad3d_isFacingCameraX(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isFacingCameraX();
}

const bool EngineInterface::quad3d_isFacingCameraY(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isFacingCameraY();
}

const bool EngineInterface::quad3d_isDepthMapIncluded(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isDepthMapIncluded();
}

const bool EngineInterface::quad3d_isShadowed(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isShadowed();
}

const bool EngineInterface::quad3d_isReflected(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isReflected();
}

const bool EngineInterface::quad3d_isBright(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isBright();
}

const string& EngineInterface::quad3d_getDiffuseMapPath(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getDiffuseMapPath();
}

const string& EngineInterface::quad3d_getEmissionMapPath(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getEmissionMapPath();
}

const bool EngineInterface::quad3d_hasDiffuseMap(const string& id) const
{
	return (_core->getQuad3dEntityManager()->getEntity(id)->getDiffuseMap() != nullptr);
}

const bool EngineInterface::quad3d_hasEmissionMap(const string& id) const
{
	return (_core->getQuad3dEntityManager()->getEntity(id)->getEmissionMap() != nullptr);
}

const bool EngineInterface::quad3d_isFrozen(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isFrozen();
}

const bool EngineInterface::quad3d_isWireframed(const string& id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isWireframed();
}
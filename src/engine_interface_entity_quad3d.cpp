#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad3d_create(const string& ID, bool isCentered)
{
	_core->getQuad3dEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::quad3d_deleteAll()
{
	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		quad3d_delete(entity->getID());
	}
}

void EngineInterface::quad3d_delete(const string& ID)
{
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::QUAD3D))
	{
		_core->getAabbEntityManager()->deleteEntity(aabbID);
	}

	_core->getQuad3dEntityManager()->deleteEntity(ID);
}

void EngineInterface::quad3d_setVisible(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::quad3d_move(const string& ID, const fvec3& change)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::quad3d_rotate(const string& ID, const fvec3& change)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->rotate(change);
}

void EngineInterface::quad3d_scale(const string& ID, const fvec2& change)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->scale(change);
}

void EngineInterface::quad3d_moveTo(const string& ID, const fvec3& target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::quad3d_rotateTo(const string& ID, const fvec3& target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::quad3d_scaleTo(const string& ID, const fvec2& target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::quad3d_setPosition(const string& ID, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::quad3d_setRotation(const string& ID, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::quad3d_setSize(const string& ID, const fvec2& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::quad3d_setColor(const string& ID, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::quad3d_setWireframeColor(const string& ID, const fvec3& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::quad3d_setUvMultiplier(const string& ID, const fvec2& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setUvMultiplier(value);
}

void EngineInterface::quad3d_setUvOffset(const string& ID, const fvec2& value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setUvOffset(value);
}

void EngineInterface::quad3d_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMap(nullptr);
		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMapPath("");
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

		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMap(texture);
		_core->getQuad3dEntityManager()->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad3d_setEmissionMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMap(nullptr);
		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMapPath("");
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

		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMap(texture);
		_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionMapPath(value);
	}
}

void EngineInterface::quad3d_setWireframed(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::quad3d_setFrozen(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setFrozen(value);
}

void EngineInterface::quad3d_setFacingCameraX(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setFacingCameraX(value);
}

void EngineInterface::quad3d_setFacingCameraY(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setFacingCameraY(value);
}

void EngineInterface::quad3d_setDepthMapIncluded(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setDepthMapIncluded(value);
}

void EngineInterface::quad3d_setShadowed(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setShadowed(value);
}

void EngineInterface::quad3d_setReflected(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setReflected(value);
}

void EngineInterface::quad3d_setBright(const string& ID, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setBright(value);
}

void EngineInterface::quad3d_setMinHeight(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setMinHeight(value);
}

void EngineInterface::quad3d_setMaxHeight(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setMaxHeight(value);
}

void EngineInterface::quad3d_setLightness(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setLightness(value);
}

void EngineInterface::quad3d_setOpacity(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setOpacity(value);
}

void EngineInterface::quad3d_setTextureRepeat(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setTextureRepeat(value);
}

void EngineInterface::quad3d_setEmissionIntensity(const string& ID, float value)
{
	_core->getQuad3dEntityManager()->getEntity(ID)->setEmissionIntensity(value);
}

const float EngineInterface::quad3d_getLightness(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getLightness();
}

const float EngineInterface::quad3d_getMinHeight(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getMinHeight();
}

const float EngineInterface::quad3d_getMaxHeight(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::quad3d_getOpacity(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getOpacity();
}

const float EngineInterface::quad3d_getTextureRepeat(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getTextureRepeat();
}

const float EngineInterface::quad3d_getEmissionIntensity(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getEmissionIntensity();
}

const bool EngineInterface::quad3d_isExisting(const string& ID) const
{
	return _core->getQuad3dEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::quad3d_isVisible(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isVisible();
}

const fvec3& EngineInterface::quad3d_getPosition(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getPosition();
}

const fvec3& EngineInterface::quad3d_getRotation(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getRotation();
}

const fvec2& EngineInterface::quad3d_getSize(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getSize();
}

const fvec2& EngineInterface::quad3d_getUvMultiplier(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2& EngineInterface::quad3d_getUvOffset(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3& EngineInterface::quad3d_getColor(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getColor();
}

const fvec3& EngineInterface::quad3d_getWireframeColor(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getWireframeColor();
}

const vector<string> EngineInterface::quad3d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const bool EngineInterface::quad3d_isFacingCameraX(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isFacingCameraX();
}

const bool EngineInterface::quad3d_isFacingCameraY(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isFacingCameraY();
}

const bool EngineInterface::quad3d_isDepthMapIncluded(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isDepthMapIncluded();
}

const bool EngineInterface::quad3d_isShadowed(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isShadowed();
}

const bool EngineInterface::quad3d_isReflected(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isReflected();
}

const bool EngineInterface::quad3d_isBright(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isBright();
}

const string& EngineInterface::quad3d_getDiffuseMapPath(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const string& EngineInterface::quad3d_getEmissionMapPath(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->getEmissionMapPath();
}

const bool EngineInterface::quad3d_hasDiffuseMap(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::quad3d_hasEmissionMap(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->hasEmissionMap();
}

const bool EngineInterface::quad3d_isFrozen(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isFrozen();
}

const bool EngineInterface::quad3d_isWireframed(const string& ID) const
{
	return _core->getQuad3dEntityManager()->getEntity(ID)->isWireframed();
}
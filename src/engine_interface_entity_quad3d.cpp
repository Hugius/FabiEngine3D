#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad3d_create(const string & id, bool isCentered)
{
	_core->getQuad3dEntityManager()->createEntity(id, isCentered);
}

void EngineInterface::quad3d_delete(const string & id)
{
	for(const auto & [animationId, quadId] : _core->getAnimation2dPlayer()->getStartedQuad3dAnimationIds())
	{
		if(id == quadId)
		{
			quad3d_stopAnimation(quadId, animationId);
		}
	}

	for(const auto & [entityId, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(id == entity->getParentId())
			{
				if(entity->getParentType() == AabbParentType::QUAD3D)
				{
					aabb_delete(entityId);
				}
			}
		}
	}

	_core->getQuad3dEntityManager()->deleteEntity(id);
}

void EngineInterface::quad3d_setVisible(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::quad3d_move(const string & id, const fvec3 & change)
{
	_core->getQuad3dEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::quad3d_rotate(const string & id, const fvec3 & change)
{
	_core->getQuad3dEntityManager()->getEntity(id)->rotate(change);
}

void EngineInterface::quad3d_scale(const string & id, const fvec2 & change)
{
	_core->getQuad3dEntityManager()->getEntity(id)->scale(change);
}

void EngineInterface::quad3d_moveTo(const string & id, const fvec3 & target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::quad3d_rotateTo(const string & id, const fvec3 & target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(id)->rotateTo(target, speed);
}

void EngineInterface::quad3d_scaleTo(const string & id, const fvec2 & target, float speed)
{
	_core->getQuad3dEntityManager()->getEntity(id)->scaleTo(target, speed);
}

void EngineInterface::quad3d_setPosition(const string & id, const fvec3 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::quad3d_setRotation(const string & id, const fvec3 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setRotation(value);
}

void EngineInterface::quad3d_setSize(const string & id, const fvec2 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setSize(value);
}

void EngineInterface::quad3d_setColor(const string & id, const fvec3 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::quad3d_setWireframeColor(const string & id, const fvec3 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::quad3d_setUvMultiplier(const string & id, const fvec2 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setUvMultiplier(value);
}

void EngineInterface::quad3d_setUvOffset(const string & id, const fvec2 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setUvOffset(value);
}

void EngineInterface::quad3d_setMinClipPosition(const string & id, const fvec3 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setMinClipPosition(value);
}

void EngineInterface::quad3d_setMaxClipPosition(const string & id, const fvec3 & value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setMaxClipPosition(value);
}

void EngineInterface::quad3d_setDiffuseMap(const string & id, const string & value)
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
			auto image = _core->getImageLoader()->loadImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);
				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getQuad3dEntityManager()->getEntity(id)->setDiffuseMap(texture);
		_core->getQuad3dEntityManager()->getEntity(id)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad3d_setEmissionMap(const string & id, const string & value)
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
			auto image = _core->getImageLoader()->loadImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);
				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getQuad3dEntityManager()->getEntity(id)->setEmissionMap(texture);
		_core->getQuad3dEntityManager()->getEntity(id)->setEmissionMapPath(value);
	}
}

void EngineInterface::quad3d_setWireframed(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::quad3d_setFrozen(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setFrozen(value);
}

void EngineInterface::quad3d_startAnimation(const string & quadId, const string & animationId, int playCount)
{
	_core->getAnimation2dPlayer()->startQuad3dAnimation(animationId, quadId, playCount);
}

void EngineInterface::quad3d_pauseAnimation(const string & quadId, const string & animationId)
{
	_core->getAnimation2dPlayer()->pauseQuad3dAnimation(animationId, quadId);
}

void EngineInterface::quad3d_autopauseAnimation(const string & quadId, const string & animationId)
{
	_core->getAnimation2dPlayer()->autopauseQuad3dAnimation(animationId, quadId);
}

void EngineInterface::quad3d_resumeAnimation(const string & quadId, const string & animationId)
{
	_core->getAnimation2dPlayer()->resumeQuad3dAnimation(animationId, quadId);
}

void EngineInterface::quad3d_stopAnimation(const string & quadId, const string & animationId)
{
	_core->getAnimation2dPlayer()->stopQuad3dAnimation(animationId, quadId);
}

void EngineInterface::quad3d_setAnimationRowIndex(const string & quadId, const string & animationId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimationRowIndex(animationId, quadId, value);
}

void EngineInterface::quad3d_setAnimationColumnIndex(const string & quadId, const string & animationId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimationColumnIndex(animationId, quadId, value);
}

void EngineInterface::quad3d_setAnimationIntervalMultiplier(const string & quadId, const string & animationId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimationIntervalMultiplier(animationId, quadId, value);
}

void EngineInterface::quad3d_setAnimationIntervalDivider(const string & quadId, const string & animationId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimationIntervalDivider(animationId, quadId, value);
}

void EngineInterface::quad3d_setHorizontallyFlipped(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setHorizontallyFlipped(value);
}

void EngineInterface::quad3d_setVerticallyFlipped(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setVerticallyFlipped(value);
}

void EngineInterface::quad3d_setRotationOrder(const string & id, DirectionOrderType value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setRotationOrder(value);
}

void EngineInterface::quad3d_setFacingCameraHorizontally(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setFacingCameraHorizontally(value);
}

void EngineInterface::quad3d_setFacingCameraVertically(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setFacingCameraVertically(value);
}

void EngineInterface::quad3d_setShadowed(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setShadowed(value);
}

void EngineInterface::quad3d_setReflected(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setReflected(value);
}

void EngineInterface::quad3d_setBright(const string & id, bool value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setBright(value);
}

void EngineInterface::quad3d_setLightness(const string & id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setLightness(value);
}

void EngineInterface::quad3d_setOpacity(const string & id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setOpacity(value);
}

void EngineInterface::quad3d_setTextureRepeat(const string & id, int value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setTextureRepeat(value);
}

void EngineInterface::quad3d_setEmissionIntensity(const string & id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setEmissionIntensity(value);
}

void EngineInterface::quad3d_setMinTextureAlpha(const string & id, float value)
{
	_core->getQuad3dEntityManager()->getEntity(id)->setMinTextureAlpha(value);
}

const float EngineInterface::quad3d_getLightness(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getLightness();
}

const float EngineInterface::quad3d_getOpacity(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getOpacity();
}

const unsigned int EngineInterface::quad3d_getTextureRepeat(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getTextureRepeat();
}

const float EngineInterface::quad3d_getEmissionIntensity(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getEmissionIntensity();
}

const float EngineInterface::quad3d_getMinTextureAlpha(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getMinTextureAlpha();
}

const int EngineInterface::quad3d_getAnimationPlayCount(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimationPlayCount(quadId, animationId);
}

const unsigned int EngineInterface::quad3d_getAnimationRowIndex(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimationRowIndex(quadId, animationId);
}

const unsigned int EngineInterface::quad3d_getAnimationColumnIndex(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimationColumnIndex(quadId, animationId);
}

const unsigned int EngineInterface::quad3d_getAnimationIntervalMultiplier(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimationIntervalMultiplier(quadId, animationId);
}

const unsigned int EngineInterface::quad3d_getAnimationIntervalDivider(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimationIntervalDivider(quadId, animationId);
}

const bool EngineInterface::quad3d_isExisting(const string & id) const
{
	return _core->getQuad3dEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::quad3d_isVisible(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isVisible();
}

const fvec3 & EngineInterface::quad3d_getPosition(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getPosition();
}

const fvec3 & EngineInterface::quad3d_getRotation(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getRotation();
}

const fvec2 & EngineInterface::quad3d_getSize(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getSize();
}

const fvec2 & EngineInterface::quad3d_getUvMultiplier(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getUvMultiplier();
}

const fvec2 & EngineInterface::quad3d_getUvOffset(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getUvOffset();
}

const fvec3 & EngineInterface::quad3d_getColor(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getColor();
}

const fvec3 & EngineInterface::quad3d_getWireframeColor(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getWireframeColor();
}

const fvec3 & EngineInterface::quad3d_getMinClipPosition(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getMinClipPosition();
}

const fvec3 & EngineInterface::quad3d_getMaxClipPosition(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getMaxClipPosition();
}

const vector<string> EngineInterface::quad3d_getIds() const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getQuad3dEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const vector<string> EngineInterface::quad3d_getAnimationIds(const string & id) const
{
	vector<string> result;

	for(const auto & [animationId, quadId] : _core->getAnimation2dPlayer()->getStartedQuad3dAnimationIds())
	{
		if(id == quadId)
		{
			result.push_back(animationId);
		}
	}

	return result;
}

const vector<string> EngineInterface::quad3d_getChildAabbIds(const string & id) const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(id == entity->getParentId())
			{
				if(entity->getParentType() == AabbParentType::QUAD3D)
				{
					result.push_back(entity->getId());
				}
			}
		}
	}

	return result;
}

const bool EngineInterface::quad3d_isFacingCameraHorizontally(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isFacingCameraHorizontally();
}

const bool EngineInterface::quad3d_isFacingCameraVertically(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isFacingCameraVertically();
}

const bool EngineInterface::quad3d_isShadowed(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isShadowed();
}

const bool EngineInterface::quad3d_isReflected(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isReflected();
}

const bool EngineInterface::quad3d_isBright(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isBright();
}

const string & EngineInterface::quad3d_getDiffuseMapPath(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getDiffuseMapPath();
}

const string & EngineInterface::quad3d_getEmissionMapPath(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getEmissionMapPath();
}

const bool EngineInterface::quad3d_hasDiffuseMap(const string & id) const
{
	return (_core->getQuad3dEntityManager()->getEntity(id)->getDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::quad3d_hasEmissionMap(const string & id) const
{
	return (_core->getQuad3dEntityManager()->getEntity(id)->getEmissionTextureBuffer() != nullptr);
}

const bool EngineInterface::quad3d_isFrozen(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isFrozen();
}

const bool EngineInterface::quad3d_isAnimationStarted(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->isQuad3dAnimationStarted(animationId, quadId);
}

const bool EngineInterface::quad3d_isAnimationPaused(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->isQuad3dAnimationPaused(animationId, quadId);
}

const bool EngineInterface::quad3d_isAnimationAutopaused(const string & quadId, const string & animationId) const
{
	return _core->getAnimation2dPlayer()->isQuad3dAnimationAutopaused(animationId, quadId);
}

const bool EngineInterface::quad3d_isHorizontallyFlipped(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isHorizontallyFlipped();
}

const bool EngineInterface::quad3d_isVerticallyFlipped(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isVerticallyFlipped();
}

const DirectionOrderType EngineInterface::quad3d_getRotationOrder(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->getRotationOrder();
}

const bool EngineInterface::quad3d_isWireframed(const string & id) const
{
	return _core->getQuad3dEntityManager()->getEntity(id)->isWireframed();
}
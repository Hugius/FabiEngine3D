#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad3d_create(const string & quad3dId, bool isCentered)
{
	_core->getQuad3dManager()->createQuad3d(quad3dId, isCentered);
}

void EngineInterface::quad3d_delete(const string & quad3dId)
{
	for(const auto & [animation2dId, quad3dId] : _core->getAnimation2dPlayer()->getStartedQuad3dAnimation2dIds())
	{
		if(quad3dId == quad3dId)
		{
			quad3d_stopAnimation(quad3dId, animation2dId);
		}
	}

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasParent())
		{
			if(quad3dId == aabb->getParentId())
			{
				if(aabb->getParentType() == AabbParentType::QUAD3D)
				{
					aabb_delete(aabbId);
				}
			}
		}
	}

	_core->getQuad3dManager()->deleteQuad3d(quad3dId);
}

void EngineInterface::quad3d_setVisible(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setVisible(value);
}

void EngineInterface::quad3d_move(const string & quad3dId, const fvec3 & change)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->move(change);
}

void EngineInterface::quad3d_rotate(const string & quad3dId, const fvec3 & change)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->rotate(change);
}

void EngineInterface::quad3d_scale(const string & quad3dId, const fvec2 & change)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->scale(change);
}

void EngineInterface::quad3d_moveTo(const string & quad3dId, const fvec3 & target, float speed)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->moveTo(target, speed);
}

void EngineInterface::quad3d_rotateTo(const string & quad3dId, const fvec3 & target, float speed)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->rotateTo(target, speed);
}

void EngineInterface::quad3d_scaleTo(const string & quad3dId, const fvec2 & target, float speed)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->scaleTo(target, speed);
}

void EngineInterface::quad3d_setPosition(const string & quad3dId, const fvec3 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setPosition(value);
}

void EngineInterface::quad3d_setRotation(const string & quad3dId, const fvec3 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setRotation(value);
}

void EngineInterface::quad3d_setSize(const string & quad3dId, const fvec2 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setSize(value);
}

void EngineInterface::quad3d_setColor(const string & quad3dId, const fvec3 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setColor(value);
}

void EngineInterface::quad3d_setWireframeColor(const string & quad3dId, const fvec3 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setWireframeColor(value);
}

void EngineInterface::quad3d_setUvMultiplier(const string & quad3dId, const fvec2 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setUvMultiplier(value);
}

void EngineInterface::quad3d_setUvOffset(const string & quad3dId, const fvec2 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setUvOffset(value);
}

void EngineInterface::quad3d_setMinClipPosition(const string & quad3dId, const fvec3 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setMinClipPosition(value);
}

void EngineInterface::quad3d_setMaxClipPosition(const string & quad3dId, const fvec3 & value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setMaxClipPosition(value);
}

void EngineInterface::quad3d_setDiffuseMap(const string & quad3dId, const string & value)
{
	if(value.empty())
	{
		_core->getQuad3dManager()->getQuad3d(quad3dId)->setDiffuseMap(nullptr);
		_core->getQuad3dManager()->getQuad3d(quad3dId)->setDiffuseMapPath("");
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

		_core->getQuad3dManager()->getQuad3d(quad3dId)->setDiffuseMap(texture);
		_core->getQuad3dManager()->getQuad3d(quad3dId)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad3d_setEmissionMap(const string & quad3dId, const string & value)
{
	if(value.empty())
	{
		_core->getQuad3dManager()->getQuad3d(quad3dId)->setEmissionMap(nullptr);
		_core->getQuad3dManager()->getQuad3d(quad3dId)->setEmissionMapPath("");
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

		_core->getQuad3dManager()->getQuad3d(quad3dId)->setEmissionMap(texture);
		_core->getQuad3dManager()->getQuad3d(quad3dId)->setEmissionMapPath(value);
	}
}

void EngineInterface::quad3d_setWireframed(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setWireframed(value);
}

void EngineInterface::quad3d_setFrozen(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setFrozen(value);
}

void EngineInterface::quad3d_startAnimation(const string & quad3dId, const string & animation2dId, int playCount)
{
	_core->getAnimation2dPlayer()->startQuad3dAnimation2d(animation2dId, quad3dId, playCount);
}

void EngineInterface::quad3d_pauseAnimation(const string & quad3dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->pauseQuad3dAnimation2d(animation2dId, quad3dId);
}

void EngineInterface::quad3d_autopauseAnimation(const string & quad3dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->autopauseQuad3dAnimation2d(animation2dId, quad3dId);
}

void EngineInterface::quad3d_resumeAnimation(const string & quad3dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->resumeQuad3dAnimation2d(animation2dId, quad3dId);
}

void EngineInterface::quad3d_stopAnimation(const string & quad3dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->stopQuad3dAnimation2d(animation2dId, quad3dId);
}

void EngineInterface::quad3d_setAnimationRowIndex(const string & quad3dId, const string & animation2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimation2dRowIndex(animation2dId, quad3dId, value);
}

void EngineInterface::quad3d_setAnimationColumnIndex(const string & quad3dId, const string & animation2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimation2dColumnIndex(animation2dId, quad3dId, value);
}

void EngineInterface::quad3d_setAnimationIntervalMultiplier(const string & quad3dId, const string & animation2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimation2dIntervalMultiplier(animation2dId, quad3dId, value);
}

void EngineInterface::quad3d_setAnimationIntervalDivider(const string & quad3dId, const string & animation2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad3dAnimation2dIntervalDivider(animation2dId, quad3dId, value);
}

void EngineInterface::quad3d_setHorizontallyFlipped(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setHorizontallyFlipped(value);
}

void EngineInterface::quad3d_setVerticallyFlipped(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setVerticallyFlipped(value);
}

void EngineInterface::quad3d_setRotationOrder(const string & quad3dId, DirectionOrderType value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setRotationOrder(value);
}

void EngineInterface::quad3d_setFacingCameraHorizontally(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setFacingCameraHorizontally(value);
}

void EngineInterface::quad3d_setFacingCameraVertically(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setFacingCameraVertically(value);
}

void EngineInterface::quad3d_setShadowed(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setShadowed(value);
}

void EngineInterface::quad3d_setReflected(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setReflected(value);
}

void EngineInterface::quad3d_setRefracted(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setRefracted(value);
}

void EngineInterface::quad3d_setBright(const string & quad3dId, bool value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setBright(value);
}

void EngineInterface::quad3d_setLightness(const string & quad3dId, float value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setLightness(value);
}

void EngineInterface::quad3d_setOpacity(const string & quad3dId, float value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setOpacity(value);
}

void EngineInterface::quad3d_setTextureRepeat(const string & quad3dId, int value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setTextureRepeat(value);
}

void EngineInterface::quad3d_setEmissionIntensity(const string & quad3dId, float value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setEmissionIntensity(value);
}

void EngineInterface::quad3d_setMinAlpha(const string & quad3dId, float value)
{
	_core->getQuad3dManager()->getQuad3d(quad3dId)->setMinAlpha(value);
}

const float EngineInterface::quad3d_getLightness(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getLightness();
}

const float EngineInterface::quad3d_getOpacity(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getOpacity();
}

const int EngineInterface::quad3d_getTextureRepeat(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getTextureRepeat();
}

const float EngineInterface::quad3d_getEmissionIntensity(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getEmissionIntensity();
}

const float EngineInterface::quad3d_getMinAlpha(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getMinAlpha();
}

const int EngineInterface::quad3d_getAnimationPlayCount(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimation2dPlayCount(quad3dId, animation2dId);
}

const int EngineInterface::quad3d_getAnimationRowIndex(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimation2dRowIndex(quad3dId, animation2dId);
}

const int EngineInterface::quad3d_getAnimationColumnIndex(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimation2dColumnIndex(quad3dId, animation2dId);
}

const int EngineInterface::quad3d_getAnimationIntervalMultiplier(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimation2dIntervalMultiplier(quad3dId, animation2dId);
}

const int EngineInterface::quad3d_getAnimationIntervalDivider(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad3dAnimation2dIntervalDivider(quad3dId, animation2dId);
}

const bool EngineInterface::quad3d_isExisting(const string & quad3dId) const
{
	return _core->getQuad3dManager()->isQuad3dExisting(quad3dId);
}

const bool EngineInterface::quad3d_isVisible(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isVisible();
}

const fvec3 & EngineInterface::quad3d_getPosition(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getPosition();
}

const fvec3 & EngineInterface::quad3d_getRotation(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getRotation();
}

const fvec2 & EngineInterface::quad3d_getSize(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getSize();
}

const fvec2 & EngineInterface::quad3d_getUvMultiplier(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getUvMultiplier();
}

const fvec2 & EngineInterface::quad3d_getUvOffset(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getUvOffset();
}

const fvec3 & EngineInterface::quad3d_getColor(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getColor();
}

const fvec3 & EngineInterface::quad3d_getWireframeColor(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getWireframeColor();
}

const fvec3 & EngineInterface::quad3d_getMinClipPosition(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getMinClipPosition();
}

const fvec3 & EngineInterface::quad3d_getMaxClipPosition(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getMaxClipPosition();
}

const vector<string> EngineInterface::quad3d_getIds() const
{
	vector<string> result = {};

	for(const auto & [quad3dId, quad3d] : _core->getQuad3dManager()->getQuad3ds())
	{
		result.push_back(quad3d->getId());
	}

	return result;
}

const vector<string> EngineInterface::quad3d_getAnimationIds(const string & quad3dId) const
{
	vector<string> result = {};

	for(const auto & [animation2dId, quad3dId] : _core->getAnimation2dPlayer()->getStartedQuad3dAnimation2dIds())
	{
		if(quad3dId == quad3dId)
		{
			result.push_back(animation2dId);
		}
	}

	return result;
}

const vector<string> EngineInterface::quad3d_getChildAabbIds(const string & quad3dId) const
{
	vector<string> result = {};

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasParent())
		{
			if(quad3dId == aabb->getParentId())
			{
				if(aabb->getParentType() == AabbParentType::QUAD3D)
				{
					result.push_back(aabb->getId());
				}
			}
		}
	}

	return result;
}

const bool EngineInterface::quad3d_isFacingCameraHorizontally(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isFacingCameraHorizontally();
}

const bool EngineInterface::quad3d_isFacingCameraVertically(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isFacingCameraVertically();
}

const bool EngineInterface::quad3d_isShadowed(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isShadowed();
}

const bool EngineInterface::quad3d_isReflected(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isReflected();
}

const bool EngineInterface::quad3d_isRefracted(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isRefracted();
}

const bool EngineInterface::quad3d_isBright(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isBright();
}

const string & EngineInterface::quad3d_getDiffuseMapPath(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getDiffuseMapPath();
}

const string & EngineInterface::quad3d_getEmissionMapPath(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getEmissionMapPath();
}

const bool EngineInterface::quad3d_hasDiffuseMap(const string & quad3dId) const
{
	return (_core->getQuad3dManager()->getQuad3d(quad3dId)->getDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::quad3d_hasEmissionMap(const string & quad3dId) const
{
	return (_core->getQuad3dManager()->getQuad3d(quad3dId)->getEmissionTextureBuffer() != nullptr);
}

const bool EngineInterface::quad3d_isFrozen(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isFrozen();
}

const bool EngineInterface::quad3d_isAnimationStarted(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->isQuad3dAnimation2dStarted(animation2dId, quad3dId);
}

const bool EngineInterface::quad3d_isAnimationPaused(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->isQuad3dAnimation2dPaused(animation2dId, quad3dId);
}

const bool EngineInterface::quad3d_isAnimationAutopaused(const string & quad3dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->isQuad3dAnimation2dAutopaused(animation2dId, quad3dId);
}

const bool EngineInterface::quad3d_isHorizontallyFlipped(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isHorizontallyFlipped();
}

const bool EngineInterface::quad3d_isVerticallyFlipped(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isVerticallyFlipped();
}

const DirectionOrderType EngineInterface::quad3d_getRotationOrder(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->getRotationOrder();
}

const bool EngineInterface::quad3d_isWireframed(const string & quad3dId) const
{
	return _core->getQuad3dManager()->getQuad3d(quad3dId)->isWireframed();
}
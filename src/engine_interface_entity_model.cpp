#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::model_create(const string & id, const string & meshPath)
{
	_core->getModelEntityManager()->createEntity(id, meshPath);
}

void EngineInterface::model_delete(const string & id)
{
	for(const auto & [animationId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimationIds())
	{
		if(id == modelId)
		{
			model_stopAnimation(modelId, animationId);
		}
	}

	for(const auto & [entityId, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(id == entity->getParentId())
			{
				if(entity->getParentType() == AabbParentType::MODEL)
				{
					aabb_delete(entityId);
				}
			}
		}
	}

	for(const auto & reflectionId : reflection_getIds())
	{
		if(id == reflection_getExceptionEntityId(reflectionId))
		{
			reflection_setExceptionEntityId(reflectionId, "");
		}
	}

	_core->getModelEntityManager()->deleteEntity(id);
}

void EngineInterface::model_setVisible(const string & id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::model_setDiffuseMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(modelId)->setDiffuseTextureBuffer(partId, 0);
		_core->getModelEntityManager()->getEntity(modelId)->setDiffuseMapPath(partId, "");
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

		_core->getModelEntityManager()->getEntity(modelId)->setDiffuseTextureBuffer(partId, texture);
		_core->getModelEntityManager()->getEntity(modelId)->setDiffuseMapPath(partId, value);
	}
}

void EngineInterface::model_setEmissionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(modelId)->setEmissionTextureBuffer(partId, 0);
		_core->getModelEntityManager()->getEntity(modelId)->setEmissionMapPath(partId, "");
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

		_core->getModelEntityManager()->getEntity(modelId)->setEmissionTextureBuffer(partId, texture);
		_core->getModelEntityManager()->getEntity(modelId)->setEmissionMapPath(partId, value);
	}
}

void EngineInterface::model_setSpecularMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(modelId)->setSpecularTextureBuffer(partId, 0);
		_core->getModelEntityManager()->getEntity(modelId)->setSpecularMapPath(partId, "");
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

		_core->getModelEntityManager()->getEntity(modelId)->setSpecularTextureBuffer(partId, texture);
		_core->getModelEntityManager()->getEntity(modelId)->setSpecularMapPath(partId, value);
	}
}

void EngineInterface::model_setNormalMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(modelId)->setNormalTextureBuffer(partId, 0);
		_core->getModelEntityManager()->getEntity(modelId)->setNormalMapPath(partId, "");
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

		_core->getModelEntityManager()->getEntity(modelId)->setNormalTextureBuffer(partId, texture);
		_core->getModelEntityManager()->getEntity(modelId)->setNormalMapPath(partId, value);
	}
}

void EngineInterface::model_setReflectionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(modelId)->setReflectionTextureBuffer(partId, 0);
		_core->getModelEntityManager()->getEntity(modelId)->setReflectionMapPath(partId, "");
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

		_core->getModelEntityManager()->getEntity(modelId)->setReflectionTextureBuffer(partId, texture);
		_core->getModelEntityManager()->getEntity(modelId)->setReflectionMapPath(partId, value);
	}
}

void EngineInterface::model_setLevelOfDetailEntityId(const string & id, const string & value)
{
	_core->getModelEntityManager()->getEntity(id)->setLevelOfDetailEntityId(value);
}

void EngineInterface::model_setFaceCulled(const string & modelId, const string & partId, bool value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setFaceCulled(partId, value);
}

void EngineInterface::model_setReflectionType(const string & modelId, const string & partId, ReflectionType value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setReflectionType(partId, value);
}

void EngineInterface::model_setSpecular(const string & modelId, const string & partId, bool value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setSpecular(partId, value);
}

void EngineInterface::model_setReflective(const string & modelId, const string & partId, bool value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setReflective(partId, value);
}

void EngineInterface::model_setBasePosition(const string & id, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(id)->setBasePosition(value);
}

void EngineInterface::model_setBaseRotation(const string & id, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(id)->setBaseRotation(value);
}

void EngineInterface::model_setBaseRotationOrigin(const string & id, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(id)->setBaseRotationOrigin(value);
}

void EngineInterface::model_setBaseSize(const string & id, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(id)->setBaseSize(value);
}

void EngineInterface::model_setPartPosition(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setPartPosition(partId, value);
}

void EngineInterface::model_setPartRotation(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setPartRotation(partId, value);
}

void EngineInterface::model_setPartRotationOrigin(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setPartRotationOrigin(partId, value);
}

void EngineInterface::model_setPartSize(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setPartSize(partId, value);
}

void EngineInterface::model_moveBase(const string & id, const fvec3 & change)
{
	_core->getModelEntityManager()->getEntity(id)->moveBase(change);
}

void EngineInterface::model_rotateBase(const string & id, const fvec3 & change)
{
	_core->getModelEntityManager()->getEntity(id)->rotateBase(change);
}

void EngineInterface::model_scaleBase(const string & id, const fvec3 & change)
{
	_core->getModelEntityManager()->getEntity(id)->scaleBase(change);
}

void EngineInterface::model_movePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelEntityManager()->getEntity(modelId)->movePart(partId, change);
}

void EngineInterface::model_rotatePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelEntityManager()->getEntity(modelId)->rotatePart(partId, change);
}

void EngineInterface::model_scalePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelEntityManager()->getEntity(modelId)->scalePart(partId, change);
}

void EngineInterface::model_moveBaseTo(const string & id, const fvec3 & target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->moveBaseTo(target, speed);
}

void EngineInterface::model_rotateBaseTo(const string & id, const fvec3 & target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->rotateBaseTo(target, speed);
}

void EngineInterface::model_scaleBaseTo(const string & id, const fvec3 & target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->scaleBaseTo(target, speed);
}

void EngineInterface::model_setSpecularShininess(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setSpecularShininess(partId, value);
}

void EngineInterface::model_setSpecularIntensity(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setSpecularIntensity(partId, value);
}

void EngineInterface::model_setReflectivity(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setReflectivity(partId, value);
}

void EngineInterface::model_setLightness(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setLightness(partId, value);
}

void EngineInterface::model_setEmissionIntensity(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setEmissionIntensity(partId, value);
}

void EngineInterface::model_setLevelOfDetailDistance(const string & id, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setLevelOfDetailDistance(value);
}

void EngineInterface::model_movePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelEntityManager()->getEntity(modelId)->movePartTo(partId, target, speed);
}

void EngineInterface::model_rotatePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelEntityManager()->getEntity(modelId)->rotatePartTo(partId, target, speed);
}

void EngineInterface::model_scalePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelEntityManager()->getEntity(modelId)->scalePartTo(partId, target, speed);
}

void EngineInterface::model_setTextureRepeat(const string & modelId, const string & partId, unsigned int value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setTextureRepeat(partId, value);
}

void EngineInterface::model_setBright(const string & modelId, const string & partId, bool value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setBright(partId, value);
}

void EngineInterface::model_setRotationOrder(const string & id, DirectionOrderType value)
{
	_core->getModelEntityManager()->getEntity(id)->setRotationOrder(value);
}

void EngineInterface::model_startAnimation(const string & modelId, const string & animationId, int playCount)
{
	_core->getAnimation3dPlayer()->startModelAnimation(animationId, modelId, playCount);
}

void EngineInterface::model_pauseAnimation(const string & modelId, const string & animationId)
{
	_core->getAnimation3dPlayer()->pauseModelAnimation(animationId, modelId);
}

void EngineInterface::model_autopauseAnimation(const string & modelId, const string & animationId)
{
	_core->getAnimation3dPlayer()->autopauseModelAnimation(animationId, modelId);
}

void EngineInterface::model_resumeAnimation(const string & modelId, const string & animationId)
{
	_core->getAnimation3dPlayer()->resumeModelAnimation(animationId, modelId);
}

void EngineInterface::model_stopAnimation(const string & modelId, const string & animationId)
{
	_core->getAnimation3dPlayer()->stopModelAnimation(animationId, modelId);
}

void EngineInterface::model_setAnimationSpeedMultiplier(const string & modelId, const string & animationId, float value)
{
	_core->getAnimation3dPlayer()->setModelAnimationSpeedMultiplier(animationId, modelId, value);
}

void EngineInterface::model_setAnimationFrameIndex(const string & modelId, const string & animationId, unsigned int value)
{
	_core->getAnimation3dPlayer()->setModelAnimationFrameIndex(animationId, modelId, value);
}

void EngineInterface::model_setFrozen(const string & id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setFrozen(value);
}

void EngineInterface::model_setWireframed(const string & modelId, const string & partId, bool value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setWireframed(partId, value);
}

void EngineInterface::model_setOpacity(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setOpacity(partId, value);
}

void EngineInterface::model_setMinTextureAlpha(const string & modelId, const string & partId, float value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setMinTextureAlpha(partId, value);
}

void EngineInterface::model_setShadowed(const string & id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setShadowed(value);
}

void EngineInterface::model_setColor(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setColor(partId, value);
}

void EngineInterface::model_setWireframeColor(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(modelId)->setWireframeColor(partId, value);
}

void EngineInterface::model_setMinClippingPosition(const string & id, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(id)->setMinClippingPosition(value);
}

void EngineInterface::model_setMaxClippingPosition(const string & id, const fvec3 & value)
{
	_core->getModelEntityManager()->getEntity(id)->setMaxClippingPosition(value);
}

void EngineInterface::model_setReflected(const string & id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setReflected(value);
}

const bool EngineInterface::model_isExisting(const string & id) const
{
	return _core->getModelEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::model_isVisible(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::model_isMultiParted(const string & id) const
{
	return (_core->getModelEntityManager()->getEntity(id)->getPartIds().size() > 1);
}

const bool EngineInterface::model_isFaceCulled(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->isFaceCulled(partId);
}

const bool EngineInterface::model_isSpecular(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->isSpecular(partId);
}

const bool EngineInterface::model_isShadowed(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isShadowed();
}

const bool EngineInterface::model_isReflected(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isReflected();
}

const bool EngineInterface::model_isFrozen(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isFrozen();
}

const bool EngineInterface::model_isWireframed(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->isWireframed(partId);
}

const bool EngineInterface::model_hasPart(const string & modelId, const string & partId) const
{
	for(const auto & existingPartId : model_getPartIds(modelId))
	{
		if(partId == existingPartId)
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::model_isBright(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->isBright(partId);
}

const bool EngineInterface::model_isReflective(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->isReflective(partId);
}

const bool EngineInterface::model_hasDiffuseMap(const string & modelId, const string & partId) const
{
	return (_core->getModelEntityManager()->getEntity(modelId)->getDiffuseTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasEmissionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelEntityManager()->getEntity(modelId)->getEmissionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasSpecularMap(const string & modelId, const string & partId) const
{
	return (_core->getModelEntityManager()->getEntity(modelId)->getSpecularTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasReflectionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelEntityManager()->getEntity(modelId)->getReflectionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasNormalMap(const string & modelId, const string & partId) const
{
	return (_core->getModelEntityManager()->getEntity(modelId)->getNormalTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_isAnimationStarted(const string & modelId, const string & animationId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimationStarted(animationId, modelId);
}

const bool EngineInterface::model_isAnimationPaused(const string & modelId, const string & animationId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimationPaused(animationId, modelId);
}

const bool EngineInterface::model_isAnimationAutopaused(const string & modelId, const string & animationId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimationAutopaused(animationId, modelId);
}

const ReflectionType EngineInterface::model_getReflectionType(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getReflectionType(partId);
}

const DirectionOrderType EngineInterface::model_getRotationOrder(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getRotationOrder();
}

const fvec3 & EngineInterface::model_getBasePosition(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBasePosition();
}

const fvec3 & EngineInterface::model_getBaseRotation(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBaseRotation();
}

const fvec3 & EngineInterface::model_getBaseRotationOrigin(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBaseRotationOrigin();
}

const fvec3 & EngineInterface::model_getBaseSize(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBaseSize();
}

const fvec3 & EngineInterface::model_getPartPosition(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getPartPosition(partId);
}

const fvec3 & EngineInterface::model_getPartRotation(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getPartRotation(partId);
}

const fvec3 & EngineInterface::model_getPartRotationOrigin(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getPartRotationOrigin(partId);
}

const fvec3 & EngineInterface::model_getPartSize(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getPartSize(partId);
}

const fvec3 & EngineInterface::model_getColor(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getColor(partId);
}

const fvec3 & EngineInterface::model_getWireframeColor(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getWireframeColor(partId);
}

const fvec3 & EngineInterface::model_getMinClippingPosition(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getMinClippingPosition();
}

const fvec3 & EngineInterface::model_getMaxClippingPosition(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getMaxClippingPosition();
}

const float EngineInterface::model_getLightness(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getLightness(partId);
}

const float EngineInterface::model_getReflectivity(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getReflectivity(partId);
}

const float EngineInterface::model_getSpecularShininess(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getSpecularShininess(partId);
}

const float EngineInterface::model_getSpecularIntensity(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getSpecularIntensity(partId);
}

const float EngineInterface::model_getOpacity(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getOpacity(partId);
}

const float EngineInterface::model_getLevelOfDetailDistance(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getLevelOfDetailDistance();
}

const unsigned int EngineInterface::model_getTextureRepeat(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getTextureRepeat(partId);
}

const float EngineInterface::model_getEmissionIntensity(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getEmissionIntensity(partId);
}

const float EngineInterface::model_getMinTextureAlpha(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getMinTextureAlpha(partId);
}

const float EngineInterface::model_getAnimationSpeedMultiplier(const string & modelId, const string & animationId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimationSpeedMultiplier(animationId, modelId);
}

const int EngineInterface::model_getAnimationPlayCount(const string & modelId, const string & animationId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimationPlayCount(animationId, modelId);
}

const unsigned int EngineInterface::model_getAnimationFrameIndex(const string & modelId, const string & animationId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimationFrameIndex(animationId, modelId);
}

const string & EngineInterface::model_getMeshPath(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getMeshPath();
}

const string & EngineInterface::model_getDiffuseMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getDiffuseMapPath(partId);
}

const string & EngineInterface::model_getEmissionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getEmissionMapPath(partId);
}

const string & EngineInterface::model_getSpecularMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getSpecularMapPath(partId);
}

const string & EngineInterface::model_getReflectionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getReflectionMapPath(partId);
}

const string & EngineInterface::model_getNormalMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelEntityManager()->getEntity(modelId)->getNormalMapPath(partId);
}

const string & EngineInterface::model_getLevelOfDetailEntityId(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getLevelOfDetailEntityId();
}

const vector<string> EngineInterface::model_getPartIds(const string & id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getPartIds();
}

const vector<string> EngineInterface::model_getAnimationIds(const string & id) const
{
	vector<string> result;

	for(const auto & [animationId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimationIds())
	{
		if(id == modelId)
		{
			result.push_back(animationId);
		}
	}

	return result;
}

const vector<string> EngineInterface::model_getIds() const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getModelEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const vector<string> EngineInterface::model_getChildAabbIds(const string & id)
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasParent())
		{
			if(id == entity->getParentId())
			{
				if(entity->getParentType() == AabbParentType::MODEL)
				{
					result.push_back(entity->getId());
				}
			}
		}
	}

	return result;
}
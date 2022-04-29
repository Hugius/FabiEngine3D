#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::model_create(const string & modelId, const string & meshPath)
{
	_core->getModelManager()->createEntity(modelId, meshPath);
}

void EngineInterface::model_delete(const string & modelId)
{
	for(const auto & [animation3dId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimationIds())
	{
		if(modelId == modelId)
		{
			model_stopAnimation(modelId, animation3dId);
		}
	}

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasParent())
		{
			if(modelId == aabb->getParentId())
			{
				if(aabb->getParentType() == AabbParentType::MODEL)
				{
					aabb_delete(aabbId);
				}
			}
		}
	}

	for(const auto & captorId : captor_getIds())
	{
		if(modelId == captor_getExceptionId(captorId))
		{
			captor_setExceptionId(captorId, "");
		}
	}

	_core->getModelManager()->deleteEntity(modelId);
}

void EngineInterface::model_setVisible(const string & modelId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setVisible(value);
}

void EngineInterface::model_setDiffuseMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getEntity(modelId)->setDiffuseTextureBuffer(partId, 0);
		_core->getModelManager()->getEntity(modelId)->setDiffuseMapPath(partId, "");
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

		_core->getModelManager()->getEntity(modelId)->setDiffuseTextureBuffer(partId, texture);
		_core->getModelManager()->getEntity(modelId)->setDiffuseMapPath(partId, value);
	}
}

void EngineInterface::model_setEmissionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getEntity(modelId)->setEmissionTextureBuffer(partId, 0);
		_core->getModelManager()->getEntity(modelId)->setEmissionMapPath(partId, "");
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

		_core->getModelManager()->getEntity(modelId)->setEmissionTextureBuffer(partId, texture);
		_core->getModelManager()->getEntity(modelId)->setEmissionMapPath(partId, value);
	}
}

void EngineInterface::model_setSpecularMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getEntity(modelId)->setSpecularTextureBuffer(partId, 0);
		_core->getModelManager()->getEntity(modelId)->setSpecularMapPath(partId, "");
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

		_core->getModelManager()->getEntity(modelId)->setSpecularTextureBuffer(partId, texture);
		_core->getModelManager()->getEntity(modelId)->setSpecularMapPath(partId, value);
	}
}

void EngineInterface::model_setNormalMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getEntity(modelId)->setNormalTextureBuffer(partId, 0);
		_core->getModelManager()->getEntity(modelId)->setNormalMapPath(partId, "");
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

		_core->getModelManager()->getEntity(modelId)->setNormalTextureBuffer(partId, texture);
		_core->getModelManager()->getEntity(modelId)->setNormalMapPath(partId, value);
	}
}

void EngineInterface::model_setReflectionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getEntity(modelId)->setReflectionTextureBuffer(partId, 0);
		_core->getModelManager()->getEntity(modelId)->setReflectionMapPath(partId, "");
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

		_core->getModelManager()->getEntity(modelId)->setReflectionTextureBuffer(partId, texture);
		_core->getModelManager()->getEntity(modelId)->setReflectionMapPath(partId, value);
	}
}

void EngineInterface::model_setLevelOfDetailId(const string & modelId, const string & value)
{
	_core->getModelManager()->getEntity(modelId)->setLevelOfDetailId(value);
}

void EngineInterface::model_setFaceCulled(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setFaceCulled(partId, value);
}

void EngineInterface::model_setReflectionType(const string & modelId, const string & partId, ReflectionType value)
{
	_core->getModelManager()->getEntity(modelId)->setReflectionType(partId, value);
}

void EngineInterface::model_setSpecular(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setSpecular(partId, value);
}

void EngineInterface::model_setReflective(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setReflective(partId, value);
}

void EngineInterface::model_setBasePosition(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setBasePosition(value);
}

void EngineInterface::model_setBaseRotation(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setBaseRotation(value);
}

void EngineInterface::model_setBaseRotationOrigin(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setBaseRotationOrigin(value);
}

void EngineInterface::model_setBaseSize(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setBaseSize(value);
}

void EngineInterface::model_setPartPosition(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setPartPosition(partId, value);
}

void EngineInterface::model_setPartRotation(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setPartRotation(partId, value);
}

void EngineInterface::model_setPartRotationOrigin(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setPartRotationOrigin(partId, value);
}

void EngineInterface::model_setPartSize(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setPartSize(partId, value);
}

void EngineInterface::model_moveBase(const string & modelId, const fvec3 & change)
{
	_core->getModelManager()->getEntity(modelId)->moveBase(change);
}

void EngineInterface::model_rotateBase(const string & modelId, const fvec3 & change)
{
	_core->getModelManager()->getEntity(modelId)->rotateBase(change);
}

void EngineInterface::model_scaleBase(const string & modelId, const fvec3 & change)
{
	_core->getModelManager()->getEntity(modelId)->scaleBase(change);
}

void EngineInterface::model_movePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelManager()->getEntity(modelId)->movePart(partId, change);
}

void EngineInterface::model_rotatePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelManager()->getEntity(modelId)->rotatePart(partId, change);
}

void EngineInterface::model_scalePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelManager()->getEntity(modelId)->scalePart(partId, change);
}

void EngineInterface::model_moveBaseTo(const string & modelId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getEntity(modelId)->moveBaseTo(target, speed);
}

void EngineInterface::model_rotateBaseTo(const string & modelId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getEntity(modelId)->rotateBaseTo(target, speed);
}

void EngineInterface::model_scaleBaseTo(const string & modelId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getEntity(modelId)->scaleBaseTo(target, speed);
}

void EngineInterface::model_setSpecularShininess(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setSpecularShininess(partId, value);
}

void EngineInterface::model_setSpecularIntensity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setSpecularIntensity(partId, value);
}

void EngineInterface::model_setReflectivity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setReflectivity(partId, value);
}

void EngineInterface::model_setLightness(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setLightness(partId, value);
}

void EngineInterface::model_setEmissionIntensity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setEmissionIntensity(partId, value);
}

void EngineInterface::model_setLevelOfDetailDistance(const string & modelId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setLevelOfDetailDistance(value);
}

void EngineInterface::model_movePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getEntity(modelId)->movePartTo(partId, target, speed);
}

void EngineInterface::model_rotatePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getEntity(modelId)->rotatePartTo(partId, target, speed);
}

void EngineInterface::model_scalePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getEntity(modelId)->scalePartTo(partId, target, speed);
}

void EngineInterface::model_setTextureRepeat(const string & modelId, const string & partId, int value)
{
	_core->getModelManager()->getEntity(modelId)->setTextureRepeat(partId, value);
}

void EngineInterface::model_setBright(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setBright(partId, value);
}

void EngineInterface::model_setRotationOrder(const string & modelId, DirectionOrderType value)
{
	_core->getModelManager()->getEntity(modelId)->setRotationOrder(value);
}

void EngineInterface::model_startAnimation(const string & modelId, const string & animation3dId, int playCount)
{
	_core->getAnimation3dPlayer()->startModelAnimation(animation3dId, modelId, playCount);
}

void EngineInterface::model_pauseAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->pauseModelAnimation(animation3dId, modelId);
}

void EngineInterface::model_autopauseAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->autopauseModelAnimation(animation3dId, modelId);
}

void EngineInterface::model_resumeAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->resumeModelAnimation(animation3dId, modelId);
}

void EngineInterface::model_stopAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->stopModelAnimation(animation3dId, modelId);
}

void EngineInterface::model_setAnimationSpeedMultiplier(const string & modelId, const string & animation3dId, float value)
{
	_core->getAnimation3dPlayer()->setModelAnimationSpeedMultiplier(animation3dId, modelId, value);
}

void EngineInterface::model_setAnimationFrameIndex(const string & modelId, const string & animation3dId, int value)
{
	_core->getAnimation3dPlayer()->setModelAnimationFrameIndex(animation3dId, modelId, value);
}

void EngineInterface::model_setFrozen(const string & modelId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setFrozen(value);
}

void EngineInterface::model_setWireframed(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setWireframed(partId, value);
}

void EngineInterface::model_setOpacity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setOpacity(partId, value);
}

void EngineInterface::model_setMinTextureAlpha(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getEntity(modelId)->setMinTextureAlpha(partId, value);
}

void EngineInterface::model_setShadowed(const string & modelId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setShadowed(value);
}

void EngineInterface::model_setColor(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setColor(partId, value);
}

void EngineInterface::model_setWireframeColor(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setWireframeColor(partId, value);
}

void EngineInterface::model_setMinClipPosition(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setMinClipPosition(value);
}

void EngineInterface::model_setMaxClipPosition(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getEntity(modelId)->setMaxClipPosition(value);
}

void EngineInterface::model_setReflected(const string & modelId, bool value)
{
	_core->getModelManager()->getEntity(modelId)->setReflected(value);
}

const bool EngineInterface::model_isExisting(const string & modelId) const
{
	return _core->getModelManager()->isEntityExisting(modelId);
}

const bool EngineInterface::model_isVisible(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->isVisible();
}

const bool EngineInterface::model_isMultiParted(const string & modelId) const
{
	return (_core->getModelManager()->getEntity(modelId)->getPartIds().size() > 1);
}

const bool EngineInterface::model_isFaceCulled(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->isFaceCulled(partId);
}

const bool EngineInterface::model_isSpecular(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->isSpecular(partId);
}

const bool EngineInterface::model_isShadowed(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->isShadowed();
}

const bool EngineInterface::model_isReflected(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->isReflected();
}

const bool EngineInterface::model_isFrozen(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->isFrozen();
}

const bool EngineInterface::model_isWireframed(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->isWireframed(partId);
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
	return _core->getModelManager()->getEntity(modelId)->isBright(partId);
}

const bool EngineInterface::model_isReflective(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->isReflective(partId);
}

const bool EngineInterface::model_hasDiffuseMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getEntity(modelId)->getDiffuseTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasEmissionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getEntity(modelId)->getEmissionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasSpecularMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getEntity(modelId)->getSpecularTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasReflectionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getEntity(modelId)->getReflectionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasNormalMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getEntity(modelId)->getNormalTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_isAnimationStarted(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimationStarted(animation3dId, modelId);
}

const bool EngineInterface::model_isAnimationPaused(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimationPaused(animation3dId, modelId);
}

const bool EngineInterface::model_isAnimationAutopaused(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimationAutopaused(animation3dId, modelId);
}

const ReflectionType EngineInterface::model_getReflectionType(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getReflectionType(partId);
}

const DirectionOrderType EngineInterface::model_getRotationOrder(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getRotationOrder();
}

const fvec3 & EngineInterface::model_getBasePosition(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getBasePosition();
}

const fvec3 & EngineInterface::model_getBaseRotation(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getBaseRotation();
}

const fvec3 & EngineInterface::model_getBaseRotationOrigin(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getBaseRotationOrigin();
}

const fvec3 & EngineInterface::model_getBaseSize(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getBaseSize();
}

const fvec3 & EngineInterface::model_getPartPosition(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getPartPosition(partId);
}

const fvec3 & EngineInterface::model_getPartRotation(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getPartRotation(partId);
}

const fvec3 & EngineInterface::model_getPartRotationOrigin(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getPartRotationOrigin(partId);
}

const fvec3 & EngineInterface::model_getPartSize(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getPartSize(partId);
}

const fvec3 & EngineInterface::model_getColor(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getColor(partId);
}

const fvec3 & EngineInterface::model_getWireframeColor(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getWireframeColor(partId);
}

const fvec3 & EngineInterface::model_getMinClipPosition(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getMinClipPosition();
}

const fvec3 & EngineInterface::model_getMaxClipPosition(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getMaxClipPosition();
}

const float EngineInterface::model_getLightness(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getLightness(partId);
}

const float EngineInterface::model_getReflectivity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getReflectivity(partId);
}

const float EngineInterface::model_getSpecularShininess(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getSpecularShininess(partId);
}

const float EngineInterface::model_getSpecularIntensity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getSpecularIntensity(partId);
}

const float EngineInterface::model_getOpacity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getOpacity(partId);
}

const float EngineInterface::model_getLevelOfDetailDistance(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getLevelOfDetailDistance();
}

const int EngineInterface::model_getTextureRepeat(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getTextureRepeat(partId);
}

const float EngineInterface::model_getEmissionIntensity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getEmissionIntensity(partId);
}

const float EngineInterface::model_getMinTextureAlpha(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getMinTextureAlpha(partId);
}

const float EngineInterface::model_getAnimationSpeedMultiplier(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimationSpeedMultiplier(animation3dId, modelId);
}

const int EngineInterface::model_getAnimationPlayCount(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimationPlayCount(animation3dId, modelId);
}

const int EngineInterface::model_getAnimationFrameIndex(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimationFrameIndex(animation3dId, modelId);
}

const string & EngineInterface::model_getMeshPath(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getMeshPath();
}

const string & EngineInterface::model_getDiffuseMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getDiffuseMapPath(partId);
}

const string & EngineInterface::model_getEmissionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getEmissionMapPath(partId);
}

const string & EngineInterface::model_getSpecularMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getSpecularMapPath(partId);
}

const string & EngineInterface::model_getReflectionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getReflectionMapPath(partId);
}

const string & EngineInterface::model_getNormalMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getEntity(modelId)->getNormalMapPath(partId);
}

const string & EngineInterface::model_getLevelOfDetailId(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getLevelOfDetailId();
}

const vector<string> EngineInterface::model_getPartIds(const string & modelId) const
{
	return _core->getModelManager()->getEntity(modelId)->getPartIds();
}

const vector<string> EngineInterface::model_getAnimationIds(const string & modelId) const
{
	vector<string> result;

	for(const auto & [animation3dId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimationIds())
	{
		if(modelId == modelId)
		{
			result.push_back(animation3dId);
		}
	}

	return result;
}

const vector<string> EngineInterface::model_getIds() const
{
	vector<string> result;

	for(const auto & [modelId, model] : _core->getModelManager()->getEntities())
	{
		result.push_back(model->getId());
	}

	return result;
}

const vector<string> EngineInterface::model_getChildAabbIds(const string & modelId)
{
	vector<string> result;

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasParent())
		{
			if(modelId == aabb->getParentId())
			{
				if(aabb->getParentType() == AabbParentType::MODEL)
				{
					result.push_back(aabb->getId());
				}
			}
		}
	}

	return result;
}
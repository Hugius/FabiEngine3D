#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::model_create(const string & modelId, const string & meshPath)
{
	_core->getModelManager()->createModel(modelId, meshPath);
}

void EngineInterface::model_delete(const string & modelId)
{
	for(const auto & [animation3dId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimation3dIds())
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

	_core->getModelManager()->deleteModel(modelId);
}

void EngineInterface::model_setVisible(const string & modelId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setVisible(value);
}

void EngineInterface::model_setDiffuseMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getModel(modelId)->setDiffuseTextureBuffer(partId, 0);
		_core->getModelManager()->getModel(modelId)->setDiffuseMapPath(partId, "");
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

		_core->getModelManager()->getModel(modelId)->setDiffuseTextureBuffer(partId, texture);
		_core->getModelManager()->getModel(modelId)->setDiffuseMapPath(partId, value);
	}
}

void EngineInterface::model_setEmissionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getModel(modelId)->setEmissionTextureBuffer(partId, 0);
		_core->getModelManager()->getModel(modelId)->setEmissionMapPath(partId, "");
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

		_core->getModelManager()->getModel(modelId)->setEmissionTextureBuffer(partId, texture);
		_core->getModelManager()->getModel(modelId)->setEmissionMapPath(partId, value);
	}
}

void EngineInterface::model_setSpecularMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getModel(modelId)->setSpecularTextureBuffer(partId, 0);
		_core->getModelManager()->getModel(modelId)->setSpecularMapPath(partId, "");
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

		_core->getModelManager()->getModel(modelId)->setSpecularTextureBuffer(partId, texture);
		_core->getModelManager()->getModel(modelId)->setSpecularMapPath(partId, value);
	}
}

void EngineInterface::model_setNormalMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getModel(modelId)->setNormalTextureBuffer(partId, 0);
		_core->getModelManager()->getModel(modelId)->setNormalMapPath(partId, "");
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

		_core->getModelManager()->getModel(modelId)->setNormalTextureBuffer(partId, texture);
		_core->getModelManager()->getModel(modelId)->setNormalMapPath(partId, value);
	}
}

void EngineInterface::model_setReflectionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getModel(modelId)->setReflectionTextureBuffer(partId, 0);
		_core->getModelManager()->getModel(modelId)->setReflectionMapPath(partId, "");
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

		_core->getModelManager()->getModel(modelId)->setReflectionTextureBuffer(partId, texture);
		_core->getModelManager()->getModel(modelId)->setReflectionMapPath(partId, value);
	}
}

void EngineInterface::model_setRefractionMap(const string & modelId, const string & partId, const string & value)
{
	if(value.empty())
	{
		_core->getModelManager()->getModel(modelId)->setRefractionTextureBuffer(partId, 0);
		_core->getModelManager()->getModel(modelId)->setRefractionMapPath(partId, "");
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

		_core->getModelManager()->getModel(modelId)->setRefractionTextureBuffer(partId, texture);
		_core->getModelManager()->getModel(modelId)->setRefractionMapPath(partId, value);
	}
}

void EngineInterface::model_setLevelOfDetailId(const string & modelId, const string & value)
{
	_core->getModelManager()->getModel(modelId)->setLevelOfDetailId(value);
}

void EngineInterface::model_setFaceCulled(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setFaceCulled(partId, value);
}

void EngineInterface::model_setReflectionType(const string & modelId, const string & partId, ReflectionType value)
{
	_core->getModelManager()->getModel(modelId)->setReflectionType(partId, value);
}

void EngineInterface::model_setRefractionType(const string & modelId, const string & partId, RefractionType value)
{
	_core->getModelManager()->getModel(modelId)->setRefractionType(partId, value);
}

void EngineInterface::model_setSpecular(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setSpecular(partId, value);
}

void EngineInterface::model_setReflective(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setReflective(partId, value);
}

void EngineInterface::model_setRefractive(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setRefractive(partId, value);
}

void EngineInterface::model_setBasePosition(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setBasePosition(value);
}

void EngineInterface::model_setBaseRotation(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setBaseRotation(value);
}

void EngineInterface::model_setBaseRotationOrigin(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setBaseRotationOrigin(value);
}

void EngineInterface::model_setBaseSize(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setBaseSize(value);
}

void EngineInterface::model_setPartPosition(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setPartPosition(partId, value);
}

void EngineInterface::model_setPartRotation(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setPartRotation(partId, value);
}

void EngineInterface::model_setPartRotationOrigin(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setPartRotationOrigin(partId, value);
}

void EngineInterface::model_setPartSize(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setPartSize(partId, value);
}

void EngineInterface::model_moveBase(const string & modelId, const fvec3 & change)
{
	_core->getModelManager()->getModel(modelId)->moveBase(change);
}

void EngineInterface::model_rotateBase(const string & modelId, const fvec3 & change)
{
	_core->getModelManager()->getModel(modelId)->rotateBase(change);
}

void EngineInterface::model_scaleBase(const string & modelId, const fvec3 & change)
{
	_core->getModelManager()->getModel(modelId)->scaleBase(change);
}

void EngineInterface::model_movePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelManager()->getModel(modelId)->movePart(partId, change);
}

void EngineInterface::model_rotatePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelManager()->getModel(modelId)->rotatePart(partId, change);
}

void EngineInterface::model_scalePart(const string & modelId, const string & partId, const fvec3 & change)
{
	_core->getModelManager()->getModel(modelId)->scalePart(partId, change);
}

void EngineInterface::model_moveBaseTo(const string & modelId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getModel(modelId)->moveBaseTo(target, speed);
}

void EngineInterface::model_rotateBaseTo(const string & modelId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getModel(modelId)->rotateBaseTo(target, speed);
}

void EngineInterface::model_scaleBaseTo(const string & modelId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getModel(modelId)->scaleBaseTo(target, speed);
}

void EngineInterface::model_setSpecularShininess(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setSpecularShininess(partId, value);
}

void EngineInterface::model_setSpecularIntensity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setSpecularIntensity(partId, value);
}

void EngineInterface::model_setReflectivity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setReflectivity(partId, value);
}

void EngineInterface::model_setRefractivity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setRefractivity(partId, value);
}

void EngineInterface::model_setLightness(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setLightness(partId, value);
}

void EngineInterface::model_setEmissionIntensity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setEmissionIntensity(partId, value);
}

void EngineInterface::model_setLevelOfDetailDistance(const string & modelId, float value)
{
	_core->getModelManager()->getModel(modelId)->setLevelOfDetailDistance(value);
}

void EngineInterface::model_movePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getModel(modelId)->movePartTo(partId, target, speed);
}

void EngineInterface::model_rotatePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getModel(modelId)->rotatePartTo(partId, target, speed);
}

void EngineInterface::model_scalePartTo(const string & modelId, const string & partId, const fvec3 & target, float speed)
{
	_core->getModelManager()->getModel(modelId)->scalePartTo(partId, target, speed);
}

void EngineInterface::model_setTextureRepeat(const string & modelId, const string & partId, int value)
{
	_core->getModelManager()->getModel(modelId)->setTextureRepeat(partId, value);
}

void EngineInterface::model_setBright(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setBright(partId, value);
}

void EngineInterface::model_setRotationOrder(const string & modelId, DirectionOrderType value)
{
	_core->getModelManager()->getModel(modelId)->setRotationOrder(value);
}

void EngineInterface::model_startAnimation(const string & modelId, const string & animation3dId, int playCount)
{
	_core->getAnimation3dPlayer()->startModelAnimation3d(animation3dId, modelId, playCount);
}

void EngineInterface::model_pauseAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->pauseModelAnimation3d(animation3dId, modelId);
}

void EngineInterface::model_autopauseAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->autopauseModelAnimation3d(animation3dId, modelId);
}

void EngineInterface::model_resumeAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->resumeModelAnimation3d(animation3dId, modelId);
}

void EngineInterface::model_stopAnimation(const string & modelId, const string & animation3dId)
{
	_core->getAnimation3dPlayer()->stopModelAnimation3d(animation3dId, modelId);
}

void EngineInterface::model_setAnimationSpeedMultiplier(const string & modelId, const string & animation3dId, float value)
{
	_core->getAnimation3dPlayer()->setModelAnimation3dSpeedMultiplier(animation3dId, modelId, value);
}

void EngineInterface::model_setAnimationFrameIndex(const string & modelId, const string & animation3dId, int value)
{
	_core->getAnimation3dPlayer()->setModelAnimation3dFrameIndex(animation3dId, modelId, value);
}

void EngineInterface::model_setFrozen(const string & modelId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setFrozen(value);
}

void EngineInterface::model_setWireframed(const string & modelId, const string & partId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setWireframed(partId, value);
}

void EngineInterface::model_setOpacity(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setOpacity(partId, value);
}

void EngineInterface::model_setMinTextureAlpha(const string & modelId, const string & partId, float value)
{
	_core->getModelManager()->getModel(modelId)->setMinTextureAlpha(partId, value);
}

void EngineInterface::model_setShadowed(const string & modelId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setShadowed(value);
}

void EngineInterface::model_setColor(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setColor(partId, value);
}

void EngineInterface::model_setWireframeColor(const string & modelId, const string & partId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setWireframeColor(partId, value);
}

void EngineInterface::model_setMinClipPosition(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setMinClipPosition(value);
}

void EngineInterface::model_setMaxClipPosition(const string & modelId, const fvec3 & value)
{
	_core->getModelManager()->getModel(modelId)->setMaxClipPosition(value);
}

void EngineInterface::model_setReflected(const string & modelId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setReflected(value);
}

void EngineInterface::model_setRefracted(const string & modelId, bool value)
{
	_core->getModelManager()->getModel(modelId)->setRefracted(value);
}

const bool EngineInterface::model_isExisting(const string & modelId) const
{
	return _core->getModelManager()->isModelExisting(modelId);
}

const bool EngineInterface::model_isVisible(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->isVisible();
}

const bool EngineInterface::model_isMultiParted(const string & modelId) const
{
	return (_core->getModelManager()->getModel(modelId)->getPartIds().size() > 1);
}

const bool EngineInterface::model_isFaceCulled(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->isFaceCulled(partId);
}

const bool EngineInterface::model_isSpecular(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->isSpecular(partId);
}

const bool EngineInterface::model_isShadowed(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->isShadowed();
}

const bool EngineInterface::model_isReflected(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->isReflected();
}

const bool EngineInterface::model_isRefracted(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->isRefracted();
}

const bool EngineInterface::model_isFrozen(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->isFrozen();
}

const bool EngineInterface::model_isWireframed(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->isWireframed(partId);
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
	return _core->getModelManager()->getModel(modelId)->isBright(partId);
}

const bool EngineInterface::model_isReflective(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->isReflective(partId);
}

const bool EngineInterface::model_isRefractive(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->isRefractive(partId);
}

const bool EngineInterface::model_hasDiffuseMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getModel(modelId)->getDiffuseTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasEmissionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getModel(modelId)->getEmissionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasSpecularMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getModel(modelId)->getSpecularTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasReflectionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getModel(modelId)->getReflectionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasRefractionMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getModel(modelId)->getRefractionTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_hasNormalMap(const string & modelId, const string & partId) const
{
	return (_core->getModelManager()->getModel(modelId)->getNormalTextureBuffer(partId) != nullptr);
}

const bool EngineInterface::model_isAnimationStarted(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimation3dStarted(animation3dId, modelId);
}

const bool EngineInterface::model_isAnimationPaused(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimation3dPaused(animation3dId, modelId);
}

const bool EngineInterface::model_isAnimationAutopaused(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->isModelAnimation3dAutopaused(animation3dId, modelId);
}

const ReflectionType EngineInterface::model_getReflectionType(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getReflectionType(partId);
}

const RefractionType EngineInterface::model_getRefractionType(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getRefractionType(partId);
}

const DirectionOrderType EngineInterface::model_getRotationOrder(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getRotationOrder();
}

const fvec3 & EngineInterface::model_getBasePosition(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getBasePosition();
}

const fvec3 & EngineInterface::model_getBaseRotation(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getBaseRotation();
}

const fvec3 & EngineInterface::model_getBaseRotationOrigin(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getBaseRotationOrigin();
}

const fvec3 & EngineInterface::model_getBaseSize(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getBaseSize();
}

const fvec3 & EngineInterface::model_getPartPosition(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getPartPosition(partId);
}

const fvec3 & EngineInterface::model_getPartRotation(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getPartRotation(partId);
}

const fvec3 & EngineInterface::model_getPartRotationOrigin(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getPartRotationOrigin(partId);
}

const fvec3 & EngineInterface::model_getPartSize(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getPartSize(partId);
}

const fvec3 & EngineInterface::model_getColor(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getColor(partId);
}

const fvec3 & EngineInterface::model_getWireframeColor(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getWireframeColor(partId);
}

const fvec3 & EngineInterface::model_getMinClipPosition(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getMinClipPosition();
}

const fvec3 & EngineInterface::model_getMaxClipPosition(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getMaxClipPosition();
}

const float EngineInterface::model_getLightness(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getLightness(partId);
}

const float EngineInterface::model_getReflectivity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getReflectivity(partId);
}

const float EngineInterface::model_getRefractivity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getRefractivity(partId);
}

const float EngineInterface::model_getSpecularShininess(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getSpecularShininess(partId);
}

const float EngineInterface::model_getSpecularIntensity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getSpecularIntensity(partId);
}

const float EngineInterface::model_getOpacity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getOpacity(partId);
}

const float EngineInterface::model_getLevelOfDetailDistance(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getLevelOfDetailDistance();
}

const int EngineInterface::model_getTextureRepeat(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getTextureRepeat(partId);
}

const float EngineInterface::model_getEmissionIntensity(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getEmissionIntensity(partId);
}

const float EngineInterface::model_getMinTextureAlpha(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getMinTextureAlpha(partId);
}

const float EngineInterface::model_getAnimationSpeedMultiplier(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimation3dSpeedMultiplier(animation3dId, modelId);
}

const int EngineInterface::model_getAnimationPlayCount(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimation3dPlayCount(animation3dId, modelId);
}

const int EngineInterface::model_getAnimationFrameIndex(const string & modelId, const string & animation3dId) const
{
	return _core->getAnimation3dPlayer()->getModelAnimation3dFrameIndex(animation3dId, modelId);
}

const string & EngineInterface::model_getMeshPath(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getMeshPath();
}

const string & EngineInterface::model_getDiffuseMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getDiffuseMapPath(partId);
}

const string & EngineInterface::model_getEmissionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getEmissionMapPath(partId);
}

const string & EngineInterface::model_getSpecularMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getSpecularMapPath(partId);
}

const string & EngineInterface::model_getReflectionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getReflectionMapPath(partId);
}

const string & EngineInterface::model_getRefractionMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getRefractionMapPath(partId);
}

const string & EngineInterface::model_getNormalMapPath(const string & modelId, const string & partId) const
{
	return _core->getModelManager()->getModel(modelId)->getNormalMapPath(partId);
}

const string & EngineInterface::model_getLevelOfDetailId(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getLevelOfDetailId();
}

const vector<string> EngineInterface::model_getPartIds(const string & modelId) const
{
	return _core->getModelManager()->getModel(modelId)->getPartIds();
}

const vector<string> EngineInterface::model_getAnimationIds(const string & modelId) const
{
	vector<string> result;

	for(const auto & [animation3dId, modelId] : _core->getAnimation3dPlayer()->getStartedModelAnimation3dIds())
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

	for(const auto & [modelId, model] : _core->getModelManager()->getModels())
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
#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::model_create(const string& ID, const string& meshPath)
{
	_core->getModelEntityManager()->createEntity(ID, meshPath);
}

void EngineInterface::model_deleteAll()
{
	for(const auto& [key, entity] : _core->getModelEntityManager()->getEntities())
	{
		model_delete(entity->getID());
	}
}

void EngineInterface::model_delete(const string& ID)
{
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::MODEL))
	{
		_core->getAabbEntityManager()->deleteEntity(aabbID);
	}

	_core->getModelEntityManager()->deleteEntity(ID);
}

void EngineInterface::model_setVisible(const string& ID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::model_setDiffuseMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(ID)->setDiffuseMap(partID, 0);
		_core->getModelEntityManager()->getEntity(ID)->setDiffuseMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(ID)->setDiffuseMap(partID, texture);
		_core->getModelEntityManager()->getEntity(ID)->setDiffuseMapPath(partID, value);
	}
}

void EngineInterface::model_setEmissionMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(ID)->setEmissionMap(partID, 0);
		_core->getModelEntityManager()->getEntity(ID)->setEmissionMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(ID)->setEmissionMap(partID, texture);
		_core->getModelEntityManager()->getEntity(ID)->setEmissionMapPath(partID, value);
	}
}

void EngineInterface::model_setSpecularMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(ID)->setSpecularMap(partID, 0);
		_core->getModelEntityManager()->getEntity(ID)->setSpecularMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(ID)->setSpecularMap(partID, texture);
		_core->getModelEntityManager()->getEntity(ID)->setSpecularMapPath(partID, value);
	}
}

void EngineInterface::model_setNormalMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(ID)->setNormalMap(partID, 0);
		_core->getModelEntityManager()->getEntity(ID)->setNormalMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(ID)->setNormalMap(partID, texture);
		_core->getModelEntityManager()->getEntity(ID)->setNormalMapPath(partID, value);
	}
}

void EngineInterface::model_setReflectionMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(ID)->setReflectionMap(partID, 0);
		_core->getModelEntityManager()->getEntity(ID)->setReflectionMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(ID)->setReflectionMap(partID, texture);
		_core->getModelEntityManager()->getEntity(ID)->setReflectionMapPath(partID, value);
	}
}

void EngineInterface::model_setLevelOfDetailEntityID(const string& ID, const string& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setLevelOfDetailEntityID(value);
}

void EngineInterface::model_setFaceCulled(const string& ID, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setFaceCulled(partID, value);
}

void EngineInterface::model_setReflectionType(const string& ID, const string& partID, ReflectionType value)
{
	_core->getModelEntityManager()->getEntity(ID)->setReflectionType(partID, value);
}

void EngineInterface::model_setSpecular(const string& ID, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setSpecular(partID, value);
}

void EngineInterface::model_setReflective(const string& ID, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setReflective(partID, value);
}

void EngineInterface::model_setBasePosition(const string& ID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setBasePosition(value);
}

void EngineInterface::model_setBaseRotation(const string& ID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setBaseRotation(value);
}

void EngineInterface::model_setBaseRotationOrigin(const string& ID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setBaseRotationOrigin(value);
}

void EngineInterface::model_setBaseSize(const string& ID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setBaseSize(value);
}

void EngineInterface::model_setPartPosition(const string& ID, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setPartPosition(partID, value);
}

void EngineInterface::model_setPartRotation(const string& ID, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setPartRotation(partID, value);
}

void EngineInterface::model_setPartRotationOrigin(const string& ID, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setPartRotationOrigin(partID, value);
}

void EngineInterface::model_setPartSize(const string& ID, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setPartSize(partID, value);
}

void EngineInterface::model_moveBase(const string& ID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(ID)->moveBase(change);
}

void EngineInterface::model_rotateBase(const string& ID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(ID)->rotateBase(change);
}

void EngineInterface::model_scaleBase(const string& ID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(ID)->scaleBase(change);
}

void EngineInterface::model_movePart(const string& ID, const string& partID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(ID)->movePart(partID, change);
}

void EngineInterface::model_rotatePart(const string& ID, const string& partID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(ID)->rotatePart(partID, change);
}

void EngineInterface::model_scalePart(const string& ID, const string& partID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(ID)->scalePart(partID, change);
}

void EngineInterface::model_moveBaseTo(const string& ID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(ID)->moveBaseTo(target, speed);
}

void EngineInterface::model_rotateBaseTo(const string& ID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(ID)->rotateBaseTo(target, speed);
}

void EngineInterface::model_scaleBaseTo(const string& ID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(ID)->scaleBaseTo(target, speed);
}

void EngineInterface::model_setSpecularShininess(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setSpecularShininess(partID, value);
}

void EngineInterface::model_setSpecularIntensity(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setSpecularIntensity(partID, value);
}

void EngineInterface::model_setReflectivity(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setReflectivity(partID, value);
}

void EngineInterface::model_setLightness(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setLightness(partID, value);
}

void EngineInterface::model_setEmissionIntensity(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setEmissionIntensity(partID, value);
}

void EngineInterface::model_setMinHeight(const string& ID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setMinHeight(value);
}

void EngineInterface::model_setMaxHeight(const string& ID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setMaxHeight(value);
}

void EngineInterface::model_setLevelOfDetailDistance(const string& ID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setLevelOfDetailDistance(value);
}

void EngineInterface::model_movePartTo(const string& ID, const string& partID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(ID)->movePartTo(partID, target, speed);
}

void EngineInterface::model_rotatePartTo(const string& ID, const string& partID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(ID)->rotatePartTo(partID, target, speed);
}

void EngineInterface::model_scalePartTo(const string& ID, const string& partID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(ID)->scalePartTo(partID, target, speed);
}

void EngineInterface::model_setLevelOfDetailSize(const string& ID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setLevelOfDetailSize(value);
}

void EngineInterface::model_setTextureRepeat(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setTextureRepeat(partID, value);
}

void EngineInterface::model_setBright(const string& ID, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setBright(partID, value);
}

void EngineInterface::model_setRotationOrder(const string& ID, DirectionOrder value)
{
	_core->getModelEntityManager()->getEntity(ID)->setRotationOrder(value);
}

void EngineInterface::model_setFrozen(const string& ID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setFrozen(value);
}

void EngineInterface::model_setWireframed(const string& ID, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setWireframed(partID, value);
}

void EngineInterface::model_setOpacity(const string& ID, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(ID)->setOpacity(partID, value);
}

void EngineInterface::model_setShadowed(const string& ID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setShadowed(value);
}

void EngineInterface::model_setDepthMapIncluded(const string& ID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setDepthMapIncluded(value);
}

void EngineInterface::model_setColor(const string& ID, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setColor(partID, value);
}

void EngineInterface::model_setWireframeColor(const string& ID, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(ID)->setWireframeColor(partID, value);
}

void EngineInterface::model_setReflected(const string& ID, bool value)
{
	_core->getModelEntityManager()->getEntity(ID)->setReflected(value);
}

const bool EngineInterface::model_isExisting(const string& ID) const
{
	return _core->getModelEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::model_isVisible(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::model_isMultiParted(const string& ID) const
{
	return (_core->getModelEntityManager()->getEntity(ID)->getPartIDs().size() > 1);
}

const bool EngineInterface::model_isFaceCulled(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isFaceCulled(partID);
}

const bool EngineInterface::model_isSpecular(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isSpecular(partID);
}

const bool EngineInterface::model_isShadowed(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isShadowed();
}

const bool EngineInterface::model_isReflected(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isReflected();
}

const bool EngineInterface::model_isFrozen(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isFrozen();
}

const bool EngineInterface::model_isWireframed(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isWireframed(partID);
}

const bool EngineInterface::model_isDepthMapIncluded(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isDepthMapIncluded();
}

const bool EngineInterface::model_hasPart(const string& ID, const string& partID) const
{
	for(const auto& existingPartID : model_getPartIDs(ID))
	{
		if(partID == existingPartID)
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::model_isBright(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isBright(partID);
}

const bool EngineInterface::model_isReflective(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isReflective(partID);
}

const bool EngineInterface::model_hasDiffuseMap(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->hasDiffuseMap(partID);
}

const bool EngineInterface::model_hasEmissionMap(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->hasEmissionMap(partID);
}

const bool EngineInterface::model_hasSpecularMap(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->hasSpecularMap(partID);
}

const bool EngineInterface::model_hasReflectionMap(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->hasReflectionMap(partID);
}

const bool EngineInterface::model_hasNormalMap(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->hasNormalMap(partID);
}

const ReflectionType EngineInterface::model_getReflectionType(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getReflectionType(partID);
}

const DirectionOrder EngineInterface::model_getRotationOrder(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getRotationOrder();
}

const fvec3& EngineInterface::model_getBasePosition(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBasePosition();
}

const fvec3& EngineInterface::model_getBaseRotation(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBaseRotation();
}

const fvec3& EngineInterface::model_getBaseRotationOrigin(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBaseRotationOrigin();
}

const fvec3& EngineInterface::model_getBaseSize(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBaseSize();
}

const fvec3& EngineInterface::model_getPartPosition(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartPosition(partID);
}

const fvec3& EngineInterface::model_getPartRotation(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartRotation(partID);
}

const fvec3& EngineInterface::model_getPartRotationOrigin(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartRotationOrigin(partID);
}

const fvec3& EngineInterface::model_getPartSize(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartSize(partID);
}

const fvec3& EngineInterface::model_getColor(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getColor(partID);
}

const fvec3& EngineInterface::model_getWireframeColor(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getWireframeColor(partID);
}

const fvec3& EngineInterface::model_getLevelOfDetailSize(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getLevelOfDetailSize();
}

const float EngineInterface::model_getLightness(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getLightness(partID);
}

const float EngineInterface::model_getReflectivity(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getReflectivity(partID);
}

const float EngineInterface::model_getSpecularShininess(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getSpecularShininess(partID);
}

const float EngineInterface::model_getSpecularIntensity(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getSpecularIntensity(partID);
}

const float EngineInterface::model_getOpacity(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getOpacity(partID);
}

const float EngineInterface::model_getMinHeight(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getMinHeight();
}

const float EngineInterface::model_getMaxHeight(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::model_getLevelOfDetailDistance(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getLevelOfDetailDistance();
}

const float EngineInterface::model_getTextureRepeat(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getTextureRepeat(partID);
}

const float EngineInterface::model_getEmissionIntensity(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getEmissionIntensity(partID);
}

const string& EngineInterface::model_getMeshPath(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getMeshPath();
}

const string& EngineInterface::model_getDiffuseMapPath(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getDiffuseMapPath(partID);
}

const string& EngineInterface::model_getEmissionMapPath(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getEmissionMapPath(partID);
}

const string& EngineInterface::model_getSpecularMapPath(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getSpecularMapPath(partID);
}

const string& EngineInterface::model_getReflectionMapPath(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getReflectionMapPath(partID);
}

const string& EngineInterface::model_getNormalMapPath(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getNormalMapPath(partID);
}

const string& EngineInterface::model_getLevelOfDetailEntityID(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getLevelOfDetailEntityID();
}

const vector<string> EngineInterface::model_getPartIDs(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartIDs();
}

const vector<string> EngineInterface::model_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getModelEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const vector<string> EngineInterface::model_getGroupIDs(const string& ID) const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getModelEntityManager()->getEntities())
	{
		if(entity->getID().size() >= ID.size())
		{
			if(entity->getID().substr(0, ID.size()) == ID)
			{
				result.push_back(entity->getID());
			}
		}
	}

	return result;
}
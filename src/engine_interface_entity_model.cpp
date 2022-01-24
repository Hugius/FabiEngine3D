#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::model_create(const string& id, const string& meshPath)
{
	_core->getModelEntityManager()->createEntity(id, meshPath);
}

void EngineInterface::model_deleteAll()
{
	for(const auto& [key, entity] : _core->getModelEntityManager()->getEntities())
	{
		model_delete(entity->getID());
	}
}

void EngineInterface::model_delete(const string& id)
{
	for(const auto& aabbID : aabb_getChildIDs(id, AabbParentEntityType::MODEL))
	{
		_core->getAabbEntityManager()->deleteEntity(aabbID);
	}

	_core->getModelEntityManager()->deleteEntity(id);
}

void EngineInterface::model_setVisible(const string& id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::model_setDiffuseMap(const string& id, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(id)->setDiffuseMap(partID, 0);
		_core->getModelEntityManager()->getEntity(id)->setDiffuseMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(id)->setDiffuseMap(partID, texture);
		_core->getModelEntityManager()->getEntity(id)->setDiffuseMapPath(partID, value);
	}
}

void EngineInterface::model_setEmissionMap(const string& id, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(id)->setEmissionMap(partID, 0);
		_core->getModelEntityManager()->getEntity(id)->setEmissionMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(id)->setEmissionMap(partID, texture);
		_core->getModelEntityManager()->getEntity(id)->setEmissionMapPath(partID, value);
	}
}

void EngineInterface::model_setSpecularMap(const string& id, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(id)->setSpecularMap(partID, 0);
		_core->getModelEntityManager()->getEntity(id)->setSpecularMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(id)->setSpecularMap(partID, texture);
		_core->getModelEntityManager()->getEntity(id)->setSpecularMapPath(partID, value);
	}
}

void EngineInterface::model_setNormalMap(const string& id, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(id)->setNormalMap(partID, 0);
		_core->getModelEntityManager()->getEntity(id)->setNormalMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(id)->setNormalMap(partID, texture);
		_core->getModelEntityManager()->getEntity(id)->setNormalMapPath(partID, value);
	}
}

void EngineInterface::model_setReflectionMap(const string& id, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->getModelEntityManager()->getEntity(id)->setReflectionMap(partID, 0);
		_core->getModelEntityManager()->getEntity(id)->setReflectionMapPath(partID, "");
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

		_core->getModelEntityManager()->getEntity(id)->setReflectionMap(partID, texture);
		_core->getModelEntityManager()->getEntity(id)->setReflectionMapPath(partID, value);
	}
}

void EngineInterface::model_setLevelOfDetailEntityID(const string& id, const string& value)
{
	_core->getModelEntityManager()->getEntity(id)->setLevelOfDetailEntityID(value);
}

void EngineInterface::model_setFaceCulled(const string& id, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setFaceCulled(partID, value);
}

void EngineInterface::model_setReflectionType(const string& id, const string& partID, ReflectionType value)
{
	_core->getModelEntityManager()->getEntity(id)->setReflectionType(partID, value);
}

void EngineInterface::model_setSpecular(const string& id, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setSpecular(partID, value);
}

void EngineInterface::model_setReflective(const string& id, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setReflective(partID, value);
}

void EngineInterface::model_setBasePosition(const string& id, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setBasePosition(value);
}

void EngineInterface::model_setBaseRotation(const string& id, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setBaseRotation(value);
}

void EngineInterface::model_setBaseRotationOrigin(const string& id, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setBaseRotationOrigin(value);
}

void EngineInterface::model_setBaseSize(const string& id, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setBaseSize(value);
}

void EngineInterface::model_setPartPosition(const string& id, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setPartPosition(partID, value);
}

void EngineInterface::model_setPartRotation(const string& id, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setPartRotation(partID, value);
}

void EngineInterface::model_setPartRotationOrigin(const string& id, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setPartRotationOrigin(partID, value);
}

void EngineInterface::model_setPartSize(const string& id, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setPartSize(partID, value);
}

void EngineInterface::model_moveBase(const string& id, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(id)->moveBase(change);
}

void EngineInterface::model_rotateBase(const string& id, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(id)->rotateBase(change);
}

void EngineInterface::model_scaleBase(const string& id, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(id)->scaleBase(change);
}

void EngineInterface::model_movePart(const string& id, const string& partID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(id)->movePart(partID, change);
}

void EngineInterface::model_rotatePart(const string& id, const string& partID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(id)->rotatePart(partID, change);
}

void EngineInterface::model_scalePart(const string& id, const string& partID, const fvec3& change)
{
	_core->getModelEntityManager()->getEntity(id)->scalePart(partID, change);
}

void EngineInterface::model_moveBaseTo(const string& id, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->moveBaseTo(target, speed);
}

void EngineInterface::model_rotateBaseTo(const string& id, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->rotateBaseTo(target, speed);
}

void EngineInterface::model_scaleBaseTo(const string& id, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->scaleBaseTo(target, speed);
}

void EngineInterface::model_setSpecularShininess(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setSpecularShininess(partID, value);
}

void EngineInterface::model_setSpecularIntensity(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setSpecularIntensity(partID, value);
}

void EngineInterface::model_setReflectivity(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setReflectivity(partID, value);
}

void EngineInterface::model_setLightness(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setLightness(partID, value);
}

void EngineInterface::model_setEmissionIntensity(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setEmissionIntensity(partID, value);
}

void EngineInterface::model_setMinHeight(const string& id, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setMinHeight(value);
}

void EngineInterface::model_setMaxHeight(const string& id, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setMaxHeight(value);
}

void EngineInterface::model_setLevelOfDetailDistance(const string& id, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setLevelOfDetailDistance(value);
}

void EngineInterface::model_movePartTo(const string& id, const string& partID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->movePartTo(partID, target, speed);
}

void EngineInterface::model_rotatePartTo(const string& id, const string& partID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->rotatePartTo(partID, target, speed);
}

void EngineInterface::model_scalePartTo(const string& id, const string& partID, const fvec3& target, float speed)
{
	_core->getModelEntityManager()->getEntity(id)->scalePartTo(partID, target, speed);
}

void EngineInterface::model_setLevelOfDetailSize(const string& id, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setLevelOfDetailSize(value);
}

void EngineInterface::model_setTextureRepeat(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setTextureRepeat(partID, value);
}

void EngineInterface::model_setBright(const string& id, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setBright(partID, value);
}

void EngineInterface::model_setRotationOrder(const string& id, DirectionOrder value)
{
	_core->getModelEntityManager()->getEntity(id)->setRotationOrder(value);
}

void EngineInterface::model_setFrozen(const string& id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setFrozen(value);
}

void EngineInterface::model_setWireframed(const string& id, const string& partID, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setWireframed(partID, value);
}

void EngineInterface::model_setOpacity(const string& id, const string& partID, float value)
{
	_core->getModelEntityManager()->getEntity(id)->setOpacity(partID, value);
}

void EngineInterface::model_setShadowed(const string& id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setShadowed(value);
}

void EngineInterface::model_setDepthMapIncluded(const string& id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setDepthMapIncluded(value);
}

void EngineInterface::model_setColor(const string& id, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setColor(partID, value);
}

void EngineInterface::model_setWireframeColor(const string& id, const string& partID, const fvec3& value)
{
	_core->getModelEntityManager()->getEntity(id)->setWireframeColor(partID, value);
}

void EngineInterface::model_setReflected(const string& id, bool value)
{
	_core->getModelEntityManager()->getEntity(id)->setReflected(value);
}

const bool EngineInterface::model_isExisting(const string& id) const
{
	return _core->getModelEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::model_isVisible(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::model_isMultiParted(const string& id) const
{
	return (_core->getModelEntityManager()->getEntity(id)->getPartIDs().size() > 1);
}

const bool EngineInterface::model_isFaceCulled(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->isFaceCulled(partID);
}

const bool EngineInterface::model_isSpecular(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->isSpecular(partID);
}

const bool EngineInterface::model_isShadowed(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isShadowed();
}

const bool EngineInterface::model_isReflected(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isReflected();
}

const bool EngineInterface::model_isFrozen(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isFrozen();
}

const bool EngineInterface::model_isWireframed(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->isWireframed(partID);
}

const bool EngineInterface::model_isDepthMapIncluded(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->isDepthMapIncluded();
}

const bool EngineInterface::model_hasPart(const string& id, const string& partID) const
{
	for(const auto& existingPartID : model_getPartIDs(id))
	{
		if(partID == existingPartID)
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::model_isBright(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->isBright(partID);
}

const bool EngineInterface::model_isReflective(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->isReflective(partID);
}

const bool EngineInterface::model_hasDiffuseMap(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->hasDiffuseMap(partID);
}

const bool EngineInterface::model_hasEmissionMap(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->hasEmissionMap(partID);
}

const bool EngineInterface::model_hasSpecularMap(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->hasSpecularMap(partID);
}

const bool EngineInterface::model_hasReflectionMap(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->hasReflectionMap(partID);
}

const bool EngineInterface::model_hasNormalMap(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->hasNormalMap(partID);
}

const ReflectionType EngineInterface::model_getReflectionType(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getReflectionType(partID);
}

const DirectionOrder EngineInterface::model_getRotationOrder(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getRotationOrder();
}

const fvec3& EngineInterface::model_getBasePosition(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBasePosition();
}

const fvec3& EngineInterface::model_getBaseRotation(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBaseRotation();
}

const fvec3& EngineInterface::model_getBaseRotationOrigin(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBaseRotationOrigin();
}

const fvec3& EngineInterface::model_getBaseSize(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getBaseSize();
}

const fvec3& EngineInterface::model_getPartPosition(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getPartPosition(partID);
}

const fvec3& EngineInterface::model_getPartRotation(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getPartRotation(partID);
}

const fvec3& EngineInterface::model_getPartRotationOrigin(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getPartRotationOrigin(partID);
}

const fvec3& EngineInterface::model_getPartSize(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getPartSize(partID);
}

const fvec3& EngineInterface::model_getColor(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getColor(partID);
}

const fvec3& EngineInterface::model_getWireframeColor(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getWireframeColor(partID);
}

const fvec3& EngineInterface::model_getLevelOfDetailSize(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getLevelOfDetailSize();
}

const float EngineInterface::model_getLightness(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getLightness(partID);
}

const float EngineInterface::model_getReflectivity(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getReflectivity(partID);
}

const float EngineInterface::model_getSpecularShininess(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getSpecularShininess(partID);
}

const float EngineInterface::model_getSpecularIntensity(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getSpecularIntensity(partID);
}

const float EngineInterface::model_getOpacity(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getOpacity(partID);
}

const float EngineInterface::model_getMinHeight(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getMinHeight();
}

const float EngineInterface::model_getMaxHeight(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getMaxHeight();
}

const float EngineInterface::model_getLevelOfDetailDistance(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getLevelOfDetailDistance();
}

const float EngineInterface::model_getTextureRepeat(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getTextureRepeat(partID);
}

const float EngineInterface::model_getEmissionIntensity(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getEmissionIntensity(partID);
}

const string& EngineInterface::model_getMeshPath(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getMeshPath();
}

const string& EngineInterface::model_getDiffuseMapPath(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getDiffuseMapPath(partID);
}

const string& EngineInterface::model_getEmissionMapPath(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getEmissionMapPath(partID);
}

const string& EngineInterface::model_getSpecularMapPath(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getSpecularMapPath(partID);
}

const string& EngineInterface::model_getReflectionMapPath(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getReflectionMapPath(partID);
}

const string& EngineInterface::model_getNormalMapPath(const string& id, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(id)->getNormalMapPath(partID);
}

const string& EngineInterface::model_getLevelOfDetailEntityID(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getLevelOfDetailEntityID();
}

const vector<string> EngineInterface::model_getPartIDs(const string& id) const
{
	return _core->getModelEntityManager()->getEntity(id)->getPartIDs();
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

const vector<string> EngineInterface::model_getGroupIDs(const string& id) const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getModelEntityManager()->getEntities())
	{
		if(entity->getID().size() >= id.size())
		{
			if(entity->getID().substr(0, id.size()) == id)
			{
				result.push_back(entity->getID());
			}
		}
	}

	return result;
}
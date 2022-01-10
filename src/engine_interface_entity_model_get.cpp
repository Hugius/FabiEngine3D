#include "engine_interface.hpp"
#include "engine_core.hpp"

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

const bool EngineInterface::model_isFaceCulled(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isFaceCulled();
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

const bool EngineInterface::model_isBright(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->isBright();
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

const fvec3 EngineInterface::model_getBasePosition(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBasePosition();
}

const fvec3 EngineInterface::model_getBaseRotation(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBaseRotation();
}

const fvec3 EngineInterface::model_getBaseRotationOrigin(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBaseRotationOrigin();
}

const fvec3 EngineInterface::model_getBaseSize(const string& ID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getBaseSize();
}

const fvec3 EngineInterface::model_getPartPosition(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartPosition(partID);
}

const fvec3 EngineInterface::model_getPartRotation(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartRotation(partID);
}

const fvec3 EngineInterface::model_getPartRotationOrigin(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartRotationOrigin(partID);
}

const fvec3 EngineInterface::model_getPartSize(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getPartSize(partID);
}

const fvec3 EngineInterface::model_getColor(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getColor(partID);
}

const fvec3 EngineInterface::model_getWireframeColor(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getWireframeColor(partID);
}

const fvec3 EngineInterface::model_getLevelOfDetailSize(const string& ID) const
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

const float EngineInterface::model_getTransparency(const string& ID, const string& partID) const
{
	return _core->getModelEntityManager()->getEntity(ID)->getTransparency(partID);
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
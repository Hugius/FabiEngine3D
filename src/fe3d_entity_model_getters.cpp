#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::model_isExisting(const string& ID) const
{
	return _core->_modelEntityManager.isExisting(ID);
}

const bool FabiEngine3D::model_isVisible(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::model_isInstanced(const string& ID) const
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	return entity->getRenderBuffer(entity->getPartIDs()[0])->isInstanced();
}

const bool FabiEngine3D::model_isMultiParted(const string& ID) const
{
	return (_core->_modelEntityManager.getEntity(ID)->getPartIDs().size() > 1);
}

const bool FabiEngine3D::model_isFaceCulled(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isFaceCulled();
}

const bool FabiEngine3D::model_isSpecular(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isSpecular(partID);
}

const bool FabiEngine3D::model_isShadowed(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isShadowed();
}

const bool FabiEngine3D::model_isReflected(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isReflected();
}

const bool FabiEngine3D::model_isFrozen(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isFrozen();
}

const bool FabiEngine3D::model_isWireframed(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isWireframed(partID);
}

const bool FabiEngine3D::model_isDepthMapIncluded(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isDepthMapIncluded();
}

const bool FabiEngine3D::model_hasPart(const string& ID, const string& partID) const
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

const bool FabiEngine3D::model_isBright(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isBright();
}

const bool FabiEngine3D::model_isReflective(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isReflective(partID);
}

const bool FabiEngine3D::model_hasDiffuseMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasDiffuseMap(partID);
}

const bool FabiEngine3D::model_hasEmissionMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasEmissionMap(partID);
}

const bool FabiEngine3D::model_hasSpecularMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasSpecularMap(partID);
}

const bool FabiEngine3D::model_hasReflectionMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasReflectionMap(partID);
}

const bool FabiEngine3D::model_hasNormalMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasNormalMap(partID);
}

const ReflectionType FabiEngine3D::model_getReflectionType(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionType(partID);
}

const DirectionOrder FabiEngine3D::model_getRotationOrder(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getRotationOrder();
}

const fvec3 FabiEngine3D::model_getBasePosition(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBasePosition();
}

const fvec3 FabiEngine3D::model_getBaseRotation(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseRotation();
}

const fvec3 FabiEngine3D::model_getBaseRotationOrigin(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseRotationOrigin();
}

const fvec3 FabiEngine3D::model_getBaseSize(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseSize();
}

const fvec3 FabiEngine3D::model_getPartPosition(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartPosition(partID);
}

const fvec3 FabiEngine3D::model_getPartRotation(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartRotation(partID);
}

const fvec3 FabiEngine3D::model_getPartRotationOrigin(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartRotationOrigin(partID);
}

const fvec3 FabiEngine3D::model_getPartSize(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartSize(partID);
}

const fvec3 FabiEngine3D::model_getColor(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getColor(partID);
}

const fvec3 FabiEngine3D::model_getWireframeColor(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getWireframeColor(partID);
}

const fvec3 FabiEngine3D::model_getLevelOfDetailSize(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getLevelOfDetailSize();
}

const float FabiEngine3D::model_getLightness(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getLightness(partID);
}

const float FabiEngine3D::model_getReflectivity(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectivity(partID);
}

const float FabiEngine3D::model_getSpecularShininess(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularShininess(partID);
}

const float FabiEngine3D::model_getSpecularIntensity(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularIntensity(partID);
}

const float FabiEngine3D::model_getTransparency(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getTransparency(partID);
}

const float FabiEngine3D::model_getMinHeight(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getMinHeight();
}

const float FabiEngine3D::model_getMaxHeight(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::model_getLevelOfDetailDistance(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getLevelOfDetailDistance();
}

const float FabiEngine3D::model_getTextureRepeat(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getTextureRepeat(partID);
}

const float FabiEngine3D::model_getEmissionIntensity(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getEmissionIntensity(partID);
}

const string& FabiEngine3D::model_getMeshPath(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getMeshPath();
}

const string& FabiEngine3D::model_getDiffuseMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getDiffuseMapPath(partID);
}

const string& FabiEngine3D::model_getEmissionMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getEmissionMapPath(partID);
}

const string& FabiEngine3D::model_getSpecularMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularMapPath(partID);
}

const string& FabiEngine3D::model_getReflectionMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionMapPath(partID);
}

const string& FabiEngine3D::model_getNormalMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getNormalMapPath(partID);
}

const string& FabiEngine3D::model_getLevelOfDetailEntityID(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getLevelOfDetailEntityID();
}

const vector<fvec3>& FabiEngine3D::model_getInstancedOffsets(const string& ID) const
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	return entity->getRenderBuffer(entity->getPartIDs()[0])->getInstancedOffsets();
}

const vector<string> FabiEngine3D::model_getPartIDs(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartIDs();
}

const vector<string> FabiEngine3D::model_getAllIDs() const
{
	vector<string> result;

	for(const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through model entities
	{
		result.push_back(entity->getID());
	}

	return result;
}

const vector<string> FabiEngine3D::model_getGroupIDs(const string& ID) const
{
	vector<string> result;

	for(const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through model entities
	{
		if(entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			if(entity->getID().substr(0, ID.size()) == ID) // If entity matches ID
			{
				result.push_back(entity->getID());
			}
		}
	}

	return result;
}
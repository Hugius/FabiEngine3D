#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::modelEntity_isExisting(const string& ID) const
{
	return _core->_modelEntityManager.isExisting(ID);
}

const bool FabiEngine3D::modelEntity_isVisible(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::modelEntity_isInstanced(const string& ID) const
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	return entity->getRenderBuffer(entity->getPartIDs()[0])->isInstanced();
}

const bool FabiEngine3D::modelEntity_isMultiParted(const string& ID) const
{
	return (_core->_modelEntityManager.getEntity(ID)->getPartIDs().size() > 1);
}

const bool FabiEngine3D::modelEntity_isFaceCulled(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isFaceCulled();
}

const bool FabiEngine3D::modelEntity_isSpecular(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isSpecular(partID);
}

const bool FabiEngine3D::modelEntity_isShadowed(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isShadowed();
}

const bool FabiEngine3D::modelEntity_isReflected(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isReflected();
}

const bool FabiEngine3D::modelEntity_isStaticToCamera(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isCameraStatic();
}

const bool FabiEngine3D::modelEntity_isWireframed(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::modelEntity_isDepthMapIncluded(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isDepthMapIncluded();
}

const bool FabiEngine3D::modelEntity_hasPart(const string& ID, const string& partID) const
{
	for(const auto& existingPartID : modelEntity_getPartIDs(ID))
	{
		if(partID == existingPartID)
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::modelEntity_isBright(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isBright();
}

const bool FabiEngine3D::modelEntity_isReflective(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->isReflective(partID);
}

const bool FabiEngine3D::modelEntity_hasDiffuseMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasDiffuseMap(partID);
}

const bool FabiEngine3D::modelEntity_hasEmissionMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasEmissionMap(partID);
}

const bool FabiEngine3D::modelEntity_hasSpecularMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasSpecularMap(partID);
}

const bool FabiEngine3D::modelEntity_hasReflectionMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasReflectionMap(partID);
}

const bool FabiEngine3D::modelEntity_hasNormalMap(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->hasNormalMap(partID);
}

const ReflectionType FabiEngine3D::modelEntity_getReflectionType(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionType(partID);
}

const DirectionOrder FabiEngine3D::modelEntity_getRotationOrder(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getRotationOrder();
}

const Vec3 FabiEngine3D::modelEntity_getBasePosition(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBasePosition();
}

const Vec3 FabiEngine3D::modelEntity_getBaseRotation(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseRotation();
}

const Vec3 FabiEngine3D::modelEntity_getBaseRotationOrigin(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseRotationOrigin();
}

const Vec3 FabiEngine3D::modelEntity_getBaseSize(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseSize();
}

const Vec3 FabiEngine3D::modelEntity_getPartPosition(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartPosition(partID);
}

const Vec3 FabiEngine3D::modelEntity_getPartRotation(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartRotation(partID);
}

const Vec3 FabiEngine3D::modelEntity_getPartRotationOrigin(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartRotationOrigin(partID);
}

const Vec3 FabiEngine3D::modelEntity_getPartSize(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartSize(partID);
}

const Vec3 FabiEngine3D::modelEntity_getColor(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getColor(partID);
}

const Vec3 FabiEngine3D::modelEntity_getLevelOfDetailSize(const string& ID) const
{
	_core->_modelEntityManager.getEntity(ID)->getLevelOfDetailSize();
}

const float FabiEngine3D::modelEntity_getLightness(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getLightness(partID);
}

const float FabiEngine3D::modelEntity_getColorInversion(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getColorInversion(partID);
}

const float FabiEngine3D::modelEntity_getReflectivity(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectivity(partID);
}

const float FabiEngine3D::modelEntity_getSpecularShininess(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularShininess(partID);
}

const float FabiEngine3D::modelEntity_getSpecularIntensity(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularIntensity(partID);
}

const float FabiEngine3D::modelEntity_getTransparency(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getTransparency(partID);
}

const float FabiEngine3D::modelEntity_getMinHeight(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getMinHeight();
}

const float FabiEngine3D::modelEntity_getMaxHeight(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::modelEntity_getTextureRepeat(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getTextureRepeat(partID);
}

const float FabiEngine3D::modelEntity_getEmissionIntensity(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getEmissionIntensity(partID);
}

const string& FabiEngine3D::modelEntity_getMeshPath(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getMeshPath();
}

const string& FabiEngine3D::modelEntity_getDiffuseMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getDiffuseMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getEmissionMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getEmissionMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getSpecularMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getReflectionMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getNormalMapPath(const string& ID, const string& partID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getNormalMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getLevelOfDetailEntityID(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getLevelOfDetailEntityID();
}

const vector<Vec3>& FabiEngine3D::modelEntity_getInstancedOffsets(const string& ID) const
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	return entity->getRenderBuffer(entity->getPartIDs()[0])->getInstancedOffsets();
}

const vector<string> FabiEngine3D::modelEntity_getPartIDs(const string& ID) const
{
	return _core->_modelEntityManager.getEntity(ID)->getPartIDs();
}

const vector<string> FabiEngine3D::modelEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through model entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const vector<string> FabiEngine3D::modelEntity_getGroupIDs(const string& ID) const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through model entities
	{
		if(entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			if(entity->getID().substr(0, ID.size()) == ID) // If entity matches ID
			{
				IDs.push_back(entity->getID());
			}
		}
	}

	return IDs;
}
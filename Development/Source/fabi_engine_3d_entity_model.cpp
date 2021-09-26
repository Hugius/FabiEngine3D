#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::modelEntity_create(const string& ID, const string& meshPath)
{
	_core->_modelEntityManager.createEntity(ID, meshPath);
}

void FabiEngine3D::modelEntity_deleteAll()
{
	// For every model entity
	for (const auto& [keyID, entity] : _core->_modelEntityManager.getEntities())
	{
		modelEntity_delete(entity->getID());
	}
}

void FabiEngine3D::modelEntity_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for (const auto& aabbID : aabbEntity_getChildIDs(ID, AabbParentType::MODEL_ENTITY))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete model entity
	_core->_modelEntityManager.deleteEntity(ID);
}

void FabiEngine3D::modelEntity_deleteGroup(const string& ID)
{
	for (const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through MODEL entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
			if (subString == ID) 
			{
				modelEntity_delete(entity->getID());
			}
		}
	}
}

void FabiEngine3D::modelEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_modelEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::modelEntity_setDiffuseMap(const string& ID, const string& partID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(partID, _core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(partID, texturePath);
	}
}

void FabiEngine3D::modelEntity_setEmissionMap(const string& ID, const string& partID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setEmissionMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setEmissionMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setEmissionMap(partID, _core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setEmissionMapPath(partID, texturePath);
	}
}

void FabiEngine3D::modelEntity_setSpecularMap(const string& ID, const string& partID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setSpecularMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setSpecularMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setSpecularMap(partID, _core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setSpecularMapPath(partID, texturePath);
	}
}

void FabiEngine3D::modelEntity_setNormalMap(const string& ID, const string& partID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setNormalMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setNormalMap(partID, _core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(partID, texturePath);
	}
}

void FabiEngine3D::modelEntity_setReflectionMap(const string& ID, const string& partID, const string& texturePath)
{
	if (texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setReflectionMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setReflectionMap(partID, _core->_textureLoader.getTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(partID, texturePath);
	}
}

void FabiEngine3D::modelEntity_setLevelOfDetailEntity(const string& ID, const string& levelOfDetailID)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailEntityID(levelOfDetailID);
}

void FabiEngine3D::modelEntity_setFaceCulled(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setFaceCulled(enabled);
}

void FabiEngine3D::modelEntity_setReflectionType(const string& ID, const string& partID, ReflectionType type)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectionType(partID, type);
}

void FabiEngine3D::modelEntity_setSpecular(const string& ID, const string& partID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecular(partID, enabled);
}

void FabiEngine3D::modelEntity_setReflective(const string& ID, const string& partID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setReflective(partID, enabled);
}

const bool FabiEngine3D::modelEntity_isExisting(const string& ID)
{
	return _core->_modelEntityManager.isExisting(ID);
}

const bool FabiEngine3D::modelEntity_isVisible(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::modelEntity_isInstanced(const string& ID)
{
	auto entity = _core->_modelEntityManager.getEntity(ID);
	return entity->getRenderBuffer(entity->getPartIDs()[0])->isInstanced();
}

const bool FabiEngine3D::modelEntity_isMultiParted(const string& ID)
{
	return (_core->_modelEntityManager.getEntity(ID)->getPartIDs().size() > 1);
}

const bool FabiEngine3D::modelEntity_isFaceCulled(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isFaceCulled();
}

const bool FabiEngine3D::modelEntity_isSpecular(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->isSpecular(partID);
}

const bool FabiEngine3D::modelEntity_isShadowed(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isShadowed();
}

const bool FabiEngine3D::modelEntity_isReflected(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isReflected();
}

const bool FabiEngine3D::modelEntity_isStaticToCamera(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isCameraStatic();
}

const bool FabiEngine3D::modelEntity_isWireFramed(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isWireFramed();
}

const bool FabiEngine3D::modelEntity_isDepthMapIncluded(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isDepthMapIncluded();
}

const bool FabiEngine3D::modelEntity_hasPart(const string& ID, const string& partID)
{
	for (const auto& existingPartID : modelEntity_getPartIDs(ID))
	{
		if (partID == existingPartID)
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::modelEntity_isBright(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isBright();
}

const bool FabiEngine3D::modelEntity_isReflective(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->isReflective(partID);
}

const bool FabiEngine3D::modelEntity_hasDiffuseMap(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->hasDiffuseMap(partID);
}

const bool FabiEngine3D::modelEntity_hasEmissionMap(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->hasEmissionMap(partID);
}

const bool FabiEngine3D::modelEntity_hasSpecularMap(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->hasSpecularMap(partID);
}

const bool FabiEngine3D::modelEntity_hasReflectionMap(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->hasReflectionMap(partID);
}

const bool FabiEngine3D::modelEntity_hasNormalMap(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->hasNormalMap(partID);
}

const ReflectionType FabiEngine3D::modelEntity_getReflectionType(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionType(partID);
}

void FabiEngine3D::modelEntity_setBasePosition(const string& ID, Vec3 position)
{
	_core->_modelEntityManager.getEntity(ID)->setBasePosition(position);
}

void FabiEngine3D::modelEntity_setBaseRotation(const string& ID, Vec3 rotation)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseRotation(rotation);
}

void FabiEngine3D::modelEntity_setBaseRotationOrigin(const string& ID, Vec3 rotationOrigin)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseRotationOrigin(rotationOrigin);
}

void FabiEngine3D::modelEntity_setBaseSize(const string& ID, Vec3 size)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseSize(size);
}

void FabiEngine3D::modelEntity_setPartPosition(const string& ID, const string& partID, Vec3 position)
{
	_core->_modelEntityManager.getEntity(ID)->setPartPosition(partID, position);
}

void FabiEngine3D::modelEntity_setPartRotation(const string& ID, const string& partID, Vec3 rotation)
{
	_core->_modelEntityManager.getEntity(ID)->setPartRotation(partID, rotation);
}

void FabiEngine3D::modelEntity_setPartRotationOrigin(const string& ID, const string& partID, Vec3 rotationOrigin)
{
	_core->_modelEntityManager.getEntity(ID)->setPartRotationOrigin(partID, rotationOrigin);
}

void FabiEngine3D::modelEntity_setPartSize(const string& ID, const string& partID, Vec3 size)
{
	_core->_modelEntityManager.getEntity(ID)->setPartSize(partID, size);
}

void FabiEngine3D::modelEntity_moveBase(const string& ID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->moveBase(change);
}

void FabiEngine3D::modelEntity_rotateBase(const string& ID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->rotateBase(change);
}

void FabiEngine3D::modelEntity_scaleBase(const string& ID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->scaleBase(change);
}

void FabiEngine3D::modelEntity_movePart(const string& ID, const string& partID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->movePart(partID, change);
}

void FabiEngine3D::modelEntity_rotatePart(const string& ID, const string& partID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->rotatePart(partID, change);
}

void FabiEngine3D::modelEntity_scalePart(const string& ID, const string& partID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->scalePart(partID, change);
}

void FabiEngine3D::modelEntity_moveBaseTo(const string& ID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->moveBaseTo(target, speed);
}

void FabiEngine3D::modelEntity_rotateBaseTo(const string& ID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->rotateBaseTo(target, speed);
}

void FabiEngine3D::modelEntity_scaleBaseTo(const string& ID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->scaleBaseTo(target, speed);
}

const Vec3 FabiEngine3D::modelEntity_getBasePosition(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getBasePosition();
}

const Vec3 FabiEngine3D::modelEntity_getBaseRotation(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseRotation();
}

const Vec3 FabiEngine3D::modelEntity_getBaseRotationOrigin(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseRotationOrigin();
}

const Vec3 FabiEngine3D::modelEntity_getBaseSize(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getBaseSize();
}

const Vec3 FabiEngine3D::modelEntity_getPartPosition(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getPartPosition(partID);
}

const Vec3 FabiEngine3D::modelEntity_getPartRotation(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getPartRotation(partID);
}

const Vec3 FabiEngine3D::modelEntity_getPartRotationOrigin(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getPartRotationOrigin(partID);
}

const Vec3 FabiEngine3D::modelEntity_getPartSize(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getPartSize(partID);
}

const Vec3 FabiEngine3D::modelEntity_getColor(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getColor(partID);
}

const Vec3 FabiEngine3D::modelEntity_getLevelOfDetailSize(const string& ID)
{
	_core->_modelEntityManager.getEntity(ID)->getLevelOfDetailSize();
}

void FabiEngine3D::modelEntity_setSpecularShininess(const string& ID, const string& partID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularShininess(partID, intensity);
}

void FabiEngine3D::modelEntity_setSpecularIntensity(const string& ID, const string& partID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularIntensity(partID, intensity);
}

void FabiEngine3D::modelEntity_setReflectivity(const string& ID, const string& partID, float reflectivity)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectivity(partID,reflectivity);
}

void FabiEngine3D::modelEntity_setLightness(const string& ID, const string& partID, float lightness)
{
	_core->_modelEntityManager.getEntity(ID)->setLightness(partID, lightness);
}

void FabiEngine3D::modelEntity_setColorInversion(const string& ID, const string& partID, float colorInversion)
{
	_core->_modelEntityManager.getEntity(ID)->setColorInversion(partID, colorInversion);
}

void FabiEngine3D::modelEntity_setEmissionIntensity(const string& ID, const string& partID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setEmissionIntensity(partID, intensity);
}

void FabiEngine3D::modelEntity_setMinHeight(const string& ID, float height)
{
	_core->_modelEntityManager.getEntity(ID)->setMinHeight(height);
}

void FabiEngine3D::modelEntity_setMaxHeight(const string& ID, float height)
{
	_core->_modelEntityManager.getEntity(ID)->setMaxHeight(height);
}

void FabiEngine3D::modelEntity_movePartTo(const string& ID, const string& partID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->movePartTo(partID, target, speed);
}

void FabiEngine3D::modelEntity_rotatePartTo(const string& ID, const string& partID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->rotatePartTo(partID, target, speed);
}

void FabiEngine3D::modelEntity_scalePartTo(const string& ID, const string& partID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->scalePartTo(partID, target, speed);
}

void FabiEngine3D::modelEntity_setLevelOfDetailSize(const string& ID, Vec3 size)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailSize(size);
}

void FabiEngine3D::modelEntity_setUvRepeat(const string& ID, const string& partID, float repeat)
{
	_core->_modelEntityManager.getEntity(ID)->setUvRepeat(partID, repeat);
}

void FabiEngine3D::modelEntity_enableInstancing(const string& ID, vector<Vec3> offsets)
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	for (const auto& partID : entity->getPartIDs())
	{
		entity->getRenderBuffer(partID)->enableInstancing(offsets);
	}
}

void FabiEngine3D::modelEntity_disableInstancing(const string& ID)
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	for (const auto& partID : entity->getPartIDs())
	{
		entity->getRenderBuffer(partID)->disableInstancing();
	}
}

void FabiEngine3D::modelEntity_setBright(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setBright(enabled);
}

void FabiEngine3D::modelEntity_setStaticToCamera(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setCameraStatic(enabled);
}

void FabiEngine3D::modelEntity_setWireFramed(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setWireFramed(enabled);
}

const float FabiEngine3D::modelEntity_getLightness(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getLightness(partID);
}

const float FabiEngine3D::modelEntity_getColorInversion(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getColorInversion(partID);
}

const float FabiEngine3D::modelEntity_getReflectivity(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectivity(partID);
}

const float FabiEngine3D::modelEntity_getSpecularShininess(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularShininess(partID);
}

const float FabiEngine3D::modelEntity_getSpecularIntensity(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularIntensity(partID);
}

const float FabiEngine3D::modelEntity_getAlpha(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getAlpha(partID);
}

const float FabiEngine3D::modelEntity_getMinHeight(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getMinHeight();
}

const float FabiEngine3D::modelEntity_getMaxHeight(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getMaxHeight();
}

const float FabiEngine3D::modelEntity_getUvRepeat(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getUvRepeat(partID);
}

const float FabiEngine3D::modelEntity_getEmissionIntensity(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getEmissionIntensity(partID);
}

const string& FabiEngine3D::modelEntity_getMeshPath(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getMeshPath();
}

const string& FabiEngine3D::modelEntity_getDiffuseMapPath(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getDiffuseMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getEmissionMapPath(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getEmissionMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getSpecularMapPath(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getReflectionMapPath(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getNormalMapPath(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getNormalMapPath(partID);
}

const string& FabiEngine3D::modelEntity_getLevelOfDetailEntityID(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getLevelOfDetailEntityID();
}

const vector<Vec3> FabiEngine3D::modelEntity_getInstancedOffsets(const string& ID)
{
	// Temporary values
	auto entity = _core->_modelEntityManager.getEntity(ID);

	// Check if model is instanced
	if (modelEntity_isInstanced(ID))
	{
		return entity->getRenderBuffer(entity->getPartIDs()[0])->getInstancedOffsets();
	}
	else
	{
		return {};
	}
}

const vector<string> FabiEngine3D::modelEntity_getPartIDs(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getPartIDs();
}

void FabiEngine3D::modelEntity_setAlpha(const string& ID, const string& partID, float alpha)
{
	_core->_modelEntityManager.getEntity(ID)->setAlpha(partID, alpha);
}

void FabiEngine3D::modelEntity_setShadowed(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setShadowed(enabled);
}

void FabiEngine3D::modelEntity_setDepthMapIncluded(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setDepthMapIncluded(enabled);
}

void FabiEngine3D::modelEntity_setColor(const string& ID, const string& partID, Vec3 color)
{
	_core->_modelEntityManager.getEntity(ID)->setColor(partID, color);
}

void FabiEngine3D::modelEntity_setReflected(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setReflected(enabled);
}

const vector<string> FabiEngine3D::modelEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through MODEL entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const vector<string> FabiEngine3D::modelEntity_getGroupIDs(const string& ID)
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through MODEL entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			if (entity->getID().substr(0, ID.size()) == ID) // If entity matches ID
			{
				IDs.push_back(entity->getID());
			}
		}
	}

	return IDs;
}
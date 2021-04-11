#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::modelEntity_add
(
	const string& ID, const string& meshPath,
	Vec3 position, Vec3 rotation, Vec3 size, bool visible
)
{
	_core->_modelEntityManager.addModelEntity(ID, meshPath, position, rotation, size);
	_core->_modelEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::modelEntity_deleteAll()
{
	// For every model entity
	for (auto& [keyID, entity] : _core->_modelEntityManager.getEntities())
	{
		modelEntity_delete(entity->getID());
	}
}

void FabiEngine3D::modelEntity_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for (auto& aabbID : aabbEntity_getBoundIDs(ID, true, false))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete model entity
	_core->_modelEntityManager.deleteEntity(ID);
}

void FabiEngine3D::modelEntity_deleteGroup(const string& ID)
{
	for (auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Loop over GAME entities
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

void FabiEngine3D::modelEntity_hideAll()
{
	for (auto [keyID, entity] : _core->_modelEntityManager.getEntities())
	{
		modelEntity_hide(entity->getID());
	}
}

void FabiEngine3D::modelEntity_showAll()
{
	for (auto [keyID, entity] : _core->_modelEntityManager.getEntities())
	{
		modelEntity_show(entity->getID());
	}
}

void FabiEngine3D::modelEntity_hide(const string& ID)
{
	_core->_modelEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::modelEntity_show(const string& ID)
{
	_core->_modelEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::modelEntity_loadModel(const string& ID, const string& meshPath)
{
	_core->_modelEntityManager.loadMesh(ID, meshPath);
}

void FabiEngine3D::modelEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::modelEntity_setLightMap(const string& ID, const string& texturePath)
{
	_core->_modelEntityManager.getEntity(ID)->setLightMap(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_modelEntityManager.getEntity(ID)->setLightMapPath(texturePath);
}

void FabiEngine3D::modelEntity_setNormalMap(const string& ID, const string& texturePath)
{
	_core->_modelEntityManager.getEntity(ID)->setNormalMap(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
}

void FabiEngine3D::modelEntity_setReflectionMap(const string& ID, const string& texturePath)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectionMap(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(texturePath);
}

void FabiEngine3D::modelEntity_setLevelOfDetailEntity(const string& ID, const string& lodID)
{
	_core->_modelEntityManager.getEntity(ID)->setLodEntityID(lodID);
}

void FabiEngine3D::modelEntity_setTransparent(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setTransparent(enabled);
}

void FabiEngine3D::modelEntity_setFaceCulled(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setFaceCulled(enabled);
}

void FabiEngine3D::modelEntity_setLightMapped(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setLightMapped(enabled);
}

void FabiEngine3D::modelEntity_setNormalMapped(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setNormalMapped(enabled);

	if (enabled)
	{
		_core->_modelEntityManager.loadNormalMapping(ID);
	}
}

void FabiEngine3D::modelEntity_setSkyReflective(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setSkyReflective(enabled);
}

void FabiEngine3D::modelEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}

bool FabiEngine3D::modelEntity_isExisting(const string& ID)
{
	return _core->_modelEntityManager.isExisting(ID);
}

bool FabiEngine3D::modelEntity_isVisible(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::modelEntity_isInstanced(const string& ID)
{
	if (!_core->_modelEntityManager.getEntity(ID)->getRenderBuffers().empty())
	{
		return _core->_modelEntityManager.getEntity(ID)->getRenderBuffer(0)->isInstanced();
	}
	else
	{
		return false;
	}
}

bool FabiEngine3D::modelEntity_isMultiParted(const string& ID)
{
	return (_core->_modelEntityManager.getEntity(ID)->getPartIDs().size() > 1);
}

bool FabiEngine3D::modelEntity_isTransparent(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isTransparent();
}

bool FabiEngine3D::modelEntity_isFaceCulled(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isFaceCulled();
}

bool FabiEngine3D::modelEntity_isLightMapped(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isLightMapped();
}

bool FabiEngine3D::modelEntity_isNormalMapped(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isNormalMapped();
}

bool FabiEngine3D::modelEntity_isSkyReflective(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isSkyReflective();
}

bool FabiEngine3D::modelEntity_isSpecularLighted(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isSpecularLighted();
}

bool FabiEngine3D::modelEntity_isSceneReflective(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isSceneReflective();
}

bool FabiEngine3D::modelEntity_isShadowed(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isShadowed();
}

bool FabiEngine3D::modelEntity_isStaticToCamera(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isCameraStatic();
}

bool FabiEngine3D::modelEntity_isWireframed(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isWireframed();
}

bool FabiEngine3D::modelEntity_isDepthMapIncluded(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->isDepthMapIncluded();
}

bool FabiEngine3D::modelEntity_hasPart(const string& ID, const string& partID)
{
	for (auto& existingPartID : modelEntity_getPartIDs(ID))
	{
		if (partID == existingPartID)
		{
			return true;
		}
	}

	return false;
}

void FabiEngine3D::modelEntity_move(const string& ID, Vec3 factor, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->translate(factor, partID);
}

void FabiEngine3D::modelEntity_rotate(const string& ID, Vec3 factor, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->rotate(factor, partID);
}

void FabiEngine3D::modelEntity_scale(const string& ID, Vec3 factor, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->scale(factor, partID);
}

void FabiEngine3D::modelEntity_setPosition(const string& ID, Vec3 position, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->setTranslation(position, partID);
}

void FabiEngine3D::modelEntity_setRotation(const string& ID, Vec3 rotation, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->setRotation(rotation, partID);
}

void FabiEngine3D::modelEntity_setRotationOrigin(const string& ID, Vec3 rotationOrigin, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->setRotationOrigin(rotationOrigin, partID);
}

void FabiEngine3D::modelEntity_setSize(const string& ID, Vec3 size, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->setScaling(size, partID);
}

Vec3 FabiEngine3D::modelEntity_getPosition(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getTranslation(partID);
}

Vec3 FabiEngine3D::modelEntity_getRotation(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getRotation(partID);
}

Vec3 FabiEngine3D::modelEntity_getRotationOrigin(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getRotationOrigin(partID);
}

Vec3 FabiEngine3D::modelEntity_getSize(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getScaling(partID);
}

void FabiEngine3D::modelEntity_setSpecularFactor(const string& ID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularFactor(intensity);
}

void FabiEngine3D::modelEntity_setSpecularIntensity(const string& ID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularIntensity(intensity);
}

void FabiEngine3D::modelEntity_setLightness(const string& ID, float lightness)
{
	_core->_modelEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::modelEntity_setMinHeight(const string& ID, float height)
{
	_core->_modelEntityManager.getEntity(ID)->setMinHeight(height);
}

void FabiEngine3D::modelEntity_setMaxHeight(const string& ID, float height)
{
	_core->_modelEntityManager.getEntity(ID)->setMaxHeight(height);
}

void FabiEngine3D::modelEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_modelEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

void FabiEngine3D::modelEntity_setInstanced(const string& ID, bool instanced, vector<Vec3> offsets)
{
	if (instanced) // Add instancing
	{
		for (auto& buffer : _core->_modelEntityManager.getEntity(ID)->getRenderBuffers())
		{
			if (buffer->isInstanced())
			{
				buffer->removeInstancing();
			}

			buffer->addInstancing(offsets);
		}
	}
	else // Remove instancing
	{
		for (auto& buffer : _core->_modelEntityManager.getEntity(ID)->getRenderBuffers())
		{
			if (buffer->isInstanced())
			{
				buffer->removeInstancing();
			}
		}
	}
}

void FabiEngine3D::modelEntity_setStaticToCamera(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setCameraStatic(enabled);
}

void FabiEngine3D::modelEntity_setWireframed(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setWireframed(enabled);
}

float FabiEngine3D::modelEntity_getLightness(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getLightness();
}

float FabiEngine3D::modelEntity_getSpecularFactor(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularFactor();
}

float FabiEngine3D::modelEntity_getSpecularIntensity(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getSpecularIntensity();
}

float FabiEngine3D::modelEntity_getAlpha(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getAlpha();
}

float FabiEngine3D::modelEntity_getMinHeight(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getMinHeight();
}

float FabiEngine3D::modelEntity_getMaxHeight(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getMaxHeight();
}

float FabiEngine3D::modelEntity_getUvRepeat(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getUvRepeat();
}

Vec3 FabiEngine3D::modelEntity_getColor(const string& ID, const string& partID)
{
	return _core->_modelEntityManager.getEntity(ID)->getColor(partID);
}

string FabiEngine3D::modelEntity_getMeshPath(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getMeshPath();
}

string FabiEngine3D::modelEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getDiffuseMapPath();
}

string FabiEngine3D::modelEntity_getLightMapPath(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getLightMapPath();
}

string FabiEngine3D::modelEntity_getNormalMapPath(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getNormalMapPath();
}

string FabiEngine3D::modelEntity_getReflectionMapPath(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionMapPath();
}

string FabiEngine3D::modelEntity_getLevelOfDetailEntityID(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getLodEntityID();
}

const vector<Vec3> FabiEngine3D::modelEntity_getInstancedOffsets(const string& ID)
{
	if (modelEntity_isInstanced(ID))
	{
		return _core->_modelEntityManager.getEntity(ID)->getRenderBuffer(0)->getInstancedOffsets();
	}
	else
	{
		return {};
	}
}

const vector<string>& FabiEngine3D::modelEntity_getDiffuseMapPaths(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getDiffuseMapPaths();
}

const vector<string>& FabiEngine3D::modelEntity_getLightMapPaths(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getLightMapPaths();
}

const vector<string>& FabiEngine3D::modelEntity_getReflectionMapPaths(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getReflectionMapPaths();
}

const vector<string>& FabiEngine3D::modelEntity_getNormalMapPaths(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getNormalMapPaths();
}

const vector<string>& FabiEngine3D::modelEntity_getPartIDs(const string& ID)
{
	return _core->_modelEntityManager.getEntity(ID)->getPartIDs();
}

void FabiEngine3D::modelEntity_setAlpha(const string& ID, float alpha)
{
	_core->_modelEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::modelEntity_setShadowed(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setShadowed(enabled);
}

void FabiEngine3D::modelEntity_setDepthMapIncluded(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setDepthMapIncluded(enabled);
}

void FabiEngine3D::modelEntity_setColor(const string& ID, Vec3 color, const string& partID)
{
	_core->_modelEntityManager.getEntity(ID)->setColor(color, partID);
}

void FabiEngine3D::modelEntity_setSceneReflective(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setSceneReflective(enabled);
}

vector<string> FabiEngine3D::modelEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_modelEntityManager.getEntities()) // Loop over GAME entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

vector<string> FabiEngine3D::modelEntity_getGroupIDs(const string& ID)
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_modelEntityManager.getEntities()) // Loop over GAME entities
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
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gameEntity_add
(
	const string& ID, const string& objName,
	Vec3 position, Vec3 rotation, Vec3 size, bool visible
)
{
	_core->_gameEntityManager.addGameEntity(ID, objName, position, rotation, size);
	_core->_gameEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::gameEntity_deleteAll()
{
	// For every GAME entity
	for (auto& [keyID, entity] : _core->_gameEntityManager.getEntities())
	{
		gameEntity_delete(entity->getID());
	}
}

void FabiEngine3D::gameEntity_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for (auto& aabbID : aabbEntity_getBoundIDs(ID, true, false))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete GAME entity
	_core->_gameEntityManager.deleteEntity(ID);
}

void FabiEngine3D::gameEntity_deleteGroup(const string& ID)
{
	for (auto& [keyID, entity] : _core->_gameEntityManager.getEntities()) // Loop over GAME entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
			if (subString == ID) 
			{
				gameEntity_delete(entity->getID());
			}
		}
	}
}

void FabiEngine3D::gameEntity_hideAll()
{
	for (auto [keyID, entity] : _core->_gameEntityManager.getEntities())
	{
		gameEntity_hide(entity->getID());
	}
}

void FabiEngine3D::gameEntity_showAll()
{
	for (auto [keyID, entity] : _core->_gameEntityManager.getEntities())
	{
		gameEntity_show(entity->getID());
	}
}

void FabiEngine3D::gameEntity_hide(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::gameEntity_show(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::gameEntity_loadModel(const string& ID, const string& objPath)
{
	_core->_gameEntityManager.generateModel(ID, objPath);
}

void FabiEngine3D::gameEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	_core->_gameEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_gameEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::gameEntity_setLightMap(const string& ID, const string& texturePath)
{
	_core->_gameEntityManager.getEntity(ID)->setLightMap(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_gameEntityManager.getEntity(ID)->setLightMapPath(texturePath);
}

void FabiEngine3D::gameEntity_setNormalMap(const string& ID, const string& texturePath)
{
	_core->_gameEntityManager.getEntity(ID)->setNormalMap(_core->_texLoader.getTexture(texturePath, false, false));
	_core->_gameEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
}

void FabiEngine3D::gameEntity_setReflectionMap(const string& ID, const string& texturePath)
{
	_core->_gameEntityManager.getEntity(ID)->setReflectionMap(_core->_texLoader.getTexture(texturePath, true, true));
	_core->_gameEntityManager.getEntity(ID)->setReflectionMapPath(texturePath);
}

void FabiEngine3D::gameEntity_setLevelOfDetailEntity(const string& ID, const string& lodID)
{
	_core->_gameEntityManager.getEntity(ID)->setLodEntityID(lodID);
}

void FabiEngine3D::gameEntity_setTransparent(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setTransparent(enabled);
}

void FabiEngine3D::gameEntity_setFaceCulled(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setFaceCulled(enabled);
}

void FabiEngine3D::gameEntity_setLightMapped(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setLightMapped(enabled);
}

void FabiEngine3D::gameEntity_setNormalMapped(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setNormalMapped(enabled);

	if (enabled)
	{
		_core->_gameEntityManager.loadNormalMapping(ID);
	}
}

void FabiEngine3D::gameEntity_setSkyReflective(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setSkyReflective(enabled);
}

void FabiEngine3D::gameEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}

bool FabiEngine3D::gameEntity_isExisting(const string& ID)
{
	return _core->_gameEntityManager.isExisting(ID);
}

bool FabiEngine3D::gameEntity_isVisible(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::gameEntity_isInstanced(const string& ID)
{
	if (!_core->_gameEntityManager.getEntity(ID)->getOglBuffers().empty())
	{
		return _core->_gameEntityManager.getEntity(ID)->getOglBuffer(0)->isInstanced();
	}
	else
	{
		return false;
	}
}

bool FabiEngine3D::gameEntity_isMultiParted(const string& ID)
{
	return (_core->_gameEntityManager.getEntity(ID)->getPartNames().size() > 1);
}

bool FabiEngine3D::gameEntity_isTransparent(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isTransparent();
}

bool FabiEngine3D::gameEntity_isFaceCulled(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isFaceCulled();
}

bool FabiEngine3D::gameEntity_isLightMapped(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isLightMapped();
}

bool FabiEngine3D::gameEntity_isNormalMapped(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isNormalMapped();
}

bool FabiEngine3D::gameEntity_isSkyReflective(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isSkyReflective();
}

bool FabiEngine3D::gameEntity_isSpecularLighted(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isSpecularLighted();
}

bool FabiEngine3D::gameEntity_isSceneReflective(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isSceneReflective();
}

bool FabiEngine3D::gameEntity_isShadowed(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isShadowed();
}

bool FabiEngine3D::gameEntity_isStaticToCamera(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isCameraStatic();
}

bool FabiEngine3D::gameEntity_isWireframed(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isWireframed();
}

bool FabiEngine3D::gameEntity_isDepthMapIncluded(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isDepthMapIncluded();
}

bool FabiEngine3D::gameEntity_hasPart(const string& ID, const string& partName)
{
	for (auto& existingPartname : gameEntity_getPartNames(ID))
	{
		if (partName == existingPartname)
		{
			return true;
		}
	}

	return false;
}

void FabiEngine3D::gameEntity_move(const string& ID, Vec3 factor, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->translate(factor, partName);
}

void FabiEngine3D::gameEntity_rotate(const string& ID, Vec3 factor, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->rotate(factor, partName);
}

void FabiEngine3D::gameEntity_scale(const string& ID, Vec3 factor, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->scale(factor, partName);
}

void FabiEngine3D::gameEntity_setPosition(const string& ID, Vec3 position, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->setTranslation(position, partName);
}

void FabiEngine3D::gameEntity_setRotation(const string& ID, Vec3 rotation, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->setRotation(rotation, partName);
}

void FabiEngine3D::gameEntity_setRotationOrigin(const string& ID, Vec3 rotationOrigin, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->setRotationOrigin(rotationOrigin, partName);
}

void FabiEngine3D::gameEntity_setSize(const string& ID, Vec3 size, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->setScaling(size, partName);
}

Vec3 FabiEngine3D::gameEntity_getPosition(const string& ID, const string& partName)
{
	return _core->_gameEntityManager.getEntity(ID)->getTranslation(partName);
}

Vec3 FabiEngine3D::gameEntity_getRotation(const string& ID, const string& partName)
{
	return _core->_gameEntityManager.getEntity(ID)->getRotation(partName);
}

Vec3 FabiEngine3D::gameEntity_getRotationOrigin(const string& ID, const string& partName)
{
	return _core->_gameEntityManager.getEntity(ID)->getRotationOrigin(partName);
}

Vec3 FabiEngine3D::gameEntity_getSize(const string& ID, const string& partName)
{
	return _core->_gameEntityManager.getEntity(ID)->getScaling(partName);
}

void FabiEngine3D::gameEntity_setSpecularFactor(const string& ID, float intensity)
{
	_core->_gameEntityManager.getEntity(ID)->setSpecularFactor(intensity);
}

void FabiEngine3D::gameEntity_setSpecularIntensity(const string& ID, float intensity)
{
	_core->_gameEntityManager.getEntity(ID)->setSpecularIntensity(intensity);
}

void FabiEngine3D::gameEntity_setLightness(const string& ID, float lightness)
{
	_core->_gameEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::gameEntity_setMinHeight(const string& ID, float height)
{
	_core->_gameEntityManager.getEntity(ID)->setMinHeight(height);
}

void FabiEngine3D::gameEntity_setMaxHeight(const string& ID, float height)
{
	_core->_gameEntityManager.getEntity(ID)->setMaxHeight(height);
}

void FabiEngine3D::gameEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_gameEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

void FabiEngine3D::gameEntity_setLevelOfDetailDistance(float distance)
{
	_core->_gameEntityManager.setLodDistance(distance);
}

void FabiEngine3D::gameEntity_setInstanced(const string& ID, bool instanced, vector<Vec3> offsets)
{
	if (instanced) // Add instancing
	{
		for (auto& buffer : _core->_gameEntityManager.getEntity(ID)->getOglBuffers())
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
		for (auto& buffer : _core->_gameEntityManager.getEntity(ID)->getOglBuffers())
		{
			if (buffer->isInstanced())
			{
				buffer->removeInstancing();
			}
		}
	}
}

void FabiEngine3D::gameEntity_setStaticToCamera(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setCameraStatic(enabled);
}

void FabiEngine3D::gameEntity_setWireframed(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setWireframed(enabled);
}

float FabiEngine3D::gameEntity_getLightness(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getLightness();
}

float FabiEngine3D::gameEntity_getSpecularFactor(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getSpecularFactor();
}

float FabiEngine3D::gameEntity_getSpecularIntensity(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getSpecularIntensity();
}

float FabiEngine3D::gameEntity_getAlpha(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getAlpha();
}

float FabiEngine3D::gameEntity_getMinHeight(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getMinHeight();
}

float FabiEngine3D::gameEntity_getMaxHeight(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getMaxHeight();
}

float FabiEngine3D::gameEntity_getUvRepeat(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getUvRepeat();
}

float FabiEngine3D::gameEntity_getLevelOfDetailDistance()
{
	return _core->_gameEntityManager.getLodDistance();
}

Vec3 FabiEngine3D::gameEntity_getColor(const string& ID, const string& partName)
{
	return _core->_gameEntityManager.getEntity(ID)->getColor(partName);
}

string FabiEngine3D::gameEntity_getObjPath(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getObjPath();
}

string FabiEngine3D::gameEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getDiffuseMapPath();
}

string FabiEngine3D::gameEntity_getLightMapPath(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getLightMapPath();
}

string FabiEngine3D::gameEntity_getNormalMapPath(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getNormalMapPath();
}

string FabiEngine3D::gameEntity_getReflectionMapPath(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getReflectionMapPath();
}

string FabiEngine3D::gameEntity_getLevelOfDetailEntityID(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getLodEntityID();
}

const vector<Vec3> FabiEngine3D::gameEntity_getInstancedOffsets(const string& ID)
{
	if (gameEntity_isInstanced(ID))
	{
		return _core->_gameEntityManager.getEntity(ID)->getOglBuffer(0)->getInstancedOffsets();
	}
	else
	{
		return {};
	}
}

const vector<string>& FabiEngine3D::gameEntity_getDiffuseMapPaths(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getDiffuseMapPaths();
}

const vector<string>& FabiEngine3D::gameEntity_getLightMapPaths(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getLightMapPaths();
}

const vector<string>& FabiEngine3D::gameEntity_getReflectionMapPaths(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getReflectionMapPaths();
}

const vector<string>& FabiEngine3D::gameEntity_getNormalMapPaths(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getNormalMapPaths();
}

const vector<string>& FabiEngine3D::gameEntity_getPartNames(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getPartNames();
}

void FabiEngine3D::gameEntity_setAlpha(const string& ID, float alpha)
{
	_core->_gameEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::gameEntity_setShadowed(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setShadowed(enabled);
}

void FabiEngine3D::gameEntity_setDepthMapIncluded(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setDepthMapIncluded(enabled);
}

void FabiEngine3D::gameEntity_setColor(const string& ID, Vec3 color, const string& partName)
{
	_core->_gameEntityManager.getEntity(ID)->setColor(color, partName);
}

void FabiEngine3D::gameEntity_setSceneReflective(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setSceneReflective(enabled);
}

vector<string> FabiEngine3D::gameEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_gameEntityManager.getEntities()) // Loop over GAME entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

vector<string> FabiEngine3D::gameEntity_getGroupIDs(const string& ID)
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_gameEntityManager.getEntities()) // Loop over GAME entities
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
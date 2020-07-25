#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gameEntity_deleteAll()
{
	// For every GAME entity
	for (auto& entity : _core->_gameEntityManager.getEntities())
	{
		// Check if AABB entity is bound
		if (_core->_aabbEntityManager.isExisting(entity->getID()))
		{
			// If the case, delete it too
			_core->_aabbEntityManager.deleteEntity(entity->getID(), EntityType::AABB);
		}

		// Delete GAME entity
		gameEntity_delete(entity->getID());
	}
}

void FabiEngine3D::gameEntity_add
(
	const string& ID, const string& objName,
	vec3 position, vec3 rotation, vec3 size, bool visible
)
{
	_core->_gameEntityManager.addGameEntity(ID, objName, position, rotation, size);
	_core->_gameEntityManager.getEntity(ID)->setEnabled(visible);
}

void FabiEngine3D::gameEntity_delete(const string& ID)
{
	// Check if AABB entity is bound
	if (_core->_aabbEntityManager.isExisting(ID))
	{
		// If the case, delete it too
		_core->_aabbEntityManager.deleteEntity(ID, EntityType::AABB);
	}

	// Delete GAME entity
	_core->_gameEntityManager.deleteEntity(ID, EntityType::GAME);
}

void FabiEngine3D::gameEntity_deleteGroup(const string& ID)
{
	for (auto entity : _core->_gameEntityManager.getEntities()) // Loop over game entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				// Delete possible AABB
				if (aabbEntity_isExisting(entity->getID()))
				{
					aabbEntity_delete(entity->getID());
				}

				// Delete game entity
				_core->_gameEntityManager.deleteEntity(entity->getID(), EntityType::GAME);
			}
		}
	}
}

void FabiEngine3D::gameEntity_hideAll()
{
	for (auto entity : _core->_gameEntityManager.getEntities())
	{
		entity->setEnabled(false);

		// Hide possible AABB
		if (aabbEntity_isExisting(entity->getID()))
		{
			aabbEntity_hide(entity->getID());
		}
	}
}

void FabiEngine3D::gameEntity_showAll()
{
	for (auto entity : _core->_gameEntityManager.getEntities())
	{
		entity->setEnabled(true);

		// Show possible AABB
		if (aabbEntity_isExisting(entity->getID()))
		{
			aabbEntity_show(entity->getID());
		}
	}
}

void FabiEngine3D::gameEntity_hide(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setEnabled(false);

	// Hide possible AABB
	if (aabbEntity_isExisting(ID))
	{
		aabbEntity_hide(ID);
	}
}

void FabiEngine3D::gameEntity_show(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setEnabled(true);

	// Show possible AABB
	if (aabbEntity_isExisting(ID))
	{
		aabbEntity_show(ID);
	}
}

void FabiEngine3D::gameEntity_setDiffuseMap(const string& ID, const string& fileName)
{
	_core->_gameEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(fileName, true, true));
	_core->_gameEntityManager.getEntity(ID)->setDiffuseMapPath(fileName);
}

void FabiEngine3D::gameEntity_setLightMap(const string& ID, const string& fileName)
{
	_core->_gameEntityManager.getEntity(ID)->setLightMap(_core->_texLoader.getTexture(fileName, true, true));
	_core->_gameEntityManager.getEntity(ID)->setLightMapPath(fileName);
}

void FabiEngine3D::gameEntity_setReflectionMap(const string& ID, const string& fileName)
{
	_core->_gameEntityManager.getEntity(ID)->setReflectionMap(_core->_texLoader.getTexture(fileName, true, true));
	_core->_gameEntityManager.getEntity(ID)->setReflectionMapPath(fileName);
}

void FabiEngine3D::gameEntity_setTransparent(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setTransparent(enabled);
}

void FabiEngine3D::gameEntity_setFaceCulled(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setFaceCulled(enabled);
}

void FabiEngine3D::gameEntity_setLightmapped(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setLightMapped(enabled);
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
	return _core->_gameEntityManager.getEntity(ID)->isEnabled();
}

bool FabiEngine3D::gameEntity_isMultiTextured(const string& ID)
{
	return (_core->_gameEntityManager.getEntity(ID)->getOglBuffers().size() > 1);
}

bool FabiEngine3D::gameEntity_isTransparent(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isTransparent();
}

bool FabiEngine3D::gameEntity_isFaceCulled(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isFaceCulled();
}

bool FabiEngine3D::gameEntity_isLightmapped(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->isLightMapped();
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

void FabiEngine3D::gameEntity_move(const string& ID, vec3 factor)
{
	_core->_gameEntityManager.getEntity(ID)->translate(factor);

	// Also update potential bound AABB entities
	if (_core->_aabbEntityManager.isExisting(ID))
	{
		_core->_aabbEntityManager.getEntity(ID)->translate(factor);
	}
}

void FabiEngine3D::gameEntity_rotate(const string& ID, vec3 factor)
{
	_core->_gameEntityManager.getEntity(ID)->rotate(factor);
}

void FabiEngine3D::gameEntity_scale(const string& ID, vec3 factor)
{
	_core->_gameEntityManager.getEntity(ID)->scale(factor);
}

void FabiEngine3D::gameEntity_setPosition(const string& ID, vec3 position)
{
	_core->_gameEntityManager.getEntity(ID)->setTranslation(position);

	// Also update potential bound AABB entities
	if (_core->_aabbEntityManager.isExisting(ID))
	{
		_core->_aabbEntityManager.getEntity(ID)->setTranslation(position);
	}
}

void FabiEngine3D::gameEntity_setRotation(const string& ID, vec3 rotation)
{
	_core->_gameEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::gameEntity_setSize(const string& ID, vec3 size)
{
	_core->_gameEntityManager.getEntity(ID)->setScaling(size);
}

vec3 FabiEngine3D::gameEntity_getPosition(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getTranslation();
}

vec3 FabiEngine3D::gameEntity_getRotation(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getRotation();
}

vec3 FabiEngine3D::gameEntity_getSize(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getScaling();
}

void FabiEngine3D::gameEntity_enable(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::gameEntity_disable(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::gameEntity_setSpecularFactor(const string& ID, float intensity)
{
	_core->_gameEntityManager.getEntity(ID)->setSpecularFactor(intensity);
}

void FabiEngine3D::gameEntity_setLightness(const string& ID, float lightness)
{
	_core->_gameEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::gameEntity_setMaxY(const string& ID, float y)
{
	_core->_gameEntityManager.getEntity(ID)->setMaxY(y);
}

void FabiEngine3D::gameEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_gameEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

void FabiEngine3D::gameEntity_setStaticToCamera(const string& ID, bool staticToCamera)
{
	_core->_gameEntityManager.getEntity(ID)->setCameraStatic(staticToCamera);
}

float FabiEngine3D::gameEntity_getLightness(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getLightness();
}

float FabiEngine3D::gameEntity_getSpecularFactor(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getSpecularFactor();
}

float FabiEngine3D::gameEntity_getAlpha(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getAlpha();
}

float FabiEngine3D::gameEntity_getMaxY(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getMaxY();
}

float FabiEngine3D::gameEntity_getUvRepeat(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getUvRepeat();
}

vec3 FabiEngine3D::gameEntity_getColor(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getColor();
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

string FabiEngine3D::gameEntity_getReflectionMapPath(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getReflectionMapPath();
}

void FabiEngine3D::gameEntity_setAlpha(const string& ID, float alpha)
{
	_core->_gameEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::gameEntity_setShadowed(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setShadowed(enabled);
}

void FabiEngine3D::gameEntity_setColor(const string& ID, vec3 color)
{
	_core->_gameEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::gameEntity_setSceneReflective(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setSceneReflective(enabled);
}

vector<string> FabiEngine3D::gameEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto entity : _core->_gameEntityManager.getEntities()) // Loop over game entities
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

vector<string> FabiEngine3D::gameEntity_getGroupIDs(const string& ID)
{
	vector<string> IDs;

	for (auto entity : _core->_gameEntityManager.getEntities()) // Loop over game entities
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
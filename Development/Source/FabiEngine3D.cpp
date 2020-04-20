#include <algorithm>
#include <limits>
#include <chrono>

#include "FabiEngine3D.hpp"
#include "CoreEngine.hpp"
#include "Configuration.hpp"
#include "ShaderBus.hpp"
#include "InputHandler.hpp"
#include "Tools.hpp"

FabiEngine3D::FabiEngine3D()
{
	_core = new CoreEngine(*this);
}

FabiEngine3D::~FabiEngine3D()
{
	delete _core;
}

/* --------------------------------------------- Game interface --------------------------------------------- */

void FabiEngine3D::engine_start()
{
	_core->_start();
}

void FabiEngine3D::engine_stop()
{
	_core->_stop();
}

/* --------------------------------------------- Camera interface --------------------------------------------- */

void FabiEngine3D::camera_load(float fov, float nearZ, float farZ, vec3 startPos, float yaw, float pitch)
{
	_core->_cameraManager.setFOV(fov);
	_core->_cameraManager.setNearZ(nearZ);
	_core->_cameraManager.setFarZ(farZ);
	_core->_cameraManager.setPosition(startPos);
	_core->_cameraManager.setYaw(yaw);
	_core->_cameraManager.setPitch(pitch);
}

void FabiEngine3D::camera_enableLookat(vec3 position)
{
	_core->_cameraManager.enableLookat(position);
}

void FabiEngine3D::camera_enableFirstPersonView(float mouseSensitivity)
{
	_core->_cameraManager.enableFirstPersonView();
	_core->_cameraManager.setMouseSensitivity(mouseSensitivity);
}

void FabiEngine3D::camera_disableFirstPersonView()
{
	_core->_cameraManager.disableFirstPersonView();
}

void FabiEngine3D::camera_enableFreeMovement()
{
	_core->_cameraManager.enableFreeMovement();
}

void FabiEngine3D::camera_disableFreeMovement()
{
	_core->_cameraManager.disableFreeMovement();
}

void FabiEngine3D::camera_translateFollowX(float speed)
{
	_core->_cameraManager.translateFollowX(speed, _core->_timer.getDeltaTime());
}

void FabiEngine3D::camera_translateFollowZY(float speed)
{
	_core->_cameraManager.translateFollowZY(speed, _core->_timer.getDeltaTime());
}

void FabiEngine3D::camera_translateFollowZ(float speed)
{
	_core->_cameraManager.translateFollowZ(speed, _core->_timer.getDeltaTime());
}

void FabiEngine3D::camera_translate(vec3 translation)
{
	_core->_cameraManager.translate(translation, _core->_timer.getDeltaTime());
}

void FabiEngine3D::camera_setPosition(vec3 pos)
{
	_core->_cameraManager.setPosition(pos);
}

void FabiEngine3D::camera_invertYaw()
{
	_core->_cameraManager.invertYaw();
}

void FabiEngine3D::camera_invertPitch()
{
	_core->_cameraManager.invertPitch();
}

void FabiEngine3D::camera_setFOV(float fov)
{
	_core->_cameraManager.setFOV(fov);
}

void FabiEngine3D::camera_setSensitivity(float speed)
{
	_core->_cameraManager.setMouseSensitivity(speed);
}

void FabiEngine3D::camera_setYaw(float val)
{
	_core->_cameraManager.setYaw(val);
}

void FabiEngine3D::camera_setPitch(float val)
{
	_core->_cameraManager.setPitch(val);
}

float FabiEngine3D::camera_getYaw()
{
	return _core->_cameraManager.getYaw();
}

float FabiEngine3D::camera_getPitch()
{
	return _core->_cameraManager.getPitch();
}

float FabiEngine3D::camera_getMouseOffset()
{
	return _core->_cameraManager.getMouseOffset();
}

float FabiEngine3D::camera_getFOV()
{
	return _core->_cameraManager.getFOV();
}

vec3 FabiEngine3D::camera_getPos()
{
	return _core->_cameraManager.getPosition();
}

vec3 FabiEngine3D::camera_getFront()
{
	return _core->_cameraManager.getFront();
}

/* --------------------------------------------- Sky interface --------------------------------------------- */

void FabiEngine3D::skyEntity_add(const string& ID, float rotationSpeed)
{
	_core->_skyEntityManager.addSkyEntity(ID, rotationSpeed, _core->_texLoader);
}

void FabiEngine3D::skyEntity_delete(const string& ID)
{
	_core->_skyEntityManager.deleteEntity(ID);
	_core->_skyEntityManager.selectSky("");
}

void FabiEngine3D::skyEntity_setAmbientLighting(const string& ID, float nightAmbStrength, float dayAmbStrength)
{
	_core->_skyEntityManager.getEntity(ID)->setNightAmbStrength(nightAmbStrength);
	_core->_skyEntityManager.getEntity(ID)->setDayAmbStrength(dayAmbStrength);
}

void FabiEngine3D::skyEntity_setDirectionalLighting(const string& ID, float nightDirStrength, float dayDirStrength)
{
	_core->_skyEntityManager.getEntity(ID)->setNightDirStrength(nightDirStrength);
	_core->_skyEntityManager.getEntity(ID)->setDayDirStrength(dayDirStrength);
}

void FabiEngine3D::skyEntity_select(const string& ID)
{
	_core->_skyEntityManager.selectSky(ID);
}

void FabiEngine3D::skyEntity_setDayTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setDayTime();
	_core->_skyEntityManager.getEntity(ID)->setMixValue(0.0f);

	if (_core->_skyEntityManager.getEntity(ID)->getAmbStrength() != -1.0f)
	{
		_core->_shaderBus.setAmbLightStrength(_core->_skyEntityManager.getEntity(ID)->getAmbStrength());
	}

	if (_core->_skyEntityManager.getEntity(ID)->getDirStrength() != -1.0f)
	{
		_core->_shaderBus.setDirLightStrength(_core->_skyEntityManager.getEntity(ID)->getDirStrength());
	}
}

void FabiEngine3D::skyEntity_setNightTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setNightTime();
	_core->_skyEntityManager.getEntity(ID)->setMixValue(1.0f);

	if (_core->_skyEntityManager.getEntity(ID)->getAmbStrength() != -1.0f)
	{
		_core->_shaderBus.setAmbLightStrength(_core->_skyEntityManager.getEntity(ID)->getAmbStrength());
	}

	if (_core->_skyEntityManager.getEntity(ID)->getDirStrength() != -1.0f)
	{
		_core->_shaderBus.setDirLightStrength(_core->_skyEntityManager.getEntity(ID)->getDirStrength());
	}
}

void FabiEngine3D::skyEntity_fadeDayTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setDayTime();
}

void FabiEngine3D::skyEntity_fadeNightTime(const string& ID)
{
	_core->_skyEntityManager.getEntity(ID)->setNightTime();
}

bool FabiEngine3D::skyEntity_isDayTime(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->isDayTime();
}

bool FabiEngine3D::skyEntity_isNightTime(const string& ID)
{
	return _core->_skyEntityManager.getEntity(ID)->isNightTime();
}

string FabiEngine3D::skyEntity_getSelectedID()
{
	if (_core->_skyEntityManager.getSelectedSky() != nullptr)
	{
		return _core->_skyEntityManager.getSelectedSky()->getID();
	}
	else
	{
		return "";
	}
}

bool FabiEngine3D::skyEntity_isExisting(const string& ID)
{
	return _core->_skyEntityManager.isExisting(ID);
}

/* --------------------------------------------- Terrain interface --------------------------------------------- */

void FabiEngine3D::terrainEntity_add(const string& ID, const string& heightmapName, const string& textureName, vec3 pos, float size, float maxHeight, float uvRepeat)
{
	_core->_terrainEntityManager.addTerrainEntity(ID, heightmapName, textureName, pos, size, maxHeight, uvRepeat);
}

void FabiEngine3D::terrainEntity_delete(const string& ID)
{
	_core->_terrainEntityManager.deleteEntity(ID);
	_core->_terrainEntityManager.selectTerrain("");
}

bool FabiEngine3D::terrainEntity_isExisting(const string& ID)
{
	return _core->_terrainEntityManager.isExisting(ID);
}

bool FabiEngine3D::terrainEntity_isInside(float x, float z)
{
	return _core->_terrainEntityManager.isInside(x, z);
}

vec3 FabiEngine3D::terrainEntity_getMousePoint()
{
return _core->_mousePicker.getTerrainPoint();
}

float FabiEngine3D::terrainEntity_getPixelHeight(float x, float z)
{
	return _core->_terrainEntityManager.getPixelHeight(x, z);
}

string FabiEngine3D::terrainEntity_getSelectedID()
{
	if (_core->_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		return _core->_terrainEntityManager.getSelectedTerrain()->getID();
	}
	else
	{
		return "";
	}
}

void FabiEngine3D::terrainEntity_select(const string& ID)
{
	_core->_terrainEntityManager.selectTerrain(ID);
}

void FabiEngine3D::terrainEntity_addBlending
(
	const string& ID, const string blendmapName, const string blendmapNameR,
	const string blendmapNameG, const string blendmapNameB,
	float blendRepeatR, float blendRepeatG, float blendRepeatB
)
{
	_core->_terrainEntityManager.addBlendingToTerrain(ID, blendmapName, blendmapNameR, blendmapNameG, blendmapNameB, blendRepeatR, blendRepeatG, blendRepeatB);
}

void FabiEngine3D::waterEntity_add(const string& ID, const string& assetName, vec3 pos, float size, float tileRepeat, float speed, bool waving, bool rippling, vec3 color, float shininess)
{
	_core->_waterEntityManager.addWaterEntity(ID, assetName, pos, size, tileRepeat, speed, waving, rippling, color, shininess);
}

void FabiEngine3D::waterEntity_delete(const string& ID)
{
	_core->_waterEntityManager.deleteEntity(ID);
	_core->_waterEntityManager.selectWater("");
}

bool FabiEngine3D::waterEntity_isExisting(const string& ID)
{
	return _core->_waterEntityManager.isExisting(ID);
}

void FabiEngine3D::waterEntity_select(const string& ID)
{
	_core->_waterEntityManager.selectWater(ID);
}

void FabiEngine3D::waterEntity_enableWaving(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setWaving(true);
}

void FabiEngine3D::waterEntity_disableWaving(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setWaving(false);
}

void FabiEngine3D::waterEntity_enableRippling(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setRippling(true);
}

void FabiEngine3D::waterEntity_disableRippling(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setRippling(false);
}

void FabiEngine3D::waterEntity_setColor(const string& ID, vec3 color)
{
	_core->_waterEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::waterEntity_setShininess(const string& ID, float shininess)
{
	_core->_waterEntityManager.getEntity(ID)->setShininess(shininess);
}

void FabiEngine3D::waterEntity_setTransparency(const string& ID, float transparency)
{
	transparency = std::clamp(transparency, 0.0f, 1.0f);
	_core->_waterEntityManager.getEntity(ID)->setTransparency(transparency * 10.0f);
}

string FabiEngine3D::waterEntity_getSelectedID()
{
	if (_core->_waterEntityManager.getSelectedWater() != nullptr)
	{
		return _core->_waterEntityManager.getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

/* --------------------------------------------- Game entity interface --------------------------------------------- */

void FabiEngine3D::gameEntity_deleteAll()
{
	// For every GAME entity
	for (auto& entity : _core->_gameEntityManager.getEntities())
	{
		// Check if AABB entity is bound
		if (_core->_aabbEntityManager.isExisting(entity->getID()))
		{
			// If the case, delete it too
			_core->_aabbEntityManager.deleteEntity(entity->getID());
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

void FabiEngine3D::gameEntity_addInstanced
(
	const string& ID, const string& modelName,
	const vector<vec3>& positions, vec3 rotation, vec3 size,
	bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
)
{
	_core->_gameEntityManager.addGameEntity(ID, modelName, positions, rotation, size, transparent, faceCulled, lightMapped, reflective, specular);
}

void FabiEngine3D::gameEntity_delete(const string& ID)
{
	// Check if AABB entity is bound
	if (_core->_aabbEntityManager.isExisting(ID))
	{
		// If the case, delete it too
		_core->_aabbEntityManager.deleteEntity(ID);
	}

	// Delete GAME entity
	_core->_gameEntityManager.deleteEntity(ID);
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
				_core->_gameEntityManager.deleteEntity(entity->getID());
			}
		}
	}
}

void FabiEngine3D::gameEntity_hideAll()
{
	for (auto entity : _core->_gameEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void FabiEngine3D::gameEntity_showAll()
{
	for (auto entity : _core->_gameEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void FabiEngine3D::gameEntity_hide(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::gameEntity_show(const string& ID)
{
	_core->_gameEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::gameEntity_setDiffuseMap(const string& ID, const string& fileName)
{
	_core->_gameEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(fileName, true, true));
}

void FabiEngine3D::gameEntity_setLightMap(const string& ID, const string& fileName)
{
	_core->_gameEntityManager.getEntity(ID)->setLightMap(_core->_texLoader.getTexture(fileName, true, true));
}

void FabiEngine3D::gameEntity_setReflectionMap(const string& ID, const string& fileName)
{
	_core->_gameEntityManager.getEntity(ID)->setReflectionMap(_core->_texLoader.getTexture(fileName, true, true));
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

void FabiEngine3D::gameEntity_move(const string& ID, vec3 factor)
{
	_core->_gameEntityManager.getEntity(ID)->translate(factor, _core->_timer.getDeltaTime());

	// Also update potential bound AABB entities
	if (_core->_aabbEntityManager.isExisting(ID))
	{
		_core->_aabbEntityManager.getEntity(ID)->translate(factor, _core->_timer.getDeltaTime());
	}
}

void FabiEngine3D::gameEntity_rotate(const string& ID, vec3 factor)
{
	_core->_gameEntityManager.getEntity(ID)->rotate(factor, _core->_timer.getDeltaTime());
}

void FabiEngine3D::gameEntity_scale(const string& ID, vec3 factor)
{
	_core->_gameEntityManager.getEntity(ID)->scale(factor, _core->_timer.getDeltaTime());
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

void FabiEngine3D::gameEntity_setMaxY(const string& ID, float y)
{
	_core->_gameEntityManager.getEntity(ID)->setMaxY(y);
}

void FabiEngine3D::gameEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_gameEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

float FabiEngine3D::gameEntity_getMaxY(const string& ID)
{
	return _core->_gameEntityManager.getEntity(ID)->getMaxY();
}

void FabiEngine3D::gameEntity_setAlpha(const string& ID, float alpha)
{
	_core->_gameEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::gameEntity_setShadowed(const string& ID, bool shadowed)
{
	_core->_gameEntityManager.getEntity(ID)->setShadowed(shadowed);
}

void FabiEngine3D::gameEntity_setColor(const string& ID, vec3 color)
{
	_core->_gameEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::gameEntity_setSceneReflective(const string& ID, bool enabled)
{
	_core->_gameEntityManager.getEntity(ID)->setSceneReflective(enabled);
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

/* --------------------------------------------- Billboard interface --------------------------------------------- */

void FabiEngine3D::billBoardEntity_add(const string& ID, const string& text, const string& fontPath, vec3 color, vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, text, fontPath, color, T, R, S, facingCameraX, facingCameraY);
	_core->_billboardEntityManager.getEntity(ID)->setEnabled(visible);
}

void FabiEngine3D::billBoardEntity_add(const string& ID, const string& textureName, vec3 T, vec3 R, vec3 S, bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering, bool visible)
{
	_core->_billboardEntityManager.addBillboardEntity(ID, textureName, T, R, S, transparent, facingCameraX, facingCameraY, textureFiltering);
	_core->_billboardEntityManager.getEntity(ID)->setEnabled(visible);
}

void FabiEngine3D::billboardEntity_deleteAll()
{
	_core->_billboardEntityManager.deleteEntities();
}

void FabiEngine3D::billboardEntity_delete(const string& ID)
{
	_core->_billboardEntityManager.deleteEntity(ID);
}

void FabiEngine3D::billboardEntity_hideAll()
{
	for (auto& entity : _core->_billboardEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void FabiEngine3D::billboardEntity_showAll()
{
	for (auto& entity : _core->_billboardEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void FabiEngine3D::billboardEntity_hide(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::billboardEntity_show(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->setEnabled(true);
}

bool FabiEngine3D::billboardEntity_isExisting(const string& ID)
{
	return _core->_billboardEntityManager.isExisting(ID);
}

void FabiEngine3D::billboardEntity_move(const string& ID, vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->translate(factor, _core->_timer.getDeltaTime());
}

void FabiEngine3D::billboardEntity_rotate(const string& ID, vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->rotate(factor, _core->_timer.getDeltaTime());
}

void FabiEngine3D::billboardEntity_scale(const string& ID, vec3 factor)
{
	_core->_billboardEntityManager.getEntity(ID)->scale(factor, _core->_timer.getDeltaTime());
}

void FabiEngine3D::billboardEntity_setPosition(const string& ID, vec3 position)
{
	_core->_billboardEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::billboardEntity_setRotation(const string& ID, vec3 rotation)
{
	_core->_billboardEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::billboardEntity_setSize(const string& ID, vec3 size)
{
	_core->_billboardEntityManager.getEntity(ID)->setScaling(size);
}

vec3 FabiEngine3D::billboardEntity_getPosition(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getTranslation();
}

vec3 FabiEngine3D::billboardEntity_getRotation(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getRotation();
}

vec3 FabiEngine3D::billboardEntity_getSize(const string& ID)
{
	return _core->_billboardEntityManager.getEntity(ID)->getScaling();
}

void FabiEngine3D::billboardEntity_enable(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::billboardEntity_disable(const string& ID)
{
	_core->_billboardEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::billBoardEntity_playSpriteAnimation(const string& ID, int rows, int columns, float maxDelta, int repeats)
{
	_core->_billboardEntityManager.getEntity(ID)->setSpriteAnimation(rows, columns, maxDelta, repeats);
}

void FabiEngine3D::billBoardEntity_changeText(const string& ID, const string& text, vec3 color)
{
	string fontPath = _core->_billboardEntityManager.getEntity(ID)->getFontPath();

	_core->_billboardEntityManager.getEntity(ID)->setText(text);
	_core->_billboardEntityManager.getEntity(ID)->setColor(color);
	_core->_billboardEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getText(text, fontPath));
}

void FabiEngine3D::billboardEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_billboardEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

bool FabiEngine3D::billboardEntity_isFinished(const string& ID)
{
	int repeats = _core->_billboardEntityManager.getEntity(ID)->getAnimationRepeats();
	int maxRepeats = _core->_billboardEntityManager.getEntity(ID)->getMaxAnimationRepeats();
	return (repeats == maxRepeats);
}

/* --------------------------------------------- AABB entity interface --------------------------------------------- */

void FabiEngine3D::aabbEntity_deleteAll()
{
	_core->_aabbEntityManager.deleteEntities();
}

void FabiEngine3D::aabbEntity_add(const string& ID, vec3 T, vec3 S, bool responsive)
{
	_core->_aabbEntityManager.addAabbEntity(ID, T, vec3(0.0f), S, responsive);
}

void FabiEngine3D::aabbEntity_bindToGameEntity(const string& parentID, vec3 S, bool responsive)
{
	if (_core->_gameEntityManager.isExisting(parentID))
	{
		_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, vec3(0.0f), S, responsive);
		_core->_aabbEntityManager.getEntity(parentID)->setTranslation(_core->_gameEntityManager.getEntity(parentID)->getTranslation());
	}
	else
	{
		logger_throwError("Tried to bind AABB entity to non-existing GAME entity \"" + parentID + "\"!");
	}
}

void FabiEngine3D::aabbEntity_bindToGameEntityGroup(const string& parentID, vec3 S, bool responsive)
{
	bool found = false;

	for (auto entity : _core->_gameEntityManager.getEntities()) // Loop over game entities
	{
		if (entity->getID().size() >= parentID.size()) // Check if entity ID is at least the size of group ID
		{
			if (entity->getID().substr(0, parentID.size()) == parentID) // If entity matches ID
			{
				found = true;
				_core->_aabbEntityManager.bindAabbEntity(entity->getID(), entity->getID(), vec3(0.0f), S, responsive); // Add new box
			}
		}
	}

	if (!found)
	{
		logger_throwError("Tried to bind AABB entities to non-existing GAME entity group \"" + parentID + "\"!");
	}
}

void FabiEngine3D::aabbEntity_delete(const string& ID)
{
	_core->_aabbEntityManager.deleteEntity(ID);
}

void FabiEngine3D::aabbEntity_setResponsiveness(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setResponsiveness(responsive);
}

void FabiEngine3D::aabbEntity_setGroupResponsiveness(const string& ID, bool responsive)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				_core->_aabbEntityManager.getEntity(entity->getID())->setResponsiveness(responsive);
			}
		}
	}
}

void FabiEngine3D::aabbEntity_setPosition(const string& ID, vec3 position)
{
	_core->_aabbEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::aabbEntity_setSize(const string& ID, vec3 size)
{
	_core->_aabbEntityManager.getEntity(ID)->setScaling(size);
}

vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getTranslation();
}

vec3 FabiEngine3D::aabbEntity_getSize(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getScaling();
}

bool FabiEngine3D::aabbEntity_isExisting(const string& ID)
{
	return _core->_aabbEntityManager.isExisting(ID);
}

/* --------------------------------------------- Global collision interface --------------------------------------------- */

void FabiEngine3D::collision_enableCameraResponse()
{
	_core->_collisionResolver.enableAabbResponse();
}

void FabiEngine3D::collision_disableCameraResponse()
{
	_core->_collisionResolver.disableAabbResponse();
}

void FabiEngine3D::collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_core->_collisionResolver.enableTerrainResponse(cameraHeight, cameraSpeed);
}

void FabiEngine3D::collision_disableCameraTerrainResponse()
{
	_core->_collisionResolver.disableTerrainResponse();
}

void FabiEngine3D::collision_enableFrameRendering()
{
	_core->_shaderBus.setAabbFrameEnabled(true);
}

void FabiEngine3D::collision_disableFrameRendering()
{
	_core->_shaderBus.setAabbFrameEnabled(false);
}

bool FabiEngine3D::collision_checkAnyWithCamera()
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getCollisionDirection() != CollisionDir::NONE)
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::collision_checkEntityCamera(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection() != CollisionDir::NONE;
}

bool FabiEngine3D::collision_isCameraUnderGround()
{
	return _core->_collisionResolver.isCameraUnderGround();
}

bool FabiEngine3D::collision_isCameraAboveGround()
{
	return _core->_collisionResolver.isCameraAboveGround();
}

string FabiEngine3D::collision_checkEntityOthers(const string ID)
{
	for (auto other : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (other->getID() != ID && other->isResponsive()) // Don't check own entity & must be responsive
		{
			auto self = _core->_aabbEntityManager.getEntity(ID);
			vec3 selfPos = self->getTranslation();
			vec3 selfSize = self->getScaling();
			vec3 otherPos = other->getTranslation();
			vec3 otherSize = other->getScaling();

			// Check XYZ collision between 2 entities
			if 
			( 
				// Check both all X collision situations
				((selfPos.z > otherPos.z - otherSize.z && selfPos.z < otherPos.z + otherSize.z) || // Middle coordinate within
				(selfPos.z - selfSize.z > otherPos.z - otherSize.z && selfPos.z - selfSize.z < otherPos.z + otherSize.z) || // Lower corner within
				(selfPos.z + selfSize.z > otherPos.z - otherSize.z && selfPos.z + selfSize.z < otherPos.z + otherSize.z) || // Upper corner within 
				(selfPos.z - selfSize.z < otherPos.z - otherSize.z && selfPos.z + selfSize.z > otherPos.z + otherSize.z))   // AABB too big but overlapping 
				
				&&

				// Check both all Y collision situations
				((selfPos.y > otherPos.y - otherSize.y && selfPos.y < otherPos.y + otherSize.y) || // Middle coordinate within
				(selfPos.y - selfSize.y > otherPos.y - otherSize.y && selfPos.y - selfSize.y < otherPos.y + otherSize.y) || // Lower corner within
				(selfPos.y + selfSize.y > otherPos.y - otherSize.y && selfPos.y + selfSize.y < otherPos.y + otherSize.y) || // Upper corner within 
				(selfPos.y - selfSize.y < otherPos.y - otherSize.y && selfPos.y + selfSize.y > otherPos.y + otherSize.y))   // AABB too big but overlapping 

				&&

				// Check both all Z collision situations
				((selfPos.x > otherPos.x - otherSize.x && selfPos.x < otherPos.x + otherSize.x) || // Middle coordinate within
				(selfPos.x - selfSize.x > otherPos.x - otherSize.x && selfPos.x - selfSize.x < otherPos.x + otherSize.x) || // Lower corner within
				(selfPos.x + selfSize.x > otherPos.x - otherSize.x && selfPos.x + selfSize.x < otherPos.x + otherSize.x) || // Upper corner within 
				(selfPos.x - selfSize.x < otherPos.x - otherSize.x && selfPos.x + selfSize.x > otherPos.x + otherSize.x))   // AABB too big but overlapping 
			) 
			{
				return other->getID();
			}
		}
	}

	return "";
}

string FabiEngine3D::collision_checkEntityGroupCamera(const string& ID)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				auto direction = entity->getCollisionDirection(); // Calculate direction

				// True if collides
				if (direction != CollisionDir::NONE)
				{
					return entity->getID();
				}
			}
		}
	}

	// No collision
	return "";
}

bool FabiEngine3D::collision_checkCursorInEntity(const string& ID)
{
	auto entity = _core->_aabbEntityManager.getEntity(ID);
	vec3 lb, rt;
	lb.x = (entity->getTranslation().x - entity->getScaling().x);
	lb.y = (entity->getTranslation().y);
	lb.z = (entity->getTranslation().z + entity->getScaling().z);
	rt.x = (entity->getTranslation().x + entity->getScaling().x);
	rt.y = (entity->getTranslation().y + entity->getScaling().y);
	rt.z = (entity->getTranslation().z - entity->getScaling().z);

	return _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition()) != -1.0f;
}

string FabiEngine3D::collision_checkCursorInEntityGroup(const string& ID, const string exception)
{
	float closestDistance = (std::numeric_limits<float>::max)();
	string closestBox = "";

	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID && entity->getID() != exception) // If entity matches ID
			{
				// Calculate box left bottom (LB) and right top (RT)
				vec3 lb, rt;
				lb.x = (entity->getTranslation().x - entity->getScaling().x);
				lb.y = (entity->getTranslation().y);
				lb.z = (entity->getTranslation().z + entity->getScaling().z);
				rt.x = (entity->getTranslation().x + entity->getScaling().x);
				rt.y = (entity->getTranslation().y + entity->getScaling().y);
				rt.z = (entity->getTranslation().z - entity->getScaling().z);

				// Check intersection
				float distance = _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());

				// Check if closest to camera
				if (distance != -1.0f && distance < closestDistance)
				{
					closestDistance = distance;
					closestBox = entity->getID();
				}
			}
		}
	}

	// No intersection
	return closestBox;
}

ivec3 FabiEngine3D::collision_checkEntityCameraDir(const string& ID)
{
	// Calculate direction
	auto state = _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection();

	// Return collision
	return ivec3(state == CollisionDir::X, state == CollisionDir::Y, state == CollisionDir::Z);
}

ivec3 FabiEngine3D::collision_checkEntityGroupCameraDir(const string& ID)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				auto direction = entity->getCollisionDirection(); // Calculate direction

				// Return direction if collides
				if (direction != CollisionDir::NONE)
				{
					return ivec3(direction == CollisionDir::X, direction == CollisionDir::Y, direction == CollisionDir::Z);
				}
			}
		}
	}

	// No collision
	return ivec3(0);
}

/* --------------------------------------------- Light entity interface --------------------------------------------- */

void FabiEngine3D::lightEntity_deleteAll()
{
	_core->_lightEntityManager.deleteEntities();
}

void FabiEngine3D::lightEntity_add(const string& ID, vec3 position, vec3 color, float strength)
{
	_core->_lightEntityManager.addLightEntity(ID, position, color, strength);
}

void FabiEngine3D::lightEntity_delete(const string& ID)
{
	_core->_lightEntityManager.deleteEntity(ID);
}

void FabiEngine3D::lightEntity_hide(const string& ID)
{
	_core->_lightEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::lightEntity_show(const string& ID)
{
	_core->_lightEntityManager.getEntity(ID)->setEnabled(true);
}

bool FabiEngine3D::lightEntity_isExisting(const string& ID)
{
	return _core->_lightEntityManager.isExisting(ID);
}

void FabiEngine3D::lightEntity_setPosition(const string& ID, vec3 position)
{
	_core->_lightEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::lightEntity_setColor(const string& ID, vec3 color)
{
	_core->_lightEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::lightEntity_setStrength(const string& ID, float strength)
{
	_core->_lightEntityManager.getEntity(ID)->setStrength(strength);
}

/* --------------------------------------------- Gui interface --------------------------------------------- */

void FabiEngine3D::guiEntity_deleteAll()
{
	_core->_guiEntityManager.deleteEntities();
}

void FabiEngine3D::guiEntity_hideAll()
{
	for (auto& entity : _core->_guiEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void FabiEngine3D::guiEntity_showAll()
{
	for (auto& entity : _core->_guiEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void FabiEngine3D::guiEntity_add(const string& ID, const string& assetName, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, assetName, translation, rotation, scaling, false, centered);
	_core->_guiEntityManager.getEntity(ID)->setEnabled(visible);
}

void FabiEngine3D::guiEntity_add(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, color, translation, rotation, scaling, centered);
	_core->_guiEntityManager.getEntity(ID)->setEnabled(visible);
}

void FabiEngine3D::guiEntity_hide(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::guiEntity_show(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::guiEntity_delete(const string& ID)
{
	_core->_guiEntityManager.deleteEntity(ID);
}

void FabiEngine3D::guiEntity_changeTexture(const string& ID, const string& assetName)
{
	_core->_guiEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture("User\\Assets\\Textures\\GuiMaps" + assetName, true, true));
}

bool FabiEngine3D::guiEntity_isExisting(const string& ID)
{
	return _core->_guiEntityManager.isExisting(ID);
}

void FabiEngine3D::guiEntity_setPosition(const string& ID, vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::guiEntity_setRotation(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::guiEntity_setSize(const string& ID, vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::guiEntity_move(const string& ID, vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->translate(position, _core->_timer.getDeltaTime());
}

void FabiEngine3D::guiEntity_rotate(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->rotate(rotation, _core->_timer.getDeltaTime());
}

void FabiEngine3D::guiEntity_scale(const string& ID, vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->scale(size, _core->_timer.getDeltaTime());
}

void FabiEngine3D::guiEntity_setColor(const string& ID, vec3 color)
{
	_core->_guiEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::guiEntity_setAlpha(const string& ID, float alpha)
{
	_core->_guiEntityManager.getEntity(ID)->setAlpha(alpha);
 }

void FabiEngine3D::guiEntity_setMinPosition(const string& ID, vec2 minPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::guiEntity_setMaxPosition(const string& ID, vec2 maxPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

vec2 FabiEngine3D::guiEntity_getPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::guiEntity_getRotation(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getRotation();
}

vec2 FabiEngine3D::guiEntity_getSize(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getScaling();
}

bool FabiEngine3D::guiEntity_isVisible(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isEnabled();
}

/* --------------------------------------------- Text interface --------------------------------------------- */

void FabiEngine3D::textEntity_deleteAll()
{
	_core->_textEntityManager.deleteEntities();
}

void FabiEngine3D::textEntity_hideAll()
{
	for (auto& entity : _core->_textEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void FabiEngine3D::textEntity_showAll()
{
	for (auto& entity : _core->_textEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void FabiEngine3D::textEntity_add(const string& ID, const string& text, const string& fontPath, vec3 color, vec2 position, float rotation, vec2 size, bool centered)
{
	_core->_textEntityManager.addTextEntity(ID, text, fontPath, color, position, rotation, size, false, centered);
}

void FabiEngine3D::textEntity_delete(const string& ID)
{
	_core->_textEntityManager.deleteEntity(ID);
}

bool FabiEngine3D::textEntity_isExisting(const string& ID)
{
	return _core->_textEntityManager.isExisting(ID);
}

void FabiEngine3D::textEntity_setTextContent(const string& ID, const string& textContent, float charWidth)
{
	auto entity = _core->_textEntityManager.getEntity(ID);

	entity->setTextContent(textContent);
	entity->setScaling(vec2(charWidth*float(textContent.size()), entity->getScaling().y));
	entity->setDiffuseMap(_core->_texLoader.getText(textContent, entity->getFontPath()));
}

void FabiEngine3D::textEntity_setColor(const string& ID, vec3 color)
{
	_core->_textEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::textEntity_setAlpha(const string& ID, float alpha)
{
	_core->_textEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::textEntity_hide(const string& ID)
{
	_core->_textEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::textEntity_show(const string& ID)
{
	_core->_textEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::textEntity_setPosition(const string& ID, vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::textEntity_setRotation(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::textEntity_setSize(const string& ID, vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::textEntity_move(const string& ID, vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->translate(position, _core->_timer.getDeltaTime());
}

void FabiEngine3D::textEntity_rotate(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->rotate(rotation, _core->_timer.getDeltaTime());
}

void FabiEngine3D::textEntity_scale(const string& ID, vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->scale(size, _core->_timer.getDeltaTime());
}

void FabiEngine3D::textEntity_setMinPosition(const string& ID, vec2 minPos)
{
	_core->_textEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::textEntity_setMaxPosition(const string& ID, vec2 maxPos)
{
	_core->_textEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

vec2 FabiEngine3D::textEntity_getPosition(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::textEntity_getRotation(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getRotation();
}

vec2 FabiEngine3D::textEntity_getSize(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getScaling();
}

string FabiEngine3D::textEntity_getTextContent(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTextContent();
}

/* --------------------------------------------- Graphics interface --------------------------------------------- */

void FabiEngine3D::gfx_addAmbientLighting(float strength)
{
	_core->_shaderBus.setAmbLightEnabled(true);

	// Sky overrides
	if (_core->_skyEntityManager.getSelectedSky() == nullptr)
	{
		_core->_shaderBus.setAmbLightStrength(strength);
	}
}

void FabiEngine3D::gfx_addDirectionalLighting(vec3 position, float strength)
{
	_core->_shaderBus.setDirLightEnabled(true);
	_core->_shaderBus.setDirLightPos(position);
	_core->_shaderBus.setDirLightStrength(strength);

	// Sky overrides
	if (_core->_skyEntityManager.getSelectedSky() == nullptr)
	{
		_core->_shaderBus.setAmbLightStrength(strength);
	}
}

void FabiEngine3D::gfx_addSpecularLighting(float shininess)
{
	_core->_shaderBus.setSpecLightEnabled(true);
	_core->_shaderBus.setSpecLightStrength(shininess);
}

void FabiEngine3D::gfx_addPointLighting()
{
	_core->_shaderBus.setPointLightEnabled(true);
}

void FabiEngine3D::gfx_addFog(float minDistance)
{
	_core->_shaderBus.setFogEnabled(true);
	_core->_shaderBus.setFogMinDistance(minDistance);
}

void FabiEngine3D::gfx_addSkyReflections(float factor)
{
	_core->_shaderBus.setSkyReflectionsEnabled(true);
	_core->_shaderBus.setSkyReflectionFactor(factor);
}

void FabiEngine3D::gfx_addSceneReflections(float height, float factor)
{
	// Check if water is already using reflection graphics
	if (_core->_shaderBus.isWaterEffectsEnabled())
	{
		Logger::getInst().throwWarning("Cannot enable screen reflection graphics; \"water effects\" is currently using it!");
	}
	else
	{
		_core->_shaderBus.setSceneReflectionsEnabled(true);
		_core->_shaderBus.setSceneReflectionHeight(height);
		_core->_shaderBus.setSceneReflectionFactor(factor);
	}

}

void FabiEngine3D::gfx_addLightMapping()
{
	_core->_shaderBus.setLightMappingEnabled(true);
}

void FabiEngine3D::gfx_addMSAA()
{
	_core->_shaderBus.setMSAAEnabled(true);
}

void FabiEngine3D::gfx_addShadows(vec3 eye, vec3 center, float size, float reach)
{
	_core->_shadowManager.loadShadows(eye, center, size, reach);
	_core->_shaderBus.setShadowsEnabled(true);
}

void FabiEngine3D::gfx_addBloom(float intensity, float brightnessTreshold, int blurSize)
{
	_core->_shaderBus.setBloomEnabled(true);
	_core->_shaderBus.setBloomIntensity(intensity);
	_core->_shaderBus.setBloomTreshold(brightnessTreshold);
	_core->_shaderBus.setBloomBlurSize(blurSize);
}

void FabiEngine3D::gfx_addWaterEffects()
{
	_core->_shaderBus.setWaterEffectsEnabled(true);
}

void FabiEngine3D::gfx_addSkyHDR()
{
	_core->_shaderBus.setSkyHdrEnabled(true);
}

void FabiEngine3D::gfx_addDOF(float minDistance)
{
	_core->_shaderBus.setDofEnabled(true);
	_core->_shaderBus.setDofMinDistance(minDistance);
}

void FabiEngine3D::gfx_addMotionBlur()
{
	_core->_shaderBus.setMotionBlurEnabled(true);
}

void FabiEngine3D::gfx_removeAmbientLighting()
{
	_core->_shaderBus.setAmbLightEnabled(false);
}

void FabiEngine3D::gfx_removeDirectionalLighting()
{
	_core->_shaderBus.setDirLightEnabled(false);
}

void FabiEngine3D::gfx_removeSpecularLighting()
{
	_core->_shaderBus.setSpecLightEnabled(false);
}

void FabiEngine3D::gfx_removePointLighting()
{
	_core->_shaderBus.setPointLightEnabled(false);
}

void FabiEngine3D::gfx_removeFog()
{
	_core->_shaderBus.setFogEnabled(false);
}

void FabiEngine3D::gfx_removeSkyReflections()
{
	_core->_shaderBus.setSkyReflectionsEnabled(false);
}

void FabiEngine3D::gfx_removeSceneReflections()
{
	_core->_shaderBus.setSceneReflectionsEnabled(false);
}

void FabiEngine3D::gfx_removeLightMapping()
{
	_core->_shaderBus.setLightMappingEnabled(false);
}

void FabiEngine3D::gfx_removeMSAA()
{
	_core->_shaderBus.setMSAAEnabled(false);
}

void FabiEngine3D::gfx_removeShadows()
{
	_core->_shaderBus.setShadowsEnabled(false);
}

void FabiEngine3D::gfx_removeBloom()
{
	_core->_shaderBus.setBloomEnabled(false);
}

void FabiEngine3D::gfx_removeWaterEffects()
{
	_core->_shaderBus.setWaterEffectsEnabled(false);
}

void FabiEngine3D::gfx_removeSkyHDR()
{
	_core->_shaderBus.setSkyHdrEnabled(false);
}

void FabiEngine3D::gfx_removeDOF()
{
	_core->_shaderBus.setDofEnabled(false);
}

void FabiEngine3D::gfx_removeMotionBlur()
{
	_core->_shaderBus.setMotionBlurEnabled(false);
}

void FabiEngine3D::gfx_setSkyBrightness(float brightness)
{
	_core->_shaderBus.setSkyBrightness(brightness);
}

float FabiEngine3D::gfx_getSkyBrightness()
{
	return _core->_shaderBus.getSkyBrightness();
}

/* --------------------------------------------- Input interface --------------------------------------------- */

bool FabiEngine3D::input_getKeyDown(Input keyName)
{
	return _core->_inputHandler.getKeyDown(keyName);
}

bool FabiEngine3D::input_getKeyPressed(Input keyName)
{
	return _core->_inputHandler.getKeyPressed(keyName);
}

bool FabiEngine3D::input_getKeyToggled(Input keyName)
{
	return _core->_inputHandler.getKeyToggled(keyName);
}

bool FabiEngine3D::input_getMouseDown(Input mouseButton)
{
	return _core->_inputHandler.getMouseDown(mouseButton);
}

bool FabiEngine3D::input_getMousePressed(Input mouseButton)
{
	return _core->_inputHandler.getMousePressed(mouseButton);
}

bool FabiEngine3D::input_getMouseToggled(Input mouseButton)
{
	return _core->_inputHandler.getMouseToggled(mouseButton);
}

int FabiEngine3D::input_getMouseWheelX()
{
	return _core->_inputHandler.getMouseWheelX();
}

int FabiEngine3D::input_getMouseWheelY()
{
	return _core->_inputHandler.getMouseWheelY();
}

void FabiEngine3D::audioEntity_setSoundEnabled(bool val)
{
	_core->_audioPlayer.setSoundEnabled(val);
}

void FabiEngine3D::audioEntity_setMusicEnabled(bool val)
{
	_core->_audioPlayer.setMusicEnabled(val);
}

/* --------------------------------------------- Audio interface --------------------------------------------- */

void FabiEngine3D::audioEntity_deleteAllSounds()
{
	audioEntity_stopAllSounds();
	_core->_audioManager.deleteAllChunks();
}

void FabiEngine3D::audioEntity_deleteAllMusic()
{
	audioEntity_stopAllMusic();
	_core->_audioManager.deleteAllMusic();
}

void FabiEngine3D::audioEntity_stopAllSounds()
{
	_core->_audioPlayer.stopAllSounds();
}

void FabiEngine3D::audioEntity_stopAllMusic()
{
	_core->_audioPlayer.stopAllMusic();
}

void FabiEngine3D::audioEntity_addMusic(const std::string& fileName)
{
	_core->_audioManager.addMusic(fileName);
}

void FabiEngine3D::audioEntity_deleteMusic()
{
	_core->_audioManager.removeMusic();
}

void FabiEngine3D::audioEntity_setMusicVolume(int volume)
{
	volume = std::clamp(volume, 0, 100);
	_core->_audioPlayer.setMusicVolume(int((float(volume) / 100.0f) * 128.0f));
}

void FabiEngine3D::audioEntity_addGlobal(const std::string& ID, const std::string& fileName)
{
	_core->_audioManager.addGlobalChunk(ID, fileName);
}

void FabiEngine3D::audioEntity_addPoint(const std::string& ID, const std::string& fileName, vec3 position, float maxDistance)
{
	_core->_audioManager.addPointChunk(ID, fileName, position, maxDistance);
}

void FabiEngine3D::audioEntity_delete(const std::string& ID)
{
	if (_core->_audioManager.isChunkExisting(ID)) // If chunk exists
	{
		if (_core->_audioPlayer.isPlaying(_core->_audioManager.getChunk(ID))) // If chunk is playing
		{
			_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), 0);
		}
	}

	_core->_audioManager.removeChunk(ID);
}

void FabiEngine3D::audioEntity_play(const std::string& ID, int loops, int initialVolume, bool noRestart, int fadeMillis)
{
	initialVolume = std::clamp(initialVolume, 0, 100);
	_core->_audioPlayer.playChunk(_core->_audioManager.getChunk(ID), loops, int((float(initialVolume) / 100.0f) * 128.0f), noRestart, fadeMillis);
}

void FabiEngine3D::audioEntity_pause(const std::string& ID)
{
	_core->_audioPlayer.pauseChunk(_core->_audioManager.getChunk(ID));
}

void FabiEngine3D::audioEntity_resume(const std::string& ID)
{
	_core->_audioPlayer.resumeChunk(_core->_audioManager.getChunk(ID));
}

void FabiEngine3D::audioEntity_stop(const std::string& ID, int fadeMillis)
{
	_core->_audioPlayer.stopChunk(_core->_audioManager.getChunk(ID), fadeMillis);
}

void FabiEngine3D::audioEntity_setVolume(const std::string& ID, int volume)
{
	volume = std::clamp(volume, 0, 100);
	_core->_audioPlayer.setChunkVolume(_core->_audioManager.getChunk(ID), int((float(volume) / 100.0f) * 128.0f));
}

void FabiEngine3D::audioEntity_changePoint(const std::string& ID, vec3 position)
{
	_core->_audioManager.getChunk(ID).setPosition(position);
}

bool FabiEngine3D::audioEntity_isPlaying(const std::string& ID)
{
	return _core->_audioPlayer.isPlaying(_core->_audioManager.getChunk(ID));
}

int FabiEngine3D::audioEntity_getVolume(const std::string& ID)
{
	return _core->_audioPlayer.getVolume(_core->_audioManager.getChunk(ID));
}

int FabiEngine3D::audioEntity_getUsedChannelCount()
{
	return _core->_audioPlayer.getUsedChannelCount();
}

/* --------------------------------------------- Miscellaneous interface --------------------------------------------- */

int FabiEngine3D::misc_getUniqueInt()
{
	static vector<int> uniqueInts;
	int randomInt = misc_getRandomInt(0, INT_MAX);

	// Check if already existing
	if (std::find(uniqueInts.begin(), uniqueInts.end(), randomInt) != uniqueInts.end())
	{
		return misc_getUniqueInt();
	}
	else
	{
		uniqueInts.push_back(randomInt);
		return randomInt;
	}
}

int FabiEngine3D::misc_getWindowWidth()
{
	return Config::getInst().getWindowWidth();
}

int FabiEngine3D::misc_getWindowHeight()
{
	return Config::getInst().getWindowHeight();
}

int FabiEngine3D::misc_getRandomInt(int min, int max)
{
	return Tools::getInst().getRandomInt(min, max);
}

int FabiEngine3D::misc_getMsTimeSinceEpoch()
{
	using namespace std::chrono;
	return int(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

float FabiEngine3D::misc_getRandomFloat(float min, float max)
{
	return Tools::getInst().getRandomFloat(min, max);
}

float FabiEngine3D::misc_getAspectRatio()
{
	return float(misc_getWindowWidth()) / float(misc_getWindowHeight());
}

void FabiEngine3D::misc_showCursor()
{
	_core->_windowManager.showMouseCursor();
}

void FabiEngine3D::misc_hideCursor()
{
	_core->_windowManager.hideMouseCursor();
}

void FabiEngine3D::misc_enableWireframeRendering()
{
	_core->_shaderBus.setWireframeEnabled(true);
}

void FabiEngine3D::misc_disableWireframeRendering()
{
	_core->_shaderBus.setWireframeEnabled(false);
}

void FabiEngine3D::misc_enableDebugRendering()
{
	_core->_shaderBus.setDebugRenderEnabled(true);
}

void FabiEngine3D::misc_disableDebugRendering()
{
	_core->_shaderBus.setDebugRenderEnabled(false);
}

void FabiEngine3D::misc_setMousePos(ivec2 pos)
{
	_core->_mousePicker.update(pos, _core->_terrainEntityManager);
	_core->_windowManager.setMousePos(pos);
}

void FabiEngine3D::misc_preLoadGameEntity(const std::string& assetName, bool lightMapped, bool reflective)
{
	// Load OBJ model
	auto parts = _core->_objLoader.loadOBJ(assetName);

	// Create OpenGL buffers
	for (auto& part : parts)
	{
		// Diffuse map
		_core->_texLoader.getTexture("../Game/Textures/DiffuseMaps/" + part.textureName, true, true);

		// Light map
		if (lightMapped)
		{
			_core->_texLoader.getTexture("../Game/Textures/LightMaps/" + part.textureName, false, false);
		}

		// Reflection map
		if (reflective)
		{
			_core->_texLoader.getTexture("../Game/Textures/ReflectionMaps/" + part.textureName, false, false);
		}
	}
}

void FabiEngine3D::misc_showPerformanceProfiling()
{
	_core->_showStats = true;
}

void FabiEngine3D::misc_hidePerformanceProfiling()
{
	_core->_showStats = false;
	
	vector<string> elements =
	{
		"inputHandle", "gameUpdates", "raycastUpdates", "physicsUpdates", "cameraUpdates", "entityUpdates", "shadowUpdates", "audioUpdates",
		"renderSwap", "reflectionPreRender", "waterPreRender", "shadowPreRender", "depthPreRender", "skyEntity", "terrainEntity", "waterEntity",
		"gameEntities", "bBoardEntities", "aabbEntities", "postProcessing", "guiRender", "textRender", "misc", "fps"
	};

	for (auto& e : elements)
	{
		if (_core->_textEntityManager.isExisting(e))
		{
			_core->_textEntityManager.getEntity(e)->setEnabled(false);
		}
	}
}

void FabiEngine3D::misc_showAudioDebugging()
{
	_core->_audioPlayer.setChannelDebugging(true);
}

void FabiEngine3D::misc_hideAudioDebugging()
{
	_core->_audioPlayer.setChannelDebugging(false);
}

void FabiEngine3D::misc_setMainColor(vec3 color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

string FabiEngine3D::misc_getWinExplorerFilename(string startingDir, string fileType)
{
	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string fullDir = buffer;
	fullDir = fullDir.substr(0, fullDir.size() - 25);

	// Prepare filter C-string
	string filter = fileType;
	filter.push_back('\0');
	filter += "*." + fileType + '\0';

	// Open file explorer
	OPENFILENAME ofn;
	char pathBuffer[100];
	char titleBuffer[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = pathBuffer;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(pathBuffer);
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = titleBuffer;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(titleBuffer);
	ofn.lpstrInitialDir = string(fullDir + startingDir).c_str(); // Projects folder
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	// Return chosen filename
	return ofn.lpstrFileTitle;
}

string FabiEngine3D::misc_vec2str(vec2 vec)
{
	return std::to_string(vec.x) + " " + std::to_string(vec.y);
}

string FabiEngine3D::misc_vec2str(vec3 vec)
{
	return std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
}

string FabiEngine3D::misc_vec2str(vec4 vec)
{
	return std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z) + " " + std::to_string(vec.w);
}

ivec2 FabiEngine3D::misc_getMousePos()
{
	ivec2 mousePos = _core->_windowManager.getMousePos();

	return ivec2(mousePos.x, misc_getWindowHeight() - mousePos.y);
}

vec2 FabiEngine3D::misc_convertToNDC(vec2 pos)
{
	pos.x = (pos.x * 2.0f) - 1.0f;
	pos.y = (pos.y * 2.0f) - 1.0f;
	
	return vec2(pos.x, pos.y);
}

vec2 FabiEngine3D::misc_convertFromNDC(vec2 pos)
{
	pos.x += 1.0f;
	pos.x /= 2.0f;
	pos.y += 1.0f;
	pos.y /= 2.0f;

	return vec2(pos.x, pos.y);
}

ivec2 FabiEngine3D::misc_convertToScreenCoords(vec2 pos)
{
	float x = float(pos.x) * float(misc_getWindowWidth());
	float y = float(pos.y) * float(misc_getWindowHeight());

	return ivec2(int(x), int(y));
}

vec2 FabiEngine3D::misc_convertFromScreenCoords(ivec2 pos)
{
	float x = float(pos.x) / float(misc_getWindowWidth());
	float y = float(pos.y) / float(misc_getWindowHeight());

	return vec2(x, y);
}

vec2 FabiEngine3D::misc_getViewportPosition()
{
	return Config::getInst().getVpPos();
}

vec2 FabiEngine3D::misc_getViewportSize()
{
	return Config::getInst().getVpSize();
}

bool FabiEngine3D::misc_isMouseInsideViewport()
{
	// Variables for calculating the scrolling speed
	vec2 mousePos = misc_getMousePos();
	vec2 viewportPos = misc_getViewportPosition();
	vec2 viewportSize = misc_getViewportSize();

	// Checking if cursor is inside scrolling list
	if (mousePos.x > viewportPos.x && mousePos.x < viewportPos.x + viewportSize.x)
	{
		if (mousePos.y > viewportPos.y && mousePos.y < viewportPos.y + viewportSize.y)
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::world_check(const string& worldName)
{
	return _core->_worldEditor.checkWorld(worldName);
}

void FabiEngine3D::world_load(const string& worldName)
{
	_core->_worldEditor.loadWorld(worldName);
}

void FabiEngine3D::world_export(const string& worldName)
{
	_core->_worldEditor.exportWorld(worldName);
}
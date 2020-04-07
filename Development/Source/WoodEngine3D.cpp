#include <algorithm>
#include <limits>
#include <chrono>

#include <WE3D/WoodEngine3D.hpp>
#include <WE3D/CoreEngine.hpp>
#include <WE3D/Configuration.hpp>
#include <WE3D/ShaderBus.hpp>
#include <WE3D/InputHandler.hpp>
#include <WE3D/Tools.hpp>

WoodEngine3D::WoodEngine3D(EngineState state)
{
	p_core = new CoreEngine(*this, state);
}

WoodEngine3D::~WoodEngine3D()
{
	delete p_core;
}

/* --------------------------------------------- Game interface --------------------------------------------- */

void WoodEngine3D::game_start()
{
	p_core->p_start();
}

void WoodEngine3D::game_pause()
{
	p_core->p_isPaused = true;
}

void WoodEngine3D::game_unpause()
{
	p_core->p_isPaused = false;
}

void WoodEngine3D::game_pauseEntityUpdates()
{
	p_core->p_entitiesPaused = true;
}

void WoodEngine3D::game_unpauseEntityUpdates()
{
	p_core->p_entitiesPaused = false;
}

void WoodEngine3D::game_stop()
{
	p_core->p_stop();
}

/* --------------------------------------------- Camera interface --------------------------------------------- */

void WoodEngine3D::camera_load(float fov, float nearZ, float farZ, vec3 startPos, float yaw, float pitch)
{
	p_core->p_cameraManager.setFOV(fov);
	p_core->p_cameraManager.setNearZ(nearZ);
	p_core->p_cameraManager.setFarZ(farZ);
	p_core->p_cameraManager.setPosition(startPos);
	p_core->p_cameraManager.setYaw(yaw);
	p_core->p_cameraManager.setPitch(pitch);
}

void WoodEngine3D::camera_enableFirstPersonView(float mouseSensitivity)
{
	p_core->p_cameraManager.enableFirstPersonView();
	p_core->p_cameraManager.setMouseSensitivity(mouseSensitivity);
}

void WoodEngine3D::camera_disableFirstPersonView()
{
	p_core->p_cameraManager.disableFirstPersonView();
}

void WoodEngine3D::camera_enableFreeMovement()
{
	p_core->p_cameraManager.enableFreeMovement();
}

void WoodEngine3D::camera_disableFreeMovement()
{
	p_core->p_cameraManager.disableFreeMovement();
}

void WoodEngine3D::camera_translateFollowX(float speed)
{
	p_core->p_cameraManager.translateFollowX(speed, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::camera_translateFollowZY(float speed)
{
	p_core->p_cameraManager.translateFollowZY(speed, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::camera_translateFollowZ(float speed)
{
	p_core->p_cameraManager.translateFollowZ(speed, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::camera_translate(vec3 translation)
{
	p_core->p_cameraManager.translate(translation, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::camera_setPosition(vec3 pos)
{
	p_core->p_cameraManager.setPosition(pos);
}

void WoodEngine3D::camera_invertYaw()
{
	p_core->p_cameraManager.invertYaw();
}

void WoodEngine3D::camera_invertPitch()
{
	p_core->p_cameraManager.invertPitch();
}

void WoodEngine3D::camera_setFOV(float fov)
{
	p_core->p_cameraManager.setFOV(fov);
}

void WoodEngine3D::camera_setSensitivity(float speed)
{
	p_core->p_cameraManager.setMouseSensitivity(speed);
}

void WoodEngine3D::camera_setYaw(float val)
{
	p_core->p_cameraManager.setYaw(val);
}

void WoodEngine3D::camera_setPitch(float val)
{
	p_core->p_cameraManager.setPitch(val);
}

float WoodEngine3D::camera_getYaw()
{
	return p_core->p_cameraManager.getYaw();
}

float WoodEngine3D::camera_getPitch()
{
	return p_core->p_cameraManager.getPitch();
}

float WoodEngine3D::camera_getMouseOffset()
{
	return p_core->p_cameraManager.getMouseOffset();
}

vec3 WoodEngine3D::camera_getPos()
{
	return p_core->p_cameraManager.getPosition();
}

vec3 WoodEngine3D::camera_getFront()
{
	return p_core->p_cameraManager.getFront();
}

/* --------------------------------------------- Sky interface --------------------------------------------- */

void WoodEngine3D::skyEntity_add
(
	const string& ID, const string& dayDirectory, const string& nightDirectory, float rotationSpeed
)
{
	p_core->p_skyEntityManager.addSkyEntity(ID, dayDirectory, nightDirectory, rotationSpeed, p_core->p_texLoader);
}

void WoodEngine3D::skyEntity_delete(const string& ID)
{
	p_core->p_skyEntityManager.deleteEntity(ID);
	p_core->p_skyEntityManager.selectSky("");
}

void WoodEngine3D::skyEntity_setAmbientLighting(const string& ID, float nightAmbStrength, float dayAmbStrength)
{
	p_core->p_skyEntityManager.getEntity(ID)->setNightAmbStrength(nightAmbStrength);
	p_core->p_skyEntityManager.getEntity(ID)->setDayAmbStrength(dayAmbStrength);
}

void WoodEngine3D::skyEntity_setDirectionalLighting(const string& ID, float nightDirStrength, float dayDirStrength)
{
	p_core->p_skyEntityManager.getEntity(ID)->setNightDirStrength(nightDirStrength);
	p_core->p_skyEntityManager.getEntity(ID)->setDayDirStrength(dayDirStrength);
}

void WoodEngine3D::skyEntity_select(const string& ID)
{
	p_core->p_skyEntityManager.selectSky(ID);
}

void WoodEngine3D::skyEntity_setDayTime(const string& ID)
{
	p_core->p_skyEntityManager.getEntity(ID)->setDayTime();
	p_core->p_skyEntityManager.getEntity(ID)->setMixValue(0.0f);

	if (p_core->p_skyEntityManager.getEntity(ID)->getAmbStrength() != -1.0f)
	{
		p_core->p_shaderBus.setAmbLightStrength(p_core->p_skyEntityManager.getEntity(ID)->getAmbStrength());
	}

	if (p_core->p_skyEntityManager.getEntity(ID)->getDirStrength() != -1.0f)
	{
		p_core->p_shaderBus.setDirLightStrength(p_core->p_skyEntityManager.getEntity(ID)->getDirStrength());
	}
}

void WoodEngine3D::skyEntity_setNightTime(const string& ID)
{
	p_core->p_skyEntityManager.getEntity(ID)->setNightTime();
	p_core->p_skyEntityManager.getEntity(ID)->setMixValue(1.0f);

	if (p_core->p_skyEntityManager.getEntity(ID)->getAmbStrength() != -1.0f)
	{
		p_core->p_shaderBus.setAmbLightStrength(p_core->p_skyEntityManager.getEntity(ID)->getAmbStrength());
	}

	if (p_core->p_skyEntityManager.getEntity(ID)->getDirStrength() != -1.0f)
	{
		p_core->p_shaderBus.setDirLightStrength(p_core->p_skyEntityManager.getEntity(ID)->getDirStrength());
	}
}

void WoodEngine3D::skyEntity_fadeDayTime(const string& ID)
{
	p_core->p_skyEntityManager.getEntity(ID)->setDayTime();
}

void WoodEngine3D::skyEntity_fadeNightTime(const string& ID)
{
	p_core->p_skyEntityManager.getEntity(ID)->setNightTime();
}

bool WoodEngine3D::skyEntity_isDayTime(const string& ID)
{
	return p_core->p_skyEntityManager.getEntity(ID)->isDayTime();
}

bool WoodEngine3D::skyEntity_isNightTime(const string& ID)
{
	return p_core->p_skyEntityManager.getEntity(ID)->isNightTime();
}

string WoodEngine3D::skyEntity_getSelectedID()
{
	if (p_core->p_skyEntityManager.getSelectedSky() != nullptr)
	{
		return p_core->p_skyEntityManager.getSelectedSky()->getID();
	}
	else
	{
		return "";
	}
}

bool WoodEngine3D::skyEntity_isExisting(const string& ID)
{
	return p_core->p_skyEntityManager.isExisting(ID);
}

/* --------------------------------------------- Terrain interface --------------------------------------------- */

void WoodEngine3D::terrainEntity_add(const string& ID, const string& heightmapName, const string& textureName, vec3 pos, float size, float maxHeight, float uvRepeat)
{
	p_core->p_terrainEntityManager.addTerrainEntity(ID, heightmapName, textureName, pos, size, maxHeight, uvRepeat);
}

void WoodEngine3D::terrainEntity_delete(const string& ID)
{
	p_core->p_terrainEntityManager.deleteEntity(ID);
	p_core->p_terrainEntityManager.selectTerrain("");
}

bool WoodEngine3D::terrainEntity_isExisting(const string& ID)
{
	return p_core->p_terrainEntityManager.isExisting(ID);
}

bool WoodEngine3D::terrainEntity_isInside(float x, float z)
{
	return p_core->p_terrainEntityManager.isInside(x, z);
}

vec3 WoodEngine3D::terrainEntity_getMousePoint()
{
return p_core->p_mousePicker.getTerrainPoint();
}

float WoodEngine3D::terrainEntity_getPixelHeight(float x, float z)
{
	return p_core->p_terrainEntityManager.getPixelHeight(x, z);
}

string WoodEngine3D::terrainEntity_getSelectedID()
{
	if (p_core->p_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		return p_core->p_terrainEntityManager.getSelectedTerrain()->getID();
	}
	else
	{
		return "";
	}
}

void WoodEngine3D::terrainEntity_select(const string& ID)
{
	p_core->p_terrainEntityManager.selectTerrain(ID);
}

void WoodEngine3D::terrainEntity_addBlending
(
	const string& ID, const string blendmapName, const string blendmapNameR,
	const string blendmapNameG, const string blendmapNameB,
	float blendRepeatR, float blendRepeatG, float blendRepeatB
)
{
	p_core->p_terrainEntityManager.addBlendingToTerrain(ID, blendmapName, blendmapNameR, blendmapNameG, blendmapNameB, blendRepeatR, blendRepeatG, blendRepeatB);
}

void WoodEngine3D::waterEntity_add(const string& ID, const string& assetName, vec3 pos, float size, float tileRepeat, float speed, bool waving, bool rippling, vec3 color, float shininess)
{
	p_core->p_waterEntityManager.addWaterEntity(ID, assetName, pos, size, tileRepeat, speed, waving, rippling, color, shininess);
}

void WoodEngine3D::waterEntity_delete(const string& ID)
{
	p_core->p_waterEntityManager.deleteEntity(ID);
	p_core->p_waterEntityManager.selectWater("");
}

bool WoodEngine3D::waterEntity_isExisting(const string& ID)
{
	return p_core->p_waterEntityManager.isExisting(ID);
}

void WoodEngine3D::waterEntity_select(const string& ID)
{
	p_core->p_waterEntityManager.selectWater(ID);
}

void WoodEngine3D::waterEntity_enableWaving(const string& ID)
{
	p_core->p_waterEntityManager.getEntity(ID)->setWaving(true);
}

void WoodEngine3D::waterEntity_disableWaving(const string& ID)
{
	p_core->p_waterEntityManager.getEntity(ID)->setWaving(false);
}

void WoodEngine3D::waterEntity_enableRippling(const string& ID)
{
	p_core->p_waterEntityManager.getEntity(ID)->setRippling(true);
}

void WoodEngine3D::waterEntity_disableRippling(const string& ID)
{
	p_core->p_waterEntityManager.getEntity(ID)->setRippling(false);
}

void WoodEngine3D::waterEntity_setColor(const string& ID, vec3 color)
{
	p_core->p_waterEntityManager.getEntity(ID)->setColor(color);
}

void WoodEngine3D::waterEntity_setShininess(const string& ID, float shininess)
{
	p_core->p_waterEntityManager.getEntity(ID)->setShininess(shininess);
}

void WoodEngine3D::waterEntity_setTransparency(const string& ID, float transparency)
{
	transparency = std::clamp(transparency, 0.0f, 1.0f);
	p_core->p_waterEntityManager.getEntity(ID)->setTransparency(transparency * 10.0f);
}

string WoodEngine3D::waterEntity_getSelectedID()
{
	if (p_core->p_waterEntityManager.getSelectedWater() != nullptr)
	{
		return p_core->p_waterEntityManager.getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

/* --------------------------------------------- Game entity interface --------------------------------------------- */

void WoodEngine3D::gameEntity_deleteAll()
{
	// For every GAME entity
	for (auto& entity : p_core->p_gameEntityManager.getEntities())
	{
		// Check if AABB entity is bound
		if (p_core->p_aabbEntityManager.isExisting(entity->getID()))
		{
			// If the case, delete it too
			p_core->p_aabbEntityManager.deleteEntity(entity->getID());
		}

		// Delete GAME entity
		gameEntity_delete(entity->getID());
	}
}

void WoodEngine3D::gameEntity_add
(
	const string& ID, const string& modelName,
	vec3 position, vec3 rotation, vec3 size,
	bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular, bool visible
)
{
	p_core->p_gameEntityManager.addGameEntity(ID, modelName, position, rotation, size, transparent, faceCulled, lightMapped, reflective, specular);
	p_core->p_gameEntityManager.getEntity(ID)->setEnabled(visible);
}

void WoodEngine3D::gameEntity_addInstanced
(
	const string& ID, const string& modelName,
	const vector<vec3>& positions, vec3 rotation, vec3 size,
	bool transparent, bool faceCulled, bool lightMapped, bool reflective, bool specular
)
{
	p_core->p_gameEntityManager.addGameEntity(ID, modelName, positions, rotation, size, transparent, faceCulled, lightMapped, reflective, specular);
}

void WoodEngine3D::gameEntity_delete(const string& ID)
{
	// Check if AABB entity is bound
	if (p_core->p_aabbEntityManager.isExisting(ID))
	{
		// If the case, delete it too
		p_core->p_aabbEntityManager.deleteEntity(ID);
	}

	// Delete GAME entity
	p_core->p_gameEntityManager.deleteEntity(ID);
}

void WoodEngine3D::gameEntity_deleteGroup(const string& ID)
{
	for (auto entity : p_core->p_gameEntityManager.getEntities()) // Loop over game entities
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
				p_core->p_gameEntityManager.deleteEntity(entity->getID());
			}
		}
	}
}

void WoodEngine3D::gameEntity_hideAll()
{
	for (auto entity : p_core->p_gameEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void WoodEngine3D::gameEntity_showAll()
{
	for (auto entity : p_core->p_gameEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void WoodEngine3D::gameEntity_hide(const string& ID)
{
	p_core->p_gameEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::gameEntity_show(const string& ID)
{
	p_core->p_gameEntityManager.getEntity(ID)->setEnabled(true);
}

bool WoodEngine3D::gameEntity_isExisting(const string& ID)
{
	return p_core->p_gameEntityManager.isExisting(ID);
}

bool WoodEngine3D::gameEntity_isVisible(const string& ID)
{
	return p_core->p_gameEntityManager.getEntity(ID)->isEnabled();
}

void WoodEngine3D::gameEntity_move(const string& ID, vec3 factor)
{
	p_core->p_gameEntityManager.getEntity(ID)->translate(factor, p_core->p_timer.getDeltaTime());

	// Also update potential bound AABB entities
	if (p_core->p_aabbEntityManager.isExisting(ID))
	{
		p_core->p_aabbEntityManager.getEntity(ID)->translate(factor, p_core->p_timer.getDeltaTime());
	}
}

void WoodEngine3D::gameEntity_rotate(const string& ID, vec3 factor)
{
	p_core->p_gameEntityManager.getEntity(ID)->rotate(factor, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::gameEntity_scale(const string& ID, vec3 factor)
{
	p_core->p_gameEntityManager.getEntity(ID)->scale(factor, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::gameEntity_setPosition(const string& ID, vec3 position)
{
	p_core->p_gameEntityManager.getEntity(ID)->setTranslation(position);

	// Also update potential bound AABB entities
	if (p_core->p_aabbEntityManager.isExisting(ID))
	{
		p_core->p_aabbEntityManager.getEntity(ID)->setTranslation(position);
	}
}

void WoodEngine3D::gameEntity_setRotation(const string& ID, vec3 rotation)
{
	p_core->p_gameEntityManager.getEntity(ID)->setRotation(rotation);
}

void WoodEngine3D::gameEntity_setSize(const string& ID, vec3 size)
{
	p_core->p_gameEntityManager.getEntity(ID)->setScaling(size);
}

vec3 WoodEngine3D::gameEntity_getPosition(const string& ID)
{
	return p_core->p_gameEntityManager.getEntity(ID)->getTranslation();
}

vec3 WoodEngine3D::gameEntity_getRotation(const string& ID)
{
	return p_core->p_gameEntityManager.getEntity(ID)->getRotation();
}

vec3 WoodEngine3D::gameEntity_getSize(const string& ID)
{
	return p_core->p_gameEntityManager.getEntity(ID)->getScaling();
}

void WoodEngine3D::gameEntity_enable(const string& ID)
{
	p_core->p_gameEntityManager.getEntity(ID)->setEnabled(true);
}

void WoodEngine3D::gameEntity_disable(const string& ID)
{
	p_core->p_gameEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::gameEntity_setMaxY(const string& ID, float y)
{
	p_core->p_gameEntityManager.getEntity(ID)->setMaxY(y);
}

void WoodEngine3D::gameEntity_setUvRepeat(const string& ID, float repeat)
{
	p_core->p_gameEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

float WoodEngine3D::gameEntity_getMaxY(const string& ID)
{
	return p_core->p_gameEntityManager.getEntity(ID)->getMaxY();
}

void WoodEngine3D::gameEntity_setAlpha(const string& ID, float alpha)
{
	p_core->p_gameEntityManager.getEntity(ID)->setAlpha(alpha);
}

void WoodEngine3D::gameEntity_setShadowed(const string& ID, bool shadowed)
{
	p_core->p_gameEntityManager.getEntity(ID)->setShadowed(shadowed);
}

void WoodEngine3D::gameEntity_setColor(const string& ID, vec3 color)
{
	p_core->p_gameEntityManager.getEntity(ID)->setColor(color);
}

void WoodEngine3D::gameEntity_setScreenReflective(const string& ID, bool enabled)
{
	p_core->p_gameEntityManager.getEntity(ID)->setScreenReflective(enabled);
}

vector<string> WoodEngine3D::gameEntity_getGroupIDs(const string& ID)
{
	vector<string> IDs;

	for (auto entity : p_core->p_gameEntityManager.getEntities()) // Loop over game entities
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

void WoodEngine3D::billBoardEntity_add(const string& ID, const string& text, const string& fontName, vec3 color, vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY, bool visible)
{
	p_core->p_billboardEntityManager.addBillboardEntity(ID, text, fontName, color, T, R, S, facingCameraX, facingCameraY);
	p_core->p_billboardEntityManager.getEntity(ID)->setEnabled(visible);
}

void WoodEngine3D::billBoardEntity_add(const string& ID, const string& textureName, vec3 T, vec3 R, vec3 S, bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering, bool visible)
{
	p_core->p_billboardEntityManager.addBillboardEntity(ID, textureName, T, R, S, transparent, facingCameraX, facingCameraY, textureFiltering);
	p_core->p_billboardEntityManager.getEntity(ID)->setEnabled(visible);
}

void WoodEngine3D::billboardEntity_deleteAll()
{
	p_core->p_billboardEntityManager.deleteEntities();
}

void WoodEngine3D::billboardEntity_delete(const string& ID)
{
	p_core->p_billboardEntityManager.deleteEntity(ID);
}

void WoodEngine3D::billboardEntity_hideAll()
{
	for (auto& entity : p_core->p_billboardEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void WoodEngine3D::billboardEntity_showAll()
{
	for (auto& entity : p_core->p_billboardEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void WoodEngine3D::billboardEntity_hide(const string& ID)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::billboardEntity_show(const string& ID)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setEnabled(true);
}

bool WoodEngine3D::billboardEntity_isExisting(const string& ID)
{
	return p_core->p_billboardEntityManager.isExisting(ID);
}

void WoodEngine3D::billboardEntity_move(const string& ID, vec3 factor)
{
	p_core->p_billboardEntityManager.getEntity(ID)->translate(factor, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::billboardEntity_rotate(const string& ID, vec3 factor)
{
	p_core->p_billboardEntityManager.getEntity(ID)->rotate(factor, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::billboardEntity_scale(const string& ID, vec3 factor)
{
	p_core->p_billboardEntityManager.getEntity(ID)->scale(factor, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::billboardEntity_setPosition(const string& ID, vec3 position)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setTranslation(position);
}

void WoodEngine3D::billboardEntity_setRotation(const string& ID, vec3 rotation)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setRotation(rotation);
}

void WoodEngine3D::billboardEntity_setSize(const string& ID, vec3 size)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setScaling(size);
}

vec3 WoodEngine3D::billboardEntity_getPosition(const string& ID)
{
	return p_core->p_billboardEntityManager.getEntity(ID)->getTranslation();
}

vec3 WoodEngine3D::billboardEntity_getRotation(const string& ID)
{
	return p_core->p_billboardEntityManager.getEntity(ID)->getRotation();
}

vec3 WoodEngine3D::billboardEntity_getSize(const string& ID)
{
	return p_core->p_billboardEntityManager.getEntity(ID)->getScaling();
}

void WoodEngine3D::billboardEntity_enable(const string& ID)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setEnabled(true);
}

void WoodEngine3D::billboardEntity_disable(const string& ID)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::billBoardEntity_playSpriteAnimation(const string& ID, int rows, int columns, float maxDelta, int repeats)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setSpriteAnimation(rows, columns, maxDelta, repeats);
}

void WoodEngine3D::billBoardEntity_changeText(const string& ID, const string& text, const string& fontName, vec3 color)
{
	p_core->p_billboardEntityManager.getEntity(ID)->setText(text);
	p_core->p_billboardEntityManager.getEntity(ID)->setColor(color);
	p_core->p_billboardEntityManager.getEntity(ID)->setDiffuseMap(p_core->p_texLoader.getText(text, "../Game/Fonts/" + fontName));
}

bool WoodEngine3D::billboardEntity_isFinished(const string& ID)
{
	int repeats = p_core->p_billboardEntityManager.getEntity(ID)->getRepeats();
	int maxRepeats = p_core->p_billboardEntityManager.getEntity(ID)->getMaxRepeats();
	return (repeats == maxRepeats);
}

/* --------------------------------------------- AABB entity interface --------------------------------------------- */

void WoodEngine3D::aabbEntity_deleteAll()
{
	p_core->p_aabbEntityManager.deleteEntities();
}

void WoodEngine3D::aabbEntity_add(const string& ID, vec3 T, vec3 S, bool responsive)
{
	p_core->p_aabbEntityManager.addAabbEntity(ID, T, vec3(0.0f), S, responsive);
}

void WoodEngine3D::aabbEntity_bindToGameEntity(const string& parentID, vec3 S, bool responsive)
{
	if (p_core->p_gameEntityManager.isExisting(parentID))
	{
		p_core->p_aabbEntityManager.bindAabbEntity(parentID, parentID, vec3(0.0f), S, responsive);
		p_core->p_aabbEntityManager.getEntity(parentID)->setTranslation(p_core->p_gameEntityManager.getEntity(parentID)->getTranslation());
	}
	else
	{
		logger_throwError("Tried to bind AABB entity to non-existing GAME entity \"" + parentID + "\"!");
	}
}

void WoodEngine3D::aabbEntity_bindToGameEntityGroup(const string& parentID, vec3 S, bool responsive)
{
	bool found = false;

	for (auto entity : p_core->p_gameEntityManager.getEntities()) // Loop over game entities
	{
		if (entity->getID().size() >= parentID.size()) // Check if entity ID is at least the size of group ID
		{
			if (entity->getID().substr(0, parentID.size()) == parentID) // If entity matches ID
			{
				found = true;
				p_core->p_aabbEntityManager.bindAabbEntity(entity->getID(), entity->getID(), vec3(0.0f), S, responsive); // Add new box
			}
		}
	}

	if (!found)
	{
		logger_throwError("Tried to bind AABB entities to non-existing GAME entity group \"" + parentID + "\"!");
	}
}

void WoodEngine3D::aabbEntity_delete(const string& ID)
{
	p_core->p_aabbEntityManager.deleteEntity(ID);
}

void WoodEngine3D::aabbEntity_setResponsiveness(const string& ID, bool responsive)
{
	p_core->p_aabbEntityManager.getEntity(ID)->setResponsiveness(responsive);
}

void WoodEngine3D::aabbEntity_setGroupResponsiveness(const string& ID, bool responsive)
{
	for (auto entity : p_core->p_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				p_core->p_aabbEntityManager.getEntity(entity->getID())->setResponsiveness(responsive);
			}
		}
	}
}

void WoodEngine3D::aabbEntity_setPosition(const string& ID, vec3 position)
{
	p_core->p_aabbEntityManager.getEntity(ID)->setTranslation(position);
}

void WoodEngine3D::aabbEntity_setSize(const string& ID, vec3 size)
{
	p_core->p_aabbEntityManager.getEntity(ID)->setScaling(size);
}

vec3 WoodEngine3D::aabbEntity_getPosition(const string& ID)
{
	return p_core->p_aabbEntityManager.getEntity(ID)->getTranslation();
}

vec3 WoodEngine3D::aabbEntity_getSize(const string& ID)
{
	return p_core->p_aabbEntityManager.getEntity(ID)->getScaling();
}

bool WoodEngine3D::aabbEntity_isExisting(const string& ID)
{
	return p_core->p_aabbEntityManager.isExisting(ID);
}

/* --------------------------------------------- Global collision interface --------------------------------------------- */

void WoodEngine3D::collision_enableCameraResponse()
{
	p_core->p_collisionResolver.enableAabbResponse();
}

void WoodEngine3D::collision_disableCameraResponse()
{
	p_core->p_collisionResolver.disableAabbResponse();
}

void WoodEngine3D::collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	p_core->p_collisionResolver.enableTerrainResponse(cameraHeight, cameraSpeed);
}

void WoodEngine3D::collision_disableCameraTerrainResponse()
{
	p_core->p_collisionResolver.disableTerrainResponse();
}

void WoodEngine3D::collision_enableFrameRendering()
{
	p_core->p_shaderBus.setAabbFrameEnabled(true);
}

void WoodEngine3D::collision_disableFrameRendering()
{
	p_core->p_shaderBus.setAabbFrameEnabled(false);
}

bool WoodEngine3D::collision_checkAnyWithCamera()
{
	for (auto entity : p_core->p_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (entity->getCollisionDirection() != CollisionDir::NONE)
		{
			return true;
		}
	}

	return false;
}

bool WoodEngine3D::collision_checkEntityCamera(const string& ID)
{
	return p_core->p_aabbEntityManager.getEntity(ID)->getCollisionDirection() != CollisionDir::NONE;
}

bool WoodEngine3D::collision_isCameraUnderGround()
{
	return p_core->p_collisionResolver.isCameraUnderGround();
}

bool WoodEngine3D::collision_isCameraAboveGround()
{
	return p_core->p_collisionResolver.isCameraAboveGround();
}

string WoodEngine3D::collision_checkEntityOthers(const string ID)
{
	for (auto other : p_core->p_aabbEntityManager.getEntities()) // Loop over aabb entities
	{
		if (other->getID() != ID && other->isResponsive()) // Don't check own entity & must be responsive
		{
			auto self = p_core->p_aabbEntityManager.getEntity(ID);
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

string WoodEngine3D::collision_checkEntityGroupCamera(const string& ID)
{
	for (auto entity : p_core->p_aabbEntityManager.getEntities()) // Loop over aabb entities
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

bool WoodEngine3D::collision_checkCursorInEntity(const string& ID)
{
	auto entity = p_core->p_aabbEntityManager.getEntity(ID);
	vec3 lb, rt;
	lb.x = (entity->getTranslation().x - entity->getScaling().x);
	lb.y = (entity->getTranslation().y);
	lb.z = (entity->getTranslation().z + entity->getScaling().z);
	rt.x = (entity->getTranslation().x + entity->getScaling().x);
	rt.y = (entity->getTranslation().y + entity->getScaling().y);
	rt.z = (entity->getTranslation().z - entity->getScaling().z);

	return p_core->p_mousePicker.checkCursorInBox(lb, rt, p_core->p_cameraManager.getPosition()) != -1.0f;
}

string WoodEngine3D::collision_checkCursorInEntityGroup(const string& ID, const string exception)
{
	float closestDistance = (std::numeric_limits<float>::max)();
	string closestBox = "";

	for (auto entity : p_core->p_aabbEntityManager.getEntities()) // Loop over aabb entities
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
				float distance = p_core->p_mousePicker.checkCursorInBox(lb, rt, p_core->p_cameraManager.getPosition());

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

ivec3 WoodEngine3D::collision_checkEntityCameraDir(const string& ID)
{
	// Calculate direction
	auto state = p_core->p_aabbEntityManager.getEntity(ID)->getCollisionDirection();

	// Return collision
	return ivec3(state == CollisionDir::X, state == CollisionDir::Y, state == CollisionDir::Z);
}

ivec3 WoodEngine3D::collision_checkEntityGroupCameraDir(const string& ID)
{
	for (auto entity : p_core->p_aabbEntityManager.getEntities()) // Loop over aabb entities
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

void WoodEngine3D::lightEntity_deleteAll()
{
	p_core->p_lightEntityManager.deleteEntities();
}

void WoodEngine3D::lightEntity_add(const string& ID, vec3 position, vec3 color, float strength)
{
	p_core->p_lightEntityManager.addLightEntity(ID, position, color, strength);
}

void WoodEngine3D::lightEntity_delete(const string& ID)
{
	p_core->p_lightEntityManager.deleteEntity(ID);
}

void WoodEngine3D::lightEntity_hide(const string& ID)
{
	p_core->p_lightEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::lightEntity_show(const string& ID)
{
	p_core->p_lightEntityManager.getEntity(ID)->setEnabled(true);
}

bool WoodEngine3D::lightEntity_isExisting(const string& ID)
{
	return p_core->p_lightEntityManager.isExisting(ID);
}

void WoodEngine3D::lightEntity_setPosition(const string& ID, vec3 position)
{
	p_core->p_lightEntityManager.getEntity(ID)->setPosition(position);
}

void WoodEngine3D::lightEntity_setColor(const string& ID, vec3 color)
{
	p_core->p_lightEntityManager.getEntity(ID)->setColor(color);
}

void WoodEngine3D::lightEntity_setStrength(const string& ID, float strength)
{
	p_core->p_lightEntityManager.getEntity(ID)->setStrength(strength);
}

/* --------------------------------------------- Gui interface --------------------------------------------- */

void WoodEngine3D::guiEntity_deleteAll()
{
	p_core->p_guiEntityManager.deleteEntities();
}

void WoodEngine3D::guiEntity_hideAll()
{
	for (auto& entity : p_core->p_guiEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void WoodEngine3D::guiEntity_showAll()
{
	for (auto& entity : p_core->p_guiEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void WoodEngine3D::guiEntity_add(const string& ID, const string& assetName, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible)
{
	p_core->p_guiEntityManager.addGuiEntity(ID, assetName, translation, rotation, scaling, false, centered);
	p_core->p_guiEntityManager.getEntity(ID)->setEnabled(visible);
}

void WoodEngine3D::guiEntity_add(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible)
{
	p_core->p_guiEntityManager.addGuiEntity(ID, color, translation, rotation, scaling, centered);
	p_core->p_guiEntityManager.getEntity(ID)->setEnabled(visible);
}

void WoodEngine3D::guiEntity_hide(const string& ID)
{
	p_core->p_guiEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::guiEntity_show(const string& ID)
{
	p_core->p_guiEntityManager.getEntity(ID)->setEnabled(true);
}

void WoodEngine3D::guiEntity_delete(const string& ID)
{
	p_core->p_guiEntityManager.deleteEntity(ID);
}

void WoodEngine3D::guiEntity_changeTexture(const string& ID, const string& assetName)
{
	p_core->p_guiEntityManager.getEntity(ID)->setDiffuseMap(p_core->p_texLoader.getTexture("../Game/Textures/GuiMaps/" + assetName, true, true));
}

bool WoodEngine3D::guiEntity_isExisting(const string& ID)
{
	return p_core->p_guiEntityManager.isExisting(ID);
}

void WoodEngine3D::guiEntity_setPosition(const string& ID, vec2 position)
{
	p_core->p_guiEntityManager.getEntity(ID)->setTranslation(position);
}

void WoodEngine3D::guiEntity_setRotation(const string& ID, float rotation)
{
	p_core->p_guiEntityManager.getEntity(ID)->setRotation(rotation);
}

void WoodEngine3D::guiEntity_setSize(const string& ID, vec2 size)
{
	p_core->p_guiEntityManager.getEntity(ID)->setScaling(size);
}

void WoodEngine3D::guiEntity_move(const string& ID, vec2 position)
{
	p_core->p_guiEntityManager.getEntity(ID)->translate(position, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::guiEntity_rotate(const string& ID, float rotation)
{
	p_core->p_guiEntityManager.getEntity(ID)->rotate(rotation, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::guiEntity_scale(const string& ID, vec2 size)
{
	p_core->p_guiEntityManager.getEntity(ID)->scale(size, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::guiEntity_setColor(const string& ID, vec3 color)
{
	p_core->p_guiEntityManager.getEntity(ID)->setColor(color);
}

vec2 WoodEngine3D::guiEntity_getPosition(const string& ID)
{
	return p_core->p_guiEntityManager.getEntity(ID)->getTranslation();
}

float WoodEngine3D::guiEntity_getRotation(const string& ID)
{
	return p_core->p_guiEntityManager.getEntity(ID)->getRotation();
}

vec2 WoodEngine3D::guiEntity_getSize(const string& ID)
{
	return p_core->p_guiEntityManager.getEntity(ID)->getScaling();
}

bool WoodEngine3D::guiEntity_isVisible(const string& ID)
{
	return p_core->p_guiEntityManager.getEntity(ID)->isEnabled();
}

/* --------------------------------------------- Text interface --------------------------------------------- */

void WoodEngine3D::textEntity_deleteAll()
{
	p_core->p_textEntityManager.deleteEntities();
}

void WoodEngine3D::textEntity_hideAll()
{
	for (auto& entity : p_core->p_textEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void WoodEngine3D::textEntity_showAll()
{
	for (auto& entity : p_core->p_textEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void WoodEngine3D::textEntity_add(const string& ID, const string& text, const string& fontName, vec3 color, vec2 position, float rotation, vec2 size, bool centered)
{
	p_core->p_textEntityManager.addTextEntity(ID, text, fontName, color, position, rotation, size, false, false, centered);
}

void WoodEngine3D::textEntity_delete(const string& ID)
{
	p_core->p_textEntityManager.deleteEntity(ID);
}

bool WoodEngine3D::textEntity_isExisting(const string& ID)
{
	return p_core->p_textEntityManager.isExisting(ID);
}

void WoodEngine3D::textEntity_changeText(const string& ID, const string& text, float charWidth, vec3 color)
{
	auto entity = p_core->p_textEntityManager.getEntity(ID);

	entity->setText(text);
	entity->setColor(color);
	entity->setScaling(vec2(charWidth*float(text.size()), entity->getScaling().y));
	entity->setDiffuseMap(p_core->p_texLoader.getText(text, "../Game/Fonts/" + entity->getFontName()));
}

void WoodEngine3D::textEntity_hide(const string& ID)
{
	p_core->p_textEntityManager.getEntity(ID)->setEnabled(false);
}

void WoodEngine3D::textEntity_show(const string& ID)
{
	p_core->p_textEntityManager.getEntity(ID)->setEnabled(true);
}

void WoodEngine3D::textEntity_setPosition(const string& ID, vec2 position)
{
	p_core->p_textEntityManager.getEntity(ID)->setTranslation(position);
}

void WoodEngine3D::textEntity_setRotation(const string& ID, float rotation)
{
	p_core->p_textEntityManager.getEntity(ID)->setRotation(rotation);
}

void WoodEngine3D::textEntity_setSize(const string& ID, vec2 size)
{
	p_core->p_textEntityManager.getEntity(ID)->setScaling(size);
}

void WoodEngine3D::textEntity_move(const string& ID, vec2 position)
{
	p_core->p_textEntityManager.getEntity(ID)->translate(position, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::textEntity_rotate(const string& ID, float rotation)
{
	p_core->p_textEntityManager.getEntity(ID)->rotate(rotation, p_core->p_timer.getDeltaTime());
}

void WoodEngine3D::textEntity_scale(const string& ID, vec2 size)
{
	p_core->p_textEntityManager.getEntity(ID)->scale(size, p_core->p_timer.getDeltaTime());
}

vec2 WoodEngine3D::textEntity_getPosition(const string& ID)
{
	return p_core->p_textEntityManager.getEntity(ID)->getTranslation();
}

float WoodEngine3D::textEntity_getRotation(const string& ID)
{
	return p_core->p_textEntityManager.getEntity(ID)->getRotation();
}

vec2 WoodEngine3D::textEntity_getSize(const string& ID)
{
	return p_core->p_textEntityManager.getEntity(ID)->getScaling();
}

string WoodEngine3D::textEntity_getText(const string& ID)
{
	return p_core->p_textEntityManager.getEntity(ID)->getText();
}

/* --------------------------------------------- Graphics interface --------------------------------------------- */

void WoodEngine3D::gfx_addAmbientLighting(float strength)
{
	p_core->p_shaderBus.setAmbLightEnabled(true);

	// Sky overrides
	if (p_core->p_skyEntityManager.getSelectedSky() == nullptr)
	{
		p_core->p_shaderBus.setAmbLightStrength(strength);
	}
}

void WoodEngine3D::gfx_addDirectionalLighting(vec3 position, float strength)
{
	p_core->p_shaderBus.setDirLightEnabled(true);
	p_core->p_shaderBus.setDirLightPos(position);
	p_core->p_shaderBus.setDirLightStrength(strength);

	// Sky overrides
	if (p_core->p_skyEntityManager.getSelectedSky() == nullptr)
	{
		p_core->p_shaderBus.setAmbLightStrength(strength);
	}
}

void WoodEngine3D::gfx_addSpecularLighting(float shininess)
{
	p_core->p_shaderBus.setSpecLightEnabled(true);
	p_core->p_shaderBus.setSpecLightStrength(shininess);
}

void WoodEngine3D::gfx_addPointLighting()
{
	p_core->p_shaderBus.setPointLightEnabled(true);
}

void WoodEngine3D::gfx_addFog(float minDistance)
{
	p_core->p_shaderBus.setFogEnabled(true);
	p_core->p_shaderBus.setFogMinDistance(minDistance);
}

void WoodEngine3D::gfx_addSkyReflections(float factor)
{
	p_core->p_shaderBus.setSkyReflectionsEnabled(true);
	p_core->p_shaderBus.setSkyReflectionFactor(factor);
}

void WoodEngine3D::gfx_addSSR(float height, float factor)
{
	// Check if water is already using reflection graphics
	if (p_core->p_shaderBus.isWaterEffectsEnabled())
	{
		Logger::getInst().throwWarning("Cannot enable SSR graphics; \"water effects\" is currently using it!");
	}
	else
	{
		p_core->p_shaderBus.setSSREnabled(true);
		p_core->p_shaderBus.setSSRHeight(height);
		p_core->p_shaderBus.setSSRFactor(factor);
	}

}

void WoodEngine3D::gfx_addLightMapping()
{
	p_core->p_shaderBus.setLightMappingEnabled(true);
}

void WoodEngine3D::gfx_addMSAA()
{
	p_core->p_shaderBus.setMSAAEnabled(true);
}

void WoodEngine3D::gfx_addShadows(vec3 eye, vec3 center, float size, float reach)
{
	p_core->p_shadowManager.loadShadows(eye, center, size, reach);
	p_core->p_shaderBus.setShadowsEnabled(true);
}

void WoodEngine3D::gfx_addBloom(float intensity, float brightnessTreshold, int blurSize)
{
	p_core->p_shaderBus.setBloomEnabled(true);
	p_core->p_shaderBus.setBloomIntensity(intensity);
	p_core->p_shaderBus.setBloomTreshold(brightnessTreshold);
	p_core->p_shaderBus.setBloomBlurSize(blurSize);
}

void WoodEngine3D::gfx_addWaterEffects()
{
	p_core->p_shaderBus.setWaterEffectsEnabled(true);
}

void WoodEngine3D::gfx_addSkyHDR()
{
	p_core->p_shaderBus.setSkyHdrEnabled(true);
}

void WoodEngine3D::gfx_addDOF(float minDistance)
{
	p_core->p_shaderBus.setDofEnabled(true);
	p_core->p_shaderBus.setDofMinDistance(minDistance);
}

void WoodEngine3D::gfx_addMotionBlur()
{
	p_core->p_shaderBus.setMotionBlurEnabled(true);
}

void WoodEngine3D::gfx_removeAmbientLighting()
{
	p_core->p_shaderBus.setAmbLightEnabled(false);
}

void WoodEngine3D::gfx_removeDirectionalLighting()
{
	p_core->p_shaderBus.setDirLightEnabled(false);
}

void WoodEngine3D::gfx_removeSpecularLighting()
{
	p_core->p_shaderBus.setSpecLightEnabled(false);
}

void WoodEngine3D::gfx_removePointLighting()
{
	p_core->p_shaderBus.setPointLightEnabled(false);
}

void WoodEngine3D::gfx_removeFog()
{
	p_core->p_shaderBus.setFogEnabled(false);
}

void WoodEngine3D::gfx_removeSkyReflections()
{
	p_core->p_shaderBus.setSkyReflectionsEnabled(false);
}

void WoodEngine3D::gfx_removeSSR()
{
	p_core->p_shaderBus.setSSREnabled(false);
}

void WoodEngine3D::gfx_removeLightMapping()
{
	p_core->p_shaderBus.setLightMappingEnabled(false);
}

void WoodEngine3D::gfx_removeMSAA()
{
	p_core->p_shaderBus.setMSAAEnabled(false);
}

void WoodEngine3D::gfx_removeShadows()
{
	p_core->p_shaderBus.setShadowsEnabled(false);
}

void WoodEngine3D::gfx_removeBloom()
{
	p_core->p_shaderBus.setBloomEnabled(false);
}

void WoodEngine3D::gfx_removeWaterEffects()
{
	p_core->p_shaderBus.setWaterEffectsEnabled(false);
}

void WoodEngine3D::gfx_removeSkyHDR()
{
	p_core->p_shaderBus.setSkyHdrEnabled(false);
}

void WoodEngine3D::gfx_removeDOF()
{
	p_core->p_shaderBus.setDofEnabled(false);
}

void WoodEngine3D::gfx_removeMotionBlur()
{
	p_core->p_shaderBus.setMotionBlurEnabled(false);
}

void WoodEngine3D::gfx_setSkyBrightness(float brightness)
{
	p_core->p_shaderBus.setSkyBrightness(brightness);
}

float WoodEngine3D::gfx_getSkyBrightness()
{
	return p_core->p_shaderBus.getSkyBrightness();
}

/* --------------------------------------------- Input interface --------------------------------------------- */

bool WoodEngine3D::input_getKeyDown(Input keyName)
{
	return p_core->p_inputHandler.getKeyDown(keyName);
}

bool WoodEngine3D::input_getKeyPressed(Input keyName)
{
	return p_core->p_inputHandler.getKeyPressed(keyName);
}

bool WoodEngine3D::input_getKeyToggled(Input keyName)
{
	return p_core->p_inputHandler.getKeyToggled(keyName);
}

bool WoodEngine3D::input_getMouseDown(Input mouseButton)
{
	return p_core->p_inputHandler.getMouseDown(mouseButton);
}

bool WoodEngine3D::input_getMousePressed(Input mouseButton)
{
	return p_core->p_inputHandler.getMousePressed(mouseButton);
}

bool WoodEngine3D::input_getMouseToggled(Input mouseButton)
{
	return p_core->p_inputHandler.getMouseToggled(mouseButton);
}

int WoodEngine3D::input_getMouseWheelX()
{
	return p_core->p_inputHandler.getMouseWheelX();
}

int WoodEngine3D::input_getMouseWheelY()
{
	return p_core->p_inputHandler.getMouseWheelY();
}

void WoodEngine3D::audioEntity_setSoundEnabled(bool val)
{
	p_core->p_audioPlayer.setSoundEnabled(val);
}

void WoodEngine3D::audioEntity_setMusicEnabled(bool val)
{
	p_core->p_audioPlayer.setMusicEnabled(val);
}

/* --------------------------------------------- Audio interface --------------------------------------------- */

void WoodEngine3D::audioEntity_deleteAllSounds()
{
	audioEntity_stopAllSounds();
	p_core->p_audioManager.deleteAllChunks();
}

void WoodEngine3D::audioEntity_deleteAllMusic()
{
	audioEntity_stopAllMusic();
	p_core->p_audioManager.deleteAllMusic();
}

void WoodEngine3D::audioEntity_stopAllSounds()
{
	p_core->p_audioPlayer.stopAllSounds();
}

void WoodEngine3D::audioEntity_stopAllMusic()
{
	p_core->p_audioPlayer.stopAllMusic();
}

void WoodEngine3D::audioEntity_addMusic(const std::string& fileName)
{
	p_core->p_audioManager.addMusic(fileName);
}

void WoodEngine3D::audioEntity_deleteMusic()
{
	p_core->p_audioManager.removeMusic();
}

void WoodEngine3D::audioEntity_setMusicVolume(int volume)
{
	volume = std::clamp(volume, 0, 100);
	p_core->p_audioPlayer.setMusicVolume(int((float(volume) / 100.0f) * 128.0f));
}

void WoodEngine3D::audioEntity_addGlobal(const std::string& ID, const std::string& fileName)
{
	p_core->p_audioManager.addGlobalChunk(ID, fileName);
}

void WoodEngine3D::audioEntity_addPoint(const std::string& ID, const std::string& fileName, vec3 position, float maxDistance)
{
	p_core->p_audioManager.addPointChunk(ID, fileName, position, maxDistance);
}

void WoodEngine3D::audioEntity_delete(const std::string& ID)
{
	if (p_core->p_audioManager.isChunkExisting(ID)) // If chunk exists
	{
		if (p_core->p_audioPlayer.isPlaying(p_core->p_audioManager.getChunk(ID))) // If chunk is playing
		{
			p_core->p_audioPlayer.stopChunk(p_core->p_audioManager.getChunk(ID), 0);
		}
	}

	p_core->p_audioManager.removeChunk(ID);
}

void WoodEngine3D::audioEntity_play(const std::string& ID, int loops, int initialVolume, bool noRestart, int fadeMillis)
{
	initialVolume = std::clamp(initialVolume, 0, 100);
	p_core->p_audioPlayer.playChunk(p_core->p_audioManager.getChunk(ID), loops, int((float(initialVolume) / 100.0f) * 128.0f), noRestart, fadeMillis);
}

void WoodEngine3D::audioEntity_pause(const std::string& ID)
{
	p_core->p_audioPlayer.pauseChunk(p_core->p_audioManager.getChunk(ID));
}

void WoodEngine3D::audioEntity_resume(const std::string& ID)
{
	p_core->p_audioPlayer.resumeChunk(p_core->p_audioManager.getChunk(ID));
}

void WoodEngine3D::audioEntity_stop(const std::string& ID, int fadeMillis)
{
	p_core->p_audioPlayer.stopChunk(p_core->p_audioManager.getChunk(ID), fadeMillis);
}

void WoodEngine3D::audioEntity_setVolume(const std::string& ID, int volume)
{
	volume = std::clamp(volume, 0, 100);
	p_core->p_audioPlayer.setChunkVolume(p_core->p_audioManager.getChunk(ID), int((float(volume) / 100.0f) * 128.0f));
}

void WoodEngine3D::audioEntity_changePoint(const std::string& ID, vec3 position)
{
	p_core->p_audioManager.getChunk(ID).setPosition(position);
}

bool WoodEngine3D::audioEntity_isPlaying(const std::string& ID)
{
	return p_core->p_audioPlayer.isPlaying(p_core->p_audioManager.getChunk(ID));
}

int WoodEngine3D::audioEntity_getVolume(const std::string& ID)
{
	return p_core->p_audioPlayer.getVolume(p_core->p_audioManager.getChunk(ID));
}

int WoodEngine3D::audioEntity_getUsedChannelCount()
{
	return p_core->p_audioPlayer.getUsedChannelCount();
}

/* --------------------------------------------- Miscellaneous interface --------------------------------------------- */

int WoodEngine3D::misc_getUniqueInt()
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

int WoodEngine3D::misc_getWindowWidth()
{
	return Config::getInst().getWindowWidth();
}

int WoodEngine3D::misc_getWindowHeight()
{
	return Config::getInst().getWindowHeight();
}

int WoodEngine3D::misc_getRandomInt(int min, int max)
{
	return Tools::getInst().getRandomInt(min, max);
}

int WoodEngine3D::misc_getMsTimeSinceEpoch()
{
	using namespace std::chrono;
	return int(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

float WoodEngine3D::misc_getRandomFloat(float min, float max)
{
	return Tools::getInst().getRandomFloat(min, max);
}

float WoodEngine3D::misc_getAspectRatio()
{
	return float(misc_getWindowWidth()) / float(misc_getWindowHeight());
}

void WoodEngine3D::misc_showCursor()
{
	p_core->p_windowManager.showMouseCursor();
}

void WoodEngine3D::misc_hideCursor()
{
	p_core->p_windowManager.hideMouseCursor();
}

void WoodEngine3D::misc_enableWireframeRendering()
{
	p_core->p_shaderBus.setWireframeEnabled(true);
}

void WoodEngine3D::misc_disableWireframeRendering()
{
	p_core->p_shaderBus.setWireframeEnabled(false);
}

void WoodEngine3D::misc_enableDebugRendering()
{
	p_core->p_shaderBus.setDebugRenderEnabled(true);
}

void WoodEngine3D::misc_disableDebugRendering()
{
	p_core->p_shaderBus.setDebugRenderEnabled(false);
}

void WoodEngine3D::misc_setMousePos(ivec2 pos)
{
	p_core->p_mousePicker.update(pos, p_core->p_terrainEntityManager);
	p_core->p_windowManager.setMousePos(pos);
}

void WoodEngine3D::misc_preLoadGameEntity(const std::string& assetName, bool lightMapped, bool reflective)
{
	// Load OBJ model
	auto parts = p_core->p_objLoader.loadOBJ(assetName);

	// Create OpenGL buffers
	for (auto& part : parts)
	{
		// Diffuse map
		p_core->p_texLoader.getTexture("../Game/Textures/DiffuseMaps/" + part.textureName, true, true);

		// Light map
		if (lightMapped)
		{
			p_core->p_texLoader.getTexture("../Game/Textures/LightMaps/" + part.textureName, false, false);
		}

		// Reflection map
		if (reflective)
		{
			p_core->p_texLoader.getTexture("../Game/Textures/ReflectionMaps/" + part.textureName, false, false);
		}
	}
}

void WoodEngine3D::misc_showPerformanceProfiling()
{
	p_core->p_showStats = true;
}

void WoodEngine3D::misc_hidePerformanceProfiling()
{
	p_core->p_showStats = false;
	
	vector<string> elements =
	{
		"inputHandle", "gameUpdates", "raycastUpdates", "physicsUpdates", "cameraUpdates", "entityUpdates", "shadowUpdates", "audioUpdates",
		"renderSwap", "SSRPreRender", "waterPreRender", "shadowPreRender", "depthPreRender", "skyEntity", "terrainEntity", "waterEntity",
		"gameEntities", "bBoardEntities", "aabbEntities", "postProcessing", "guiRender", "textRender", "misc", "fps"
	};

	for (auto& e : elements)
	{
		if (p_core->p_textEntityManager.isExisting(e))
		{
			p_core->p_textEntityManager.getEntity(e)->setEnabled(false);
		}
	}
}

void WoodEngine3D::misc_showAudioDebugging()
{
	p_core->p_audioPlayer.setChannelDebugging(true);
}

void WoodEngine3D::misc_hideAudioDebugging()
{
	p_core->p_audioPlayer.setChannelDebugging(false);
}

string WoodEngine3D::misc_vec2str(vec2 vec)
{
	return std::to_string(vec.x) + " " + std::to_string(vec.y);
}

string WoodEngine3D::misc_vec2str(vec3 vec)
{
	return std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
}

string WoodEngine3D::misc_vec2str(vec4 vec)
{
	return std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z) + " " + std::to_string(vec.w);
}

ivec2 WoodEngine3D::misc_getMousePos()
{
	return p_core->p_windowManager.getMousePos();
}

vec2 WoodEngine3D::misc_convertToNDC(ivec2 pos)
{
	float x = float(pos.x) / float(misc_getWindowWidth());
	float y = float(pos.y) / float(misc_getWindowHeight());
	x = (x * 2.0f) - 1.0f;
	y = (y * 2.0f) - 1.0f;
	y *= -1.0f;
	
	return vec2(x, y);
}

ivec2 WoodEngine3D::misc_convertFromNDC(vec2 pos)
{
	pos.y *= -1.0f;
	pos.x += 1.0f;
	pos.x /= 2.0f;
	pos.y += 1.0f;
	pos.y /= 2.0f;
	float x = float(pos.x) * float(misc_getWindowWidth());
	float y = float(pos.y) * float(misc_getWindowHeight());

	return ivec2(int(x), int(y));
}

bool WoodEngine3D::world_check(const string& worldName)
{
	return p_core->p_worldEditor.checkWorld(worldName);
}

void WoodEngine3D::world_load(const string& worldName)
{
	p_core->p_worldEditor.loadWorld(worldName);
}

void WoodEngine3D::world_export(const string& worldName)
{
	p_core->p_worldEditor.exportWorld(worldName);
}
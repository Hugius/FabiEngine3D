#pragma once

#include "logger.hpp"
#include "input_type.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"
#include "network_client_message.hpp"
#include "network_server_message.hpp"
#include "mathematics.hpp"

#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>

using std::array;
using std::vector;
using std::set;
using std::map;
using std::unordered_map;
using std::pair;
using std::string;
using std::shared_ptr;
using std::reverse;
using std::to_string;
using std::make_shared;
using std::make_pair;

class CoreEngine;

class FabiEngine3D
{
	friend class CoreEngine;

public:
	FabiEngine3D();
	virtual ~FabiEngine3D();

	// Engine interface
	void application_start();
	void application_pause();
	void application_resume();
	void application_stop();
	bool application_isPaused();
	bool application_isExported();
	const string& application_getTitle();

	// Input interface - setters
	void input_setLocked(bool locked);
	void input_clearKeyToggles();
	void input_clearMouseToggles();
	void input_setKeyTogglingLocked(bool locked);
	void input_setMouseTogglingLocked(bool locked);

	// Input interface - getters
	const bool input_isKeyDown(InputType keyName);
	const bool input_isKeyPressed(InputType keyName);
	const bool input_isKeyToggled(InputType keyName);
	const bool input_isMouseDown(InputType mouseButton);
	const bool input_isMousePressed(InputType mouseButton);
	const bool input_isMouseToggled(InputType mouseButton);
	const int input_getMouseWheelX();
	const int input_getMouseWheelY();

	// Camera interface - setters
	void camera_load(float fov, float nearZ, float farZ, Vec3 startPosition, float yaw, float pitch);
	void camera_enableLookatView();
	void camera_disableLookatView();
	void camera_enableFirstPersonView();
	void camera_disableFirstPersonView();
	void camera_translateFollowX(float speed);
	void camera_translateFollowZY(float speed);
	void camera_translateFollowZ(float speed);
	void camera_translate(Vec3 translation);
	void camera_setPosition(Vec3 position);
	void camera_setLookatPosition(Vec3 position);
	void camera_lockYaw();
	void camera_unlockYaw();
	void camera_lockPitch();
	void camera_unlockPitch();
	void camera_setFOV(float fov);
	void camera_setMouseSensitivity(float speed);
	void camera_setYaw(float yaw);
	void camera_setPitch(float pitch);
	void camera_setNearDistance(float nearZ);
	void camera_setFarDistance(float farZ);
	void camera_setMaxPitch(float pitch);

	// Camera interface - getters
	const bool camera_isLookatViewEnabled();
	const bool camera_isFirstPersonViewEnabled();
	const Vec3 camera_getPosition();
	const Vec3 camera_getLookatPosition();
	const float camera_getFOV();
	const float getAspectRatio();
	const float camera_getMouseSensitivity();
	const float camera_getYaw();
	const float camera_getPitch();
	const float camera_getNearDistance();
	const float camera_getFarDistance();
	const float camera_getMouseOffset();
	const float camera_getMaxPitch();

	// Sky entity interface - setters
	void skyEntity_add(const string& ID);
	void skyEntity_deleteAll();
	void skyEntity_delete(const string& ID);
	void skyEntity_hide(const string& ID);
	void skyEntity_show(const string& ID);
	void skyEntity_select(const string& ID);
	void skyEntity_setDiffuseMaps(const string& ID, const array<string, 6>& texturePaths);
	void skyEntity_setDiffuseMapRight(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapLeft(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapTop(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapBottom(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapBack(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapFront(const string& ID, const string& texturePath);
	void skyEntity_setLightness(const string& ID, float lightness);
	void skyEntity_setRotationSpeed(const string& ID, float speed);
	void skyEntity_setColor(const string& ID, Vec3 color);
	void skyEntity_mixWithSelected(const string& ID);
	void skyEntity_setMixValue(float mixValue);

	// Sky entity interface - getters
	const bool skyEntity_isExisting(const string& ID);
	const bool skyEntity_isVisible(const string& ID);
	const string skyEntity_getSelectedID();
	const vector<string> skyEntity_getAllIDs();
	const array<string, 6>& skyEntity_getDiffuseMapPaths(const string& ID);
	const float skyEntity_getLightness(const string& ID);
	const float skyEntity_getOriginalLightness(const string& ID);
	const float skyEntity_getRotationSpeed(const string& ID);
	const float skyEntity_getMixValue();
	const Vec3 skyEntity_getColor(const string& ID);

	// Terrain entity interface - setters
	void terrainEntity_add(const string& ID, const string& heightMapPath);
	void terrainEntity_deleteAll();
	void terrainEntity_delete(const string& ID);
	void terrainEntity_hide(const string& ID);
	void terrainEntity_show(const string& ID);
	void terrainEntity_select(const string& ID);
	void terrainEntity_setHeightmap(const string& ID, const string& heightMapPath);
	void terrainEntity_setMaxHeight(const string& ID, float height);
	void terrainEntity_setUvRepeat(const string& ID, float repeat);
	void terrainEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMap(const string& ID, const string& texturePath);
	void terrainEntity_setLightness(const string& ID, float lightness);
	void terrainEntity_setBlendMapped(const string& ID, bool enabled);
	void terrainEntity_setNormalMapped(const string& ID, bool enabled);
	void terrainEntity_setNormalMappedR(const string& ID, bool enabled);
	void terrainEntity_setNormalMappedG(const string& ID, bool enabled);
	void terrainEntity_setNormalMappedB(const string& ID, bool enabled);
	void terrainEntity_setSpecularLighted(const string& ID, bool enabled);
	void terrainEntity_setBlendMap(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMapR(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMapG(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMapB(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMapR(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMapG(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMapB(const string& ID, const string& texturePath);
	void terrainEntity_setBlendRepeatR(const string& ID, float repeat);
	void terrainEntity_setBlendRepeatG(const string& ID, float repeat);
	void terrainEntity_setBlendRepeatB(const string& ID, float repeat);
	void terrainEntity_setSpecularLightingFactor(const string& ID, float factor);
	void terrainEntity_setSpecularLightingIntensity(const string& ID, float intensity);

	// Terrain entity interface - getters
	const bool terrainEntity_isExisting(const string& ID);
	const bool terrainEntity_isVisible(const string& ID);
	const bool terrainEntity_isBlendMapped(const string& ID);
	const bool terrainEntity_isNormalMapped(const string& ID);
	const bool terrainEntity_isNormalMappedR(const string& ID);
	const bool terrainEntity_isNormalMappedG(const string& ID);
	const bool terrainEntity_isNormalMappedB(const string& ID);
	const bool terrainEntity_isSpecularLighted(const string& ID);
	const bool terrainEntity_isInside(const string& ID, float x, float z);
	const string terrainEntity_getSelectedID();
	const vector<string> terrainEntity_getAllIDs();
	const string& terrainEntity_getDiffuseMapPath(const string& ID);
	const string& terrainEntity_getNormalMapPath(const string& ID);
	const string& terrainEntity_getHeightMapPath(const string& ID);
	const string& terrainEntity_getBlendMapPath(const string& ID);
	const string& terrainEntity_getBlendMapPathR(const string& ID);
	const string& terrainEntity_getBlendMapPathG(const string& ID);
	const string& terrainEntity_getBlendMapPathB(const string& ID);
	const string& terrainEntity_getNormalMapPathR(const string& ID);
	const string& terrainEntity_getNormalMapPathG(const string& ID);
	const string& terrainEntity_getNormalMapPathB(const string& ID);
	const float terrainEntity_getMaxHeight(const string& ID);
	const float terrainEntity_getUvRepeat(const string& ID);
	const float terrainEntity_getLightness(const string& ID);
	const float terrainEntity_getBlendRepeatR(const string& ID);
	const float terrainEntity_getBlendRepeatG(const string& ID);
	const float terrainEntity_getBlendRepeatB(const string& ID);
	const float terrainEntity_getSize(const string& ID);
	const float terrainEntity_getPixelHeight(const string& ID, float x, float z);
	const float terrainEntity_getSpecularLightingFactor(const string& ID);
	const float terrainEntity_getSpecularLightingIntensity(const string& ID);

	// Water entity interface - setters
	void waterEntity_add(const string& ID);
	void waterEntity_deleteAll();
	void waterEntity_delete(const string& ID);
	void waterEntity_hide(const string& ID);
	void waterEntity_show(const string& ID);
	void waterEntity_select(const string& ID);
	void waterEntity_setSpeed(const string& ID, Vec2 speed);
	void waterEntity_setPosition(const string& ID, Vec3 position);
	void waterEntity_setSize(const string& ID, float size);
	void waterEntity_setWaving(const string& ID, bool enabled);
	void waterEntity_setRippling(const string& ID, bool enabled);
	void waterEntity_setSpecularLighted(const string& ID, bool enabled);
	void waterEntity_setReflective(const string& ID, bool enabled);
	void waterEntity_setRefractive(const string& ID, bool enabled);
	void waterEntity_setDudvMap(const string& ID, const string& texturePath);
	void waterEntity_setNormalMap(const string& ID, const string& texturePath);
	void waterEntity_setDisplacementMap(const string& ID, const string& texturePath);
	void waterEntity_setWaveHeightFactor(const string& ID, float factor);
	void waterEntity_setSpecularLightingFactor(const string& ID, float factor);
	void waterEntity_setSpecularLightingIntensity(const string& ID, float intensity);
	void waterEntity_setTransparency(const string& ID, float transparency);
	void waterEntity_setColor(const string& ID, Vec3 color);
	void waterEntity_setUvRepeat(const string& ID, float repeat);

	// Water entity interface - getters
	const bool waterEntity_isExisting(const string& ID);
	const bool waterEntity_isVisible(const string& ID);
	const bool waterEntity_isWaving(const string& ID);
	const bool waterEntity_isRippling(const string& ID);
	const bool waterEntity_isSpecularLighted(const string& ID);
	const bool waterEntity_isReflective(const string& ID);
	const bool waterEntity_isRefractive(const string& ID);
	const Vec2 waterEntity_getSpeed(const string& ID);
	const Vec3 waterEntity_getPosition(const string& ID);
	const Vec3 waterEntity_getColor(const string& ID);
	const float waterEntity_getSize(const string& ID);
	const float waterEntity_getUvRepeat(const string& ID);
	const float waterEntity_getWaveHeightFactor(const string& ID);
	const float waterEntity_getSpecularLightingFactor(const string& ID);
	const float waterEntity_getSpecularLightingIntensity(const string& ID);
	const float waterEntity_getTransparency(const string& ID);
	const string& waterEntity_getDudvMapPath(const string& ID);
	const string& waterEntity_getNormalMapPath(const string& ID);
	const string& waterEntity_getDisplacementMapPath(const string& ID);
	const string waterEntity_getSelectedID();
	const vector<string> waterEntity_getAllIDs();

	// Model entity interface - setters
	void modelEntity_add
	(
		const string& ID, const string& meshPath,
		Vec3 position, Vec3 rotation, Vec3 size, bool visible = true
	);
	void modelEntity_deleteAll();
	void modelEntity_delete(const string& ID);
	void modelEntity_deleteGroup(const string& ID);
	void modelEntity_hideAll();
	void modelEntity_showAll();
	void modelEntity_hide(const string& ID);
	void modelEntity_show(const string& ID);
	void modelEntity_loadModel(const string& ID, const string& meshPath);
	void modelEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void modelEntity_setLightMap(const string& ID, const string& texturePath);
	void modelEntity_setNormalMap(const string& ID, const string& texturePath);
	void modelEntity_setReflectionMap(const string& ID, const string& texturePath);
	void modelEntity_setLevelOfDetailEntity(const string& ID, const string& lodID);
	void modelEntity_setTransparent(const string& ID, bool enabled);
	void modelEntity_setFaceCulled(const string& ID, bool enabled);
	void modelEntity_setLightMapped(const string& ID, bool enabled);
	void modelEntity_setNormalMapped(const string& ID, bool enabled);
	void modelEntity_setSkyReflective(const string& ID, bool enabled);
	void modelEntity_setSpecularLighted(const string& ID, bool enabled);
	void modelEntity_setSceneReflective(const string& ID, bool enabled);
	void modelEntity_setShadowed(const string& ID, bool enabled);
	void modelEntity_setDepthMapIncluded(const string& ID, bool enabled);
	void modelEntity_setStaticToCamera(const string& ID, bool enabled);
	void modelEntity_setWireframed(const string& ID, bool enabled);
	void modelEntity_move(const string& ID, Vec3 factor, const string& partID = "");
	void modelEntity_rotate(const string& ID, Vec3 factor, const string& partID = "");
	void modelEntity_scale(const string& ID, Vec3 factor, const string& partID = "");
	void modelEntity_setPosition(const string& ID, Vec3 position, const string& partID = "");
	void modelEntity_setRotation(const string& ID, Vec3 rotation, const string& partID = "");
	void modelEntity_setRotationOrigin(const string& ID, Vec3 rotationOrigin, const string& partID = "");
	void modelEntity_setSize(const string& ID, Vec3 size, const string& partID = "");
	void modelEntity_setSpecularFactor(const string& ID, float intensity);
	void modelEntity_setSpecularIntensity(const string& ID, float intensity);
	void modelEntity_setLightness(const string& ID, float lightness);
	void modelEntity_setAlpha(const string& ID, float alpha);
	void modelEntity_setColor(const string& ID, Vec3 color, const string& partID = "");
	void modelEntity_setMinHeight(const string& ID, float height);
	void modelEntity_setMaxHeight(const string& ID, float height);
	void modelEntity_setUvRepeat(const string& ID, float repeat);
	void modelEntity_setInstanced(const string& ID, bool instanced, vector<Vec3> offsets);

	// Model entity interface - getters
	const bool modelEntity_isExisting(const string& ID);
	const bool modelEntity_isVisible(const string& ID);
	const bool modelEntity_isInstanced(const string& ID);
	const bool modelEntity_isMultiParted(const string& ID);
	const bool modelEntity_isTransparent(const string& ID);
	const bool modelEntity_isFaceCulled(const string& ID);
	const bool modelEntity_isLightMapped(const string& ID);
	const bool modelEntity_isNormalMapped(const string& ID);
	const bool modelEntity_isSkyReflective(const string& ID);
	const bool modelEntity_isSpecularLighted(const string& ID);
	const bool modelEntity_isSceneReflective(const string& ID);
	const bool modelEntity_isShadowed(const string& ID);
	const bool modelEntity_isStaticToCamera(const string& ID);
	const bool modelEntity_isWireframed(const string& ID);
	const bool modelEntity_isDepthMapIncluded(const string& ID);
	const bool modelEntity_hasPart(const string& ID, const string& partID);
	const float modelEntity_getLightness(const string& ID);
	const float modelEntity_getSpecularFactor(const string& ID);
	const float modelEntity_getSpecularIntensity(const string& ID);
	const float modelEntity_getAlpha(const string& ID);
	const float modelEntity_getMinHeight(const string& ID);
	const float modelEntity_getMaxHeight(const string& ID);
	const float modelEntity_getUvRepeat(const string& ID);
	const Vec3 modelEntity_getPosition(const string& ID, const string& partID = "");
	const Vec3 modelEntity_getRotation(const string& ID, const string& partID = "");
	const Vec3 modelEntity_getRotationOrigin(const string& ID, const string& partID = "");
	const Vec3 modelEntity_getSize(const string& ID, const string& partID = "");
	const Vec3 modelEntity_getColor(const string& ID, const string& partID = "");
	const string& modelEntity_getMeshPath(const string& ID);
	const string& modelEntity_getDiffuseMapPath(const string& ID);
	const string& modelEntity_getLightMapPath(const string& ID);
	const string& modelEntity_getNormalMapPath(const string& ID);
	const string& modelEntity_getReflectionMapPath(const string& ID);
	const string& modelEntity_getLevelOfDetailEntityID(const string& ID);
	const vector<Vec3>    modelEntity_getInstancedOffsets(const string& ID);
	const vector<string>& modelEntity_getDiffuseMapPaths(const string& ID);
	const vector<string>& modelEntity_getLightMapPaths(const string& ID);
	const vector<string>& modelEntity_getReflectionMapPaths(const string& ID);
	const vector<string>& modelEntity_getNormalMapPaths(const string& ID);
	const vector<string>& modelEntity_getPartIDs(const string& ID);
	const vector<string> modelEntity_getAllIDs();
	const vector<string> modelEntity_getGroupIDs(const string& ID);

	// Billboard entity interface (core) - setters
	void billboardEntity_add
	(
		const string& ID, Vec3 color,
		Vec3 T, Vec3 R, Vec2 S, bool facingCameraX, bool facingCameraY, bool visible = true
	);
	void billboardEntity_deleteAll();
	void billboardEntity_delete(const string& ID);
	void billboardEntity_deleteGroup(const string& ID);
	void billboardEntity_hideAll();
	void billboardEntity_showAll();
	void billboardEntity_hide(const string& ID);
	void billboardEntity_show(const string& ID);
	void billboardEntity_move(const string& ID, Vec3 factor);
	void billboardEntity_rotate(const string& ID, Vec3 factor);
	void billboardEntity_scale(const string& ID, Vec2 factor);
	void billboardEntity_setPosition(const string& ID, Vec3 position);
	void billboardEntity_setRotation(const string& ID, Vec3 rotation);
	void billboardEntity_setSize(const string& ID, Vec2 size);
	void billboardEntity_setColor(const string& ID, Vec3 color);
	void billboardEntity_setCameraFacingX(const string& ID, bool enabled);
	void billboardEntity_setCameraFacingY(const string& ID, bool enabled);
	void billboardEntity_setDepthMapIncluded(const string& ID, bool enabled);
	void billboardEntity_setMinHeight(const string& ID, float height);
	void billboardEntity_setMaxHeight(const string& ID, float height);
	void billboardEntity_setLightness(const string& ID, float lightness);

	// Billboard entity interface (core) - getters
	const float billboardEntity_getLightness(const string& ID);
	const float billboardEntity_getMinHeight(const string& ID);
	const float billboardEntity_getMaxHeight(const string& ID);
	const bool billboardEntity_isExisting(const string& ID);
	const bool billboardEntity_isVisible(const string& ID);
	const bool billboardEntity_isFacingCameraX(const string& ID);
	const bool billboardEntity_isFacingCameraY(const string& ID);
	const bool billboardEntity_isDepthMapIncluded(const string& ID);
	const bool billboardEntity_isInstanced(const string& ID);
	const Vec3 billboardEntity_getPosition(const string& ID);
	const Vec3 billboardEntity_getRotation(const string& ID);
	const Vec2 billboardEntity_getSize(const string& ID);
	const Vec3 billboardEntity_getColor(const string& ID);
	const vector<string> billboardEntity_getAllIDs();
	const vector<Vec3> billboardEntity_getInstancedOffsets(const string& ID);

	// Billboard entity interface (diffuseMap) - setters
	void billboardEntity_add
	(
		const string& ID, const string& diffuseMapPath,
		Vec3 T, Vec3 R, Vec2 S,
		bool transparent, bool facingCameraX, bool facingCameraY, bool visible = true
	);
	void billboardEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void billboardEntity_setTransparent(const string& ID, bool enabled);

	// Billboard entity interface (diffuseMap) - getters
	const string& billboardEntity_getDiffuseMapPath(const string& ID);
	const bool billboardEntity_isTransparent(const string& ID);

	// Billboard entity interface (text) - setters
	void billboardEntity_add
	(
		const string& ID, const string& text,
		const string& fontPath, Vec3 color,
		Vec3 T, Vec3 R, Vec2 S, bool facingCameraX, bool facingCameraY, bool visible = true
	);
	void billboardEntity_setFont(const string& ID, const string& fontPath);
	void billboardEntity_setTextContent(const string& ID, const string& textContent);

	// Billboard entity interface (text) - getters
	const string& billboardEntity_getFontPath(const string& ID);
	const string& billboardEntity_getTextContent(const string& ID);
	
	// Billboard entity interface (sprite animation) - setters
	void billboardEntity_startSpriteAnimation(const string& ID, int loops);
	void billboardEntity_pauseSpriteAnimation(const string& ID);
	void billboardEntity_resumeSpriteAnimation(const string& ID);
	void billboardEntity_stopSpriteAnimation(const string& ID);
	void billboardEntity_setSpriteAnimationRows(const string& ID, unsigned int rows);
	void billboardEntity_setSpriteAnimationColumns(const string& ID, unsigned int columns);
	void billboardEntity_setSpriteAnimationFramestep(const string& ID, unsigned int framestep);
	void billboardEntity_setSpriteAnimationRowIndex(const string& ID, unsigned int index);
	void billboardEntity_setSpriteAnimationColumnIndex(const string& ID, unsigned int index);

	// Billboard entity interface (animation) - getters
	const bool billboardEntity_isSpriteAnimationStarted(const string& ID);
	const bool billboardEntity_isSpriteAnimationPlaying(const string& ID);
	const bool billboardEntity_isSpriteAnimationPaused(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationRows(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationColumns(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationFramestep(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationRowIndex(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationColumnIndex(const string& ID);
	const int billboardEntity_getRemainingSpriteAnimationLoops(const string& ID);

	// AABB entity interface - setters
	void aabbEntity_add(const string& ID, Vec3 position, Vec3 size, bool raycastResponsive, bool collisionResponsive, bool visible = true);
	void aabbEntity_bindToModelEntity(const string& parentID, Vec3 position, Vec3 size, bool raycastResponsive, bool collisionResponsive, const string& customAabbID = "");
	void aabbEntity_bindToBillboardEntity(const string& parentID, bool raycastResponsive, bool collisionResponsive, const string& customAabbID = "");
	void aabbEntity_deleteAll();
	void aabbEntity_delete(const string& ID);
	void aabbEntity_hide(const string& ID);
	void aabbEntity_show(const string& ID);
	void aabbEntity_setRaycastResponsive(const string& ID, bool responsive);
	void aabbEntity_setCollisionResponsive(const string& ID, bool responsive);
	void aabbEntity_setPosition(const string& ID, Vec3 position, bool noLocal = false);
	void aabbEntity_setSize(const string& ID, Vec3 size, bool noLocal = false);
	void aabbEntity_move(const string& ID, Vec3 factor, bool noLocal = false);
	void aabbEntity_scale(const string& ID, Vec3 factor, bool noLocal = false);

	// AABB entity interface - getters
	const Vec3 aabbEntity_getPosition(const string& ID, bool noLocal = false);
	const Vec3 aabbEntity_getSize(const string& ID, bool noLocal = false);
	const bool aabbEntity_isRaycastResponsive(const string& ID);
	const bool aabbEntity_isCollisionResponsive(const string& ID);
	const bool aabbEntity_isExisting(const string& ID);
	const bool aabbEntity_isVisible(const string& ID);
	const vector<string> aabbEntity_getBoundIDs(const string& parentID, bool modelEntity, bool billboardEntity);
	const vector<string> aabbEntity_getAllIDs();
	const string& aabbEntity_getParentID(const string& ID);
	const AabbParentType aabbEntity_getParentType(const string& ID);

	// Global collision interface - setters
	void collision_setCameraBoxSize(float bottom, float top, float left, float right, float front, float back);
	void collision_enableCameraResponse(bool x, bool y, bool z);
	void collision_disableCameraResponse();
	void collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraTerrainResponse();

	// Global collision interface - getters
	const pair<const string, float> collision_checkCursorInAny();
	const pair<bool, float>		  collision_checkCursorInEntity(const string& ID, bool canBeOccluded);
	const pair<const string, float> collision_checkCursorInEntities(const string& ID, bool canBeOccluded, const string& exception = "");
	const bool		 collision_checkCameraWithTerrain();
	const bool		 collision_checkCameraWithEntity(const string& ID);
	const string collision_checkCameraWithAny();
	const string collision_checkCameraWithEntities(const string& ID);
	const bool		 collision_checkCameraWithEntityDirection(const string& ID, Direction direction);
	const bool		 collision_checkCameraWithAnyDirection(Direction direction);
	const bool		 collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction);
	const string collision_checkEntityWithEntities(const string& selfID, const string& otherID);

	// Light entity interface - setters
	void lightEntity_add(const string& ID, Vec3 position = Vec3(0.0f), Vec3 color = Vec3(1.0f), float intensity = 1.0f, float distanceFactor = 1.0f, bool visible = true);
	void lightEntity_deleteAll();
	void lightEntity_delete(const string& ID);
	void lightEntity_hide(const string& ID);
	void lightEntity_show(const string& ID);
	void lightEntity_setPosition(const string& ID, Vec3 position);
	void lightEntity_move(const string& ID, Vec3 factor);
	void lightEntity_setColor(const string& ID, Vec3 color);
	void lightEntity_setIntensity(const string& ID, float intensity);
	void lightEntity_setDistanceFactor(const string& ID, float factor);

	// Light entity interface - getters
	const bool lightEntity_isExisting(const string& ID);
	const bool lightEntity_isVisible(const string& ID);
	const Vec3 lightEntity_getPosition(const string& ID);
	const Vec3 lightEntity_getColor(const string& ID);
	const float lightEntity_getIntensity(const string& ID);
	const float lightEntity_getDistanceFactor(const string& ID);
	const vector<string> lightEntity_getAllIDs();

	// Image entity interface - setters
	void imageEntity_add(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible = true);
	void imageEntity_add(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible = true);
	void imageEntity_deleteAll();
	void imageEntity_delete(const string& ID);
	void imageEntity_hideAll();
	void imageEntity_hide(const string& ID);
	void imageEntity_showAll();
	void imageEntity_show(const string& ID);
	void imageEntity_changeTexture(const string& ID, const string& texturePath);
	void imageEntity_setPosition(const string& ID, Vec2 position);
	void imageEntity_setRotation(const string& ID, float rotation);
	void imageEntity_setSize(const string& ID, Vec2 size);
	void imageEntity_move(const string& ID, Vec2 position);
	void imageEntity_rotate(const string& ID, float rotation);
	void imageEntity_scale(const string& ID, Vec2 size);
	void imageEntity_setColor(const string& ID, Vec3 color);
	void imageEntity_setAlpha(const string& ID, float alpha);
	void imageEntity_setMinPosition(const string& ID, Vec2 minPos);
	void imageEntity_setMaxPosition(const string& ID, Vec2 maxPos);
	void imageEntity_setMirroredHorizontally(const string& ID, bool mirrored);
	void imageEntity_setMirroredVertically(const string& ID, bool mirrored);
	void imageEntity_startSpriteAnimation(const string& ID, int loops);
	void imageEntity_pauseSpriteAnimation(const string& ID);
	void imageEntity_resumeSpriteAnimation(const string& ID);
	void imageEntity_stopSpriteAnimation(const string& ID);
	void imageEntity_setSpriteAnimationRows(const string& ID, int rows);
	void imageEntity_setSpriteAnimationColumns(const string& ID, int columns);
	void imageEntity_setSpriteAnimationFramestep(const string& ID, int framestep);
	void imageEntity_setSpriteAnimationRowIndex(const string& ID, unsigned int index);
	void imageEntity_setSpriteAnimationColumnIndex(const string& ID, unsigned int index);

	// Image entity interface - getters
	const bool imageEntity_isExisting(const string& ID);
	const bool imageEntity_isVisible(const string& ID);
	const bool imageEntity_isCentered(const string& ID);
	const bool imageEntity_isMirroredHorizontally(const string& ID);
	const bool imageEntity_isMirroredVertically(const string& ID);
	const bool imageEntity_isSpriteAnimationStarted(const string& ID);
	const bool imageEntity_isSpriteAnimationPlaying(const string& ID);
	const bool imageEntity_isSpriteAnimationPaused(const string& ID);
	const Vec2 imageEntity_getPosition(const string& ID);
	const Vec2 imageEntity_getSize(const string& ID);
	const Vec2 imageEntity_getMinPosition(const string& ID);
	const Vec2 imageEntity_getMaxPosition(const string& ID);
	const Vec3 imageEntity_getColor(const string& ID);
	const float imageEntity_getRotation(const string& ID);
	const float imageEntity_getAlpha(const string& ID);
	const int imageEntity_getRemainingSpriteAnimationLoops(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationRows(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationColumns(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationFramestep(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationRowIndex(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationColumnIndex(const string& ID);
	const vector<string> imageEntity_getAllIDs();

	// Text entity interface - setters
	void textEntity_add
	(
		const string& ID, const string& textContent,
		const string& fontPath, Vec3 color,
		Vec2 position, float rotation, Vec2 size, bool isCentered, bool isDynamic
	);
	void textEntity_deleteAll();
	void textEntity_delete(const string& ID);
	void textEntity_hideAll();
	void textEntity_hide(const string& ID);
	void textEntity_showAll();
	void textEntity_show(const string& ID);
	void textEntity_setTextContent(const string& ID, const string& textContent, float charWidth = -1.0f, float charHeight = -1.0f);
	void textEntity_setColor(const string& ID, Vec3 color);
	void textEntity_setAlpha(const string& ID, float alpha);
	void textEntity_setPosition(const string& ID, Vec2 position);
	void textEntity_setRotation(const string& ID, float rotation);
	void textEntity_setSize(const string& ID, Vec2 size);
	void textEntity_move(const string& ID, Vec2 position);
	void textEntity_rotate(const string& ID, float rotation);
	void textEntity_scale(const string& ID, Vec2 size);
	void textEntity_setMinPosition(const string& ID, Vec2 minPos);
	void textEntity_setMaxPosition(const string& ID, Vec2 maxPos);

	// Text interface - getters
	const bool textEntity_isExisting(const string& ID);
	const bool textEntity_isVisible(const string& ID);
	const Vec2 textEntity_getPosition(const string& ID);
	const Vec2 textEntity_getSize(const string& ID);
	const Vec2 textEntity_getMinPosition(const string& ID);
	const Vec2 textEntity_getMaxPosition(const string& ID);
	const Vec3 textEntity_getColor(const string& ID);
	const float textEntity_getRotation(const string& ID);
	const float textEntity_getAlpha(const string& ID);
	const string& textEntity_getTextContent(const string& ID);
	const vector<string> textEntity_getAllIDs();

	// Sound entity interface - setters
	void soundEntity_add(const string& ID, const string& audioPath);
	void soundEntity_make3D(const string& ID, Vec3 position, float maxVolume, float maxDistance);
	void soundEntity_delete(const string& ID);
	void soundEntity_deleteAll();
	void soundEntity_play(const string& ID, int loops, int fadeMS, bool forcePlay = false);
	void soundEntity_pause(const string& ID);
	void soundEntity_pauseAll();
	void soundEntity_resume(const string& ID);
	void soundEntity_resumeAll();
	void soundEntity_stop(const string& ID, int fadeMS);
	void soundEntity_stopAll();
	void soundEntity_setPosition(const string& ID, Vec3 position);
	void soundEntity_move(const string& ID, Vec3 factor);
	void soundEntity_setVolume(const string& ID, float volume);
	void soundEntity_setMaxVolume(const string& ID, float volume);
	void soundEntity_setMaxDistance(const string& ID, float maxDistance);

	// Sound entity interface - getters
	const vector<string> soundEntity_getAllIDs();
	const string& soundEntity_getFilePath(const string& ID);
	const Vec3 soundEntity_getPosition(const string& ID);
	const float soundEntity_getMaxDistance(const string& ID);
	const float soundEntity_getVolume(const string& ID);
	const float soundEntity_getMaxVolume(const string& ID);
	const bool soundEntity_isExisting(const string& ID);
	const bool soundEntity_isStarted(const string& ID);
	const bool soundEntity_isPlaying(const string& ID);
	const bool soundEntity_isPaused(const string& ID);
	const bool soundEntity_isLoaded(const string& ID);
	const bool soundEntity_is3D(const string& ID);
	const int soundEntity_getUsedChannelCount();

	// Music interface - setters
	void music_addToPlaylist(const string& audioPath);
	void music_clearPlaylist();
	void music_setVolume(float volume);
	void music_pause();
	void music_resume();

	// Music interface - getters
	const bool music_isStarted();
	const bool music_isPlaying();
	const bool music_isPaused();
	const float music_getVolume();

	// Graphics interface - setters
	void gfx_setMsaaQuality(int quality);
	void gfx_setShadowQuality(int quality);
	void gfx_setReflectionQuality(int quality);
	void gfx_setRefractionQuality(int quality);
	void gfx_enableAmbientLighting(Vec3 color, float intensity);
	void gfx_enableDirectionalLighting(Vec3 position, Vec3 color, float intensity);
	void gfx_enableSpecularLighting();
	void gfx_enablePointLighting();
	void gfx_enableSpotLighting(Vec3 color, float intensity, float angle, float distance);
	void gfx_enableFog(float minDistance, float maxDistance, float thickness, Vec3 color);
	void gfx_enableSkyReflections(float factor);
	void gfx_enableSceneReflections(float factor);
	void gfx_enableLightMapping();
	void gfx_enableNormalMapping();
	void gfx_enableMSAA();
	void gfx_enableShadows(Vec3 eye, Vec3 center, float size, float reach, float lightness, bool followingCamera, bool softShadowing, int interval);
	void gfx_enableBloom(float intensity, float brightnessTreshold, int blurSize);
	void gfx_enableWaterEffects();
	void gfx_enableSkyHDR(float brightnessFactor);
	void gfx_enableDOF(bool dynamic, float maxDistance, float blurDistance);
	void gfx_enableMotionBlur(float strength);
	void gfx_enableLensFlare(const string& texturePath, float intensity, float multiplier);
	void gfx_disableAmbientLighting(bool resetProperties = false);
	void gfx_disableDirectionalLighting(bool resetProperties = false);
	void gfx_disableSpecularLighting(bool resetProperties = false);
	void gfx_disablePointLighting(bool resetProperties = false);
	void gfx_disableSpotLighting(bool resetProperties = false);
	void gfx_disableFog(bool resetProperties = false);
	void gfx_disableSkyReflections(bool resetProperties = false);
	void gfx_disableSceneReflections(bool resetProperties = false);
	void gfx_disableLightMapping(bool resetProperties = false);
	void gfx_disableNormalMapping(bool resetProperties = false);
	void gfx_disableMSAA(bool resetProperties = false);
	void gfx_disableShadows(bool resetProperties = false);
	void gfx_disableBloom(bool resetProperties = false);
	void gfx_disableWaterEffects(bool resetProperties = false);
	void gfx_disableSkyHDR(bool resetProperties = false);
	void gfx_disableDOF(bool resetProperties = false);
	void gfx_disableMotionBlur(bool resetProperties = false);
	void gfx_disableLensFlare(bool resetProperties = false);
	
	// Graphics interface - getters
	const Vec3 gfx_getDirectionalLightingPosition();
	const Vec3 gfx_getAmbientLightingColor();
	const Vec3 gfx_getDirectionalLightingColor();
	const Vec3 gfx_getSpotLightingColor();
	const Vec3 gfx_getFogColor();
	const Vec3 gfx_getShadowEye();
	const Vec3 gfx_getShadowCenter();
	const string& gfx_getLensFlareMapPath();
	const float gfx_getAmbientLightingIntensity();
	const float gfx_getDirectionalLightingIntensity();
	const float gfx_getSpotLightingIntensity();
	const float gfx_getSpotLightingAngle();
	const float gfx_getSpotLightingDistance();
	const float gfx_getFogMinDistance();
	const float gfx_getFogMaxDistance();
	const float gfx_getFogThickness();
	const float gfx_getSkyReflectionFactor();
	const float gfx_getSceneReflectionHeight();
	const float gfx_getSceneReflectionFactor();
	const float gfx_getShadowSize();
	const float gfx_getShadowReach();
	const float gfx_getShadowLightness();
	const float gfx_getBloomIntensity();
	const float gfx_getBloomBrightnessTreshold();
	const float gfx_getSkyHdrBrightnessFactor();
	const float gfx_getaMaxDofDistance();
	const float gfx_getDofBlurDistance();
	const float gfx_getLensFlareIntensity();
	const float gfx_getLensFlareMultiplier();
	const float gfx_getMotionBlurStrength();
	const unsigned int gfx_getMsaaQuality();
	const unsigned int gfx_getShadowQuality();
	const unsigned int gfx_getReflectionQuality();
	const unsigned int gfx_getRefractionQuality();
	const unsigned int gfx_getBloomBlurSize();
	const unsigned int gfx_getShadowInterval();
	const bool gfx_isMsaaEnabled();
	const bool gfx_isAmbientLightingEnabled();
	const bool gfx_isDirectionalLightingEnabled();
	const bool gfx_isSpecularLightingEnabled();
	const bool gfx_isPointLightingEnabled();
	const bool gfx_isSpotLightingEnabled();
	const bool gfx_isFogEnabled();
	const bool gfx_isLightMappingEnabled();
	const bool gfx_isNormalMappingEnabled();
	const bool gfx_isSkyReflectionsEnabled();
	const bool gfx_isSceneReflectionsEnabled();
	const bool gfx_isBloomEnabled();
	const bool gfx_isWaterEffectsEnabled();
	const bool gfx_isSkyHdrEnabled();
	const bool gfx_isShadowsEnabled();
	const bool gfx_isDofEnabled();
	const bool gfx_isDofDynamic();
	const bool gfx_isMotionBlurEnabled();
	const bool gfx_isLensFlareEnabled();
	const bool gfx_isShadowFollowingCamera();
	const bool gfx_isSoftShadowingEnabled();

	// Logger interface
	template<typename T, typename...Rest> inline void logger_throwInfo(T first, Rest...rest)
	{
		Logger::throwInfo(first, rest...);
	}
	template<typename T, typename...Rest> inline void logger_throwError(T first, Rest...rest)
	{
		Logger::throwError(first, rest...);
	}
	template<typename T, typename...Rest> inline void logger_throwDebug(T first, Rest...rest)
	{
		Logger::throwDebug(first, rest...);
	}
	template<typename T, typename...Rest> inline void logger_throwWarning(T first, Rest...rest)
	{
		Logger::throwWarning(first, rest...);
	}
	inline const vector<string>& logger_getMessageQueue()
	{
		return Logger::getMessageQueue();
	}
	inline unsigned int logger_getMessageCount()
	{
		return Logger::getMessageCount();
	}
	inline void logger_setMessageQueue(const vector<string>& customMessages)
	{
		return Logger::setCustomMessageQueue(customMessages);
	}
	inline void logger_clearMessageQueue()
	{
		return Logger::clearMessageQueue();
	}

	// Server interface - setters
	void networkServer_start(unsigned int maxClientCount);
	void networkServer_sendMessageTCP(const string& username, const string& content);
	void networkServer_sendMessageUDP(const string& username, const string& content);
	void networkServer_broadcastMessageTCP(const string& content, const string& exceptionUsername);
	void networkServer_broadcastMessageUDP(const string& content, const string& exceptionUsername);
	void networkServer_disconnectClient(const string& username);
	void networkServer_stop();

	// Server interface - getters
	const bool networkServer_isRunning();
	const bool networkServer_isClientConnected(const string& username);
	const vector<NetworkClientMessage>& networkServer_getPendingMessages();
	const vector<string> networkServer_getClientIPs();
	const vector<string> networkServer_getClientPorts();
	const vector<string> networkServer_getClientUsernames();
	const string& networkServer_getNewClientIP();
	const string& networkServer_getNewClientPort();
	const string& networkServer_getNewClientUsername();
	const string networkServer_getOldClientIP();
	const string networkServer_getOldClientPort();
	const string networkServer_getOldClientUsername();

	// Client interface - setters
	void networkClient_start(const string& username);
	void networkClient_connect(const string& serverIP);
	void networkClient_sendMessageTCP(const string& content);
	void networkClient_sendMessageUDP(const string& content);
	void networkClient_disconnect();
	void networkClient_stop();

	// Client interface - getters
	const bool networkClient_isRunning();
	const bool networkClient_isConnecting();
	const bool networkClient_isConnected();
	const unsigned int networkClient_getPingLatency();
	const string& networkClient_getUsername();
	const string& networkClient_getServerIP();
	const vector<NetworkServerMessage>& networkClient_getPendingMessages();

	// Miscellaneous interface - setters
	void misc_enableWireframeRendering();
	void misc_disableWireframeRendering();
	void misc_enableShadowFrameRendering();
	void misc_disableShadowFrameRendering();
	void misc_enableAabbFrameRendering();
	void misc_disableAabbFrameRendering();
	void misc_enableDebugRendering();
	void misc_disableDebugRendering();
	void misc_enableTerrainRaycasting(float distance, float precision);
	void misc_disableTerrainRaycasting();
	void misc_enableVsync();
	void misc_disableVsync();
	void misc_enableSounds();
	void misc_disableSounds();
	void misc_enableMusic();
	void misc_disableMusic();
	void misc_setCustomCursor(const string& imageEntityID);
	void misc_centerCursor();
	void misc_showCursor();
	void misc_hideCursor();
	void misc_setCursorPosition(Ivec2 pos);
	void misc_setMainRenderingColor(Vec3 color);
	void misc_setWindowTitle(const string& title);
	void misc_clearMeshCache(const string& filePath);
	void misc_clearTextureCache2D(const string& filePath);
	void misc_clearTextureCache3D(const array<string, 6>& filePaths);
	void misc_clearFontCache(const string& filePath);
	void misc_clearTextCache(const string& textContent, const string& fontPath);
	void misc_clearBitmapCache(const string& filePath);
	void misc_clearAudioChunkCache(const string& filePath);
	void misc_clearAudioMusicCache(const string& filePath);
	void misc_cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths);
	void misc_cacheTexturesMultiThreaded2D(const vector<string>& filePaths);
	void misc_cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePaths);
	void misc_cacheAudioMultiThreaded(const vector<string>& filePaths);
	void misc_startMillisecondTimer();
	void misc_setLevelOfDetailDistance(float distance);
	void misc_setMaxAudioChannels(unsigned int count);

	// Miscellaneous interface - getters
	const int misc_getRandomInteger(int min, int max);
	const int misc_getMsTimeSinceEpoch();
	const int misc_getTriangleCount();
	const int misc_getMaxChannels();
	const float misc_getRandomFloat(float min, float max);
	const float misc_getAspectRatio();
	const float misc_getFPS();
	const float misc_getPI();
	const float misc_degreesToRadians(float angle);
	const float misc_radiansToDegrees(float angle);
	const float misc_stopMillisecondTimer();
	const float misc_getLevelOfDetailDistance();
	const string misc_getWinExplorerFilename(const string& startingDirectory, const string& fileType);
	const string misc_vec2str(Ivec2 vec);
	const string misc_vec2str(Vec2 vec);
	const string misc_vec2str(Vec3 vec);
	const string misc_vec2str(Vec4 vec);
	const string misc_getRootDirectory();
	const string misc_getCpuName();
	const string misc_getGpuName();
	const string misc_getOpenglVersion();
	const Ivec2 misc_getCursorPosition();
	const Ivec2 misc_getCursorPositionRelativeToViewport();
	const Ivec2 misc_convertToScreenCoords(Vec2 pos);
	const Ivec2 misc_getViewportPosition();
	const Ivec2 misc_getViewportSize();
	const Ivec2 misc_getWindowSize();
	const Vec2 misc_convertToNDC(Vec2 pos);
	const Vec2 misc_convertFromNDC(Vec2 pos);
	const Vec2 misc_convertFromScreenCoords(Ivec2 pos);
	const Vec3 misc_getRaycastVector();
	const Vec3 misc_getRaycastPositionOnTerrain();
	const bool misc_isCursorVisible();
	const bool misc_isCursorInsideViewport();
	const bool misc_isCursorInsideWindow();
	const bool misc_isDirectoryExisting(const string& filePath);
	const bool misc_isFileExisting(const string& filePath);
	const bool misc_checkInterval(unsigned int frames);
	const bool misc_isRaycastPositionOnTerrainValid();
	const bool misc_isMillisecondTimerStarted();
	const bool misc_createNewDirectory(const string& directoryPath);
	const bool misc_isVsyncEnabled();
	const vector<pair<string, int>> misc_getUpdateProfilingStatistics();
	const vector<pair<string, int>> misc_getRenderProfilingStatistics();

protected:
	// Virtual interface
	virtual void FE3D_CONTROLLER_INIT() = 0;
	virtual void FE3D_CONTROLLER_UPDATE() = 0;
	virtual void FE3D_CONTROLLER_DESTROY() = 0;

private:
	CoreEngine* _core = nullptr;

	bool _isRaycastUpdated = false;

	string _hoveredAabbID = "";

	float _hoveredAabbDistance = -1.0f;
};
#pragma once

#include "logger.hpp"
#include "input_type.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"
#include "network_peer_type.hpp"
#include "network_message.hpp"
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
	void   engine_start();
	void   engine_pause();
	void   engine_resume();
	void   engine_stop();
	bool   engine_isPaused();
	bool   engine_isGameExported();
	string engine_getGameTitle();

	// Camera interface - setters
	void camera_load(float fov, float nearZ, float farZ, Vec3 startPosition, float yaw = 0.0f, float pitch = 0.0f);
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
	void camera_invertYaw();
	void camera_invertPitch();
	void camera_setFOV(float fov);
	void camera_setMouseSensitivity(float speed);
	void camera_setYaw(float yaw);
	void camera_setPitch(float pitch);
	void camera_setNearDistance(float nearZ);
	void camera_setFarDistance(float farZ);
	void camera_setMaxPitch(float pitch);

	// Camera interface - getters
	bool camera_isLookatViewEnabled();
	bool camera_isFirstPersonViewEnabled();
	Vec3 camera_getPosition();
	Vec3 camera_getLookatPosition();
	float camera_getFOV();
	float getAspectRatio();
	float camera_getMouseSensitivity();
	float camera_getYaw();
	float camera_getPitch();
	float camera_getNearDistance();
	float camera_getFarDistance();
	float camera_getMouseOffset();
	float camera_getMaxPitch();

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
	bool skyEntity_isExisting(const string& ID);
	bool skyEntity_isVisible(const string& ID);
	string skyEntity_getSelectedID();
	vector<string> skyEntity_getAllIDs();
	const array<string, 6>& skyEntity_getDiffuseMapPaths(const string& ID);
	float skyEntity_getLightness(const string& ID);
	float skyEntity_getOriginalLightness(const string& ID);
	float skyEntity_getRotationSpeed(const string& ID);
	float skyEntity_getMixValue();
	Vec3 skyEntity_getColor(const string& ID);

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
	bool terrainEntity_isExisting(const string& ID);
	bool terrainEntity_isVisible(const string& ID);
	bool terrainEntity_isBlendMapped(const string& ID);
	bool terrainEntity_isNormalMapped(const string& ID);
	bool terrainEntity_isNormalMappedR(const string& ID);
	bool terrainEntity_isNormalMappedG(const string& ID);
	bool terrainEntity_isNormalMappedB(const string& ID);
	bool terrainEntity_isSpecularLighted(const string& ID);
	bool terrainEntity_isInside(const string& ID, float x, float z);
	string terrainEntity_getSelectedID();
	vector<string> terrainEntity_getAllIDs();
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
	float terrainEntity_getMaxHeight(const string& ID);
	float terrainEntity_getUvRepeat(const string& ID);
	float terrainEntity_getLightness(const string& ID);
	float terrainEntity_getBlendRepeatR(const string& ID);
	float terrainEntity_getBlendRepeatG(const string& ID);
	float terrainEntity_getBlendRepeatB(const string& ID);
	float terrainEntity_getSize(const string& ID);
	float terrainEntity_getPixelHeight(const string& ID, float x, float z);
	float terrainEntity_getSpecularLightingFactor(const string& ID);
	float terrainEntity_getSpecularLightingIntensity(const string& ID);

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
	bool waterEntity_isExisting(const string& ID);
	bool waterEntity_isVisible(const string& ID);
	bool waterEntity_isWaving(const string& ID);
	bool waterEntity_isRippling(const string& ID);
	bool waterEntity_isSpecularLighted(const string& ID);
	bool waterEntity_isReflective(const string& ID);
	bool waterEntity_isRefractive(const string& ID);
	Vec2 waterEntity_getSpeed(const string& ID);
	Vec3 waterEntity_getPosition(const string& ID);
	Vec3 waterEntity_getColor(const string& ID);
	float waterEntity_getSize(const string& ID);
	float waterEntity_getUvRepeat(const string& ID);
	float waterEntity_getWaveHeightFactor(const string& ID);
	float waterEntity_getSpecularLightingFactor(const string& ID);
	float waterEntity_getSpecularLightingIntensity(const string& ID);
	float waterEntity_getTransparency(const string& ID);
	const string& waterEntity_getDudvMapPath(const string& ID);
	const string& waterEntity_getNormalMapPath(const string& ID);
	const string& waterEntity_getDisplacementMapPath(const string& ID);
	string waterEntity_getSelectedID();
	vector<string> waterEntity_getAllIDs();

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
	bool modelEntity_isExisting(const string& ID);
	bool modelEntity_isVisible(const string& ID);
	bool modelEntity_isInstanced(const string& ID);
	bool modelEntity_isMultiParted(const string& ID);
	bool modelEntity_isTransparent(const string& ID);
	bool modelEntity_isFaceCulled(const string& ID);
	bool modelEntity_isLightMapped(const string& ID);
	bool modelEntity_isNormalMapped(const string& ID);
	bool modelEntity_isSkyReflective(const string& ID);
	bool modelEntity_isSpecularLighted(const string& ID);
	bool modelEntity_isSceneReflective(const string& ID);
	bool modelEntity_isShadowed(const string& ID);
	bool modelEntity_isStaticToCamera(const string& ID);
	bool modelEntity_isWireframed(const string& ID);
	bool modelEntity_isDepthMapIncluded(const string& ID);
	bool modelEntity_hasPart(const string& ID, const string& partID);
	float modelEntity_getLightness(const string& ID);
	float modelEntity_getSpecularFactor(const string& ID);
	float modelEntity_getSpecularIntensity(const string& ID);
	float modelEntity_getAlpha(const string& ID);
	float modelEntity_getMinHeight(const string& ID);
	float modelEntity_getMaxHeight(const string& ID);
	float modelEntity_getUvRepeat(const string& ID);
	Vec3 modelEntity_getPosition(const string& ID, const string& partID = "");
	Vec3 modelEntity_getRotation(const string& ID, const string& partID = "");
	Vec3 modelEntity_getRotationOrigin(const string& ID, const string& partID = "");
	Vec3 modelEntity_getSize(const string& ID, const string& partID = "");
	Vec3 modelEntity_getColor(const string& ID, const string& partID = "");
	string modelEntity_getMeshPath(const string& ID);
	string modelEntity_getDiffuseMapPath(const string& ID);
	string modelEntity_getLightMapPath(const string& ID);
	string modelEntity_getNormalMapPath(const string& ID);
	string modelEntity_getReflectionMapPath(const string& ID);
	string modelEntity_getLevelOfDetailEntityID(const string& ID);
	const vector<Vec3>    modelEntity_getInstancedOffsets(const string& ID);
	const vector<string>& modelEntity_getDiffuseMapPaths(const string& ID);
	const vector<string>& modelEntity_getLightMapPaths(const string& ID);
	const vector<string>& modelEntity_getReflectionMapPaths(const string& ID);
	const vector<string>& modelEntity_getNormalMapPaths(const string& ID);
	const vector<string>& modelEntity_getPartIDs(const string& ID);
	vector<string> modelEntity_getAllIDs();
	vector<string> modelEntity_getGroupIDs(const string& ID);

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
	float billboardEntity_getLightness(const string& ID);
	float billboardEntity_getMinHeight(const string& ID);
	float billboardEntity_getMaxHeight(const string& ID);
	bool billboardEntity_isExisting(const string& ID);
	bool billboardEntity_isVisible(const string& ID);
	bool billboardEntity_isFacingCameraX(const string& ID);
	bool billboardEntity_isFacingCameraY(const string& ID);
	bool billboardEntity_isDepthMapIncluded(const string& ID);
	bool billboardEntity_isInstanced(const string& ID);
	Vec3 billboardEntity_getPosition(const string& ID);
	Vec3 billboardEntity_getRotation(const string& ID);
	Vec2 billboardEntity_getSize(const string& ID);
	Vec3 billboardEntity_getColor(const string& ID);
	vector<string> billboardEntity_getAllIDs();
	vector<Vec3>   billboardEntity_getInstancedOffsets(const string& ID);

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
	bool billboardEntity_isTransparent(const string& ID);

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
	bool billboardEntity_isSpriteAnimationStarted(const string& ID);
	bool billboardEntity_isSpriteAnimationPlaying(const string& ID);
	bool billboardEntity_isSpriteAnimationPaused(const string& ID);
	unsigned int billboardEntity_getSpriteAnimationRows(const string& ID);
	unsigned int billboardEntity_getSpriteAnimationColumns(const string& ID);
	unsigned int billboardEntity_getSpriteAnimationFramestep(const string& ID);
	unsigned int billboardEntity_getSpriteAnimationRowIndex(const string& ID);
	unsigned int billboardEntity_getSpriteAnimationColumnIndex(const string& ID);
	int billboardEntity_getRemainingSpriteAnimationLoops(const string& ID);

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
	Vec3 aabbEntity_getPosition(const string& ID, bool noLocal = false);
	Vec3 aabbEntity_getSize(const string& ID, bool noLocal = false);
	bool aabbEntity_isRaycastResponsive(const string& ID);
	bool aabbEntity_isCollisionResponsive(const string& ID);
	bool aabbEntity_isExisting(const string& ID);
	bool aabbEntity_isVisible(const string& ID);
	vector<string> aabbEntity_getBoundIDs(const string& parentID, bool modelEntity, bool billboardEntity);
	vector<string> aabbEntity_getAllIDs();
	string aabbEntity_getParentID(const string& ID);
	AabbParentType aabbEntity_getParentType(const string& ID);

	// Global collision interface - setters
	void collision_setCameraBoxSize(float bottom, float top, float left, float right, float front, float back);
	void collision_enableCameraResponse(bool x, bool y, bool z);
	void collision_disableCameraResponse();
	void collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraTerrainResponse();

	// Global collision interface - getters
	pair<const string, float> collision_checkCursorInAny();
	pair<bool, float>		  collision_checkCursorInEntity(const string& ID, bool canBeOccluded);
	pair<const string, float> collision_checkCursorInEntities(const string& ID, bool canBeOccluded, const string& exception = "");
	bool		 collision_checkCameraWithTerrain();
	bool		 collision_checkCameraWithEntity(const string& ID);
	const string collision_checkCameraWithAny();
	const string collision_checkCameraWithEntities(const string& ID);
	bool		 collision_checkCameraWithEntityDirection(const string& ID, Direction direction);
	bool		 collision_checkCameraWithAnyDirection(Direction direction);
	bool		 collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction);
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
	bool lightEntity_isExisting(const string& ID);
	bool lightEntity_isVisible(const string& ID);
	Vec3 lightEntity_getPosition(const string& ID);
	Vec3 lightEntity_getColor(const string& ID);
	float lightEntity_getIntensity(const string& ID);
	float lightEntity_getDistanceFactor(const string& ID);
	vector<string> lightEntity_getAllIDs();

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
	bool imageEntity_isExisting(const string& ID);
	bool imageEntity_isVisible(const string& ID);
	bool imageEntity_isCentered(const string& ID);
	bool imageEntity_isMirroredHorizontally(const string& ID);
	bool imageEntity_isMirroredVertically(const string& ID);
	bool imageEntity_isSpriteAnimationStarted(const string& ID);
	bool imageEntity_isSpriteAnimationPlaying(const string& ID);
	bool imageEntity_isSpriteAnimationPaused(const string& ID);
	Vec2 imageEntity_getPosition(const string& ID);
	Vec2 imageEntity_getSize(const string& ID);
	Vec2 imageEntity_getMinPosition(const string& ID);
	Vec2 imageEntity_getMaxPosition(const string& ID);
	Vec3 imageEntity_getColor(const string& ID);
	float imageEntity_getRotation(const string& ID);
	float imageEntity_getAlpha(const string& ID);
	int imageEntity_getRemainingSpriteAnimationLoops(const string& ID);
	unsigned int imageEntity_getSpriteAnimationRows(const string& ID);
	unsigned int imageEntity_getSpriteAnimationColumns(const string& ID);
	unsigned int imageEntity_getSpriteAnimationFramestep(const string& ID);
	unsigned int imageEntity_getSpriteAnimationRowIndex(const string& ID);
	unsigned int imageEntity_getSpriteAnimationColumnIndex(const string& ID);
	vector<string> imageEntity_getAllIDs();

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
	bool textEntity_isExisting(const string& ID);
	bool textEntity_isVisible(const string& ID);
	Vec2 textEntity_getPosition(const string& ID);
	Vec2 textEntity_getSize(const string& ID);
	Vec2 textEntity_getMinPosition(const string& ID);
	Vec2 textEntity_getMaxPosition(const string& ID);
	Vec3 textEntity_getColor(const string& ID);
	float textEntity_getRotation(const string& ID);
	float textEntity_getAlpha(const string& ID);
	const string& textEntity_getTextContent(const string& ID);
	vector<string> textEntity_getAllIDs();

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
	vector<string> soundEntity_getAllIDs();
	string soundEntity_getFilePath(const string& ID);
	Vec3 soundEntity_getPosition(const string& ID);
	float soundEntity_getMaxDistance(const string& ID);
	float soundEntity_getVolume(const string& ID);
	float soundEntity_getMaxVolume(const string& ID);
	bool soundEntity_isExisting(const string& ID);
	bool soundEntity_isStarted(const string& ID);
	bool soundEntity_isPlaying(const string& ID);
	bool soundEntity_isPaused(const string& ID);
	bool soundEntity_isLoaded(const string& ID);
	bool soundEntity_is3D(const string& ID);
	int soundEntity_getUsedChannelCount();

	// Music interface - setters
	void music_addToPlaylist(const string& audioPath);
	void music_clearPlaylist();
	void music_setVolume(float volume);
	void music_pause();
	void music_resume();

	// Music interface - getters
	bool music_isStarted();
	bool music_isPlaying();
	bool music_isPaused();
	float music_getVolume();

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
	Vec3 gfx_getDirectionalLightingPosition();
	Vec3 gfx_getAmbientLightingColor();
	Vec3 gfx_getDirectionalLightingColor();
	Vec3 gfx_getSpotLightingColor();
	Vec3 gfx_getFogColor();
	Vec3 gfx_getShadowEye();
	Vec3 gfx_getShadowCenter();
	string gfx_getLensFlareMapPath();
	float gfx_getAmbientLightingIntensity();
	float gfx_getDirectionalLightingIntensity();
	float gfx_getSpotLightingIntensity();
	float gfx_getSpotLightingAngle();
	float gfx_getSpotLightingDistance();
	float gfx_getFogMinDistance();
	float gfx_getFogMaxDistance();
	float gfx_getFogThickness();
	float gfx_getSkyReflectionFactor();
	float gfx_getSceneReflectionHeight();
	float gfx_getSceneReflectionFactor();
	float gfx_getShadowSize();
	float gfx_getShadowReach();
	float gfx_getShadowLightness();
	float gfx_getBloomIntensity();
	float gfx_getBloomBrightnessTreshold();
	float gfx_getSkyHdrBrightnessFactor();
	float gfx_getaMaxDofDistance();
	float gfx_getDofBlurDistance();
	float gfx_getLensFlareIntensity();
	float gfx_getLensFlareMultiplier();
	float gfx_getMotionBlurStrength();
	unsigned int gfx_getMsaaQuality();
	unsigned int gfx_getShadowQuality();
	unsigned int gfx_getReflectionQuality();
	unsigned int gfx_getRefractionQuality();
	unsigned int gfx_getBloomBlurSize();
	unsigned int gfx_getShadowInterval();
	bool gfx_isMsaaEnabled();
	bool gfx_isAmbientLightingEnabled();
	bool gfx_isDirectionalLightingEnabled();
	bool gfx_isSpecularLightingEnabled();
	bool gfx_isPointLightingEnabled();
	bool gfx_isSpotLightingEnabled();
	bool gfx_isFogEnabled();
	bool gfx_isLightMappingEnabled();
	bool gfx_isNormalMappingEnabled();
	bool gfx_isSkyReflectionsEnabled();
	bool gfx_isSceneReflectionsEnabled();
	bool gfx_isBloomEnabled();
	bool gfx_isWaterEffectsEnabled();
	bool gfx_isSkyHdrEnabled();
	bool gfx_isShadowsEnabled();
	bool gfx_isDofEnabled();
	bool gfx_isDofDynamic();
	bool gfx_isMotionBlurEnabled();
	bool gfx_isLensFlareEnabled();
	bool gfx_isShadowFollowingCamera();
	bool gfx_isSoftShadowingEnabled();

	// Input interface
	void input_setLocked(bool locked);
	void input_clearKeyToggles();
	void input_clearMouseToggles();
	void input_setKeyTogglingLocked(bool locked);
	void input_setMouseTogglingLocked(bool locked);
	bool input_getKeyDown(InputType keyName);
	bool input_getKeyPressed(InputType keyName);
	bool input_getKeyToggled(InputType keyName);
	bool input_getMouseDown(InputType mouseButton);
	bool input_getMousePressed(InputType mouseButton);
	bool input_getMouseToggled(InputType mouseButton);
	int input_getMouseWheelX();
	int input_getMouseWheelY();

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

	// Networking interface - setters
	void network_start(NetworkPeerType type, const string& serverIP = "");
	void network_stop();
	void network_loadNextPendingMessage();

	// Networking interface - getters
	bool network_isStarted();
	bool network_isConnectedToServer();
	bool network_isMessagePending();
	const string& network_getConnectedServerAddress();
	const string& network_getConnectedServerPort();
	const shared_ptr<NetworkMessage> network_getPendingMessage();

	// Miscellaneous interface - setters
	void misc_setCustomCursor(const string& imageEntityID);
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
	void misc_centerCursor();
	void misc_showCursor();
	void misc_hideCursor();
	void misc_setCursorPosition(Ivec2 pos);
	void misc_setVsync(bool enabled);
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
	void misc_setSoundsEnabled(bool enabled);
	void misc_setMusicEnabled(bool enabled);
	void misc_setMaxAudioChannels(unsigned int count);

	// Miscellaneous interface - getters
	int misc_getRandomInteger(int min, int max);
	int misc_getMsTimeSinceEpoch();
	int misc_getTriangleCount();
	int misc_getMaxChannels();
	float misc_getRandomFloat(float min, float max);
	float misc_getAspectRatio();
	float misc_getFPS();
	float misc_getPI();
	float misc_degreesToRadians(float angle);
	float misc_radiansToDegrees(float angle);
	float misc_stopMillisecondTimer();
	float misc_getLevelOfDetailDistance();
	string misc_getWinExplorerFilename(const string& startingDirectory, const string& fileType);
	string misc_vec2str(Ivec2 vec);
	string misc_vec2str(Vec2 vec);
	string misc_vec2str(Vec3 vec);
	string misc_vec2str(Vec4 vec);
	string misc_getRootDirectory();
	string misc_getCpuName();
	string misc_getGpuName();
	string misc_getOpenglVersion();
	Ivec2 misc_getCursorPosition();
	Ivec2 misc_getCursorPositionRelativeToViewport();
	Ivec2 misc_convertToScreenCoords(Vec2 pos);
	Ivec2 misc_getViewportPosition();
	Ivec2 misc_getViewportSize();
	Ivec2 misc_getWindowSize();
	Vec2 misc_convertToNDC(Vec2 pos);
	Vec2 misc_convertFromNDC(Vec2 pos);
	Vec2 misc_convertFromScreenCoords(Ivec2 pos);
	Vec3 misc_getRaycastVector();
	Vec3 misc_getRaycastPositionOnTerrain();
	bool misc_isCursorVisible();
	bool misc_isCursorInsideViewport();
	bool misc_isCursorInsideWindow();
	bool misc_isDirectoryExisting(const string& filePath);
	bool misc_isFileExisting(const string& filePath);
	bool misc_checkInterval(unsigned int frames);
	bool misc_isRaycastPositionOnTerrainValid();
	bool misc_isMillisecondTimerStarted();
	vector<pair<string, int>> misc_getUpdateProfilingStatistics();
	vector<pair<string, int>> misc_getRenderProfilingStatistics();

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
#pragma once

#include "input_types.hpp"
#include "logger.hpp"

#include <array>
#include <vector>
#include <map>
#include <string>
#include <GLM\\glm.hpp>
#include <memory>

using std::array;
using std::vector;
using std::map;
using std::string;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;

class CoreEngine;

class FabiEngine3D
{
	friend class CoreEngine;
public:
	FabiEngine3D();
	virtual ~FabiEngine3D();

	// Engine interface
	void engine_start();
	void engine_stop();

	// Camera interface - setters
	void  camera_load(float fov, float nearZ, float farZ, vec3 startPosition, float yaw = 0.0f, float pitch = 0.0f);
	void  camera_enableLookat(vec3 position);
	void  camera_disableLookat();
	void  camera_enableFirstPersonView(float mouseSensitivity);
	void  camera_disableFirstPersonView();
	void  camera_enableFreeMovement();
	void  camera_disableFreeMovement();
	void  camera_translateFollowX(float speed);
	void  camera_translateFollowZY(float speed);
	void  camera_translateFollowZ(float speed);
	void  camera_translate(vec3 translation);
	void  camera_setPosition(vec3 pos);
	void  camera_invertYaw();
	void  camera_invertPitch();
	void  camera_setFOV(float fov);
	void  camera_setMouseSensitivity(float speed);
	void  camera_setYaw(float yaw);
	void  camera_setPitch(float pitch);
	void  camera_setNearDistance(float nearZ);
	void  camera_setFarDistance(float farZ);

	// Camera interface - getters
	bool  camera_isLookatEnabled();
	bool  camera_isFirstPersonViewEnabled();
	bool  camera_isFreeMovementEnabled();
	vec3  camera_getPosition();
	float camera_getFOV();
	float getAspectRatio();
	float camera_getMouseSensitivity();
	float camera_getYaw();
	float camera_getPitch();
	float camera_getNearDistance();
	float camera_getFarDistance();
	float camera_getMouseOffset();

	// Sky entity interface - setters
	void skyEntity_add(const string& ID);
	void skyEntity_delete(const string& ID);
	void skyEntity_hide(const string& ID);
	void skyEntity_show(const string& ID);
	void skyEntity_select(const string& ID);
	void skyEntity_setDiffuseMaps(const string& ID, const array<string, 6>& texturePaths);
	void skyEntity_setDiffuseMapRight(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapLeft(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapTop(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapBottom(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapFront(const string& ID, const string& texturePath);
	void skyEntity_setDiffuseMapBack(const string& ID, const string& texturePath);
	void skyEntity_setLightness(const string& ID, float lightness);
	void skyEntity_setRotationSpeed(const string& ID, float speed);
	void skyEntity_setColor(const string& ID, vec3 color);

	// Sky entity interface - getters
	bool skyEntity_isExisting(const string& ID);
	bool skyEntity_isVisible(const string& ID);
	string skyEntity_getSelectedID();
	const array<string, 6>& skyEntity_getDiffuseMapPaths(const string& ID);
	float skyEntity_getLightness(const string& ID);
	float skyEntity_getRotationSpeed(const string& ID);
	vec3 skyEntity_getColor(const string& ID);

	// Terrain entity interface - setters
	void terrainEntity_add(const string& ID, const string& heightMapPath);
	void terrainEntity_delete(const string& ID);
	void terrainEntity_hide(const string& ID);
	void terrainEntity_show(const string& ID);
	void terrainEntity_select(const string& ID);
	void terrainEntity_setMaxHeight(const string& ID, float height);
	void terrainEntity_setUvRepeat(const string& ID, float repeat);
	void terrainEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void terrainEntity_setLightness(const string& ID, float lightness);
	void terrainEntity_setBlendMapped(const string& ID, bool enabled);
	void terrainEntity_setBlendMap(const string& ID, const string& texturePath);
	void terrainEntity_setBlendMapR(const string& ID, const string& texturePath);
	void terrainEntity_setBlendMapG(const string& ID, const string& texturePath);
	void terrainEntity_setBlendMapB(const string& ID, const string& texturePath);
	void terrainEntity_setBlendRepeatR(const string& ID, float repeat);
	void terrainEntity_setBlendRepeatG(const string& ID, float repeat);
	void terrainEntity_setBlendRepeatB(const string& ID, float repeat);

	// Terrain entity interface - getters
	bool terrainEntity_isExisting(const string& ID);
	bool terrainEntity_isVisible(const string& ID);
	bool terrainEntity_isBlendMapped(const string& ID);
	bool terrainEntity_isInside(const string& ID, float x, float z);
	string terrainEntity_getSelectedID();
	const string& terrainEntity_getDiffuseMapPath(const string& ID);
	const string& terrainEntity_getHeightMapPath(const string& ID);
	const string& terrainEntity_getBlendMapPath(const string& ID);
	const string& terrainEntity_getBlendMapPathR(const string& ID);
	const string& terrainEntity_getBlendMapPathG(const string& ID);
	const string& terrainEntity_getBlendMapPathB(const string& ID);
	float terrainEntity_getMaxHeight(const string& ID);
	float terrainEntity_getUvRepeat(const string& ID);
	float terrainEntity_getLightness(const string& ID);
	float terrainEntity_getBlendRepeatR(const string& ID);
	float terrainEntity_getBlendRepeatG(const string& ID);
	float terrainEntity_getBlendRepeatB(const string& ID);
	float terrainEntity_getSize(const string& ID);
	float terrainEntity_getPixelHeight(const string& ID, float x, float z);
	vec3 terrainEntity_getMousePoint();
	bool terrainEntity_isValidMousePoint();

	// Water entity interface - setters
	void waterEntity_add(const string& ID);
	void waterEntity_delete(const string& ID);
	void waterEntity_hide(const string& ID);
	void waterEntity_show(const string& ID);
	void waterEntity_select(const string& ID);
	void waterEntity_setSpeed(const string& ID, vec2 speed);
	void waterEntity_setPosition(const string& ID, vec3 position);
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
	void waterEntity_setColor(const string& ID, vec3 color);
	void waterEntity_setUvRepeat(const string& ID, float repeat);

	// Water entity interface - getters
	bool   waterEntity_isExisting(const string& ID);
	bool   waterEntity_isVisible(const string& ID);
	bool   waterEntity_isWaving(const string& ID);
	bool   waterEntity_isRippling(const string& ID);
	bool   waterEntity_isSpecularLighted(const string& ID);
	bool   waterEntity_isReflective(const string& ID);
	bool   waterEntity_isRefractive(const string& ID);
	vec2  waterEntity_getSpeed(const string& ID);
	vec3   waterEntity_getPosition(const string& ID);
	vec3   waterEntity_getColor(const string& ID);
	float  waterEntity_getSize(const string& ID);
	float  waterEntity_getUvRepeat(const string& ID);
	float  waterEntity_getWaveHeightFactor(const string& ID);
	float  waterEntity_getSpecularLightingFactor(const string& ID);
	float  waterEntity_getSpecularLightingIntensity(const string& ID);
	float  waterEntity_getTransparency(const string& ID);
	const string& waterEntity_getDudvMapPath(const string& ID);
	const string& waterEntity_getNormalMapPath(const string& ID);
	const string& waterEntity_getDisplacementMapPath(const string& ID);
	string waterEntity_getSelectedID();

	// Game entity interface - setters
	void gameEntity_add
	(
		const string& ID, const string& objPath,
		vec3 position, vec3 rotation, vec3 size, bool visible = true
	);
	void		   gameEntity_deleteAll();
	void		   gameEntity_delete(const string& ID);
	void		   gameEntity_deleteGroup(const string& ID);
	void		   gameEntity_hideAll();
	void		   gameEntity_showAll();
	void		   gameEntity_hide(const string& ID);
	void		   gameEntity_show(const string& ID);
	void		   gameEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void		   gameEntity_setLightMap(const string& ID, const string& texturePath);
	void		   gameEntity_setReflectionMap(const string& ID, const string& texturePath);
	void		   gameEntity_setTransparent(const string& ID, bool enabled);
	void		   gameEntity_setFaceCulled(const string& ID, bool enabled);
	void		   gameEntity_setLightMapped(const string& ID, bool enabled);
	void		   gameEntity_setSkyReflective(const string& ID, bool enabled);
	void		   gameEntity_setSpecularLighted(const string& ID, bool enabled);
	void		   gameEntity_setSceneReflective(const string& ID, bool enabled);
	void		   gameEntity_setShadowed(const string& ID, bool enabled);
	void		   gameEntity_setDepthMapIncluded(const string& ID, bool enabled);
	void		   gameEntity_setStaticToCamera(const string& ID, bool staticToCamera);
	void		   gameEntity_move(const string& ID, vec3 factor);
	void		   gameEntity_rotate(const string& ID, vec3 factor);
	void		   gameEntity_scale(const string& ID, vec3 factor);
	void		   gameEntity_setPosition(const string& ID, vec3 position);
	void		   gameEntity_setRotation(const string& ID, vec3 rotation);
	void		   gameEntity_setSize(const string& ID, vec3 size);
	void		   gameEntity_enable(const string& ID);
	void		   gameEntity_disable(const string& ID);
	void		   gameEntity_setSpecularFactor(const string& ID, float intensity);
	void		   gameEntity_setSpecularIntensity(const string& ID, float intensity);
	void		   gameEntity_setOriginalLightness(const string& ID, float lightness);
	void		   gameEntity_setLightness(const string& ID, float lightness);
	void		   gameEntity_setAlpha(const string& ID, float alpha);
	void		   gameEntity_setColor(const string& ID, vec3 color);
	void		   gameEntity_setMaxY(const string& ID, float y);
	void		   gameEntity_setUvRepeat(const string& ID, float repeat);

	// Game entity interface - getters
	bool		   gameEntity_isExisting(const string& ID);
	bool		   gameEntity_isVisible(const string& ID);
	bool		   gameEntity_isMultiTextured(const string& ID);
	bool		   gameEntity_isTransparent(const string& ID);
	bool		   gameEntity_isFaceCulled(const string& ID);
	bool		   gameEntity_isLightMapped(const string& ID);
	bool		   gameEntity_isSkyReflective(const string& ID);
	bool		   gameEntity_isSpecularLighted(const string& ID);
	bool		   gameEntity_isSceneReflective(const string& ID);
	bool		   gameEntity_isShadowed(const string& ID);
	bool		   gameEntity_isStaticToCamera(const string& ID);
	bool		   gameEntity_isDepthMapIncluded(const string& ID);
	float		   gameEntity_getOriginalLightness(const string& ID);
	float		   gameEntity_getLightness(const string& ID);
	float		   gameEntity_getSpecularFactor(const string& ID);
	float		   gameEntity_getSpecularIntensity(const string& ID);
	float		   gameEntity_getAlpha(const string& ID);
	float		   gameEntity_getMaxY(const string& ID);
	float		   gameEntity_getUvRepeat(const string& ID);
	vec3		   gameEntity_getPosition(const string& ID);
	vec3		   gameEntity_getRotation(const string& ID);
	vec3		   gameEntity_getSize(const string& ID);
	vec3		   gameEntity_getColor(const string& ID);
	string		   gameEntity_getObjPath(const string& ID);
	string		   gameEntity_getDiffuseMapPath(const string& ID);
	string		   gameEntity_getLightMapPath(const string& ID);
	string		   gameEntity_getReflectionMapPath(const string& ID);
	vector<string> gameEntity_getAllIDs();
	vector<string> gameEntity_getGroupIDs(const string& ID);

	// Billboard entity interface (core) - setters
	void billBoardEntity_add
	(
		const string& ID, vec3 color,
		vec3 T, vec3 R, vec2 S, bool facingCameraX, bool facingCameraY, bool visible = true
	);
	void billboardEntity_deleteAll();
	void billboardEntity_delete(const string& ID);
	void billboardEntity_hideAll();
	void billboardEntity_showAll();
	void billboardEntity_hide(const string& ID);
	void billboardEntity_show(const string& ID);
	void billboardEntity_move(const string& ID, vec3 factor);
	void billboardEntity_rotate(const string& ID, vec3 factor);
	void billboardEntity_scale(const string& ID, vec3 factor);
	void billboardEntity_setPosition(const string& ID, vec3 position);
	void billboardEntity_setRotation(const string& ID, vec3 rotation);
	void billboardEntity_setSize(const string& ID, vec2 size);
	void billboardEntity_setColor(const string& ID, vec3 color);
	void billboardEntity_setCameraFacingX(const string& ID, bool enabled);
	void billboardEntity_setCameraFacingY(const string& ID, bool enabled);

	// Billboard entity interface (core) - getters
	bool billboardEntity_isExisting(const string& ID);
	bool billboardEntity_isVisible(const string& ID);
	bool billboardEntity_isFacingCameraX(const string& ID);
	bool billboardEntity_isFacingCameraY(const string& ID);
	vec3 billboardEntity_getPosition(const string& ID);
	vec3 billboardEntity_getRotation(const string& ID);
	vec2 billboardEntity_getSize(const string& ID);
	vec3 billboardEntity_getColor(const string& ID);
	vector<string> billboardEntity_getAllIDs();

	// Billboard entity interface (diffuseMap) - setters
	void billBoardEntity_add
	(
		const string& ID, const string& diffuseMapPath,
		vec3 T, vec3 R, vec2 S,
		bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering, bool visible = true
	);
	void billboardEntity_setDiffuseMap(const string& ID, const string& texturePath, bool textureFiltering);
	void billboardEntity_setTransparent(const string& ID, bool enabled);
	void billboardEntity_setUvRepeat(const string& ID, float repeat);

	// Billboard entity interface (diffuseMap) - getters
	const string& billboardEntity_getDiffuseMapPath(const string& ID);
	bool billboardEntity_isTransparent(const string& ID);
	float billboardEntity_getUvRepeat(const string& ID);

	// Billboard entity interface (text) - setters
	void billBoardEntity_add
	(
		const string& ID, const string& text,
		const string& fontPath, vec3 color,
		vec3 T, vec3 R, vec2 S, bool facingCameraX, bool facingCameraY, bool visible = true
	);
	void billBoardEntity_setFont(const string& ID, const string& fontPath);
	void billBoardEntity_setTextContent(const string& ID, const string& textContent);

	// Billboard entity interface (text) - getters
	const string& billboardEntity_getFontPath(const string& ID);
	const string& billboardEntity_getTextContent(const string& ID);
	
	// Billboard entity interface (animation) - setters
	void billBoardEntity_playSpriteAnimation(const string& ID, int maxAnimationRepeats);
	void billboardEntity_stopSpriteAnimation(const string& ID);
	void billboardEntity_setAnimationRows(const string& ID, int rows);
	void billboardEntity_setAnimationColumns(const string& ID, int columns);
	void billboardEntity_setAnimationFramestep(const string& ID, int framestep);

	// Billboard entity interface (animation) - getters
	bool billboardEntity_isAnimationFinished(const string& ID);
	bool billboardEntity_isAnimationPlaying(const string& ID);
	int billboardEntity_getAnimationRows(const string& ID);
	int billboardEntity_getAnimationColumns(const string& ID);
	int billboardEntity_getAnimationFramestep(const string& ID);

	// AABB entity interface - setters
	void aabbEntity_add(const string& ID, vec3 T, vec3 S, bool responsive);
	void aabbEntity_bindToGameEntity(const string& parentID, vec3 S, bool responsive);
	void aabbEntity_bindToGameEntityGroup(const string& parentID, vec3 S, bool responsive);
	void aabbEntity_deleteAll();
	void aabbEntity_delete(const string& ID);
	void aabbEntity_hide(const string& ID);
	void aabbEntity_show(const string& ID);
	void aabbEntity_setResponsiveness(const string& ID, bool responsive);
	void aabbEntity_setGroupResponsiveness(const string& ID, bool responsive);
	void aabbEntity_setPosition(const string& ID, vec3 position);
	void aabbEntity_setSize(const string& ID, vec3 size);

	// AABB entity interface - getters
	vec3 aabbEntity_getPosition(const string& ID);
	vec3 aabbEntity_getSize(const string& ID);
	bool aabbEntity_isResponsive(const string& ID);
	bool aabbEntity_isExisting(const string& ID);
	vector<string> aabbEntity_getAllIDs();

	// Global collision interface - setters
	void collision_enableCameraResponse();
	void collision_disableCameraResponse();
	void collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraTerrainResponse();

	// Global collision interface - getters
	string collision_checkCursorInAny();
	bool		  collision_checkCursorInEntity(const string& ID);
	string collision_checkCursorInEntityGroup(const string& ID, const string& exception = "");
	bool		  collision_checkAnyWithCamera();
	bool		  collision_checkEntityWithCamera(const string& ID);
	const string& collision_checkEntityGroupWithCamera(const string& ID);
	const string& collision_checkEntityWithOthers(const string& ID);
	ivec3		  collision_checkEntityWithCameraDirection(const string& ID);
	ivec3		  collision_checkEntityGroupWithCameraDirection(const string& ID);

	// Light entity interface - setters
	void lightEntity_add(const string& ID, vec3 position = vec3(0.0f), vec3 color = vec3(1.0f), float intensity = 1.0f, float distanceFactor = 1.0f, bool visible = true);
	void lightEntity_deleteAll();
	void lightEntity_delete(const string& ID);
	void lightEntity_hide(const string& ID);
	void lightEntity_show(const string& ID);
	void lightEntity_setPosition(const string& ID, vec3 position);
	void lightEntity_setColor(const string& ID, vec3 color);
	void lightEntity_setIntensity(const string& ID, float intensity);
	void lightEntity_setDistanceFactor(const string& ID, float factor);

	// Light entity interface - getters
	bool lightEntity_isExisting(const string& ID);
	bool lightEntity_isVisible(const string& ID);
	vec3 lightEntity_getPosition(const string& ID);
	vec3 lightEntity_getColor(const string& ID);
	float lightEntity_getIntensity(const string& ID);
	float lightEntity_getDistanceFactor(const string& ID);
	vector<string> lightEntity_getAllIDs();

	// Gui entity interface - setters
	void guiEntity_add(const string& ID, const string& texturePath, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible = true);
	void guiEntity_add(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible = true);
	void guiEntity_deleteAll();
	void guiEntity_delete(const string& ID);
	void guiEntity_hideAll();
	void guiEntity_hide(const string& ID);
	void guiEntity_showAll();
	void guiEntity_show(const string& ID);
	void guiEntity_changeTexture(const string& ID, const string& texturePath);
	void guiEntity_setPosition(const string& ID, vec2 position);
	void guiEntity_setRotation(const string& ID, float rotation);
	void guiEntity_setSize(const string& ID, vec2 size);
	void guiEntity_move(const string& ID, vec2 position);
	void guiEntity_rotate(const string& ID, float rotation);
	void guiEntity_scale(const string& ID, vec2 size);
	void guiEntity_setColor(const string& ID, vec3 color);
	void guiEntity_setAlpha(const string& ID, float alpha);
	void guiEntity_setMinPosition(const string& ID, vec2 minPos);
	void guiEntity_setMaxPosition(const string& ID, vec2 maxPos);

	// Gui entity interface - getters
	bool guiEntity_isExisting(const string& ID);
	bool guiEntity_isVisible(const string& ID);
	bool guiEntity_isCentered(const string& ID);
	vec2 guiEntity_getPosition(const string& ID);
	vec2 guiEntity_getSize(const string& ID);
	vec2 guiEntity_getMinPosition(const string& ID);
	vec2 guiEntity_getMaxPosition(const string& ID);
	float guiEntity_getRotation(const string& ID);
	float guiEntity_getAlpha(const string& ID);
	vector<string> guiEntity_getAllIDs();

	// Text entity interface - setters
	void textEntity_add
	(
		const string& ID, const string& text,
		const string& fontPath, vec3 color,
		vec2 position, float rotation, vec2 size, bool centered
	);
	void textEntity_deleteAll();
	void textEntity_delete(const string& ID);
	void textEntity_hideAll();
	void textEntity_hide(const string& ID);
	void textEntity_showAll();
	void textEntity_show(const string& ID);
	void textEntity_setTextContent(const string& ID, const string& textContent, float charWidth = -1.0f);
	void textEntity_setColor(const string& ID, vec3 color);
	void textEntity_setAlpha(const string& ID, float alpha);
	void textEntity_setPosition(const string& ID, vec2 position);
	void textEntity_setRotation(const string& ID, float rotation);
	void textEntity_setSize(const string& ID, vec2 size);
	void textEntity_move(const string& ID, vec2 position);
	void textEntity_rotate(const string& ID, float rotation);
	void textEntity_scale(const string& ID, vec2 size);
	void textEntity_setMinPosition(const string& ID, vec2 minPos);
	void textEntity_setMaxPosition(const string& ID, vec2 maxPos);

	// Text interface - getters
	bool textEntity_isExisting(const string& ID);
	vec2 textEntity_getPosition(const string& ID);
	vec2 textEntity_getSize(const string& ID);
	vec2 textEntity_getMinPosition(const string& ID);
	vec2 textEntity_getMaxPosition(const string& ID);
	float textEntity_getRotation(const string& ID);
	float textEntity_getAlpha(const string& ID);
	const string& textEntity_getTextContent(const string& ID);
	vector<string> textEntity_getAllIDs();

	// Graphics interface - setters
	void gfx_setMsaaQuality(int quality);
	void gfx_setShadowQuality(int quality);
	void gfx_setReflectionQuality(int quality);
	void gfx_setRefractionQuality(int quality);
	void gfx_enableAmbientLighting(vec3 color, float intensity);
	void gfx_enableDirectionalLighting(vec3 position, vec3 color, float intensity);
	void gfx_enableSpecularLighting();
	void gfx_enablePointLighting();
	void gfx_enableFog(float minDistance, float maxDistance, float defaultFactor, vec3 color);
	void gfx_enableSkyReflections(float factor);
	void gfx_enableSceneReflections(float factor);
	void gfx_enableLightMapping();
	void gfx_enableMSAA();
	void gfx_enableShadows(vec3 eye, vec3 center, float size, float reach, bool followingCamera);
	void gfx_enableBloom(float intensity, float brightnessTreshold, int blurSize);
	void gfx_enableWaterEffects();
	void gfx_enableSkyHDR(float brightnessFactor);
	void gfx_enableDOF(float maxDistance, float blurDistance);
	void gfx_enableMotionBlur(float strength);
	void gfx_enableLensFlare(const string& texturePath, float intensity, float multiplier);
	void gfx_disableAmbientLighting();
	void gfx_disableDirectionalLighting();
	void gfx_disableSpecularLighting();
	void gfx_disablePointLighting();
	void gfx_disableFog();
	void gfx_disableSkyReflections();
	void gfx_disableSceneReflections();
	void gfx_disableLightMapping();
	void gfx_disableMSAA();
	void gfx_disableShadows();
	void gfx_disableBloom();
	void gfx_disableWaterEffects();
	void gfx_disableSkyHDR();
	void gfx_disableDOF();
	void gfx_disableMotionBlur();
	void gfx_disableLensFlare();

	// Graphics interface - getters
	bool gfx_isMsaaEnabled();
	bool gfx_isAmbientLightingEnabled();
	bool gfx_isDirectionalLightingEnabled();
	bool gfx_isSpecularLightingEnabled();
	bool gfx_isPointLightingEnabled();
	bool gfx_isFogEnabled();
	bool gfx_isLightMappingEnabled();
	bool gfx_isSkyReflectionsEnabled();
	bool gfx_isSceneReflectionsEnabled();
	bool gfx_isBloomEnabled();
	bool gfx_isWaterEffectsEnabled();
	bool gfx_isSkyHdrEnabled();
	bool gfx_isShadowsEnabled();
	bool gfx_isDofEnabled();
	bool gfx_isMotionBlurEnabled();
	bool gfx_isLensFlareEnabled();
	bool gfx_isShadowFollowingCamera();
	int gfx_getMsaaQuality();
	int gfx_getShadowQuality();
	int gfx_getReflectionQuality();
	int gfx_getRefractionQuality();
	int gfx_getBloomBlurSize();
	float gfx_getAmbientLightingIntensity();
	float gfx_geDirectionalLightingIntensity();
	float gfx_getFogMinDistance();
	float gfx_getFogMaxDistance();
	float gfx_getFogDefaultFactor();
	float gfx_getSkyReflectionFactor();
	float gfx_getSceneReflectionHeight();
	float gfx_getSceneReflectionFactor();
	float gfx_getShadowSize();
	float gfx_getShadowReach();
	float gfx_getBloomIntensity();
	float gfx_getBloomBrightnessTreshold();
	float gfx_getSkyHdrBrightnessFactor();
	float gfx_getDofMaxDistance();
	float gfx_getDofBlurDistance();
	float gfx_getLensFlareIntensity();
	float gfx_getLensFlareMultiplier();
	float gfx_getMotionBlurStrength();
	vec3 gfx_getDirectionalLightingPosition();
	vec3 gfx_getAmbientLightingColor();
	vec3 gfx_getDirectionalLightingColor();
	vec3 gfx_getFogColor();
	vec3 gfx_getShadowEyePosition();
	vec3 gfx_getShadowCenter();
	string gfx_getLensFlareMapPath();

	// Input interface
	void input_setLocked(bool locked);
	void input_setKeyTogglingLocked(bool locked);
	void input_setMouseTogglingLocked(bool locked);
	bool input_getKeyDown(Input keyName);
	bool input_getKeyPressed(Input keyName);
	bool input_getKeyToggled(Input keyName);
	bool input_getMouseDown(Input mouseButton);
	bool input_getMousePressed(Input mouseButton);
	bool input_getMouseToggled(Input mouseButton);
	int  input_getMouseWheelX();
	int  input_getMouseWheelY();

	// Audio entity interface - setters
	void audioEntity_setSoundEnabled(bool enabled);
	void audioEntity_setMusicEnabled(bool enabled);
	void audioEntity_deleteAllSounds();
	void audioEntity_deleteAllMusic();
	void audioEntity_stopAllSounds();
	void audioEntity_stopAllMusic();
	void audioEntity_addMusic(const std::string& audioPath);
	void audioEntity_deleteMusic();
	void audioEntity_setMusicVolume(int volume);
	void audioEntity_addGlobal(const std::string& ID, const std::string& audioPath);
	void audioEntity_addPoint(const std::string& ID, const std::string& audioPath, vec3 position, float maxDistance);
	void audioEntity_delete(const std::string& ID);
	void audioEntity_play(const std::string& ID, int loops, int initialVolume, bool noRestart = false, int fadeMillis = 0);
	void audioEntity_pause(const std::string& ID);
	void audioEntity_resume(const std::string& ID);
	void audioEntity_stop(const std::string& ID, int fadeMillis = 0);
	void audioEntity_setVolume(const std::string& ID, int volume);
	void audioEntity_changePoint(const std::string& ID, vec3 position);

	// Audio entity interface - getters
	bool audioEntity_isPlaying(const std::string& ID);
	int  audioEntity_getVolume(const std::string& ID);
	int  audioEntity_getUsedChannelCount();

	// Audio interface - setters
	void audio_setMaxChannels(int count);

	// Audio interface - getters
	int audio_getMaxChannels();

	// Logger interface
	template<typename T, typename...Rest> inline void logger_throwInfo(T first, Rest...rest)
	{
		Logger::getInst().throwInfo(first, rest...);
	}

	template<typename T, typename...Rest> inline void logger_throwError(T first, Rest...rest)
	{
		Logger::getInst().throwError(first, rest...);
	}

	template<typename T, typename...Rest> inline void logger_throwDebug(T first, Rest...rest)
	{
		Logger::getInst().throwDebug(first, rest...);
	}

	template<typename T, typename...Rest> inline void logger_throwWarning(T first, Rest...rest)
	{
		Logger::getInst().throwWarning(first, rest...);
	}

	// Miscellaneous interface - setters
	void misc_setCustomCursor(const string& guiEntityID);
	void misc_enableWireframeRendering();
	void misc_disableWireframeRendering();
	void misc_enableShadowFrameRendering();
	void misc_disableShadowFrameRendering();
	void misc_enableAabbFrameRendering();
	void misc_disableAabbFrameRendering();
	void misc_enableDebugRendering();
	void misc_disableDebugRendering();
	void misc_showAudioDebugging();
	void misc_hideAudioDebugging();
	void misc_showCursor();
	void misc_hideCursor();
	void misc_setMousePos(ivec2 pos);
	void misc_setMainRenderingColor(vec3 color);
	void misc_setWindowTitle(const string& title);
	void misc_clearOBJCache(const string& filePath);
	void misc_clearTextCache(const string& filePath);
	void misc_clearFontCache(const string& filePath);
	void misc_clearTextureCache(const string& filePath);
	void misc_clearCubeMapCache(const array<string, 6>& filePaths);
	void misc_clearHeightMapCache(const string& filePath);

	// Miscellaneous interface - getters
	int misc_getUniqueInt(int min, int max);
	int misc_getWindowWidth();
	int misc_getWindowHeight();
	int misc_getRandomInt(int min, int max);
	int misc_getMsTimeSinceEpoch();
	int misc_getTriangleCount();
	float misc_getRandomFloat(float min, float max);
	float misc_getAspectRatio();
	float misc_getFPS();
	string misc_getWinExplorerFilename(const string& startingDir, const string& fileType);
	string misc_vec2str(ivec2 vec);
	string misc_vec2str(ivec3 vec);
	string misc_vec2str(ivec4 vec);
	string misc_vec2str(vec2 vec);
	string misc_vec2str(vec3 vec);
	string misc_vec2str(vec4 vec);
	string misc_getRootDirectory();
	string misc_getGpuName();
	string misc_getOpenglVersion();
	vec2 misc_convertToNDC(vec2 pos);
	vec2 misc_convertFromNDC(vec2 pos);
	vec2 misc_convertFromScreenCoords(ivec2 pos);
	ivec2 misc_convertToScreenCoords(vec2 pos);
	ivec2 misc_getMousePos();
	ivec2 misc_getWindowSize();
	ivec2 misc_getViewportPosition();
	ivec2 misc_getViewportSize();
	bool misc_isMouseInsideViewport();
	bool misc_isMouseInsideWindow();
	bool misc_isDirectory(const string& filePath);
	bool misc_isFileExisting(const string& filePath);
	bool misc_checkInterval(const string& key, int frameCount);
	map<string, int> misc_getPerformanceProfilingStatistics();

protected:
	// Virtual interface
	virtual void FE3D_CONTROLLER_INIT() = 0;
	virtual void FE3D_CONTROLLER_UPDATE() = 0;
	virtual void FE3D_CONTROLLER_DESTROY() = 0;

private:
	CoreEngine* _core = nullptr;
};
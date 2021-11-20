#pragma once

#include "input_type.hpp"
#include "direction.hpp"
#include "direction_order.hpp"
#include "aabb_parent_type.hpp"
#include "network_client_message.hpp"
#include "network_server_message.hpp"
#include "mathematics.hpp"
#include "water_quality.hpp"
#include "bloom_type.hpp"
#include "reflection_type.hpp"
#include "pointlight_shape.hpp"
#include "ray.hpp"

#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>

using std::min;
using std::max;
using std::reverse;
using std::to_string;
using std::make_shared;
using std::make_pair;
using std::array;
using std::vector;
using std::set;
using std::map;
using std::unordered_map;
using std::pair;
using std::string;
using std::shared_ptr;

class CoreEngine;

class FabiEngine3D
{
	friend class CoreEngine;

public:
	FabiEngine3D();
	virtual ~FabiEngine3D();

	// Application interface - setters
	void application_start();
	void application_pause();
	void application_resume();
	void application_stop();

	// Application interface - getters
	const bool application_isPaused() const;

	// Sky entity interface - setters
	void skyEntity_create(const string& ID);
	void skyEntity_deleteAll();
	void skyEntity_delete(const string& ID);
	void skyEntity_setVisible(const string& ID, bool isVisible);
	void skyEntity_selectMainSky(const string& ID);
	void skyEntity_selectMixSky(const string& ID);
	void skyEntity_setMixValue(float mixValue);
	void skyEntity_setCubeMaps(const string& ID, const array<string, 6>& texturePaths);
	void skyEntity_setCubeMapRight(const string& ID, const string& texturePath);
	void skyEntity_setCubeMapLeft(const string& ID, const string& texturePath);
	void skyEntity_setCubeMapTop(const string& ID, const string& texturePath);
	void skyEntity_setCubeMapBottom(const string& ID, const string& texturePath);
	void skyEntity_setCubeMapBack(const string& ID, const string& texturePath);
	void skyEntity_setCubeMapFront(const string& ID, const string& texturePath);
	void skyEntity_setLightness(const string& ID, float lightness);
	void skyEntity_setRotation(const string& ID, float rotation);
	void skyEntity_setColor(const string& ID, Vec3 color);
	void skyEntity_setWireframed(const string& ID, bool enabled);

	// Sky entity interface - getters
	const vector<string> skyEntity_getAllIDs() const;
	const array<string, 6>& skyEntity_getCubeMapPaths(const string& ID) const;
	const string& skyEntity_getCubeMapRight(const string& ID) const;
	const string& skyEntity_getCubeMapLeft(const string& ID) const;
	const string& skyEntity_getCubeMapTop(const string& ID) const;
	const string& skyEntity_getCubeMapBottom(const string& ID) const;
	const string& skyEntity_getCubeMapBack(const string& ID) const;
	const string& skyEntity_getCubeMapFront(const string& ID) const;
	const string skyEntity_getSelectedID() const;
	const string skyEntity_getMixID() const;
	const Vec3 skyEntity_getColor(const string& ID) const;
	const float skyEntity_getLightness(const string& ID) const;
	const float skyEntity_getInitialLightness(const string& ID) const;
	const float skyEntity_getRotation(const string& ID) const;
	const float skyEntity_getMixValue() const;
	const bool skyEntity_isExisting(const string& ID) const;
	const bool skyEntity_isVisible(const string& ID) const;
	const bool skyEntity_isWireframed(const string& ID) const;
	const bool skyEntity_hasCubeMapRight(const string& ID) const;
	const bool skyEntity_hasCubeMapLeft(const string& ID) const;
	const bool skyEntity_hasCubeMapTop(const string& ID) const;
	const bool skyEntity_hasCubeMapBottom(const string& ID) const;
	const bool skyEntity_hasCubeMapBack(const string& ID) const;
	const bool skyEntity_hasCubeMapFront(const string& ID) const;

	// Terrain entity interface - setters
	void terrainEntity_create(const string& ID, const string& heightMapPath);
	void terrainEntity_deleteAll();
	void terrainEntity_delete(const string& ID);
	void terrainEntity_setVisible(const string& ID, bool isVisible);
	void terrainEntity_select(const string& ID);
	void terrainEntity_setBlendMap(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMapR(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMapG(const string& ID, const string& texturePath);
	void terrainEntity_setDiffuseMapB(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMap(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMapR(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMapG(const string& ID, const string& texturePath);
	void terrainEntity_setNormalMapB(const string& ID, const string& texturePath);
	void terrainEntity_setRedRepeat(const string& ID, float repeat);
	void terrainEntity_setGreenRepeat(const string& ID, float repeat);
	void terrainEntity_setBlueRepeat(const string& ID, float repeat);
	void terrainEntity_setMaxHeight(const string& ID, float height);
	void terrainEntity_setTextureRepeat(const string& ID, float repeat);
	void terrainEntity_setLightness(const string& ID, float lightness);
	void terrainEntity_setSpecularShininess(const string& ID, float shininess);
	void terrainEntity_setSpecularIntensity(const string& ID, float intensity);
	void terrainEntity_setSpecular(const string& ID, bool enabled);
	void terrainEntity_setWireframed(const string& ID, bool enabled);

	// Terrain entity interface - getters
	const vector<string> terrainEntity_getAllIDs() const;
	const string terrainEntity_getSelectedID() const;
	const string& terrainEntity_getHeightMapPath(const string& ID) const;
	const string& terrainEntity_getBlendMapPath(const string& ID) const;
	const string& terrainEntity_getDiffuseMapPath(const string& ID) const;
	const string& terrainEntity_getDiffuseMapPathR(const string& ID) const;
	const string& terrainEntity_getDiffuseMapPathG(const string& ID) const;
	const string& terrainEntity_getDiffuseMapPathB(const string& ID) const;
	const string& terrainEntity_getNormalMapPath(const string& ID) const;
	const string& terrainEntity_getNormalMapPathR(const string& ID) const;
	const string& terrainEntity_getNormalMapPathG(const string& ID) const;
	const string& terrainEntity_getNormalMapPathB(const string& ID) const;
	const float terrainEntity_getMaxHeight(const string& ID) const;
	const float terrainEntity_getTextureRepeat(const string& ID) const;
	const float terrainEntity_getLightness(const string& ID) const;
	const float terrainEntity_getRedRepeat(const string& ID) const;
	const float terrainEntity_getGreenRepeat(const string& ID) const;
	const float terrainEntity_getBlueRepeat(const string& ID) const;
	const float terrainEntity_getSize(const string& ID) const;
	const float terrainEntity_getPixelHeight(const string& ID, float x, float z) const;
	const float terrainEntity_getSpecularShininess(const string& ID) const;
	const float terrainEntity_getSpecularIntensity(const string& ID) const;
	const bool terrainEntity_isExisting(const string& ID) const;
	const bool terrainEntity_isVisible(const string& ID) const;
	const bool terrainEntity_isSpecular(const string& ID) const;
	const bool terrainEntity_isWireframed(const string& ID) const;
	const bool terrainEntity_isInside(const string& ID, float x, float z) const;
	const bool terrainEntity_hasBlendMap(const string& ID) const;
	const bool terrainEntity_hasDiffuseMap(const string& ID) const;
	const bool terrainEntity_hasDiffuseMapR(const string& ID) const;
	const bool terrainEntity_hasDiffuseMapG(const string& ID) const;
	const bool terrainEntity_hasDiffuseMapB(const string& ID) const;
	const bool terrainEntity_hasNormalMap(const string& ID) const;
	const bool terrainEntity_hasNormalMapR(const string& ID) const;
	const bool terrainEntity_hasNormalMapG(const string& ID) const;
	const bool terrainEntity_hasNormalMapB(const string& ID) const;

	// Water entity interface - setters
	void waterEntity_create(const string& ID);
	void waterEntity_deleteAll();
	void waterEntity_delete(const string& ID);
	void waterEntity_setVisible(const string& ID, bool isVisible);
	void waterEntity_select(const string& ID);
	void waterEntity_setSpeed(const string& ID, Vec2 speed);
	void waterEntity_setHeight(const string& ID, float height);
	void waterEntity_setSize(const string& ID, float size);
	void waterEntity_setSpecular(const string& ID, bool enabled);
	void waterEntity_setReflective(const string& ID, bool enabled);
	void waterEntity_setRefractive(const string& ID, bool enabled);
	void waterEntity_setWireframed(const string& ID, bool enabled);
	void waterEntity_setDudvMap(const string& ID, const string& texturePath);
	void waterEntity_setNormalMap(const string& ID, const string& texturePath);
	void waterEntity_setDisplacementMap(const string& ID, const string& texturePath);
	void waterEntity_setWaveHeight(const string& ID, float height);
	void waterEntity_setSpecularShininess(const string& ID, float shininess);
	void waterEntity_setSpecularIntensity(const string& ID, float intensity);
	void waterEntity_setTransparency(const string& ID, float transparency);
	void waterEntity_setColor(const string& ID, Vec3 color);
	void waterEntity_setTextureRepeat(const string& ID, float repeat);
	void waterEntity_setQuality(const string& ID, WaterQuality quality);

	// Water entity interface - getters
	const vector<string> waterEntity_getAllIDs() const;
	const string& waterEntity_getDudvMapPath(const string& ID) const;
	const string& waterEntity_getNormalMapPath(const string& ID) const;
	const string& waterEntity_getDisplacementMapPath(const string& ID) const;
	const string waterEntity_getSelectedID() const;
	const Vec3 waterEntity_getColor(const string& ID) const;
	const Vec2 waterEntity_getSpeed(const string& ID) const;
	const float waterEntity_getHeight(const string& ID) const;
	const float waterEntity_getSize(const string& ID) const;
	const float waterEntity_getTextureRepeat(const string& ID) const;
	const float waterEntity_getWaveHeight(const string& ID) const;
	const float waterEntity_getSpecularShininess(const string& ID) const;
	const float waterEntity_getSpecularIntensity(const string& ID) const;
	const float waterEntity_getTransparency(const string& ID) const;
	const bool waterEntity_isExisting(const string& ID) const;
	const bool waterEntity_isVisible(const string& ID) const;
	const bool waterEntity_isSpecular(const string& ID) const;
	const bool waterEntity_isReflective(const string& ID) const;
	const bool waterEntity_isRefractive(const string& ID) const;
	const bool waterEntity_isWireframed(const string& ID) const;
	const bool waterEntity_hasDudvMap(const string& ID) const;
	const bool waterEntity_hasNormalMap(const string& ID) const;
	const bool waterEntity_hasDisplacementMap(const string& ID) const;
	const WaterQuality waterEntity_getQuality(const string& ID) const;

	// Model entity interface - setters
	void modelEntity_create(const string& ID, const string& meshPath);
	void modelEntity_deleteAll();
	void modelEntity_delete(const string& ID);
	void modelEntity_deleteGroup(const string& ID);
	void modelEntity_setVisible(const string& ID, bool isVisible);
	void modelEntity_setDiffuseMap(const string& ID, const string& partID, const string& texturePath);
	void modelEntity_setEmissionMap(const string& ID, const string& partID, const string& texturePath);
	void modelEntity_setSpecularMap(const string& ID, const string& partID, const string& texturePath);
	void modelEntity_setReflectionMap(const string& ID, const string& partID, const string& texturePath);
	void modelEntity_setNormalMap(const string& ID, const string& partID, const string& texturePath);
	void modelEntity_setLevelOfDetailEntity(const string& ID, const string& levelOfDetailID);
	void modelEntity_setFaceCulled(const string& ID, bool enabled);
	void modelEntity_setReflectionType(const string& ID, const string& partID, ReflectionType type);
	void modelEntity_setSpecular(const string& ID, const string& partID, bool enabled);
	void modelEntity_setReflective(const string& ID, const string& partID, bool enabled);
	void modelEntity_setShadowed(const string& ID, bool enabled);
	void modelEntity_setReflected(const string& ID, bool enabled);
	void modelEntity_setDepthMapIncluded(const string& ID, bool enabled);
	void modelEntity_setStaticToCamera(const string& ID, bool enabled);
	void modelEntity_setWireframed(const string& ID, bool enabled);
	void modelEntity_setBasePosition(const string& ID, Vec3 position);
	void modelEntity_setBaseRotation(const string& ID, Vec3 rotation);
	void modelEntity_setBaseRotationOrigin(const string& ID, Vec3 rotationOrigin);
	void modelEntity_setBaseSize(const string& ID, Vec3 size);
	void modelEntity_setPartPosition(const string& ID, const string& partID, Vec3 position);
	void modelEntity_setPartRotation(const string& ID, const string& partID, Vec3 rotation);
	void modelEntity_setPartRotationOrigin(const string& ID, const string& partID, Vec3 rotationOrigin);
	void modelEntity_setPartSize(const string& ID, const string& partID, Vec3 size);
	void modelEntity_moveBase(const string& ID, Vec3 change);
	void modelEntity_rotateBase(const string& ID, Vec3 change);
	void modelEntity_scaleBase(const string& ID, Vec3 change);
	void modelEntity_movePart(const string& ID, const string& partID, Vec3 change);
	void modelEntity_rotatePart(const string& ID, const string& partID, Vec3 change);
	void modelEntity_scalePart(const string& ID, const string& partID, Vec3 change);
	void modelEntity_moveBaseTo(const string& ID, Vec3 target, float speed);
	void modelEntity_rotateBaseTo(const string& ID, Vec3 target, float speed);
	void modelEntity_scaleBaseTo(const string& ID, Vec3 target, float speed);
	void modelEntity_movePartTo(const string& ID, const string& partID, Vec3 target, float speed);
	void modelEntity_rotatePartTo(const string& ID, const string& partID, Vec3 target, float speed);
	void modelEntity_scalePartTo(const string& ID, const string& partID, Vec3 target, float speed);
	void modelEntity_setLevelOfDetailSize(const string& ID, Vec3 size);
	void modelEntity_setSpecularShininess(const string& ID, const string& partID, float intensity);
	void modelEntity_setSpecularIntensity(const string& ID, const string& partID, float intensity);
	void modelEntity_setReflectivity(const string& ID, const string& partID, float reflectivity);
	void modelEntity_setLightness(const string& ID, const string& partID, float lightness);
	void modelEntity_setColorInversion(const string& ID, const string& partID, float colorInversion);
	void modelEntity_setEmissionIntensity(const string& ID, const string& partID, float intensity);
	void modelEntity_setTransparency(const string& ID, const string& partID, float transparency);
	void modelEntity_setColor(const string& ID, const string& partID, Vec3 color);
	void modelEntity_setMinHeight(const string& ID, float height);
	void modelEntity_setMaxHeight(const string& ID, float height);
	void modelEntity_setTextureRepeat(const string& ID, const string& partID, float repeat);
	void modelEntity_enableInstancing(const string& ID, vector<Vec3> offsets);
	void modelEntity_disableInstancing(const string& ID);
	void modelEntity_setBright(const string& ID, bool enabled);
	void modelEntity_setRotationOrder(const string& ID, DirectionOrder order);

	// Model entity interface - getters
	const vector<string> modelEntity_getPartIDs(const string& ID) const;
	const vector<string> modelEntity_getAllIDs() const;
	const vector<string> modelEntity_getGroupIDs(const string& ID) const;
	const string& modelEntity_getMeshPath(const string& ID) const;
	const string& modelEntity_getDiffuseMapPath(const string& ID, const string& partID) const;
	const string& modelEntity_getEmissionMapPath(const string& ID, const string& partID) const;
	const string& modelEntity_getSpecularMapPath(const string& ID, const string& partID) const;
	const string& modelEntity_getReflectionMapPath(const string& ID, const string& partID) const;
	const string& modelEntity_getNormalMapPath(const string& ID, const string& partID) const;
	const string& modelEntity_getLevelOfDetailEntityID(const string& ID) const;
	const vector<Vec3>& modelEntity_getInstancedOffsets(const string& ID) const;
	const Vec3 modelEntity_getLevelOfDetailSize(const string& ID) const;
	const Vec3 modelEntity_getBasePosition(const string& ID) const;
	const Vec3 modelEntity_getBaseRotation(const string& ID) const;
	const Vec3 modelEntity_getBaseRotationOrigin(const string& ID) const;
	const Vec3 modelEntity_getBaseSize(const string& ID) const;
	const Vec3 modelEntity_getPartPosition(const string& ID, const string& partID) const;
	const Vec3 modelEntity_getPartRotation(const string& ID, const string& partID) const;
	const Vec3 modelEntity_getPartRotationOrigin(const string& ID, const string& partID) const;
	const Vec3 modelEntity_getPartSize(const string& ID, const string& partID) const;
	const Vec3 modelEntity_getColor(const string& ID, const string& partID) const;
	const float modelEntity_getColorInversion(const string& ID, const string& partID) const;
	const float modelEntity_getReflectivity(const string& ID, const string& partID) const;
	const float modelEntity_getLightness(const string& ID, const string& partID) const;
	const float modelEntity_getSpecularShininess(const string& ID, const string& partID) const;
	const float modelEntity_getSpecularIntensity(const string& ID, const string& partID) const;
	const float modelEntity_getTransparency(const string& ID, const string& partID) const;
	const float modelEntity_getMinHeight(const string& ID) const;
	const float modelEntity_getMaxHeight(const string& ID) const;
	const float modelEntity_getTextureRepeat(const string& ID, const string& partID) const;
	const float modelEntity_getEmissionIntensity(const string& ID, const string& partID) const;
	const bool modelEntity_isExisting(const string& ID) const;
	const bool modelEntity_isVisible(const string& ID) const;
	const bool modelEntity_isInstanced(const string& ID) const;
	const bool modelEntity_isMultiParted(const string& ID) const;
	const bool modelEntity_isFaceCulled(const string& ID) const;
	const bool modelEntity_isSpecular(const string& ID, const string& partID) const;
	const bool modelEntity_isShadowed(const string& ID) const;
	const bool modelEntity_isReflected(const string& ID) const;
	const bool modelEntity_isStaticToCamera(const string& ID) const;
	const bool modelEntity_isWireframed(const string& ID) const;
	const bool modelEntity_isDepthMapIncluded(const string& ID) const;
	const bool modelEntity_hasPart(const string& ID, const string& partID) const;
	const bool modelEntity_isBright(const string& ID) const;
	const bool modelEntity_isReflective(const string& ID, const string& partID) const;
	const bool modelEntity_hasDiffuseMap(const string& ID, const string& partID) const;
	const bool modelEntity_hasEmissionMap(const string& ID, const string& partID) const;
	const bool modelEntity_hasSpecularMap(const string& ID, const string& partID) const;
	const bool modelEntity_hasReflectionMap(const string& ID, const string& partID) const;
	const bool modelEntity_hasNormalMap(const string& ID, const string& partID) const;
	const ReflectionType modelEntity_getReflectionType(const string& ID, const string& partID) const;
	const DirectionOrder modelEntity_getRotationOrder(const string& ID) const;

	// Billboard entity interface - setters
	void billboardEntity_create(const string& ID);
	void billboardEntity_deleteAll();
	void billboardEntity_delete(const string& ID);
	void billboardEntity_deleteGroup(const string& ID);
	void billboardEntity_pauseSpriteAnimation(const string& ID);
	void billboardEntity_resumeSpriteAnimation(const string& ID);
	void billboardEntity_stopSpriteAnimation(const string& ID);
	void billboardEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void billboardEntity_setEmissionMap(const string& ID, const string& texturePath);
	void billboardEntity_setFont(const string& ID, const string& fontPath);
	void billboardEntity_setTextContent(const string& ID, const string& textContent);
	void billboardEntity_setPosition(const string& ID, Vec3 position);
	void billboardEntity_setRotation(const string& ID, Vec3 rotation);
	void billboardEntity_setSize(const string& ID, Vec2 size);
	void billboardEntity_move(const string& ID, Vec3 change);
	void billboardEntity_rotate(const string& ID, Vec3 change);
	void billboardEntity_scale(const string& ID, Vec2 change);
	void billboardEntity_moveTo(const string& ID, Vec3 target, float speed);
	void billboardEntity_rotateTo(const string& ID, Vec3 target, float speed);
	void billboardEntity_scaleTo(const string& ID, Vec2 target, float speed);
	void billboardEntity_setColor(const string& ID, Vec3 color);
	void billboardEntity_setMinHeight(const string& ID, float height);
	void billboardEntity_setMaxHeight(const string& ID, float height);
	void billboardEntity_setLightness(const string& ID, float lightness);
	void billboardEntity_setColorInversion(const string& ID, float colorInversion);
	void billboardEntity_setTransparency(const string& ID, float transparency);
	void billboardEntity_setTextureRepeat(const string& ID, float repeat);
	void billboardEntity_setEmissionIntensity(const string& ID, float intensity);
	void billboardEntity_startSpriteAnimation(const string& ID, int loops);
	void billboardEntity_setSpriteAnimationRows(const string& ID, unsigned int rows);
	void billboardEntity_setSpriteAnimationColumns(const string& ID, unsigned int columns);
	void billboardEntity_setSpriteAnimationFramestep(const string& ID, unsigned int framestep);
	void billboardEntity_setSpriteAnimationRowIndex(const string& ID, unsigned int index);
	void billboardEntity_setSpriteAnimationColumnIndex(const string& ID, unsigned int index);
	void billboardEntity_setVisible(const string& ID, bool isVisible);
	void billboardEntity_setCameraFacingX(const string& ID, bool enabled);
	void billboardEntity_setCameraFacingY(const string& ID, bool enabled);
	void billboardEntity_setDepthMapIncluded(const string& ID, bool enabled);
	void billboardEntity_setShadowed(const string& ID, bool enabled);
	void billboardEntity_setReflected(const string& ID, bool enabled);
	void billboardEntity_setBright(const string& ID, bool enabled);
	void billboardEntity_setWireframed(const string& ID, bool enabled);

	// Billboard entity interface - getters
	const vector<string> billboardEntity_getAllIDs() const;
	const string& billboardEntity_getDiffuseMapPath(const string& ID) const;
	const string& billboardEntity_getEmissionMapPath(const string& ID) const;
	const string& billboardEntity_getFontPath(const string& ID) const;
	const string& billboardEntity_getTextContent(const string& ID) const;
	const Vec3 billboardEntity_getPosition(const string& ID) const;
	const Vec3 billboardEntity_getRotation(const string& ID) const;
	const Vec2 billboardEntity_getSize(const string& ID) const;
	const Vec3 billboardEntity_getColor(const string& ID) const;
	const float billboardEntity_getLightness(const string& ID) const;
	const float billboardEntity_getColorInversion(const string& ID) const;
	const float billboardEntity_getMinHeight(const string& ID) const;
	const float billboardEntity_getMaxHeight(const string& ID) const;
	const float billboardEntity_getTransparency(const string& ID) const;
	const float billboardEntity_getTextureRepeat(const string& ID) const;
	const float billboardEntity_getEmissionIntensity(const string& ID) const;
	const int billboardEntity_getRemainingSpriteAnimationLoops(const string& ID) const;
	const unsigned int billboardEntity_getSpriteAnimationRows(const string& ID) const;
	const unsigned int billboardEntity_getSpriteAnimationColumns(const string& ID) const;
	const unsigned int billboardEntity_getSpriteAnimationFramestep(const string& ID) const;
	const unsigned int billboardEntity_getSpriteAnimationRowIndex(const string& ID) const;
	const unsigned int billboardEntity_getSpriteAnimationColumnIndex(const string& ID) const;
	const bool billboardEntity_isExisting(const string& ID) const;
	const bool billboardEntity_isVisible(const string& ID) const;
	const bool billboardEntity_isFacingCameraX(const string& ID) const;
	const bool billboardEntity_isFacingCameraY(const string& ID) const;
	const bool billboardEntity_isDepthMapIncluded(const string& ID) const;
	const bool billboardEntity_isShadowed(const string& ID) const;
	const bool billboardEntity_isReflected(const string& ID) const;
	const bool billboardEntity_isBright(const string& ID) const;
	const bool billboardEntity_isWireframed(const string& ID) const;
	const bool billboardEntity_isSpriteAnimationStarted(const string& ID) const;
	const bool billboardEntity_isSpriteAnimationPlaying(const string& ID) const;
	const bool billboardEntity_isSpriteAnimationPaused(const string& ID) const;
	const bool billboardEntity_hasDiffuseMap(const string& ID) const;
	const bool billboardEntity_hasEmissionMap(const string& ID) const;
	const bool billboardEntity_isText(const string& ID) const;

	// AABB entity interface - setters
	void aabbEntity_create(const string& ID);
	void aabbEntity_setParent(const string& ID, const string& parentID, AabbParentType parentType);
	void aabbEntity_deleteAll();
	void aabbEntity_delete(const string& ID);
	void aabbEntity_setVisible(const string& ID, bool isVisible);
	void aabbEntity_setRaycastResponsive(const string& ID, bool responsive);
	void aabbEntity_setCollisionResponsive(const string& ID, bool responsive);
	void aabbEntity_setFollowParentTransformation(const string& ID, bool mustFollow);
	void aabbEntity_setFollowParentVisibility(const string& ID, bool mustFollow);
	void aabbEntity_setLocalPosition(const string& ID, Vec3 position);
	void aabbEntity_setLocalSize(const string& ID, Vec3 size);
	void aabbEntity_setBasePosition(const string& ID, Vec3 position);
	void aabbEntity_setBaseSize(const string& ID, Vec3 size);
	void aabbEntity_move(const string& ID, Vec3 change);
	void aabbEntity_scale(const string& ID, Vec3 change);
	void aabbEntity_moveTo(const string& ID, Vec3 target, float speed);
	void aabbEntity_scaleTo(const string& ID, Vec3 target, float speed);

	// AABB entity interface - getters
	const vector<string> aabbEntity_getChildIDs(const string& parentID, AabbParentType parentType) const;
	const vector<string> aabbEntity_getAllIDs() const;
	const string& aabbEntity_getParentID(const string& ID) const;
	const Vec3 aabbEntity_getPosition(const string& ID) const;
	const Vec3 aabbEntity_getSize(const string& ID) const;
	const bool aabbEntity_isRaycastResponsive(const string& ID) const;
	const bool aabbEntity_isCollisionResponsive(const string& ID) const;
	const bool aabbEntity_isExisting(const string& ID) const;
	const bool aabbEntity_isVisible(const string& ID) const;
	const bool aabbEntity_hasParent(const string& ID) const;
	const AabbParentType aabbEntity_getParentType(const string& ID) const;

	// Pointlight entity interface - setters
	void pointlightEntity_create(const string& ID);
	void pointlightEntity_deleteAll();
	void pointlightEntity_delete(const string& ID);
	void pointlightEntity_setVisible(const string& ID, bool isVisible);
	void pointlightEntity_setPosition(const string& ID, Vec3 position);
	void pointlightEntity_move(const string& ID, Vec3 change);
	void pointlightEntity_moveTo(const string& ID, Vec3 target, float speed);
	void pointlightEntity_setRadius(const string& ID, Vec3 radius);
	void pointlightEntity_setColor(const string& ID, Vec3 color);
	void pointlightEntity_setIntensity(const string& ID, float intensity);
	void pointlightEntity_setShape(const string& ID, PointlightShape shape);

	// Pointlight entity interface - getters
	const vector<string> pointlightEntity_getAllIDs() const;
	const Vec3 pointlightEntity_getPosition(const string& ID) const;
	const Vec3 pointlightEntity_getRadius(const string& ID) const;
	const Vec3 pointlightEntity_getColor(const string& ID) const;
	const float pointlightEntity_getIntensity(const string& ID) const;
	const bool pointlightEntity_isExisting(const string& ID) const;
	const bool pointlightEntity_isVisible(const string& ID) const;
	const PointlightShape pointlightEntity_getShape(const string& ID) const;

	// Spotlight entity interface - setters
	void spotlightEntity_create(const string& ID);
	void spotlightEntity_deleteAll();
	void spotlightEntity_delete(const string& ID);
	void spotlightEntity_setVisible(const string& ID, bool isVisible);
	void spotlightEntity_setPosition(const string& ID, Vec3 position);
	void spotlightEntity_move(const string& ID, Vec3 change);
	void spotlightEntity_moveTo(const string& ID, Vec3 target, float speed);
	void spotlightEntity_setColor(const string& ID, Vec3 color);
	void spotlightEntity_setYaw(const string& ID, float yaw);
	void spotlightEntity_setPitch(const string& ID, float pitch);
	void spotlightEntity_setIntensity(const string& ID, float intensity);
	void spotlightEntity_setAngle(const string& ID, float angle);
	void spotlightEntity_setDistance(const string& ID, float distance);

	// Spotlight entity interface - getters
	const vector<string> spotlightEntity_getAllIDs() const;
	const Vec3 spotlightEntity_getPosition(const string& ID) const;
	const Vec3 spotlightEntity_getColor(const string& ID) const;
	const float spotlightEntity_getYaw(const string& ID) const;
	const float spotlightEntity_getPitch(const string& ID) const;
	const float spotlightEntity_getIntensity(const string& ID) const;
	const float spotlightEntity_getAngle(const string& ID) const;
	const float spotlightEntity_getDistance(const string& ID) const;
	const bool spotlightEntity_isExisting(const string& ID) const;
	const bool spotlightEntity_isVisible(const string& ID) const;

	// Reflection entity interface - setters
	void reflectionEntity_create(const string& ID);
	void reflectionEntity_deleteAll();
	void reflectionEntity_delete(const string& ID);
	void reflectionEntity_setVisible(const string& ID, bool isVisible);
	void reflectionEntity_setPosition(const string& ID, Vec3 position);
	void reflectionEntity_move(const string& ID, Vec3 change);
	void reflectionEntity_moveTo(const string& ID, Vec3 target, float speed);
	void reflectionEntity_capture(const string& ID);

	// Reflection entity interface - getters
	const vector<string> reflectionEntity_getAllIDs() const;
	const Vec3 reflectionEntity_getPosition(const string& ID) const;
	const bool reflectionEntity_isExisting(const string& ID) const;
	const bool reflectionEntity_isVisible(const string& ID) const;

	// Image entity interface - setters
	void imageEntity_create(const string& ID, bool isCentered);
	void imageEntity_deleteAll();
	void imageEntity_delete(const string& ID);
	void imageEntity_setVisible(const string& ID, bool isVisible);
	void imageEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void imageEntity_setColor(const string& ID, Vec3 color);
	void imageEntity_setTransparency(const string& ID, float transparency);
	void imageEntity_setMinPosition(const string& ID, Vec2 minPos);
	void imageEntity_setMaxPosition(const string& ID, Vec2 maxPos);
	void imageEntity_setPosition(const string& ID, Vec2 position);
	void imageEntity_setRotation(const string& ID, float rotation);
	void imageEntity_setSize(const string& ID, Vec2 size);
	void imageEntity_move(const string& ID, Vec2 position);
	void imageEntity_rotate(const string& ID, float rotation);
	void imageEntity_scale(const string& ID, Vec2 size);
	void imageEntity_moveTo(const string& ID, Vec2 target, float speed);
	void imageEntity_rotateTo(const string& ID, float target, float speed);
	void imageEntity_scaleTo(const string& ID, Vec2 target, float speed);
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
	const vector<string> imageEntity_getAllIDs() const;
	const string& imageEntity_getDiffuseMapPath(const string& ID) const;
	const Vec3 imageEntity_getColor(const string& ID) const;
	const Vec2 imageEntity_getPosition(const string& ID) const;
	const Vec2 imageEntity_getSize(const string& ID) const;
	const Vec2 imageEntity_getMinPosition(const string& ID) const;
	const Vec2 imageEntity_getMaxPosition(const string& ID) const;
	const float imageEntity_getRotation(const string& ID) const;
	const float imageEntity_getTransparency(const string& ID) const;
	const int imageEntity_getRemainingSpriteAnimationLoops(const string& ID) const;
	const unsigned int imageEntity_getSpriteAnimationRows(const string& ID) const;
	const unsigned int imageEntity_getSpriteAnimationColumns(const string& ID) const;
	const unsigned int imageEntity_getSpriteAnimationFramestep(const string& ID) const;
	const unsigned int imageEntity_getSpriteAnimationRowIndex(const string& ID) const;
	const unsigned int imageEntity_getSpriteAnimationColumnIndex(const string& ID) const;
	const bool imageEntity_isExisting(const string& ID) const;
	const bool imageEntity_isVisible(const string& ID) const;
	const bool imageEntity_isCentered(const string& ID) const;
	const bool imageEntity_isMirroredHorizontally(const string& ID) const;
	const bool imageEntity_isMirroredVertically(const string& ID) const;
	const bool imageEntity_isSpriteAnimationStarted(const string& ID) const;
	const bool imageEntity_isSpriteAnimationPlaying(const string& ID) const;
	const bool imageEntity_isSpriteAnimationPaused(const string& ID) const;
	const bool imageEntity_hasDiffuseMap(const string& ID) const;

	// Text entity interface - setters
	void textEntity_create(const string& ID, bool isCentered, bool isDynamic);
	void textEntity_deleteAll();
	void textEntity_delete(const string& ID);
	void textEntity_setVisible(const string& ID, bool isVisible);
	void textEntity_setFont(const string& ID, const string& fontPath);
	void textEntity_setTextContent(const string& ID, const string& textContent, float charWidth = -1.0f, float charHeight = -1.0f);
	void textEntity_setColor(const string& ID, Vec3 color);
	void textEntity_setTransparency(const string& ID, float transparency);
	void textEntity_setMinPosition(const string& ID, Vec2 minPos);
	void textEntity_setMaxPosition(const string& ID, Vec2 maxPos);
	void textEntity_setPosition(const string& ID, Vec2 position);
	void textEntity_setRotation(const string& ID, float rotation);
	void textEntity_setSize(const string& ID, Vec2 size);
	void textEntity_move(const string& ID, Vec2 position);
	void textEntity_rotate(const string& ID, float rotation);
	void textEntity_scale(const string& ID, Vec2 size);
	void textEntity_moveTo(const string& ID, Vec2 target, float speed);
	void textEntity_rotateTo(const string& ID, float target, float speed);
	void textEntity_scaleTo(const string& ID, Vec2 target, float speed);

	// Text interface - getters
	const vector<string> textEntity_getAllIDs() const;
	const string& textEntity_getFontPath(const string& ID) const;
	const string& textEntity_getTextContent(const string& ID) const;
	const Vec3 textEntity_getColor(const string& ID) const;
	const Vec2 textEntity_getPosition(const string& ID) const;
	const Vec2 textEntity_getSize(const string& ID) const;
	const Vec2 textEntity_getMinPosition(const string& ID) const;
	const Vec2 textEntity_getMaxPosition(const string& ID) const;
	const float textEntity_getRotation(const string& ID) const;
	const float textEntity_getTransparency(const string& ID) const;
	const bool textEntity_isExisting(const string& ID) const;
	const bool textEntity_isVisible(const string& ID) const;

	// Sound interface - setters
	void sound_create(const string& ID, const string& filePath);
	void sound_make3D(const string& ID, Vec3 position, float maxVolume, float maxDistance);
	void sound_delete(const string& ID);
	void sound_deleteAll();
	void sound_play(const string& ID, int loops, int fadeMS, bool mustForcePlay);
	void sound_pause(const string& ID);
	void sound_pauseAll();
	void sound_resume(const string& ID);
	void sound_resumeAll();
	void sound_stop(const string& ID, int fadeMS);
	void sound_stopAll();
	void sound_setPosition(const string& ID, Vec3 position);
	void sound_move(const string& ID, Vec3 change);
	void sound_setVolume(const string& ID, float volume);
	void sound_setMaxVolume(const string& ID, float volume);
	void sound_setMaxDistance(const string& ID, float maxDistance);

	// Sound interface - getters
	const vector<string> sound_getAllIDs() const;
	const string& sound_getFilePath(const string& ID) const;
	const Vec3 sound_getPosition(const string& ID) const;
	const float sound_getMaxDistance(const string& ID) const;
	const float sound_getVolume(const string& ID) const;
	const float sound_getMaxVolume(const string& ID) const;
	const unsigned int sound_getUsedChannelCount() const;
	const bool sound_isExisting(const string& ID) const;
	const bool sound_isStarted(const string& ID) const;
	const bool sound_isPlaying(const string& ID) const;
	const bool sound_isPaused(const string& ID) const;
	const bool sound_isLoaded(const string& ID) const;
	const bool sound_is3D(const string& ID) const;

	// Music interface - setters
	void music_addToPlaylist(const string& filePath);
	void music_clearPlaylist();
	void music_setVolume(float volume);
	void music_pause();
	void music_resume();

	// Music interface - getters
	const float music_getVolume() const;
	const bool music_isStarted() const;
	const bool music_isPlaying() const;
	const bool music_isPaused() const;

	// Input interface - setters
	void input_setLocked(bool locked);

	// Input interface - getters
	const int input_getMouseWheelX() const;
	const int input_getMouseWheelY() const;
	const bool input_isLocked() const;
	const bool input_isKeyDown(InputType key) const;
	const bool input_isKeyPressed(InputType key) const;
	const bool input_isMouseDown(InputType button) const;
	const bool input_isMousePressed(InputType button) const;

	// Camera interface - setters
	void camera_reset();
	void camera_enableFirstPersonView(float initialYaw, float initialPitch);
	void camera_enableThirdPersonView(float initialYaw, float initialPitch);
	void camera_disableFirstPersonView();
	void camera_disableThirdPersonView();
	void camera_moveFollowX(float speed);
	void camera_moveFollowZY(float speed);
	void camera_moveFollowZ(float speed);
	void camera_move(Vec3 speed);
	void camera_setPosition(Vec3 position);
	void camera_setThirdPersonLookat(Vec3 position);
	void camera_setThirdPersonDistance(float distance);
	void camera_setFOV(float angle);
	void camera_setYaw(float angle);
	void camera_setPitch(float angle);
	void camera_setMinFirstPersonPitch(float angle);
	void camera_setMaxFirstPersonPitch(float angle);
	void camera_setMinThirdPersonPitch(float angle);
	void camera_setMaxThirdPersonPitch(float angle);
	void camera_setCursorSensitivity(float speed);

	// Camera interface - getters
	const Vec3 camera_getPosition() const;
	const Vec3 camera_getUpVector() const;
	const Vec3 camera_getFrontVector() const;
	const Vec3 camera_getRightVector() const;
	const Vec3 camera_getThirdPersonLookat() const;
	const float camera_getFOV() const;
	const float camera_getAspectRatio() const;
	const float camera_getCursorSensitivity() const;
	const float camera_getYaw() const;
	const float camera_getPitch() const;
	const float camera_getFirstPersonYaw() const;
	const float camera_getFirstPersonPitch() const;
	const float camera_getThirdPersonYaw() const;
	const float camera_getThirdPersonPitch() const;
	const float camera_getThirdPersonDistance() const;
	const float camera_getNearDistance() const;
	const float camera_getFarDistance() const;
	const bool camera_isThirdPersonViewEnabled() const;
	const bool camera_isFirstPersonViewEnabled() const;

	// Collision interface - setters
	void collision_setCameraBox(float left, float right, float bottom, float top, float back, float front);
	void collision_enableCameraResponse(bool x, bool y, bool z);
	void collision_enableTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraResponse();
	void collision_disableTerrainResponse();

	// Collision interface - getters
	const string collision_checkCameraWithAny() const;
	const string collision_checkCameraWithEntities(const string& ID) const;
	const string collision_checkEntityWithEntities(const string& selfID, const string& otherID) const;
	const bool collision_checkCameraWithTerrain() const;
	const bool collision_checkCameraWithEntity(const string& ID) const;
	const bool collision_checkCameraWithEntityDirection(const string& ID, Direction direction) const;
	const bool collision_checkCameraWithAnyDirection(Direction direction) const;
	const bool collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction) const;
	const bool collision_isCameraResponseEnabled() const;
	const bool collision_isTerrainResponseEnabled() const;

	// Raycast inferface - setters
	void raycast_enableTerrainPointing(float distance, float precision);
	void raycast_disableTerrainPointing();

	// Raycast inferface - getters
	const pair<const string, float> raycast_checkCursorInAny();
	const pair<const string, float> raycast_checkCursorInEntities(const string& ID, bool canBeOccluded);
	const pair<bool, float> raycast_checkCursorInEntity(const string& ID, bool canBeOccluded);
	const Vec3 raycast_getPointOnTerrain() const;
	const bool raycast_isPointOnTerrainValid() const;
	const bool raycast_isTerrainPointingEnabled() const;
	const Ray raycast_getCursorRay() const;

	// Graphics interface - setters
	void gfx_enableAmbientLighting();
	void gfx_enableDirectionalLighting();
	void gfx_enableFog();
	void gfx_enableAntiAliasing();
	void gfx_enableShadows();
	void gfx_enableBloom();
	void gfx_enableSkyExposure();
	void gfx_enableDOF();
	void gfx_enableMotionBlur();
	void gfx_enableLensFlare();
	void gfx_disableAmbientLighting(bool mustResetProperties);
	void gfx_disableDirectionalLighting(bool mustResetProperties);
	void gfx_disableFog(bool mustResetProperties);
	void gfx_disableAntiAliasing(bool mustResetProperties);
	void gfx_disableShadows(bool mustResetProperties);
	void gfx_disableBloom(bool mustResetProperties);
	void gfx_disableSkyExposure(bool mustResetProperties);
	void gfx_disableDOF(bool mustResetProperties);
	void gfx_disableMotionBlur(bool mustResetProperties);
	void gfx_disableLensFlare(bool mustResetProperties);
	void gfx_setPlanarReflectionHeight(float height);
	void gfx_setBloomSize(unsigned int size);
	void gfx_setDofSize(unsigned int size);
	void gfx_setMotionBlurSize(unsigned int size);
	void gfx_setAnisotropicFilteringQuality(unsigned int quality);
	void gfx_setCubeReflectionQuality(unsigned int quality);
	void gfx_setPlanarReflectionQuality(unsigned int quality);
	void gfx_setRefractionQuality(unsigned int quality);
	void gfx_setShadowQuality(unsigned int quality);
	void gfx_setAmbientLightingColor(Vec3 color);
	void gfx_setAmbientLightingIntensity(float intensity);
	void gfx_setDirectionalLightingPosition(Vec3 position);
	void gfx_setDirectionalLightingColor(Vec3 color);
	void gfx_setDirectionalLightingIntensity(float intensity);
	void gfx_setFogColor(Vec3 color);
	void gfx_setFogThickness(float thickness);
	void gfx_setFogMinDistance(float minDistance);
	void gfx_setFogMaxDistance(float maxDistance);
	void gfx_setShadowEyePosition(Vec3 position);
	void gfx_setShadowCenterPosition(Vec3 position);
	void gfx_setShadowAreaSize(float size);
	void gfx_setShadowAreaReach(float reach);
	void gfx_setShadowLightness(float lightness);
	void gfx_setShadowInterval(unsigned int interval);
	void gfx_setShadowFollowingCamera(bool isFollowingCamera);
	void gfx_setBloomIntensity(float intensity);
	void gfx_setBloomBlurCount(unsigned int blurCount);
	void gfx_setBloomType(BloomType type);
	void gfx_setSkyExposureIntensity(float intensity);
	void gfx_setSkyExposureSpeed(float speed);
	void gfx_setDofMaxDistance(float maxDistance);
	void gfx_setDofBlurDistance(float blurDistance);
	void gfx_setDofDynamic(bool isDynamic);
	void gfx_setMotionBlurStrength(float strength);
	void gfx_setLensFlareMap(const string& texturePath);
	void gfx_setLensFlareIntensity(float intensity);
	void gfx_setLensFlareSensitivity(float size);

	// Graphics interface - getters
	const string& gfx_getLensFlareMapPath() const;
	const Vec3 gfx_getDirectionalLightingPosition() const;
	const Vec3 gfx_getAmbientLightingColor() const;
	const Vec3 gfx_getDirectionalLightingColor() const;
	const Vec3 gfx_getFogColor() const;
	const Vec3 gfx_getShadowEye() const;
	const Vec3 gfx_getShadowCenter() const;
	const float gfx_getAmbientLightingIntensity() const;
	const float gfx_getDirectionalLightingIntensity() const;
	const float gfx_getFogMinDistance() const;
	const float gfx_getFogMaxDistance() const;
	const float gfx_getFogThickness() const;
	const float gfx_getPlanarReflectionHeight() const;
	const float gfx_getShadowSize() const;
	const float gfx_getShadowReach() const;
	const float gfx_getShadowLightness() const;
	const float gfx_getBloomIntensity() const;
	const float gfx_getSkyExposureIntensity() const;
	const float gfx_getSkyExposureSpeed() const;
	const float gfx_getaMaxDofDistance() const;
	const float gfx_getDofBlurDistance() const;
	const float gfx_getLensFlareIntensity() const;
	const float gfx_getLensFlareSensitivity() const;
	const float gfx_getMotionBlurStrength() const;
	const unsigned int gfx_getBloomSize() const;
	const unsigned int gfx_getDofSize() const;
	const unsigned int gfx_getMotionBlurSize() const;
	const unsigned int gfx_getAnisotropicFilteringQuality() const;
	const unsigned int gfx_getShadowQuality() const;
	const unsigned int gfx_getCubeReflectionQuality() const;
	const unsigned int gfx_getPlanarReflectionQuality() const;
	const unsigned int gfx_getRefractionQuality() const;
	const unsigned int gfx_getBloomBlurCount() const;
	const unsigned int gfx_getShadowInterval() const;
	const bool gfx_isAntiAliasingEnabled() const;
	const bool gfx_isAmbientLightingEnabled() const;
	const bool gfx_isDirectionalLightingEnabled() const;
	const bool gfx_isFogEnabled() const;
	const bool gfx_isBloomEnabled() const;
	const bool gfx_isSkyExposureEnabled() const;
	const bool gfx_isShadowsEnabled() const;
	const bool gfx_isDofEnabled() const;
	const bool gfx_isDofDynamic() const;
	const bool gfx_isMotionBlurEnabled() const;
	const bool gfx_isLensFlareEnabled() const;
	const bool gfx_isShadowFollowingCamera() const;
	const BloomType gfx_getBloomType() const;

	// Server interface - setters
	void networkServer_start(unsigned int maxClientCount);
	void networkServer_sendMessageTCP(const string& username, const string& content);
	void networkServer_sendMessageUDP(const string& username, const string& content);
	void networkServer_broadcastMessageTCP(const string& content, const string& exceptionUsername);
	void networkServer_broadcastMessageUDP(const string& content, const string& exceptionUsername);
	void networkServer_disconnectClient(const string& username);
	void networkServer_disconnectClients();
	void networkServer_stop();

	// Server interface - getters
	const vector<NetworkClientMessage> networkServer_getPendingMessages() const;
	const vector<string> networkServer_getClientIPs() const;
	const vector<string> networkServer_getClientUsernames() const;
	const string networkServer_getNewClientIP() const;
	const string networkServer_getNewClientUsername() const;
	const string networkServer_getOldClientIP() const;
	const string networkServer_getOldClientUsername() const;
	const bool networkServer_isRunning() const;
	const bool networkServer_isClientConnected(const string& username) const;

	// Client interface - setters
	void networkClient_start(const string& username);
	void networkClient_connect(const string& serverIP);
	void networkClient_sendMessageTCP(const string& content);
	void networkClient_sendMessageUDP(const string& content);
	void networkClient_disconnect();
	void networkClient_stop();

	// Client interface - getters
	const vector<NetworkServerMessage> networkClient_getPendingMessages() const;
	const string networkClient_getUsername() const;
	const string networkClient_getServerIP() const;
	const unsigned int networkClient_getPingLatency() const;
	const bool networkClient_isValidServerIP(const string& serverIP) const;
	const bool networkClient_isRunning() const;
	const bool networkClient_isConnecting() const;
	const bool networkClient_isConnected() const;
	const bool networkClient_isAccepted() const;

	// Miscellaneous interface - setters
	void misc_enableWireframeRendering();
	void misc_enableShadowFrameRendering();
	void misc_enableAabbFrameRendering();
	void misc_enableDebugRendering();
	void misc_enableVsync();
	void misc_enableSounds();
	void misc_enableMusic();
	void misc_disableWireframeRendering();
	void misc_disableShadowFrameRendering();
	void misc_disableAabbFrameRendering();
	void misc_disableDebugRendering();
	void misc_disableVsync();
	void misc_disableSounds();
	void misc_disableMusic();
	void misc_setCursorVisible(bool isVisible);
	void misc_setCustomCursor(const string& imageEntityID);
	void misc_centerCursor();
	void misc_setCursorPosition(Ivec2 pos);
	void misc_setWindowTitle(const string& title);
	void misc_clearMeshCache(const string& filePath);
	void misc_clearTextureCache2D(const string& filePath);
	void misc_clearTextureCache3D(const array<string, 6>& filePaths);
	void misc_clearFontCache(const string& filePath);
	void misc_clearBitmapCache(const string& filePath);
	void misc_clearAudioCache(const string& filePath);
	void misc_cacheMeshesMultiThreaded(const vector<string>& filePaths);
	void misc_cacheTexturesMultiThreaded2D(const vector<string>& filePaths);
	void misc_cacheTexturesMultiThreaded3D(const vector<array<string, 6>>& filePaths);
	void misc_cacheBitmapsMultiThreaded(const vector<string>& filePaths);
	void misc_cacheFontsMultiThreaded(const vector<string>& filePaths);
	void misc_cacheSoundsMultiThreaded(const vector<string>& filePaths);
	void misc_cacheMusicMultiThreaded(const vector<string>& filePaths);
	void misc_startMillisecondTimer();
	void misc_setLevelOfDetailDistance(float distance);
	void misc_setMaxAudioChannelCount(unsigned int count);

	// Miscellaneous interface - getters
	const vector<pair<string, int>> misc_getUpdateProfilingStatistics() const;
	const vector<pair<string, int>> misc_getRenderProfilingStatistics() const;
	const string misc_getCpuModel() const;
	const string misc_getGpuModel() const;
	const string misc_getOpenglVersion() const;
	const Ivec2 misc_getCursorPosition() const;
	const Ivec2 misc_getCursorPositionRelativeToViewport() const;
	const float misc_getFPS() const;
	const float misc_stopMillisecondTimer() const;
	const float misc_getLevelOfDetailDistance() const;
	const unsigned int misc_getTriangleCount() const;
	const unsigned int misc_getMaxAudioChannelCount() const;
	const bool misc_isCursorVisible() const;
	const bool misc_isCursorInsideViewport() const;
	const bool misc_isCursorInsideWindow() const;
	const bool misc_checkInterval(unsigned int ticks) const;
	const bool misc_isMillisecondTimerStarted() const;
	const bool misc_isVsyncEnabled() const;
	const bool misc_isWireframeRenderingEnabled() const;
	const bool misc_isShadowFrameRenderingEnabled() const;
	const bool misc_isAabbFrameRenderingEnabled() const;
	const bool misc_isDebugRenderingEnabled() const;
	const bool misc_isSoundsEnabled() const;
	const bool misc_isMusicEnabled() const;

protected:
	virtual void FE3D_CONTROLLER_INIT() = 0;
	virtual void FE3D_CONTROLLER_UPDATE() = 0;
	virtual void FE3D_CONTROLLER_DESTROY() = 0;

private:
	// Strings
	string _hoveredAabbID = "";

	// Decimals
	float _hoveredAabbDistance = -1.0f;

	// Booleans
	bool _isRaycastUpdated = false;

	// Miscellaneous
	CoreEngine* _core = nullptr;
};
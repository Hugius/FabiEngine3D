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
	const string& application_getTitle();
	bool application_isPaused();
	bool application_isExported();

	// Sky entity interface - setters
	void skyEntity_create(const string& ID);
	void skyEntity_deleteAll();
	void skyEntity_delete(const string& ID);
	void skyEntity_setVisible(const string& ID, bool isVisible);
	void skyEntity_selectMainSky(const string& ID);
	void skyEntity_selectMixSky(const string& ID);
	void skyEntity_setMixValue(float mixValue);
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
	void skyEntity_setWireFramed(const string& ID, bool enabled);

	// Sky entity interface - getters
	const vector<string> skyEntity_getAllIDs() const;
	const array<string, 6>& skyEntity_getDiffuseMapPaths(const string& ID) const;
	const string& skyEntity_getSelectedID() const;
	const string& skyEntity_getMixID() const;
	const Vec3 skyEntity_getColor(const string& ID) const;
	const float skyEntity_getLightness(const string& ID) const;
	const float skyEntity_getOriginalLightness(const string& ID) const;
	const float skyEntity_getRotationSpeed(const string& ID) const;
	const float skyEntity_getMixValue() const;
	const bool skyEntity_isExisting(const string& ID) const;
	const bool skyEntity_isVisible(const string& ID) const;
	const bool skyEntity_isWireFramed(const string& ID) const;
	const bool skyEntity_hasDiffuseMapRight(const string& ID) const;
	const bool skyEntity_hasDiffuseMapLeft(const string& ID) const;
	const bool skyEntity_hasDiffuseMapTop(const string& ID) const;
	const bool skyEntity_hasDiffuseMapBottom(const string& ID) const;
	const bool skyEntity_hasDiffuseMapBack(const string& ID) const;
	const bool skyEntity_hasDiffuseMapFront(const string& ID) const;

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
	void terrainEntity_setWireFramed(const string& ID, bool enabled);

	// Terrain entity interface - getters
	const vector<string> terrainEntity_getAllIDs();
	const string& terrainEntity_getSelectedID();
	const string& terrainEntity_getHeightMapPath(const string& ID);
	const string& terrainEntity_getBlendMapPath(const string& ID);
	const string& terrainEntity_getDiffuseMapPath(const string& ID);
	const string& terrainEntity_getDiffuseMapPathR(const string& ID);
	const string& terrainEntity_getDiffuseMapPathG(const string& ID);
	const string& terrainEntity_getDiffuseMapPathB(const string& ID);
	const string& terrainEntity_getNormalMapPath(const string& ID);
	const string& terrainEntity_getNormalMapPathR(const string& ID);
	const string& terrainEntity_getNormalMapPathG(const string& ID);
	const string& terrainEntity_getNormalMapPathB(const string& ID);
	const float terrainEntity_getMaxHeight(const string& ID);
	const float terrainEntity_getTextureRepeat(const string& ID);
	const float terrainEntity_getLightness(const string& ID);
	const float terrainEntity_getRedRepeat(const string& ID);
	const float terrainEntity_getGreenRepeat(const string& ID);
	const float terrainEntity_getBlueRepeat(const string& ID);
	const float terrainEntity_getSize(const string& ID);
	const float terrainEntity_getPixelHeight(const string& ID, float x, float z);
	const float terrainEntity_getSpecularShininess(const string& ID);
	const float terrainEntity_getSpecularIntensity(const string& ID);
	const bool terrainEntity_isExisting(const string& ID);
	const bool terrainEntity_isVisible(const string& ID);
	const bool terrainEntity_isSpecular(const string& ID);
	const bool terrainEntity_isWireFramed(const string& ID);
	const bool terrainEntity_isInside(const string& ID, float x, float z);
	const bool terrainEntity_hasBlendMap(const string& ID);
	const bool terrainEntity_hasDiffuseMap(const string& ID);
	const bool terrainEntity_hasDiffuseMapR(const string& ID);
	const bool terrainEntity_hasDiffuseMapG(const string& ID);
	const bool terrainEntity_hasDiffuseMapB(const string& ID);
	const bool terrainEntity_hasNormalMap(const string& ID);
	const bool terrainEntity_hasNormalMapR(const string& ID);
	const bool terrainEntity_hasNormalMapG(const string& ID);
	const bool terrainEntity_hasNormalMapB(const string& ID);

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
	void waterEntity_setWireFramed(const string& ID, bool enabled);
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
	const vector<string> waterEntity_getAllIDs();
	const string& waterEntity_getDudvMapPath(const string& ID);
	const string& waterEntity_getNormalMapPath(const string& ID);
	const string& waterEntity_getDisplacementMapPath(const string& ID);
	const string& waterEntity_getSelectedID();
	const Vec3 waterEntity_getColor(const string& ID);
	const Vec2 waterEntity_getSpeed(const string& ID);
	const float waterEntity_getHeight(const string& ID);
	const float waterEntity_getSize(const string& ID);
	const float waterEntity_getTextureRepeat(const string& ID);
	const float waterEntity_getWaveHeight(const string& ID);
	const float waterEntity_getSpecularShininess(const string& ID);
	const float waterEntity_getSpecularIntensity(const string& ID);
	const float waterEntity_getTransparency(const string& ID);
	const bool waterEntity_isExisting(const string& ID);
	const bool waterEntity_isVisible(const string& ID);
	const bool waterEntity_isSpecular(const string& ID);
	const bool waterEntity_isReflective(const string& ID);
	const bool waterEntity_isRefractive(const string& ID);
	const bool waterEntity_isWireFramed(const string& ID);
	const bool waterEntity_hasDudvMap(const string& ID);
	const bool waterEntity_hasNormalMap(const string& ID);
	const bool waterEntity_hasDisplacementMap(const string& ID);
	const WaterQuality waterEntity_getQuality(const string& ID);

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
	void modelEntity_setWireFramed(const string& ID, bool enabled);
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
	void modelEntity_setAlpha(const string& ID, const string& partID, float alpha);
	void modelEntity_setColor(const string& ID, const string& partID, Vec3 color);
	void modelEntity_setMinHeight(const string& ID, float height);
	void modelEntity_setMaxHeight(const string& ID, float height);
	void modelEntity_setTextureRepeat(const string& ID, const string& partID, float repeat);
	void modelEntity_enableInstancing(const string& ID, vector<Vec3> offsets);
	void modelEntity_disableInstancing(const string& ID);
	void modelEntity_setBright(const string& ID, bool enabled);
	void modelEntity_setRotationOrder(const string& ID, DirectionOrder order);

	// Model entity interface - getters
	const vector<string> modelEntity_getPartIDs(const string& ID);
	const vector<string> modelEntity_getAllIDs();
	const vector<string> modelEntity_getGroupIDs(const string& ID);
	const string& modelEntity_getMeshPath(const string& ID);
	const string& modelEntity_getDiffuseMapPath(const string& ID, const string& partID);
	const string& modelEntity_getEmissionMapPath(const string& ID, const string& partID);
	const string& modelEntity_getSpecularMapPath(const string& ID, const string& partID);
	const string& modelEntity_getReflectionMapPath(const string& ID, const string& partID);
	const string& modelEntity_getNormalMapPath(const string& ID, const string& partID);
	const string& modelEntity_getLevelOfDetailEntityID(const string& ID);
	const vector<Vec3>& modelEntity_getInstancedOffsets(const string& ID);
	const Vec3 modelEntity_getLevelOfDetailSize(const string& ID);
	const Vec3 modelEntity_getBasePosition(const string& ID);
	const Vec3 modelEntity_getBaseRotation(const string& ID);
	const Vec3 modelEntity_getBaseRotationOrigin(const string& ID);
	const Vec3 modelEntity_getBaseSize(const string& ID);
	const Vec3 modelEntity_getPartPosition(const string& ID, const string& partID);
	const Vec3 modelEntity_getPartRotation(const string& ID, const string& partID);
	const Vec3 modelEntity_getPartRotationOrigin(const string& ID, const string& partID);
	const Vec3 modelEntity_getPartSize(const string& ID, const string& partID);
	const Vec3 modelEntity_getColor(const string& ID, const string& partID);
	const float modelEntity_getColorInversion(const string& ID, const string& partID);
	const float modelEntity_getReflectivity(const string& ID, const string& partID);
	const float modelEntity_getLightness(const string& ID, const string& partID);
	const float modelEntity_getSpecularShininess(const string& ID, const string& partID);
	const float modelEntity_getSpecularIntensity(const string& ID, const string& partID);
	const float modelEntity_getAlpha(const string& ID, const string& partID);
	const float modelEntity_getMinHeight(const string& ID);
	const float modelEntity_getMaxHeight(const string& ID);
	const float modelEntity_getTextureRepeat(const string& ID, const string& partID);
	const float modelEntity_getEmissionIntensity(const string& ID, const string& partID);
	const bool modelEntity_isExisting(const string& ID);
	const bool modelEntity_isVisible(const string& ID);
	const bool modelEntity_isInstanced(const string& ID);
	const bool modelEntity_isMultiParted(const string& ID);
	const bool modelEntity_isFaceCulled(const string& ID);
	const bool modelEntity_isSpecular(const string& ID, const string& partID);
	const bool modelEntity_isShadowed(const string& ID);
	const bool modelEntity_isReflected(const string& ID);
	const bool modelEntity_isStaticToCamera(const string& ID);
	const bool modelEntity_isWireFramed(const string& ID);
	const bool modelEntity_isDepthMapIncluded(const string& ID);
	const bool modelEntity_hasPart(const string& ID, const string& partID);
	const bool modelEntity_isBright(const string& ID);
	const bool modelEntity_isReflective(const string& ID, const string& partID);
	const bool modelEntity_hasDiffuseMap(const string& ID, const string& partID);
	const bool modelEntity_hasEmissionMap(const string& ID, const string& partID);
	const bool modelEntity_hasSpecularMap(const string& ID, const string& partID);
	const bool modelEntity_hasReflectionMap(const string& ID, const string& partID);
	const bool modelEntity_hasNormalMap(const string& ID, const string& partID);
	const ReflectionType modelEntity_getReflectionType(const string& ID, const string& partID);
	const DirectionOrder modelEntity_getRotationOrder(const string& ID);

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
	void billboardEntity_setAlpha(const string& ID, float alpha);
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
	void billboardEntity_setWireFramed(const string& ID, bool enabled);

	// Billboard entity interface - getters
	const vector<string> billboardEntity_getAllIDs();
	const string& billboardEntity_getDiffuseMapPath(const string& ID);
	const string& billboardEntity_getEmissionMapPath(const string& ID);
	const string& billboardEntity_getFontPath(const string& ID);
	const string& billboardEntity_getTextContent(const string& ID);
	const Vec3 billboardEntity_getPosition(const string& ID);
	const Vec3 billboardEntity_getRotation(const string& ID);
	const Vec2 billboardEntity_getSize(const string& ID);
	const Vec3 billboardEntity_getColor(const string& ID);
	const float billboardEntity_getLightness(const string& ID);
	const float billboardEntity_getColorInversion(const string& ID);
	const float billboardEntity_getMinHeight(const string& ID);
	const float billboardEntity_getMaxHeight(const string& ID);
	const float billboardEntity_getAlpha(const string& ID);
	const float billboardEntity_getTextureRepeat(const string& ID);
	const float billboardEntity_getEmissionIntensity(const string& ID);
	const int billboardEntity_getRemainingSpriteAnimationLoops(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationRows(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationColumns(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationFramestep(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationRowIndex(const string& ID);
	const unsigned int billboardEntity_getSpriteAnimationColumnIndex(const string& ID);
	const bool billboardEntity_isExisting(const string& ID);
	const bool billboardEntity_isVisible(const string& ID);
	const bool billboardEntity_isFacingCameraX(const string& ID);
	const bool billboardEntity_isFacingCameraY(const string& ID);
	const bool billboardEntity_isDepthMapIncluded(const string& ID);
	const bool billboardEntity_isShadowed(const string& ID);
	const bool billboardEntity_isReflected(const string& ID);
	const bool billboardEntity_isBright(const string& ID);
	const bool billboardEntity_isWireFramed(const string& ID);
	const bool billboardEntity_isSpriteAnimationStarted(const string& ID);
	const bool billboardEntity_isSpriteAnimationPlaying(const string& ID);
	const bool billboardEntity_isSpriteAnimationPaused(const string& ID);
	const bool billboardEntity_hasDiffuseMap(const string& ID);
	const bool billboardEntity_hasEmissionMap(const string& ID);
	const bool billboardEntity_isText(const string& ID);

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
	const vector<string> aabbEntity_getChildIDs(const string& parentID, AabbParentType parentType);
	const vector<string> aabbEntity_getAllIDs();
	const string& aabbEntity_getParentID(const string& ID);
	const Vec3 aabbEntity_getPosition(const string& ID);
	const Vec3 aabbEntity_getSize(const string& ID);
	const bool aabbEntity_isRaycastResponsive(const string& ID);
	const bool aabbEntity_isCollisionResponsive(const string& ID);
	const bool aabbEntity_isExisting(const string& ID);
	const bool aabbEntity_isVisible(const string& ID);
	const bool aabbEntity_hasParent(const string& ID);
	const AabbParentType aabbEntity_getParentType(const string& ID);

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
	const vector<string> pointlightEntity_getAllIDs();
	const Vec3 pointlightEntity_getPosition(const string& ID);
	const Vec3 pointlightEntity_getRadius(const string& ID);
	const Vec3 pointlightEntity_getColor(const string& ID);
	const float pointlightEntity_getIntensity(const string& ID);
	const bool pointlightEntity_isExisting(const string& ID);
	const bool pointlightEntity_isVisible(const string& ID);
	const PointlightShape pointlightEntity_getShape(const string& ID);

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
	const vector<string> spotlightEntity_getAllIDs();
	const Vec3 spotlightEntity_getPosition(const string& ID);
	const Vec3 spotlightEntity_getColor(const string& ID);
	const float spotlightEntity_getYaw(const string& ID);
	const float spotlightEntity_getPitch(const string& ID);
	const float spotlightEntity_getIntensity(const string& ID);
	const float spotlightEntity_getAngle(const string& ID);
	const float spotlightEntity_getDistance(const string& ID);
	const bool spotlightEntity_isExisting(const string& ID);
	const bool spotlightEntity_isVisible(const string& ID);

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
	const vector<string> reflectionEntity_getAllIDs();
	const Vec3 reflectionEntity_getPosition(const string& ID);
	const bool reflectionEntity_isExisting(const string& ID);
	const bool reflectionEntity_isVisible(const string& ID);

	// Image entity interface - setters
	void imageEntity_create(const string& ID, bool isCentered);
	void imageEntity_deleteAll();
	void imageEntity_delete(const string& ID);
	void imageEntity_setVisible(const string& ID, bool isVisible);
	void imageEntity_setDiffuseMap(const string& ID, const string& texturePath);
	void imageEntity_setColor(const string& ID, Vec3 color);
	void imageEntity_setAlpha(const string& ID, float alpha);
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
	const vector<string> imageEntity_getAllIDs();
	const string& imageEntity_getDiffuseMapPath(const string& ID);
	const Vec3 imageEntity_getColor(const string& ID);
	const Vec2 imageEntity_getPosition(const string& ID);
	const Vec2 imageEntity_getSize(const string& ID);
	const Vec2 imageEntity_getMinPosition(const string& ID);
	const Vec2 imageEntity_getMaxPosition(const string& ID);
	const float imageEntity_getRotation(const string& ID);
	const float imageEntity_getAlpha(const string& ID);
	const int imageEntity_getRemainingSpriteAnimationLoops(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationRows(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationColumns(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationFramestep(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationRowIndex(const string& ID);
	const unsigned int imageEntity_getSpriteAnimationColumnIndex(const string& ID);
	const bool imageEntity_isExisting(const string& ID);
	const bool imageEntity_isVisible(const string& ID);
	const bool imageEntity_isCentered(const string& ID);
	const bool imageEntity_isMirroredHorizontally(const string& ID);
	const bool imageEntity_isMirroredVertically(const string& ID);
	const bool imageEntity_isSpriteAnimationStarted(const string& ID);
	const bool imageEntity_isSpriteAnimationPlaying(const string& ID);
	const bool imageEntity_isSpriteAnimationPaused(const string& ID);
	const bool imageEntity_hasDiffuseMap(const string& ID);

	// Text entity interface - setters
	void textEntity_create(const string& ID, bool isCentered, bool isDynamic);
	void textEntity_deleteAll();
	void textEntity_delete(const string& ID);
	void textEntity_setVisible(const string& ID, bool isVisible);
	void textEntity_setFont(const string& ID, const string& fontPath);
	void textEntity_setTextContent(const string& ID, const string& textContent, float charWidth = -1.0f, float charHeight = -1.0f);
	void textEntity_setColor(const string& ID, Vec3 color);
	void textEntity_setAlpha(const string& ID, float alpha);
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
	const vector<string> textEntity_getAllIDs();
	const string& textEntity_getFontPath(const string& ID);
	const string& textEntity_getTextContent(const string& ID);
	const Vec3 textEntity_getColor(const string& ID);
	const Vec2 textEntity_getPosition(const string& ID);
	const Vec2 textEntity_getSize(const string& ID);
	const Vec2 textEntity_getMinPosition(const string& ID);
	const Vec2 textEntity_getMaxPosition(const string& ID);
	const float textEntity_getRotation(const string& ID);
	const float textEntity_getAlpha(const string& ID);
	const bool textEntity_isExisting(const string& ID);
	const bool textEntity_isVisible(const string& ID);

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
	const vector<string> sound_getAllIDs();
	const string& sound_getFilePath(const string& ID);
	const Vec3 sound_getPosition(const string& ID);
	const float sound_getMaxDistance(const string& ID);
	const float sound_getVolume(const string& ID);
	const float sound_getMaxVolume(const string& ID);
	const unsigned int sound_getUsedChannelCount();
	const bool sound_isExisting(const string& ID);
	const bool sound_isStarted(const string& ID);
	const bool sound_isPlaying(const string& ID);
	const bool sound_isPaused(const string& ID);
	const bool sound_isLoaded(const string& ID);
	const bool sound_is3D(const string& ID);

	// Music interface - setters
	void music_addToPlaylist(const string& filePath);
	void music_clearPlaylist();
	void music_setVolume(float volume);
	void music_pause();
	void music_resume();

	// Music interface - getters
	const float music_getVolume();
	const bool music_isStarted();
	const bool music_isPlaying();
	const bool music_isPaused();

	// Input interface - setters
	void input_setLocked(bool locked);

	// Input interface - getters
	const int input_getMouseWheelX();
	const int input_getMouseWheelY();
	const bool input_isLocked();
	const bool input_isKeyDown(InputType key);
	const bool input_isKeyPressed(InputType key);
	const bool input_isMouseDown(InputType button);
	const bool input_isMousePressed(InputType button);

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
	void camera_setNearDistance(float distance);
	void camera_setFarDistance(float distance);
	void camera_setCursorSensitivity(float speed);

	// Camera interface - getters
	const Vec3 camera_getPosition();
	const Vec3 camera_getUpVector();
	const Vec3 camera_getFrontVector();
	const Vec3 camera_getRightVector();
	const Vec3 camera_getThirdPersonLookat();
	const float camera_getFOV();
	const float camera_getAspectRatio();
	const float camera_getCursorSensitivity();
	const float camera_getYaw();
	const float camera_getPitch();
	const float camera_getFirstPersonYaw();
	const float camera_getFirstPersonPitch();
	const float camera_getThirdPersonYaw();
	const float camera_getThirdPersonPitch();
	const float camera_getThirdPersonDistance();
	const float camera_getNearDistance();
	const float camera_getFarDistance();
	const bool camera_isThirdPersonViewEnabled();
	const bool camera_isFirstPersonViewEnabled();

	// Collision interface - setters
	void collision_setCameraBox(float left, float right, float bottom, float top, float back, float front);
	void collision_enableCameraResponse(bool x, bool y, bool z);
	void collision_enableTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraResponse();
	void collision_disableTerrainResponse();

	// Collision interface - getters
	const string collision_checkCameraWithAny();
	const string collision_checkCameraWithEntities(const string& ID);
	const string collision_checkEntityWithEntities(const string& selfID, const string& otherID);
	const bool collision_checkCameraWithTerrain();
	const bool collision_checkCameraWithEntity(const string& ID);
	const bool collision_checkCameraWithEntityDirection(const string& ID, Direction direction);
	const bool collision_checkCameraWithAnyDirection(Direction direction);
	const bool collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction);
	const bool collision_isCameraResponseEnabled();
	const bool collision_isTerrainResponseEnabled();

	// Raycast inferface - setters
	void raycast_enableTerrainPointing(float distance, float precision);
	void raycast_disableTerrainPointing();

	// Raycast inferface - getters
	const pair<const string, float> raycast_checkCursorInAny();
	const pair<const string, float> raycast_checkCursorInEntities(const string& ID, bool canBeOccluded);
	const pair<bool, float> raycast_checkCursorInEntity(const string& ID, bool canBeOccluded);
	const Vec3 raycast_getPointOnTerrain();
	const bool raycast_isPointOnTerrainValid();
	const bool raycast_isTerrainPointingEnabled();
	const Ray raycast_getCursorRay();

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
	const string& gfx_getLensFlareMapPath();
	const Vec3 gfx_getDirectionalLightingPosition();
	const Vec3 gfx_getAmbientLightingColor();
	const Vec3 gfx_getDirectionalLightingColor();
	const Vec3 gfx_getFogColor();
	const Vec3 gfx_getShadowEye();
	const Vec3 gfx_getShadowCenter();
	const float gfx_getAmbientLightingIntensity();
	const float gfx_getDirectionalLightingIntensity();
	const float gfx_getFogMinDistance();
	const float gfx_getFogMaxDistance();
	const float gfx_getFogThickness();
	const float gfx_getPlanarReflectionHeight();
	const float gfx_getShadowSize();
	const float gfx_getShadowReach();
	const float gfx_getShadowLightness();
	const float gfx_getBloomIntensity();
	const float gfx_getSkyExposureIntensity();
	const float gfx_getSkyExposureSpeed();
	const float gfx_getaMaxDofDistance();
	const float gfx_getDofBlurDistance();
	const float gfx_getLensFlareIntensity();
	const float gfx_getLensFlareSensitivity();
	const float gfx_getMotionBlurStrength();
	const unsigned int gfx_getBloomSize();
	const unsigned int gfx_getDofSize();
	const unsigned int gfx_getMotionBlurSize();
	const unsigned int gfx_getAnisotropicFilteringQuality();
	const unsigned int gfx_getShadowQuality();
	const unsigned int gfx_getCubeReflectionQuality();
	const unsigned int gfx_getPlanarReflectionQuality();
	const unsigned int gfx_getRefractionQuality();
	const unsigned int gfx_getBloomBlurCount();
	const unsigned int gfx_getShadowInterval();
	const bool gfx_isAntiAliasingEnabled();
	const bool gfx_isAmbientLightingEnabled();
	const bool gfx_isDirectionalLightingEnabled();
	const bool gfx_isFogEnabled();
	const bool gfx_isBloomEnabled();
	const bool gfx_isSkyExposureEnabled();
	const bool gfx_isShadowsEnabled();
	const bool gfx_isDofEnabled();
	const bool gfx_isDofDynamic();
	const bool gfx_isMotionBlurEnabled();
	const bool gfx_isLensFlareEnabled();
	const bool gfx_isShadowFollowingCamera();
	const BloomType gfx_getBloomType();

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
	const vector<NetworkClientMessage>& networkServer_getPendingMessages();
	const vector<string> networkServer_getClientIPs();
	const vector<string> networkServer_getClientUsernames();
	const string networkServer_getNewClientIP() const;
	const string networkServer_getNewClientUsername() const;
	const string networkServer_getOldClientIP() const;
	const string networkServer_getOldClientUsername() const;
	const bool networkServer_isRunning();
	const bool networkServer_isClientConnected(const string& username);

	// Client interface - setters
	void networkClient_start(const string& username);
	void networkClient_connect(const string& serverIP);
	void networkClient_sendMessageTCP(const string& content);
	void networkClient_sendMessageUDP(const string& content);
	void networkClient_disconnect();
	void networkClient_stop();

	// Client interface - getters
	const vector<NetworkServerMessage>& networkClient_getPendingMessages();
	const string& networkClient_getUsername();
	const string& networkClient_getServerIP();
	const unsigned int networkClient_getPingLatency();
	const bool networkClient_isValidServerIP(const string& serverIP);
	const bool networkClient_isRunning();
	const bool networkClient_isConnecting();
	const bool networkClient_isConnected();
	const bool networkClient_isAccepted();

	// Miscellaneous interface - setters
	void misc_enableWireFrameRendering();
	void misc_enableShadowFrameRendering();
	void misc_enableAabbFrameRendering();
	void misc_enableDebugRendering();
	void misc_enableVsync();
	void misc_enableSounds();
	void misc_enableMusic();
	void misc_disableWireFrameRendering();
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
	const vector<pair<string, int>> misc_getUpdateProfilingStatistics();
	const vector<pair<string, int>> misc_getRenderProfilingStatistics();
	const string misc_getCpuModel();
	const string misc_getGpuModel();
	const string misc_getOpenglVersion();
	const Ivec2 misc_getCursorPosition();
	const Ivec2 misc_getCursorPositionRelativeToViewport();
	const float misc_getFPS();
	const float misc_stopMillisecondTimer();
	const float misc_getLevelOfDetailDistance();
	const unsigned int misc_getTriangleCount();
	const unsigned int misc_getMaxAudioChannelCount();
	const bool misc_isCursorVisible();
	const bool misc_isCursorInsideViewport();
	const bool misc_isCursorInsideWindow();
	const bool misc_checkInterval(unsigned int ticks);
	const bool misc_isMillisecondTimerStarted();
	const bool misc_isVsyncEnabled();
	const bool misc_isWireFrameRenderingEnabled();
	const bool misc_isShadowFrameRenderingEnabled();
	const bool misc_isAabbFrameRenderingEnabled();
	const bool misc_isDebugRenderingEnabled();
	const bool misc_isSoundsEnabled();
	const bool misc_isMusicEnabled();

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
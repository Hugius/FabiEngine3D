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

	// APPLICATION - setters
	void application_start();
	void application_pause();
	void application_resume();
	void application_stop();

	// APPLICATION - getters
	const bool application_isPaused() const;

	// SKY - setters
	void sky_create(const string& ID);
	void sky_deleteAll();
	void sky_delete(const string& ID);
	void sky_setVisible(const string& ID, bool isVisible);
	void sky_selectMainSky(const string& ID);
	void sky_selectMixSky(const string& ID);
	void sky_setMixValue(float mixValue);
	void sky_setCubeMaps(const string& ID, const array<string, 6>& texturePaths);
	void sky_setCubeMapRight(const string& ID, const string& texturePath);
	void sky_setCubeMapLeft(const string& ID, const string& texturePath);
	void sky_setCubeMapTop(const string& ID, const string& texturePath);
	void sky_setCubeMapBottom(const string& ID, const string& texturePath);
	void sky_setCubeMapBack(const string& ID, const string& texturePath);
	void sky_setCubeMapFront(const string& ID, const string& texturePath);
	void sky_setLightness(const string& ID, float lightness);
	void sky_setRotation(const string& ID, float rotation);
	void sky_setColor(const string& ID, fvec3 color);
	void sky_setWireframed(const string& ID, bool enabled);
	void sky_setWireframeColor(const string& ID, fvec3 color);

	// SKY - getters
	const vector<string> sky_getAllIDs() const;
	const array<string, 6>& sky_getCubeMapPaths(const string& ID) const;
	const string& sky_getCubeMapRight(const string& ID) const;
	const string& sky_getCubeMapLeft(const string& ID) const;
	const string& sky_getCubeMapTop(const string& ID) const;
	const string& sky_getCubeMapBottom(const string& ID) const;
	const string& sky_getCubeMapBack(const string& ID) const;
	const string& sky_getCubeMapFront(const string& ID) const;
	const string sky_getSelectedID() const;
	const string sky_getMixID() const;
	const fvec3 sky_getWireframeColor(const string& ID) const;
	const fvec3 sky_getColor(const string& ID) const;
	const float sky_getLightness(const string& ID) const;
	const float sky_getInitialLightness(const string& ID) const;
	const float sky_getRotation(const string& ID) const;
	const float sky_getMixValue() const;
	const bool sky_isExisting(const string& ID) const;
	const bool sky_isVisible(const string& ID) const;
	const bool sky_isWireframed(const string& ID) const;
	const bool sky_hasCubeMapRight(const string& ID) const;
	const bool sky_hasCubeMapLeft(const string& ID) const;
	const bool sky_hasCubeMapTop(const string& ID) const;
	const bool sky_hasCubeMapBottom(const string& ID) const;
	const bool sky_hasCubeMapBack(const string& ID) const;
	const bool sky_hasCubeMapFront(const string& ID) const;

	// TERRAIN - setters
	void terrain_create(const string& ID, const string& heightMapPath);
	void terrain_deleteAll();
	void terrain_delete(const string& ID);
	void terrain_setVisible(const string& ID, bool isVisible);
	void terrain_select(const string& ID);
	void terrain_setBlendMap(const string& ID, const string& texturePath);
	void terrain_setDiffuseMap(const string& ID, const string& texturePath);
	void terrain_setDiffuseMapR(const string& ID, const string& texturePath);
	void terrain_setDiffuseMapG(const string& ID, const string& texturePath);
	void terrain_setDiffuseMapB(const string& ID, const string& texturePath);
	void terrain_setNormalMap(const string& ID, const string& texturePath);
	void terrain_setNormalMapR(const string& ID, const string& texturePath);
	void terrain_setNormalMapG(const string& ID, const string& texturePath);
	void terrain_setNormalMapB(const string& ID, const string& texturePath);
	void terrain_setRedRepeat(const string& ID, float repeat);
	void terrain_setGreenRepeat(const string& ID, float repeat);
	void terrain_setBlueRepeat(const string& ID, float repeat);
	void terrain_setMaxHeight(const string& ID, float height);
	void terrain_setTextureRepeat(const string& ID, float repeat);
	void terrain_setLightness(const string& ID, float lightness);
	void terrain_setSpecularShininess(const string& ID, float shininess);
	void terrain_setSpecularIntensity(const string& ID, float intensity);
	void terrain_setSpecular(const string& ID, bool enabled);
	void terrain_setWireframed(const string& ID, bool enabled);
	void terrain_setWireframeColor(const string& ID, fvec3 color);

	// TERRAIN - getters
	const vector<string> terrain_getAllIDs() const;
	const string terrain_getSelectedID() const;
	const string& terrain_getHeightMapPath(const string& ID) const;
	const string& terrain_getBlendMapPath(const string& ID) const;
	const string& terrain_getDiffuseMapPath(const string& ID) const;
	const string& terrain_getDiffuseMapPathR(const string& ID) const;
	const string& terrain_getDiffuseMapPathG(const string& ID) const;
	const string& terrain_getDiffuseMapPathB(const string& ID) const;
	const string& terrain_getNormalMapPath(const string& ID) const;
	const string& terrain_getNormalMapPathR(const string& ID) const;
	const string& terrain_getNormalMapPathG(const string& ID) const;
	const string& terrain_getNormalMapPathB(const string& ID) const;
	const fvec3 terrain_getWireframeColor(const string& ID) const;
	const float terrain_getMaxHeight(const string& ID) const;
	const float terrain_getTextureRepeat(const string& ID) const;
	const float terrain_getLightness(const string& ID) const;
	const float terrain_getRedRepeat(const string& ID) const;
	const float terrain_getGreenRepeat(const string& ID) const;
	const float terrain_getBlueRepeat(const string& ID) const;
	const float terrain_getSize(const string& ID) const;
	const float terrain_getPixelHeight(const string& ID, float x, float z) const;
	const float terrain_getSpecularShininess(const string& ID) const;
	const float terrain_getSpecularIntensity(const string& ID) const;
	const bool terrain_isExisting(const string& ID) const;
	const bool terrain_isVisible(const string& ID) const;
	const bool terrain_isSpecular(const string& ID) const;
	const bool terrain_isWireframed(const string& ID) const;
	const bool terrain_isInside(const string& ID, float x, float z) const;
	const bool terrain_hasBlendMap(const string& ID) const;
	const bool terrain_hasDiffuseMap(const string& ID) const;
	const bool terrain_hasDiffuseMapR(const string& ID) const;
	const bool terrain_hasDiffuseMapG(const string& ID) const;
	const bool terrain_hasDiffuseMapB(const string& ID) const;
	const bool terrain_hasNormalMap(const string& ID) const;
	const bool terrain_hasNormalMapR(const string& ID) const;
	const bool terrain_hasNormalMapG(const string& ID) const;
	const bool terrain_hasNormalMapB(const string& ID) const;

	// WATER - setters
	void water_create(const string& ID);
	void water_deleteAll();
	void water_delete(const string& ID);
	void water_setVisible(const string& ID, bool isVisible);
	void water_select(const string& ID);
	void water_setSpeed(const string& ID, fvec2 speed);
	void water_setHeight(const string& ID, float height);
	void water_setSize(const string& ID, float size);
	void water_setSpecular(const string& ID, bool enabled);
	void water_setReflective(const string& ID, bool enabled);
	void water_setRefractive(const string& ID, bool enabled);
	void water_setWireframed(const string& ID, bool enabled);
	void water_setWireframeColor(const string& ID, fvec3 color);
	void water_setDudvMap(const string& ID, const string& texturePath);
	void water_setNormalMap(const string& ID, const string& texturePath);
	void water_setDisplacementMap(const string& ID, const string& texturePath);
	void water_setWaveHeight(const string& ID, float height);
	void water_setSpecularShininess(const string& ID, float shininess);
	void water_setSpecularIntensity(const string& ID, float intensity);
	void water_setTransparency(const string& ID, float transparency);
	void water_setColor(const string& ID, fvec3 color);
	void water_setTextureRepeat(const string& ID, float repeat);
	void water_setQuality(const string& ID, WaterQuality quality);

	// WATER - getters
	const vector<string> water_getAllIDs() const;
	const string& water_getDudvMapPath(const string& ID) const;
	const string& water_getNormalMapPath(const string& ID) const;
	const string& water_getDisplacementMapPath(const string& ID) const;
	const string water_getSelectedID() const;
	const fvec3 water_getWireframeColor(const string& ID) const;
	const fvec3 water_getColor(const string& ID) const;
	const fvec2 water_getSpeed(const string& ID) const;
	const float water_getHeight(const string& ID) const;
	const float water_getSize(const string& ID) const;
	const float water_getTextureRepeat(const string& ID) const;
	const float water_getWaveHeight(const string& ID) const;
	const float water_getSpecularShininess(const string& ID) const;
	const float water_getSpecularIntensity(const string& ID) const;
	const float water_getTransparency(const string& ID) const;
	const bool water_isExisting(const string& ID) const;
	const bool water_isVisible(const string& ID) const;
	const bool water_isSpecular(const string& ID) const;
	const bool water_isReflective(const string& ID) const;
	const bool water_isRefractive(const string& ID) const;
	const bool water_isWireframed(const string& ID) const;
	const bool water_hasDudvMap(const string& ID) const;
	const bool water_hasNormalMap(const string& ID) const;
	const bool water_hasDisplacementMap(const string& ID) const;
	const WaterQuality water_getQuality(const string& ID) const;

	// MODEL - setters
	void model_create(const string& ID, const string& meshPath);
	void model_deleteAll();
	void model_delete(const string& ID);
	void model_deleteGroup(const string& ID);
	void model_setVisible(const string& ID, bool isVisible);
	void model_setDiffuseMap(const string& ID, const string& partID, const string& texturePath);
	void model_setEmissionMap(const string& ID, const string& partID, const string& texturePath);
	void model_setSpecularMap(const string& ID, const string& partID, const string& texturePath);
	void model_setReflectionMap(const string& ID, const string& partID, const string& texturePath);
	void model_setNormalMap(const string& ID, const string& partID, const string& texturePath);
	void model_setLevelOfDetail(const string& ID, const string& levelOfDetailID);
	void model_setFaceCulled(const string& ID, bool enabled);
	void model_setReflectionType(const string& ID, const string& partID, ReflectionType type);
	void model_setSpecular(const string& ID, const string& partID, bool enabled);
	void model_setReflective(const string& ID, const string& partID, bool enabled);
	void model_setShadowed(const string& ID, bool enabled);
	void model_setReflected(const string& ID, bool enabled);
	void model_setDepthMapIncluded(const string& ID, bool enabled);
	void model_setStaticToCamera(const string& ID, bool enabled);
	void model_setWireframed(const string& ID, const string& partID, bool enabled);
	void model_setBasePosition(const string& ID, fvec3 position);
	void model_setBaseRotation(const string& ID, fvec3 rotation);
	void model_setBaseRotationOrigin(const string& ID, fvec3 rotationOrigin);
	void model_setBaseSize(const string& ID, fvec3 size);
	void model_setPartPosition(const string& ID, const string& partID, fvec3 position);
	void model_setPartRotation(const string& ID, const string& partID, fvec3 rotation);
	void model_setPartRotationOrigin(const string& ID, const string& partID, fvec3 rotationOrigin);
	void model_setPartSize(const string& ID, const string& partID, fvec3 size);
	void model_moveBase(const string& ID, fvec3 change);
	void model_rotateBase(const string& ID, fvec3 change);
	void model_scaleBase(const string& ID, fvec3 change);
	void model_movePart(const string& ID, const string& partID, fvec3 change);
	void model_rotatePart(const string& ID, const string& partID, fvec3 change);
	void model_scalePart(const string& ID, const string& partID, fvec3 change);
	void model_moveBaseTo(const string& ID, fvec3 target, float speed);
	void model_rotateBaseTo(const string& ID, fvec3 target, float speed);
	void model_scaleBaseTo(const string& ID, fvec3 target, float speed);
	void model_movePartTo(const string& ID, const string& partID, fvec3 target, float speed);
	void model_rotatePartTo(const string& ID, const string& partID, fvec3 target, float speed);
	void model_scalePartTo(const string& ID, const string& partID, fvec3 target, float speed);
	void model_setLevelOfDetailSize(const string& ID, fvec3 size);
	void model_setSpecularShininess(const string& ID, const string& partID, float intensity);
	void model_setSpecularIntensity(const string& ID, const string& partID, float intensity);
	void model_setReflectivity(const string& ID, const string& partID, float reflectivity);
	void model_setLightness(const string& ID, const string& partID, float lightness);
	void model_setEmissionIntensity(const string& ID, const string& partID, float intensity);
	void model_setTransparency(const string& ID, const string& partID, float transparency);
	void model_setColor(const string& ID, const string& partID, fvec3 color);
	void model_setWireframeColor(const string& ID, const string& partID, fvec3 color);
	void model_setMinHeight(const string& ID, float height);
	void model_setMaxHeight(const string& ID, float height);
	void model_setTextureRepeat(const string& ID, const string& partID, float repeat);
	void model_enableInstancing(const string& ID, vector<fvec3> offsets);
	void model_disableInstancing(const string& ID);
	void model_setBright(const string& ID, bool enabled);
	void model_setRotationOrder(const string& ID, DirectionOrder order);

	// MODEL - getters
	const vector<string> model_getPartIDs(const string& ID) const;
	const vector<string> model_getAllIDs() const;
	const vector<string> model_getGroupIDs(const string& ID) const;
	const string& model_getMeshPath(const string& ID) const;
	const string& model_getDiffuseMapPath(const string& ID, const string& partID) const;
	const string& model_getEmissionMapPath(const string& ID, const string& partID) const;
	const string& model_getSpecularMapPath(const string& ID, const string& partID) const;
	const string& model_getReflectionMapPath(const string& ID, const string& partID) const;
	const string& model_getNormalMapPath(const string& ID, const string& partID) const;
	const string& model_getLevelOfDetailID(const string& ID) const;
	const vector<fvec3>& model_getInstancedOffsets(const string& ID) const;
	const fvec3 model_getLevelOfDetailSize(const string& ID) const;
	const fvec3 model_getBasePosition(const string& ID) const;
	const fvec3 model_getBaseRotation(const string& ID) const;
	const fvec3 model_getBaseRotationOrigin(const string& ID) const;
	const fvec3 model_getBaseSize(const string& ID) const;
	const fvec3 model_getPartPosition(const string& ID, const string& partID) const;
	const fvec3 model_getPartRotation(const string& ID, const string& partID) const;
	const fvec3 model_getPartRotationOrigin(const string& ID, const string& partID) const;
	const fvec3 model_getPartSize(const string& ID, const string& partID) const;
	const fvec3 model_getColor(const string& ID, const string& partID) const;
	const fvec3 model_getWireframeColor(const string& ID, const string& partID) const;
	const float model_getReflectivity(const string& ID, const string& partID) const;
	const float model_getLightness(const string& ID, const string& partID) const;
	const float model_getSpecularShininess(const string& ID, const string& partID) const;
	const float model_getSpecularIntensity(const string& ID, const string& partID) const;
	const float model_getTransparency(const string& ID, const string& partID) const;
	const float model_getMinHeight(const string& ID) const;
	const float model_getMaxHeight(const string& ID) const;
	const float model_getTextureRepeat(const string& ID, const string& partID) const;
	const float model_getEmissionIntensity(const string& ID, const string& partID) const;
	const bool model_isExisting(const string& ID) const;
	const bool model_isVisible(const string& ID) const;
	const bool model_isInstanced(const string& ID) const;
	const bool model_isMultiParted(const string& ID) const;
	const bool model_isFaceCulled(const string& ID) const;
	const bool model_isSpecular(const string& ID, const string& partID) const;
	const bool model_isShadowed(const string& ID) const;
	const bool model_isReflected(const string& ID) const;
	const bool model_isStaticToCamera(const string& ID) const;
	const bool model_isWireframed(const string& ID, const string& partID) const;
	const bool model_isDepthMapIncluded(const string& ID) const;
	const bool model_hasPart(const string& ID, const string& partID) const;
	const bool model_isBright(const string& ID) const;
	const bool model_isReflective(const string& ID, const string& partID) const;
	const bool model_hasDiffuseMap(const string& ID, const string& partID) const;
	const bool model_hasEmissionMap(const string& ID, const string& partID) const;
	const bool model_hasSpecularMap(const string& ID, const string& partID) const;
	const bool model_hasReflectionMap(const string& ID, const string& partID) const;
	const bool model_hasNormalMap(const string& ID, const string& partID) const;
	const ReflectionType model_getReflectionType(const string& ID, const string& partID) const;
	const DirectionOrder model_getRotationOrder(const string& ID) const;

	// MODEL - setters
	void billboard_create(const string& ID);
	void billboard_deleteAll();
	void billboard_delete(const string& ID);
	void billboard_deleteGroup(const string& ID);
	void billboard_pauseSpriteAnimation(const string& ID);
	void billboard_resumeSpriteAnimation(const string& ID);
	void billboard_stopSpriteAnimation(const string& ID);
	void billboard_setDiffuseMap(const string& ID, const string& texturePath);
	void billboard_setEmissionMap(const string& ID, const string& texturePath);
	void billboard_setFont(const string& ID, const string& fontPath);
	void billboard_setTextContent(const string& ID, const string& textContent);
	void billboard_setPosition(const string& ID, fvec3 position);
	void billboard_setRotation(const string& ID, fvec3 rotation);
	void billboard_setSize(const string& ID, fvec2 size);
	void billboard_move(const string& ID, fvec3 change);
	void billboard_rotate(const string& ID, fvec3 change);
	void billboard_scale(const string& ID, fvec2 change);
	void billboard_moveTo(const string& ID, fvec3 target, float speed);
	void billboard_rotateTo(const string& ID, fvec3 target, float speed);
	void billboard_scaleTo(const string& ID, fvec2 target, float speed);
	void billboard_setColor(const string& ID, fvec3 color);
	void billboard_setWireframeColor(const string& ID, fvec3 color);
	void billboard_setMinHeight(const string& ID, float height);
	void billboard_setMaxHeight(const string& ID, float height);
	void billboard_setLightness(const string& ID, float lightness);
	void billboard_setTransparency(const string& ID, float transparency);
	void billboard_setTextureRepeat(const string& ID, float repeat);
	void billboard_setEmissionIntensity(const string& ID, float intensity);
	void billboard_startSpriteAnimation(const string& ID, int loops);
	void billboard_setSpriteAnimationRowCount(const string& ID, unsigned int count);
	void billboard_setSpriteAnimationColumnCount(const string& ID, unsigned int count);
	void billboard_setSpriteAnimationRowIndex(const string& ID, unsigned int index);
	void billboard_setSpriteAnimationColumnIndex(const string& ID, unsigned int index);
	void billboard_setSpriteAnimationFramestep(const string& ID, unsigned int framestep);
	void billboard_setVisible(const string& ID, bool isVisible);
	void billboard_setCameraFacingX(const string& ID, bool enabled);
	void billboard_setCameraFacingY(const string& ID, bool enabled);
	void billboard_setDepthMapIncluded(const string& ID, bool enabled);
	void billboard_setShadowed(const string& ID, bool enabled);
	void billboard_setReflected(const string& ID, bool enabled);
	void billboard_setBright(const string& ID, bool enabled);
	void billboard_setWireframed(const string& ID, bool enabled);

	// MODEL - getters
	const vector<string> billboard_getAllIDs() const;
	const string& billboard_getDiffuseMapPath(const string& ID) const;
	const string& billboard_getEmissionMapPath(const string& ID) const;
	const string& billboard_getFontPath(const string& ID) const;
	const string& billboard_getTextContent(const string& ID) const;
	const fvec3 billboard_getPosition(const string& ID) const;
	const fvec3 billboard_getRotation(const string& ID) const;
	const fvec2 billboard_getSize(const string& ID) const;
	const fvec3 billboard_getColor(const string& ID) const;
	const fvec3 billboard_getWireframeColor(const string& ID) const;
	const float billboard_getLightness(const string& ID) const;
	const float billboard_getMinHeight(const string& ID) const;
	const float billboard_getMaxHeight(const string& ID) const;
	const float billboard_getTransparency(const string& ID) const;
	const float billboard_getTextureRepeat(const string& ID) const;
	const float billboard_getEmissionIntensity(const string& ID) const;
	const int billboard_getRemainingSpriteAnimationLoops(const string& ID) const;
	const unsigned int billboard_getSpriteAnimationRowCount(const string& ID) const;
	const unsigned int billboard_getSpriteAnimationColumnCount(const string& ID) const;
	const unsigned int billboard_getSpriteAnimationRowIndex(const string& ID) const;
	const unsigned int billboard_getSpriteAnimationColumnIndex(const string& ID) const;
	const unsigned int billboard_getSpriteAnimationFramestep(const string& ID) const;
	const bool billboard_isExisting(const string& ID) const;
	const bool billboard_isVisible(const string& ID) const;
	const bool billboard_isFacingCameraX(const string& ID) const;
	const bool billboard_isFacingCameraY(const string& ID) const;
	const bool billboard_isDepthMapIncluded(const string& ID) const;
	const bool billboard_isShadowed(const string& ID) const;
	const bool billboard_isReflected(const string& ID) const;
	const bool billboard_isBright(const string& ID) const;
	const bool billboard_isWireframed(const string& ID) const;
	const bool billboard_isSpriteAnimationStarted(const string& ID) const;
	const bool billboard_isSpriteAnimationPlaying(const string& ID) const;
	const bool billboard_isSpriteAnimationPaused(const string& ID) const;
	const bool billboard_hasDiffuseMap(const string& ID) const;
	const bool billboard_hasEmissionMap(const string& ID) const;
	const bool billboard_isTextual(const string& ID) const;

	// AABB - setters
	void aabb_create(const string& ID);
	void aabb_setParent(const string& ID, const string& parentID, AabbParentType parentType);
	void aabb_deleteAll();
	void aabb_delete(const string& ID);
	void aabb_setVisible(const string& ID, bool isVisible);
	void aabb_setRaycastResponsive(const string& ID, bool responsive);
	void aabb_setCollisionResponsive(const string& ID, bool responsive);
	void aabb_setFollowParentTransformation(const string& ID, bool mustFollow);
	void aabb_setFollowParentVisibility(const string& ID, bool mustFollow);
	void aabb_setLocalPosition(const string& ID, fvec3 position);
	void aabb_setLocalSize(const string& ID, fvec3 size);
	void aabb_setBasePosition(const string& ID, fvec3 position);
	void aabb_setBaseSize(const string& ID, fvec3 size);
	void aabb_move(const string& ID, fvec3 change);
	void aabb_scale(const string& ID, fvec3 change);
	void aabb_moveTo(const string& ID, fvec3 target, float speed);
	void aabb_scaleTo(const string& ID, fvec3 target, float speed);

	// AABB - getters
	const vector<string> aabb_getChildIDs(const string& parentID, AabbParentType parentType) const;
	const vector<string> aabb_getAllIDs() const;
	const string& aabb_getParentID(const string& ID) const;
	const fvec3 aabb_getPosition(const string& ID) const;
	const fvec3 aabb_getSize(const string& ID) const;
	const bool aabb_isRaycastResponsive(const string& ID) const;
	const bool aabb_isCollisionResponsive(const string& ID) const;
	const bool aabb_isExisting(const string& ID) const;
	const bool aabb_isVisible(const string& ID) const;
	const bool aabb_hasParent(const string& ID) const;
	const AabbParentType aabb_getParentType(const string& ID) const;

	// POINTLIGHT - setters
	void pointlight_create(const string& ID);
	void pointlight_deleteAll();
	void pointlight_delete(const string& ID);
	void pointlight_setVisible(const string& ID, bool isVisible);
	void pointlight_setPosition(const string& ID, fvec3 position);
	void pointlight_move(const string& ID, fvec3 change);
	void pointlight_moveTo(const string& ID, fvec3 target, float speed);
	void pointlight_setRadius(const string& ID, fvec3 radius);
	void pointlight_setColor(const string& ID, fvec3 color);
	void pointlight_setIntensity(const string& ID, float intensity);
	void pointlight_setShape(const string& ID, PointlightShape shape);

	// POINTLIGHT - getters
	const vector<string> pointlight_getAllIDs() const;
	const fvec3 pointlight_getPosition(const string& ID) const;
	const fvec3 pointlight_getRadius(const string& ID) const;
	const fvec3 pointlight_getColor(const string& ID) const;
	const float pointlight_getIntensity(const string& ID) const;
	const bool pointlight_isExisting(const string& ID) const;
	const bool pointlight_isVisible(const string& ID) const;
	const PointlightShape pointlight_getShape(const string& ID) const;

	// SPOTLIGHT - setters
	void spotlight_create(const string& ID);
	void spotlight_deleteAll();
	void spotlight_delete(const string& ID);
	void spotlight_setVisible(const string& ID, bool isVisible);
	void spotlight_setPosition(const string& ID, fvec3 position);
	void spotlight_move(const string& ID, fvec3 change);
	void spotlight_moveTo(const string& ID, fvec3 target, float speed);
	void spotlight_setColor(const string& ID, fvec3 color);
	void spotlight_setYaw(const string& ID, float yaw);
	void spotlight_setPitch(const string& ID, float pitch);
	void spotlight_setIntensity(const string& ID, float intensity);
	void spotlight_setAngle(const string& ID, float angle);
	void spotlight_setDistance(const string& ID, float distance);

	// SPOTLIGHT - getters
	const vector<string> spotlight_getAllIDs() const;
	const fvec3 spotlight_getPosition(const string& ID) const;
	const fvec3 spotlight_getColor(const string& ID) const;
	const float spotlight_getYaw(const string& ID) const;
	const float spotlight_getPitch(const string& ID) const;
	const float spotlight_getIntensity(const string& ID) const;
	const float spotlight_getAngle(const string& ID) const;
	const float spotlight_getDistance(const string& ID) const;
	const bool spotlight_isExisting(const string& ID) const;
	const bool spotlight_isVisible(const string& ID) const;

	// REFLECTION - setters
	void reflection_create(const string& ID);
	void reflection_deleteAll();
	void reflection_delete(const string& ID);
	void reflection_setVisible(const string& ID, bool isVisible);
	void reflection_setPosition(const string& ID, fvec3 position);
	void reflection_move(const string& ID, fvec3 change);
	void reflection_moveTo(const string& ID, fvec3 target, float speed);
	void reflection_capture(const string& ID);

	// REFLECTION - getters
	const vector<string> reflection_getAllIDs() const;
	const fvec3 reflection_getPosition(const string& ID) const;
	const bool reflection_isExisting(const string& ID) const;
	const bool reflection_isVisible(const string& ID) const;

	// IMAGE - setters
	void image_create(const string& ID, bool isCentered);
	void image_deleteAll();
	void image_delete(const string& ID);
	void image_setVisible(const string& ID, bool isVisible);
	void image_setDiffuseMap(const string& ID, const string& texturePath);
	void image_setColor(const string& ID, fvec3 color);
	void image_setTransparency(const string& ID, float transparency);
	void image_setMinPosition(const string& ID, fvec2 minPos);
	void image_setMaxPosition(const string& ID, fvec2 maxPos);
	void image_setPosition(const string& ID, fvec2 position);
	void image_setRotation(const string& ID, float rotation);
	void image_setSize(const string& ID, fvec2 size);
	void image_move(const string& ID, fvec2 position);
	void image_rotate(const string& ID, float rotation);
	void image_scale(const string& ID, fvec2 size);
	void image_moveTo(const string& ID, fvec2 target, float speed);
	void image_rotateTo(const string& ID, float target, float speed);
	void image_scaleTo(const string& ID, fvec2 target, float speed);
	void image_setMirroredHorizontally(const string& ID, bool mirrored);
	void image_setMirroredVertically(const string& ID, bool mirrored);
	void image_startSpriteAnimation(const string& ID, int loops);
	void image_pauseSpriteAnimation(const string& ID);
	void image_resumeSpriteAnimation(const string& ID);
	void image_stopSpriteAnimation(const string& ID);
	void image_setSpriteAnimationRowCount(const string& ID, int count);
	void image_setSpriteAnimationColumnCount(const string& ID, int count);
	void image_setSpriteAnimationRowIndex(const string& ID, unsigned int index);
	void image_setSpriteAnimationColumnIndex(const string& ID, unsigned int index);
	void image_setSpriteAnimationFramestep(const string& ID, int framestep);
	void image_setWireframed(const string& ID, bool enabled);
	void image_setWireframeColor(const string& ID, fvec3 color);

	// IMAGE - getters
	const vector<string> image_getAllIDs() const;
	const string& image_getDiffuseMapPath(const string& ID) const;
	const fvec3 image_getWireframeColor(const string& ID) const;
	const fvec3 image_getColor(const string& ID) const;
	const fvec2 image_getPosition(const string& ID) const;
	const fvec2 image_getSize(const string& ID) const;
	const fvec2 image_getMinPosition(const string& ID) const;
	const fvec2 image_getMaxPosition(const string& ID) const;
	const float image_getRotation(const string& ID) const;
	const float image_getTransparency(const string& ID) const;
	const int image_getRemainingSpriteAnimationLoops(const string& ID) const;
	const unsigned int image_getSpriteAnimationRowCount(const string& ID) const;
	const unsigned int image_getSpriteAnimationColumnCount(const string& ID) const;
	const unsigned int image_getSpriteAnimationRowIndex(const string& ID) const;
	const unsigned int image_getSpriteAnimationColumnIndex(const string& ID) const;
	const unsigned int image_getSpriteAnimationFramestep(const string& ID) const;
	const bool image_isExisting(const string& ID) const;
	const bool image_isVisible(const string& ID) const;
	const bool image_isCentered(const string& ID) const;
	const bool image_isMirroredHorizontally(const string& ID) const;
	const bool image_isMirroredVertically(const string& ID) const;
	const bool image_isSpriteAnimationStarted(const string& ID) const;
	const bool image_isSpriteAnimationPlaying(const string& ID) const;
	const bool image_isSpriteAnimationPaused(const string& ID) const;
	const bool image_hasDiffuseMap(const string& ID) const;
	const bool image_isWireframed(const string& ID) const;

	// TEXT - setters
	void text_create(const string& ID, bool isCentered, bool isDynamic);
	void text_deleteAll();
	void text_delete(const string& ID);
	void text_setVisible(const string& ID, bool isVisible);
	void text_setFont(const string& ID, const string& fontPath);
	void text_setTextContent(const string& ID, const string& textContent, float charWidth = -1.0f, float charHeight = -1.0f);
	void text_setColor(const string& ID, fvec3 color);
	void text_setTransparency(const string& ID, float transparency);
	void text_setMinPosition(const string& ID, fvec2 minPos);
	void text_setMaxPosition(const string& ID, fvec2 maxPos);
	void text_setPosition(const string& ID, fvec2 position);
	void text_setRotation(const string& ID, float rotation);
	void text_setSize(const string& ID, fvec2 size);
	void text_move(const string& ID, fvec2 position);
	void text_rotate(const string& ID, float rotation);
	void text_scale(const string& ID, fvec2 size);
	void text_moveTo(const string& ID, fvec2 target, float speed);
	void text_rotateTo(const string& ID, float target, float speed);
	void text_scaleTo(const string& ID, fvec2 target, float speed);
	void text_setMirroredHorizontally(const string& ID, bool mirrored);
	void text_setMirroredVertically(const string& ID, bool mirrored);
	void text_setWireframed(const string& ID, bool enabled);
	void text_setWireframeColor(const string& ID, fvec3 color);

	// TEXT - getters
	const vector<string> text_getAllIDs() const;
	const string& text_getFontPath(const string& ID) const;
	const string& text_getTextContent(const string& ID) const;
	const fvec3 text_getColor(const string& ID) const;
	const fvec2 text_getPosition(const string& ID) const;
	const fvec2 text_getSize(const string& ID) const;
	const fvec2 text_getMinPosition(const string& ID) const;
	const fvec2 text_getMaxPosition(const string& ID) const;
	const float text_getRotation(const string& ID) const;
	const float text_getTransparency(const string& ID) const;
	const bool text_isExisting(const string& ID) const;
	const bool text_isVisible(const string& ID) const;
	const bool text_isCentered(const string& ID) const;
	const bool text_isDynamic(const string& ID) const;
	const bool text_isMirroredHorizontally(const string& ID) const;
	const bool text_isMirroredVertically(const string& ID) const;
	const bool text_isWireframed(const string& ID) const;

	// SOUND - setters
	void sound_create(const string& ID, const string& filePath);
	void sound_make3D(const string& ID, fvec3 position, float maxVolume, float maxDistance);
	void sound_delete(const string& ID);
	void sound_deleteAll();
	void sound_play(const string& ID, int loops, int fadeMS, bool mustForcePlay);
	void sound_pause(const string& ID);
	void sound_pauseAll();
	void sound_resume(const string& ID);
	void sound_resumeAll();
	void sound_stop(const string& ID, int fadeMS);
	void sound_stopAll();
	void sound_setPosition(const string& ID, fvec3 position);
	void sound_move(const string& ID, fvec3 change);
	void sound_setVolume(const string& ID, float volume);
	void sound_setMaxVolume(const string& ID, float volume);
	void sound_setMaxDistance(const string& ID, float maxDistance);

	// SOUND - getters
	const vector<string> sound_getAllIDs() const;
	const string& sound_getFilePath(const string& ID) const;
	const fvec3 sound_getPosition(const string& ID) const;
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

	// MUSIC - setters
	void music_addToPlaylist(const string& filePath);
	void music_clearPlaylist();
	void music_setVolume(float volume);
	void music_pause();
	void music_resume();

	// MUSIC - getters
	const float music_getVolume() const;
	const bool music_isStarted() const;
	const bool music_isPlaying() const;
	const bool music_isPaused() const;

	// INPUT - setters
	void input_setLocked(bool locked);

	// INPUT - getters
	const int input_getMouseWheelX() const;
	const int input_getMouseWheelY() const;
	const bool input_isLocked() const;
	const bool input_isKeyDown(InputType key) const;
	const bool input_isKeyPressed(InputType key) const;
	const bool input_isMouseDown(InputType button) const;
	const bool input_isMousePressed(InputType button) const;

	// CAMERA - setters
	void camera_reset();
	void camera_enableFirstPersonView(float initialYaw, float initialPitch);
	void camera_enableThirdPersonView(float initialYaw, float initialPitch);
	void camera_disableFirstPersonView();
	void camera_disableThirdPersonView();
	void camera_moveFollowX(float speed);
	void camera_moveFollowZY(float speed);
	void camera_moveFollowZ(float speed);
	void camera_move(fvec3 speed);
	void camera_setPosition(fvec3 position);
	void camera_setThirdPersonLookat(fvec3 position);
	void camera_setThirdPersonDistance(float distance);
	void camera_setFOV(float angle);
	void camera_setYaw(float angle);
	void camera_setPitch(float angle);
	void camera_setMinFirstPersonPitch(float angle);
	void camera_setMaxFirstPersonPitch(float angle);
	void camera_setMinThirdPersonPitch(float angle);
	void camera_setMaxThirdPersonPitch(float angle);
	void camera_setCursorSensitivity(float speed);

	// CAMERA - getters
	const fvec3 camera_getPosition() const;
	const fvec3 camera_getUpVector() const;
	const fvec3 camera_getFrontVector() const;
	const fvec3 camera_getRightVector() const;
	const fvec3 camera_getThirdPersonLookat() const;
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

	// COLLISION - setters
	void collision_setCameraBox(float left, float right, float bottom, float top, float back, float front);
	void collision_enableCameraResponse(bool x, bool y, bool z);
	void collision_enableTerrainResponse(float cameraHeight, float cameraSpeed);
	void collision_disableCameraResponse();
	void collision_disableTerrainResponse();

	// COLLISION - getters
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

	// RAYCAST - setters
	void raycast_enableTerrainPointing(float distance, float precision);
	void raycast_disableTerrainPointing();

	// RAYCAST - getters
	const pair<const string, float> raycast_checkCursorInAny();
	const pair<const string, float> raycast_checkCursorInEntities(const string& ID, bool canBeOccluded);
	const pair<bool, float> raycast_checkCursorInEntity(const string& ID, bool canBeOccluded);
	const fvec3 raycast_getPointOnTerrain() const;
	const bool raycast_isPointOnTerrainValid() const;
	const bool raycast_isTerrainPointingEnabled() const;
	const Ray raycast_getCursorRay() const;

	// GRAPHICS - setters
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
	void gfx_setAmbientLightingColor(fvec3 color);
	void gfx_setAmbientLightingIntensity(float intensity);
	void gfx_setDirectionalLightingPosition(fvec3 position);
	void gfx_setDirectionalLightingColor(fvec3 color);
	void gfx_setDirectionalLightingIntensity(float intensity);
	void gfx_setFogColor(fvec3 color);
	void gfx_setFogThickness(float thickness);
	void gfx_setFogMinDistance(float minDistance);
	void gfx_setFogMaxDistance(float maxDistance);
	void gfx_setShadowEyePosition(fvec3 position);
	void gfx_setShadowCenterPosition(fvec3 position);
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

	// GRAPHICS - getters
	const string& gfx_getLensFlareMapPath() const;
	const fvec3 gfx_getDirectionalLightingPosition() const;
	const fvec3 gfx_getAmbientLightingColor() const;
	const fvec3 gfx_getDirectionalLightingColor() const;
	const fvec3 gfx_getFogColor() const;
	const fvec3 gfx_getShadowEye() const;
	const fvec3 gfx_getShadowCenter() const;
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

	// SERVER - setters
	void server_start(unsigned int maxClientCount);
	void server_sendMessageTCP(const string& username, const string& content);
	void server_sendMessageUDP(const string& username, const string& content);
	void server_broadcastMessageTCP(const string& content, const string& exceptionUsername);
	void server_broadcastMessageUDP(const string& content, const string& exceptionUsername);
	void server_disconnectClient(const string& username);
	void server_disconnectClients();
	void server_stop();

	// SERVER - getters
	const vector<NetworkClientMessage> server_getPendingMessages() const;
	const vector<string> server_getClientIPs() const;
	const vector<string> server_getClientUsernames() const;
	const string server_getNewClientIP() const;
	const string server_getNewClientUsername() const;
	const string server_getOldClientIP() const;
	const string server_getOldClientUsername() const;
	const bool server_isRunning() const;
	const bool server_isClientConnected(const string& username) const;

	// CLIENT - setters
	void client_start(const string& username);
	void client_connect(const string& serverIP);
	void client_sendMessageTCP(const string& content);
	void client_sendMessageUDP(const string& content);
	void client_disconnect();
	void client_stop();

	// CLIENT - getters
	const vector<NetworkServerMessage> client_getPendingMessages() const;
	const string client_getUsername() const;
	const string client_getServerIP() const;
	const unsigned int client_getPingLatency() const;
	const bool client_isValidServerIP(const string& serverIP) const;
	const bool client_isRunning() const;
	const bool client_isConnecting() const;
	const bool client_isConnected() const;
	const bool client_isAccepted() const;

	// MISC - setters
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
	void misc_setCustomCursor(const string& imageID);
	void misc_centerCursor();
	void misc_setCursorPosition(ivec2 pos);
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

	// MISC - getters
	const vector<pair<string, int>> misc_getUpdateProfilingStatistics() const;
	const vector<pair<string, int>> misc_getRenderProfilingStatistics() const;
	const string misc_getCpuModel() const;
	const string misc_getGpuModel() const;
	const string misc_getOpenglVersion() const;
	const ivec2 misc_getCursorPosition() const;
	const ivec2 misc_getCursorPositionRelativeToViewport() const;
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
	// STRING
	string _hoveredAabbID = "";

	// FLOAT
	float _hoveredAabbDistance = -1.0f;

	// BOOL
	bool _isRaycastUpdated = false;

	// Miscellaneous
	CoreEngine* _core = nullptr;
};
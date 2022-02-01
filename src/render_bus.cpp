#include "render_bus.hpp"
#include "render_bus.hpp"
#include "render_bus.hpp"
#include "render_bus.hpp"
#include "render_bus.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void RenderBus::setPlanarReflectionMap(shared_ptr<TextureBuffer> value)
{
	_planarReflectionMap = value;
}

void RenderBus::setWaterReflectionMap(shared_ptr<TextureBuffer> value)
{
	_waterReflectionMap = value;
}

void RenderBus::setWaterRefractionMap(shared_ptr<TextureBuffer> value)
{
	_waterRefractionMap = value;
}

void RenderBus::setWaterEdgeMap(shared_ptr<TextureBuffer> value)
{
	_waterEdgeMap = value;
}

void RenderBus::setBloomMap(shared_ptr<TextureBuffer> value)
{
	_bloomMap = value;
}

void RenderBus::setPrimarySceneMap(shared_ptr<TextureBuffer> value)
{
	_primarySceneMap = value;
}

void RenderBus::setSecondarySceneMap(shared_ptr<TextureBuffer> value)
{
	_secondarySceneMap = value;
}

void RenderBus::setShadowMap(shared_ptr<TextureBuffer> value)
{
	_shadowMap = value;
}

void RenderBus::setMotionBlurMap(shared_ptr<TextureBuffer> value)
{
	_motionBlurMap = value;
}

void RenderBus::setLensFlareMap(shared_ptr<TextureBuffer> value)
{
	_lensFlareMap = value;
}

void RenderBus::setDepthMap(shared_ptr<TextureBuffer> value)
{
	_depthMap = value;
}

void RenderBus::setDofMap(shared_ptr<TextureBuffer> value)
{
	_dofMap = value;
}

void RenderBus::setFinalSceneMap(shared_ptr<TextureBuffer> value)
{
	_finalSceneMap = value;
}

void RenderBus::setCameraViewMatrix(const mat44& value)
{
	_cameraViewMatrix = value;
}

void RenderBus::setCameraProjectionMatrix(const mat44& value)
{
	_cameraProjectionMatrix = value;
}

void RenderBus::setCameraShadowMatrix(const mat44& value)
{
	_cameraShadowMatrix = value;
}

void RenderBus::setMinPosition(const fvec3& value)
{
	_minPosition = value;
}

void RenderBus::setMaxPosition(const fvec3& value)
{
	_maxPosition = value;
}

void RenderBus::setFlareSourceUv(const fvec2& value)
{
	_flareSourceUv = value;
}

void RenderBus::setCameraPosition(const fvec3& value)
{
	_cameraPosition = value;
}

void RenderBus::setCameraUpVector(const fvec3& value)
{
	_cameraUpVector = value;
}

void RenderBus::setCameraFrontVector(const fvec3& value)
{
	_cameraFrontVector = value;
}

void RenderBus::setCameraRightVector(const fvec3& value)
{
	_cameraRightVector = value;
}

void RenderBus::setAmbientLightingColor(const fvec3& value)
{
	_ambientLightColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setDirectionalLightingPosition(const fvec3& value)
{
	_directionalLightPosition = value;
}

void RenderBus::setDirectionalLightingColor(const fvec3& value)
{
	_directionalLightColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setShadowEyePosition(const fvec3& value)
{
	_shadowEyePosition = value;
}

void RenderBus::setShadowEyeOffset(const fvec3& value)
{
	_shadowEyeOffset = value;
}

void RenderBus::setShadowCenterPosition(const fvec3& value)
{
	_shadowCenterPosition = value;
}

void RenderBus::setShadowCenterOffset(const fvec3& value)
{
	_shadowCenterOffset = value;
}

void RenderBus::setFogColor(const fvec3& value)
{
	_fogColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setFlareSourcePosition(const fvec3& value)
{
	_flareSourcePosition = value;
}

void RenderBus::setPlanarReflectionHeight(float value)
{
	_planarReflectionHeight = value;
}

void RenderBus::setShadowSize(float value)
{
	_shadowSize = max(0.0f, value);
}

void RenderBus::setShadowLightness(float value)
{
	_shadowLightness = max(0.0f, value);
}

void RenderBus::setLensFlareOpacity(float value)
{
	_lensFlareOpacity = max(0.0f, value);
}

void RenderBus::setLensFlareIntensity(float value)
{
	_lensFlareIntensity = max(0.0f, value);
}

void RenderBus::setLensFlareSensitivity(float value)
{
	_lensFlareSensitivity = max(0.0f, value);
}

void RenderBus::setMotionBlurIntensity(float value)
{
	_motionBlurIntensity = max(0.0f, value);
}

void RenderBus::setMotionBlurMixValue(float value)
{
	_motionBlurMixValue = clamp(value, 0.0f, 1.0f);
}

void RenderBus::setMotionBlurDifference(fvec2 value)
{
	_motionBlurDifference = value;
}

void RenderBus::setBloomQuality(unsigned int value)
{
	_bloomQuality = clamp(value, Config::MIN_BLOOM_QUALITY, Config::MAX_BLOOM_QUALITY);
}

void RenderBus::setDofQuality(unsigned int value)
{
	_dofQuality = clamp(value, Config::MIN_DOF_QUALITY, Config::MAX_DOF_QUALITY);
}

void RenderBus::setMotionBlurQuality(unsigned int value)
{
	_motionBlurQuality = clamp(value, Config::MIN_MOTION_BLUR_QUALITY, Config::MAX_MOTION_BLUR_QUALITY);
}

void RenderBus::setAmbientLightingIntensity(float value)
{
	_ambientLightIntensity = max(0.0f, value);
}

void RenderBus::setDirectionalLightingIntensity(float value)
{
	_directionalLightIntensity = max(0.0f, value);
}

void RenderBus::setFogMinDistance(float value)
{
	_fogMinDistance = max(0.0f, value);
}

void RenderBus::setFogMaxDistance(float value)
{
	_fogMaxDistance = max(0.0f, value);
}

void RenderBus::setFogThickness(float value)
{
	_fogThickness = clamp(value, 0.0f, 1.0f);
}

void RenderBus::setBloomIntensity(float value)
{
	_bloomIntensity = max(0.0f, value);
}

void RenderBus::setCameraYaw(float value)
{
	_cameraYaw = value;
}

void RenderBus::setCameraPitch(float value)
{
	_cameraPitch = value;
}

void RenderBus::setCameraNearDistance(float value)
{
	_cameraNearDistance = max(0.0f, value);
}

void RenderBus::setCameraFarDistance(float value)
{
	_farDistance = value;
}

void RenderBus::setDofDynamicDistance(float value)
{
	_dofDynamicDistance = max(0.0f, value);
}

void RenderBus::setDofBlurDistance(float value)
{
	_dofBlurDistance = max(0.0f, value);
}

void RenderBus::setBloomBlurCount(unsigned int value)
{
	_bloomBlurCount = value;
}

void RenderBus::increaseTriangleCount(unsigned int value)
{
	if(_isTriangleCountingEnabled)
	{
		_triangleCount += value;
	}
}

void RenderBus::setShadowQuality(unsigned int value)
{
	_shadowQuality = clamp(value, Config::MIN_SHADOW_QUALITY, Config::MAX_SHADOW_QUALITY);
}

void RenderBus::setCubeReflectionQuality(unsigned int value)
{
	_cubeReflectionQuality = clamp(value, Config::MIN_REFLECTION_QUALITY, Config::MAX_REFLECTION_QUALITY);
}

void RenderBus::setPlanarReflectionQuality(unsigned int value)
{
	_planarReflectionQuality = clamp(value, Config::MIN_REFLECTION_QUALITY, Config::MAX_REFLECTION_QUALITY);
}

void RenderBus::setPlanarRefractionQuality(unsigned int value)
{
	_planarRefractionQuality = clamp(value, Config::MIN_REFRACTION_QUALITY, Config::MAX_REFRACTION_QUALITY);
}

void RenderBus::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderBus::setAntiAliasingEnabled(bool value)
{
	_isAntiAliasingEnabled = value;
}

void RenderBus::setAmbientLightingEnabled(bool value)
{
	_isAmbientLightingEnabled = value;
}

void RenderBus::setDirectionalLightingEnabled(bool value)
{
	_isDirectionalLightingEnabled = value;
}

void RenderBus::setReflectionsEnabled(bool value)
{
	_isReflectionsEnabled = value;
}

void RenderBus::setRefractionsEnabled(bool value)
{
	_isRefractionsEnabled = value;
}

void RenderBus::setFogEnabled(bool value)
{
	_isFogEnabled = value;
}

void RenderBus::setBloomEnabled(bool value)
{
	_isBloomEnabled = value;
}

void RenderBus::setShadowsEnabled(bool value)
{
	_isShadowsEnabled = value;
}

void RenderBus::setDofEnabled(bool value)
{
	_isDofEnabled = value;
}

void RenderBus::setMotionBlurEnabled(bool value)
{
	_isMotionBlurEnabled = value;
}

void RenderBus::setLensFlareEnabled(bool value)
{
	_isLensFlareEnabled = value;
}

void RenderBus::setShadowCircleEnabled(bool value)
{
	_isShadowCircleEnabled = value;
}

void RenderBus::setTriangleCountingEnabled(bool value)
{
	_isTriangleCountingEnabled = value;
}

void RenderBus::setDofDynamic(bool value)
{
	_isDofDynamic = value;
}

void RenderBus::setBloomType(BloomType value)
{
	_bloomType = value;
}

void RenderBus::setGuiDepth(unsigned int value)
{
	_guiDepth = value;
}

void RenderBus::setAnisotropicFilteringQuality(unsigned int value)
{
	_anisotropicFilteringQuality = clamp(value, Config::MIN_ANISOTROPIC_FILTERING_QUALITY, Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
}

void RenderBus::setCursorEntityId(const string& value)
{
	_cursorEntityId = value;
}

void RenderBus::setLensFlareMapPath(const string& value)
{
	_lensFlareMapPath = value;
}

void RenderBus::setSkyExposureIntensity(float value)
{
	_skyExposureIntensity = value;
}

void RenderBus::setSkyExposureSpeed(float value)
{
	_skyExposureSpeed = value;
}

void RenderBus::setSkyExposureLightness(float value)
{
	_skyExposureLightness = value;
}

void RenderBus::setSkyExposureEnabled(bool value)
{
	_isSkyExposureEnabled = value;
}

void RenderBus::setShadowInterval(unsigned int value)
{
	_shadowInterval = value;
}

void RenderBus::setShadowsFollowingCamera(bool value)
{
	_isShadowsFollowingCamera = value;
}

const shared_ptr<TextureBuffer> RenderBus::getPlanarReflectionMap() const
{
	return _planarReflectionMap;
}

const shared_ptr<TextureBuffer> RenderBus::getWaterReflectionMap() const
{
	return _waterReflectionMap;
}

const shared_ptr<TextureBuffer> RenderBus::getWaterRefractionMap() const
{
	return _waterRefractionMap;
}

const shared_ptr<TextureBuffer> RenderBus::getWaterEdgeMap() const
{
	return _waterEdgeMap;
}

const shared_ptr<TextureBuffer> RenderBus::getBloomMap() const
{
	return _bloomMap;
}

const shared_ptr<TextureBuffer> RenderBus::getPrimarySceneMap() const
{
	return _primarySceneMap;
}

const shared_ptr<TextureBuffer> RenderBus::getSecondarySceneMap() const
{
	return _secondarySceneMap;
}

const shared_ptr<TextureBuffer> RenderBus::getShadowMap() const
{
	return _shadowMap;
}

const shared_ptr<TextureBuffer> RenderBus::getMotionBlurMap() const
{
	return _motionBlurMap;
}

const shared_ptr<TextureBuffer> RenderBus::getLensFlareMap() const
{
	return _lensFlareMap;
}

const shared_ptr<TextureBuffer> RenderBus::getDepthMap() const
{
	return _depthMap;
}

const shared_ptr<TextureBuffer> RenderBus::getDofMap() const
{
	return _dofMap;
}

const shared_ptr<TextureBuffer> RenderBus::getFinalSceneMap() const
{
	return _finalSceneMap;
}

const mat44& RenderBus::getCameraViewMatrix() const
{
	return _cameraViewMatrix;
}

const mat44& RenderBus::getCameraProjectionMatrix() const
{
	return _cameraProjectionMatrix;
}

const mat44& RenderBus::getCameraShadowMatrix() const
{
	return _cameraShadowMatrix;
}

const fvec3& RenderBus::getMinPosition() const
{
	return _minPosition;
}

const fvec3& RenderBus::getMaxPosition() const
{
	return _maxPosition;
}

const fvec2& RenderBus::getFlareSourceUv() const
{
	return _flareSourceUv;
}

const fvec3& RenderBus::getCameraPosition() const
{
	return _cameraPosition;
}

const fvec3& RenderBus::getCameraUpVector() const
{
	return _cameraUpVector;
}

const fvec3& RenderBus::getCameraFrontVector() const
{
	return _cameraFrontVector;
}

const fvec3& RenderBus::getCameraRightVector() const
{
	return _cameraRightVector;
}

const fvec3& RenderBus::getAmbientLightingColor() const
{
	return _ambientLightColor;
}

const fvec3& RenderBus::getDirectionalLightingPosition() const
{
	return _directionalLightPosition;
}

const fvec3& RenderBus::getShadowEyePosition() const
{
	return _shadowEyePosition;
}

const fvec3& RenderBus::getShadowEyeOffset() const
{
	return _shadowEyeOffset;
}

const fvec3& RenderBus::getShadowCenterPosition() const
{
	return _shadowCenterPosition;
}

const fvec3& RenderBus::getShadowCenterOffset() const
{
	return _shadowCenterOffset;
}

const fvec3& RenderBus::getFogColor() const
{
	return _fogColor;
}

const fvec3& RenderBus::getFlareSourcePosition() const
{
	return _flareSourcePosition;
}

const fvec3& RenderBus::getDirectionalLightingColor() const
{
	return _directionalLightColor;
}

const float RenderBus::getPlanarReflectionHeight() const
{
	return _planarReflectionHeight;
}

const float RenderBus::getShadowSize() const
{
	return _shadowSize;
}

const float RenderBus::getShadowLightness() const
{
	return _shadowLightness;
}

const float RenderBus::getLensFlareOpacity() const
{
	return _lensFlareOpacity;
}

const float RenderBus::getLensFlareIntensity() const
{
	return _lensFlareIntensity;
}

const float RenderBus::getLensFlareSensitivity() const
{
	return _lensFlareSensitivity;
}

const float RenderBus::getMotionBlurIntensity() const
{
	return _motionBlurIntensity;
}

const float RenderBus::getMotionBlurMixValue() const
{
	return _motionBlurMixValue;
}

const unsigned int RenderBus::getBloomQuality() const
{
	return _bloomQuality;
}

const unsigned int RenderBus::getDofQuality() const
{
	return _dofQuality;
}

const unsigned int RenderBus::getMotionBlurQuality() const
{
	return _motionBlurQuality;
}

const float RenderBus::getAmbientLightingIntensity() const
{
	return _ambientLightIntensity;
}

const float RenderBus::getDirectionalLightingIntensity() const
{
	return _directionalLightIntensity;
}

const float RenderBus::getFogMinDistance() const
{
	return _fogMinDistance;
}

const float RenderBus::getFogMaxDistance() const
{
	return _fogMaxDistance;
}

const float RenderBus::getFogThickness() const
{
	return _fogThickness;
}

const float RenderBus::getBloomIntensity() const
{
	return _bloomIntensity;
}

const float RenderBus::getCameraYaw() const
{
	return _cameraYaw;
}

const float RenderBus::getCameraPitch() const
{
	return _cameraPitch;
}

const float RenderBus::getCameraNearDistance() const
{
	return _cameraNearDistance;
}

const float RenderBus::getFarDistance() const
{
	return _farDistance;
}

const float RenderBus::getDofDynamicDistance() const
{
	return _dofDynamicDistance;
}

const float RenderBus::getDofBlurDistance() const
{
	return _dofBlurDistance;
}

const unsigned int RenderBus::getBloomBlurCount() const
{
	return _bloomBlurCount;
}

const unsigned int RenderBus::getTriangleCount() const
{
	return _triangleCount;
}

const unsigned int RenderBus::getGuiDepth() const
{
	return _guiDepth;
}

const unsigned int RenderBus::getAnisotropicFilteringQuality() const
{
	return _anisotropicFilteringQuality;
}

const unsigned int RenderBus::getShadowInterval() const
{
	return _shadowInterval;
}

const unsigned int RenderBus::getShadowQuality() const
{
	return _shadowQuality;
}

const unsigned int RenderBus::getCubeReflectionQuality() const
{
	return _cubeReflectionQuality;
}

const unsigned int RenderBus::getPlanarReflectionQuality() const
{
	return _planarReflectionQuality;
}

const unsigned int RenderBus::getPlanarRefractionQuality() const
{
	return _planarRefractionQuality;
}

const bool RenderBus::isAntiAliasingEnabled() const
{
	return _isAntiAliasingEnabled;
}

const bool RenderBus::isAmbientLightingEnabled() const
{
	return _isAmbientLightingEnabled;
}

const bool RenderBus::isDirectionalLightingEnabled() const
{
	return _isDirectionalLightingEnabled;
}

const bool RenderBus::isReflectionsEnabled() const
{
	return _isReflectionsEnabled;
}

const bool RenderBus::isRefractionsEnabled() const
{
	return _isRefractionsEnabled;
}

const bool RenderBus::isFogEnabled() const
{
	return _isFogEnabled;
}

const bool RenderBus::isBloomEnabled() const
{
	return _isBloomEnabled;
}

const bool RenderBus::isShadowsEnabled() const
{
	return _isShadowsEnabled;
}

const bool RenderBus::isDofEnabled() const
{
	return _isDofEnabled;
}

const bool RenderBus::isMotionBlurEnabled() const
{
	return _isMotionBlurEnabled;
}

const bool RenderBus::isLensFlareEnabled() const
{
	return _isLensFlareEnabled;
}

const bool RenderBus::isShadowCircleEnabled() const
{
	return _isShadowCircleEnabled;
}

const bool RenderBus::isTriangleCountingEnabled() const
{
	return _isTriangleCountingEnabled;
}

const bool RenderBus::isDofDynamic() const
{
	return _isDofDynamic;
}

const BloomType RenderBus::getBloomType() const
{
	return _bloomType;
}

const string& RenderBus::getCursorEntityId() const
{
	return _cursorEntityId;
}

const string& RenderBus::getLensFlareMapPath() const
{
	return _lensFlareMapPath;
}

const float RenderBus::getSkyExposureIntensity() const
{
	return _skyExposureIntensity;
}

const float RenderBus::getSkyExposureSpeed() const
{
	return _skyExposureSpeed;
}

const float RenderBus::getSkyExposureLightness() const
{
	return _skyExposureLightness;
}

const fvec2 RenderBus::getMotionBlurDifference() const
{
	return _motionBlurDifference;
}

const bool RenderBus::isSkyExposureEnabled() const
{
	return _isSkyExposureEnabled;
}

const bool RenderBus::isShadowsFollowingCamera() const
{
	return _isShadowsFollowingCamera;
}
#include "render_storage.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void RenderStorage::setPlanarReflectionMap(shared_ptr<TextureBuffer> value)
{
	_planarReflectionMap = value;
}

void RenderStorage::setWaterReflectionMap(shared_ptr<TextureBuffer> value)
{
	_waterReflectionMap = value;
}

void RenderStorage::setWaterRefractionMap(shared_ptr<TextureBuffer> value)
{
	_waterRefractionMap = value;
}

void RenderStorage::setWaterEdgeMap(shared_ptr<TextureBuffer> value)
{
	_waterEdgeMap = value;
}

void RenderStorage::setBloomMap(shared_ptr<TextureBuffer> value)
{
	_bloomMap = value;
}

void RenderStorage::setPrimarySceneMap(shared_ptr<TextureBuffer> value)
{
	_primarySceneMap = value;
}

void RenderStorage::setSecondarySceneMap(shared_ptr<TextureBuffer> value)
{
	_secondarySceneMap = value;
}

void RenderStorage::setShadowMap(shared_ptr<TextureBuffer> value)
{
	_shadowMap = value;
}

void RenderStorage::setMotionBlurMap(shared_ptr<TextureBuffer> value)
{
	_motionBlurMap = value;
}

void RenderStorage::setLensFlareMap(shared_ptr<TextureBuffer> value)
{
	_lensFlareMap = value;
}

void RenderStorage::setDepthMap(shared_ptr<TextureBuffer> value)
{
	_depthMap = value;
}

void RenderStorage::setDofMap(shared_ptr<TextureBuffer> value)
{
	_dofMap = value;
}

void RenderStorage::setFinalSceneMap(shared_ptr<TextureBuffer> value)
{
	_finalSceneMap = value;
}

void RenderStorage::setShadowView(const mat44& value)
{
	_shadowView = value;
}

void RenderStorage::setShadowProjection(const mat44& value)
{
	_shadowProjection = value;
}

void RenderStorage::setMinPosition(const fvec3& value)
{
	_minPosition = value;
}

void RenderStorage::setMaxPosition(const fvec3& value)
{
	_maxPosition = value;
}

void RenderStorage::setFlareSourceUv(const fvec2& value)
{
	_flareSourceUv = fvec2(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f));
}

void RenderStorage::setAmbientLightingColor(const fvec3& value)
{
	_ambientLightingColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderStorage::setDirectionalLightingPosition(const fvec3& value)
{
	_directionalLightingPosition = value;
}

void RenderStorage::setDirectionalLightingColor(const fvec3& value)
{
	_directionalLightingColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderStorage::setShadowPosition(const fvec3& value)
{
	_shadowPosition = value;
}

void RenderStorage::setShadowPositionOffset(const fvec3& value)
{
	_shadowPositionOffset = value;
}

void RenderStorage::setShadowLookat(const fvec3& value)
{
	_shadowLookat = value;
}

void RenderStorage::setShadowLookatOffset(const fvec3& value)
{
	_shadowLookatOffset = value;
}

void RenderStorage::setFogColor(const fvec3& value)
{
	_fogColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderStorage::setFlareSourcePosition(const fvec3& value)
{
	_flareSourcePosition = value;
}

void RenderStorage::setPlanarReflectionHeight(float value)
{
	_planarReflectionHeight = value;
}

void RenderStorage::setShadowSize(float value)
{
	_shadowSize = max(0.0f, value);
}

void RenderStorage::setShadowLightness(float value)
{
	_shadowLightness = max(0.0f, value);
}

void RenderStorage::setLensFlareOpacity(float value)
{
	_lensFlareOpacity = max(0.0f, value);
}

void RenderStorage::setLensFlareIntensity(float value)
{
	_lensFlareIntensity = max(0.0f, value);
}

void RenderStorage::setLensFlareSensitivity(float value)
{
	_lensFlareSensitivity = max(0.0f, value);
}

void RenderStorage::setMotionBlurIntensity(float value)
{
	_motionBlurIntensity = max(0.0f, value);
}

void RenderStorage::setMotionBlurMixValue(float value)
{
	_motionBlurMixValue = clamp(value, 0.0f, 1.0f);
}

void RenderStorage::setMotionBlurDifference(fvec2 value)
{
	_motionBlurDifference = value;
}

void RenderStorage::setBloomQuality(unsigned int value)
{
	_bloomQuality = clamp(value, MIN_BLOOM_QUALITY, MAX_BLOOM_QUALITY);
}

void RenderStorage::setDofQuality(unsigned int value)
{
	_dofQuality = clamp(value, MIN_DOF_QUALITY, MAX_DOF_QUALITY);
}

void RenderStorage::setMotionBlurQuality(unsigned int value)
{
	_motionBlurQuality = clamp(value, MIN_MOTION_BLUR_QUALITY, MAX_MOTION_BLUR_QUALITY);
}

void RenderStorage::setAmbientLightingIntensity(float value)
{
	_ambientLightingIntensity = max(0.0f, value);
}

void RenderStorage::setDirectionalLightingIntensity(float value)
{
	_directionalLightingIntensity = max(0.0f, value);
}

void RenderStorage::setMinFogDistance(float value)
{
	_minFogDistance = max(0.0f, value);
}

void RenderStorage::setMaxFogDistance(float value)
{
	_maxFogDistance = max(0.0f, value);
}

void RenderStorage::setFogThickness(float value)
{
	_fogThickness = clamp(value, 0.0f, 1.0f);
}

void RenderStorage::setBloomIntensity(float value)
{
	_bloomIntensity = max(0.0f, value);
}

void RenderStorage::setDofDynamicDistance(float value)
{
	_dofDynamicDistance = max(0.0f, value);
}

void RenderStorage::setDofBlurDistance(float value)
{
	_dofBlurDistance = max(0.0f, value);
}

void RenderStorage::setBloomBlurCount(unsigned int value)
{
	_bloomBlurCount = value;
}

void RenderStorage::increaseTriangleCount(unsigned int value)
{
	if(_isTriangleCountingEnabled)
	{
		_triangleCount += value;
	}
}

void RenderStorage::setShadowQuality(unsigned int value)
{
	_shadowQuality = clamp(value, MIN_SHADOW_QUALITY, MAX_SHADOW_QUALITY);
}

void RenderStorage::setCubeReflectionQuality(unsigned int value)
{
	_cubeReflectionQuality = clamp(value, MIN_REFLECTION_QUALITY, MAX_REFLECTION_QUALITY);
}

void RenderStorage::setPlanarReflectionQuality(unsigned int value)
{
	_planarReflectionQuality = clamp(value, MIN_REFLECTION_QUALITY, MAX_REFLECTION_QUALITY);
}

void RenderStorage::setPlanarRefractionQuality(unsigned int value)
{
	_planarRefractionQuality = clamp(value, MIN_REFRACTION_QUALITY, MAX_REFRACTION_QUALITY);
}

void RenderStorage::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderStorage::setAntiAliasingEnabled(bool value)
{
	_isAntiAliasingEnabled = value;
}

void RenderStorage::setAmbientLightingEnabled(bool value)
{
	_isAmbientLightingEnabled = value;
}

void RenderStorage::setDirectionalLightingEnabled(bool value)
{
	_isDirectionalLightingEnabled = value;
}

void RenderStorage::setReflectionsEnabled(bool value)
{
	_isReflectionsEnabled = value;
}

void RenderStorage::setRefractionsEnabled(bool value)
{
	_isRefractionsEnabled = value;
}

void RenderStorage::setFogEnabled(bool value)
{
	_isFogEnabled = value;
}

void RenderStorage::setBloomEnabled(bool value)
{
	_isBloomEnabled = value;
}

void RenderStorage::setShadowsEnabled(bool value)
{
	_isShadowsEnabled = value;
}

void RenderStorage::setDofEnabled(bool value)
{
	_isDofEnabled = value;
}

void RenderStorage::setMotionBlurEnabled(bool value)
{
	_isMotionBlurEnabled = value;
}

void RenderStorage::setLensFlareEnabled(bool value)
{
	_isLensFlareEnabled = value;
}

void RenderStorage::setShadowCircleEnabled(bool value)
{
	_isShadowCircleEnabled = value;
}

void RenderStorage::setTriangleCountingEnabled(bool value)
{
	_isTriangleCountingEnabled = value;
}

void RenderStorage::setDofDynamic(bool value)
{
	_isDofDynamic = value;
}

void RenderStorage::setBloomType(BloomType value)
{
	_bloomType = value;
}

void RenderStorage::setGuiDepth(unsigned int value)
{
	_guiDepth = value;
}

void RenderStorage::setAnisotropicFilteringQuality(unsigned int value)
{
	_anisotropicFilteringQuality = clamp(value, MIN_ANISOTROPIC_FILTERING_QUALITY, MAX_ANISOTROPIC_FILTERING_QUALITY);
}

void RenderStorage::setCursorEntityId(const string& value)
{
	_cursorEntityId = value;
}

void RenderStorage::setLensFlareMapPath(const string& value)
{
	_lensFlareMapPath = value;
}

void RenderStorage::setSkyExposureIntensity(float value)
{
	_skyExposureIntensity = max(0.0f, value);
}

void RenderStorage::setSkyExposureSpeed(float value)
{
	_skyExposureSpeed = value;
}

void RenderStorage::setSkyExposureLightness(float value)
{
	_skyExposureLightness = max(0.0f, value);
}

void RenderStorage::setSkyExposureEnabled(bool value)
{
	_isSkyExposureEnabled = value;
}

void RenderStorage::setShadowInterval(unsigned int value)
{
	_shadowInterval = value;
}

void RenderStorage::setShadowsFollowingCamera(bool value)
{
	_isShadowsFollowingCamera = value;
}

void RenderStorage::setCubeReflectionInterval(unsigned int value)
{
	_cubeReflectionInterval = value;
}

const shared_ptr<TextureBuffer> RenderStorage::getPlanarReflectionMap() const
{
	return _planarReflectionMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getWaterReflectionMap() const
{
	return _waterReflectionMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getWaterRefractionMap() const
{
	return _waterRefractionMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getWaterEdgeMap() const
{
	return _waterEdgeMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getBloomMap() const
{
	return _bloomMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getPrimarySceneMap() const
{
	return _primarySceneMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getSecondarySceneMap() const
{
	return _secondarySceneMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getShadowMap() const
{
	return _shadowMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getMotionBlurMap() const
{
	return _motionBlurMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getLensFlareMap() const
{
	return _lensFlareMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getDepthMap() const
{
	return _depthMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getDofMap() const
{
	return _dofMap;
}

const shared_ptr<TextureBuffer> RenderStorage::getFinalSceneMap() const
{
	return _finalSceneMap;
}

const mat44& RenderStorage::getShadowView() const
{
	return _shadowView;
}

const mat44& RenderStorage::getShadowProjection() const
{
	return _shadowProjection;
}

const fvec3& RenderStorage::getMinPosition() const
{
	return _minPosition;
}

const fvec3& RenderStorage::getMaxPosition() const
{
	return _maxPosition;
}

const fvec2& RenderStorage::getFlareSourceUv() const
{
	return _flareSourceUv;
}

const fvec3& RenderStorage::getAmbientLightingColor() const
{
	return _ambientLightingColor;
}

const fvec3& RenderStorage::getDirectionalLightingPosition() const
{
	return _directionalLightingPosition;
}

const fvec3& RenderStorage::getShadowPosition() const
{
	return _shadowPosition;
}

const fvec3& RenderStorage::getShadowPositionOffset() const
{
	return _shadowPositionOffset;
}

const fvec3& RenderStorage::getShadowLookat() const
{
	return _shadowLookat;
}

const fvec3& RenderStorage::getShadowLookatOffset() const
{
	return _shadowLookatOffset;
}

const fvec3& RenderStorage::getFogColor() const
{
	return _fogColor;
}

const fvec3& RenderStorage::getFlareSourcePosition() const
{
	return _flareSourcePosition;
}

const fvec3& RenderStorage::getDirectionalLightingColor() const
{
	return _directionalLightingColor;
}

const float RenderStorage::getPlanarReflectionHeight() const
{
	return _planarReflectionHeight;
}

const float RenderStorage::getShadowSize() const
{
	return _shadowSize;
}

const float RenderStorage::getShadowLightness() const
{
	return _shadowLightness;
}

const float RenderStorage::getLensFlareOpacity() const
{
	return _lensFlareOpacity;
}

const float RenderStorage::getLensFlareIntensity() const
{
	return _lensFlareIntensity;
}

const float RenderStorage::getLensFlareSensitivity() const
{
	return _lensFlareSensitivity;
}

const float RenderStorage::getMotionBlurIntensity() const
{
	return _motionBlurIntensity;
}

const float RenderStorage::getMotionBlurMixValue() const
{
	return _motionBlurMixValue;
}

const unsigned int RenderStorage::getBloomQuality() const
{
	return _bloomQuality;
}

const unsigned int RenderStorage::getDofQuality() const
{
	return _dofQuality;
}

const unsigned int RenderStorage::getMotionBlurQuality() const
{
	return _motionBlurQuality;
}

const float RenderStorage::getAmbientLightingIntensity() const
{
	return _ambientLightingIntensity;
}

const float RenderStorage::getDirectionalLightingIntensity() const
{
	return _directionalLightingIntensity;
}

const float RenderStorage::getMinFogDistance() const
{
	return _minFogDistance;
}

const float RenderStorage::getMaxFogDistance() const
{
	return _maxFogDistance;
}

const float RenderStorage::getFogThickness() const
{
	return _fogThickness;
}

const float RenderStorage::getBloomIntensity() const
{
	return _bloomIntensity;
}

const float RenderStorage::getDofDynamicDistance() const
{
	return _dofDynamicDistance;
}

const float RenderStorage::getDofBlurDistance() const
{
	return _dofBlurDistance;
}

const unsigned int RenderStorage::getBloomBlurCount() const
{
	return _bloomBlurCount;
}

const unsigned int RenderStorage::getTriangleCount() const
{
	return _triangleCount;
}

const unsigned int RenderStorage::getGuiDepth() const
{
	return _guiDepth;
}

const unsigned int RenderStorage::getAnisotropicFilteringQuality() const
{
	return _anisotropicFilteringQuality;
}

const unsigned int RenderStorage::getShadowInterval() const
{
	return _shadowInterval;
}

const unsigned int RenderStorage::getCubeReflectionInterval() const
{
	return _cubeReflectionInterval;
}

const unsigned int RenderStorage::getShadowQuality() const
{
	return _shadowQuality;
}

const unsigned int RenderStorage::getCubeReflectionQuality() const
{
	return _cubeReflectionQuality;
}

const unsigned int RenderStorage::getPlanarReflectionQuality() const
{
	return _planarReflectionQuality;
}

const unsigned int RenderStorage::getPlanarRefractionQuality() const
{
	return _planarRefractionQuality;
}

const unsigned int RenderStorage::getMinBloomQuality() const
{
	return MIN_BLOOM_QUALITY;
}

const unsigned int RenderStorage::getMinDofQuality() const
{
	return MIN_DOF_QUALITY;
}

const unsigned int RenderStorage::getMinMotionBlurQuality() const
{
	return MIN_MOTION_BLUR_QUALITY;
}

const unsigned int RenderStorage::getMinShadowQuality() const
{
	return MIN_SHADOW_QUALITY;
}

const unsigned int RenderStorage::getMinReflectionQuality() const
{
	return MIN_REFLECTION_QUALITY;
}

const unsigned int RenderStorage::getMinRefractionQuality() const
{
	return MIN_REFRACTION_QUALITY;
}

const unsigned int RenderStorage::getMinAnisotropicFilteringQuality() const
{
	return MIN_ANISOTROPIC_FILTERING_QUALITY;
}

const unsigned int RenderStorage::getMaxBloomQuality() const
{
	return MAX_BLOOM_QUALITY;
}

const unsigned int RenderStorage::getMaxDofQuality() const
{
	return MAX_DOF_QUALITY;
}

const unsigned int RenderStorage::getMaxMotionBlurQuality() const
{
	return MAX_MOTION_BLUR_QUALITY;
}

const unsigned int RenderStorage::getMaxShadowQuality() const
{
	return MAX_SHADOW_QUALITY;
}

const unsigned int RenderStorage::getMaxReflectionQuality() const
{
	return MAX_REFLECTION_QUALITY;
}

const unsigned int RenderStorage::getMaxRefractionQuality() const
{
	return MAX_REFRACTION_QUALITY;
}

const unsigned int RenderStorage::getMaxAnisotropicFilteringQuality() const
{
	return MAX_ANISOTROPIC_FILTERING_QUALITY;
}

const bool RenderStorage::isAntiAliasingEnabled() const
{
	return _isAntiAliasingEnabled;
}

const bool RenderStorage::isAmbientLightingEnabled() const
{
	return _isAmbientLightingEnabled;
}

const bool RenderStorage::isDirectionalLightingEnabled() const
{
	return _isDirectionalLightingEnabled;
}

const bool RenderStorage::isReflectionsEnabled() const
{
	return _isReflectionsEnabled;
}

const bool RenderStorage::isRefractionsEnabled() const
{
	return _isRefractionsEnabled;
}

const bool RenderStorage::isFogEnabled() const
{
	return _isFogEnabled;
}

const bool RenderStorage::isBloomEnabled() const
{
	return _isBloomEnabled;
}

const bool RenderStorage::isShadowsEnabled() const
{
	return _isShadowsEnabled;
}

const bool RenderStorage::isDofEnabled() const
{
	return _isDofEnabled;
}

const bool RenderStorage::isMotionBlurEnabled() const
{
	return _isMotionBlurEnabled;
}

const bool RenderStorage::isLensFlareEnabled() const
{
	return _isLensFlareEnabled;
}

const bool RenderStorage::isShadowCircleEnabled() const
{
	return _isShadowCircleEnabled;
}

const bool RenderStorage::isTriangleCountingEnabled() const
{
	return _isTriangleCountingEnabled;
}

const bool RenderStorage::isDofDynamic() const
{
	return _isDofDynamic;
}

const BloomType RenderStorage::getBloomType() const
{
	return _bloomType;
}

const string& RenderStorage::getCursorEntityId() const
{
	return _cursorEntityId;
}

const string& RenderStorage::getLensFlareMapPath() const
{
	return _lensFlareMapPath;
}

const float RenderStorage::getSkyExposureIntensity() const
{
	return _skyExposureIntensity;
}

const float RenderStorage::getSkyExposureSpeed() const
{
	return _skyExposureSpeed;
}

const float RenderStorage::getSkyExposureLightness() const
{
	return _skyExposureLightness;
}

const fvec2 RenderStorage::getMotionBlurDifference() const
{
	return _motionBlurDifference;
}

const bool RenderStorage::isSkyExposureEnabled() const
{
	return _isSkyExposureEnabled;
}

const bool RenderStorage::isShadowsFollowingCamera() const
{
	return _isShadowsFollowingCamera;
}
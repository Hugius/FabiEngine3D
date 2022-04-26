#include "render_storage.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void RenderStorage::setPlanarReflectionMap(shared_ptr<TextureBuffer> value)
{
	_planarReflectionTextureBuffer = value;
}

void RenderStorage::setWaterReflectionMap(shared_ptr<TextureBuffer> value)
{
	_waterReflectionTextureBuffer = value;
}

void RenderStorage::setWaterRefractionMap(shared_ptr<TextureBuffer> value)
{
	_waterRefractionTextureBuffer = value;
}

void RenderStorage::setWaterEdgeMap(shared_ptr<TextureBuffer> value)
{
	_waterEdgeTextureBuffer = value;
}

void RenderStorage::setBloomMap(shared_ptr<TextureBuffer> value)
{
	_bloomTextureBuffer = value;
}

void RenderStorage::setPrimarySceneMap(shared_ptr<TextureBuffer> value)
{
	_primarySceneTextureBuffer = value;
}

void RenderStorage::setSecondarySceneMap(shared_ptr<TextureBuffer> value)
{
	_secondarySceneTextureBuffer = value;
}

void RenderStorage::setShadowMap(shared_ptr<TextureBuffer> value)
{
	_shadowTextureBuffer = value;
}

void RenderStorage::setMotionBlurMap(shared_ptr<TextureBuffer> value)
{
	_motionBlurTextureBuffer = value;
}

void RenderStorage::setLensFlareMap(shared_ptr<TextureBuffer> value)
{
	_lensFlareTextureBuffer = value;
}

void RenderStorage::setDepthMap(shared_ptr<TextureBuffer> value)
{
	_depthTextureBuffer = value;
}

void RenderStorage::setDofMap(shared_ptr<TextureBuffer> value)
{
	_dofTextureBuffer = value;
}

void RenderStorage::setFinalSceneMap(shared_ptr<TextureBuffer> value)
{
	_finalSceneTextureBuffer = value;
}

void RenderStorage::setShadowView(const mat44 & value)
{
	_shadowView = value;
}

void RenderStorage::setShadowProjection(const mat44 & value)
{
	_shadowProjection = value;
}

void RenderStorage::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void RenderStorage::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void RenderStorage::setFlareSourceUv(const fvec2 & value)
{
	_flareSourceUv = fvec2(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f));
}

void RenderStorage::setAmbientLightingColor(const fvec3 & value)
{
	_ambientLightingColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderStorage::setDirectionalLightingPosition(const fvec3 & value)
{
	_directionalLightingPosition = value;
}

void RenderStorage::setDirectionalLightingColor(const fvec3 & value)
{
	_directionalLightingColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderStorage::setShadowPosition(const fvec3 & value)
{
	_shadowPosition = value;
}

void RenderStorage::setShadowPositionOffset(const fvec3 & value)
{
	_shadowPositionOffset = value;
}

void RenderStorage::setShadowLookat(const fvec3 & value)
{
	_shadowLookat = value;
}

void RenderStorage::setShadowLookatOffset(const fvec3 & value)
{
	_shadowLookatOffset = value;
}

void RenderStorage::setFogColor(const fvec3 & value)
{
	_fogColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderStorage::setFlareSourcePosition(const fvec3 & value)
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

void RenderStorage::setMotionBlurDifference(const fvec2 & value)
{
	_motionBlurDifference = value;
}

void RenderStorage::setBloomQuality(int value)
{
	_bloomQuality = clamp(value, MIN_BLOOM_QUALITY, MAX_BLOOM_QUALITY);
}

void RenderStorage::setDofQuality(int value)
{
	_dofQuality = clamp(value, MIN_DOF_QUALITY, MAX_DOF_QUALITY);
}

void RenderStorage::setMotionBlurQuality(int value)
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

void RenderStorage::setBloomBlurCount(int value)
{
	_bloomBlurCount = max(0, value);
}

void RenderStorage::increaseTriangleCount(int value)
{
	if(_isTriangleCountingEnabled)
	{
		_triangleCount = max(0, (_triangleCount + value));
	}
}

void RenderStorage::setShadowQuality(int value)
{
	_shadowQuality = clamp(value, MIN_SHADOW_QUALITY, MAX_SHADOW_QUALITY);
}

void RenderStorage::setCubeReflectionQuality(int value)
{
	_cubeReflectionQuality = clamp(value, MIN_REFLECTION_QUALITY, MAX_REFLECTION_QUALITY);
}

void RenderStorage::setPlanarReflectionQuality(int value)
{
	_planarReflectionQuality = clamp(value, MIN_REFLECTION_QUALITY, MAX_REFLECTION_QUALITY);
}

void RenderStorage::setPlanarRefractionQuality(int value)
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

void RenderStorage::setGuiDepth(int value)
{
	_guiDepth = max(0, value);
}

void RenderStorage::setAnisotropicFilteringQuality(int value)
{
	_anisotropicFilteringQuality = clamp(value, MIN_ANISOTROPIC_FILTERING_QUALITY, MAX_ANISOTROPIC_FILTERING_QUALITY);
}

void RenderStorage::setCursorEntityId(const string & value)
{
	_cursorEntityId = value;
}

void RenderStorage::setLensFlareMapPath(const string & value)
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

void RenderStorage::setShadowInterval(int value)
{
	_shadowInterval = max(0, value);
}

void RenderStorage::setShadowsFollowingCamera(bool value)
{
	_isShadowsFollowingCamera = value;
}

void RenderStorage::setCubeReflectionInterval(int value)
{
	_cubeReflectionInterval = max(0, value);
}

const shared_ptr<TextureBuffer> RenderStorage::getPlanarReflectionTextureBuffer() const
{
	return _planarReflectionTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getWaterReflectionTextureBuffer() const
{
	return _waterReflectionTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getWaterRefractionTextureBuffer() const
{
	return _waterRefractionTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getWaterEdgeTextureBuffer() const
{
	return _waterEdgeTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getBloomTextureBuffer() const
{
	return _bloomTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getPrimarySceneTextureBuffer() const
{
	return _primarySceneTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getSecondarySceneTextureBuffer() const
{
	return _secondarySceneTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getShadowTextureBuffer() const
{
	return _shadowTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getMotionBlurTextureBuffer() const
{
	return _motionBlurTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getLensFlareTextureBuffer() const
{
	return _lensFlareTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getDepthTextureBuffer() const
{
	return _depthTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getDofTextureBuffer() const
{
	return _dofTextureBuffer;
}

const shared_ptr<TextureBuffer> RenderStorage::getFinalSceneTextureBuffer() const
{
	return _finalSceneTextureBuffer;
}

const mat44 & RenderStorage::getShadowView() const
{
	return _shadowView;
}

const mat44 & RenderStorage::getShadowProjection() const
{
	return _shadowProjection;
}

const fvec3 & RenderStorage::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & RenderStorage::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const fvec2 & RenderStorage::getFlareSourceUv() const
{
	return _flareSourceUv;
}

const fvec3 & RenderStorage::getAmbientLightingColor() const
{
	return _ambientLightingColor;
}

const fvec3 & RenderStorage::getDirectionalLightingPosition() const
{
	return _directionalLightingPosition;
}

const fvec3 & RenderStorage::getShadowPosition() const
{
	return _shadowPosition;
}

const fvec3 & RenderStorage::getShadowPositionOffset() const
{
	return _shadowPositionOffset;
}

const fvec3 & RenderStorage::getShadowLookat() const
{
	return _shadowLookat;
}

const fvec3 & RenderStorage::getShadowLookatOffset() const
{
	return _shadowLookatOffset;
}

const fvec3 & RenderStorage::getFogColor() const
{
	return _fogColor;
}

const fvec3 & RenderStorage::getFlareSourcePosition() const
{
	return _flareSourcePosition;
}

const fvec3 & RenderStorage::getDirectionalLightingColor() const
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

const int RenderStorage::getBloomQuality() const
{
	return _bloomQuality;
}

const int RenderStorage::getDofQuality() const
{
	return _dofQuality;
}

const int RenderStorage::getMotionBlurQuality() const
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

const int RenderStorage::getBloomBlurCount() const
{
	return _bloomBlurCount;
}

const int RenderStorage::getTriangleCount() const
{
	return _triangleCount;
}

const int RenderStorage::getGuiDepth() const
{
	return _guiDepth;
}

const int RenderStorage::getAnisotropicFilteringQuality() const
{
	return _anisotropicFilteringQuality;
}

const int RenderStorage::getShadowInterval() const
{
	return _shadowInterval;
}

const int RenderStorage::getCubeReflectionInterval() const
{
	return _cubeReflectionInterval;
}

const int RenderStorage::getShadowQuality() const
{
	return _shadowQuality;
}

const int RenderStorage::getCubeReflectionQuality() const
{
	return _cubeReflectionQuality;
}

const int RenderStorage::getPlanarReflectionQuality() const
{
	return _planarReflectionQuality;
}

const int RenderStorage::getPlanarRefractionQuality() const
{
	return _planarRefractionQuality;
}

const int RenderStorage::getMinBloomQuality() const
{
	return MIN_BLOOM_QUALITY;
}

const int RenderStorage::getMinDofQuality() const
{
	return MIN_DOF_QUALITY;
}

const int RenderStorage::getMinMotionBlurQuality() const
{
	return MIN_MOTION_BLUR_QUALITY;
}

const int RenderStorage::getMinShadowQuality() const
{
	return MIN_SHADOW_QUALITY;
}

const int RenderStorage::getMinReflectionQuality() const
{
	return MIN_REFLECTION_QUALITY;
}

const int RenderStorage::getMinRefractionQuality() const
{
	return MIN_REFRACTION_QUALITY;
}

const int RenderStorage::getMinAnisotropicFilteringQuality() const
{
	return MIN_ANISOTROPIC_FILTERING_QUALITY;
}

const int RenderStorage::getMaxBloomQuality() const
{
	return MAX_BLOOM_QUALITY;
}

const int RenderStorage::getMaxDofQuality() const
{
	return MAX_DOF_QUALITY;
}

const int RenderStorage::getMaxMotionBlurQuality() const
{
	return MAX_MOTION_BLUR_QUALITY;
}

const int RenderStorage::getMaxShadowQuality() const
{
	return MAX_SHADOW_QUALITY;
}

const int RenderStorage::getMaxReflectionQuality() const
{
	return MAX_REFLECTION_QUALITY;
}

const int RenderStorage::getMaxRefractionQuality() const
{
	return MAX_REFRACTION_QUALITY;
}

const int RenderStorage::getMaxAnisotropicFilteringQuality() const
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

const string & RenderStorage::getCursorEntityId() const
{
	return _cursorEntityId;
}

const string & RenderStorage::getLensFlareMapPath() const
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
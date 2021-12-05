#include "render_bus.hpp"

const TextureID RenderBus::getPlanarReflectionMap() const
{
	return _planarReflectionMap;
}

const TextureID RenderBus::getWaterReflectionMap() const
{
	return _waterReflectionMap;
}

const TextureID RenderBus::getWaterRefractionMap() const
{
	return _waterRefractionMap;
}

const TextureID RenderBus::getBloomMap() const
{
	return _bloomMap;
}

const TextureID RenderBus::getPrimaryWorldMap() const
{
	return _primaryWorldMap;
}

const TextureID RenderBus::getSecondaryWorldMap() const
{
	return _secondaryWorldMap;
}

const TextureID RenderBus::getShadowMap() const
{
	return _shadowMap;
}

const TextureID RenderBus::getMotionBlurMap() const
{
	return _motionBlurMap;
}

const TextureID RenderBus::getLensFlareMap() const
{
	return _lensFlareMap;
}

const TextureID RenderBus::getDepthMap() const
{
	return _depthMap;
}

const TextureID RenderBus::getDofMap() const
{
	return _dofMap;
}

const TextureID RenderBus::getFinalWorldMap() const
{
	return _finalWorldMap;
}

const mat44 RenderBus::getViewMatrix() const
{
	return _viewMatrix;
}

const mat44 RenderBus::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const mat44 RenderBus::getShadowMatrix() const
{
	return _shadowMatrix;
}

const fvec2 RenderBus::getFlareSourceUV() const
{
	return _flareSourceUV;
}

const fvec4 RenderBus::getClippingPlane() const
{
	return _clippingPlane;
}

const fvec3 RenderBus::getCameraPosition() const
{
	return _cameraPosition;
}

const fvec3 RenderBus::getCameraFront() const
{
	return _cameraFront;
}

const fvec3 RenderBus::getAmbientLightingColor() const
{
	return _ambientLightColor;
}

const fvec3 RenderBus::getDirectionalLightingPosition() const
{
	return _directionalLightPosition;
}

const fvec3 RenderBus::getShadowEyePosition() const
{
	return _shadowEyePosition;
}

const fvec3 RenderBus::getShadowCenterPosition() const
{
	return _shadowCenterPosition;
}

const fvec3 RenderBus::getFogColor() const
{
	return _fogColor;
}

const fvec3 RenderBus::getFlareSourcePosition() const
{
	return _flareSourcePosition;
}

const fvec3 RenderBus::getDirectionalLightingColor() const
{
	return _directionalLightColor;
}

const float RenderBus::getPlanarReflectionHeight() const
{
	return _planarReflectionHeight;
}

const float RenderBus::getShadowAreaSize() const
{
	return _shadowAreaSize;
}

const float RenderBus::getShadowAreaReach() const
{
	return _shadowAreaReach;
}

const float RenderBus::getShadowLightness() const
{
	return _shadowLightness;
}

const float RenderBus::getLensFlareTransparency() const
{
	return _lensFlareTransparency;
}

const float RenderBus::getLensFlareIntensity() const
{
	return _lensFlareIntensity;
}

const float RenderBus::getLensFlareSensitivity() const
{
	return _lensFlareSensitivity;
}

const float RenderBus::getMotionBlurStrength() const
{
	return _motionBlurStrength;
}

const float RenderBus::getMotionBlurMixValue() const
{
	return _motionBlurMixValue;
}

const float RenderBus::getSkyMixValue() const
{
	return _skyMixValue;
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

const float RenderBus::getNearDistance() const
{
	return _nearDistance;
}

const float RenderBus::getFarDistance() const
{
	return _farDistance;
}

const float RenderBus::getDofMaxDistance() const
{
	return _dofMaxDistance;
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

const unsigned int RenderBus::getRefractionQuality() const
{
	return _refractionQuality;
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

const bool RenderBus::isWireframeRenderingEnabled() const
{
	return _isWireframeRenderingEnabled;
}

const bool RenderBus::isAabbFrameRenderingEnabled() const
{
	return _isAabbFrameRenderingEnabled;
}

const bool RenderBus::isShadowFrameRenderingEnabled() const
{
	return _isShadowFrameRenderingEnabled;
}

const bool RenderBus::isDebugRenderingEnabled() const
{
	return _isDebugRenderingEnabled;
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

const string& RenderBus::getCursorEntityID() const
{
	return _cursorEntityID;
}

const string& RenderBus::getLensFlareMapPath() const
{
	return _lensFlareMapPath;
}
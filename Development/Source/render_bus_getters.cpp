#include "render_bus.hpp"

const TextureID RenderBus::getMainSkyReflectionCubeMap()
{
	return _mainSkyReflectionCubeMap;
}

const TextureID RenderBus::getMixSkyReflectionCubeMap()
{
	return _mixSkyReflectionCubeMap;
}

const TextureID RenderBus::getSceneReflectionMap()
{
	return _sceneReflectionMap;
}

const TextureID RenderBus::getWaterReflectionMap()
{
	return _waterReflectionMap;
}

const TextureID RenderBus::getWaterRefractionMap()
{
	return _waterRefractionMap;
}

const TextureID RenderBus::getBloomMap()
{
	return _bloomMap;
}

const TextureID RenderBus::getPrimarySceneMap()
{
	return _primarySceneMap;
}

const TextureID RenderBus::getSecondarySceneMap()
{
	return _secondarySceneMap;
}

const TextureID RenderBus::getShadowMap()
{
	return _shadowMap;
}

const TextureID RenderBus::getMotionBlurMap()
{
	return _motionBlurMap;
}

const TextureID RenderBus::getLensFlareMap()
{
	return _lensFlareMap;
}

const TextureID RenderBus::getSceneDepthMap()
{
	return _sceneDepthMap;
}

const TextureID RenderBus::getDofMap()
{
	return _dofMap;
}

const TextureID RenderBus::getFinalSceneMap()
{
	return _finalSceneMap;
}

const Matrix44 RenderBus::getViewMatrix()
{
	return _viewMatrix;
}

const Matrix44 RenderBus::getProjectionMatrix()
{
	return _projectionMatrix;
}

const Matrix44 RenderBus::getSkyRotationMatrix()
{
	return _skyRotationMatrix;
}

const Matrix44 RenderBus::getShadowMatrix()
{
	return _shadowMatrix;
}

const Vec4 RenderBus::getFlareSourcePositionClipspace()
{
	return _flareSourcePositionClipspace;
}

const Vec4 RenderBus::getClippingPlane()
{
	return _clippingPlane;
}

const Vec3 RenderBus::getCameraPosition()
{
	return _cameraPosition;
}

const Vec3 RenderBus::getCameraFront()
{
	return _cameraFront;
}

const Vec3 RenderBus::getAmbientLightColor()
{
	return _ambientLightColor;
}

const Vec3 RenderBus::getDirectionalLightPosition()
{
	return _directionalLightPosition;
}

const Vec3 RenderBus::getSpotLightColor()
{
	return _spotLightColor;
}

const Vec3 RenderBus::getShadowEyePosition()
{
	return _shadowEyePosition;
}

const Vec3 RenderBus::getShadowAreaCenter()
{
	return _shadowAreaCenter;
}

const Vec3 RenderBus::getFogColor()
{
	return _fogColor;
}

const Vec3 RenderBus::getFlareSourcePosition()
{
	return _flareSourcePosition;
}

const Vec3 RenderBus::getMainSkyColor()
{
	return _mainSkyColor;
}

const Vec3 RenderBus::getMixSkyColor()
{
	return _mixSkyColor;
}

const Vec3 RenderBus::getDirectionalLightColor()
{
	return _directionalLightColor;
}

const float RenderBus::getSceneReflectionHeight()
{
	return _sceneReflectionHeight;
}

const float RenderBus::getShadowAreaSize()
{
	return _shadowAreaSize;
}

const float RenderBus::getShadowAreaReach()
{
	return _shadowAreaReach;
}

const float RenderBus::getShadowLightness()
{
	return _shadowLightness;
}

const float RenderBus::getLensFlareAlpha()
{
	return _lensFlareAlpha;
}

const float RenderBus::getLensFlareIntensity()
{
	return _lensFlareIntensity;
}

const float RenderBus::getLensFlareMultiplier()
{
	return _lensFlareMultiplier;
}

const float RenderBus::getMotionBlurStrength()
{
	return _motionBlurStrength;
}

const float RenderBus::getMotionBlurMixValue()
{
	return _motionBlurMixValue;
}

const float RenderBus::getSkyMixValue()
{
	return _skyMixValue;
}

const float RenderBus::getMainSkyLightness()
{
	return _mainSkyLightness;
}

const float RenderBus::getMixSkyLightness()
{
	return _mixSkyLightness;
}

const float RenderBus::getAmbientLightIntensity()
{
	return _ambientLightIntensity;
}

const float RenderBus::getDirectionalLightIntensity()
{
	return _directionalLightIntensity;
}

const float RenderBus::getSpotLightIntensity()
{
	return _spotLightIntensity;
}

const float RenderBus::getMaxSpotLightAngle()
{
	return _maxSpotLightAngle;
}

const float RenderBus::getMaxSpotLightDistance()
{
	return _maxSpotLightDistance;
}

const float RenderBus::getFogMinDistance()
{
	return _fogMinDistance;
}

const float RenderBus::getFogMaxDistance()
{
	return _fogMaxDistance;
}

const float RenderBus::getFogThickness()
{
	return _fogThickness;
}

const float RenderBus::getBloomIntensity()
{
	return _bloomIntensity;
}

const float RenderBus::getCameraYaw()
{
	return _cameraYaw;
}

const float RenderBus::getCameraPitch()
{
	return _cameraPitch;
}

const float RenderBus::getNearZ()
{
	return _nearZ;
}

const float RenderBus::getFarZ()
{
	return _farZ;
}

const float RenderBus::getDofMaxDistance()
{
	return _dofMaxDistance;
}

const float RenderBus::getDofBlurDistance()
{
	return _dofBlurDistance;
}

const unsigned int RenderBus::getBloomBlurCount()
{
	return _bloomBlurCount;
}

const unsigned int RenderBus::getTriangleCount()
{
	return _triangleCount;
}

const unsigned int RenderBus::getAnisotropicFilteringQuality()
{
	return _anisotropicFilteringQuality;
}

const unsigned int RenderBus::getShadowQuality()
{
	return _shadowQuality;
}

const unsigned int RenderBus::getReflectionQuality()
{
	return _reflectionQuality;
}

const unsigned int RenderBus::getRefractionQuality()
{
	return _refractionQuality;
}

const bool RenderBus::isFxaaEnabled()
{
	return _isFxaaEnabled;
}

const bool RenderBus::isAmbientLightingEnabled()
{
	return _isAmbientLightingEnabled;
}

const bool RenderBus::isDirectionalLightingEnabled()
{
	return _isDirectionalLightingEnabled;
}

const bool RenderBus::isSpecularLightingEnabled()
{
	return _isSpecularLightingEnabled;
}

const bool RenderBus::isPointLightingEnabled()
{
	return _isPointLightingEnabled;
}

const bool RenderBus::isSpotLightingEnabled()
{
	return _isSpotLightingEnabled;
}

const bool RenderBus::isFogEnabled()
{
	return _isFogEnabled;
}

const bool RenderBus::isBloomEnabled()
{
	return _isBloomEnabled;
}

const bool RenderBus::isSkyExposureEnabled()
{
	return _isSkyExposureEnabled;
}

const bool RenderBus::isShadowsEnabled()
{
	return _isShadowsEnabled;
}

const bool RenderBus::isDofEnabled()
{
	return _isDofEnabled;
}

const bool RenderBus::isMotionBlurEnabled()
{
	return _isMotionBlurEnabled;
}

const bool RenderBus::isLensFlareEnabled()
{
	return _isLensFlareEnabled;
}

const bool RenderBus::isWireFrameRenderingEnabled()
{
	return _isWireFrameRenderingEnabled;
}

const bool RenderBus::isAabbFrameRenderingEnabled()
{
	return _isAabbFrameRenderingEnabled;
}

const bool RenderBus::isShadowFrameRenderingEnabled()
{
	return _isShadowFrameRenderingEnabled;
}

const bool RenderBus::isLightedShadowingEnabled()
{
	return _isLightedShadowingEnabled;
}

const bool RenderBus::isDebugRenderingEnabled()
{
	return _isDebugRenderingEnabled;
}

const bool RenderBus::isTriangleCountingEnabled()
{
	return _isTriangleCountingEnabled;
}

const bool RenderBus::isDofDynamic()
{
	return _isDofDynamic;
}

const BloomType RenderBus::getBloomType()
{
	return _bloomType;
}

const string& RenderBus::getCursorEntityID()
{
	return _cursorEntityID;
}

const string& RenderBus::getLensFlareMapPath()
{
	return _lensFlareMapPath;
}
#include "render_bus.hpp"

const GLuint RenderBus::getMainSkyReflectionCubeMap() const
{
	return _mainSkyReflectionCubeMap;
}

const GLuint RenderBus::getMixSkyReflectionCubeMap() const
{
	return _mixSkyReflectionCubeMap;
}

const GLuint RenderBus::getSceneReflectionMap() const
{
	return _sceneReflectionMap;
}

const GLuint RenderBus::getWaterReflectionMap() const
{
	return _waterReflectionMap;
}

const GLuint RenderBus::getWaterRefractionMap() const
{
	return _waterRefractionMap;
}

const GLuint RenderBus::getBloomMap() const
{
	return _bloomMap;
}

const GLuint RenderBus::getPrimarySceneMap() const
{
	return _primarySceneMap;
}

const GLuint RenderBus::getSecondarySceneMap() const
{
	return _secondarySceneMap;
}

const GLuint RenderBus::getShadowMap() const
{
	return _shadowMap;
}

const GLuint RenderBus::getMotionBlurMap() const
{
	return _motionBlurMap;
}

const GLuint RenderBus::getLensFlareMap() const
{
	return _lensFlareMap;
}

const GLuint RenderBus::getSceneDepthMap() const
{
	return _sceneDepthMap;
}

const GLuint RenderBus::getBlurMap() const
{
	return _blurMap;
}

const GLuint RenderBus::getPostProcessedSceneMap() const
{
	return _postProcessedSceneMap;
}

const Matrix44 & RenderBus::getViewMatrix() const
{
	return _viewMatrix;
}

const Matrix44 & RenderBus::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const Matrix44 & RenderBus::getSkyRotationMatrix() const
{
	return _skyRotationMatrix;
}

const Matrix44 & RenderBus::getShadowMatrix() const
{
	return _shadowMatrix;
}

const Vec4 RenderBus::getFlareSourcePositionClipspace() const
{
	return _flareSourcePositionClipspace;
}

const Vec4 RenderBus::getClippingPlane() const
{
	return _clippingPlane;
}

const Vec3 RenderBus::getCameraPosition() const
{
	return _cameraPosition;
}

const Vec3 RenderBus::getCameraFront() const
{
	return _cameraFront;
}

const Vec3 RenderBus::getAmbientLightColor() const
{
	return _ambientLightColor;
}

const Vec3 RenderBus::getDirectionalLightPosition() const
{
	return _directionalLightPosition;
}

const Vec3 RenderBus::getSpotLightColor() const
{
	return _spotLightColor;
}

const Vec3 RenderBus::getShadowEyePosition() const
{
	return _shadowEyePosition;
}

const Vec3 RenderBus::getShadowAreaCenter() const
{
	return _shadowAreaCenter;
}

const Vec3 RenderBus::getFogColor() const
{
	return _fogColor;
}

const Vec3 RenderBus::getFlareSourcePosition() const
{
	return _flareSourcePosition;
}

const Vec3 RenderBus::getMainSkyColor() const
{
	return _mainSkyColor;
}

const Vec3 RenderBus::getMixSkyColor() const
{
	return _mixSkyColor;
}

const Vec3 RenderBus::getDirectionalLightColor() const
{
	return _directionalLightColor;
}

const float RenderBus::getSceneReflectionHeight() const
{
	return _sceneReflectionHeight;
}

const float RenderBus::getSceneReflectionMixValue() const
{
	return _sceneReflectionMixValue;
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

const float RenderBus::getLensFlareAlpha() const
{
	return _lensFlareAlpha;
}

const float RenderBus::getLensFlareIntensity() const
{
	return _lensFlareIntensity;
}

const float RenderBus::getLensFlareMultiplier() const
{
	return _lensFlareMultiplier;
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

const float RenderBus::getMainSkyLightness() const
{
	return _mainSkyLightness;
}

const float RenderBus::getMixSkyLightness() const
{
	return _mixSkyLightness;
}

const float RenderBus::getAmbientLightIntensity() const
{
	return _ambientLightIntensity;
}

const float RenderBus::getDirectionalLightIntensity() const
{
	return _directionalLightIntensity;
}

const float RenderBus::getSpotLightIntensity() const
{
	return _spotLightIntensity;
}

const float RenderBus::getMaxSpotLightAngle() const
{
	return _maxSpotLightAngle;
}

const float RenderBus::getMaxSpotLightDistance() const
{
	return _maxSpotLightDistance;
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

const float RenderBus::getNearZ() const
{
	return _nearZ;
}

const float RenderBus::getFarZ() const
{
	return _farZ;
}

const float RenderBus::getDofMaxDistance() const
{
	return _dofMaxDistance;
}

const float RenderBus::getDofBlurDistance() const
{
	return _dofBlurDistance;
}

const float RenderBus::getSkyReflectionMixValue() const
{
	return _skyReflectionMixValue;
}

const unsigned int RenderBus::getBloomBlurSize() const
{
	return _bloomBlurSize;
}

const unsigned int RenderBus::getTriangleCount() const
{
	return _triangleCount;
}

const unsigned int RenderBus::getShadowMapSize() const
{
	return _shadowMapSize;
}

const unsigned int RenderBus::getReflectionMapSize() const
{
	return _reflectionMapSize;
}

const unsigned int RenderBus::getRefractionMapSize() const
{
	return _refractionMapSize;
}

const bool RenderBus::isFxaaEnabled() const
{
	return _isFxaaEnabled;
}

const bool RenderBus::isSceneReflectionsEnabled() const
{
	return _isSceneReflectionsEnabled;
}

const bool RenderBus::isAmbientLightingEnabled() const
{
	return _isAmbientLightingEnabled;
}

const bool RenderBus::isDirectionalLightingEnabled() const
{
	return _isDirectionalLightingEnabled;
}

const bool RenderBus::isSpecularLightingEnabled() const
{
	return _isSpecularLightingEnabled;
}

const bool RenderBus::isPointLightingEnabled() const
{
	return _isPointLightingEnabled;
}

const bool RenderBus::isSpotLightingEnabled() const
{
	return _isSpotLightingEnabled;
}

const bool RenderBus::isFogEnabled() const
{
	return _isFogEnabled;
}

const bool RenderBus::isLightMappingEnabled() const
{
	return _isLightMappingEnabled;
}

const bool RenderBus::isNormalMappingEnabled() const
{
	return _isNormalMappingEnabled;
}

const bool RenderBus::isSkyReflectionsEnabled() const
{
	return _isSkyReflectionsEnabled;
}

const bool RenderBus::isBloomEnabled() const
{
	return _isBloomEnabled;
}

const bool RenderBus::isSkyHdrEnabled() const
{
	return _isSkyHdrEnabled;
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

const bool RenderBus::isLightedShadowingEnabled() const
{
	return _isLightedShadowingEnabled;
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
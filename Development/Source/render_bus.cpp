#include "render_bus.hpp"

void RenderBus::setSkyReflectionCubeMap(GLuint value)
{
	_skyReflectionCubeMap = value;
}

void RenderBus::setSceneReflectionMap(GLuint value)
{
	_sceneReflectionMap = value;
}

void RenderBus::setSceneRefractionMap(GLuint value)
{
	_sceneRefractionMap = value;
}

void RenderBus::setBloomMap(GLuint value)
{
	_bloomMap = value;
}

void RenderBus::setSceneMap(GLuint value)
{
	_sceneMap = value;
}

void RenderBus::setShadowMap(GLuint value)
{
	_shadowMap = value;
}

void RenderBus::setMotionBlurMap(GLuint value)
{
	_motionBlurMap = value;
}

void RenderBus::setLensFlareMap(GLuint value)
{
	_lensFlareMap = value;
}

void RenderBus::setSceneDepthMap(GLuint value)
{
	_sceneDepthMap = value;
}

void RenderBus::setBlurMap(GLuint value)
{
	_blurMap = value;
}

void RenderBus::setPostProcessedSceneMap(GLuint value)
{
	_postProcessedSceneMap = value;
}

void RenderBus::setViewMatrix(const Matrix44& value)
{
	_viewMatrix = value;
}

void RenderBus::setProjectionMatrix(const Matrix44& value)
{
	_projectionMatrix = value;
}

void RenderBus::setSkyRotationMatrix(const Matrix44& value)
{
	_skyRotationMatrix = value;
}

void RenderBus::setShadowMatrix(const Matrix44& value)
{
	_shadowMatrix = value;
}

void RenderBus::setFlareSourcePositionClipspace(Vec4 value)
{
	_flareSourcePositionClipspace = value;
}

void RenderBus::setCameraPosition(Vec3 value)
{
	_cameraPosition = value;
}

void RenderBus::setCameraFront(Vec3 value)
{
	_cameraFront = value;
}

void RenderBus::setAmbientLightColor(Vec3 value)
{
	_ambientLightColor = value;
}

void RenderBus::setDirectionalLightPos(Vec3 value)
{
	_directionalLightPosition = value;
}

void RenderBus::setDirectionalLightColor(Vec3 value)
{
	_directionalLightColor = value;
}

void RenderBus::setSpotLightColor(Vec3 value)
{
	_spotLightColor = value;
}

void RenderBus::setShadowEyePosition(Vec3 value)
{
	_shadowEyePosition = value;
}

void RenderBus::setShadowAreaCenter(Vec3 value)
{
	_shadowAreaCenter = value;
}

void RenderBus::setFogColor(Vec3 value)
{
	_fogColor = value;
}

void RenderBus::setFlareSourcePosition(Vec3 value)
{
	_flareSourcePosition = value;
}

void RenderBus::setSceneReflectionHeight(float value)
{
	_sceneReflectionHeight = value;
}

void RenderBus::setSceneReflectionOffset(float value)
{
	_sceneReflectionOffset = value;
}

void RenderBus::setSceneReflectionFactor(float value)
{
	_sceneReflectionFactor = value;
}

void RenderBus::setShadowAreaSize(float value)
{
	_shadowAreaSize = value;
}

void RenderBus::setShadowAreaReach(float value)
{
	_shadowAreaReach = value;
}

void RenderBus::setLensFlareAlpha(float value)
{
	_lensFlareAlpha = value;
}

void RenderBus::setLensFlareIntensity(float value)
{
	_lensFlareIntensity = value;
}

void RenderBus::setLensFlareMultiplier(float value)
{
	_lensFlareMultiplier = value;
}

void RenderBus::setMotionBlurStrength(float value)
{
	_motionBlurStrength = value;
}

void RenderBus::setMotionBlurMixValue(float value)
{
	_motionBlurMixValue = value;
}

void RenderBus::setMaxSpotLightAngle(float value)
{
	_maxSpotLightAngle = value;
}

void RenderBus::setMaxSpotLightDistance(float value)
{
	_maxSpotLightDistance = value;
}

void RenderBus::setAmbientLightIntensity(float value)
{
	_ambientLightIntensity = value;
}

void RenderBus::setDirectionalLightIntensity(float value)
{
	_directionalLightIntensity = value;
}

void RenderBus::setSpotLightIntensity(float value)
{
	_spotLightIntensity = value;
}

void RenderBus::setFogMinDistance(float value)
{
	_fogMinDistance = value;
}

void RenderBus::setFogMaxDistance(float value)
{
	_fogMaxDistance = value;
}

void RenderBus::setFogDefaultFactor(float value)
{
	_fogDefaultFactor = value;
}

void RenderBus::setBloomIntensity(float value)
{
	_bloomIntensity = value;
}

void RenderBus::setBloomBrightnessTreshold(float value)
{
	_bloomBrightnessTreshold = value;
}

void RenderBus::setCameraYaw(float value)
{
	_cameraYaw = value;
}

void RenderBus::setCameraPitch(float value)
{
	_cameraPitch = value;
}

void RenderBus::setNearZ(float value)
{
	_nearZ = value;
}

void RenderBus::setFarZ(float value)
{
	_farZ = value;
}

void RenderBus::setDofMaxDistance(float value)
{
	_dofMaxDistance = value;
}

void RenderBus::setDofBlurDistance(float value)
{
	_dofBlurDistance = value;
}

void RenderBus::setSkyReflectionFactor(float value)
{
	_skyReflectionFactor = value;
}

void RenderBus::setBloomBlurSize(int value)
{
	_bloomBlurSize = value;
}

void RenderBus::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderBus::increaseTriangleCount(int value)
{
	if (_isTriangleCountingEnabled)
	{
		_triangleCount += value;
	}
}

void RenderBus::setMsaaSampleCount(int value)
{
	_msaaSampleCount = value;
}

void RenderBus::setShadowMapSize(int value)
{
	_shadowMapSize = value;
}

void RenderBus::setSceneReflectionMapSize(int value)
{
	_sceneReflectionMapSize = value;
}

void RenderBus::setSceneRefractionMapSize(int value)
{
	_sceneRefractionMapSize = value;
}

void RenderBus::setMsaaEnabled(bool value)
{
	_isMsaaEnabled = value;
}

void RenderBus::setSceneReflectionsEnabled(bool value)
{
	_isSceneReflectionsEnabled = value;
}

void RenderBus::setAmbientLightingEnabled(bool value)
{
	_isAmbientLightingEnabled = value;
}

void RenderBus::setDirectionalLightingEnabled(bool value)
{
	_isDirectionalLightingEnabled = value;
}

void RenderBus::setSpecularLightingEnabled(bool value)
{
	_isSpecularLightingEnabled = value;
}

void RenderBus::setPointLightingEnabled(bool value)
{
	_isPointLightingEnabled = value;
}

void RenderBus::setSpotLightingEnabled(bool value)
{
	_isSpotLightingEnabled = value;
}

void RenderBus::setFogEnabled(bool value)
{
	_isFogEnabled = value;
}

void RenderBus::setLightMappingEnabled(bool value)
{
	_isLightMappingEnabled = value;
}

void RenderBus::setNormalMappingEnabled(bool value)
{
	_isNormalMappingEnabled = value;
}

void RenderBus::setSkyReflectionsEnabled(bool value)
{
	_isSkyReflectionsEnabled = value;
}

void RenderBus::setBloomEnabled(bool value)
{
	_isBloomEnabled = value;
}

void RenderBus::setWaterEffectsEnabled(bool value)
{
	_isWaterEffectsEnabled = value;
}

void RenderBus::setSkyHdrEnabled(bool value)
{
	_isSkyHdrEnabled = value;
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

void RenderBus::setWireframeRenderingEnabled(bool value)
{
	_isWireframeRenderingEnabled = value;
}

void RenderBus::setAabbFrameRenderingEnabled(bool value)
{
	_isAabbFrameRenderingEnabled = value;
}

void RenderBus::setDebugRenderingEnabled(bool value)
{
	_isDebugRenderingEnabled = value;
}

void RenderBus::setShadowFrameRenderingEnabled(bool value)
{
	_isShadowFrameRenderingEnabled = value;
}

void RenderBus::setTriangleCountingEnabled(bool value)
{
	_isTriangleCountingEnabled = value;
}

void RenderBus::setDofDynamic(bool value)
{
	_isDofDynamic = value;
}

void RenderBus::setCursorEntityID(const string& value)
{
	_cursorEntityID = value;
}

void RenderBus::setLensFlareMapPath(const string& value)
{
	_lensFlareMapPath = value;
}

const GLuint RenderBus::getSkyReflectionCubeMap() const
{
	return _skyReflectionCubeMap;
}

const GLuint RenderBus::getSceneReflectionMap() const
{
	return _sceneReflectionMap;
}

const GLuint RenderBus::getSceneRefractionMap() const
{
	return _sceneRefractionMap;
}

const GLuint RenderBus::getBloomMap() const
{
	return _bloomMap;
}

const GLuint RenderBus::getSceneMap() const
{
	return _sceneMap;
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

const Vec3 RenderBus::getDirectionalLightColor() const
{
	return _directionalLightColor;
}

const float RenderBus::getSceneReflectionHeight() const
{
	return _sceneReflectionHeight;
}

const float RenderBus::getSceneReflectionOffset() const
{
	return _sceneReflectionOffset;
}

const float RenderBus::getSceneReflectionFactor() const
{
	return _sceneReflectionFactor;
}

const float RenderBus::getShadowAreaSize() const
{
	return _shadowAreaSize;
}

const float RenderBus::getShadowAreaReach() const
{
	return _shadowAreaReach;
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

const float RenderBus::getFogDefaultFactor() const
{
	return _fogDefaultFactor;
}

const float RenderBus::getBloomIntensity() const
{
	return _bloomIntensity;
}

const float RenderBus::getBloomBrightnessTreshold() const
{
	return _bloomBrightnessTreshold;
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

const float RenderBus::getSkyReflectionFactor() const
{
	return _skyReflectionFactor;
}

const int RenderBus::getBloomBlurSize() const
{
	return _bloomBlurSize;
}

const int RenderBus::getTriangleCount() const
{
	return _triangleCount;
}

const int RenderBus::getMsaaSampleCount() const
{
	return _msaaSampleCount;
}

const int RenderBus::getShadowMapSize() const
{
	return _shadowMapSize;
}

const int RenderBus::getSceneReflectionMapSize() const
{
	return _sceneReflectionMapSize;
}

const int RenderBus::getSceneRefractionMapSize() const
{
	return _sceneRefractionMapSize;
}

const bool RenderBus::isMsaaEnabled() const
{
	return _isMsaaEnabled;
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

const bool RenderBus::isWaterEffectsEnabled() const
{
	return _isWaterEffectsEnabled;
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

const string& RenderBus::getCursorEntityID() const
{
	return _cursorEntityID;
}

const string& RenderBus::getLensFlareMapPath() const
{
	return _lensFlareMapPath;
}
#include "render_bus.hpp"

void RenderBus::setSkyReflectionCubeMap(GLuint val)
{
	_skyReflectionCubeMap = val;
}

void RenderBus::setSceneReflectionMap(GLuint val)
{
	_sceneReflectionMap = val;
}

void RenderBus::setSceneRefractionMap(GLuint val)
{
	_sceneRefractionMap = val;
}

void RenderBus::setBloomMap(GLuint val)
{
	_bloomMap = val;
}

void RenderBus::setSceneMap(GLuint val)
{
	_sceneMap = val;
}

void RenderBus::setShadowMap(GLuint val)
{
	_shadowMap = val;
}

void RenderBus::setMotionBlurMap(GLuint val)
{
	_motionBlurMap = val;
}

void RenderBus::setLensFlareMap(GLuint val)
{
	_lensFlareMap = val;
}

void RenderBus::setSceneDepthMap(GLuint val)
{
	_sceneDepthMap = val;
}

void RenderBus::setBlurMap(GLuint val)
{
	_blurMap = val;
}

void RenderBus::setPostProcessedSceneMap(GLuint val)
{
	_postProcessedSceneMap = val;
}

void RenderBus::setViewMatrix(const Matrix44 & val)
{
	_viewMatrix = val;
}

void RenderBus::setProjectionMatrix(const Matrix44 & val)
{
	_projectionMatrix = val;
}

void RenderBus::setSkyRotationMatrix(const Matrix44 & val)
{
	_skyRotationMatrix = val;
}

void RenderBus::setShadowMatrix(const Matrix44 & val)
{
	_shadowMatrix = val;
}

void RenderBus::setFlareSourcePositionClipspace(Vec4 val)
{
	_flareSourcePositionClipspace = val;
}

void RenderBus::setCameraPosition(Vec3 val)
{
	_cameraPosition = val;
}

void RenderBus::setCameraFront(Vec3 val)
{
	_cameraFront = val;
}

void RenderBus::setAmbientLightColor(Vec3 val)
{
	_ambientLightColor = val;
}

void RenderBus::setDirectionalLightPos(Vec3 val)
{
	_directionalLightPosition = val;
}

void RenderBus::setDirectionalLightColor(Vec3 val)
{
	_directionalLightColor = val;
}

void RenderBus::setSpotLightColor(Vec3 val)
{
	_spotLightColor = val;
}

void RenderBus::setShadowEyePosition(Vec3 val)
{
	_shadowEyePosition = val;
}

void RenderBus::setShadowAreaCenter(Vec3 val)
{
	_shadowAreaCenter = val;
}

void RenderBus::setFogColor(Vec3 val)
{
	_fogColor = val;
}

void RenderBus::setFlareSourcePosition(Vec3 val)
{
	_flareSourcePosition = val;
}

void RenderBus::setSceneReflectionHeight(float val)
{
	_sceneReflectionHeight = val;
}

void RenderBus::setSceneReflectionOffset(float val)
{
	_sceneReflectionOffset = val;
}

void RenderBus::setSceneReflectionFactor(float val)
{
	_sceneReflectionFactor = val;
}

void RenderBus::setShadowAreaSize(float val)
{
	_shadowAreaSize = val;
}

void RenderBus::setShadowAreaReach(float val)
{
	_shadowAreaReach = val;
}

void RenderBus::setLensFlareAlpha(float val)
{
	_lensFlareAlpha = val;
}

void RenderBus::setLensFlareIntensity(float val)
{
	_lensFlareIntensity = val;
}

void RenderBus::setLensFlareMultiplier(float val)
{
	_lensFlareMultiplier = val;
}

void RenderBus::setMotionBlurStrength(float val)
{
	_motionBlurStrength = val;
}

void RenderBus::setMaxSpotLightAngle(float val)
{
	_maxSpotLightAngle = val;
}

void RenderBus::setMaxSpotLightDistance(float val)
{
	_maxSpotLightDistance = val;
}

void RenderBus::setAmbientLightIntensity(float val)
{
	_ambientLightIntensity = val;
}

void RenderBus::setDirectionalLightIntensity(float val)
{
	_directionalLightIntensity = val;
}

void RenderBus::setSpotLightIntensity(float val)
{
	_spotLightIntensity = val;
}

void RenderBus::setFogMinDistance(float val)
{
	_fogMinDistance = val;
}

void RenderBus::setFogMaxDistance(float val)
{
	_fogMaxDistance = val;
}

void RenderBus::setFogDefaultFactor(float val)
{
	_fogDefaultFactor = val;
}

void RenderBus::setBloomIntensity(float val)
{
	_bloomIntensity = val;
}

void RenderBus::setBloomBrightnessTreshold(float val)
{
	_bloomBrightnessTreshold = val;
}

void RenderBus::setCameraYaw(float val)
{
	_cameraYaw = val;
}

void RenderBus::setCameraPitch(float val)
{
	_cameraPitch = val;
}

void RenderBus::setNearZ(float val)
{
	_nearZ = val;
}

void RenderBus::setFarZ(float val)
{
	_farZ = val;
}

void RenderBus::setDofMaxDistance(float val)
{
	_dofMaxDistance = val;
}

void RenderBus::setDofBlurDistance(float val)
{
	_dofBlurDistance = val;
}

void RenderBus::setSkyReflectionFactor(float val)
{
	_skyReflectionFactor = val;
}

void RenderBus::setBloomBlurSize(int val)
{
	_bloomBlurSize = val;
}

void RenderBus::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderBus::increaseTriangleCount(int val)
{
	if (_isTriangleCountingEnabled)
	{
		_triangleCount += val;
	}
}

void RenderBus::setMsaaSampleCount(int val)
{
	_msaaSampleCount = val;
}

void RenderBus::setShadowMapSize(int val)
{
	_shadowMapSize = val;
}

void RenderBus::setSceneReflectionMapSize(int val)
{
	_sceneReflectionMapSize = val;
}

void RenderBus::setSceneRefractionMapSize(int val)
{
	_sceneRefractionMapSize = val;
}

void RenderBus::setMsaaEnabled(bool val)
{
	_isMsaaEnabled = val;
}

void RenderBus::setSceneReflectionsEnabled(bool val)
{
	_isSceneReflectionsEnabled = val;
}

void RenderBus::setAmbientLightingEnabled(bool val)
{
	_isAmbientLightingEnabled = val;
}

void RenderBus::setDirectionalLightingEnabled(bool val)
{
	_isDirectionalLightingEnabled = val;
}

void RenderBus::setSpecularLightingEnabled(bool val)
{
	_isSpecularLightingEnabled = val;
}

void RenderBus::setPointLightingEnabled(bool val)
{
	_isPointLightingEnabled = val;
}

void RenderBus::setSpotLightingEnabled(bool val)
{
	_isSpotLightingEnabled = val;
}

void RenderBus::setFogEnabled(bool val)
{
	_isFogEnabled = val;
}

void RenderBus::setLightMappingEnabled(bool val)
{
	_isLightMappingEnabled = val;
}

void RenderBus::setNormalMappingEnabled(bool val)
{
	_isNormalMappingEnabled = val;
}

void RenderBus::setSkyReflectionsEnabled(bool val)
{
	_isSkyReflectionsEnabled = val;
}

void RenderBus::setBloomEnabled(bool val)
{
	_isBloomEnabled = val;
}

void RenderBus::setWaterEffectsEnabled(bool val)
{
	_isWaterEffectsEnabled = val;
}

void RenderBus::setSkyHdrEnabled(bool val)
{
	_isSkyHdrEnabled = val;
}

void RenderBus::setShadowsEnabled(bool val)
{
	_isShadowsEnabled = val;
}

void RenderBus::setDofEnabled(bool val)
{
	_isDofEnabled = val;
}

void RenderBus::setMotionBlurEnabled(bool val)
{
	_isMotionBlurEnabled = val;
}

void RenderBus::setLensFlareEnabled(bool val)
{
	_isLensFlareEnabled = val;
}

void RenderBus::setWireframeRenderingEnabled(bool val)
{
	_isWireframeRenderingEnabled = val;
}

void RenderBus::setAabbFrameRenderingEnabled(bool val)
{
	_isAabbFrameRenderingEnabled = val;
}

void RenderBus::setDebugRenderingEnabled(bool val)
{
	_isDebugRenderingEnabled = val;
}

void RenderBus::setShadowFrameRenderingEnabled(bool val)
{
	_isShadowFrameRenderingEnabled = val;
}

void RenderBus::setTriangleCountingEnabled(bool val)
{
	_isTriangleCountingEnabled = val;
}

void RenderBus::setDofDynamic(bool val)
{
	_isDofDynamic = val;
}

void RenderBus::setCursorEntityID(const string& val)
{
	_cursorEntityID = val;
}

void RenderBus::setLensFlareMapPath(const string& val)
{
	_lensFlareMapPath = val;
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
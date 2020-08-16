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

void RenderBus::setDofDepthMap(GLuint val)
{
	_dofDepthMap = val;
}

void RenderBus::setWaterDepthMap(GLuint val)
{
	_waterDepthMap = val;
}

void RenderBus::setBlurMap(GLuint val)
{
	_blurMap = val;
}

void RenderBus::setPostProcessedSceneMap(GLuint val)
{
	_postProcessedSceneMap = val;
}

void RenderBus::setViewMatrix(const mat4 & val)
{
	_viewMatrix = val;
}

void RenderBus::setProjectionMatrix(const mat4 & val)
{
	_projectionMatrix = val;
}

void RenderBus::setSkyRotationMatrix(const mat4 & val)
{
	_skyRotationMatrix = val;
}

void RenderBus::setShadowMatrix(const mat4 & val)
{
	_shadowMatrix = val;
}

void RenderBus::setCameraPosition(vec3 val)
{
	_cameraPosition = val;
}

void RenderBus::setAmbientLightColor(vec3 val)
{
	_ambientLightingColor = val;
}

void RenderBus::setDirectionalLightPos(vec3 val)
{
	_directionalLightingPosition = val;
}

void RenderBus::setDirectionalLightColor(vec3 val)
{
	_directionalLightingColor = val;
}

void RenderBus::setShadowEyePosition(vec3 val)
{
	_shadowEyePosition = val;
}

void RenderBus::setShadowAreaCenter(vec3 val)
{
	_shadowAreaCenter = val;
}

void RenderBus::setFogColor(vec3 val)
{
	_fogColor = val;
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

void RenderBus::setAmbientLightIntensity(float val)
{
	_ambientLightingIntensity = val;
}

void RenderBus::setDirectionalLightIntensity(float val)
{
	_directionalLightingIntensity = val;
}

void RenderBus::setFogMinDistance(float val)
{
	_fogMinDistance = val;
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

void RenderBus::setDofMinDistance(float val)
{
	_dofMinDistance = val;
}

void RenderBus::setSkyReflectionFactor(float val)
{
	_skyReflectionFactor = val;
}

void RenderBus::setBloomBlurSize(int val)
{
	_bloomBlurSize = val;
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

void RenderBus::setFogEnabled(bool val)
{
	_isFogEnabled = val;
}

void RenderBus::setLightMappingEnabled(bool val)
{
	_isLightMappingEnabled = val;
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

void RenderBus::setCursorEntityID(const string& val)
{
	_cursorEntityID = val;
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

const GLuint RenderBus::getDofDepthMap() const
{
	return _dofDepthMap;
}

const GLuint RenderBus::getWaterDepthMap() const
{
	return _waterDepthMap;
}

const GLuint RenderBus::getBlurMap() const
{
	return _blurMap;
}

const GLuint RenderBus::getPostProcessedSceneMap() const
{
	return _postProcessedSceneMap;
}

const mat4 & RenderBus::getViewMatrix() const
{
	return _viewMatrix;
}

const mat4 & RenderBus::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const mat4 & RenderBus::getSkyRotationMatrix() const
{
	return _skyRotationMatrix;
}

const mat4 & RenderBus::getShadowMatrix() const
{
	return _shadowMatrix;
}

const vec3 RenderBus::getCameraPos() const
{
	return _cameraPosition;
}

const vec3 RenderBus::getAmbientLightingColor() const
{
	return _ambientLightingColor;
}

const vec3 RenderBus::getDirectionalLightingPosition() const
{
	return _directionalLightingPosition;
}

const vec3 RenderBus::getShadowEyePosition() const
{
	return _shadowEyePosition;
}

const vec3 RenderBus::getShadowAreaCenter() const
{
	return _shadowAreaCenter;
}

const vec3 RenderBus::getFogColor() const
{
	return _fogColor;
}

const vec3 RenderBus::getDirectionalLightingColor() const
{
	return _directionalLightingColor;
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

const float RenderBus::getAmbientLightingIntensity() const
{
	return _ambientLightingIntensity;
}

const float RenderBus::getDirectionalLightingIntensity() const
{
	return _directionalLightingIntensity;
}

const float RenderBus::getFogMinDistance() const
{
	return _fogMinDistance;
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

const float RenderBus::getDofMinDistance() const
{
	return _dofMinDistance;
}

const float RenderBus::getSkyReflectionFactor() const
{
	return _skyReflectionFactor;
}

const int RenderBus::getBloomBlurSize() const
{
	return _bloomBlurSize;
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

const bool RenderBus::isFogEnabled() const
{
	return _isFogEnabled;
}

const bool RenderBus::isLightMappingEnabled() const
{
	return _isLightMappingEnabled;
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

const string& RenderBus::getCursorEntityID() const
{
	return _cursorEntityID;
}
#include "shader_bus.hpp"

void ShaderBus::setSkyReflectionCubeMap(GLuint val)
{
	_skyReflectionCubeMap = val;
}

void ShaderBus::setSceneReflectionMap(GLuint val)
{
	_sceneReflectionMap = val;
}

void ShaderBus::setSceneRefractionMap(GLuint val)
{
	_sceneRefractionMap = val;
}

void ShaderBus::setBloomMap(GLuint val)
{
	_bloomMap = val;
}

void ShaderBus::setSceneMap(GLuint val)
{
	_sceneMap = val;
}

void ShaderBus::setShadowMap(GLuint val)
{
	_shadowMap = val;
}

void ShaderBus::setMotionBlurMap(GLuint val)
{
	_motionBlurMap = val;
}

void ShaderBus::setLensFlareMap(GLuint val)
{
	_lensFlareMap = val;
}

void ShaderBus::setDepthMap(GLuint val)
{
	_depthMap = val;
}

void ShaderBus::setBlurMap(GLuint val)
{
	_blurMap = val;
}

void ShaderBus::setPostProcessedSceneMap(GLuint val)
{
	_postProcessedSceneMap = val;
}

void ShaderBus::setViewMatrix(const mat4 & val)
{
	_viewMatrix = val;
}

void ShaderBus::setProjectionMatrix(const mat4 & val)
{
	_projectionMatrix = val;
}

void ShaderBus::setSkyRotationMatrix(const mat4 & val)
{
	_skyRotationMatrix = val;
}

void ShaderBus::setShadowMatrix(const mat4 & val)
{
	_shadowMatrix = val;
}

void ShaderBus::setCameraPosition(vec3 val)
{
	_cameraPosition = val;
}

void ShaderBus::setAmbientLightColor(vec3 val)
{
	_ambientLightingColor = val;
}

void ShaderBus::setDirectionalLightPos(vec3 val)
{
	_directionalLightingPosition = val;
}

void ShaderBus::setDirectionalLightColor(vec3 val)
{
	_directionalLightingColor = val;
}

void ShaderBus::setShadowAreaCenter(vec3 val)
{
	_shadowAreaCenter = val;
}

void ShaderBus::setFogColor(vec3 val)
{
	_fogColor = val;
}

void ShaderBus::setSceneReflectionHeight(float val)
{
	_sceneReflectionHeight = val;
}

void ShaderBus::setSceneReflectionFactor(float val)
{
	_sceneReflectionFactor = val;
}

void ShaderBus::setShadowAreaSize(float val)
{
	_shadowAreaSize = val;
}

void ShaderBus::setLensFlareAlpha(float val)
{
	_lensFlareAlpha = val;
}

void ShaderBus::setAmbientLightIntensity(float val)
{
	_ambientLightingIntensity = val;
}

void ShaderBus::setDirectionalLightIntensity(float val)
{
	_directionalLightingIntensity = val;
}

void ShaderBus::setSpecularLightingIntensity(float val)
{
	_specularLightingIntensity = val;
}

void ShaderBus::setFogMinDistance(float val)
{
	_fogMinDistance = val;
}

void ShaderBus::setBloomIntensity(float val)
{
	_bloomIntensity = val;
}

void ShaderBus::setBloomTreshold(float val)
{
	_bloomTreshold = val;
}

void ShaderBus::setCameraYaw(float val)
{
	_cameraYaw = val;
}

void ShaderBus::setCameraPitch(float val)
{
	_cameraPitch = val;
}

void ShaderBus::setNearZ(float val)
{
	_nearZ = val;
}

void ShaderBus::setFarZ(float val)
{
	_farZ = val;
}

void ShaderBus::setDofMinDistance(float val)
{
	_dofMinDistance = val;
}

void ShaderBus::setSkyReflectionFactor(float val)
{
	_skyReflectionFactor = val;
}

void ShaderBus::setBloomBlurSize(int val)
{
	_bloomBlurSize = val;
}

void ShaderBus::setMsaaEnabled(bool val)
{
	_isMsaaEnabled = val;
}

void ShaderBus::setSceneReflectionsEnabled(bool val)
{
	_isSceneReflectionsEnabled = val;
}

void ShaderBus::setAmbientLightingEnabled(bool val)
{
	_isAmbientLightingEnabled = val;
}

void ShaderBus::setDirectionalLightingEnabled(bool val)
{
	_isDirectionalLightingEnabled = val;
}

void ShaderBus::setSpecularLightingEnabled(bool val)
{
	_isSpecularLightingEnabled = val;
}

void ShaderBus::setPointLightingEnabled(bool val)
{
	_isPointLightingEnabled = val;
}

void ShaderBus::setFogEnabled(bool val)
{
	_isFogEnabled = val;
}

void ShaderBus::setLightMappingEnabled(bool val)
{
	_isLightMappingEnabled = val;
}

void ShaderBus::setSkyReflectionsEnabled(bool val)
{
	_isSkyReflectionsEnabled = val;
}

void ShaderBus::setBloomEnabled(bool val)
{
	_isBloomEnabled = val;
}

void ShaderBus::setWaterEffectsEnabled(bool val)
{
	_isWaterEffectsEnabled = val;
}

void ShaderBus::setSkyHdrEnabled(bool val)
{
	_isSkyHdrEnabled = val;
}

void ShaderBus::setShadowsEnabled(bool val)
{
	_isShadowsEnabled = val;
}

void ShaderBus::setDofEnabled(bool val)
{
	_isDofEnabled = val;
}

void ShaderBus::setMotionBlurEnabled(bool val)
{
	_isMotionBlurEnabled = val;
}

void ShaderBus::setLensFlareEnabled(bool val)
{
	_isLensFlareEnabled = val;
}

void ShaderBus::setWireframeRenderingEnabled(bool val)
{
	_isWireframeRenderingEnabled = val;
}

void ShaderBus::setAabbFrameRenderingEnabled(bool val)
{
	_isAabbFrameRenderingEnabled = val;
}

void ShaderBus::setDebugRenderingEnabled(bool val)
{
	_isDebugRenderingEnabled = val;
}

void ShaderBus::setShadowFrameRenderingEnabled(bool val)
{
	_isShadowFrameRenderingEnabled = val;
}

const GLuint ShaderBus::getSkyReflectionCubeMap() const
{
	return _skyReflectionCubeMap;
}

const GLuint ShaderBus::getSceneReflectionMap() const
{
	return _sceneReflectionMap;
}

const GLuint ShaderBus::getSceneRefractionMap() const
{
	return _sceneRefractionMap;
}

const GLuint ShaderBus::getBloomMap() const
{
	return _bloomMap;
}

const GLuint ShaderBus::getSceneMap() const
{
	return _sceneMap;
}

const GLuint ShaderBus::getShadowMap() const
{
	return _shadowMap;
}

const GLuint ShaderBus::getMotionBlurMap() const
{
	return _motionBlurMap;
}

const GLuint ShaderBus::getLensFlareMap() const
{
	return _lensFlareMap;
}

const GLuint ShaderBus::getDepthMap() const
{
	return _depthMap;
}

const GLuint ShaderBus::getBlurMap() const
{
	return _blurMap;
}

const GLuint ShaderBus::getPostProcessedSceneMap() const
{
	return _postProcessedSceneMap;
}

const mat4 & ShaderBus::getViewMatrix() const
{
	return _viewMatrix;
}

const mat4 & ShaderBus::getProjectionMatrix() const
{
	return _projectionMatrix;
}

const mat4 & ShaderBus::getSkyRotationMatrix() const
{
	return _skyRotationMatrix;
}

const mat4 & ShaderBus::getShadowMatrix() const
{
	return _shadowMatrix;
}

const vec3 ShaderBus::getCameraPos() const
{
	return _cameraPosition;
}

const vec3 ShaderBus::getAmbientLightingColor() const
{
	return _ambientLightingColor;
}

const vec3 ShaderBus::getDirectionalLightingPosition() const
{
	return _directionalLightingPosition;
}

const vec3 ShaderBus::getShadowAreaCenter() const
{
	return _shadowAreaCenter;
}

const vec3 ShaderBus::getFogColor() const
{
	return _fogColor;
}

const vec3 ShaderBus::getDirectionalLightingColor() const
{
	return _directionalLightingColor;
}

const float ShaderBus::getSceneReflectionHeight() const
{
	return _sceneReflectionHeight;
}

const float ShaderBus::getSceneReflectionFactor() const
{
	return _sceneReflectionFactor;
}

const float ShaderBus::getShadowAreaSize() const
{
	return _shadowAreaSize;
}

const float ShaderBus::getLensFlareAlpha() const
{
	return _lensFlareAlpha;
}

const float ShaderBus::getAmbientLightingIntensity() const
{
	return _ambientLightingIntensity;
}

const float ShaderBus::getDirectionalLightingIntensity() const
{
	return _directionalLightingIntensity;
}

const float ShaderBus::getSpecularLightingIntensity() const
{
	return _specularLightingIntensity;
}

const float ShaderBus::getFogMinDistance() const
{
	return _fogMinDistance;
}

const float ShaderBus::getBloomIntensity() const
{
	return _bloomIntensity;
}

const float ShaderBus::getBloomTreshold() const
{
	return _bloomTreshold;
}

const float ShaderBus::getCameraYaw() const
{
	return _cameraYaw;
}

const float ShaderBus::getCameraPitch() const
{
	return _cameraPitch;
}

const float ShaderBus::getNearZ() const
{
	return _nearZ;
}

const float ShaderBus::getFarZ() const
{
	return _farZ;
}

const float ShaderBus::getDofMinDistance() const
{
	return _dofMinDistance;
}

const float ShaderBus::getSkyReflectionFactor() const
{
	return _skyReflectionFactor;
}

const int ShaderBus::getBloomBlurSize() const
{
	return _bloomBlurSize;
}

const bool ShaderBus::isMsaaEnabled() const
{
	return _isMsaaEnabled;
}

const bool ShaderBus::isSceneReflectionsEnabled() const
{
	return _isSceneReflectionsEnabled;
}

const bool ShaderBus::isAmbientLightingEnabled() const
{
	return _isAmbientLightingEnabled;
}

const bool ShaderBus::isDirectionalLightingEnabled() const
{
	return _isDirectionalLightingEnabled;
}

const bool ShaderBus::isSpecularLightingEnabled() const
{
	return _isSpecularLightingEnabled;
}

const bool ShaderBus::isPointLightingEnabled() const
{
	return _isPointLightingEnabled;
}

const bool ShaderBus::isFogEnabled() const
{
	return _isFogEnabled;
}

const bool ShaderBus::isLightMappingEnabled() const
{
	return _isLightMappingEnabled;
}

const bool ShaderBus::isSkyReflectionsEnabled() const
{
	return _isSkyReflectionsEnabled;
}

const bool ShaderBus::isBloomEnabled() const
{
	return _isBloomEnabled;
}

const bool ShaderBus::isWaterEffectsEnabled() const
{
	return _isWaterEffectsEnabled;
}

const bool ShaderBus::isSkyHdrEnabled() const
{
	return _isSkyHdrEnabled;
}

const bool ShaderBus::isShadowsEnabled() const
{
	return _isShadowsEnabled;
}

const bool ShaderBus::isDofEnabled() const
{
	return _isDofEnabled;
}

const bool ShaderBus::isMotionBlurEnabled() const
{
	return _isMotionBlurEnabled;
}

const bool ShaderBus::isLensFlareEnabled() const
{
	return _isLensFlareEnabled;
}

const bool ShaderBus::isWireframeRenderingEnabled() const
{
	return _isWireframeRenderingEnabled;
}

const bool ShaderBus::isAabbFrameRenderingEnabled() const
{
	return _isAabbFrameRenderingEnabled;
}

const bool ShaderBus::isShadowFrameRenderingEnabled() const
{
	return _isShadowFrameRenderingEnabled;
}

const bool ShaderBus::isDebugRenderingEnabled() const
{
	return _isDebugRenderingEnabled;
}
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

void ShaderBus::setDepthMap(GLuint val)
{
	_depthMap = val;
}

void ShaderBus::setBlurMap(GLuint val)
{
	_blurMap = val;
}

void ShaderBus::setBloomedDofSceneMap(GLuint val)
{
	_bloomedDofSceneMap = val;
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

void ShaderBus::setShadowCasterPosition(vec3 val)
{
	_shadowCasterPosition = val;
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

void ShaderBus::setMSAAEnabled(bool val)
{
	_msaaEnabled = val;
}

void ShaderBus::setSceneReflectionsEnabled(bool val)
{
	_sceneReflectionsEnabled = val;
}

void ShaderBus::setAmbientLightingEnabled(bool val)
{
	_ambientLightingEnabled = val;
}

void ShaderBus::setDirectionalLightingEnabled(bool val)
{
	_directionalLightingEnabled = val;
}

void ShaderBus::setSpecularLightingEnabled(bool val)
{
	_specularLightingEnabled = val;
}

void ShaderBus::setPointLightingEnabled(bool val)
{
	_pointLightingEnabled = val;
}

void ShaderBus::setFogEnabled(bool val)
{
	_fogEnabled = val;
}

void ShaderBus::setLightMappingEnabled(bool val)
{
	_lightMappingEnabled = val;
}

void ShaderBus::setSkyReflectionsEnabled(bool val)
{
	_skyReflectionsEnabled = val;
}

void ShaderBus::setBloomEnabled(bool val)
{
	_bloomEnabled = val;
}

void ShaderBus::setWaterEffectsEnabled(bool val)
{
	_waterEffectsEnabled = val;
}

void ShaderBus::setSkyHdrEnabled(bool val)
{
	_skyHdrEnabled = val;
}

void ShaderBus::setShadowsEnabled(bool val)
{
	_shadowsEnabled = val;
}

void ShaderBus::setDofEnabled(bool val)
{
	_dofEnabled = val;
}

void ShaderBus::setMotionBlurEnabled(bool val)
{
	_motionBlurEnabled = val;
}

void ShaderBus::setWireframeEnabled(bool val)
{
	_wireframeEnabled = val;
}

void ShaderBus::setAabbFrameEnabled(bool val)
{
	_aabbFrameEnabled = val;
}

void ShaderBus::setDebugRenderEnabled(bool val)
{
	_debugRenderEnabled = val;
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

const GLuint ShaderBus::getDepthMap() const
{
	return _depthMap;
}

const GLuint ShaderBus::getBlurMap() const
{
	return _blurMap;
}

const GLuint ShaderBus::getBloomedDofSceneMap() const
{
	return _bloomedDofSceneMap;
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

const vec3 ShaderBus::getShadowCasterPosition() const
{
	return _shadowCasterPosition;
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

const bool ShaderBus::isMSAAEnabled() const
{
	return _msaaEnabled;
}

const bool ShaderBus::isSceneReflectionsEnabled() const
{
	return _sceneReflectionsEnabled;
}

const bool ShaderBus::isAmbientLightingEnabled() const
{
	return _ambientLightingEnabled;
}

const bool ShaderBus::isDirectionalLightingEnabled() const
{
	return _directionalLightingEnabled;
}

const bool ShaderBus::isSpecularLightingEnabled() const
{
	return _specularLightingEnabled;
}

const bool ShaderBus::isPointLightingEnabled() const
{
	return _pointLightingEnabled;
}

const bool ShaderBus::isFogEnabled() const
{
	return _fogEnabled;
}

const bool ShaderBus::isLightMappingEnabled() const
{
	return _lightMappingEnabled;
}

const bool ShaderBus::isSkyReflectionsEnabled() const
{
	return _skyReflectionsEnabled;
}

const bool ShaderBus::isBloomEnabled() const
{
	return _bloomEnabled;
}

const bool ShaderBus::isWaterEffectsEnabled() const
{
	return _waterEffectsEnabled;
}

const bool ShaderBus::isSkyHdrEnabled() const
{
	return _skyHdrEnabled;
}

const bool ShaderBus::isShadowsEnabled() const
{
	return _shadowsEnabled;
}

const bool ShaderBus::isDofEnabled() const
{
	return _dofEnabled;
}

const bool ShaderBus::isMotionBlurEnabled() const
{
	return _motionBlurEnabled;
}

const bool ShaderBus::isWireframeEnabled() const
{
	return _wireframeEnabled;
}

const bool ShaderBus::isAabbFrameEnabled() const
{
	return _aabbFrameEnabled;
}

const bool ShaderBus::isDebugRenderEnabled() const
{
	return _debugRenderEnabled;
}
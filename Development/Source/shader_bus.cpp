#include "shader_bus.hpp"

void ShaderBus::setSkyReflectionCubeMapDay(GLuint val)
{
	_skyReflectionCubeMapDay = val;
}

void ShaderBus::setSkyReflectionCubeMapNight(GLuint val)
{
	_skyReflectionCubeMapNight = val;
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

void ShaderBus::setCameraPos(vec3 val)
{
	_cameraPosition = val;
}

void ShaderBus::setDirLightPos(vec3 val)
{
	_dirLightPosition = val;
}

void ShaderBus::setSceneReflectionHeight(float val)
{
	_sceneReflectionHeight = val;
}

void ShaderBus::setSceneReflectionFactor(float val)
{
	_sceneReflectionFactor = val;
}

void ShaderBus::setAmbLightStrength(float val)
{
	_ambientLightingStrength = val;
}

void ShaderBus::setDirLightStrength(float val)
{
	_directionalLightingStrength = val;
}

void ShaderBus::setSpecLightStrength(float val)
{
	_specularLightingStrength = val;
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

void ShaderBus::setSkyBrightness(float val)
{
	_skyBrightness = val;
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

void ShaderBus::setSkyReflectionMixValue(float val)
{
	_skyReflectionMixValue = val;
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

void ShaderBus::setAmbLightEnabled(bool val)
{
	_ambientLightingEnabled = val;
}

void ShaderBus::setDirLightEnabled(bool val)
{
	_directionalLightingEnabled = val;
}

void ShaderBus::setSpecLightEnabled(bool val)
{
	_specularLightingEnabled = val;
}

void ShaderBus::setPointLightEnabled(bool val)
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

const GLuint ShaderBus::getSkyReflectionCubeMapDay() const
{
	return _skyReflectionCubeMapDay;
}

const GLuint ShaderBus::getSceneReflectionCubeMapNight() const
{
	return _skyReflectionCubeMapNight;
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

const vec3 ShaderBus::getDirLightPos() const
{
	return _dirLightPosition;
}

const float ShaderBus::getSceneReflectionHeight() const
{
	return _sceneReflectionHeight;
}

const float ShaderBus::getSceneReflectionFactor() const
{
	return _sceneReflectionFactor;
}

const float ShaderBus::getAmbLightStrength() const
{
	return _ambientLightingStrength;
}

const float ShaderBus::getDirLightStrength() const
{
	return _directionalLightingStrength;
}

const float ShaderBus::getSpecLightStrength() const
{
	return _specularLightingStrength;
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

const float ShaderBus::getSkyBrightness() const
{
	return _skyBrightness;
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

const float ShaderBus::getSkyReflectionMixValue() const
{
	return _skyReflectionMixValue;
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

const bool ShaderBus::isAmbLightingEnabled() const
{
	return _ambientLightingEnabled;
}

const bool ShaderBus::isDirLightingEnabled() const
{
	return _directionalLightingEnabled;
}

const bool ShaderBus::isSpecLightingEnabled() const
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
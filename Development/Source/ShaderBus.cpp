#include <WE3D/ShaderBus.hpp>

void ShaderBus::setDayReflectionCubeMap(GLuint val)
{
	p_dayReflectionCubeMap = val;
}

void ShaderBus::setNightReflectionCubeMap(GLuint val)
{
	p_nightReflectionCubeMap = val;
}

void ShaderBus::setSSRMap(GLuint val)
{
	p_ssrMap = val;
}

void ShaderBus::setWaterRefractionMap(GLuint val)
{
	p_waterRefractionMap = val;
}

void ShaderBus::setBloomMap(GLuint val)
{
	p_bloomMap = val;
}

void ShaderBus::setSceneMap(GLuint val)
{
	p_sceneMap = val;
}

void ShaderBus::setShadowMap(GLuint val)
{
	p_shadowMap = val;
}

void ShaderBus::setMotionBlurMap(GLuint val)
{
	p_motionBlurMap = val;
}

void ShaderBus::setDepthMap(GLuint val)
{
	p_depthMap = val;
}

void ShaderBus::setBlurMap(GLuint val)
{
	p_blurMap = val;
}

void ShaderBus::setBloomedDofSceneMap(GLuint val)
{
	p_bloomedDofSceneMap = val;
}

void ShaderBus::setViewMatrix(const mat4 & val)
{
	p_viewMatrix = val;
}

void ShaderBus::setProjectionMatrix(const mat4 & val)
{
	p_projectionMatrix = val;
}

void ShaderBus::setSkyRotationMatrix(const mat4 & val)
{
	p_skyRotationMatrix = val;
}

void ShaderBus::setShadowMatrix(const mat4 & val)
{
	p_shadowMatrix = val;
}

void ShaderBus::setCameraPos(vec3 val)
{
	p_cameraPosition = val;
}

void ShaderBus::setDirLightPos(vec3 val)
{
	p_dirLightPosition = val;
}

void ShaderBus::setSSRHeight(float val)
{
	p_ssrHeight = val;
}

void ShaderBus::setSSRFactor(float val)
{
	p_ssrFactor = val;
}

void ShaderBus::setAmbLightStrength(float val)
{
	p_ambientLightingStrength = val;
}

void ShaderBus::setDirLightStrength(float val)
{
	p_directionalLightingStrength = val;
}

void ShaderBus::setSpecLightStrength(float val)
{
	p_specularLightingStrength = val;
}

void ShaderBus::setFogMinDistance(float val)
{
	p_fogMinDistance = val;
}

void ShaderBus::setBloomIntensity(float val)
{
	p_bloomIntensity = val;
}

void ShaderBus::setBloomTreshold(float val)
{
	p_bloomTreshold = val;
}

void ShaderBus::setCameraYaw(float val)
{
	p_cameraYaw = val;
}

void ShaderBus::setCameraPitch(float val)
{
	p_cameraPitch = val;
}

void ShaderBus::setSkyBrightness(float val)
{
	p_skyBrightness = val;
}

void ShaderBus::setNearZ(float val)
{
	p_nearZ = val;
}

void ShaderBus::setFarZ(float val)
{
	p_farZ = val;
}

void ShaderBus::setDofMinDistance(float val)
{
	p_dofMinDistance = val;
}

void ShaderBus::setSkyReflectionMixValue(float val)
{
	p_skyReflectionMixValue = val;
}

void ShaderBus::setSkyReflectionFactor(float val)
{
	p_skyReflectionFactor = val;
}

void ShaderBus::setBloomBlurSize(int val)
{
	p_bloomBlurSize = val;
}

void ShaderBus::setMSAAEnabled(bool val)
{
	p_msaaEnabled = val;
}

void ShaderBus::setSSREnabled(bool val)
{
	p_ssrEnabled = val;
}

void ShaderBus::setAmbLightEnabled(bool val)
{
	p_ambientLightingEnabled = val;
}

void ShaderBus::setDirLightEnabled(bool val)
{
	p_directionalLightingEnabled = val;
}

void ShaderBus::setSpecLightEnabled(bool val)
{
	p_specularLightingEnabled = val;
}

void ShaderBus::setPointLightEnabled(bool val)
{
	p_pointLightingEnabled = val;
}

void ShaderBus::setFogEnabled(bool val)
{
	p_fogEnabled = val;
}

void ShaderBus::setLightMappingEnabled(bool val)
{
	p_lightMappingEnabled = val;
}

void ShaderBus::setSkyReflectionsEnabled(bool val)
{
	p_skyReflectionsEnabled = val;
}

void ShaderBus::setBloomEnabled(bool val)
{
	p_bloomEnabled = val;
}

void ShaderBus::setWaterEffectsEnabled(bool val)
{
	p_waterEffectsEnabled = val;
}

void ShaderBus::setSkyHdrEnabled(bool val)
{
	p_skyHdrEnabled = val;
}

void ShaderBus::setShadowsEnabled(bool val)
{
	p_shadowsEnabled = val;
}

void ShaderBus::setDofEnabled(bool val)
{
	p_dofEnabled = val;
}

void ShaderBus::setMotionBlurEnabled(bool val)
{
	p_motionBlurEnabled = val;
}

void ShaderBus::setWireframeEnabled(bool val)
{
	p_wireframeEnabled = val;
}

void ShaderBus::setAabbFrameEnabled(bool val)
{
	p_aabbFrameEnabled = val;
}

void ShaderBus::setDebugRenderEnabled(bool val)
{
	p_debugRenderEnabled = val;
}

const GLuint ShaderBus::getDayReflectionCubeMap() const
{
	return p_dayReflectionCubeMap;
}

const GLuint ShaderBus::getNightReflectionCubeMap() const
{
	return p_nightReflectionCubeMap;
}

const GLuint ShaderBus::getSSRMap() const
{
	return p_ssrMap;
}

const GLuint ShaderBus::getWaterRefractionMap() const
{
	return p_waterRefractionMap;
}

const GLuint ShaderBus::getBloomMap() const
{
	return p_bloomMap;
}

const GLuint ShaderBus::getSceneMap() const
{
	return p_sceneMap;
}

const GLuint ShaderBus::getShadowMap() const
{
	return p_shadowMap;
}

const GLuint ShaderBus::getMotionBlurMap() const
{
	return p_motionBlurMap;
}

const GLuint ShaderBus::getDepthMap() const
{
	return p_depthMap;
}

const GLuint ShaderBus::getBlurMap() const
{
	return p_blurMap;
}

const GLuint ShaderBus::getBloomedDofSceneMap() const
{
	return p_bloomedDofSceneMap;
}

const mat4 & ShaderBus::getViewMatrix() const
{
	return p_viewMatrix;
}

const mat4 & ShaderBus::getProjectionMatrix() const
{
	return p_projectionMatrix;
}

const mat4 & ShaderBus::getSkyRotationMatrix() const
{
	return p_skyRotationMatrix;
}

const mat4 & ShaderBus::getShadowMatrix() const
{
	return p_shadowMatrix;
}

const vec3 ShaderBus::getCameraPos() const
{
	return p_cameraPosition;
}

const vec3 ShaderBus::getDirLightPos() const
{
	return p_dirLightPosition;
}

const float ShaderBus::getSSRHeight() const
{
	return p_ssrHeight;
}

const float ShaderBus::getSSRFactor() const
{
	return p_ssrFactor;
}

const float ShaderBus::getAmbLightStrength() const
{
	return p_ambientLightingStrength;
}

const float ShaderBus::getDirLightStrength() const
{
	return p_directionalLightingStrength;
}

const float ShaderBus::getSpecLightStrength() const
{
	return p_specularLightingStrength;
}

const float ShaderBus::getFogMinDistance() const
{
	return p_fogMinDistance;
}

const float ShaderBus::getBloomIntensity() const
{
	return p_bloomIntensity;
}

const float ShaderBus::getBloomTreshold() const
{
	return p_bloomTreshold;
}

const float ShaderBus::getCameraYaw() const
{
	return p_cameraYaw;
}

const float ShaderBus::getCameraPitch() const
{
	return p_cameraPitch;
}

const float ShaderBus::getSkyBrightness() const
{
	return p_skyBrightness;
}

const float ShaderBus::getNearZ() const
{
	return p_nearZ;
}

const float ShaderBus::getFarZ() const
{
	return p_farZ;
}

const float ShaderBus::getDofMinDistance() const
{
	return p_dofMinDistance;
}

const float ShaderBus::getSkyReflectionMixValue() const
{
	return p_skyReflectionMixValue;
}

const float ShaderBus::getSkyReflectionFactor() const
{
	return p_skyReflectionFactor;
}

const int ShaderBus::getBloomBlurSize() const
{
	return p_bloomBlurSize;
}

const bool ShaderBus::isMSAAEnabled() const
{
	return p_msaaEnabled;
}

const bool ShaderBus::isSSREnabled() const
{
	return p_ssrEnabled;
}

const bool ShaderBus::isAmbLightingEnabled() const
{
	return p_ambientLightingEnabled;
}

const bool ShaderBus::isDirLightingEnabled() const
{
	return p_directionalLightingEnabled;
}

const bool ShaderBus::isSpecLightingEnabled() const
{
	return p_specularLightingEnabled;
}

const bool ShaderBus::isPointLightingEnabled() const
{
	return p_pointLightingEnabled;
}

const bool ShaderBus::isFogEnabled() const
{
	return p_fogEnabled;
}

const bool ShaderBus::isLightMappingEnabled() const
{
	return p_lightMappingEnabled;
}

const bool ShaderBus::isSkyReflectionsEnabled() const
{
	return p_skyReflectionsEnabled;
}

const bool ShaderBus::isBloomEnabled() const
{
	return p_bloomEnabled;
}

const bool ShaderBus::isWaterEffectsEnabled() const
{
	return p_waterEffectsEnabled;
}

const bool ShaderBus::isSkyHdrEnabled() const
{
	return p_skyHdrEnabled;
}

const bool ShaderBus::isShadowsEnabled() const
{
	return p_shadowsEnabled;
}

const bool ShaderBus::isDofEnabled() const
{
	return p_dofEnabled;
}

const bool ShaderBus::isMotionBlurEnabled() const
{
	return p_motionBlurEnabled;
}

const bool ShaderBus::isWireframeEnabled() const
{
	return p_wireframeEnabled;
}

const bool ShaderBus::isAabbFrameEnabled() const
{
	return p_aabbFrameEnabled;
}

const bool ShaderBus::isDebugRenderEnabled() const
{
	return p_debugRenderEnabled;
}
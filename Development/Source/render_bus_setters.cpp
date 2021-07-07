#include "render_bus.hpp"

#include <algorithm>

void RenderBus::setMainSkyReflectionCubeMap(GLuint value)
{
	_mainSkyReflectionCubeMap = value;
}

void RenderBus::setMixSkyReflectionCubeMap(GLuint value)
{
	_mixSkyReflectionCubeMap = value;
}

void RenderBus::setSceneReflectionMap(GLuint value)
{
	_sceneReflectionMap = value;
}

void RenderBus::setWaterReflectionMap(GLuint value)
{
	_waterReflectionMap = value;
}

void RenderBus::setWaterRefractionMap(GLuint value)
{
	_waterRefractionMap = value;
}

void RenderBus::setBloomMap(GLuint value)
{
	_bloomMap = value;
}

void RenderBus::setPrimarySceneMap(GLuint value)
{
	_primarySceneMap = value;
}

void RenderBus::setSecondarySceneMap(GLuint value)
{
	_secondarySceneMap = value;
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

void RenderBus::setClippingPlane(Vec4 value)
{
	_clippingPlane = value;
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
	_ambientLightColor = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setDirectionalLightPosition(Vec3 value)
{
	_directionalLightPosition = value;
}

void RenderBus::setDirectionalLightColor(Vec3 value)
{
	_directionalLightColor = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setSpotLightColor(Vec3 value)
{
	_spotLightColor = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
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
	_fogColor = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setFlareSourcePosition(Vec3 value)
{
	_flareSourcePosition = value;
}

void RenderBus::setMainSkyColor(Vec3 value)
{
	_mainSkyColor = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setMixSkyColor(Vec3 value)
{
	_mixSkyColor = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setSceneReflectionHeight(float value)
{
	_sceneReflectionHeight = value;
}

void RenderBus::setSceneReflectionMixValue(float value)
{
	_sceneReflectionMixValue = std::clamp(value, 0.0f, 1.0f);
}

void RenderBus::setShadowAreaSize(float value)
{
	_shadowAreaSize = std::max(0.0f, value);
}

void RenderBus::setShadowAreaReach(float value)
{
	_shadowAreaReach = std::max(0.0f, value);
}

void RenderBus::setShadowLightness(float value)
{
	_shadowLightness = std::max(0.0f, value);
}

void RenderBus::setLensFlareAlpha(float value)
{
	_lensFlareAlpha = std::max(0.0f, value);
}

void RenderBus::setLensFlareIntensity(float value)
{
	_lensFlareIntensity = std::max(0.0f, value);
}

void RenderBus::setLensFlareMultiplier(float value)
{
	_lensFlareMultiplier = std::max(0.0f, value);
}

void RenderBus::setMotionBlurStrength(float value)
{
	_motionBlurStrength = std::max(0.0f, value);
}

void RenderBus::setMotionBlurMixValue(float value)
{
	_motionBlurMixValue = std::clamp(value, 0.0f, 1.0f);
}

void RenderBus::setMainSkyLightness(float value)
{
	_mainSkyLightness = std::max(0.0f, value);
}

void RenderBus::setMixSkyLightness(float value)
{
	_mixSkyLightness = std::max(0.0f, value);
}

void RenderBus::setSkyMixValue(float value)
{
	_skyMixValue = std::clamp(value, 0.0f, 1.0f);
}

void RenderBus::setMaxSpotLightAngle(float value)
{
	_maxSpotLightAngle = std::fmodf(value, 360.0f);
}

void RenderBus::setMaxSpotLightDistance(float value)
{
	_maxSpotLightDistance = std::max(0.0f, value);
}

void RenderBus::setAmbientLightIntensity(float value)
{
	_ambientLightIntensity = std::max(0.0f, value);
}

void RenderBus::setDirectionalLightIntensity(float value)
{
	_directionalLightIntensity = std::max(0.0f, value);
}

void RenderBus::setSpotLightIntensity(float value)
{
	_spotLightIntensity = std::max(0.0f, value);
}

void RenderBus::setFogMinDistance(float value)
{
	_fogMinDistance = std::max(0.0f, value);
}

void RenderBus::setFogMaxDistance(float value)
{
	_fogMaxDistance = std::max(0.0f, value);
}

void RenderBus::setFogThickness(float value)
{
	_fogThickness = std::clamp(value, 0.0f, 1.0f);
}

void RenderBus::setBloomIntensity(float value)
{
	_bloomIntensity = std::max(0.0f, value);
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
	_nearZ = std::max(0.0f, value);
}

void RenderBus::setFarZ(float value)
{
	_farZ = value;
}

void RenderBus::setDofMaxDistance(float value)
{
	_dofMaxDistance = std::max(0.0f, value);
}

void RenderBus::setDofBlurDistance(float value)
{
	_dofBlurDistance = std::max(0.0f, value);
}

void RenderBus::setSkyReflectionMixValue(float value)
{
	_skyReflectionMixValue = std::clamp(value, 0.0f, 1.0f);
}

void RenderBus::setBloomBlurCount(unsigned int value)
{
	_bloomBlurCount = value;
}


void RenderBus::increaseTriangleCount(unsigned int value)
{
	if (_isTriangleCountingEnabled)
	{
		_triangleCount += value;
	}
}

void RenderBus::setShadowMapSize(unsigned int value)
{
	_shadowMapSize = value;
}

void RenderBus::setReflectionMapSize(unsigned int value)
{
	_reflectionMapSize = value;
}

void RenderBus::setRefractionMapSize(unsigned int value)
{
	_refractionMapSize = value;
}

void RenderBus::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderBus::setFxaaEnabled(bool value)
{
	_isFxaaEnabled = value;
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

void RenderBus::setSkyExposureEnabled(bool value)
{
	_isSkyExposureEnabled = value;
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

void RenderBus::setLightedShadowingEnabled(bool value)
{
	_isLightedShadowingEnabled = value;
}

void RenderBus::setTriangleCountingEnabled(bool value)
{
	_isTriangleCountingEnabled = value;
}

void RenderBus::setDofDynamic(bool value)
{
	_isDofDynamic = value;
}

void RenderBus::setBloomType(BloomType value)
{
	_bloomType = value;
}

void RenderBus::setCursorEntityID(const string& value)
{
	_cursorEntityID = value;
}

void RenderBus::setLensFlareMapPath(const string& value)
{
	_lensFlareMapPath = value;
}
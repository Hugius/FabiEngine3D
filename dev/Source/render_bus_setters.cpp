#include "render_bus.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void RenderBus::setPlanarReflectionMap(TextureID value)
{
	_planarReflectionMap = value;
}

void RenderBus::setWaterReflectionMap(TextureID value)
{
	_waterReflectionMap = value;
}

void RenderBus::setWaterRefractionMap(TextureID value)
{
	_waterRefractionMap = value;
}

void RenderBus::setBloomMap(TextureID value)
{
	_bloomMap = value;
}

void RenderBus::setPrimarySceneMap(TextureID value)
{
	_primarySceneMap = value;
}

void RenderBus::setSecondarySceneMap(TextureID value)
{
	_secondarySceneMap = value;
}

void RenderBus::setShadowMap(TextureID value)
{
	_shadowMap = value;
}

void RenderBus::setMotionBlurMap(TextureID value)
{
	_motionBlurMap = value;
}

void RenderBus::setLensFlareMap(TextureID value)
{
	_lensFlareMap = value;
}

void RenderBus::setDepthMap(TextureID value)
{
	_depthMap = value;
}

void RenderBus::setDofMap(TextureID value)
{
	_dofMap = value;
}

void RenderBus::setFinalSceneMap(TextureID value)
{
	_finalSceneMap = value;
}

void RenderBus::setViewMatrix(const Matrix44 value)
{
	_viewMatrix = value;
}

void RenderBus::setProjectionMatrix(const Matrix44 value)
{
	_projectionMatrix = value;
}

void RenderBus::setShadowMatrix(const Matrix44 value)
{
	_shadowMatrix = value;
}

void RenderBus::setFlareSourceUV(Vec2 value)
{
	_flareSourceUV = value;
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

void RenderBus::setAmbientLightingColor(Vec3 value)
{
	_ambientLightColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setDirectionalLightingPosition(Vec3 value)
{
	_directionalLightPosition = value;
}

void RenderBus::setDirectionalLightingColor(Vec3 value)
{
	_directionalLightColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setShadowEyePosition(Vec3 value)
{
	_shadowEyePosition = value;
}

void RenderBus::setShadowCenterPosition(Vec3 value)
{
	_shadowCenterPosition = value;
}

void RenderBus::setFogColor(Vec3 value)
{
	_fogColor = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void RenderBus::setFlareSourcePosition(Vec3 value)
{
	_flareSourcePosition = value;
}

void RenderBus::setPlanarReflectionHeight(float value)
{
	_planarReflectionHeight = value;
}

void RenderBus::setShadowAreaSize(float value)
{
	_shadowAreaSize = max(0.0f, value);
}

void RenderBus::setShadowAreaReach(float value)
{
	_shadowAreaReach = max(0.0f, value);
}

void RenderBus::setShadowLightness(float value)
{
	_shadowLightness = max(0.0f, value);
}

void RenderBus::setLensFlareAlpha(float value)
{
	_lensFlareAlpha = max(0.0f, value);
}

void RenderBus::setLensFlareIntensity(float value)
{
	_lensFlareIntensity = max(0.0f, value);
}

void RenderBus::setLensFlareSensitivity(float value)
{
	_lensFlareSensitivity = max(0.0f, value);
}

void RenderBus::setMotionBlurStrength(float value)
{
	_motionBlurStrength = max(0.0f, value);
}

void RenderBus::setMotionBlurMixValue(float value)
{
	_motionBlurMixValue = clamp(value, 0.0f, 1.0f);
}

void RenderBus::setSkyMixValue(float value)
{
	_skyMixValue = value;
}

void RenderBus::setBloomSize(unsigned int value)
{
	_bloomSize = clamp(value, Config::MIN_BLOOM_SIZE, Config::MAX_BLOOM_SIZE);
}

void RenderBus::setDofSize(unsigned int value)
{
	_dofSize = clamp(value, Config::MIN_DOF_SIZE, Config::MAX_DOF_SIZE);
}

void RenderBus::setMotionBlurSize(unsigned int value)
{
	_motionBlurSize = clamp(value, Config::MIN_MOTION_BLUR_SIZE, Config::MAX_MOTION_BLUR_SIZE);
}

void RenderBus::setAmbientLightingIntensity(float value)
{
	_ambientLightIntensity = max(0.0f, value);
}

void RenderBus::setDirectionalLightingIntensity(float value)
{
	_directionalLightIntensity = max(0.0f, value);
}

void RenderBus::setFogMinDistance(float value)
{
	_fogMinDistance = max(0.0f, value);
}

void RenderBus::setFogMaxDistance(float value)
{
	_fogMaxDistance = max(0.0f, value);
}

void RenderBus::setFogThickness(float value)
{
	_fogThickness = clamp(value, 0.0f, 1.0f);
}

void RenderBus::setBloomIntensity(float value)
{
	_bloomIntensity = max(0.0f, value);
}

void RenderBus::setCameraYaw(float value)
{
	_cameraYaw = value;
}

void RenderBus::setCameraPitch(float value)
{
	_cameraPitch = value;
}

void RenderBus::setNearDistance(float value)
{
	_nearDistance = max(0.0f, value);
}

void RenderBus::setFarDistance(float value)
{
	_farDistance = value;
}

void RenderBus::setDofMaxDistance(float value)
{
	_dofMaxDistance = max(0.0f, value);
}

void RenderBus::setDofBlurDistance(float value)
{
	_dofBlurDistance = max(0.0f, value);
}

void RenderBus::setBloomBlurCount(unsigned int value)
{
	_bloomBlurCount = value;
}

void RenderBus::increaseTriangleCount(unsigned int value)
{
	if(_isTriangleCountingEnabled)
	{
		_triangleCount += value;
	}
}

void RenderBus::setShadowQuality(unsigned int value)
{
	_shadowQuality = clamp(value, Config::MIN_SHADOW_QUALITY, Config::MAX_SHADOW_QUALITY);
}

void RenderBus::setCubeReflectionQuality(unsigned int value)
{
	_cubeReflectionQuality = clamp(value, Config::MIN_REFLECTION_QUALITY, Config::MAX_REFLECTION_QUALITY);
}

void RenderBus::setPlanarReflectionQuality(unsigned int value)
{
	_planarReflectionQuality = clamp(value, Config::MIN_REFLECTION_QUALITY, Config::MAX_REFLECTION_QUALITY);
}

void RenderBus::setRefractionQuality(unsigned int value)
{
	_refractionQuality = clamp(value, Config::MIN_REFRACTION_QUALITY, Config::MAX_REFRACTION_QUALITY);
}

void RenderBus::resetTriangleCount()
{
	_triangleCount = 0;
}

void RenderBus::setAntiAliasingEnabled(bool value)
{
	_isAntiAliasingEnabled = value;
}

void RenderBus::setAmbientLightingEnabled(bool value)
{
	_isAmbientLightingEnabled = value;
}

void RenderBus::setDirectionalLightingEnabled(bool value)
{
	_isDirectionalLightingEnabled = value;
}

void RenderBus::setReflectionsEnabled(bool value)
{
	_isReflectionsEnabled = value;
}

void RenderBus::setFogEnabled(bool value)
{
	_isFogEnabled = value;
}

void RenderBus::setBloomEnabled(bool value)
{
	_isBloomEnabled = value;
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

void RenderBus::setWireFrameRenderingEnabled(bool value)
{
	_isWireFrameRenderingEnabled = value;
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
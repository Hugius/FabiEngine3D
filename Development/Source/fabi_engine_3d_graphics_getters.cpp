#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::gfx_isFxaaEnabled()
{
	return _core->_renderBus.isFxaaEnabled();
}

const bool FabiEngine3D::gfx_isAmbientLightingEnabled()
{
	return _core->_renderBus.isAmbientLightingEnabled();
}

const bool FabiEngine3D::gfx_isDirectionalLightingEnabled()
{
	return _core->_renderBus.isDirectionalLightingEnabled();
}

const bool FabiEngine3D::gfx_isSpecularLightingEnabled()
{
	return _core->_renderBus.isSpecularLightingEnabled();
}

const bool FabiEngine3D::gfx_isPointLightingEnabled()
{
	return _core->_renderBus.isPointLightingEnabled();
}

const bool FabiEngine3D::gfx_isSpotLightingEnabled()
{
	return _core->_renderBus.isSpotLightingEnabled();
}

const bool FabiEngine3D::gfx_isFogEnabled()
{
	return _core->_renderBus.isFogEnabled();
}

const bool FabiEngine3D::gfx_isLightMappingEnabled()
{
	return _core->_renderBus.isLightMappingEnabled();
}

const bool FabiEngine3D::gfx_isNormalMappingEnabled()
{
	return _core->_renderBus.isNormalMappingEnabled();
}

const bool FabiEngine3D::gfx_isSkyReflectionsEnabled()
{
	return _core->_renderBus.isSkyReflectionsEnabled();
}

const bool FabiEngine3D::gfx_isSceneReflectionsEnabled()
{
	return _core->_renderBus.isSceneReflectionsEnabled();
}

const bool FabiEngine3D::gfx_isBloomEnabled()
{
	return _core->_renderBus.isBloomEnabled();
}

const bool FabiEngine3D::gfx_isSkyHdrEnabled()
{
	return _core->_renderBus.isSkyHdrEnabled();
}

const bool FabiEngine3D::gfx_isShadowsEnabled()
{
	return _core->_renderBus.isShadowsEnabled();
}

const bool FabiEngine3D::gfx_isDofEnabled()
{
	return _core->_renderBus.isDofEnabled();
}

const bool FabiEngine3D::gfx_isDofDynamic()
{
	return _core->_renderBus.isDofDynamic();
}

const bool FabiEngine3D::gfx_isMotionBlurEnabled()
{
	return _core->_renderBus.isMotionBlurEnabled();
}

const bool FabiEngine3D::gfx_isLensFlareEnabled()
{
	return _core->_renderBus.isLensFlareEnabled();
}

const unsigned int FabiEngine3D::gfx_getShadowQuality()
{
	return _core->_renderBus.getShadowMapSize();
}

const unsigned int FabiEngine3D::gfx_getReflectionQuality()
{
	return _core->_renderBus.getReflectionMapSize();
}

const unsigned int FabiEngine3D::gfx_getRefractionQuality()
{
	return _core->_renderBus.getRefractionMapSize();
}

const Vec3 FabiEngine3D::gfx_getAmbientLightingColor()
{
	return _core->_renderBus.getAmbientLightColor();
}

const float FabiEngine3D::gfx_getAmbientLightingIntensity()
{
	return _core->_renderBus.getAmbientLightIntensity();
}

const float FabiEngine3D::gfx_getDirectionalLightingIntensity()
{
	return _core->_renderBus.getDirectionalLightIntensity();
}

const float FabiEngine3D::gfx_getSpotLightingIntensity()
{
	return _core->_renderBus.getSpotLightIntensity();
}

const float FabiEngine3D::gfx_getSpotLightingAngle()
{
	return _core->_renderBus.getMaxSpotLightAngle();
}

const float FabiEngine3D::gfx_getSpotLightingDistance()
{
	return _core->_renderBus.getMaxSpotLightDistance();
}

const Vec3 FabiEngine3D::gfx_getDirectionalLightingPosition()
{
	return _core->_renderBus.getDirectionalLightPosition();
}

const Vec3 FabiEngine3D::gfx_getDirectionalLightingColor()
{
	return _core->_renderBus.getDirectionalLightColor();
}

const Vec3 FabiEngine3D::gfx_getSpotLightingColor()
{
	return _core->_renderBus.getSpotLightColor();
}

const float FabiEngine3D::gfx_getFogMinDistance()
{
	return _core->_renderBus.getFogMinDistance();
}

const float FabiEngine3D::gfx_getFogMaxDistance()
{
	return _core->_renderBus.getFogMaxDistance();
}

const float FabiEngine3D::gfx_getFogThickness()
{
	return _core->_renderBus.getFogThickness();
}

const Vec3 FabiEngine3D::gfx_getFogColor()
{
	return _core->_renderBus.getFogColor();
}

const float FabiEngine3D::gfx_getSkyReflectionFactor()
{
	return _core->_renderBus.getSkyReflectionMixValue();
}

const float FabiEngine3D::gfx_getSceneReflectionHeight()
{
	return _core->_renderBus.getSceneReflectionHeight();
}

const float FabiEngine3D::gfx_getSceneReflectionFactor()
{
	return _core->_renderBus.getSceneReflectionMixValue();
}

const Vec3 FabiEngine3D::gfx_getShadowEye()
{
	return _core->_shadowGenerator.getEye();
}

const Vec3 FabiEngine3D::gfx_getShadowCenter()
{
	return _core->_shadowGenerator.getCenter();
}

const string& FabiEngine3D::gfx_getLensFlareMapPath()
{
	return _core->_renderBus.getLensFlareMapPath();
}

const float FabiEngine3D::gfx_getShadowSize()
{
	return _core->_shadowGenerator.getSize();
}

const float FabiEngine3D::gfx_getShadowReach()
{
	return _core->_shadowGenerator.getReach();
}

const float FabiEngine3D::gfx_getShadowLightness()
{
	return _core->_renderBus.getShadowLightness();
}

const bool FabiEngine3D::gfx_isShadowFollowingCamera()
{
	return _core->_shadowGenerator.isFollowingCamera();
}

const bool FabiEngine3D::gfx_isLightedShadowingEnabled()
{
	return _core->_renderBus.isLightedShadowingEnabled();
}

const float FabiEngine3D::gfx_getBloomIntensity()
{
	return _core->_renderBus.getBloomIntensity();
}

const unsigned int FabiEngine3D::gfx_getBloomBlurSize()
{
	return _core->_renderBus.getBloomBlurSize();
}

const unsigned int FabiEngine3D::gfx_getShadowInterval()
{
	return _core->_shadowGenerator.getInterval();
}

const float FabiEngine3D::gfx_getSkyHdrBrightnessFactor()
{
	return _core->_skyEntityManager.getBrightnessFactor();
}

const float FabiEngine3D::gfx_getaMaxDofDistance()
{
	return _core->_renderBus.getDofMaxDistance();
}

const float FabiEngine3D::gfx_getDofBlurDistance()
{
	return _core->_renderBus.getDofBlurDistance();
}

const float FabiEngine3D::gfx_getLensFlareIntensity()
{
	return _core->_renderBus.getLensFlareIntensity();
}

const float FabiEngine3D::gfx_getLensFlareMultiplier()
{
	return _core->_renderBus.getLensFlareMultiplier();
}

const float FabiEngine3D::gfx_getMotionBlurStrength()
{
	return _core->_renderBus.getMotionBlurStrength();
}
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::gfx_isAntiAliasingEnabled()
{
	return _core->_renderBus.isAntiAliasingEnabled();
}

const bool FabiEngine3D::gfx_isAmbientLightingEnabled()
{
	return _core->_renderBus.isAmbientLightingEnabled();
}

const bool FabiEngine3D::gfx_isDirectionalLightingEnabled()
{
	return _core->_renderBus.isDirectionalLightingEnabled();
}

const bool FabiEngine3D::gfx_isSpotLightingEnabled()
{
	return _core->_renderBus.isSpotLightingEnabled();
}

const bool FabiEngine3D::gfx_isFogEnabled()
{
	return _core->_renderBus.isFogEnabled();
}

const bool FabiEngine3D::gfx_isBloomEnabled()
{
	return _core->_renderBus.isBloomEnabled();
}

const bool FabiEngine3D::gfx_isSkyExposureEnabled()
{
	return _core->_skyEntityManager.isExposureEnabled();
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
	return _core->_renderBus.getShadowQuality();
}

const unsigned int FabiEngine3D::gfx_getCubeReflectionQuality()
{
	return _core->_renderBus.getCubeReflectionQuality();
}

const unsigned int FabiEngine3D::gfx_getPlanarReflectionQuality()
{
	return _core->_renderBus.getPlanarReflectionQuality();
}

const unsigned int FabiEngine3D::gfx_getRefractionQuality()
{
	return _core->_renderBus.getRefractionQuality();
}

const Vec3 FabiEngine3D::gfx_getAmbientLightingColor()
{
	return _core->_renderBus.getAmbientLightingColor();
}

const float FabiEngine3D::gfx_getAmbientLightingIntensity()
{
	return _core->_renderBus.getAmbientLightingIntensity();
}

const float FabiEngine3D::gfx_getDirectionalLightingIntensity()
{
	return _core->_renderBus.getDirectionalLightingIntensity();
}

const float FabiEngine3D::gfx_getSpotLightingIntensity()
{
	return _core->_renderBus.getSpotLightingIntensity();
}

const float FabiEngine3D::gfx_getSpotLightingAngle()
{
	return _core->_renderBus.getMaxSpotLightingAngle();
}

const float FabiEngine3D::gfx_getSpotLightingDistance()
{
	return _core->_renderBus.getMaxSpotLightingDistance();
}

const Vec3 FabiEngine3D::gfx_getDirectionalLightingPosition()
{
	return _core->_renderBus.getDirectionalLightingPosition();
}

const Vec3 FabiEngine3D::gfx_getDirectionalLightingColor()
{
	return _core->_renderBus.getDirectionalLightingColor();
}

const Vec3 FabiEngine3D::gfx_getSpotLightingColor()
{
	return _core->_renderBus.getSpotLightingColor();
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

const float FabiEngine3D::gfx_getPlanarReflectionHeight()
{
	return _core->_renderBus.getPlanarReflectionHeight();
}

const Vec3 FabiEngine3D::gfx_getShadowEye()
{
	return _core->_renderBus.getShadowEyePosition();
}

const Vec3 FabiEngine3D::gfx_getShadowCenter()
{
	return _core->_renderBus.getShadowCenterPosition();
}

const string& FabiEngine3D::gfx_getLensFlareMapPath()
{
	return _core->_renderBus.getLensFlareMapPath();
}

const float FabiEngine3D::gfx_getShadowSize()
{
	return _core->_renderBus.getShadowAreaSize();
}

const float FabiEngine3D::gfx_getShadowReach()
{
	return _core->_renderBus.getShadowAreaReach();
}

const float FabiEngine3D::gfx_getShadowLightness()
{
	return _core->_renderBus.getShadowLightness();
}

const bool FabiEngine3D::gfx_isShadowFollowingCamera()
{
	return _core->_shadowGenerator.isFollowingCamera();
}

const float FabiEngine3D::gfx_getBloomIntensity()
{
	return _core->_renderBus.getBloomIntensity();
}

const unsigned int FabiEngine3D::gfx_getBloomBlurCount()
{
	return _core->_renderBus.getBloomBlurCount();
}

const unsigned int FabiEngine3D::gfx_getShadowInterval()
{
	return _core->_shadowGenerator.getInterval();
}

const float FabiEngine3D::gfx_getSkyExposureIntensity()
{
	return _core->_skyEntityManager.getExposureIntensity();
}

const float FabiEngine3D::gfx_getSkyExposureSpeed()
{
	return _core->_skyEntityManager.getExposureSpeed();
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

const float FabiEngine3D::gfx_getLensFlareSensitivity()
{
	return _core->_renderBus.getLensFlareSensitivity();
}

const float FabiEngine3D::gfx_getMotionBlurStrength()
{
	return _core->_renderBus.getMotionBlurStrength();
}

const unsigned int FabiEngine3D::gfx_getBloomSize()
{
	return _core->_renderBus.getBloomSize();
}

const unsigned int FabiEngine3D::gfx_getDofSize()
{
	return _core->_renderBus.getDofSize();
}

const unsigned int FabiEngine3D::gfx_getMotionBlurSize()
{
	return _core->_renderBus.getMotionBlurSize();
}

const BloomType FabiEngine3D::gfx_getBloomType()
{
	return _core->_renderBus.getBloomType();
}

const unsigned int FabiEngine3D::gfx_getAnisotropicFilteringQuality()
{
	return _core->_textureLoader.getAnisotropicFilteringQuality();
}
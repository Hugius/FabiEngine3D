#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::gfx_isAntiAliasingEnabled() const
{
	return _core->getRenderBus()->isAntiAliasingEnabled();
}

const bool EngineInterface::gfx_isAmbientLightingEnabled() const
{
	return _core->getRenderBus()->isAmbientLightingEnabled();
}

const bool EngineInterface::gfx_isDirectionalLightingEnabled() const
{
	return _core->getRenderBus()->isDirectionalLightingEnabled();
}

const bool EngineInterface::gfx_isFogEnabled() const
{
	return _core->getRenderBus()->isFogEnabled();
}

const bool EngineInterface::gfx_isBloomEnabled() const
{
	return _core->getRenderBus()->isBloomEnabled();
}

const bool EngineInterface::gfx_isSkyExposureEnabled() const
{
	return _core->getSkyEntityManager()->isExposureEnabled();
}

const bool EngineInterface::gfx_isShadowsEnabled() const
{
	return _core->getShadowGenerator()->isEnabled();
}

const bool EngineInterface::gfx_isDofEnabled() const
{
	return _core->getRenderBus()->isDofEnabled();
}

const bool EngineInterface::gfx_isDofDynamic() const
{
	return _core->getRenderBus()->isDofDynamic();
}

const bool EngineInterface::gfx_isMotionBlurEnabled() const
{
	return _core->getRenderBus()->isMotionBlurEnabled();
}

const bool EngineInterface::gfx_isLensFlareEnabled() const
{
	return _core->getRenderBus()->isLensFlareEnabled();
}

const unsigned int EngineInterface::gfx_getShadowQuality() const
{
	return _core->getShadowGenerator()->getQuality();
}

const unsigned int EngineInterface::gfx_getCubeReflectionQuality() const
{
	return _core->getRenderBus()->getCubeReflectionQuality();
}

const unsigned int EngineInterface::gfx_getPlanarReflectionQuality() const
{
	return _core->getRenderBus()->getPlanarReflectionQuality();
}

const unsigned int EngineInterface::gfx_getPlanarRefractionQuality() const
{
	return _core->getRenderBus()->getPlanarRefractionQuality();
}

const fvec3 EngineInterface::gfx_getAmbientLightingColor() const
{
	return _core->getRenderBus()->getAmbientLightingColor();
}

const float EngineInterface::gfx_getAmbientLightingIntensity() const
{
	return _core->getRenderBus()->getAmbientLightingIntensity();
}

const float EngineInterface::gfx_getDirectionalLightingIntensity() const
{
	return _core->getRenderBus()->getDirectionalLightingIntensity();
}

const fvec3 EngineInterface::gfx_getDirectionalLightingPosition() const
{
	return _core->getRenderBus()->getDirectionalLightingPosition();
}

const fvec3 EngineInterface::gfx_getDirectionalLightingColor() const
{
	return _core->getRenderBus()->getDirectionalLightingColor();
}

const float EngineInterface::gfx_getFogMinDistance() const
{
	return _core->getRenderBus()->getFogMinDistance();
}

const float EngineInterface::gfx_getFogMaxDistance() const
{
	return _core->getRenderBus()->getFogMaxDistance();
}

const float EngineInterface::gfx_getFogThickness() const
{
	return _core->getRenderBus()->getFogThickness();
}

const fvec3 EngineInterface::gfx_getFogColor() const
{
	return _core->getRenderBus()->getFogColor();
}

const float EngineInterface::gfx_getPlanarReflectionHeight() const
{
	return _core->getRenderBus()->getPlanarReflectionHeight();
}

const fvec3 EngineInterface::gfx_getShadowEyePosition() const
{
	return _core->getShadowGenerator()->getEyePosition();
}

const fvec3 EngineInterface::gfx_getShadowCenterPosition() const
{
	return _core->getShadowGenerator()->getCenterPosition();
}

const string& EngineInterface::gfx_getLensFlareMapPath() const
{
	return _core->getRenderBus()->getLensFlareMapPath();
}

const float EngineInterface::gfx_getShadowSize() const
{
	return _core->getShadowGenerator()->getSize();
}

const float EngineInterface::gfx_getShadowReach() const
{
	return _core->getShadowGenerator()->getReach();
}

const float EngineInterface::gfx_getShadowLightness() const
{
	return _core->getShadowGenerator()->getLightness();
}

const bool EngineInterface::gfx_isShadowFollowingCamera() const
{
	return _core->getShadowGenerator()->isFollowingCamera();
}

const float EngineInterface::gfx_getBloomIntensity() const
{
	return _core->getRenderBus()->getBloomIntensity();
}

const unsigned int EngineInterface::gfx_getBloomBlurCount() const
{
	return _core->getRenderBus()->getBloomBlurCount();
}

const unsigned int EngineInterface::gfx_getShadowInterval() const
{
	return _core->getShadowGenerator()->getInterval();
}

const float EngineInterface::gfx_getSkyExposureIntensity() const
{
	return _core->getSkyEntityManager()->getExposureIntensity();
}

const float EngineInterface::gfx_getSkyExposureSpeed() const
{
	return _core->getSkyEntityManager()->getExposureSpeed();
}

const float EngineInterface::gfx_getDofDynamicDistance() const
{
	return _core->getRenderBus()->getDofDynamicDistance();
}

const float EngineInterface::gfx_getDofBlurDistance() const
{
	return _core->getRenderBus()->getDofBlurDistance();
}

const float EngineInterface::gfx_getLensFlareIntensity() const
{
	return _core->getRenderBus()->getLensFlareIntensity();
}

const float EngineInterface::gfx_getLensFlareSensitivity() const
{
	return _core->getRenderBus()->getLensFlareSensitivity();
}

const float EngineInterface::gfx_getMotionBlurStrength() const
{
	return _core->getRenderBus()->getMotionBlurStrength();
}

const unsigned int EngineInterface::gfx_getBloomQuality() const
{
	return _core->getRenderBus()->getBloomQuality();
}

const unsigned int EngineInterface::gfx_getDofQuality() const
{
	return _core->getRenderBus()->getDofQuality();
}

const unsigned int EngineInterface::gfx_getMotionBlurQuality() const
{
	return _core->getRenderBus()->getMotionBlurQuality();
}

const BloomType EngineInterface::gfx_getBloomType() const
{
	return _core->getRenderBus()->getBloomType();
}

const unsigned int EngineInterface::gfx_getAnisotropicFilteringQuality() const
{
	return _core->getRenderBus()->getAnisotropicFilteringQuality();
}
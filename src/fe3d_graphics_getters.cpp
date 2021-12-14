#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::gfx_isAntiAliasingEnabled() const
{
	return _core->_renderBus.isAntiAliasingEnabled();
}

const bool FabiEngine3D::gfx_isAmbientLightingEnabled() const
{
	return _core->_renderBus.isAmbientLightingEnabled();
}

const bool FabiEngine3D::gfx_isDirectionalLightingEnabled() const
{
	return _core->_renderBus.isDirectionalLightingEnabled();
}

const bool FabiEngine3D::gfx_isFogEnabled() const
{
	return _core->_renderBus.isFogEnabled();
}

const bool FabiEngine3D::gfx_isBloomEnabled() const
{
	return _core->_renderBus.isBloomEnabled();
}

const bool FabiEngine3D::gfx_isSkyExposureEnabled() const
{
	return _core->_skyEntityManager.isExposureEnabled();
}

const bool FabiEngine3D::gfx_isShadowsEnabled() const
{
	return _core->_shadowGenerator.isEnabled();
}

const bool FabiEngine3D::gfx_isDofEnabled() const
{
	return _core->_renderBus.isDofEnabled();
}

const bool FabiEngine3D::gfx_isDofDynamic() const
{
	return _core->_renderBus.isDofDynamic();
}

const bool FabiEngine3D::gfx_isMotionBlurEnabled() const
{
	return _core->_renderBus.isMotionBlurEnabled();
}

const bool FabiEngine3D::gfx_isLensFlareEnabled() const
{
	return _core->_renderBus.isLensFlareEnabled();
}

const unsigned int FabiEngine3D::gfx_getShadowQuality() const
{
	return _core->_shadowGenerator.getQuality();
}

const unsigned int FabiEngine3D::gfx_getCubeReflectionQuality() const
{
	return _core->_renderBus.getCubeReflectionQuality();
}

const unsigned int FabiEngine3D::gfx_getPlanarReflectionQuality() const
{
	return _core->_renderBus.getPlanarReflectionQuality();
}

const unsigned int FabiEngine3D::gfx_getPlanarRefractionQuality() const
{
	return _core->_renderBus.getPlanarRefractionQuality();
}

const fvec3 FabiEngine3D::gfx_getAmbientLightingColor() const
{
	return _core->_renderBus.getAmbientLightingColor();
}

const float FabiEngine3D::gfx_getAmbientLightingIntensity() const
{
	return _core->_renderBus.getAmbientLightingIntensity();
}

const float FabiEngine3D::gfx_getDirectionalLightingIntensity() const
{
	return _core->_renderBus.getDirectionalLightingIntensity();
}

const fvec3 FabiEngine3D::gfx_getDirectionalLightingPosition() const
{
	return _core->_renderBus.getDirectionalLightingPosition();
}

const fvec3 FabiEngine3D::gfx_getDirectionalLightingColor() const
{
	return _core->_renderBus.getDirectionalLightingColor();
}

const float FabiEngine3D::gfx_getFogMinDistance() const
{
	return _core->_renderBus.getFogMinDistance();
}

const float FabiEngine3D::gfx_getFogMaxDistance() const
{
	return _core->_renderBus.getFogMaxDistance();
}

const float FabiEngine3D::gfx_getFogThickness() const
{
	return _core->_renderBus.getFogThickness();
}

const fvec3 FabiEngine3D::gfx_getFogColor() const
{
	return _core->_renderBus.getFogColor();
}

const float FabiEngine3D::gfx_getPlanarReflectionHeight() const
{
	return _core->_renderBus.getPlanarReflectionHeight();
}

const fvec3 FabiEngine3D::gfx_getShadowEyePosition() const
{
	return _core->_shadowGenerator.getEyePosition();
}

const fvec3 FabiEngine3D::gfx_getShadowCenterPosition() const
{
	return _core->_shadowGenerator.getCenterPosition();
}

const string& FabiEngine3D::gfx_getLensFlareMapPath() const
{
	return _core->_renderBus.getLensFlareMapPath();
}

const float FabiEngine3D::gfx_getShadowSize() const
{
	return _core->_shadowGenerator.getAreaSize();
}

const float FabiEngine3D::gfx_getShadowReach() const
{
	return _core->_shadowGenerator.getAreaReach();
}

const float FabiEngine3D::gfx_getShadowLightness() const
{
	return _core->_shadowGenerator.getLightness();
}

const bool FabiEngine3D::gfx_isShadowFollowingCamera() const
{
	return _core->_shadowGenerator.isFollowingCamera();
}

const float FabiEngine3D::gfx_getBloomIntensity() const
{
	return _core->_renderBus.getBloomIntensity();
}

const unsigned int FabiEngine3D::gfx_getBloomBlurCount() const
{
	return _core->_renderBus.getBloomBlurCount();
}

const unsigned int FabiEngine3D::gfx_getShadowInterval() const
{
	return _core->_shadowGenerator.getInterval();
}

const float FabiEngine3D::gfx_getSkyExposureIntensity() const
{
	return _core->_skyEntityManager.getExposureIntensity();
}

const float FabiEngine3D::gfx_getSkyExposureSpeed() const
{
	return _core->_skyEntityManager.getExposureSpeed();
}

const float FabiEngine3D::gfx_getMaxDofDistance() const
{
	return _core->_renderBus.getDofMaxDistance();
}

const float FabiEngine3D::gfx_getDofBlurDistance() const
{
	return _core->_renderBus.getDofBlurDistance();
}

const float FabiEngine3D::gfx_getLensFlareIntensity() const
{
	return _core->_renderBus.getLensFlareIntensity();
}

const float FabiEngine3D::gfx_getLensFlareSensitivity() const
{
	return _core->_renderBus.getLensFlareSensitivity();
}

const float FabiEngine3D::gfx_getMotionBlurStrength() const
{
	return _core->_renderBus.getMotionBlurStrength();
}

const unsigned int FabiEngine3D::gfx_getBloomQuality() const
{
	return _core->_renderBus.getBloomQuality();
}

const unsigned int FabiEngine3D::gfx_getDofQuality() const
{
	return _core->_renderBus.getDofQuality();
}

const unsigned int FabiEngine3D::gfx_getMotionBlurQuality() const
{
	return _core->_renderBus.getMotionBlurQuality();
}

const BloomType FabiEngine3D::gfx_getBloomType() const
{
	return _core->_renderBus.getBloomType();
}

const unsigned int FabiEngine3D::gfx_getAnisotropicFilteringQuality() const
{
	return _core->_textureLoader.getAnisotropicFilteringQuality();
}
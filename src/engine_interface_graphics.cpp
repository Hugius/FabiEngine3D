#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::gfx_enableAmbientLighting()
{
	_core->getRenderBus()->setAmbientLightingEnabled(true);
}

void EngineInterface::gfx_enableDirectionalLighting()
{
	_core->getRenderBus()->setDirectionalLightingEnabled(true);
}

void EngineInterface::gfx_enableFog()
{
	_core->getRenderBus()->setFogEnabled(true);
}

void EngineInterface::gfx_enableAntiAliasing()
{
	_core->getRenderBus()->setAntiAliasingEnabled(true);
}

void EngineInterface::gfx_enableShadows()
{
	_core->getRenderBus()->setShadowsEnabled(true);
}

void EngineInterface::gfx_enableBloom()
{
	_core->getRenderBus()->setBloomEnabled(true);
}

void EngineInterface::gfx_enableSkyExposure()
{
	_core->getRenderBus()->setSkyExposureEnabled(true);
}

void EngineInterface::gfx_enableDOF()
{
	_core->getRenderBus()->setDofEnabled(true);
}

void EngineInterface::gfx_enableMotionBlur()
{
	_core->getRenderBus()->setMotionBlurEnabled(true);
}

void EngineInterface::gfx_enableLensFlare()
{
	_core->getRenderBus()->setLensFlareEnabled(true);
}

void EngineInterface::gfx_disableAmbientLighting(bool mustResetProperties)
{
	_core->getRenderBus()->setAmbientLightingEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setAmbientLightingColor(1.0f);
		_core->getRenderBus()->setAmbientLightingIntensity(1.0f);
	}
}

void EngineInterface::gfx_disableDirectionalLighting(bool mustResetProperties)
{
	_core->getRenderBus()->setDirectionalLightingEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setDirectionalLightingPosition(fvec3(0.0f));
		_core->getRenderBus()->setDirectionalLightingColor(1.0f);
		_core->getRenderBus()->setDirectionalLightingIntensity(1.0f);
	}
}

void EngineInterface::gfx_disableFog(bool mustResetProperties)
{
	_core->getRenderBus()->setFogEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setMinFogDistance(0.0f);
		_core->getRenderBus()->setMaxFogDistance(0.0f);
		_core->getRenderBus()->setFogThickness(0.0f);
		_core->getRenderBus()->setFogColor(fvec3(0.0f));
	}
}

void EngineInterface::gfx_disableAntiAliasing(bool mustResetProperties)
{
	_core->getRenderBus()->setAntiAliasingEnabled(false);
}

void EngineInterface::gfx_disableShadows(bool mustResetProperties)
{
	_core->getRenderBus()->setShadowsEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setShadowQuality(Config::MIN_SHADOW_QUALITY);
		_core->getRenderBus()->setShadowPositionOffset(fvec3(0.0f));
		_core->getRenderBus()->setShadowLookatOffset(fvec3(0.0f));
		_core->getRenderBus()->setShadowPosition(fvec3(0.0f));
		_core->getRenderBus()->setShadowLookat(fvec3(0.0f));
		_core->getRenderBus()->setShadowSize(0.0f);
		_core->getRenderBus()->setShadowLightness(0.0f);
		_core->getRenderBus()->setShadowInterval(0);
		_core->getRenderBus()->setShadowsFollowingCamera(false);
	}
}

void EngineInterface::gfx_disableBloom(bool mustResetProperties)
{
	_core->getRenderBus()->setBloomEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setBloomType(BloomType());
		_core->getRenderBus()->setBloomIntensity(0.0f);
		_core->getRenderBus()->setBloomBlurCount(0);
		_core->getRenderBus()->setBloomQuality(Config::MIN_BLOOM_QUALITY);
	}
}

void EngineInterface::gfx_disableSkyExposure(bool mustResetProperties)
{
	_core->getRenderBus()->setSkyExposureEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setSkyExposureIntensity(0.0f);
		_core->getRenderBus()->setSkyExposureSpeed(0.0f);
	}
}

void EngineInterface::gfx_disableDOF(bool mustResetProperties)
{
	_core->getRenderBus()->setDofEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setDofDynamic(false);
		_core->getRenderBus()->setDofDynamicDistance(0.0f);
		_core->getRenderBus()->setDofBlurDistance(0.0f);
		_core->getRenderBus()->setDofQuality(Config::MIN_DOF_QUALITY);
	}
}

void EngineInterface::gfx_disableMotionBlur(bool mustResetProperties)
{
	_core->getRenderBus()->setMotionBlurEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setMotionBlurIntensity(0.0f);
		_core->getRenderBus()->setMotionBlurQuality(Config::MIN_MOTION_BLUR_QUALITY);
	}
}

void EngineInterface::gfx_disableLensFlare(bool mustResetProperties)
{
	_core->getRenderBus()->setLensFlareEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setLensFlareMap(nullptr);
		_core->getRenderBus()->setLensFlareMapPath("");
		_core->getRenderBus()->setLensFlareIntensity(0.0f);
		_core->getRenderBus()->setLensFlareSensitivity(0.0f);
	}
}

void EngineInterface::gfx_setPlanarReflectionHeight(float value)
{
	_core->getRenderBus()->setPlanarReflectionHeight(value);
}

void EngineInterface::gfx_setBloomQuality(unsigned int value)
{
	_core->getRenderBus()->setBloomQuality(value);

	_core->getMasterRenderer()->reloadBloomBlurQuality();
}

void EngineInterface::gfx_setDofQuality(unsigned int value)
{
	_core->getRenderBus()->setDofQuality(value);

	_core->getMasterRenderer()->reloadDofBlurQuality();
}

void EngineInterface::gfx_setMotionBlurQuality(unsigned int value)
{
	_core->getRenderBus()->setMotionBlurQuality(value);

	_core->getMasterRenderer()->reloadMotionBlurBlurQuality();
}

void EngineInterface::gfx_setAnisotropicFilteringQuality(unsigned int value)
{
	_core->getRenderBus()->setAnisotropicFilteringQuality(value);

	for(const auto& [key, texture] : _core->getTextureBufferCache()->get2dBuffers())
	{
		if(texture->hasAnisotropicFiltering())
		{
			texture->loadAnisotropicFiltering(value);
		}
	}

	for(const auto& [key, texture] : _core->getTextureBufferCache()->get3dBuffers())
	{
		if(texture->hasAnisotropicFiltering())
		{
			texture->loadAnisotropicFiltering(value);
		}
	}
}

void EngineInterface::gfx_setCubeReflectionQuality(unsigned int value)
{
	_core->getRenderBus()->setCubeReflectionQuality(value);

	_core->getMasterRenderer()->reloadCubeReflectionQuality();
}

void EngineInterface::gfx_setPlanarReflectionQuality(unsigned int value)
{
	_core->getRenderBus()->setPlanarReflectionQuality(value);

	_core->getMasterRenderer()->reloadPlanarReflectionQuality();
	_core->getMasterRenderer()->reloadWaterReflectionQuality();
}

void EngineInterface::gfx_setPlanarRefractionQuality(unsigned int value)
{
	_core->getRenderBus()->setPlanarRefractionQuality(value);

	_core->getMasterRenderer()->reloadWaterRefractionQuality();
}

void EngineInterface::gfx_setShadowQuality(unsigned int value)
{
	_core->getRenderBus()->setShadowQuality(value);

	_core->getMasterRenderer()->reloadShadowQuality();
}

void EngineInterface::gfx_setAmbientLightingColor(const fvec3& value)
{
	_core->getRenderBus()->setAmbientLightingColor(value);
}

void EngineInterface::gfx_setAmbientLightingIntensity(float value)
{
	_core->getRenderBus()->setAmbientLightingIntensity(value);
}

void EngineInterface::gfx_setDirectionalLightingPosition(const fvec3& value)
{
	_core->getRenderBus()->setDirectionalLightingPosition(value);
}

void EngineInterface::gfx_setDirectionalLightingColor(const fvec3& value)
{
	_core->getRenderBus()->setDirectionalLightingColor(value);
}

void EngineInterface::gfx_setDirectionalLightingIntensity(float value)
{
	_core->getRenderBus()->setDirectionalLightingIntensity(value);
}

void EngineInterface::gfx_setFogColor(const fvec3& value)
{
	_core->getRenderBus()->setFogColor(value);
}

void EngineInterface::gfx_setFogThickness(float value)
{
	_core->getRenderBus()->setFogThickness(value);
}

void EngineInterface::gfx_setFogMinDistance(float value)
{
	_core->getRenderBus()->setMinFogDistance(value);
}

void EngineInterface::gfx_setFogMaxDistance(float value)
{
	_core->getRenderBus()->setMaxFogDistance(value);
}

void EngineInterface::gfx_setShadowCircleEnabled(bool value)
{
	_core->getRenderBus()->setShadowCircleEnabled(value);
}

void EngineInterface::gfx_setShadowPositionOffset(const fvec3& value)
{
	_core->getRenderBus()->setShadowPositionOffset(value);
}

void EngineInterface::gfx_setShadowLookatOffset(const fvec3& value)
{
	_core->getRenderBus()->setShadowLookatOffset(value);
}

void EngineInterface::gfx_setShadowSize(float value)
{
	_core->getRenderBus()->setShadowSize(value);
}

void EngineInterface::gfx_setShadowLightness(float value)
{
	_core->getRenderBus()->setShadowLightness(value);
}

void EngineInterface::gfx_setShadowInterval(unsigned int value)
{
	_core->getRenderBus()->setShadowInterval(value);
}

void EngineInterface::gfx_setShadowFollowingCamera(bool value)
{
	_core->getRenderBus()->setShadowsFollowingCamera(value);
}

void EngineInterface::gfx_setBloomIntensity(float value)
{
	_core->getRenderBus()->setBloomIntensity(value);
}

void EngineInterface::gfx_setBloomBlurCount(unsigned int value)
{
	_core->getRenderBus()->setBloomBlurCount(value);
}

void EngineInterface::gfx_setBloomType(BloomType value)
{
	_core->getRenderBus()->setBloomType(value);
}

void EngineInterface::gfx_setSkyExposureIntensity(float value)
{
	_core->getRenderBus()->setSkyExposureIntensity(value);
}

void EngineInterface::gfx_setSkyExposureSpeed(float value)
{
	_core->getRenderBus()->setSkyExposureSpeed(value);
}

void EngineInterface::gfx_setDofDynamicDistance(float value)
{
	_core->getRenderBus()->setDofDynamicDistance(value);
}

void EngineInterface::gfx_setDofBlurDistance(float value)
{
	_core->getRenderBus()->setDofBlurDistance(value);
}

void EngineInterface::gfx_setDofDynamic(bool value)
{
	_core->getRenderBus()->setDofDynamic(value);
}

void EngineInterface::gfx_setMotionBlurIntensity(float value)
{
	_core->getRenderBus()->setMotionBlurIntensity(value);
}

void EngineInterface::gfx_setLensFlareMap(const string& value)
{
	if(value.empty())
	{
		_core->getRenderBus()->setLensFlareMap(nullptr);
		_core->getRenderBus()->setLensFlareMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->loadImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getRenderBus()->setLensFlareMap(texture);
		_core->getRenderBus()->setLensFlareMapPath(value);
	}
}

void EngineInterface::gfx_setLensFlareIntensity(float value)
{
	_core->getRenderBus()->setLensFlareIntensity(value);
}

void EngineInterface::gfx_setLensFlareSensitivity(float value)
{
	_core->getRenderBus()->setLensFlareSensitivity(value);
}

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
	return _core->getRenderBus()->isSkyExposureEnabled();
}

const bool EngineInterface::gfx_isShadowsEnabled() const
{
	return _core->getRenderBus()->isShadowsEnabled();
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

const bool EngineInterface::gfx_isShadowCircleEnabled() const
{
	return _core->getRenderBus()->isShadowCircleEnabled();
}

const unsigned int EngineInterface::gfx_getShadowQuality() const
{
	return _core->getRenderBus()->getShadowQuality();
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

const fvec3& EngineInterface::gfx_getAmbientLightingColor() const
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

const fvec3& EngineInterface::gfx_getDirectionalLightingPosition() const
{
	return _core->getRenderBus()->getDirectionalLightingPosition();
}

const fvec3& EngineInterface::gfx_getDirectionalLightingColor() const
{
	return _core->getRenderBus()->getDirectionalLightingColor();
}

const float EngineInterface::gfx_getFogMinDistance() const
{
	return _core->getRenderBus()->getMinFogDistance();
}

const float EngineInterface::gfx_getFogMaxDistance() const
{
	return _core->getRenderBus()->getMaxFogDistance();
}

const float EngineInterface::gfx_getFogThickness() const
{
	return _core->getRenderBus()->getFogThickness();
}

const fvec3& EngineInterface::gfx_getFogColor() const
{
	return _core->getRenderBus()->getFogColor();
}

const float EngineInterface::gfx_getPlanarReflectionHeight() const
{
	return _core->getRenderBus()->getPlanarReflectionHeight();
}

const fvec3& EngineInterface::gfx_getShadowPositionOffset() const
{
	return _core->getRenderBus()->getShadowPositionOffset();
}

const fvec3& EngineInterface::gfx_getShadowLookatOffset() const
{
	return _core->getRenderBus()->getShadowLookatOffset();
}

const string& EngineInterface::gfx_getLensFlareMapPath() const
{
	return _core->getRenderBus()->getLensFlareMapPath();
}

const float EngineInterface::gfx_getShadowSize() const
{
	return _core->getRenderBus()->getShadowSize();
}

const float EngineInterface::gfx_getShadowLightness() const
{
	return _core->getRenderBus()->getShadowLightness();
}

const bool EngineInterface::gfx_isShadowFollowingCamera() const
{
	return _core->getRenderBus()->isShadowsFollowingCamera();
}

const bool EngineInterface::gfx_hasLensFlareMap() const
{
	return (_core->getRenderBus()->getLensFlareMap() != nullptr);
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
	return _core->getRenderBus()->getShadowInterval();
}

const float EngineInterface::gfx_getSkyExposureIntensity() const
{
	return _core->getRenderBus()->getSkyExposureIntensity();
}

const float EngineInterface::gfx_getSkyExposureSpeed() const
{
	return _core->getRenderBus()->getSkyExposureSpeed();
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

const float EngineInterface::gfx_getMotionBlurIntensity() const
{
	return _core->getRenderBus()->getMotionBlurIntensity();
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
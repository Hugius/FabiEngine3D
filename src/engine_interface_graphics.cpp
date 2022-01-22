#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::gfx_enableAmbientLighting()
{
	if(_core->getRenderBus()->isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to enable ambient lighting: already enabled");
		return;
	}

	_core->getRenderBus()->setAmbientLightingEnabled(true);
}

void EngineInterface::gfx_enableDirectionalLighting()
{
	if(_core->getRenderBus()->isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to enable directional lighting: already enabled");
		return;
	}

	_core->getRenderBus()->setDirectionalLightingEnabled(true);
}

void EngineInterface::gfx_enableFog()
{
	if(_core->getRenderBus()->isFogEnabled())
	{
		Logger::throwWarning("Tried to enable fog: already enabled");
		return;
	}

	_core->getRenderBus()->setFogEnabled(true);
}

void EngineInterface::gfx_enableAntiAliasing()
{
	if(_core->getRenderBus()->isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to enable anti aliasing: already enabled");
		return;
	}

	_core->getRenderBus()->setAntiAliasingEnabled(true);
}

void EngineInterface::gfx_enableShadows()
{
	if(_core->getShadowGenerator()->isEnabled())
	{
		Logger::throwWarning("Tried to enable shadows: already enabled");
		return;
	}

	_core->getShadowGenerator()->setEnabled(true);
}

void EngineInterface::gfx_enableBloom()
{
	if(_core->getRenderBus()->isBloomEnabled())
	{
		Logger::throwWarning("Tried to enable bloom: already enabled");
		return;
	}

	_core->getRenderBus()->setBloomEnabled(true);
}

void EngineInterface::gfx_enableSkyExposure()
{
	if(_core->getRenderBus()->isSkyExposureEnabled())
	{
		Logger::throwWarning("Tried to enable sky exposure: already enabled");
		return;
	}

	_core->getRenderBus()->setSkyExposureEnabled(true);
}

void EngineInterface::gfx_enableDOF()
{
	if(_core->getRenderBus()->isDofEnabled())
	{
		Logger::throwWarning("Tried to enable DOF: already enabled");
		return;
	}

	_core->getRenderBus()->setDofEnabled(true);
}

void EngineInterface::gfx_enableMotionBlur()
{
	if(_core->getRenderBus()->isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to enable motion blur: already enabled");
		return;
	}

	_core->getRenderBus()->setMotionBlurEnabled(true);
}

void EngineInterface::gfx_enableLensFlare()
{
	if(_core->getRenderBus()->isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to enable lens flare: already enabled");
		return;
	}

	_core->getRenderBus()->setLensFlareEnabled(true);
}

void EngineInterface::gfx_disableAmbientLighting(bool mustResetProperties)
{
	if(!_core->getRenderBus()->isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to disable ambient lighting: not enabled");
		return;
	}

	_core->getRenderBus()->setAmbientLightingEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setAmbientLightingColor(1.0f);
		_core->getRenderBus()->setAmbientLightingIntensity(1.0f);
	}
}

void EngineInterface::gfx_disableDirectionalLighting(bool mustResetProperties)
{
	if(!_core->getRenderBus()->isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to disable directional lighting: not enabled");
		return;
	}

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
	if(!_core->getRenderBus()->isFogEnabled())
	{
		Logger::throwWarning("Tried to disable fog: not enabled");
		return;
	}

	_core->getRenderBus()->setFogEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setFogMinDistance(0.0f);
		_core->getRenderBus()->setFogMaxDistance(0.0f);
		_core->getRenderBus()->setFogThickness(0.0f);
		_core->getRenderBus()->setFogColor(fvec3(0.0f));
	}
}

void EngineInterface::gfx_disableAntiAliasing(bool mustResetProperties)
{
	if(!_core->getRenderBus()->isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to disable anti aliasing: not enabled");
		return;
	}

	_core->getRenderBus()->setAntiAliasingEnabled(false);
}

void EngineInterface::gfx_disableShadows(bool mustResetProperties)
{
	if(!_core->getShadowGenerator()->isEnabled())
	{
		Logger::throwWarning("Tried to disable shadows: not enabled");
		return;
	}

	_core->getShadowGenerator()->setEnabled(false);

	if(mustResetProperties)
	{
		_core->getShadowGenerator()->setEyePosition(fvec3(0.0f));
		_core->getShadowGenerator()->setCenterPosition(fvec3(0.0f));
		_core->getShadowGenerator()->setSize(0.0f);
		_core->getShadowGenerator()->setReach(0.0f);
		_core->getShadowGenerator()->setLightness(0.0f);
		_core->getShadowGenerator()->setQuality(Config::MIN_SHADOW_QUALITY);
		_core->getShadowGenerator()->setInterval(0);
		_core->getShadowGenerator()->setFollowingCamera(false);
	}
}

void EngineInterface::gfx_disableBloom(bool mustResetProperties)
{
	if(!_core->getRenderBus()->isBloomEnabled())
	{
		Logger::throwWarning("Tried to disable bloom: not enabled");
		return;
	}

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
	if(!_core->getRenderBus()->isSkyExposureEnabled())
	{
		Logger::throwWarning("Tried to disable sky exposure: not enabled");
		return;
	}

	_core->getRenderBus()->setSkyExposureEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setSkyExposureIntensity(0.0f);
		_core->getRenderBus()->setSkyExposureSpeed(0.0f);
	}
}

void EngineInterface::gfx_disableDOF(bool mustResetProperties)
{
	if(!_core->getRenderBus()->isDofEnabled())
	{
		Logger::throwWarning("Tried to disable DOF: not enabled");
		return;
	}

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
	if(!_core->getRenderBus()->isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to disable motion blur: not enabled");
		return;
	}

	_core->getRenderBus()->setMotionBlurEnabled(false);

	if(mustResetProperties)
	{
		_core->getRenderBus()->setMotionBlurStrength(0.0f);
		_core->getRenderBus()->setMotionBlurQuality(Config::MIN_MOTION_BLUR_QUALITY);
	}
}

void EngineInterface::gfx_disableLensFlare(bool mustResetProperties)
{
	if(!_core->getRenderBus()->isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to disable lens flare: not enabled");
		return;
	}

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
	_core->getMasterRenderer()->reloadBloomBlurCaptureBuffer();
}

void EngineInterface::gfx_setDofQuality(unsigned int value)
{
	_core->getRenderBus()->setDofQuality(value);
	_core->getMasterRenderer()->reloadDofBlurCaptureBuffer();
}

void EngineInterface::gfx_setMotionBlurQuality(unsigned int value)
{
	_core->getRenderBus()->setMotionBlurQuality(value);
	_core->getMasterRenderer()->reloadMotionBlurBlurCaptureBuffer();
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
	_core->getMasterRenderer()->reloadCubeReflectionCaptureBuffer();
}

void EngineInterface::gfx_setPlanarReflectionQuality(unsigned int value)
{
	_core->getRenderBus()->setPlanarReflectionQuality(value);
	_core->getMasterRenderer()->reloadPlanarReflectionCaptureBuffer();
	_core->getMasterRenderer()->reloadWaterReflectionCaptureBuffer();
}

void EngineInterface::gfx_setPlanarRefractionQuality(unsigned int value)
{
	_core->getRenderBus()->setPlanarRefractionQuality(value);
	_core->getMasterRenderer()->reloadWaterRefractionCaptureBuffer();
}

void EngineInterface::gfx_setShadowQuality(unsigned int value)
{
	_core->getShadowGenerator()->setQuality(value);
	_core->getMasterRenderer()->reloadShadowCaptureBuffer();
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
	_core->getRenderBus()->setFogMinDistance(value);
}

void EngineInterface::gfx_setFogMaxDistance(float value)
{
	_core->getRenderBus()->setFogMaxDistance(value);
}

void EngineInterface::gfx_setShadowEyePosition(const fvec3& value)
{
	_core->getShadowGenerator()->setEyePosition(value);
}

void EngineInterface::gfx_setShadowCenterPosition(const fvec3& value)
{
	_core->getShadowGenerator()->setCenterPosition(value);
}

void EngineInterface::gfx_setShadowSize(float value)
{
	_core->getShadowGenerator()->setSize(value);
}

void EngineInterface::gfx_setShadowReach(float value)
{
	_core->getShadowGenerator()->setReach(value);
}

void EngineInterface::gfx_setShadowLightness(float value)
{
	_core->getShadowGenerator()->setLightness(value);
}

void EngineInterface::gfx_setShadowInterval(unsigned int value)
{
	_core->getShadowGenerator()->setInterval(value);
}

void EngineInterface::gfx_setShadowFollowingCamera(bool value)
{
	_core->getShadowGenerator()->setFollowingCamera(value);
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

void EngineInterface::gfx_setMotionBlurStrength(float value)
{
	_core->getRenderBus()->setMotionBlurStrength(value);
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
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
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

const fvec3& EngineInterface::gfx_getFogColor() const
{
	return _core->getRenderBus()->getFogColor();
}

const float EngineInterface::gfx_getPlanarReflectionHeight() const
{
	return _core->getRenderBus()->getPlanarReflectionHeight();
}

const fvec3& EngineInterface::gfx_getShadowEyePosition() const
{
	return _core->getShadowGenerator()->getEyePosition();
}

const fvec3& EngineInterface::gfx_getShadowCenterPosition() const
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
	return _core->getShadowGenerator()->getInterval();
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
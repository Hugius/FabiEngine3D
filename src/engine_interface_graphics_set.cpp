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
	if(_core->getSkyEntityManager()->isExposureEnabled())
	{
		Logger::throwWarning("Tried to enable sky exposure: already enabled");
		return;
	}

	_core->getSkyEntityManager()->setExposureEnabled(true);
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
	if(!_core->getSkyEntityManager()->isExposureEnabled())
	{
		Logger::throwWarning("Tried to disable sky exposure: not enabled");
		return;
	}

	_core->getSkyEntityManager()->setExposureEnabled(false);

	if(mustResetProperties)
	{
		_core->getSkyEntityManager()->setExposureIntensity(0.0f);
		_core->getSkyEntityManager()->setExposureSpeed(0.0f);
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

void EngineInterface::gfx_setAmbientLightingColor(fvec3 value)
{
	_core->getRenderBus()->setAmbientLightingColor(value);
}

void EngineInterface::gfx_setAmbientLightingIntensity(float value)
{
	_core->getRenderBus()->setAmbientLightingIntensity(value);
}

void EngineInterface::gfx_setDirectionalLightingPosition(fvec3 value)
{
	_core->getRenderBus()->setDirectionalLightingPosition(value);
}

void EngineInterface::gfx_setDirectionalLightingColor(fvec3 value)
{
	_core->getRenderBus()->setDirectionalLightingColor(value);
}

void EngineInterface::gfx_setDirectionalLightingIntensity(float value)
{
	_core->getRenderBus()->setDirectionalLightingIntensity(value);
}

void EngineInterface::gfx_setFogColor(fvec3 value)
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

void EngineInterface::gfx_setShadowEyePosition(fvec3 value)
{
	_core->getShadowGenerator()->setEyePosition(value);
}

void EngineInterface::gfx_setShadowCenterPosition(fvec3 value)
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
	_core->getSkyEntityManager()->setExposureIntensity(value);
}

void EngineInterface::gfx_setSkyExposureSpeed(float value)
{
	_core->getSkyEntityManager()->setExposureSpeed(value);
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
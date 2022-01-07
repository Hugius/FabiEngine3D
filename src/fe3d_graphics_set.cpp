#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::gfx_enableAmbientLighting()
{
	if(_core->_renderBus->isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to enable ambient lighting: already enabled");
		return;
	}

	_core->_renderBus->setAmbientLightingEnabled(true);
}

void FabiEngine3D::gfx_enableDirectionalLighting()
{
	if(_core->_renderBus->isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to enable directional lighting: already enabled");
		return;
	}

	_core->_renderBus->setDirectionalLightingEnabled(true);
}

void FabiEngine3D::gfx_enableFog()
{
	if(_core->_renderBus->isFogEnabled())
	{
		Logger::throwWarning("Tried to enable fog: already enabled");
		return;
	}

	_core->_renderBus->setFogEnabled(true);
}

void FabiEngine3D::gfx_enableAntiAliasing()
{
	if(_core->_renderBus->isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to enable anti aliasing: already enabled");
		return;
	}

	_core->_renderBus->setAntiAliasingEnabled(true);
}

void FabiEngine3D::gfx_enableShadows()
{
	if(_core->_shadowGenerator->isEnabled())
	{
		Logger::throwWarning("Tried to enable shadows: already enabled");
		return;
	}

	_core->_shadowGenerator->setEnabled(true);
}

void FabiEngine3D::gfx_enableBloom()
{
	if(_core->_renderBus->isBloomEnabled())
	{
		Logger::throwWarning("Tried to enable bloom: already enabled");
		return;
	}

	_core->_renderBus->setBloomEnabled(true);
}

void FabiEngine3D::gfx_enableSkyExposure()
{
	if(_core->_skyEntityManager->isExposureEnabled())
	{
		Logger::throwWarning("Tried to enable sky exposure: already enabled");
		return;
	}

	_core->_skyEntityManager->setExposureEnabled(true);
}

void FabiEngine3D::gfx_enableDOF()
{
	if(_core->_renderBus->isDofEnabled())
	{
		Logger::throwWarning("Tried to enable DOF: already enabled");
		return;
	}

	_core->_renderBus->setDofEnabled(true);
}

void FabiEngine3D::gfx_enableMotionBlur()
{
	if(_core->_renderBus->isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to enable motion blur: already enabled");
		return;
	}

	_core->_renderBus->setMotionBlurEnabled(true);
}

void FabiEngine3D::gfx_enableLensFlare()
{
	if(_core->_renderBus->isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to enable lens flare: already enabled");
		return;
	}

	_core->_renderBus->setLensFlareEnabled(true);
}

void FabiEngine3D::gfx_disableAmbientLighting(bool mustResetProperties)
{
	if(!_core->_renderBus->isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to disable ambient lighting: not enabled");
		return;
	}

	_core->_renderBus->setAmbientLightingEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setAmbientLightingColor(1.0f);
		_core->_renderBus->setAmbientLightingIntensity(1.0f);
	}
}

void FabiEngine3D::gfx_disableDirectionalLighting(bool mustResetProperties)
{
	if(!_core->_renderBus->isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to disable directional lighting: not enabled");
		return;
	}

	_core->_renderBus->setDirectionalLightingEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setDirectionalLightingPosition(fvec3(0.0f));
		_core->_renderBus->setDirectionalLightingColor(1.0f);
		_core->_renderBus->setDirectionalLightingIntensity(1.0f);
	}
}

void FabiEngine3D::gfx_disableFog(bool mustResetProperties)
{
	if(!_core->_renderBus->isFogEnabled())
	{
		Logger::throwWarning("Tried to disable fog: not enabled");
		return;
	}

	_core->_renderBus->setFogEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setFogMinDistance(0.0f);
		_core->_renderBus->setFogMaxDistance(0.0f);
		_core->_renderBus->setFogThickness(0.0f);
		_core->_renderBus->setFogColor(fvec3(0.0f));
	}
}

void FabiEngine3D::gfx_disableAntiAliasing(bool mustResetProperties)
{
	if(!_core->_renderBus->isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to disable anti aliasing: not enabled");
		return;
	}

	_core->_renderBus->setAntiAliasingEnabled(false);
}

void FabiEngine3D::gfx_disableShadows(bool mustResetProperties)
{
	if(!_core->_shadowGenerator->isEnabled())
	{
		Logger::throwWarning("Tried to disable shadows: not enabled");
		return;
	}

	_core->_shadowGenerator->setEnabled(false);

	if(mustResetProperties)
	{
		_core->_shadowGenerator->setEyePosition(fvec3(0.0f));
		_core->_shadowGenerator->setCenterPosition(fvec3(0.0f));
		_core->_shadowGenerator->setSize(0.0f);
		_core->_shadowGenerator->setReach(0.0f);
		_core->_shadowGenerator->setLightness(0.0f);
		_core->_shadowGenerator->setQuality(Config::MIN_SHADOW_QUALITY);
		_core->_shadowGenerator->setInterval(0);
		_core->_shadowGenerator->setFollowingCamera(false);
	}
}

void FabiEngine3D::gfx_disableBloom(bool mustResetProperties)
{
	if(!_core->_renderBus->isBloomEnabled())
	{
		Logger::throwWarning("Tried to disable bloom: not enabled");
		return;
	}

	_core->_renderBus->setBloomEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setBloomType(BloomType());
		_core->_renderBus->setBloomIntensity(0.0f);
		_core->_renderBus->setBloomBlurCount(0);
		_core->_renderBus->setBloomQuality(Config::MIN_BLOOM_QUALITY);
	}
}

void FabiEngine3D::gfx_disableSkyExposure(bool mustResetProperties)
{
	if(!_core->_skyEntityManager->isExposureEnabled())
	{
		Logger::throwWarning("Tried to disable sky exposure: not enabled");
		return;
	}

	_core->_skyEntityManager->setExposureEnabled(false);

	if(mustResetProperties)
	{
		_core->_skyEntityManager->setExposureIntensity(0.0f);
		_core->_skyEntityManager->setExposureSpeed(0.0f);
	}
}

void FabiEngine3D::gfx_disableDOF(bool mustResetProperties)
{
	if(!_core->_renderBus->isDofEnabled())
	{
		Logger::throwWarning("Tried to disable DOF: not enabled");
		return;
	}

	_core->_renderBus->setDofEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setDofDynamic(false);
		_core->_renderBus->setDofDynamicDistance(0.0f);
		_core->_renderBus->setDofBlurDistance(0.0f);
		_core->_renderBus->setDofQuality(Config::MIN_DOF_QUALITY);
	}
}

void FabiEngine3D::gfx_disableMotionBlur(bool mustResetProperties)
{
	if(!_core->_renderBus->isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to disable motion blur: not enabled");
		return;
	}

	_core->_renderBus->setMotionBlurEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setMotionBlurStrength(0.0f);
		_core->_renderBus->setMotionBlurQuality(Config::MIN_MOTION_BLUR_QUALITY);
	}
}

void FabiEngine3D::gfx_disableLensFlare(bool mustResetProperties)
{
	if(!_core->_renderBus->isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to disable lens flare: not enabled");
		return;
	}

	_core->_renderBus->setLensFlareEnabled(false);

	if(mustResetProperties)
	{
		_core->_renderBus->setLensFlareMap(0);
		_core->_renderBus->setLensFlareMapPath("");
		_core->_renderBus->setLensFlareIntensity(0.0f);
		_core->_renderBus->setLensFlareSensitivity(0.0f);
	}
}

void FabiEngine3D::gfx_setPlanarReflectionHeight(float value)
{
	_core->_renderBus->setPlanarReflectionHeight(value);
}

void FabiEngine3D::gfx_setBloomQuality(unsigned int value)
{
	_core->_renderBus->setBloomQuality(value);
	_core->_masterRenderer->reloadBloomBlurCaptureBuffer();
}

void FabiEngine3D::gfx_setDofQuality(unsigned int value)
{
	_core->_renderBus->setDofQuality(value);
	_core->_masterRenderer->reloadDofBlurCaptureBuffer();
}

void FabiEngine3D::gfx_setMotionBlurQuality(unsigned int value)
{
	_core->_renderBus->setMotionBlurQuality(value);
	_core->_masterRenderer->reloadMotionBlurBlurCaptureBuffer();
}

void FabiEngine3D::gfx_setAnisotropicFilteringQuality(unsigned int value)
{
	_core->_renderBus->setAnisotropicFilteringQuality(value);

	for(const auto& texture : _core->_textureBufferCache->getBuffers())
	{
		if(texture->hasAnisotropicFiltering())
		{
			texture->loadAnisotropicFiltering(value);
		}
	}
}

void FabiEngine3D::gfx_setCubeReflectionQuality(unsigned int value)
{
	_core->_renderBus->setCubeReflectionQuality(value);
	_core->_masterRenderer->reloadCubeReflectionCaptureBuffer();
}

void FabiEngine3D::gfx_setPlanarReflectionQuality(unsigned int value)
{
	_core->_renderBus->setPlanarReflectionQuality(value);
	_core->_masterRenderer->reloadPlanarReflectionCaptureBuffer();
	_core->_masterRenderer->reloadWaterReflectionCaptureBuffer();
}

void FabiEngine3D::gfx_setPlanarRefractionQuality(unsigned int value)
{
	_core->_renderBus->setPlanarRefractionQuality(value);
	_core->_masterRenderer->reloadWaterRefractionCaptureBuffer();
}

void FabiEngine3D::gfx_setShadowQuality(unsigned int value)
{
	_core->_shadowGenerator->setQuality(value);
	_core->_masterRenderer->reloadShadowCaptureBuffer();
}

void FabiEngine3D::gfx_setAmbientLightingColor(fvec3 value)
{
	_core->_renderBus->setAmbientLightingColor(value);
}

void FabiEngine3D::gfx_setAmbientLightingIntensity(float value)
{
	_core->_renderBus->setAmbientLightingIntensity(value);
}

void FabiEngine3D::gfx_setDirectionalLightingPosition(fvec3 value)
{
	_core->_renderBus->setDirectionalLightingPosition(value);
}

void FabiEngine3D::gfx_setDirectionalLightingColor(fvec3 value)
{
	_core->_renderBus->setDirectionalLightingColor(value);
}

void FabiEngine3D::gfx_setDirectionalLightingIntensity(float value)
{
	_core->_renderBus->setDirectionalLightingIntensity(value);
}

void FabiEngine3D::gfx_setFogColor(fvec3 value)
{
	_core->_renderBus->setFogColor(value);
}

void FabiEngine3D::gfx_setFogThickness(float value)
{
	_core->_renderBus->setFogThickness(value);
}

void FabiEngine3D::gfx_setFogMinDistance(float value)
{
	_core->_renderBus->setFogMinDistance(value);
}

void FabiEngine3D::gfx_setFogMaxDistance(float value)
{
	_core->_renderBus->setFogMaxDistance(value);
}

void FabiEngine3D::gfx_setShadowEyePosition(fvec3 value)
{
	_core->_shadowGenerator->setEyePosition(value);
}

void FabiEngine3D::gfx_setShadowCenterPosition(fvec3 value)
{
	_core->_shadowGenerator->setCenterPosition(value);
}

void FabiEngine3D::gfx_setShadowSize(float value)
{
	_core->_shadowGenerator->setSize(value);
}

void FabiEngine3D::gfx_setShadowReach(float value)
{
	_core->_shadowGenerator->setReach(value);
}

void FabiEngine3D::gfx_setShadowLightness(float value)
{
	_core->_shadowGenerator->setLightness(value);
}

void FabiEngine3D::gfx_setShadowInterval(unsigned int value)
{
	_core->_shadowGenerator->setInterval(value);
}

void FabiEngine3D::gfx_setShadowFollowingCamera(bool value)
{
	_core->_shadowGenerator->setFollowingCamera(value);
}

void FabiEngine3D::gfx_setBloomIntensity(float value)
{
	_core->_renderBus->setBloomIntensity(value);
}

void FabiEngine3D::gfx_setBloomBlurCount(unsigned int value)
{
	_core->_renderBus->setBloomBlurCount(value);
}

void FabiEngine3D::gfx_setBloomType(BloomType value)
{
	_core->_renderBus->setBloomType(value);
}

void FabiEngine3D::gfx_setSkyExposureIntensity(float value)
{
	_core->_skyEntityManager->setExposureIntensity(value);
}

void FabiEngine3D::gfx_setSkyExposureSpeed(float value)
{
	_core->_skyEntityManager->setExposureSpeed(value);
}

void FabiEngine3D::gfx_setDofDynamicDistance(float value)
{
	_core->_renderBus->setDofDynamicDistance(value);
}

void FabiEngine3D::gfx_setDofBlurDistance(float value)
{
	_core->_renderBus->setDofBlurDistance(value);
}

void FabiEngine3D::gfx_setDofDynamic(bool value)
{
	_core->_renderBus->setDofDynamic(value);
}

void FabiEngine3D::gfx_setMotionBlurStrength(float value)
{
	_core->_renderBus->setMotionBlurStrength(value);
}

void FabiEngine3D::gfx_setLensFlareMap(const string& value)
{
	auto texture = _core->_textureBufferCache->getBuffer(value);

	if(texture == nullptr)
	{
		texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value));

		_core->_textureBufferCache->storeBuffer(value, texture);
	}

	_core->_renderBus->setLensFlareMap(texture);
	_core->_renderBus->setLensFlareMapPath(value);
}

void FabiEngine3D::gfx_setLensFlareIntensity(float value)
{
	_core->_renderBus->setLensFlareIntensity(value);
}

void FabiEngine3D::gfx_setLensFlareSensitivity(float value)
{
	_core->_renderBus->setLensFlareSensitivity(value);
}
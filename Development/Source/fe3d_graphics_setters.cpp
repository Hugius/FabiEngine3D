#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gfx_enableAmbientLighting()
{
	if(_core->_renderBus.isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to enable ambient lighting: already enabled");
		return;
	}

	_core->_renderBus.setAmbientLightingEnabled(true);
}

void FabiEngine3D::gfx_enableDirectionalLighting()
{
	if(_core->_renderBus.isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to enable directional lighting: already enabled");
		return;
	}

	_core->_renderBus.setDirectionalLightingEnabled(true);
}

void FabiEngine3D::gfx_enableFog()
{
	if(_core->_renderBus.isFogEnabled())
	{
		Logger::throwWarning("Tried to enable fog: already enabled");
		return;
	}

	_core->_renderBus.setFogEnabled(true);
}

void FabiEngine3D::gfx_enableAntiAliasing()
{
	if(_core->_renderBus.isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to enable anti aliasing: already enabled");
		return;
	}

	_core->_renderBus.setAntiAliasingEnabled(true);
}

void FabiEngine3D::gfx_enableShadows()
{
	if(_core->_renderBus.isShadowsEnabled())
	{
		Logger::throwWarning("Tried to enable shadows: already enabled");
		return;
	}

	_core->_renderBus.setShadowsEnabled(true);
}

void FabiEngine3D::gfx_enableBloom()
{
	if(_core->_renderBus.isBloomEnabled())
	{
		Logger::throwWarning("Tried to enable bloom: already enabled");
		return;
	}

	_core->_renderBus.setBloomEnabled(true);
}

void FabiEngine3D::gfx_enableSkyExposure()
{
	if(_core->_skyEntityManager.isExposureEnabled())
	{
		Logger::throwWarning("Tried to enable sky exposure: already enabled");
		return;
	}

	_core->_skyEntityManager.setExposureEnabled(true);
}

void FabiEngine3D::gfx_enableDOF()
{
	if(_core->_renderBus.isDofEnabled())
	{
		Logger::throwWarning("Tried to enable DOF: already enabled");
		return;
	}

	_core->_renderBus.setDofEnabled(true);
}

void FabiEngine3D::gfx_enableMotionBlur()
{
	if(_core->_renderBus.isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to enable motion blur: already enabled");
		return;
	}

	_core->_renderBus.setMotionBlurEnabled(true);
}

void FabiEngine3D::gfx_enableLensFlare()
{
	if(_core->_renderBus.isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to enable lens flare: already enabled");
		return;
	}

	_core->_renderBus.setLensFlareEnabled(true);
}

void FabiEngine3D::gfx_disableAmbientLighting(bool resetProperties)
{
	if(!_core->_renderBus.isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to disable ambient lighting: not enabled");
		return;
	}

	_core->_renderBus.setAmbientLightingEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setAmbientLightingColor(1.0f);
		_core->_renderBus.setAmbientLightingIntensity(1.0f);
	}
}

void FabiEngine3D::gfx_disableDirectionalLighting(bool resetProperties)
{
	if(!_core->_renderBus.isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to disable directional lighting: not enabled");
		return;
	}

	_core->_renderBus.setDirectionalLightingEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setDirectionalLightingPosition(Vec3(0.0f));
		_core->_renderBus.setDirectionalLightingColor(1.0f);
		_core->_renderBus.setDirectionalLightingIntensity(1.0f);
	}
}

void FabiEngine3D::gfx_disableFog(bool resetProperties)
{
	if(!_core->_renderBus.isFogEnabled())
	{
		Logger::throwWarning("Tried to disable fog: not enabled");
		return;
	}

	_core->_renderBus.setFogEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setFogMinDistance(0.0f);
		_core->_renderBus.setFogMaxDistance(0.0f);
		_core->_renderBus.setFogThickness(0.0f);
		_core->_renderBus.setFogColor(Vec3(0.0f));
	}
}

void FabiEngine3D::gfx_disableAntiAliasing(bool resetProperties)
{
	if(!_core->_renderBus.isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to disable anti aliasing: not enabled");
		return;
	}

	_core->_renderBus.setAntiAliasingEnabled(false);
}

void FabiEngine3D::gfx_disableShadows(bool resetProperties)
{
	if(!_core->_renderBus.isShadowsEnabled())
	{
		Logger::throwWarning("Tried to disable shadows: not enabled");
		return;
	}

	_core->_renderBus.setShadowsEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setShadowEyePosition(Vec3(0.0f));
		_core->_renderBus.setShadowCenterPosition(Vec3(0.0f));
		_core->_renderBus.setShadowAreaSize(0.0f);
		_core->_renderBus.setShadowAreaReach(0.0f);
		_core->_renderBus.setShadowLightness(0.0f);
		_core->_shadowGenerator.setInterval(0);
		_core->_shadowGenerator.setFollowingCamera(false);
	}
}

void FabiEngine3D::gfx_disableBloom(bool resetProperties)
{
	if(!_core->_renderBus.isBloomEnabled())
	{
		Logger::throwWarning("Tried to disable bloom: not enabled");
		return;
	}

	_core->_renderBus.setBloomEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setBloomType(BloomType());
		_core->_renderBus.setBloomIntensity(0.0f);
		_core->_renderBus.setBloomBlurCount(0);
	}
}

void FabiEngine3D::gfx_disableSkyExposure(bool resetProperties)
{
	if(!_core->_skyEntityManager.isExposureEnabled())
	{
		Logger::throwWarning("Tried to disable sky exposure: not enabled");
		return;
	}

	_core->_skyEntityManager.setExposureEnabled(false);

	if(resetProperties)
	{
		_core->_skyEntityManager.setExposureIntensity(0.0f);
		_core->_skyEntityManager.setExposureSpeed(0.0f);
	}
}

void FabiEngine3D::gfx_disableDOF(bool resetProperties)
{
	if(!_core->_renderBus.isDofEnabled())
	{
		Logger::throwWarning("Tried to disable DOF: not enabled");
		return;
	}

	_core->_renderBus.setDofEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setDofDynamic(false);
		_core->_renderBus.setDofMaxDistance(0.0f);
		_core->_renderBus.setDofBlurDistance(0.0f);
	}
}

void FabiEngine3D::gfx_disableMotionBlur(bool resetProperties)
{
	if(!_core->_renderBus.isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to disable motion blur: not enabled");
		return;
	}

	_core->_renderBus.setMotionBlurEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setMotionBlurStrength(0.0f);
	}
}

void FabiEngine3D::gfx_disableLensFlare(bool resetProperties)
{
	if(!_core->_renderBus.isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to disable lens flare: not enabled");
		return;
	}

	_core->_renderBus.setLensFlareEnabled(false);

	if(resetProperties)
	{
		_core->_renderBus.setLensFlareMap(0);
		_core->_renderBus.setLensFlareMapPath("");
		_core->_renderBus.setLensFlareIntensity(0.0f);
		_core->_renderBus.setLensFlareSensitivity(0.0f);
	}
}

void FabiEngine3D::gfx_setPlanarReflectionHeight(float height)
{
	_core->_renderBus.setPlanarReflectionHeight(height);
}

void FabiEngine3D::gfx_setBloomSize(unsigned int size)
{
	_core->_renderBus.setBloomSize(size);
	_core->_masterRenderer.reloadBloomBlurCaptureBuffer();
}

void FabiEngine3D::gfx_setDofSize(unsigned int size)
{
	_core->_renderBus.setDofSize(size);
	_core->_masterRenderer.reloadDofBlurCaptureBuffer();
}

void FabiEngine3D::gfx_setMotionBlurSize(unsigned int size)
{
	_core->_renderBus.setMotionBlurSize(size);
	_core->_masterRenderer.reloadMotionBlurBlurCaptureBuffer();
}

void FabiEngine3D::gfx_setAnisotropicFilteringQuality(unsigned int quality)
{
	_core->_textureLoader.setAnisotropicFilteringQuality(quality);
}

void FabiEngine3D::gfx_setCubeReflectionQuality(unsigned int quality)
{
	_core->_renderBus.setCubeReflectionQuality(quality);
	_core->_masterRenderer.reloadCubeReflectionCaptureBuffer();
}

void FabiEngine3D::gfx_setPlanarReflectionQuality(unsigned int quality)
{
	_core->_renderBus.setPlanarReflectionQuality(quality);
	_core->_masterRenderer.reloadPlanarReflectionCaptureBuffer();
	_core->_masterRenderer.reloadWaterReflectionCaptureBuffer();
}

void FabiEngine3D::gfx_setRefractionQuality(unsigned int quality)
{
	_core->_renderBus.setRefractionQuality(quality);
	_core->_masterRenderer.reloadWaterRefractionCaptureBuffer();
}

void FabiEngine3D::gfx_setShadowQuality(unsigned int quality)
{
	_core->_renderBus.setShadowQuality(quality);
	_core->_masterRenderer.reloadShadowCaptureBuffer();
}

void FabiEngine3D::gfx_setAmbientLightingColor(Vec3 color)
{
	_core->_renderBus.setAmbientLightingColor(color);
}

void FabiEngine3D::gfx_setAmbientLightingIntensity(float intensity)
{
	_core->_renderBus.setAmbientLightingIntensity(intensity);
}

void FabiEngine3D::gfx_setDirectionalLightingPosition(Vec3 position)
{
	_core->_renderBus.setDirectionalLightingPosition(position);
}

void FabiEngine3D::gfx_setDirectionalLightingColor(Vec3 color)
{
	_core->_renderBus.setDirectionalLightingColor(color);
}

void FabiEngine3D::gfx_setDirectionalLightingIntensity(float intensity)
{
	_core->_renderBus.setDirectionalLightingIntensity(intensity);
}

void FabiEngine3D::gfx_setFogColor(Vec3 color)
{
	_core->_renderBus.setFogColor(color);
}

void FabiEngine3D::gfx_setFogThickness(float thickness)
{
	_core->_renderBus.setFogThickness(thickness);
}

void FabiEngine3D::gfx_setFogMinDistance(float minDistance)
{
	_core->_renderBus.setFogMinDistance(minDistance);
}

void FabiEngine3D::gfx_setFogMaxDistance(float maxDistance)
{
	_core->_renderBus.setFogMaxDistance(maxDistance);
}

void FabiEngine3D::gfx_setShadowEyePosition(Vec3 position)
{
	_core->_renderBus.setShadowEyePosition(position);
}

void FabiEngine3D::gfx_setShadowCenterPosition(Vec3 position)
{
	_core->_renderBus.setShadowCenterPosition(position);
}

void FabiEngine3D::gfx_setShadowAreaSize(float size)
{
	_core->_renderBus.setShadowAreaSize(size);
}

void FabiEngine3D::gfx_setShadowAreaReach(float reach)
{
	_core->_renderBus.setShadowAreaReach(reach);
}

void FabiEngine3D::gfx_setShadowLightness(float lightness)
{
	_core->_renderBus.setShadowLightness(lightness);
}

void FabiEngine3D::gfx_setShadowInterval(unsigned int interval)
{
	_core->_shadowGenerator.setInterval(interval);
}

void FabiEngine3D::gfx_setShadowFollowingCamera(bool isFollowingCamera)
{
	_core->_shadowGenerator.setFollowingCamera(isFollowingCamera);
}

void FabiEngine3D::gfx_setBloomIntensity(float intensity)
{
	_core->_renderBus.setBloomIntensity(intensity);
}

void FabiEngine3D::gfx_setBloomBlurCount(unsigned int blurCount)
{
	_core->_renderBus.setBloomBlurCount(blurCount);
}

void FabiEngine3D::gfx_setBloomType(BloomType type)
{
	_core->_renderBus.setBloomType(type);
}

void FabiEngine3D::gfx_setSkyExposureIntensity(float intensity)
{
	_core->_skyEntityManager.setExposureIntensity(intensity);
}

void FabiEngine3D::gfx_setSkyExposureSpeed(float speed)
{
	_core->_skyEntityManager.setExposureSpeed(speed);
}

void FabiEngine3D::gfx_setDofMaxDistance(float maxDistance)
{
	_core->_renderBus.setDofMaxDistance(maxDistance);
}

void FabiEngine3D::gfx_setDofBlurDistance(float blurDistance)
{
	_core->_renderBus.setDofBlurDistance(blurDistance);
}

void FabiEngine3D::gfx_setDofDynamic(bool isDynamic)
{
	_core->_renderBus.setDofDynamic(isDynamic);
}

void FabiEngine3D::gfx_setMotionBlurStrength(float strength)
{
	_core->_renderBus.setMotionBlurStrength(strength);
}

void FabiEngine3D::gfx_setLensFlareMap(const string& texturePath)
{
	_core->_renderBus.setLensFlareMap(_core->_textureLoader.getTexture2D(texturePath, false, false));
	_core->_renderBus.setLensFlareMapPath(texturePath);
}

void FabiEngine3D::gfx_setLensFlareIntensity(float intensity)
{
	_core->_renderBus.setLensFlareIntensity(intensity);
}

void FabiEngine3D::gfx_setLensFlareSensitivity(float size)
{
	_core->_renderBus.setLensFlareSensitivity(size);
}
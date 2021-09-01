#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gfx_setPlanarReflectionHeight(float height)
{
	_core->_renderBus.setPlanarReflectionHeight(height);
}

void FabiEngine3D::gfx_setBloomSize(unsigned int size)
{
	_core->_renderBus.setBloomSize(size);
}

void FabiEngine3D::gfx_setDofSize(unsigned int size)
{
	_core->_renderBus.setDofSize(size);
}

void FabiEngine3D::gfx_setMotionBlurSize(unsigned int size)
{
	_core->_renderBus.setMotionBlurSize(size);
}

void FabiEngine3D::gfx_setAnisotropicFilteringQuality(unsigned int quality)
{
	_core->_renderBus.setAnisotropicFilteringQuality(quality);
	_core->_textureLoader.reloadAnisotropicFiltering();
}

void FabiEngine3D::gfx_setReflectionQuality(unsigned int quality)
{
	_core->_renderBus.setReflectionQuality(quality);
	_core->_masterRenderer.reloadCubeReflectionCaptureBuffer();
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

void FabiEngine3D::gfx_enableAmbientLighting(Vec3 color, float intensity)
{
	if (_core->_renderBus.isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to enable ambient lighting: already enabled");
		return;
	}

	_core->_renderBus.setAmbientLightingEnabled(true);
	_core->_renderBus.setAmbientLightingColor(color);
	_core->_renderBus.setAmbientLightingIntensity(intensity);
}

void FabiEngine3D::gfx_enableDirectionalLighting(Vec3 position, Vec3 color, float intensity)
{
	if (_core->_renderBus.isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to enable directional lighting: already enabled");
		return;
	}

	_core->_renderBus.setDirectionalLightingEnabled(true);
	_core->_renderBus.setDirectionalLightingPosition(position);
	_core->_renderBus.setDirectionalLightingColor(color);
	_core->_renderBus.setDirectionalLightingIntensity(intensity);
}

void FabiEngine3D::gfx_enableSpotLighting(Vec3 color, float intensity, float angle, float distance)
{
	if (_core->_renderBus.isSpotLightingEnabled())
	{
		Logger::throwWarning("Tried to enable spot lighting: already enabled");
		return;
	}

	_core->_renderBus.setSpotLightingEnabled(true);
	_core->_renderBus.setSpotLightingColor(color);
	_core->_renderBus.setSpotLightingIntensity(intensity);
	_core->_renderBus.setMaxSpotLightingAngle(angle);
	_core->_renderBus.setMaxSpotLightingDistance(distance);
}

void FabiEngine3D::gfx_enableFog(float minDistance, float maxDistance, float thickness, Vec3 color)
{
	if (_core->_renderBus.isFogEnabled())
	{
		Logger::throwWarning("Tried to enable fog: already enabled");
		return;
	}

	_core->_renderBus.setFogEnabled(true);
	_core->_renderBus.setFogMinDistance(minDistance);
	_core->_renderBus.setFogMaxDistance(maxDistance);
	_core->_renderBus.setFogThickness(thickness);
	_core->_renderBus.setFogColor(color);
}

void FabiEngine3D::gfx_enableAntiAliasing()
{
	if (_core->_renderBus.isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to enable anti aliasing: already enabled");
		return;
	}

	_core->_renderBus.setAntiAliasingEnabled(true);
}

void FabiEngine3D::gfx_enableShadows(Vec3 eye, Vec3 center, float size, float reach, float lightness, bool isFollowingCamera, unsigned int interval)
{
	if (_core->_renderBus.isShadowsEnabled())
	{
		Logger::throwWarning("Tried to enable shadows: already enabled");
		return;
	}

	_core->_shadowGenerator.loadShadows(eye, center, size, reach, isFollowingCamera, interval);
	_core->_renderBus.setShadowsEnabled(true);
	_core->_renderBus.setShadowLightness(lightness);
}

void FabiEngine3D::gfx_enableBloom(BloomType type, float intensity, unsigned int blurCount)
{
	if (_core->_renderBus.isBloomEnabled())
	{
		Logger::throwWarning("Tried to enable bloom: already enabled");
		return;
	}

	_core->_renderBus.setBloomEnabled(true);
	_core->_renderBus.setBloomType(type);
	_core->_renderBus.setBloomIntensity(intensity);
	_core->_renderBus.setBloomBlurCount(blurCount);
}

void FabiEngine3D::gfx_enableSkyExposure(float factor, float speed)
{
	if (_core->_renderBus.isSkyExposureEnabled())
	{
		Logger::throwWarning("Tried to enable sky exposure: already enabled");
		return;
	}

	_core->_renderBus.setSkyExposureEnabled(true);
	_core->_skyEntityManager.setExposureFactor(factor);
	_core->_skyEntityManager.setExposureSpeed(speed);
}

void FabiEngine3D::gfx_enableDOF(bool dynamic, float maxDistance, float blurDistance)
{
	if (_core->_renderBus.isDofEnabled())
	{
		Logger::throwWarning("Tried to enable DOF: already enabled");
		return;
	}

	_core->_renderBus.setDofEnabled(true);
	_core->_renderBus.setDofDynamic(dynamic);
	_core->_renderBus.setDofMaxDistance(maxDistance);
	_core->_renderBus.setDofBlurDistance(blurDistance);
}

void FabiEngine3D::gfx_enableMotionBlur(float strength)
{
	if (_core->_renderBus.isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to enable motion blur: already enabled");
		return;
	}
	
	_core->_renderBus.setMotionBlurEnabled(true);
	_core->_renderBus.setMotionBlurStrength(strength);
}

void FabiEngine3D::gfx_enableLensFlare(const string& texturePath, float intensity, float multiplier)
{
	if (_core->_renderBus.isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to enable lens flare: already enabled");
		return;
	}

	_core->_renderBus.setLensFlareEnabled(true);
	_core->_renderBus.setLensFlareMap(_core->_textureLoader.getTexture2D(texturePath, false, false));
	_core->_renderBus.setLensFlareMapPath(texturePath);
	_core->_renderBus.setLensFlareIntensity(intensity);
	_core->_renderBus.setLensFlareMultiplier(multiplier);
}

void FabiEngine3D::gfx_disableAmbientLighting(bool resetProperties)
{
	if (!_core->_renderBus.isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to disable ambient lighting: not enabled");
		return;
	}

	_core->_renderBus.setAmbientLightingEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setAmbientLightingColor(1.0f);
		_core->_renderBus.setAmbientLightingIntensity(1.0f);
	}
}

void FabiEngine3D::gfx_disableDirectionalLighting(bool resetProperties)
{
	if (!_core->_renderBus.isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to disable directional lighting: not enabled");
		return;
	}

	_core->_renderBus.setDirectionalLightingEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setDirectionalLightingPosition(Vec3(0.0f));
		_core->_renderBus.setDirectionalLightingColor(1.0f);
		_core->_renderBus.setDirectionalLightingIntensity(1.0f);
	}
}

void FabiEngine3D::gfx_disableSpotLighting(bool resetProperties)
{
	if (!_core->_renderBus.isSpotLightingEnabled())
	{
		Logger::throwWarning("Tried to disable spot lighting: not enabled");
		return;
	}

	_core->_renderBus.setSpotLightingEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setSpotLightingColor(Vec3(1.0f));
		_core->_renderBus.setSpotLightingIntensity(1.0f);
		_core->_renderBus.setMaxSpotLightingAngle(0.0f);
		_core->_renderBus.setMaxSpotLightingDistance(0.0f);
	}
}

void FabiEngine3D::gfx_disableFog(bool resetProperties)
{
	if (!_core->_renderBus.isFogEnabled())
	{
		Logger::throwWarning("Tried to disable fog: not enabled");
		return;
	}

	_core->_renderBus.setFogEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setFogMinDistance(0.0f);
		_core->_renderBus.setFogMaxDistance(0.0f);
		_core->_renderBus.setFogThickness(0.0f);
		_core->_renderBus.setFogColor(Vec3(0.0f));
	}
}

void FabiEngine3D::gfx_disableAntiAliasing(bool resetProperties)
{
	if (!_core->_renderBus.isAntiAliasingEnabled())
	{
		Logger::throwWarning("Tried to disable anti aliasing: not enabled");
		return;
	}

	_core->_renderBus.setAntiAliasingEnabled(false);
}

void FabiEngine3D::gfx_disableShadows(bool resetProperties)
{
	if (!_core->_renderBus.isShadowsEnabled())
	{
		Logger::throwWarning("Tried to disable shadows: not enabled");
		return;
	}

	_core->_renderBus.setShadowsEnabled(false);

	if (resetProperties)
	{
		_core->_shadowGenerator.unloadShadows();
		_core->_renderBus.setShadowLightness(0.0f);
	}
}

void FabiEngine3D::gfx_disableBloom(bool resetProperties)
{
	if (!_core->_renderBus.isBloomEnabled())
	{
		Logger::throwWarning("Tried to disable bloom: not enabled");
		return;
	}

	_core->_renderBus.setBloomEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setBloomType(BloomType());
		_core->_renderBus.setBloomIntensity(0.0f);
		_core->_renderBus.setBloomBlurCount(0);
	}
}

void FabiEngine3D::gfx_disableSkyExposure(bool resetProperties)
{
	if (!_core->_renderBus.isSkyExposureEnabled())
	{
		Logger::throwWarning("Tried to disable sky exposure: not enabled");
		return;
	}

	_core->_renderBus.setSkyExposureEnabled(false);

	if (resetProperties)
	{
		_core->_skyEntityManager.setExposureFactor(0.0f);
	}
}

void FabiEngine3D::gfx_disableDOF(bool resetProperties)
{
	if (!_core->_renderBus.isDofEnabled())
	{
		Logger::throwWarning("Tried to disable DOF: not enabled");
		return;
	}

	_core->_renderBus.setDofEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setDofDynamic(false);
		_core->_renderBus.setDofMaxDistance(0.0f);
		_core->_renderBus.setDofBlurDistance(0.0f);
	}
}

void FabiEngine3D::gfx_disableMotionBlur(bool resetProperties)
{
	if (!_core->_renderBus.isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to disable motion blur: not enabled");
		return;
	}

	_core->_renderBus.setMotionBlurEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setMotionBlurStrength(0.0f);
	}
}

void FabiEngine3D::gfx_disableLensFlare(bool resetProperties)
{
	if (!_core->_renderBus.isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to disable lens flare: not enabled");
		return;
	}

	_core->_renderBus.setLensFlareEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setLensFlareMap(0);
		_core->_renderBus.setLensFlareMapPath("");
		_core->_renderBus.setLensFlareIntensity(0.0f);
		_core->_renderBus.setLensFlareMultiplier(0.0f);
	}
}
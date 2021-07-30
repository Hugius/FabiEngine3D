#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gfx_setSceneReflectionHeight(float height)
{
	_core->_renderBus.setSceneReflectionHeight(height);
}

void FabiEngine3D::gfx_setAnisotropicFilteringQuality(int quality)
{
	_core->_renderBus.setAnisotropicFilteringQuality(quality);
	_core->_textureLoader.reloadAnisotropicFiltering();
}

void FabiEngine3D::gfx_setShadowQuality(int quality)
{
	_core->_renderBus.setShadowQuality(quality);
	_core->_masterRenderer.reloadShadowFramebuffer();
}

void FabiEngine3D::gfx_setReflectionQuality(int quality)
{
	_core->_renderBus.setReflectionQuality(quality);
	_core->_masterRenderer.reloadSceneReflectionFramebuffer();
	_core->_masterRenderer.reloadWaterReflectionFramebuffer();
}

void FabiEngine3D::gfx_setRefractionQuality(int quality)
{
	_core->_renderBus.setRefractionQuality(quality);
	_core->_masterRenderer.reloadWaterRefractionFramebuffer();
}

void FabiEngine3D::gfx_enableAmbientLighting(Vec3 color, float intensity)
{
	if (_core->_renderBus.isAmbientLightingEnabled())
	{
		Logger::throwWarning("Tried to enable ambient lighting: already enabled");
	}
	else
	{
		_core->_renderBus.setAmbientLightingEnabled(true);
		_core->_renderBus.setAmbientLightColor(color);
		_core->_renderBus.setAmbientLightIntensity(intensity);
	}
}

void FabiEngine3D::gfx_enableDirectionalLighting(Vec3 position, Vec3 color, float intensity)
{
	if (_core->_renderBus.isDirectionalLightingEnabled())
	{
		Logger::throwWarning("Tried to enable directional lighting: already enabled");
	}
	else
	{
		_core->_renderBus.setDirectionalLightingEnabled(true);
		_core->_renderBus.setDirectionalLightPosition(position);
		_core->_renderBus.setDirectionalLightColor(color);
		_core->_renderBus.setDirectionalLightIntensity(intensity);
	}
}

void FabiEngine3D::gfx_enableSpecularLighting()
{
	if (_core->_renderBus.isSpecularLightingEnabled())
	{
		Logger::throwWarning("Tried to enable specular lighting: already enabled");
	}
	else
	{
		_core->_renderBus.setSpecularLightingEnabled(true);
	}
}

void FabiEngine3D::gfx_enablePointLighting()
{
	if (_core->_renderBus.isPointLightingEnabled())
	{
		Logger::throwWarning("Tried to enable point lighting: already enabled");
	}
	else
	{
		_core->_renderBus.setPointLightingEnabled(true);
	}
}

void FabiEngine3D::gfx_enableSpotLighting(Vec3 color, float intensity, float angle, float distance)
{
	if (_core->_renderBus.isSpotLightingEnabled())
	{
		Logger::throwWarning("Tried to enable spot lighting: already enabled");
	}
	else
	{
		_core->_renderBus.setSpotLightingEnabled(true);
		_core->_renderBus.setSpotLightColor(color);
		_core->_renderBus.setSpotLightIntensity(intensity);
		_core->_renderBus.setMaxSpotLightAngle(angle);
		_core->_renderBus.setMaxSpotLightDistance(distance);
	}
}

void FabiEngine3D::gfx_enableFog(float minDistance, float maxDistance, float thickness, Vec3 color)
{
	if (_core->_renderBus.isFogEnabled())
	{
		Logger::throwWarning("Tried to enable fog: already enabled");
	}
	else
	{
		_core->_renderBus.setFogEnabled(true);
		_core->_renderBus.setFogMinDistance(minDistance);
		_core->_renderBus.setFogMaxDistance(maxDistance);
		_core->_renderBus.setFogThickness(thickness);
		_core->_renderBus.setFogColor(color);
	}
}

void FabiEngine3D::gfx_enableFXAA()
{
	if (_core->_renderBus.isFxaaEnabled())
	{
		Logger::throwWarning("Tried to enable FXAA: already enabled");
	}
	else
	{
		_core->_renderBus.setFxaaEnabled(true);
	}
}

void FabiEngine3D::gfx_enableShadows(Vec3 eye, Vec3 center, float size, float reach, float lightness, bool isFollowingCamera, bool isLighted, unsigned int interval)
{
	if (_core->_renderBus.isShadowsEnabled())
	{
		Logger::throwWarning("Tried to enable shadows: already enabled");
	}
	else
	{
		_core->_shadowGenerator.loadShadows(eye, center, size, reach, isFollowingCamera, interval);
		_core->_renderBus.setShadowsEnabled(true);
		_core->_renderBus.setShadowLightness(lightness);
		_core->_renderBus.setLightedShadowingEnabled(isLighted);
	}
}

void FabiEngine3D::gfx_enableBloom(BloomType type, float intensity, unsigned int blurCount)
{
	if (_core->_renderBus.isBloomEnabled())
	{
		Logger::throwWarning("Tried to enable bloom: already enabled");
	}
	else
	{
		_core->_renderBus.setBloomEnabled(true);
		_core->_renderBus.setBloomType(type);
		_core->_renderBus.setBloomIntensity(intensity);
		_core->_renderBus.setBloomBlurCount(blurCount);
	}
}

void FabiEngine3D::gfx_enableSkyExposure(float factor, float speed)
{
	if (_core->_renderBus.isSkyExposureEnabled())
	{
		Logger::throwWarning("Tried to enable sky exposure: already enabled");
	}
	else
	{
		_core->_renderBus.setSkyExposureEnabled(true);
		_core->_skyEntityManager.setExposureFactor(factor);
		_core->_skyEntityManager.setExposureSpeed(speed);
	}
}

void FabiEngine3D::gfx_enableDOF(bool dynamic, float maxDistance, float blurDistance)
{
	if (_core->_renderBus.isDofEnabled())
	{
		Logger::throwWarning("Tried to enable DOF: already enabled");
	}
	else
	{
		_core->_renderBus.setDofEnabled(true);
		_core->_renderBus.setDofDynamic(dynamic);
		_core->_renderBus.setDofMaxDistance(maxDistance);
		_core->_renderBus.setDofBlurDistance(blurDistance);
	}
}

void FabiEngine3D::gfx_enableMotionBlur(float strength)
{
	if (_core->_renderBus.isMotionBlurEnabled())
	{
		Logger::throwWarning("Tried to enable motion blur: already enabled");
	}
	else
	{
		_core->_renderBus.setMotionBlurEnabled(true);
		_core->_renderBus.setMotionBlurStrength(strength);
	}
}

void FabiEngine3D::gfx_enableLensFlare(const string& texturePath, float intensity, float multiplier)
{
	if (_core->_renderBus.isLensFlareEnabled())
	{
		Logger::throwWarning("Tried to enable lens flare: already enabled");
	}
	else
	{
		_core->_renderBus.setLensFlareEnabled(true);
		_core->_renderBus.setLensFlareMap(_core->_textureLoader.getTexture2D(texturePath, false, false));
		_core->_renderBus.setLensFlareMapPath(texturePath);
		_core->_renderBus.setLensFlareIntensity(intensity);
		_core->_renderBus.setLensFlareMultiplier(multiplier);
	}
}

void FabiEngine3D::gfx_disableAmbientLighting(bool resetProperties)
{
	if (_core->_renderBus.isAmbientLightingEnabled())
	{
		_core->_renderBus.setAmbientLightingEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setAmbientLightColor(0.0f);
			_core->_renderBus.setAmbientLightIntensity(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable ambient lighting: not enabled");
	}
}

void FabiEngine3D::gfx_disableDirectionalLighting(bool resetProperties)
{
	if (_core->_renderBus.isDirectionalLightingEnabled())
	{
		_core->_renderBus.setDirectionalLightingEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setDirectionalLightPosition(Vec3(0.0f));
			_core->_renderBus.setDirectionalLightColor(0.0f);
			_core->_renderBus.setDirectionalLightIntensity(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable directional lighting: not enabled");
	}
}

void FabiEngine3D::gfx_disableSpecularLighting(bool resetProperties)
{
	if (_core->_renderBus.isSpecularLightingEnabled())
	{
		_core->_renderBus.setSpecularLightingEnabled(false);
	}
	else
	{
		Logger::throwWarning("Tried to disable specular lighting: not enabled");
	}
}

void FabiEngine3D::gfx_disablePointLighting(bool resetProperties)
{
	if (_core->_renderBus.isPointLightingEnabled())
	{
		_core->_renderBus.setPointLightingEnabled(false);
	}
	else
	{
		Logger::throwWarning("Tried to disable point lighting: not enabled");
	}
}

void FabiEngine3D::gfx_disableSpotLighting(bool resetProperties)
{
	if (_core->_renderBus.isSpotLightingEnabled())
	{
		_core->_renderBus.setSpotLightingEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setSpotLightColor(Vec3(0.0f));
			_core->_renderBus.setSpotLightIntensity(0.0f);
			_core->_renderBus.setMaxSpotLightAngle(0.0f);
			_core->_renderBus.setMaxSpotLightDistance(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable spot lighting: not enabled");
	}
}

void FabiEngine3D::gfx_disableFog(bool resetProperties)
{
	if (_core->_renderBus.isFogEnabled())
	{
		_core->_renderBus.setFogEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setFogMinDistance(0.0f);
			_core->_renderBus.setFogMaxDistance(0.0f);
			_core->_renderBus.setFogThickness(0.0f);
			_core->_renderBus.setFogColor(Vec3(0.0f));
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable fog: not enabled");
	}
}

void FabiEngine3D::gfx_disableFXAA(bool resetProperties)
{
	if (_core->_renderBus.isFxaaEnabled())
	{
		_core->_renderBus.setFxaaEnabled(false);
	}
	else
	{
		Logger::throwWarning("Tried to disable FXAA: not enabled");
	}
}

void FabiEngine3D::gfx_disableShadows(bool resetProperties)
{
	if (_core->_renderBus.isShadowsEnabled())
	{
		_core->_renderBus.setShadowsEnabled(false);

		if (resetProperties)
		{
			_core->_shadowGenerator.unloadShadows();
			_core->_renderBus.setShadowLightness(0.0f);
			_core->_renderBus.setLightedShadowingEnabled(false);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable shadows: not enabled");
	}
}

void FabiEngine3D::gfx_disableBloom(bool resetProperties)
{
	if (_core->_renderBus.isBloomEnabled())
	{
		_core->_renderBus.setBloomEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setBloomType(BloomType());
			_core->_renderBus.setBloomIntensity(0.0f);
			_core->_renderBus.setBloomBlurCount(0);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable bloom: not enabled");
	}
}

void FabiEngine3D::gfx_disableSkyExposure(bool resetProperties)
{
	if (_core->_renderBus.isSkyExposureEnabled())
	{
		_core->_renderBus.setSkyExposureEnabled(false);

		if (resetProperties)
		{
			_core->_skyEntityManager.setExposureFactor(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable sky exposure: not enabled");
	}
}

void FabiEngine3D::gfx_disableDOF(bool resetProperties)
{
	if (_core->_renderBus.isDofEnabled())
	{
		_core->_renderBus.setDofEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setDofDynamic(false);
			_core->_renderBus.setDofMaxDistance(0.0f);
			_core->_renderBus.setDofBlurDistance(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable DOF: not enabled");
	}
}

void FabiEngine3D::gfx_disableMotionBlur(bool resetProperties)
{
	if (_core->_renderBus.isMotionBlurEnabled())
	{
		_core->_renderBus.setMotionBlurEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setMotionBlurStrength(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable motion blur: not enabled");
	}
}

void FabiEngine3D::gfx_disableLensFlare(bool resetProperties)
{
	if (_core->_renderBus.isLensFlareEnabled())
	{
		_core->_renderBus.setLensFlareEnabled(false);

		if (resetProperties)
		{
			_core->_renderBus.setLensFlareMap(0);
			_core->_renderBus.setLensFlareMapPath("");
			_core->_renderBus.setLensFlareIntensity(0.0f);
			_core->_renderBus.setLensFlareMultiplier(0.0f);
		}
	}
	else
	{
		Logger::throwWarning("Tried to disable lens flare: not enabled");
	}
}
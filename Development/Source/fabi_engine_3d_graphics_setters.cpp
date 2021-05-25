#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gfx_enableAmbientLighting(Vec3 color, float intensity)
{
	_core->_renderBus.setAmbientLightingEnabled(true);
	_core->_renderBus.setAmbientLightColor(color);
	_core->_renderBus.setAmbientLightIntensity(intensity);
}

void FabiEngine3D::gfx_enableDirectionalLighting(Vec3 position, Vec3 color, float intensity)
{
	_core->_renderBus.setDirectionalLightingEnabled(true);
	_core->_renderBus.setDirectionalLightPosition(position);
	_core->_renderBus.setDirectionalLightColor(color);
	_core->_renderBus.setDirectionalLightIntensity(intensity);
}

void FabiEngine3D::gfx_enableSpecularLighting()
{
	_core->_renderBus.setSpecularLightingEnabled(true);
}

void FabiEngine3D::gfx_enablePointLighting()
{
	_core->_renderBus.setPointLightingEnabled(true);
}

void FabiEngine3D::gfx_enableSpotLighting(Vec3 color, float intensity, float angle, float distance)
{
	_core->_renderBus.setSpotLightingEnabled(true);
	_core->_renderBus.setSpotLightColor(color);
	_core->_renderBus.setSpotLightIntensity(intensity);
	_core->_renderBus.setMaxSpotLightAngle(angle);
	_core->_renderBus.setMaxSpotLightDistance(distance);
}

void FabiEngine3D::gfx_enableFog(float minDistance, float maxDistance, float thickness, Vec3 color)
{
	_core->_renderBus.setFogEnabled(true);
	_core->_renderBus.setFogMinDistance(minDistance);
	_core->_renderBus.setFogMaxDistance(maxDistance);
	_core->_renderBus.setFogThickness(thickness);
	_core->_renderBus.setFogColor(color);
}

void FabiEngine3D::gfx_enableSkyReflections(float factor)
{
	_core->_renderBus.setSkyReflectionsEnabled(true);
	_core->_renderBus.setSkyReflectionMixValue(factor);
}

void FabiEngine3D::gfx_enableSceneReflections(float factor)
{
	_core->_renderBus.setSceneReflectionsEnabled(true);
	_core->_renderBus.setSceneReflectionMixValue(factor);
}

void FabiEngine3D::gfx_enableLightMapping()
{
	_core->_renderBus.setLightMappingEnabled(true);
}

void FabiEngine3D::gfx_enableNormalMapping()
{
	_core->_renderBus.setNormalMappingEnabled(true);
}

void FabiEngine3D::gfx_enableMSAA()
{
	_core->_renderBus.setMsaaEnabled(true);
}

void FabiEngine3D::gfx_enableShadows(Vec3 eye, Vec3 center, float size, float reach, float lightness, bool followingCamera, bool softShadowing, int interval)
{
	_core->_shadowGenerator.loadShadows(eye, center, size, reach, followingCamera, interval);
	_core->_renderBus.setShadowsEnabled(true);
	_core->_renderBus.setShadowLightness(lightness);
	_core->_renderBus.setSoftShadowingEnabled(softShadowing);
}

void FabiEngine3D::gfx_enableBloom(float intensity, float brightnessTreshold, int blurSize)
{
	_core->_renderBus.setBloomEnabled(true);
	_core->_renderBus.setBloomIntensity(intensity);
	_core->_renderBus.setBloomBrightnessTreshold(brightnessTreshold);
	_core->_renderBus.setBloomBlurSize(blurSize);
}

void FabiEngine3D::gfx_enableWaterEffects()
{
	_core->_renderBus.setWaterEffectsEnabled(true);
}

void FabiEngine3D::gfx_enableSkyHDR(float brightnessFactor)
{
	if (_core->_renderBus.isBloomEnabled())
	{
		_core->_renderBus.setSkyHdrEnabled(true);
		_core->_skyEntityManager.setBrightnessFactor(brightnessFactor);
	}
}

void FabiEngine3D::gfx_enableDOF(bool dynamic, float maxDistance, float blurDistance)
{
	_core->_renderBus.setDofEnabled(true);
	_core->_renderBus.setDofDynamic(dynamic);
	_core->_renderBus.setDofMaxDistance(maxDistance);
	_core->_renderBus.setDofBlurDistance(blurDistance);
}

void FabiEngine3D::gfx_enableMotionBlur(float strength)
{
	_core->_renderBus.setMotionBlurEnabled(true);
	_core->_renderBus.setMotionBlurStrength(strength);
}

void FabiEngine3D::gfx_enableLensFlare(const string& texturePath, float intensity, float multiplier)
{
	_core->_renderBus.setLensFlareEnabled(true);
	_core->_renderBus.setLensFlareMap(_core->_textureLoader.getTexture2D(texturePath, false, false, false));
	_core->_renderBus.setLensFlareMapPath(texturePath);
	_core->_renderBus.setLensFlareIntensity(intensity);
	_core->_renderBus.setLensFlareMultiplier(multiplier);
}

void FabiEngine3D::gfx_disableAmbientLighting(bool resetProperties)
{
	_core->_renderBus.setAmbientLightingEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setAmbientLightColor(0.0f);
		_core->_renderBus.setAmbientLightIntensity(0.0f);
	}
}

void FabiEngine3D::gfx_disableDirectionalLighting(bool resetProperties)
{
	_core->_renderBus.setDirectionalLightingEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setDirectionalLightPosition(Vec3(0.0f));
		_core->_renderBus.setDirectionalLightColor(0.0f);
		_core->_renderBus.setDirectionalLightIntensity(0.0f);
	}
}

void FabiEngine3D::gfx_disableSpecularLighting(bool resetProperties)
{
	_core->_renderBus.setSpecularLightingEnabled(false);
}

void FabiEngine3D::gfx_disablePointLighting(bool resetProperties)
{
	_core->_renderBus.setPointLightingEnabled(false);
}

void FabiEngine3D::gfx_disableSpotLighting(bool resetProperties)
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

void FabiEngine3D::gfx_disableFog(bool resetProperties)
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

void FabiEngine3D::gfx_disableSkyReflections(bool resetProperties)
{
	_core->_renderBus.setSkyReflectionsEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setSkyReflectionMixValue(0.0f);
	}
}

void FabiEngine3D::gfx_disableSceneReflections(bool resetProperties)
{
	_core->_renderBus.setSceneReflectionsEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setSceneReflectionMixValue(0.0f);
	}
}

void FabiEngine3D::gfx_disableLightMapping(bool resetProperties)
{
	_core->_renderBus.setLightMappingEnabled(false);
}

void FabiEngine3D::gfx_disableNormalMapping(bool resetProperties)
{
	_core->_renderBus.setNormalMappingEnabled(false);
}

void FabiEngine3D::gfx_disableMSAA(bool resetProperties)
{
	_core->_renderBus.setMsaaEnabled(false);
}

void FabiEngine3D::gfx_disableShadows(bool resetProperties)
{
	_core->_renderBus.setShadowsEnabled(false);

	if (resetProperties)
	{
		_core->_shadowGenerator.unloadShadows();
		_core->_renderBus.setShadowLightness(0.0f);
		_core->_renderBus.setSoftShadowingEnabled(false);
	}
}

void FabiEngine3D::gfx_disableBloom(bool resetProperties)
{
	_core->_renderBus.setBloomEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setBloomIntensity(0.0f);
		_core->_renderBus.setBloomBrightnessTreshold(0.0f);
		_core->_renderBus.setBloomBlurSize(0);
	}
}

void FabiEngine3D::gfx_disableWaterEffects(bool resetProperties)
{
	_core->_renderBus.setWaterEffectsEnabled(false);
}

void FabiEngine3D::gfx_disableSkyHDR(bool resetProperties)
{
	_core->_renderBus.setSkyHdrEnabled(false);

	if (resetProperties)
	{
		_core->_skyEntityManager.setBrightnessFactor(0.0f);
	}
}

void FabiEngine3D::gfx_disableDOF(bool resetProperties)
{
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
	_core->_renderBus.setMotionBlurEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setMotionBlurStrength(0.0f);
	}
}

void FabiEngine3D::gfx_disableLensFlare(bool resetProperties)
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
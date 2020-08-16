#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gfx_enableAmbientLighting(vec3 color, float intensity)
{
	_core->_renderBus.setAmbientLightingEnabled(true);
	_core->_renderBus.setAmbientLightColor(color);
	_core->_renderBus.setAmbientLightIntensity(intensity);
}

void FabiEngine3D::gfx_enableDirectionalLighting(vec3 position, vec3 color, float intensity)
{
	_core->_renderBus.setDirectionalLightingEnabled(true);
	_core->_renderBus.setDirectionalLightPos(position);
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

void FabiEngine3D::gfx_enableFog(float minDistance, vec3 color)
{
	_core->_renderBus.setFogEnabled(true);
	_core->_renderBus.setFogMinDistance(minDistance);
	_core->_renderBus.setFogColor(color);
}

void FabiEngine3D::gfx_enableSkyReflections(float factor)
{
	_core->_renderBus.setSkyReflectionsEnabled(true);
	_core->_renderBus.setSkyReflectionFactor(factor);
}

void FabiEngine3D::gfx_enableSceneReflections(float factor)
{
	// Check if water is already using reflection graphics
	if (!_core->_renderBus.isWaterEffectsEnabled())
	{
		_core->_renderBus.setSceneReflectionsEnabled(true);
		_core->_renderBus.setSceneReflectionFactor(factor);
	}
}

void FabiEngine3D::gfx_enableLightMapping()
{
	_core->_renderBus.setLightMappingEnabled(true);
}

void FabiEngine3D::gfx_enableMSAA()
{
	_core->_renderBus.setMsaaEnabled(true);
}

void FabiEngine3D::gfx_enableShadows(vec3 eye, vec3 center, float size, float reach)
{
	_core->_shadowManager.loadShadows(eye, center, size, reach);
	_core->_renderBus.setShadowsEnabled(true);
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

void FabiEngine3D::gfx_enableDOF(float minDistance)
{
	_core->_renderBus.setDofEnabled(true);
	_core->_renderBus.setDofMinDistance(minDistance);
}

void FabiEngine3D::gfx_enableMotionBlur()
{
	_core->_renderBus.setMotionBlurEnabled(true);
}

void FabiEngine3D::gfx_enableLensFlare(const string& texturePath, float intensity, float multiplier)
{
	_core->_renderBus.setLensFlareMap(_core->_texLoader.getTexture(texturePath, false, false));
	_core->_renderBus.setLensFlareEnabled(true);
	_core->_renderBus.setLensFlareIntensity(intensity);
	_core->_renderBus.setLensFlareMultiplier(multiplier);
}

void FabiEngine3D::gfx_disableAmbientLighting()
{
	_core->_renderBus.setAmbientLightingEnabled(false);
}

void FabiEngine3D::gfx_disableDirectionalLighting()
{
	_core->_renderBus.setDirectionalLightingEnabled(false);
}

void FabiEngine3D::gfx_disableSpecularLighting()
{
	_core->_renderBus.setSpecularLightingEnabled(false);
}

void FabiEngine3D::gfx_disablePointLighting()
{
	_core->_renderBus.setPointLightingEnabled(false);
}

void FabiEngine3D::gfx_disableFog()
{
	_core->_renderBus.setFogEnabled(false);
}

void FabiEngine3D::gfx_disableSkyReflections()
{
	_core->_renderBus.setSkyReflectionsEnabled(false);
}

void FabiEngine3D::gfx_disableSceneReflections()
{
	_core->_renderBus.setSceneReflectionsEnabled(false);
}

void FabiEngine3D::gfx_disableLightMapping()
{
	_core->_renderBus.setLightMappingEnabled(false);
}

void FabiEngine3D::gfx_disableMSAA()
{
	_core->_renderBus.setMsaaEnabled(false);
}

void FabiEngine3D::gfx_disableShadows()
{
	_core->_renderBus.setShadowsEnabled(false);
}

void FabiEngine3D::gfx_disableBloom()
{
	_core->_renderBus.setBloomEnabled(false);
}

void FabiEngine3D::gfx_disableWaterEffects()
{
	_core->_renderBus.setWaterEffectsEnabled(false);
}

void FabiEngine3D::gfx_disableSkyHDR()
{
	_core->_renderBus.setSkyHdrEnabled(false);
}

void FabiEngine3D::gfx_disableDOF()
{
	_core->_renderBus.setDofEnabled(false);
}

void FabiEngine3D::gfx_disableMotionBlur()
{
	_core->_renderBus.setMotionBlurEnabled(false);
}

void FabiEngine3D::gfx_disableLensFlare()
{
	_core->_renderBus.setLensFlareEnabled(false);
}

vec3 FabiEngine3D::gfx_getAmbientLightingColor()
{
	return _core->_renderBus.getAmbientLightingColor();
}

float FabiEngine3D::gfx_getAmbientLightingIntensity()
{
	return _core->_renderBus.getAmbientLightingIntensity();
}

float FabiEngine3D::gfx_geDirectionalLightingIntensity()
{
	return _core->_renderBus.getDirectionalLightingIntensity();
}

vec3 FabiEngine3D::gfx_getDirectionalLightingPosition()
{
	return _core->_renderBus.getDirectionalLightingPosition();
}

vec3 FabiEngine3D::gfx_getDirectionalLightingColor()
{
	return _core->_renderBus.getDirectionalLightingColor();
}

float FabiEngine3D::gfx_getFogMinDistance()
{
	return _core->_renderBus.getFogMinDistance();
}

vec3 FabiEngine3D::gfx_getFogColor()
{
	return _core->_renderBus.getFogColor();
}

float FabiEngine3D::gfx_getSkyReflectionFactor()
{
	return _core->_renderBus.getSkyReflectionFactor();
}

float FabiEngine3D::gfx_getSceneReflectionHeight()
{
	return _core->_renderBus.getSceneReflectionHeight();
}

float FabiEngine3D::gfx_getSceneReflectionFactor()
{
	return _core->_renderBus.getSceneReflectionFactor();
}

vec3 FabiEngine3D::gfx_getShadowEyePosition()
{
	return _core->_renderBus.getShadowEyePosition();
}

vec3 FabiEngine3D::gfx_getShadowCenter()
{
	return _core->_renderBus.getShadowAreaCenter();
}

float FabiEngine3D::gfx_getShadowSize()
{
	return _core->_renderBus.getShadowAreaSize();
}

float FabiEngine3D::gfx_getShadowReach()
{
	return _core->_renderBus.getShadowAreaReach();
}

float FabiEngine3D::gfx_getBloomIntensity()
{
	return _core->_renderBus.getBloomIntensity();
}

float FabiEngine3D::gfx_getBloomBrightnessTreshold()
{
	return _core->_renderBus.getBloomBrightnessTreshold();
}

int FabiEngine3D::gfx_getBloomBlurSize()
{
	return _core->_renderBus.getBloomBlurSize();
}

float FabiEngine3D::gfx_getSkyHdrBrightnessFactor()
{
	return _core->_skyEntityManager.getBrightnessFactor();
}

float FabiEngine3D::gfx_getDofMinDistance()
{
	return _core->_renderBus.getDofMinDistance();
}

float FabiEngine3D::gfx_getLensFlareIntensity()
{
	return _core->_renderBus.getLensFlareIntensity();
}
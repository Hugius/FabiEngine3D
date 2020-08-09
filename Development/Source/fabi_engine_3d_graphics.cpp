#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::gfx_enableAmbientLighting(vec3 color, float intensity)
{
	_core->_shaderBus.setAmbientLightingEnabled(true);
	_core->_shaderBus.setAmbientLightColor(color);
	_core->_shaderBus.setAmbientLightIntensity(intensity);
}

void FabiEngine3D::gfx_enableDirectionalLighting(vec3 position, vec3 color, float intensity)
{
	_core->_shaderBus.setDirectionalLightingEnabled(true);
	_core->_shaderBus.setDirectionalLightPos(position);
	_core->_shaderBus.setDirectionalLightColor(color);
	_core->_shaderBus.setDirectionalLightIntensity(intensity);
}

void FabiEngine3D::gfx_enableSpecularLighting(float intensity)
{
	_core->_shaderBus.setSpecularLightingEnabled(true);
	_core->_shaderBus.setSpecularLightingIntensity(intensity);
}

void FabiEngine3D::gfx_enablePointLighting()
{
	_core->_shaderBus.setPointLightingEnabled(true);
}

void FabiEngine3D::gfx_enableFog(float minDistance, vec3 color)
{
	_core->_shaderBus.setFogEnabled(true);
	_core->_shaderBus.setFogMinDistance(minDistance);
	_core->_shaderBus.setFogColor(color);
}

void FabiEngine3D::gfx_enableSkyReflections(float factor)
{
	_core->_shaderBus.setSkyReflectionsEnabled(true);
	_core->_shaderBus.setSkyReflectionFactor(factor);
}

void FabiEngine3D::gfx_enableSceneReflections(float height, float factor)
{
	// Check if water is already using reflection graphics
	if (_core->_shaderBus.isWaterEffectsEnabled() && _core->_waterEntityManager.getSelectedWater() != nullptr)
	{
		Logger::getInst().throwWarning("Cannot enable screen reflection graphics; \"water effects\" is currently using it!");
	}
	else
	{
		_core->_shaderBus.setSceneReflectionsEnabled(true);
		_core->_shaderBus.setSceneReflectionHeight(height);
		_core->_shaderBus.setSceneReflectionFactor(factor);
	}

}

void FabiEngine3D::gfx_enableLightMapping()
{
	_core->_shaderBus.setLightMappingEnabled(true);
}

void FabiEngine3D::gfx_enableMSAA()
{
	_core->_shaderBus.setMsaaEnabled(true);
}

void FabiEngine3D::gfx_enableShadows(vec3 eye, vec3 center, float size, float reach)
{
	_core->_shadowManager.loadShadows(eye, center, size, reach);
	_core->_shaderBus.setShadowsEnabled(true);
}

void FabiEngine3D::gfx_enableBloom(float intensity, float brightnessTreshold, int blurSize)
{
	_core->_shaderBus.setBloomEnabled(true);
	_core->_shaderBus.setBloomIntensity(intensity);
	_core->_shaderBus.setBloomTreshold(brightnessTreshold);
	_core->_shaderBus.setBloomBlurSize(blurSize);
}

void FabiEngine3D::gfx_enableWaterEffects()
{
	_core->_shaderBus.setWaterEffectsEnabled(true);
}

void FabiEngine3D::gfx_enableSkyHDR(float brightnessFactor)
{
	if (_core->_shaderBus.isBloomEnabled())
	{
		_core->_shaderBus.setSkyHdrEnabled(true);
		_core->_skyEntityManager.setBrightnessFactor(brightnessFactor);
	}
}

void FabiEngine3D::gfx_enableDOF(float minDistance)
{
	_core->_shaderBus.setDofEnabled(true);
	_core->_shaderBus.setDofMinDistance(minDistance);
}

void FabiEngine3D::gfx_enableMotionBlur()
{
	_core->_shaderBus.setMotionBlurEnabled(true);
}

void FabiEngine3D::gfx_enableLensFlare(const string& texturePath, float intensity)
{
	_core->_shaderBus.setLensFlareMap(_core->_texLoader.getTexture(texturePath, false, false));
	_core->_shaderBus.setLensFlareEnabled(true);
	_core->_shaderBus.setLensFlareIntensity(intensity);
}

void FabiEngine3D::gfx_disableAmbientLighting()
{
	_core->_shaderBus.setAmbientLightingEnabled(false);
}

void FabiEngine3D::gfx_disableDirectionalLighting()
{
	_core->_shaderBus.setDirectionalLightingEnabled(false);
}

void FabiEngine3D::gfx_disableSpecularLighting()
{
	_core->_shaderBus.setSpecularLightingEnabled(false);
}

void FabiEngine3D::gfx_disablePointLighting()
{
	_core->_shaderBus.setPointLightingEnabled(false);
}

void FabiEngine3D::gfx_disableFog()
{
	_core->_shaderBus.setFogEnabled(false);
}

void FabiEngine3D::gfx_disableSkyReflections()
{
	_core->_shaderBus.setSkyReflectionsEnabled(false);
}

void FabiEngine3D::gfx_disableSceneReflections()
{
	_core->_shaderBus.setSceneReflectionsEnabled(false);
}

void FabiEngine3D::gfx_disableLightMapping()
{
	_core->_shaderBus.setLightMappingEnabled(false);
}

void FabiEngine3D::gfx_disableMSAA()
{
	_core->_shaderBus.setMsaaEnabled(false);
}

void FabiEngine3D::gfx_disableShadows()
{
	_core->_shaderBus.setShadowsEnabled(false);
}

void FabiEngine3D::gfx_disableBloom()
{
	_core->_shaderBus.setBloomEnabled(false);
}

void FabiEngine3D::gfx_disableWaterEffects()
{
	_core->_shaderBus.setWaterEffectsEnabled(false);
}

void FabiEngine3D::gfx_disableSkyHDR()
{
	_core->_shaderBus.setSkyHdrEnabled(false);
}

void FabiEngine3D::gfx_disableDOF()
{
	_core->_shaderBus.setDofEnabled(false);
}

void FabiEngine3D::gfx_disableMotionBlur()
{
	_core->_shaderBus.setMotionBlurEnabled(false);
}

void FabiEngine3D::gfx_disableLensFlare()
{
	_core->_shaderBus.setLensFlareEnabled(false);
}

vec3 FabiEngine3D::gfx_getAmbientLightingColor()
{
	return _core->_shaderBus.getAmbientLightingColor();
}

float FabiEngine3D::gfx_getAmbientLightingIntensity()
{
	return _core->_shaderBus.getAmbientLightingIntensity();
}

vec3 FabiEngine3D::gfx_getDirectionalLightingPosition()
{
	return _core->_shaderBus.getDirectionalLightingPosition();
}

vec3 FabiEngine3D::gfx_getDirectionalLightingColor()
{
	return _core->_shaderBus.getDirectionalLightingColor();
}

float FabiEngine3D::gfx_geDirectionalLightingIntensity()
{
	return _core->_shaderBus.getDirectionalLightingIntensity();
}

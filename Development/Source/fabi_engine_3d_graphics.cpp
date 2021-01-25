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

void FabiEngine3D::gfx_enableSpotLighting(Vec3 color, float intensity, float angle, float distance)
{
	_core->_renderBus.setSpotLightingEnabled(true);
	_core->_renderBus.setSpotLightColor(color);
	_core->_renderBus.setSpotLightIntensity(intensity);
	_core->_renderBus.setMaxSpotLightAngle(angle);
	_core->_renderBus.setMaxSpotLightDistance(distance);
}

void FabiEngine3D::gfx_enableFog(float minDistance, float maxDistance, float defaultFactor, Vec3 color)
{
	_core->_renderBus.setFogEnabled(true);
	_core->_renderBus.setFogMinDistance(minDistance);
	_core->_renderBus.setFogMaxDistance(maxDistance);
	_core->_renderBus.setFogDefaultFactor(defaultFactor);
	_core->_renderBus.setFogColor(color);
}

void FabiEngine3D::gfx_enableSkyReflections(float factor)
{
	_core->_renderBus.setSkyReflectionsEnabled(true);
	_core->_renderBus.setSkyReflectionFactor(factor);
}

void FabiEngine3D::gfx_enableSceneReflections(float factor)
{
	_core->_renderBus.setSceneReflectionsEnabled(true);
	_core->_renderBus.setSceneReflectionFactor(factor);
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

void FabiEngine3D::gfx_enableShadows(Vec3 eye, Vec3 center, float size, float reach, bool followingCamera, int interval)
{
	_core->_shadowManager.loadShadows(eye, center, size, reach, followingCamera, interval);
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
		_core->_renderBus.setDirectionalLightPos(Vec3(0.0f));
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
		_core->_renderBus.setFogDefaultFactor(0.0f);
		_core->_renderBus.setFogColor(Vec3(0.0f));
	}
}

void FabiEngine3D::gfx_disableSkyReflections(bool resetProperties)
{
	_core->_renderBus.setSkyReflectionsEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setSkyReflectionFactor(0.0f);
	}
}

void FabiEngine3D::gfx_disableSceneReflections(bool resetProperties)
{
	_core->_renderBus.setSceneReflectionsEnabled(false);

	if (resetProperties)
	{
		_core->_renderBus.setSceneReflectionFactor(0.0f);
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
		_core->_shadowManager.unloadShadows();
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
	_core->_skyEntityManager.setBrightnessFactor(0.0f);
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

bool FabiEngine3D::gfx_isMsaaEnabled()
{
	return _core->_renderBus.isMsaaEnabled();
}

bool FabiEngine3D::gfx_isAmbientLightingEnabled()
{
	return _core->_renderBus.isAmbientLightingEnabled();
}

bool FabiEngine3D::gfx_isDirectionalLightingEnabled()
{
	return _core->_renderBus.isDirectionalLightingEnabled();
}

bool FabiEngine3D::gfx_isSpecularLightingEnabled()
{
	return _core->_renderBus.isSpecularLightingEnabled();
}

bool FabiEngine3D::gfx_isPointLightingEnabled()
{
	return _core->_renderBus.isPointLightingEnabled();
}

bool FabiEngine3D::gfx_isSpotLightingEnabled()
{
	return _core->_renderBus.isSpotLightingEnabled();
}

bool FabiEngine3D::gfx_isFogEnabled()
{
	return _core->_renderBus.isFogEnabled();
}

bool FabiEngine3D::gfx_isLightMappingEnabled()
{
	return _core->_renderBus.isLightMappingEnabled();
}

bool FabiEngine3D::gfx_isNormalMappingEnabled()
{
	return _core->_renderBus.isNormalMappingEnabled();
}

bool FabiEngine3D::gfx_isSkyReflectionsEnabled()
{
	return _core->_renderBus.isSkyReflectionsEnabled();
}

bool FabiEngine3D::gfx_isSceneReflectionsEnabled()
{
	return _core->_renderBus.isSceneReflectionsEnabled();
}

bool FabiEngine3D::gfx_isBloomEnabled()
{
	return _core->_renderBus.isBloomEnabled();
}

bool FabiEngine3D::gfx_isWaterEffectsEnabled()
{
	return _core->_renderBus.isWaterEffectsEnabled();
}

bool FabiEngine3D::gfx_isSkyHdrEnabled()
{
	return _core->_renderBus.isSkyHdrEnabled();
}

bool FabiEngine3D::gfx_isShadowsEnabled()
{
	return _core->_renderBus.isShadowsEnabled();
}

bool FabiEngine3D::gfx_isDofEnabled()
{
	return _core->_renderBus.isDofEnabled();
}

bool FabiEngine3D::gfx_isDofDynamic()
{
	return _core->_renderBus.isDofDynamic();
}

bool FabiEngine3D::gfx_isMotionBlurEnabled()
{
	return _core->_renderBus.isMotionBlurEnabled();
}

bool FabiEngine3D::gfx_isLensFlareEnabled()
{
	return _core->_renderBus.isLensFlareEnabled();
}

int FabiEngine3D::gfx_getMsaaQuality()
{
	return _core->_renderBus.getMsaaSampleCount();
}

int FabiEngine3D::gfx_getShadowQuality()
{
	return _core->_renderBus.getShadowMapSize();
}

int FabiEngine3D::gfx_getReflectionQuality()
{
	return _core->_renderBus.getSceneReflectionMapSize();
}

int FabiEngine3D::gfx_getRefractionQuality()
{
	return _core->_renderBus.getSceneRefractionMapSize();
}

Vec3 FabiEngine3D::gfx_getAmbientLightingColor()
{
	return _core->_renderBus.getAmbientLightColor();
}

float FabiEngine3D::gfx_getAmbientLightingIntensity()
{
	return _core->_renderBus.getAmbientLightIntensity();
}

float FabiEngine3D::gfx_getDirectionalLightingIntensity()
{
	return _core->_renderBus.getDirectionalLightIntensity();
}

float FabiEngine3D::gfx_getSpotLightingIntensity()
{
	return _core->_renderBus.getSpotLightIntensity();
}

float FabiEngine3D::gfx_getSpotLightingAngle()
{
	return _core->_renderBus.getMaxSpotLightAngle();
}

float FabiEngine3D::gfx_getSpotLightingDistance()
{
	return _core->_renderBus.getMaxSpotLightDistance();
}

Vec3 FabiEngine3D::gfx_getDirectionalLightingPosition()
{
	return _core->_renderBus.getDirectionalLightPosition();
}

Vec3 FabiEngine3D::gfx_getDirectionalLightingColor()
{
	return _core->_renderBus.getDirectionalLightColor();
}

Vec3 FabiEngine3D::gfx_getSpotLightingColor()
{
	return _core->_renderBus.getSpotLightColor();
}

float FabiEngine3D::gfx_getFogMinDistance()
{
	return _core->_renderBus.getFogMinDistance();
}

float FabiEngine3D::gfx_getFogMaxDistance()
{
	return _core->_renderBus.getFogMaxDistance();
}

float FabiEngine3D::gfx_getFogDefaultFactor()
{
	return _core->_renderBus.getFogDefaultFactor();
}

Vec3 FabiEngine3D::gfx_getFogColor()
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

Vec3 FabiEngine3D::gfx_getShadowEyePosition()
{
	return _core->_shadowManager.getEye();
}

Vec3 FabiEngine3D::gfx_getShadowCenter()
{
	return _core->_shadowManager.getCenter();
}

string FabiEngine3D::gfx_getLensFlareMapPath()
{
	return _core->_renderBus.getLensFlareMapPath();
}

float FabiEngine3D::gfx_getShadowSize()
{
	return _core->_shadowManager.getSize();
}

float FabiEngine3D::gfx_getShadowReach()
{
	return _core->_shadowManager.getReach();
}

bool FabiEngine3D::gfx_isShadowFollowingCamera()
{
	return _core->_shadowManager.isFollowingCamera();
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

int FabiEngine3D::gfx_getShadowInterval()
{
	return _core->_shadowManager.getInterval();
}

float FabiEngine3D::gfx_getSkyHdrBrightnessFactor()
{
	return _core->_skyEntityManager.getBrightnessFactor();
}

float FabiEngine3D::gfx_getDofMaxDistance()
{
	return _core->_renderBus.getDofMaxDistance();
}

float FabiEngine3D::gfx_getDofBlurDistance()
{
	return _core->_renderBus.getDofBlurDistance();
}

float FabiEngine3D::gfx_getLensFlareIntensity()
{
	return _core->_renderBus.getLensFlareIntensity();
}

float FabiEngine3D::gfx_getLensFlareMultiplier()
{
	return _core->_renderBus.getLensFlareMultiplier();
}

float FabiEngine3D::gfx_getMotionBlurStrength()
{
	return _core->_renderBus.getMotionBlurStrength();
}
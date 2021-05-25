#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

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

unsigned int FabiEngine3D::gfx_getMsaaQuality()
{
	return _core->_renderBus.getMsaaSampleCount();
}

unsigned int FabiEngine3D::gfx_getShadowQuality()
{
	return _core->_renderBus.getShadowMapSize();
}

unsigned int FabiEngine3D::gfx_getReflectionQuality()
{
	return _core->_renderBus.getSceneReflectionMapSize();
}

unsigned int FabiEngine3D::gfx_getRefractionQuality()
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

float FabiEngine3D::gfx_getFogThickness()
{
	return _core->_renderBus.getFogThickness();
}

Vec3 FabiEngine3D::gfx_getFogColor()
{
	return _core->_renderBus.getFogColor();
}

float FabiEngine3D::gfx_getSkyReflectionFactor()
{
	return _core->_renderBus.getSkyReflectionMixValue();
}

float FabiEngine3D::gfx_getSceneReflectionHeight()
{
	return _core->_renderBus.getSceneReflectionHeight();
}

float FabiEngine3D::gfx_getSceneReflectionFactor()
{
	return _core->_renderBus.getSceneReflectionMixValue();
}

Vec3 FabiEngine3D::gfx_getShadowEye()
{
	return _core->_shadowGenerator.getEye();
}

Vec3 FabiEngine3D::gfx_getShadowCenter()
{
	return _core->_shadowGenerator.getCenter();
}

string FabiEngine3D::gfx_getLensFlareMapPath()
{
	return _core->_renderBus.getLensFlareMapPath();
}

float FabiEngine3D::gfx_getShadowSize()
{
	return _core->_shadowGenerator.getSize();
}

float FabiEngine3D::gfx_getShadowReach()
{
	return _core->_shadowGenerator.getReach();
}

float FabiEngine3D::gfx_getShadowLightness()
{
	return _core->_renderBus.getShadowLightness();
}

bool FabiEngine3D::gfx_isShadowFollowingCamera()
{
	return _core->_shadowGenerator.isFollowingCamera();
}

bool FabiEngine3D::gfx_isSoftShadowingEnabled()
{
	return _core->_renderBus.isSoftShadowingEnabled();
}

float FabiEngine3D::gfx_getBloomIntensity()
{
	return _core->_renderBus.getBloomIntensity();
}

float FabiEngine3D::gfx_getBloomBrightnessTreshold()
{
	return _core->_renderBus.getBloomBrightnessTreshold();
}

unsigned int FabiEngine3D::gfx_getBloomBlurSize()
{
	return _core->_renderBus.getBloomBlurSize();
}

unsigned int FabiEngine3D::gfx_getShadowInterval()
{
	return _core->_shadowGenerator.getInterval();
}

float FabiEngine3D::gfx_getSkyHdrBrightnessFactor()
{
	return _core->_skyEntityManager.getBrightnessFactor();
}

float FabiEngine3D::gfx_getaMaxDofDistance()
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
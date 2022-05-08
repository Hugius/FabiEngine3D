#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::graphics_setAmbientLightingEnabled(bool value)
{
	_core->getRenderStorage()->setAmbientLightingEnabled(value);
}

void EngineInterface::graphics_setDirectionalLightingEnabled(bool value)
{
	_core->getRenderStorage()->setDirectionalLightingEnabled(value);
}

void EngineInterface::graphics_setFogEnabled(bool value)
{
	_core->getRenderStorage()->setFogEnabled(value);
}

void EngineInterface::graphics_setAntiAliasingEnabled(bool value)
{
	_core->getRenderStorage()->setAntiAliasingEnabled(value);
}

void EngineInterface::graphics_setShadowsEnabled(bool value)
{
	_core->getRenderStorage()->setShadowsEnabled(value);
}

void EngineInterface::graphics_setBloomEnabled(bool value)
{
	_core->getRenderStorage()->setBloomEnabled(value);
}

void EngineInterface::graphics_setSkyExposureEnabled(bool value)
{
	_core->getRenderStorage()->setSkyExposureEnabled(value);
}

void EngineInterface::graphics_setDofEnabled(bool value)
{
	_core->getRenderStorage()->setDofEnabled(value);
}

void EngineInterface::graphics_setMotionBlurEnabled(bool value)
{
	_core->getRenderStorage()->setMotionBlurEnabled(value);
}

void EngineInterface::graphics_setLensFlareEnabled(bool value)
{
	_core->getRenderStorage()->setLensFlareEnabled(value);
}

void EngineInterface::graphics_setCubeReflectionInterval(int value)
{
	_core->getRenderStorage()->setCubeReflectionInterval(value);
}

void EngineInterface::graphics_setCubeRefractionInterval(int value)
{
	_core->getRenderStorage()->setCubeRefractionInterval(value);
}

void EngineInterface::graphics_setCubeRefractionQuality(int value)
{
	_core->getRenderStorage()->setCubeRefractionQuality(value);

	_core->getMasterRenderer()->loadCubeRefractionQuality();
}

void EngineInterface::graphics_setPlanarReflectionHeight(float value)
{
	_core->getRenderStorage()->setPlanarReflectionHeight(value);
}

void EngineInterface::graphics_setPlanarRefractionHeight(float value)
{
	_core->getRenderStorage()->setPlanarRefractionHeight(value);
}

void EngineInterface::graphics_setBloomQuality(int value)
{
	_core->getRenderStorage()->setBloomQuality(value);

	_core->getMasterRenderer()->loadBloomBlurQuality();
}

void EngineInterface::graphics_setDofQuality(int value)
{
	_core->getRenderStorage()->setDofQuality(value);

	_core->getMasterRenderer()->loadDofBlurQuality();
}

void EngineInterface::graphics_setMotionBlurQuality(int value)
{
	_core->getRenderStorage()->setMotionBlurQuality(value);

	_core->getMasterRenderer()->loadMotionBlurBlurQuality();
}

void EngineInterface::graphics_setAnisotropicFilteringQuality(int value)
{
	const auto minQuality = _core->getRenderStorage()->getMinAnisotropicFilteringQuality();
	const auto maxQuality = _core->getRenderStorage()->getMaxAnisotropicFilteringQuality();

	_core->getRenderStorage()->setAnisotropicFilteringQuality(value);

	for(const auto & [mergedId, texture] : _core->getTextureBufferCache()->get2dBuffers())
	{
		if(texture->isAnisotropicallyFiltered())
		{
			texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());
		}
	}

	for(const auto & [mergedId, texture] : _core->getTextureBufferCache()->get3dBuffers())
	{
		if(texture->isAnisotropicallyFiltered())
		{
			texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());
		}
	}
}

void EngineInterface::graphics_setCubeReflectionQuality(int value)
{
	_core->getRenderStorage()->setCubeReflectionQuality(value);

	_core->getMasterRenderer()->loadCubeReflectionQuality();
}

void EngineInterface::graphics_setPlanarReflectionQuality(int value)
{
	_core->getRenderStorage()->setPlanarReflectionQuality(value);

	_core->getMasterRenderer()->loadPlanarReflectionQuality();
	_core->getMasterRenderer()->loadWaterReflectionQuality();
}

void EngineInterface::graphics_setPlanarRefractionQuality(int value)
{
	_core->getRenderStorage()->setPlanarRefractionQuality(value);

	_core->getMasterRenderer()->loadPlanarRefractionQuality();
	_core->getMasterRenderer()->loadWaterRefractionQuality();
}

void EngineInterface::graphics_setShadowQuality(int value)
{
	_core->getRenderStorage()->setShadowQuality(value);

	_core->getMasterRenderer()->loadShadowQuality();
}

void EngineInterface::graphics_setAmbientLightingColor(const fvec3 & value)
{
	_core->getRenderStorage()->setAmbientLightingColor(value);
}

void EngineInterface::graphics_setAmbientLightingIntensity(float value)
{
	_core->getRenderStorage()->setAmbientLightingIntensity(value);
}

void EngineInterface::graphics_setDirectionalLightingPosition(const fvec3 & value)
{
	_core->getRenderStorage()->setDirectionalLightingPosition(value);
}

void EngineInterface::graphics_setDirectionalLightingColor(const fvec3 & value)
{
	_core->getRenderStorage()->setDirectionalLightingColor(value);
}

void EngineInterface::graphics_setDirectionalLightingIntensity(float value)
{
	_core->getRenderStorage()->setDirectionalLightingIntensity(value);
}

void EngineInterface::graphics_setFogColor(const fvec3 & value)
{
	_core->getRenderStorage()->setFogColor(value);
}

void EngineInterface::graphics_setFogThickness(float value)
{
	_core->getRenderStorage()->setFogThickness(value);
}

void EngineInterface::graphics_setFogMinDistance(float value)
{
	_core->getRenderStorage()->setMinFogDistance(value);
}

void EngineInterface::graphics_setFogMaxDistance(float value)
{
	_core->getRenderStorage()->setMaxFogDistance(value);
}

void EngineInterface::graphics_setShadowCircleEnabled(bool value)
{
	_core->getRenderStorage()->setShadowCircleEnabled(value);
}

void EngineInterface::graphics_setShadowPositionOffset(const fvec3 & value)
{
	_core->getRenderStorage()->setShadowPositionOffset(value);
}

void EngineInterface::graphics_setShadowLookatOffset(const fvec3 & value)
{
	_core->getRenderStorage()->setShadowLookatOffset(value);
}

void EngineInterface::graphics_setShadowSize(float value)
{
	_core->getRenderStorage()->setShadowSize(value);
}

void EngineInterface::graphics_setShadowLightness(float value)
{
	_core->getRenderStorage()->setShadowLightness(value);
}

void EngineInterface::graphics_setShadowInterval(int value)
{
	_core->getRenderStorage()->setShadowInterval(value);
}

void EngineInterface::graphics_setShadowFollowingCameraX(bool value)
{
	_core->getRenderStorage()->setShadowsFollowingCameraX(value);
}

void EngineInterface::graphics_setShadowFollowingCameraY(bool value)
{
	_core->getRenderStorage()->setShadowsFollowingCameraY(value);
}

void EngineInterface::graphics_setShadowFollowingCameraZ(bool value)
{
	_core->getRenderStorage()->setShadowsFollowingCameraZ(value);
}

void EngineInterface::graphics_setBloomIntensity(float value)
{
	_core->getRenderStorage()->setBloomIntensity(value);
}

void EngineInterface::graphics_setBloomBlurCount(int value)
{
	_core->getRenderStorage()->setBloomBlurCount(value);
}

void EngineInterface::graphics_setBloomType(BloomType value)
{
	_core->getRenderStorage()->setBloomType(value);
}

void EngineInterface::graphics_setSkyExposureIntensity(float value)
{
	_core->getRenderStorage()->setSkyExposureIntensity(value);
}

void EngineInterface::graphics_setSkyExposureSpeed(float value)
{
	_core->getRenderStorage()->setSkyExposureSpeed(value);
}

void EngineInterface::graphics_setDofDynamicDistance(float value)
{
	_core->getRenderStorage()->setDofDynamicDistance(value);
}

void EngineInterface::graphics_setDofBlurDistance(float value)
{
	_core->getRenderStorage()->setDofBlurDistance(value);
}

void EngineInterface::graphics_setDofDynamic(bool value)
{
	_core->getRenderStorage()->setDofDynamic(value);
}

void EngineInterface::graphics_setMotionBlurIntensity(float value)
{
	_core->getRenderStorage()->setMotionBlurIntensity(value);
}

void EngineInterface::graphics_setLensFlareMap(const string & value)
{
	if(value.empty())
	{
		_core->getRenderStorage()->setLensFlareMap(nullptr);
		_core->getRenderStorage()->setLensFlareMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->loadImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getRenderStorage()->setLensFlareMap(texture);
		_core->getRenderStorage()->setLensFlareMapPath(value);
	}
}

void EngineInterface::graphics_setLensFlareIntensity(float value)
{
	_core->getRenderStorage()->setLensFlareIntensity(value);
}

void EngineInterface::graphics_setLensFlareSensitivity(float value)
{
	_core->getRenderStorage()->setLensFlareSensitivity(value);
}

const bool EngineInterface::graphics_isAntiAliasingEnabled() const
{
	return _core->getRenderStorage()->isAntiAliasingEnabled();
}

const bool EngineInterface::graphics_isAmbientLightingEnabled() const
{
	return _core->getRenderStorage()->isAmbientLightingEnabled();
}

const bool EngineInterface::graphics_isDirectionalLightingEnabled() const
{
	return _core->getRenderStorage()->isDirectionalLightingEnabled();
}

const bool EngineInterface::graphics_isFogEnabled() const
{
	return _core->getRenderStorage()->isFogEnabled();
}

const bool EngineInterface::graphics_isBloomEnabled() const
{
	return _core->getRenderStorage()->isBloomEnabled();
}

const bool EngineInterface::graphics_isSkyExposureEnabled() const
{
	return _core->getRenderStorage()->isSkyExposureEnabled();
}

const bool EngineInterface::graphics_isShadowsEnabled() const
{
	return _core->getRenderStorage()->isShadowsEnabled();
}

const bool EngineInterface::graphics_isDofEnabled() const
{
	return _core->getRenderStorage()->isDofEnabled();
}

const bool EngineInterface::graphics_isDofDynamic() const
{
	return _core->getRenderStorage()->isDofDynamic();
}

const bool EngineInterface::graphics_isMotionBlurEnabled() const
{
	return _core->getRenderStorage()->isMotionBlurEnabled();
}

const bool EngineInterface::graphics_isLensFlareEnabled() const
{
	return _core->getRenderStorage()->isLensFlareEnabled();
}

const bool EngineInterface::graphics_isShadowCircleEnabled() const
{
	return _core->getRenderStorage()->isShadowCircleEnabled();
}

const int EngineInterface::graphics_getShadowQuality() const
{
	return _core->getRenderStorage()->getShadowQuality();
}

const int EngineInterface::graphics_getCubeReflectionInterval() const
{
	return _core->getRenderStorage()->getCubeReflectionInterval();
}

const int EngineInterface::graphics_getCubeRefractionInterval() const
{
	return _core->getRenderStorage()->getCubeRefractionInterval();
}

const int EngineInterface::graphics_getCubeRefractionQuality() const
{
	return _core->getRenderStorage()->getCubeRefractionQuality();
}

const int EngineInterface::graphics_getCubeReflectionQuality() const
{
	return _core->getRenderStorage()->getCubeReflectionQuality();
}

const int EngineInterface::graphics_getPlanarReflectionQuality() const
{
	return _core->getRenderStorage()->getPlanarReflectionQuality();
}

const int EngineInterface::graphics_getPlanarRefractionQuality() const
{
	return _core->getRenderStorage()->getPlanarRefractionQuality();
}

const fvec3 & EngineInterface::graphics_getAmbientLightingColor() const
{
	return _core->getRenderStorage()->getAmbientLightingColor();
}

const float EngineInterface::graphics_getAmbientLightingIntensity() const
{
	return _core->getRenderStorage()->getAmbientLightingIntensity();
}

const float EngineInterface::graphics_getDirectionalLightingIntensity() const
{
	return _core->getRenderStorage()->getDirectionalLightingIntensity();
}

const fvec3 & EngineInterface::graphics_getDirectionalLightingPosition() const
{
	return _core->getRenderStorage()->getDirectionalLightingPosition();
}

const fvec3 & EngineInterface::graphics_getDirectionalLightingColor() const
{
	return _core->getRenderStorage()->getDirectionalLightingColor();
}

const float EngineInterface::graphics_getFogMinDistance() const
{
	return _core->getRenderStorage()->getMinFogDistance();
}

const float EngineInterface::graphics_getFogMaxDistance() const
{
	return _core->getRenderStorage()->getMaxFogDistance();
}

const float EngineInterface::graphics_getFogThickness() const
{
	return _core->getRenderStorage()->getFogThickness();
}

const fvec3 & EngineInterface::graphics_getFogColor() const
{
	return _core->getRenderStorage()->getFogColor();
}

const float EngineInterface::graphics_getPlanarReflectionHeight() const
{
	return _core->getRenderStorage()->getPlanarReflectionHeight();
}

const float EngineInterface::graphics_getPlanarRefractionHeight() const
{
	return _core->getRenderStorage()->getPlanarRefractionHeight();
}

const fvec3 & EngineInterface::graphics_getShadowPositionOffset() const
{
	return _core->getRenderStorage()->getShadowPositionOffset();
}

const fvec3 & EngineInterface::graphics_getShadowLookatOffset() const
{
	return _core->getRenderStorage()->getShadowLookatOffset();
}

const string & EngineInterface::graphics_getLensFlareMapPath() const
{
	return _core->getRenderStorage()->getLensFlareMapPath();
}

const float EngineInterface::graphics_getShadowSize() const
{
	return _core->getRenderStorage()->getShadowSize();
}

const float EngineInterface::graphics_getShadowLightness() const
{
	return _core->getRenderStorage()->getShadowLightness();
}

const bool EngineInterface::graphics_isShadowFollowingCameraX() const
{
	return _core->getRenderStorage()->isShadowsFollowingCameraX();
}

const bool EngineInterface::graphics_isShadowFollowingCameraY() const
{
	return _core->getRenderStorage()->isShadowsFollowingCameraY();
}

const bool EngineInterface::graphics_isShadowFollowingCameraZ() const
{
	return _core->getRenderStorage()->isShadowsFollowingCameraZ();
}

const bool EngineInterface::graphics_hasLensFlareMap() const
{
	return (_core->getRenderStorage()->getLensFlareTextureBuffer() != nullptr);
}

const float EngineInterface::graphics_getBloomIntensity() const
{
	return _core->getRenderStorage()->getBloomIntensity();
}

const int EngineInterface::graphics_getBloomBlurCount() const
{
	return _core->getRenderStorage()->getBloomBlurCount();
}

const int EngineInterface::graphics_getShadowInterval() const
{
	return _core->getRenderStorage()->getShadowInterval();
}

const float EngineInterface::graphics_getSkyExposureIntensity() const
{
	return _core->getRenderStorage()->getSkyExposureIntensity();
}

const float EngineInterface::graphics_getSkyExposureSpeed() const
{
	return _core->getRenderStorage()->getSkyExposureSpeed();
}

const float EngineInterface::graphics_getDofDynamicDistance() const
{
	return _core->getRenderStorage()->getDofDynamicDistance();
}

const float EngineInterface::graphics_getDofBlurDistance() const
{
	return _core->getRenderStorage()->getDofBlurDistance();
}

const float EngineInterface::graphics_getLensFlareIntensity() const
{
	return _core->getRenderStorage()->getLensFlareIntensity();
}

const float EngineInterface::graphics_getLensFlareSensitivity() const
{
	return _core->getRenderStorage()->getLensFlareSensitivity();
}

const float EngineInterface::graphics_getMotionBlurIntensity() const
{
	return _core->getRenderStorage()->getMotionBlurIntensity();
}

const int EngineInterface::graphics_getBloomQuality() const
{
	return _core->getRenderStorage()->getBloomQuality();
}

const int EngineInterface::graphics_getDofQuality() const
{
	return _core->getRenderStorage()->getDofQuality();
}

const int EngineInterface::graphics_getMotionBlurQuality() const
{
	return _core->getRenderStorage()->getMotionBlurQuality();
}

const BloomType EngineInterface::graphics_getBloomType() const
{
	return _core->getRenderStorage()->getBloomType();
}

const int EngineInterface::graphics_getAnisotropicFilteringQuality() const
{
	return _core->getRenderStorage()->getAnisotropicFilteringQuality();
}
#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::gfx_setAmbientLightingEnabled(bool value)
{
	_core->getRenderStorage()->setAmbientLightingEnabled(value);
}

void EngineInterface::gfx_setDirectionalLightingEnabled(bool value)
{
	_core->getRenderStorage()->setDirectionalLightingEnabled(value);
}

void EngineInterface::gfx_setFogEnabled(bool value)
{
	_core->getRenderStorage()->setFogEnabled(value);
}

void EngineInterface::gfx_setAntiAliasingEnabled(bool value)
{
	_core->getRenderStorage()->setAntiAliasingEnabled(value);
}

void EngineInterface::gfx_setShadowsEnabled(bool value)
{
	_core->getRenderStorage()->setShadowsEnabled(value);
}

void EngineInterface::gfx_setBloomEnabled(bool value)
{
	_core->getRenderStorage()->setBloomEnabled(value);
}

void EngineInterface::gfx_setSkyExposureEnabled(bool value)
{
	_core->getRenderStorage()->setSkyExposureEnabled(value);
}

void EngineInterface::gfx_setDofEnabled(bool value)
{
	_core->getRenderStorage()->setDofEnabled(value);
}

void EngineInterface::gfx_setMotionBlurEnabled(bool value)
{
	_core->getRenderStorage()->setMotionBlurEnabled(value);
}

void EngineInterface::gfx_setLensFlareEnabled(bool value)
{
	_core->getRenderStorage()->setLensFlareEnabled(value);
}

void EngineInterface::gfx_setCubeReflectionInterval(unsigned int value)
{
	_core->getRenderStorage()->setCubeReflectionInterval(value);
}

void EngineInterface::gfx_setPlanarReflectionHeight(float value)
{
	_core->getRenderStorage()->setPlanarReflectionHeight(value);
}

void EngineInterface::gfx_setBloomQuality(unsigned int value)
{
	_core->getRenderStorage()->setBloomQuality(value);

	_core->getMasterRenderer()->reloadBloomBlurQuality();
}

void EngineInterface::gfx_setDofQuality(unsigned int value)
{
	_core->getRenderStorage()->setDofQuality(value);

	_core->getMasterRenderer()->reloadDofBlurQuality();
}

void EngineInterface::gfx_setMotionBlurQuality(unsigned int value)
{
	_core->getRenderStorage()->setMotionBlurQuality(value);

	_core->getMasterRenderer()->reloadMotionBlurBlurQuality();
}

void EngineInterface::gfx_setAnisotropicFilteringQuality(unsigned int value)
{
	const auto minQuality = _core->getRenderStorage()->getMinAnisotropicFilteringQuality();
	const auto maxQuality = _core->getRenderStorage()->getMaxAnisotropicFilteringQuality();

	_core->getRenderStorage()->setAnisotropicFilteringQuality(value);

	for(const auto& [key, texture] : _core->getTextureBufferCache()->get2dBuffers())
	{
		if(texture->isAnisotropicallyFiltered())
		{
			texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());
		}
	}

	for(const auto& [key, texture] : _core->getTextureBufferCache()->get3dBuffers())
	{
		if(texture->isAnisotropicallyFiltered())
		{
			texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());
		}
	}
}

void EngineInterface::gfx_setCubeReflectionQuality(unsigned int value)
{
	_core->getRenderStorage()->setCubeReflectionQuality(value);

	_core->getMasterRenderer()->reloadCubeReflectionQuality();
}

void EngineInterface::gfx_setPlanarReflectionQuality(unsigned int value)
{
	_core->getRenderStorage()->setPlanarReflectionQuality(value);

	_core->getMasterRenderer()->reloadPlanarReflectionQuality();
	_core->getMasterRenderer()->reloadWaterReflectionQuality();
}

void EngineInterface::gfx_setPlanarRefractionQuality(unsigned int value)
{
	_core->getRenderStorage()->setPlanarRefractionQuality(value);

	_core->getMasterRenderer()->reloadWaterRefractionQuality();
}

void EngineInterface::gfx_setShadowQuality(unsigned int value)
{
	_core->getRenderStorage()->setShadowQuality(value);

	_core->getMasterRenderer()->reloadShadowQuality();
}

void EngineInterface::gfx_setAmbientLightingColor(const fvec3& value)
{
	_core->getRenderStorage()->setAmbientLightingColor(value);
}

void EngineInterface::gfx_setAmbientLightingIntensity(float value)
{
	_core->getRenderStorage()->setAmbientLightingIntensity(value);
}

void EngineInterface::gfx_setDirectionalLightingPosition(const fvec3& value)
{
	_core->getRenderStorage()->setDirectionalLightingPosition(value);
}

void EngineInterface::gfx_setDirectionalLightingColor(const fvec3& value)
{
	_core->getRenderStorage()->setDirectionalLightingColor(value);
}

void EngineInterface::gfx_setDirectionalLightingIntensity(float value)
{
	_core->getRenderStorage()->setDirectionalLightingIntensity(value);
}

void EngineInterface::gfx_setFogColor(const fvec3& value)
{
	_core->getRenderStorage()->setFogColor(value);
}

void EngineInterface::gfx_setFogThickness(float value)
{
	_core->getRenderStorage()->setFogThickness(value);
}

void EngineInterface::gfx_setFogMinDistance(float value)
{
	_core->getRenderStorage()->setMinFogDistance(value);
}

void EngineInterface::gfx_setFogMaxDistance(float value)
{
	_core->getRenderStorage()->setMaxFogDistance(value);
}

void EngineInterface::gfx_setShadowCircleEnabled(bool value)
{
	_core->getRenderStorage()->setShadowCircleEnabled(value);
}

void EngineInterface::gfx_setShadowPositionOffset(const fvec3& value)
{
	_core->getRenderStorage()->setShadowPositionOffset(value);
}

void EngineInterface::gfx_setShadowLookatOffset(const fvec3& value)
{
	_core->getRenderStorage()->setShadowLookatOffset(value);
}

void EngineInterface::gfx_setShadowSize(float value)
{
	_core->getRenderStorage()->setShadowSize(value);
}

void EngineInterface::gfx_setShadowLightness(float value)
{
	_core->getRenderStorage()->setShadowLightness(value);
}

void EngineInterface::gfx_setShadowInterval(unsigned int value)
{
	_core->getRenderStorage()->setShadowInterval(value);
}

void EngineInterface::gfx_setShadowFollowingCamera(bool value)
{
	_core->getRenderStorage()->setShadowsFollowingCamera(value);
}

void EngineInterface::gfx_setBloomIntensity(float value)
{
	_core->getRenderStorage()->setBloomIntensity(value);
}

void EngineInterface::gfx_setBloomBlurCount(unsigned int value)
{
	_core->getRenderStorage()->setBloomBlurCount(value);
}

void EngineInterface::gfx_setBloomType(BloomType value)
{
	_core->getRenderStorage()->setBloomType(value);
}

void EngineInterface::gfx_setSkyExposureIntensity(float value)
{
	_core->getRenderStorage()->setSkyExposureIntensity(value);
}

void EngineInterface::gfx_setSkyExposureSpeed(float value)
{
	_core->getRenderStorage()->setSkyExposureSpeed(value);
}

void EngineInterface::gfx_setDofDynamicDistance(float value)
{
	_core->getRenderStorage()->setDofDynamicDistance(value);
}

void EngineInterface::gfx_setDofBlurDistance(float value)
{
	_core->getRenderStorage()->setDofBlurDistance(value);
}

void EngineInterface::gfx_setDofDynamic(bool value)
{
	_core->getRenderStorage()->setDofDynamic(value);
}

void EngineInterface::gfx_setMotionBlurIntensity(float value)
{
	_core->getRenderStorage()->setMotionBlurIntensity(value);
}

void EngineInterface::gfx_setLensFlareMap(const string& value)
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

void EngineInterface::gfx_setLensFlareIntensity(float value)
{
	_core->getRenderStorage()->setLensFlareIntensity(value);
}

void EngineInterface::gfx_setLensFlareSensitivity(float value)
{
	_core->getRenderStorage()->setLensFlareSensitivity(value);
}

const bool EngineInterface::gfx_isAntiAliasingEnabled() const
{
	return _core->getRenderStorage()->isAntiAliasingEnabled();
}

const bool EngineInterface::gfx_isAmbientLightingEnabled() const
{
	return _core->getRenderStorage()->isAmbientLightingEnabled();
}

const bool EngineInterface::gfx_isDirectionalLightingEnabled() const
{
	return _core->getRenderStorage()->isDirectionalLightingEnabled();
}

const bool EngineInterface::gfx_isFogEnabled() const
{
	return _core->getRenderStorage()->isFogEnabled();
}

const bool EngineInterface::gfx_isBloomEnabled() const
{
	return _core->getRenderStorage()->isBloomEnabled();
}

const bool EngineInterface::gfx_isSkyExposureEnabled() const
{
	return _core->getRenderStorage()->isSkyExposureEnabled();
}

const bool EngineInterface::gfx_isShadowsEnabled() const
{
	return _core->getRenderStorage()->isShadowsEnabled();
}

const bool EngineInterface::gfx_isDofEnabled() const
{
	return _core->getRenderStorage()->isDofEnabled();
}

const bool EngineInterface::gfx_isDofDynamic() const
{
	return _core->getRenderStorage()->isDofDynamic();
}

const bool EngineInterface::gfx_isMotionBlurEnabled() const
{
	return _core->getRenderStorage()->isMotionBlurEnabled();
}

const bool EngineInterface::gfx_isLensFlareEnabled() const
{
	return _core->getRenderStorage()->isLensFlareEnabled();
}

const bool EngineInterface::gfx_isShadowCircleEnabled() const
{
	return _core->getRenderStorage()->isShadowCircleEnabled();
}

const unsigned int EngineInterface::gfx_getShadowQuality() const
{
	return _core->getRenderStorage()->getShadowQuality();
}

const unsigned int EngineInterface::gfx_getCubeReflectionQuality() const
{
	return _core->getRenderStorage()->getCubeReflectionQuality();
}

const unsigned int EngineInterface::gfx_getPlanarReflectionQuality() const
{
	return _core->getRenderStorage()->getPlanarReflectionQuality();
}

const unsigned int EngineInterface::gfx_getPlanarRefractionQuality() const
{
	return _core->getRenderStorage()->getPlanarRefractionQuality();
}

const fvec3& EngineInterface::gfx_getAmbientLightingColor() const
{
	return _core->getRenderStorage()->getAmbientLightingColor();
}

const float EngineInterface::gfx_getAmbientLightingIntensity() const
{
	return _core->getRenderStorage()->getAmbientLightingIntensity();
}

const float EngineInterface::gfx_getDirectionalLightingIntensity() const
{
	return _core->getRenderStorage()->getDirectionalLightingIntensity();
}

const fvec3& EngineInterface::gfx_getDirectionalLightingPosition() const
{
	return _core->getRenderStorage()->getDirectionalLightingPosition();
}

const fvec3& EngineInterface::gfx_getDirectionalLightingColor() const
{
	return _core->getRenderStorage()->getDirectionalLightingColor();
}

const float EngineInterface::gfx_getFogMinDistance() const
{
	return _core->getRenderStorage()->getMinFogDistance();
}

const float EngineInterface::gfx_getFogMaxDistance() const
{
	return _core->getRenderStorage()->getMaxFogDistance();
}

const float EngineInterface::gfx_getFogThickness() const
{
	return _core->getRenderStorage()->getFogThickness();
}

const fvec3& EngineInterface::gfx_getFogColor() const
{
	return _core->getRenderStorage()->getFogColor();
}

const float EngineInterface::gfx_getPlanarReflectionHeight() const
{
	return _core->getRenderStorage()->getPlanarReflectionHeight();
}

const fvec3& EngineInterface::gfx_getShadowPositionOffset() const
{
	return _core->getRenderStorage()->getShadowPositionOffset();
}

const fvec3& EngineInterface::gfx_getShadowLookatOffset() const
{
	return _core->getRenderStorage()->getShadowLookatOffset();
}

const string& EngineInterface::gfx_getLensFlareMapPath() const
{
	return _core->getRenderStorage()->getLensFlareMapPath();
}

const float EngineInterface::gfx_getShadowSize() const
{
	return _core->getRenderStorage()->getShadowSize();
}

const float EngineInterface::gfx_getShadowLightness() const
{
	return _core->getRenderStorage()->getShadowLightness();
}

const bool EngineInterface::gfx_isShadowFollowingCamera() const
{
	return _core->getRenderStorage()->isShadowsFollowingCamera();
}

const bool EngineInterface::gfx_hasLensFlareMap() const
{
	return (_core->getRenderStorage()->getLensFlareTextureBuffer() != nullptr);
}

const float EngineInterface::gfx_getBloomIntensity() const
{
	return _core->getRenderStorage()->getBloomIntensity();
}

const unsigned int EngineInterface::gfx_getBloomBlurCount() const
{
	return _core->getRenderStorage()->getBloomBlurCount();
}

const unsigned int EngineInterface::gfx_getShadowInterval() const
{
	return _core->getRenderStorage()->getShadowInterval();
}

const float EngineInterface::gfx_getSkyExposureIntensity() const
{
	return _core->getRenderStorage()->getSkyExposureIntensity();
}

const float EngineInterface::gfx_getSkyExposureSpeed() const
{
	return _core->getRenderStorage()->getSkyExposureSpeed();
}

const float EngineInterface::gfx_getDofDynamicDistance() const
{
	return _core->getRenderStorage()->getDofDynamicDistance();
}

const float EngineInterface::gfx_getDofBlurDistance() const
{
	return _core->getRenderStorage()->getDofBlurDistance();
}

const float EngineInterface::gfx_getLensFlareIntensity() const
{
	return _core->getRenderStorage()->getLensFlareIntensity();
}

const float EngineInterface::gfx_getLensFlareSensitivity() const
{
	return _core->getRenderStorage()->getLensFlareSensitivity();
}

const float EngineInterface::gfx_getMotionBlurIntensity() const
{
	return _core->getRenderStorage()->getMotionBlurIntensity();
}

const unsigned int EngineInterface::gfx_getBloomQuality() const
{
	return _core->getRenderStorage()->getBloomQuality();
}

const unsigned int EngineInterface::gfx_getDofQuality() const
{
	return _core->getRenderStorage()->getDofQuality();
}

const unsigned int EngineInterface::gfx_getMotionBlurQuality() const
{
	return _core->getRenderStorage()->getMotionBlurQuality();
}

const BloomType EngineInterface::gfx_getBloomType() const
{
	return _core->getRenderStorage()->getBloomType();
}

const unsigned int EngineInterface::gfx_getAnisotropicFilteringQuality() const
{
	return _core->getRenderStorage()->getAnisotropicFilteringQuality();
}
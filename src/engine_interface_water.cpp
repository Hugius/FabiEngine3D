#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::water_create(const string & waterId)
{
	_core->getWaterManager()->createWater(waterId);
}

void EngineInterface::water_delete(const string & waterId)
{
	_core->getWaterManager()->deleteWater(waterId);
}

void EngineInterface::water_select(const string & waterId)
{
	_core->getWaterManager()->selectWater(waterId);
}

void EngineInterface::water_setHeight(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setHeight(value);
}

void EngineInterface::water_setSize(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setSize(value);

	_core->getWaterManager()->loadWaterVertexBuffer(waterId);
}

void EngineInterface::water_setSpecular(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setSpecular(value);
}

void EngineInterface::water_setTextureRepeat(const string & waterId, int value)
{
	_core->getWaterManager()->getWater(waterId)->setTextureRepeat(value);
}

void EngineInterface::water_setMinClipPosition(const string & waterId, const fvec3 & value)
{
	_core->getWaterManager()->getWater(waterId)->setMinClipPosition(value);
}

void EngineInterface::water_setMaxClipPosition(const string & waterId, const fvec3 & value)
{
	_core->getWaterManager()->getWater(waterId)->setMaxClipPosition(value);
}

void EngineInterface::water_setDistortionSize(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setDistortionSize(value);
}

void EngineInterface::water_setDistortionFactor(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setDistortionFactor(value);
}

void EngineInterface::water_setCaptureOffset(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setCaptureOffset(value);
}

void EngineInterface::water_setCapturingSky(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setCapturingSky(value);
}

void EngineInterface::water_setCapturingTerrain(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setCapturingTerrain(value);
}

void EngineInterface::water_setCapturingModels(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setCapturingModels(value);
}

void EngineInterface::water_setCapturingQuad3ds(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setCapturingQuad3ds(value);
}

void EngineInterface::water_setCapturingText3ds(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setCapturingText3ds(value);
}

void EngineInterface::water_setCapturingAabbs(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setCapturingAabbs(value);
}

void EngineInterface::water_setReflective(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setReflective(value);
}

void EngineInterface::water_setRefractive(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setRefractive(value);
}

void EngineInterface::water_setWireframed(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setWireframed(value);
}

void EngineInterface::water_setWireframeColor(const string & waterId, const fvec3 & value)
{
	_core->getWaterManager()->getWater(waterId)->setWireframeColor(value);
}

void EngineInterface::water_setDudvMap(const string & waterId, const string & value)
{
	if(value.empty())
	{
		_core->getWaterManager()->getWater(waterId)->setDudvMap(nullptr);
		_core->getWaterManager()->getWater(waterId)->setDudvMapPath("");
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

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getWaterManager()->getWater(waterId)->setDudvMap(texture);
		_core->getWaterManager()->getWater(waterId)->setDudvMapPath(value);
	}
}

void EngineInterface::water_setNormalMap(const string & waterId, const string & value)
{
	if(value.empty())
	{
		_core->getWaterManager()->getWater(waterId)->setNormalMap(nullptr);
		_core->getWaterManager()->getWater(waterId)->setNormalMapPath("");
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

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getWaterManager()->getWater(waterId)->setNormalMap(texture);
		_core->getWaterManager()->getWater(waterId)->setNormalMapPath(value);
	}
}

void EngineInterface::water_setHeightMap(const string & waterId, const string & value)
{
	if(value.empty())
	{
		_core->getWaterManager()->getWater(waterId)->setHeightMap(nullptr);
		_core->getWaterManager()->getWater(waterId)->setHeightMapPath("");
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

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getWaterManager()->getWater(waterId)->setHeightMap(texture);
		_core->getWaterManager()->getWater(waterId)->setHeightMapPath(value);
	}
}

void EngineInterface::water_setWaveHeight(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setWaveHeight(value);
}

void EngineInterface::water_setSpecularShininess(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setSpecularShininess(value);
}

void EngineInterface::water_setSpecularIntensity(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setSpecularIntensity(value);
}

void EngineInterface::water_setMaxDepth(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setMaxDepth(value);
}

void EngineInterface::water_setLightness(const string & waterId, float value)
{
	_core->getWaterManager()->getWater(waterId)->setLightness(value);
}

void EngineInterface::water_setRippleSpeed(const string & waterId, const fvec2 & value)
{
	_core->getWaterManager()->getWater(waterId)->setRippleSpeed(value);
}

void EngineInterface::water_setWaveSpeed(const string & waterId, const fvec2 & value)
{
	_core->getWaterManager()->getWater(waterId)->setWaveSpeed(value);
}

void EngineInterface::water_setColor(const string & waterId, const fvec3 & value)
{
	_core->getWaterManager()->getWater(waterId)->setColor(value);
}

void EngineInterface::water_setEdged(const string & waterId, bool value)
{
	_core->getWaterManager()->getWater(waterId)->setEdged(value);
}

const bool EngineInterface::water_isExisting(const string & waterId) const
{
	return _core->getWaterManager()->isWaterExisting(waterId);
}

const bool EngineInterface::water_isSpecular(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isSpecular();
}

const bool EngineInterface::water_isReflective(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isReflective();
}

const bool EngineInterface::water_isRefractive(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isRefractive();
}

const bool EngineInterface::water_isWireframed(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isWireframed();
}

const bool EngineInterface::water_hasDudvMap(const string & waterId) const
{
	return (_core->getWaterManager()->getWater(waterId)->getDudvTextureBuffer() != nullptr);
}

const bool EngineInterface::water_hasNormalMap(const string & waterId) const
{
	return (_core->getWaterManager()->getWater(waterId)->getNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::water_hasHeightMap(const string & waterId) const
{
	return (_core->getWaterManager()->getWater(waterId)->getHeightTextureBuffer() != nullptr);
}

const bool EngineInterface::water_isCapturingSky(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isCapturingSky();
}

const bool EngineInterface::water_isCapturingTerrain(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isCapturingTerrain();
}

const bool EngineInterface::water_isCapturingModels(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isCapturingModels();
}

const bool EngineInterface::water_isCapturingQuad3ds(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isCapturingQuad3ds();
}

const bool EngineInterface::water_isCapturingText3ds(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isCapturingText3ds();
}

const bool EngineInterface::water_isCapturingAabbs(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isCapturingAabbs();
}

const string EngineInterface::water_getSelectedId() const
{
	if(_core->getWaterManager()->getSelectedWater() == nullptr)
	{
		return "";
	}

	return _core->getWaterManager()->getSelectedWater()->getId();
}

const fvec3 & EngineInterface::water_getWireframeColor(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getWireframeColor();
}

const vector<string> EngineInterface::water_getIds() const
{
	vector<string> result = {};

	for(const auto & [waterId, water] : _core->getWaterManager()->getWaters())
	{
		result.push_back(water->getId());
	}

	return result;
}

const float EngineInterface::water_getSize(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getSize();
}

const int EngineInterface::water_getTextureRepeat(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getTextureRepeat();
}

const fvec2 & EngineInterface::water_getRippleSpeed(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getRippleSpeed();
}

const fvec2 & EngineInterface::water_getWaveSpeed(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getWaveSpeed();
}

const float EngineInterface::water_getWaveHeight(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getWaveHeight();
}

const float EngineInterface::water_getSpecularShininess(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getSpecularShininess();
}

const float EngineInterface::water_getSpecularIntensity(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getSpecularIntensity();
}

const float EngineInterface::water_getLightness(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getLightness();
}

const float EngineInterface::water_getDistortionSize(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getDistortionSize();
}

const float EngineInterface::water_getDistortionFactor(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getDistortionFactor();
}

const float EngineInterface::water_getCaptureOffset(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getCaptureOffset();
}

const bool EngineInterface::water_isEdged(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->isEdged();
}

const string & EngineInterface::water_getDudvMapPath(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getDudvMapPath();
}

const string & EngineInterface::water_getNormalMapPath(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getNormalMapPath();
}

const string & EngineInterface::water_getHeightMapPath(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getHeightMapPath();
}

const float EngineInterface::water_getHeight(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getHeight();
}

const float EngineInterface::water_getMaxDepth(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getMaxDepth();
}

const fvec3 & EngineInterface::water_getColor(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getColor();
}

const fvec3 & EngineInterface::water_getMinClipPosition(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getMinClipPosition();
}

const fvec3 & EngineInterface::water_getMaxClipPosition(const string & waterId) const
{
	return _core->getWaterManager()->getWater(waterId)->getMaxClipPosition();
}

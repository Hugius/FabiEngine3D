#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::water_create(const string & waterId)
{
	_core->getWaterEntityManager()->createEntity(waterId);
}

void EngineInterface::water_delete(const string & waterId)
{
	_core->getWaterEntityManager()->deleteEntity(waterId);
}

void EngineInterface::water_setVisible(const string & waterId, bool value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setVisible(value);
}

void EngineInterface::water_select(const string & waterId)
{
	_core->getWaterEntityManager()->selectEntity(waterId);
}

void EngineInterface::water_setHeight(const string & waterId, float value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setHeight(value);
}

void EngineInterface::water_setSize(const string & waterId, float value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setSize(value);

	_core->getWaterEntityManager()->loadVertexBuffer(waterId);
}

void EngineInterface::water_setSpecular(const string & waterId, bool value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setSpecular(value);
}

void EngineInterface::water_setTextureRepeat(const string & waterId, int value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setTextureRepeat(value);
}

void EngineInterface::water_setMinClipPosition(const string & waterId, const fvec3 & value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setMinClipPosition(value);
}

void EngineInterface::water_setMaxClipPosition(const string & waterId, const fvec3 & value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setMaxClipPosition(value);
}

void EngineInterface::water_setReflective(const string & waterId, bool value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setReflective(value);
}

void EngineInterface::water_setRefractive(const string & waterId, bool value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setRefractive(value);
}

void EngineInterface::water_setWireframed(const string & waterId, bool value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setWireframed(value);
}

void EngineInterface::water_setWireframeColor(const string & waterId, const fvec3 & value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setWireframeColor(value);
}

void EngineInterface::water_setDudvMap(const string & waterId, const string & value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(waterId)->setDudvMap(nullptr);
		_core->getWaterEntityManager()->getEntity(waterId)->setDudvMapPath("");
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

		_core->getWaterEntityManager()->getEntity(waterId)->setDudvMap(texture);
		_core->getWaterEntityManager()->getEntity(waterId)->setDudvMapPath(value);
	}
}

void EngineInterface::water_setNormalMap(const string & waterId, const string & value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(waterId)->setNormalMap(nullptr);
		_core->getWaterEntityManager()->getEntity(waterId)->setNormalMapPath("");
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

		_core->getWaterEntityManager()->getEntity(waterId)->setNormalMap(texture);
		_core->getWaterEntityManager()->getEntity(waterId)->setNormalMapPath(value);
	}
}

void EngineInterface::water_setHeightMap(const string & waterId, const string & value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(waterId)->setHeightMap(nullptr);
		_core->getWaterEntityManager()->getEntity(waterId)->setHeightMapPath("");
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

		_core->getWaterEntityManager()->getEntity(waterId)->setHeightMap(texture);
		_core->getWaterEntityManager()->getEntity(waterId)->setHeightMapPath(value);
	}
}

void EngineInterface::water_setWaveHeight(const string & waterId, float value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setWaveHeight(value);
}

void EngineInterface::water_setSpecularShininess(const string & waterId, float value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setSpecularShininess(value);
}

void EngineInterface::water_setSpecularIntensity(const string & waterId, float value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setSpecularIntensity(value);
}

void EngineInterface::water_setMaxDepth(const string & waterId, float value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setMaxDepth(value);
}

void EngineInterface::water_setRippleSpeed(const string & waterId, const fvec2 & value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setRippleSpeed(value);
}

void EngineInterface::water_setWaveSpeed(const string & waterId, const fvec2 & value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setWaveSpeed(value);
}

void EngineInterface::water_setColor(const string & waterId, const fvec3 & value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setColor(value);
}

void EngineInterface::water_setEdged(const string & waterId, bool value)
{
	_core->getWaterEntityManager()->getEntity(waterId)->setEdged(value);
}

const bool EngineInterface::water_isExisting(const string & waterId) const
{
	return _core->getWaterEntityManager()->isEntityExisting(waterId);
}

const bool EngineInterface::water_isVisible(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->isVisible();
}

const bool EngineInterface::water_isSpecular(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->isSpecular();
}

const bool EngineInterface::water_isReflective(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->isReflective();
}

const bool EngineInterface::water_isRefractive(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->isRefractive();
}

const bool EngineInterface::water_isWireframed(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->isWireframed();
}

const bool EngineInterface::water_hasDudvMap(const string & waterId) const
{
	return (_core->getWaterEntityManager()->getEntity(waterId)->getDudvTextureBuffer() != nullptr);
}

const bool EngineInterface::water_hasNormalMap(const string & waterId) const
{
	return (_core->getWaterEntityManager()->getEntity(waterId)->getNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::water_hasHeightMap(const string & waterId) const
{
	return (_core->getWaterEntityManager()->getEntity(waterId)->getHeightTextureBuffer() != nullptr);
}

const string EngineInterface::water_getSelectedId() const
{
	if(_core->getWaterEntityManager()->getSelectedEntity() == nullptr)
	{
		return "";
	}

	return _core->getWaterEntityManager()->getSelectedEntity()->getId();
}

const fvec3 & EngineInterface::water_getWireframeColor(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getWireframeColor();
}

const vector<string> EngineInterface::water_getIds() const
{
	vector<string> result;

	for(const auto & [waterId, entity] : _core->getWaterEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const float EngineInterface::water_getSize(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getSize();
}

const int EngineInterface::water_getTextureRepeat(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getTextureRepeat();
}

const fvec2 & EngineInterface::water_getRippleSpeed(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getRippleSpeed();
}

const fvec2 & EngineInterface::water_getWaveSpeed(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getWaveSpeed();
}

const float EngineInterface::water_getWaveHeight(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getWaveHeight();
}

const float EngineInterface::water_getSpecularShininess(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getSpecularShininess();
}

const float EngineInterface::water_getSpecularIntensity(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getSpecularIntensity();
}

const bool EngineInterface::water_isEdged(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->isEdged();
}

const string & EngineInterface::water_getDudvMapPath(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getDudvMapPath();
}

const string & EngineInterface::water_getNormalMapPath(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getNormalMapPath();
}

const string & EngineInterface::water_getHeightMapPath(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getHeightMapPath();
}

const float EngineInterface::water_getHeight(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getHeight();
}

const float EngineInterface::water_getMaxDepth(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getMaxDepth();
}

const fvec3 & EngineInterface::water_getColor(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getColor();
}

const fvec3 & EngineInterface::water_getMinClipPosition(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getMinClipPosition();
}

const fvec3 & EngineInterface::water_getMaxClipPosition(const string & waterId) const
{
	return _core->getWaterEntityManager()->getEntity(waterId)->getMaxClipPosition();
}

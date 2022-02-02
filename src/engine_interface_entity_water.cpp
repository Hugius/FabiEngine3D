#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::water_create(const string& id)
{
	_core->getWaterEntityManager()->createEntity(id);
}

void EngineInterface::water_deleteAll()
{
	for(const auto& [key, entity] : _core->getWaterEntityManager()->getEntities())
	{
		water_delete(entity->getId());
	}

	_core->getWaterEntityManager()->selectEntity("");
}

void EngineInterface::water_delete(const string& id)
{
	_core->getWaterEntityManager()->deleteEntity(id);
}

void EngineInterface::water_setVisible(const string& id, bool value)
{
	_core->getWaterEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::water_select(const string& id)
{
	_core->getWaterEntityManager()->selectEntity(id);
}

void EngineInterface::water_setHeight(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setHeight(value);
}

void EngineInterface::water_setSize(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setSize(value);
	_core->getWaterEntityManager()->loadMesh(id);
}

void EngineInterface::water_setSpecular(const string& id, bool value)
{
	_core->getWaterEntityManager()->getEntity(id)->setSpecular(value);
}

void EngineInterface::water_setTextureRepeat(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setTextureRepeat(value);
}

void EngineInterface::water_setReflective(const string& id, bool value)
{
	_core->getWaterEntityManager()->getEntity(id)->setReflective(value);
}

void EngineInterface::water_setRefractive(const string& id, bool value)
{
	_core->getWaterEntityManager()->getEntity(id)->setRefractive(value);
}

void EngineInterface::water_setWireframed(const string& id, bool value)
{
	_core->getWaterEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::water_setWireframeColor(const string& id, const fvec3& value)
{
	_core->getWaterEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::water_setDudvMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(id)->setDudvMap(nullptr);
		_core->getWaterEntityManager()->getEntity(id)->setDudvMapPath("");
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

		_core->getWaterEntityManager()->getEntity(id)->setDudvMap(texture);
		_core->getWaterEntityManager()->getEntity(id)->setDudvMapPath(value);
	}
}

void EngineInterface::water_setNormalMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(id)->setNormalMap(nullptr);
		_core->getWaterEntityManager()->getEntity(id)->setNormalMapPath("");
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

		_core->getWaterEntityManager()->getEntity(id)->setNormalMap(texture);
		_core->getWaterEntityManager()->getEntity(id)->setNormalMapPath(value);
	}
}

void EngineInterface::water_setDisplacementMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(id)->setDisplacementMap(nullptr);
		_core->getWaterEntityManager()->getEntity(id)->setDisplacementMapPath("");
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

		_core->getWaterEntityManager()->getEntity(id)->setDisplacementMap(texture);
		_core->getWaterEntityManager()->getEntity(id)->setDisplacementMapPath(value);
	}
}

void EngineInterface::water_setWaveHeight(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setWaveHeight(value);
}

void EngineInterface::water_setSpecularShininess(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setSpecularShininess(value);
}

void EngineInterface::water_setSpecularIntensity(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setSpecularIntensity(value);
}

void EngineInterface::water_setMaxDepth(const string& id, float value)
{
	_core->getWaterEntityManager()->getEntity(id)->setMaxDepth(value);
}

void EngineInterface::water_setRippleSpeed(const string& id, const fvec2& value)
{
	_core->getWaterEntityManager()->getEntity(id)->setRippleSpeed(value);
}

void EngineInterface::water_setWaveSpeed(const string& id, const fvec2& value)
{
	_core->getWaterEntityManager()->getEntity(id)->setWaveSpeed(value);
}

void EngineInterface::water_setColor(const string& id, const fvec3& value)
{
	_core->getWaterEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::water_setEdged(const string& id, bool value)
{
	_core->getWaterEntityManager()->getEntity(id)->setEdged(value);
}

const bool EngineInterface::water_isExisting(const string& id) const
{
	return _core->getWaterEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::water_isVisible(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::water_isSpecular(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->isSpecular();
}

const bool EngineInterface::water_isReflective(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->isReflective();
}

const bool EngineInterface::water_isRefractive(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->isRefractive();
}

const bool EngineInterface::water_isWireframed(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->isWireframed();
}

const bool EngineInterface::water_hasDudvMap(const string& id) const
{
	return (_core->getWaterEntityManager()->getEntity(id)->getDudvMap() != nullptr);
}

const bool EngineInterface::water_hasNormalMap(const string& id) const
{
	return (_core->getWaterEntityManager()->getEntity(id)->getNormalMap() != nullptr);
}

const bool EngineInterface::water_hasDisplacementMap(const string& id) const
{
	return (_core->getWaterEntityManager()->getEntity(id)->getDisplacementMap() != nullptr);
}

const string EngineInterface::water_getSelectedId() const
{
	if(_core->getWaterEntityManager()->getSelectedEntity() == nullptr)
	{
		return "";
	}

	return _core->getWaterEntityManager()->getSelectedEntity()->getId();
}

const fvec3& EngineInterface::water_getWireframeColor(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getWireframeColor();
}

const vector<string> EngineInterface::water_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getWaterEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const float EngineInterface::water_getSize(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getSize();
}

const float EngineInterface::water_getTextureRepeat(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getTextureRepeat();
}

const fvec2& EngineInterface::water_getRippleSpeed(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getRippleSpeed();
}

const fvec2& EngineInterface::water_getWaveSpeed(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getWaveSpeed();
}

const float EngineInterface::water_getWaveHeight(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getWaveHeight();
}

const float EngineInterface::water_getSpecularShininess(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getSpecularShininess();
}

const float EngineInterface::water_getSpecularIntensity(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getSpecularIntensity();
}

const bool EngineInterface::water_isEdged(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->isEdged();
}

const string& EngineInterface::water_getDudvMapPath(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getDudvMapPath();
}

const string& EngineInterface::water_getNormalMapPath(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getNormalMapPath();
}

const string& EngineInterface::water_getDisplacementMapPath(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getDisplacementMapPath();
}

const float EngineInterface::water_getHeight(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getHeight();
}

const float EngineInterface::water_getMaxDepth(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getMaxDepth();
}

const fvec3& EngineInterface::water_getColor(const string& id) const
{
	return _core->getWaterEntityManager()->getEntity(id)->getColor();
}
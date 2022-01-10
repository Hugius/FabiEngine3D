#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::water_create(const string& ID)
{
	_core->getWaterEntityManager()->createEntity(ID);
}

void EngineInterface::water_deleteAll()
{
	for(const auto& [key, entity] : _core->getWaterEntityManager()->getEntities())
	{
		water_delete(entity->getID());
	}

	_core->getWaterEntityManager()->selectWater("");
}

void EngineInterface::water_delete(const string& ID)
{
	_core->getWaterEntityManager()->deleteEntity(ID);
}

void EngineInterface::water_setVisible(const string& ID, bool value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::water_select(const string& ID)
{
	_core->getWaterEntityManager()->selectWater(ID);
}

void EngineInterface::water_setHeight(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setHeight(value);
}

void EngineInterface::water_setSize(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setSize(value);
	_core->getWaterEntityManager()->loadMesh(ID);
}

void EngineInterface::water_setSpecular(const string& ID, bool value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setSpecular(value);
}

void EngineInterface::water_setTextureRepeat(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setTextureRepeat(value);
}

void EngineInterface::water_setQuality(const string& ID, WaterQuality value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setQuality(value);
}

void EngineInterface::water_setReflective(const string& ID, bool value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setReflective(value);
}

void EngineInterface::water_setRefractive(const string& ID, bool value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setRefractive(value);
}

void EngineInterface::water_setWireframed(const string& ID, bool value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::water_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::water_setDudvMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(ID)->setDudvMap(0);
		_core->getWaterEntityManager()->getEntity(ID)->setDudvMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getWaterEntityManager()->getEntity(ID)->setDudvMap(texture);
		_core->getWaterEntityManager()->getEntity(ID)->setDudvMapPath(value);
	}
}

void EngineInterface::water_setNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(ID)->setNormalMap(0);
		_core->getWaterEntityManager()->getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getWaterEntityManager()->getEntity(ID)->setNormalMap(texture);
		_core->getWaterEntityManager()->getEntity(ID)->setNormalMapPath(value);
	}
}

void EngineInterface::water_setDisplacementMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getWaterEntityManager()->getEntity(ID)->setDisplacementMap(0);
		_core->getWaterEntityManager()->getEntity(ID)->setDisplacementMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));
			texture->loadMipMapping();
			texture->loadAnisotropicFiltering(_core->getRenderBus()->getAnisotropicFilteringQuality());

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getWaterEntityManager()->getEntity(ID)->setDisplacementMap(texture);
		_core->getWaterEntityManager()->getEntity(ID)->setDisplacementMapPath(value);
	}
}

void EngineInterface::water_setWaveHeight(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setWaveHeight(value);
}

void EngineInterface::water_setSpecularShininess(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setSpecularShininess(value);
}

void EngineInterface::water_setSpecularIntensity(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setSpecularIntensity(value);
}

void EngineInterface::water_setSpeed(const string& ID, fvec2 value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setSpeed(value);
}

void EngineInterface::water_setColor(const string& ID, fvec3 value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::water_setTransparency(const string& ID, float value)
{
	_core->getWaterEntityManager()->getEntity(ID)->setTransparency(value);
}
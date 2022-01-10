#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::terrain_create(const string& ID, const string& heightMapPath)
{
	_core->getTerrainEntityManager()->createEntity(ID, heightMapPath);
}

void EngineInterface::terrain_deleteAll()
{
	for(const auto& [key, entity] : _core->getTerrainEntityManager()->getEntities())
	{
		terrain_delete(entity->getID());
	}

	_core->getTerrainEntityManager()->selectTerrain("");
}

void EngineInterface::terrain_delete(const string& ID)
{
	_core->getTerrainEntityManager()->deleteEntity(ID);
}

void EngineInterface::terrain_setVisible(const string& ID, bool value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::terrain_select(const string& ID)
{
	_core->getTerrainEntityManager()->selectTerrain(ID);
}

void EngineInterface::terrain_setMaxHeight(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setMaxHeight(value);
	_core->getTerrainEntityManager()->loadMesh(ID);
}

void EngineInterface::terrain_setTextureRepeat(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setTextureRepeat(value);
}

void EngineInterface::terrain_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setDiffuseMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setNormalMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlendMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setBlendMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setBlendMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setBlendMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setBlendMapPath(value);
	}
}

void EngineInterface::terrain_setRedDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setRedDiffuseMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setRedDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setRedDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setRedDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setGreenDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenDiffuseMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setGreenDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setBlueDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueDiffuseMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setBlueDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setRedNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setRedNormalMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setRedNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setRedNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setRedNormalMapPath(value);
	}
}

void EngineInterface::terrain_setGreenNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenNormalMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setGreenNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlueNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueNormalMap(0);
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(ID)->setBlueNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueNormalMapPath(value);
	}
}

void EngineInterface::terrain_setRedTextureRepeat(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setRedTextureRepeat(value);
}

void EngineInterface::terrain_setGreenTextureRepeat(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setGreenTextureRepeat(value);
}

void EngineInterface::terrain_setBlueTextureRepeat(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setBlueTextureRepeat(value);
}

void EngineInterface::terrain_setSpecularShininess(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setSpecularShininess(value);
}

void EngineInterface::terrain_setSpecularIntensity(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setSpecularIntensity(value);
}

void EngineInterface::terrain_setLightness(const string& ID, float value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setLightness(value);
}

void EngineInterface::terrain_setSpecular(const string& ID, bool value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setSpecular(value);
}

void EngineInterface::terrain_setWireframed(const string& ID, bool value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::terrain_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getTerrainEntityManager()->getEntity(ID)->setWireframeColor(value);
}
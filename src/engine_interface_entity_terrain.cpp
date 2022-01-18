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
		_core->getTerrainEntityManager()->getEntity(ID)->setDiffuseMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setNormalMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setBlendMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setRedDiffuseMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenDiffuseMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueDiffuseMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setRedNormalMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setGreenNormalMap(nullptr);
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
		_core->getTerrainEntityManager()->getEntity(ID)->setBlueNormalMap(nullptr);
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

const bool EngineInterface::terrain_isExisting(const string& ID) const
{
	return _core->getTerrainEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::terrain_isVisible(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::terrain_isSpecular(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->isSpecular();
}

const bool EngineInterface::terrain_isWireframed(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->isWireframed();
}

const float EngineInterface::terrain_getSize(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getSize();
}

const float EngineInterface::terrain_getMaxHeight(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getMaxHeight();
}

const float EngineInterface::terrain_getTextureRepeat(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getTextureRepeat();
}

const bool EngineInterface::terrain_isInside(const string& ID, float x, float z) const
{
	return _core->getTerrainEntityManager()->isInside(ID, x, z);
}

const bool EngineInterface::terrain_hasBlendMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasBlendMap();
}

const bool EngineInterface::terrain_hasDiffuseMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::terrain_hasRedDiffuseMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasRedDiffuseMap();
}

const bool EngineInterface::terrain_hasGreenDiffuseMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasGreenDiffuseMap();
}

const bool EngineInterface::terrain_hasBlueDiffuseMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasBlueDiffuseMap();
}

const bool EngineInterface::terrain_hasNormalMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasNormalMap();
}

const bool EngineInterface::terrain_hasRedNormalMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasRedNormalMap();
}

const bool EngineInterface::terrain_hasGreenNormalMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasGreenNormalMap();
}

const bool EngineInterface::terrain_hasBlueNormalMap(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->hasBlueNormalMap();
}

const float EngineInterface::terrain_getPixelHeight(const string& ID, float x, float z) const
{
	return _core->getTerrainEntityManager()->getPixelHeight(ID, x, z);
}

const float EngineInterface::terrain_getSpecularShininess(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getSpecularShininess();
}

const float EngineInterface::terrain_getSpecularIntensity(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getSpecularIntensity();
}

const string EngineInterface::terrain_getSelectedID() const
{
	if(_core->getTerrainEntityManager()->getSelectedTerrain() == nullptr)
	{
		return "";
	}

	return _core->getTerrainEntityManager()->getSelectedTerrain()->getID();
}

const vector<string> EngineInterface::terrain_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getTerrainEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::terrain_getDiffuseMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const string& EngineInterface::terrain_getNormalMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getNormalMapPath();
}

const string& EngineInterface::terrain_getBlendMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getBlendMapPath();
}

const string& EngineInterface::terrain_getRedDiffuseMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getRedDiffuseMapPath();
}

const string& EngineInterface::terrain_getGreenDiffuseMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getGreenDiffuseMapPath();
}

const string& EngineInterface::terrain_getBlueDiffuseMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getBlueDiffuseMapPath();
}

const string& EngineInterface::terrain_getRedNormalMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getRedNormalMapPath();
}

const string& EngineInterface::terrain_getGreenNormalMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getGreenNormalMapPath();
}

const string& EngineInterface::terrain_getBlueNormalMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getBlueNormalMapPath();
}

const fvec3 EngineInterface::terrain_getWireframeColor(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getWireframeColor();
}

const float EngineInterface::terrain_getRedTextureRepeat(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getRedTextureRepeat();
}

const float EngineInterface::terrain_getGreenTextureRepeat(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getGreenTextureRepeat();
}

const float EngineInterface::terrain_getBlueTextureRepeat(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getBlueTextureRepeat();
}

const float EngineInterface::terrain_getLightness(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getLightness();
}

const string& EngineInterface::terrain_getHeightMapPath(const string& ID) const
{
	return _core->getTerrainEntityManager()->getEntity(ID)->getHeightMapPath();
}
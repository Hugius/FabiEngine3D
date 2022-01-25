#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::terrain_create(const string& id, const string& heightMapPath)
{
	_core->getTerrainEntityManager()->createEntity(id, heightMapPath);
}

void EngineInterface::terrain_deleteAll()
{
	for(const auto& [key, entity] : _core->getTerrainEntityManager()->getEntities())
	{
		terrain_delete(entity->getId());
	}

	_core->getTerrainEntityManager()->selectEntity("");
}

void EngineInterface::terrain_delete(const string& id)
{
	_core->getTerrainEntityManager()->deleteEntity(id);
}

void EngineInterface::terrain_setVisible(const string& id, bool value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::terrain_select(const string& id)
{
	_core->getTerrainEntityManager()->selectEntity(id);
}

void EngineInterface::terrain_setMaxHeight(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setMaxHeight(value);
	_core->getTerrainEntityManager()->loadMesh(id);
}

void EngineInterface::terrain_setTextureRepeat(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setTextureRepeat(value);
}

void EngineInterface::terrain_setDiffuseMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setNormalMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlendMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setBlendMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setBlendMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setBlendMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setBlendMapPath(value);
	}
}

void EngineInterface::terrain_setRedDiffuseMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setRedDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setRedDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setRedDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setRedDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setGreenDiffuseMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setGreenDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setGreenDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setGreenDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setGreenDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setBlueDiffuseMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setBlueDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setBlueDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setBlueDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setBlueDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setRedNormalMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setRedNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setRedNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setRedNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setRedNormalMapPath(value);
	}
}

void EngineInterface::terrain_setGreenNormalMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setGreenNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setGreenNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setGreenNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setGreenNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlueNormalMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(id)->setBlueNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(id)->setBlueNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(id)->setBlueNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(id)->setBlueNormalMapPath(value);
	}
}

void EngineInterface::terrain_setRedTextureRepeat(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setRedTextureRepeat(value);
}

void EngineInterface::terrain_setGreenTextureRepeat(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setGreenTextureRepeat(value);
}

void EngineInterface::terrain_setBlueTextureRepeat(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setBlueTextureRepeat(value);
}

void EngineInterface::terrain_setSpecularShininess(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setSpecularShininess(value);
}

void EngineInterface::terrain_setSpecularIntensity(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setSpecularIntensity(value);
}

void EngineInterface::terrain_setLightness(const string& id, float value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setLightness(value);
}

void EngineInterface::terrain_setSpecular(const string& id, bool value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setSpecular(value);
}

void EngineInterface::terrain_setWireframed(const string& id, bool value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::terrain_setWireframeColor(const string& id, const fvec3& value)
{
	_core->getTerrainEntityManager()->getEntity(id)->setWireframeColor(value);
}

const bool EngineInterface::terrain_isExisting(const string& id) const
{
	return _core->getTerrainEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::terrain_isVisible(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::terrain_isSpecular(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->isSpecular();
}

const bool EngineInterface::terrain_isWireframed(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->isWireframed();
}

const float EngineInterface::terrain_getSize(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getSize();
}

const float EngineInterface::terrain_getMaxHeight(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getMaxHeight();
}

const float EngineInterface::terrain_getTextureRepeat(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getTextureRepeat();
}

const bool EngineInterface::terrain_isInside(const string& id, float x, float z) const
{
	return _core->getTerrainEntityManager()->isInside(id, x, z);
}

const bool EngineInterface::terrain_hasBlendMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getBlendMap() != nullptr);
}

const bool EngineInterface::terrain_hasDiffuseMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getDiffuseMap() != nullptr);
}

const bool EngineInterface::terrain_hasRedDiffuseMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getRedDiffuseMap() != nullptr);
}

const bool EngineInterface::terrain_hasGreenDiffuseMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getGreenDiffuseMap() != nullptr);
}

const bool EngineInterface::terrain_hasBlueDiffuseMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getBlueDiffuseMap() != nullptr);
}

const bool EngineInterface::terrain_hasNormalMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getNormalMap() != nullptr);
}

const bool EngineInterface::terrain_hasRedNormalMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getRedNormalMap() != nullptr);
}

const bool EngineInterface::terrain_hasGreenNormalMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getGreenNormalMap() != nullptr);
}

const bool EngineInterface::terrain_hasBlueNormalMap(const string& id) const
{
	return (_core->getTerrainEntityManager()->getEntity(id)->getBlueNormalMap() != nullptr);
}

const float EngineInterface::terrain_getPixelHeight(const string& id, float x, float z) const
{
	return _core->getTerrainEntityManager()->getPixelHeight(id, x, z);
}

const float EngineInterface::terrain_getSpecularShininess(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getSpecularShininess();
}

const float EngineInterface::terrain_getSpecularIntensity(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getSpecularIntensity();
}

const string EngineInterface::terrain_getSelectedId() const
{
	if(_core->getTerrainEntityManager()->getSelectedEntity() == nullptr)
	{
		return "";
	}

	return _core->getTerrainEntityManager()->getSelectedEntity()->getId();
}

const vector<string> EngineInterface::terrain_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getTerrainEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const string& EngineInterface::terrain_getDiffuseMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getDiffuseMapPath();
}

const string& EngineInterface::terrain_getNormalMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getNormalMapPath();
}

const string& EngineInterface::terrain_getBlendMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getBlendMapPath();
}

const string& EngineInterface::terrain_getRedDiffuseMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getRedDiffuseMapPath();
}

const string& EngineInterface::terrain_getGreenDiffuseMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getGreenDiffuseMapPath();
}

const string& EngineInterface::terrain_getBlueDiffuseMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getBlueDiffuseMapPath();
}

const string& EngineInterface::terrain_getRedNormalMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getRedNormalMapPath();
}

const string& EngineInterface::terrain_getGreenNormalMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getGreenNormalMapPath();
}

const string& EngineInterface::terrain_getBlueNormalMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getBlueNormalMapPath();
}

const fvec3& EngineInterface::terrain_getWireframeColor(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getWireframeColor();
}

const float EngineInterface::terrain_getRedTextureRepeat(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getRedTextureRepeat();
}

const float EngineInterface::terrain_getGreenTextureRepeat(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getGreenTextureRepeat();
}

const float EngineInterface::terrain_getBlueTextureRepeat(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getBlueTextureRepeat();
}

const float EngineInterface::terrain_getLightness(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getLightness();
}

const string& EngineInterface::terrain_getHeightMapPath(const string& id) const
{
	return _core->getTerrainEntityManager()->getEntity(id)->getHeightMapPath();
}
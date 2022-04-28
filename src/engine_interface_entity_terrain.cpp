#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::terrain_create(const string & terrainId, const string & heightMapPath)
{
	_core->getTerrainEntityManager()->createEntity(terrainId, heightMapPath);
}

void EngineInterface::terrain_delete(const string & terrainId)
{
	_core->getTerrainEntityManager()->deleteEntity(terrainId);

	_core->getRaycastIntersector()->resetTerrainStatus(terrainId);
}

void EngineInterface::terrain_setVisible(const string & terrainId, bool value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setVisible(value);
}

void EngineInterface::terrain_select(const string & terrainId)
{
	_core->getTerrainEntityManager()->selectEntity(terrainId);

	if(terrainId.empty() || (terrainId != _core->getRaycastIntersector()->getTerrainId()))
	{
		_core->getRaycastIntersector()->resetTerrainStatus(terrainId);
	}
}

void EngineInterface::terrain_setMaxHeight(const string & terrainId, float value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setMaxHeight(value);
	_core->getTerrainEntityManager()->loadVertexBuffer(terrainId);
}

void EngineInterface::terrain_setTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setTextureRepeat(value);
}

void EngineInterface::terrain_setDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlendMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlendMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlendMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlendMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlendMapPath(value);
	}
}

void EngineInterface::terrain_setRedDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setGreenDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setBlueDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueDiffuseMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueDiffuseMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueDiffuseMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setRedNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setRedNormalMapPath(value);
	}
}

void EngineInterface::terrain_setGreenNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlueNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueNormalMap(nullptr);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueNormalMapPath("");
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

		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueNormalMap(texture);
		_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueNormalMapPath(value);
	}
}

void EngineInterface::terrain_setRedTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setRedTextureRepeat(value);
}

void EngineInterface::terrain_setGreenTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setGreenTextureRepeat(value);
}

void EngineInterface::terrain_setBlueTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setBlueTextureRepeat(value);
}

void EngineInterface::terrain_setSpecularShininess(const string & terrainId, float value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setSpecularShininess(value);
}

void EngineInterface::terrain_setSpecularIntensity(const string & terrainId, float value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setSpecularIntensity(value);
}

void EngineInterface::terrain_setLightness(const string & terrainId, float value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setLightness(value);
}

void EngineInterface::terrain_setSpecular(const string & terrainId, bool value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setSpecular(value);
}

void EngineInterface::terrain_setWireframed(const string & terrainId, bool value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setWireframed(value);
}

void EngineInterface::terrain_setWireframeColor(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setWireframeColor(value);
}

void EngineInterface::terrain_setMinClipPosition(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setMinClipPosition(value);
}

void EngineInterface::terrain_setMaxClipPosition(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainEntityManager()->getEntity(terrainId)->setMaxClipPosition(value);
}

const bool EngineInterface::terrain_isExisting(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->isEntityExisting(terrainId);
}

const bool EngineInterface::terrain_isVisible(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->isVisible();
}

const bool EngineInterface::terrain_isSpecular(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->isSpecular();
}

const bool EngineInterface::terrain_isWireframed(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->isWireframed();
}

const float EngineInterface::terrain_getSize(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getSize();
}

const float EngineInterface::terrain_getMaxHeight(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getMaxHeight();
}

const int EngineInterface::terrain_getTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getTextureRepeat();
}

const bool EngineInterface::terrain_isInside(const string & terrainId, float x, float z) const
{
	return _core->getTerrainEntityManager()->isInside(terrainId, x, z);
}

const bool EngineInterface::terrain_hasBlendMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getBlendTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasRedDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getRedDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasGreenDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getGreenDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasBlueDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getBlueDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasNormalMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasRedNormalMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getRedNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasGreenNormalMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getGreenNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasBlueNormalMap(const string & terrainId) const
{
	return (_core->getTerrainEntityManager()->getEntity(terrainId)->getBlueNormalTextureBuffer() != nullptr);
}

const float EngineInterface::terrain_getPixelHeight(const string & terrainId, float x, float z) const
{
	return _core->getTerrainEntityManager()->getPixelHeight(terrainId, x, z);
}

const float EngineInterface::terrain_getSpecularShininess(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getSpecularShininess();
}

const float EngineInterface::terrain_getSpecularIntensity(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getSpecularIntensity();
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

	for(const auto & [terrainId, entity] : _core->getTerrainEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const string & EngineInterface::terrain_getDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getDiffuseMapPath();
}

const string & EngineInterface::terrain_getNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getNormalMapPath();
}

const string & EngineInterface::terrain_getBlendMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getBlendMapPath();
}

const string & EngineInterface::terrain_getRedDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getRedDiffuseMapPath();
}

const string & EngineInterface::terrain_getGreenDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getGreenDiffuseMapPath();
}

const string & EngineInterface::terrain_getBlueDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getBlueDiffuseMapPath();
}

const string & EngineInterface::terrain_getRedNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getRedNormalMapPath();
}

const string & EngineInterface::terrain_getGreenNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getGreenNormalMapPath();
}

const string & EngineInterface::terrain_getBlueNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getBlueNormalMapPath();
}

const fvec3 & EngineInterface::terrain_getWireframeColor(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getWireframeColor();
}

const fvec3 & EngineInterface::terrain_getMinClipPosition(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getMinClipPosition();
}

const fvec3 & EngineInterface::terrain_getMaxClipPosition(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getMaxClipPosition();
}

const int EngineInterface::terrain_getRedTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getRedTextureRepeat();
}

const int EngineInterface::terrain_getGreenTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getGreenTextureRepeat();
}

const int EngineInterface::terrain_getBlueTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getBlueTextureRepeat();
}

const float EngineInterface::terrain_getLightness(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getLightness();
}

const string & EngineInterface::terrain_getHeightMapPath(const string & terrainId) const
{
	return _core->getTerrainEntityManager()->getEntity(terrainId)->getHeightMapPath();
}
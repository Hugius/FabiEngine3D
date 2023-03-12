#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::terrain_create(const string & terrainId, const string & heightMapPath)
{
	_core->getTerrainManager()->createTerrain(terrainId, heightMapPath);
}

void EngineInterface::terrain_delete(const string & terrainId)
{
	_core->getTerrainManager()->deleteTerrain(terrainId);
}

void EngineInterface::terrain_select(const string & terrainId)
{
	_core->getTerrainManager()->selectTerrain(terrainId);
}

void EngineInterface::terrain_setMaxHeight(const string & terrainId, float value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setMaxHeight(value);
	_core->getTerrainManager()->loadTerrainVertexBuffer(terrainId);
}

void EngineInterface::terrain_setTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setTextureRepeat(value);
}

void EngineInterface::terrain_setDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setDiffuseMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setDiffuseMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setNormalMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setNormalMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setNormalMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlendMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setBlendMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setBlendMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setBlendMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setBlendMapPath(value);
	}
}

void EngineInterface::terrain_setRedDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setRedDiffuseMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setRedDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setRedDiffuseMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setRedDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setGreenDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setGreenDiffuseMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setGreenDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setGreenDiffuseMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setGreenDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setBlueDiffuseMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setBlueDiffuseMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setBlueDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setBlueDiffuseMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setBlueDiffuseMapPath(value);
	}
}

void EngineInterface::terrain_setRedNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setRedNormalMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setRedNormalMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setRedNormalMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setRedNormalMapPath(value);
	}
}

void EngineInterface::terrain_setGreenNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setGreenNormalMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setGreenNormalMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setGreenNormalMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setGreenNormalMapPath(value);
	}
}

void EngineInterface::terrain_setBlueNormalMap(const string & terrainId, const string & value)
{
	if(value.empty())
	{
		_core->getTerrainManager()->getTerrain(terrainId)->setBlueNormalMap(nullptr);
		_core->getTerrainManager()->getTerrain(terrainId)->setBlueNormalMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				texture->loadMipMapping();
				texture->loadAnisotropicFiltering(_core->getRenderStorage()->getAnisotropicFilteringQuality());

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getTerrainManager()->getTerrain(terrainId)->setBlueNormalMap(texture);
		_core->getTerrainManager()->getTerrain(terrainId)->setBlueNormalMapPath(value);
	}
}

void EngineInterface::terrain_setRedTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setRedTextureRepeat(value);
}

void EngineInterface::terrain_setGreenTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setGreenTextureRepeat(value);
}

void EngineInterface::terrain_setBlueTextureRepeat(const string & terrainId, int value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setBlueTextureRepeat(value);
}

void EngineInterface::terrain_setSpecularShininess(const string & terrainId, float value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setSpecularShininess(value);
}

void EngineInterface::terrain_setSpecularIntensity(const string & terrainId, float value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setSpecularIntensity(value);
}

void EngineInterface::terrain_setLightness(const string & terrainId, float value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setLightness(value);
}

void EngineInterface::terrain_setSpecular(const string & terrainId, bool value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setSpecular(value);
}

void EngineInterface::terrain_setShadowed(const string & terrainId, bool value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setShadowed(value);
}

void EngineInterface::terrain_setWireframed(const string & terrainId, bool value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setWireframed(value);
}

void EngineInterface::terrain_setWireframeColor(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setWireframeColor(value);
}

void EngineInterface::terrain_setColor(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setColor(value);
}

void EngineInterface::terrain_setMinClipPosition(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setMinClipPosition(value);
}

void EngineInterface::terrain_setMaxClipPosition(const string & terrainId, const fvec3 & value)
{
	_core->getTerrainManager()->getTerrain(terrainId)->setMaxClipPosition(value);
}

const bool EngineInterface::terrain_isExisting(const string & terrainId) const
{
	return _core->getTerrainManager()->isTerrainExisting(terrainId);
}

const bool EngineInterface::terrain_isSpecular(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->isSpecular();
}

const bool EngineInterface::terrain_isWireframed(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->isWireframed();
}

const bool EngineInterface::terrain_isShadowed(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->isShadowed();
}

const float EngineInterface::terrain_getSize(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getSize();
}

const float EngineInterface::terrain_getMaxHeight(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getMaxHeight();
}

const int EngineInterface::terrain_getTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getTextureRepeat();
}

const bool EngineInterface::terrain_isInside(const string & terrainId, float x, float z) const
{
	return _core->getTerrainManager()->isInside(terrainId, x, z);
}

const bool EngineInterface::terrain_hasBlendMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getBlendTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasRedDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getRedDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasGreenDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getGreenDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasBlueDiffuseMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getBlueDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasNormalMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasRedNormalMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getRedNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasGreenNormalMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getGreenNormalTextureBuffer() != nullptr);
}

const bool EngineInterface::terrain_hasBlueNormalMap(const string & terrainId) const
{
	return (_core->getTerrainManager()->getTerrain(terrainId)->getBlueNormalTextureBuffer() != nullptr);
}

const float EngineInterface::terrain_getPixelHeight(const string & terrainId, float x, float z) const
{
	return _core->getTerrainManager()->getTerrainPixelHeight(terrainId, x, z);
}

const float EngineInterface::terrain_getSpecularShininess(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getSpecularShininess();
}

const float EngineInterface::terrain_getSpecularIntensity(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getSpecularIntensity();
}

const string EngineInterface::terrain_getSelectedId() const
{
	if(_core->getTerrainManager()->getSelectedTerrain() == nullptr)
	{
		return "";
	}

	return _core->getTerrainManager()->getSelectedTerrain()->getId();
}

const vector<string> EngineInterface::terrain_getIds() const
{
	vector<string> result = {};

	for(const auto & [terrainId, terrain] : _core->getTerrainManager()->getTerrains())
	{
		result.push_back(terrain->getId());
	}

	return result;
}

const string & EngineInterface::terrain_getDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getDiffuseMapPath();
}

const string & EngineInterface::terrain_getNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getNormalMapPath();
}

const string & EngineInterface::terrain_getBlendMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getBlendMapPath();
}

const string & EngineInterface::terrain_getRedDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getRedDiffuseMapPath();
}

const string & EngineInterface::terrain_getGreenDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getGreenDiffuseMapPath();
}

const string & EngineInterface::terrain_getBlueDiffuseMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getBlueDiffuseMapPath();
}

const string & EngineInterface::terrain_getRedNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getRedNormalMapPath();
}

const string & EngineInterface::terrain_getGreenNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getGreenNormalMapPath();
}

const string & EngineInterface::terrain_getBlueNormalMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getBlueNormalMapPath();
}

const fvec3 & EngineInterface::terrain_getWireframeColor(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getWireframeColor();
}

const fvec3 & EngineInterface::terrain_getColor(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getColor();
}

const fvec3 & EngineInterface::terrain_getMinClipPosition(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getMinClipPosition();
}

const fvec3 & EngineInterface::terrain_getMaxClipPosition(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getMaxClipPosition();
}

const int EngineInterface::terrain_getRedTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getRedTextureRepeat();
}

const int EngineInterface::terrain_getGreenTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getGreenTextureRepeat();
}

const int EngineInterface::terrain_getBlueTextureRepeat(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getBlueTextureRepeat();
}

const float EngineInterface::terrain_getLightness(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getLightness();
}

const string & EngineInterface::terrain_getHeightMapPath(const string & terrainId) const
{
	return _core->getTerrainManager()->getTerrain(terrainId)->getHeightMapPath();
}
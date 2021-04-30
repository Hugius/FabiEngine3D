#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::terrainEntity_add(const string& ID, const string& heightMapPath)
{
	_core->_terrainEntityManager.addTerrainEntity(ID);
	terrainEntity_setHeightmap(ID, heightMapPath);
}

void FabiEngine3D::terrainEntity_setHeightmap(const string& ID, const string& heightMapPath)
{
	auto pixelValues = _core->_textureLoader.getBitmapPixels(heightMapPath);

	// Check if heightmap loading went well
	if (pixelValues != nullptr)
	{
		_core->_terrainEntityManager.getEntity(ID)->setHeightMapPath(heightMapPath);
		_core->_terrainEntityManager.getEntity(ID)->setPixelValues(*pixelValues);
		_core->_terrainEntityManager.getEntity(ID)->setSize(static_cast<float>(sqrt(pixelValues->size())));
		_core->_terrainEntityManager.generateMesh(ID);
	}
}

void FabiEngine3D::terrainEntity_deleteAll()
{
	// For every terrain entity
	for (auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		terrainEntity_delete(entity->getID());
	}

	// Unselect terrain
	_core->_terrainEntityManager.selectTerrain("");
}

void FabiEngine3D::terrainEntity_delete(const string& ID)
{
	// Unselect terrain if selected
	if (ID == terrainEntity_getSelectedID())
	{
		_core->_terrainEntityManager.selectTerrain("");
	}

	_core->_terrainEntityManager.deleteEntity(ID);
}

void FabiEngine3D::terrainEntity_hide(const string& ID)
{
	_core->_terrainEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::terrainEntity_show(const string& ID)
{
	_core->_terrainEntityManager.getEntity(ID)->setVisible(true);
}

bool FabiEngine3D::terrainEntity_isExisting(const string& ID)
{
	return _core->_terrainEntityManager.isExisting(ID);
}

bool FabiEngine3D::terrainEntity_isVisible(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::terrainEntity_isSpecularLighted(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isSpecularLighted();
}

bool FabiEngine3D::terrainEntity_isNormalMapped(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isNormalMapped();
}

bool FabiEngine3D::terrainEntity_isNormalMappedR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isNormalMappedR();
}

bool FabiEngine3D::terrainEntity_isNormalMappedG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isNormalMappedG();
}

bool FabiEngine3D::terrainEntity_isNormalMappedB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isNormalMappedB();
}

bool FabiEngine3D::terrainEntity_isBlendMapped(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->isBlendMapped();
}

float FabiEngine3D::terrainEntity_getSize(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSize();
}

float FabiEngine3D::terrainEntity_getMaxHeight(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getMaxHeight();
}

float FabiEngine3D::terrainEntity_getUvRepeat(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getUvRepeat();
}

bool FabiEngine3D::terrainEntity_isInside(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.isInside(ID, x, z);
}

float FabiEngine3D::terrainEntity_getPixelHeight(const string& ID, float x, float z)
{
	return _core->_terrainEntityManager.getPixelHeight(ID, x, z);
}

float FabiEngine3D::terrainEntity_getSpecularLightingFactor(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularLightingFactor();
}

float FabiEngine3D::terrainEntity_getSpecularLightingIntensity(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getSpecularLightingIntensity();
}

string FabiEngine3D::terrainEntity_getSelectedID()
{
	if (_core->_terrainEntityManager.getSelectedTerrain() != nullptr)
	{
		return _core->_terrainEntityManager.getSelectedTerrain()->getID();
	}
	else
	{
		return "";
	}
}

vector<string> FabiEngine3D::terrainEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_terrainEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::terrainEntity_getDiffuseMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPath();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendMapPath();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathR();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathG();
}

const string& FabiEngine3D::terrainEntity_getBlendMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getDiffuseMapPathB();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathR();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathG();
}

const string& FabiEngine3D::terrainEntity_getNormalMapPathB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getNormalMapPathB();
}

float FabiEngine3D::terrainEntity_getBlendRepeatR(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatR();
}

float FabiEngine3D::terrainEntity_getBlendRepeatG(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatG();
}

float FabiEngine3D::terrainEntity_getBlendRepeatB(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getBlendRepeatB();
}

float FabiEngine3D::terrainEntity_getLightness(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getLightness();
}

const string& FabiEngine3D::terrainEntity_getHeightMapPath(const string& ID)
{
	return _core->_terrainEntityManager.getEntity(ID)->getHeightMapPath();
}

void FabiEngine3D::terrainEntity_select(const string& ID)
{
	_core->_terrainEntityManager.selectTerrain(ID);
}

void FabiEngine3D::terrainEntity_setMaxHeight(const string& ID, float height)
{
	_core->_terrainEntityManager.getEntity(ID)->setMaxHeight(height);

	// Check if terrain mesh is loaded
	if (!_core->_terrainEntityManager.getEntity(ID)->getPixelValues().empty())
	{	
		_core->_terrainEntityManager.generateMesh(ID);

		// Load normal mapping again
		if (_core->_terrainEntityManager.getEntity(ID)->isNormalMapped())
		{
			_core->_terrainEntityManager.loadNormalMapping(ID);
		}
	}
}

void FabiEngine3D::terrainEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setUvRepeat(repeat);

	// Check if terrain mesh is loaded
	if (!_core->_terrainEntityManager.getEntity(ID)->getPixelValues().empty())
	{
		_core->_terrainEntityManager.generateMesh(ID);

		// Load normal mapping again
		if (_core->_terrainEntityManager.getEntity(ID)->isNormalMapped())
		{
			_core->_terrainEntityManager.loadNormalMapping(ID);
		}
	}
}

void FabiEngine3D::terrainEntity_setDiffuseMap(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPath(texturePath);
}

void FabiEngine3D::terrainEntity_setNormalMap(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMap(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapPath(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendMap(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMap(_core->_textureLoader.getTexture2D(texturePath, true, true, false));
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapPath(texturePath);
}

void FabiEngine3D::terrainEntity_setDiffuseMapR(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapR(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathR(texturePath);
}

void FabiEngine3D::terrainEntity_setDiffuseMapG(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapG(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathG(texturePath);
}

void FabiEngine3D::terrainEntity_setDiffuseMapB(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapB(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setDiffuseMapPathB(texturePath);
}

void FabiEngine3D::terrainEntity_setNormalMapR(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapR(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathR(texturePath);
}

void FabiEngine3D::terrainEntity_setNormalMapG(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapG(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathG(texturePath);
}

void FabiEngine3D::terrainEntity_setNormalMapB(const string& ID, const string& texturePath)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapB(_core->_textureLoader.getTexture2D(texturePath, true, true, true));
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapPathB(texturePath);
}

void FabiEngine3D::terrainEntity_setBlendRepeatR(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatR(repeat);
}

void FabiEngine3D::terrainEntity_setBlendRepeatG(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatG(repeat);
}

void FabiEngine3D::terrainEntity_setBlendRepeatB(const string& ID, float repeat)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendRepeatB(repeat);
}

void FabiEngine3D::terrainEntity_setSpecularLightingFactor(const string& ID, float factor)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLightingFactor(factor);
}

void FabiEngine3D::terrainEntity_setSpecularLightingIntensity(const string& ID, float intensity)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLightingIntensity(intensity);
}

void FabiEngine3D::terrainEntity_setLightness(const string& ID, float lightness)
{
	_core->_terrainEntityManager.getEntity(ID)->setLightness(lightness);
}

void FabiEngine3D::terrainEntity_setSpecularLighted(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setSpecularLighted(enabled);
}

void FabiEngine3D::terrainEntity_setNormalMapped(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMapped(enabled);

	// Calculate normal mapping tangents
	if (enabled)
	{
		_core->_terrainEntityManager.loadNormalMapping(ID);
	}
}

void FabiEngine3D::terrainEntity_setNormalMappedR(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMappedR(enabled);

	// Calculate normal mapping tangents
	if (enabled)
	{
		_core->_terrainEntityManager.loadNormalMapping(ID);
	}
}

void FabiEngine3D::terrainEntity_setNormalMappedG(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMappedG(enabled);

	// Calculate normal mapping tangents
	if (enabled)
	{
		_core->_terrainEntityManager.loadNormalMapping(ID);
	}
}

void FabiEngine3D::terrainEntity_setNormalMappedB(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setNormalMappedB(enabled);

	// Calculate normal mapping tangents
	if (enabled)
	{
		_core->_terrainEntityManager.loadNormalMapping(ID);
	}
}

void FabiEngine3D::terrainEntity_setBlendMapped(const string& ID, bool enabled)
{
	_core->_terrainEntityManager.getEntity(ID)->setBlendMapped(enabled);
}
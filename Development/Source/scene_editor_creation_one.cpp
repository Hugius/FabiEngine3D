#include "scene_editor.hpp"

void SceneEditor::_placeSky(const string& newID, const string& previewID)
{
	// If editing scene, save ID
	if (!_currentSceneID.empty())
	{
		_loadedSkyID = newID;
	}

	// Delete old
	if (_fe3d.skyEntity_isExisting(newID))
	{
		_fe3d.skyEntity_delete(newID);
	}

	// Create new
	_fe3d.skyEntity_add(newID);
	_fe3d.skyEntity_setDiffuseMaps(newID, _fe3d.skyEntity_getDiffuseMapPaths(previewID));
	_fe3d.skyEntity_setLightness(newID, _fe3d.skyEntity_getLightness(previewID));
	_fe3d.skyEntity_setRotationSpeed(newID, _fe3d.skyEntity_getRotationSpeed(previewID));
	_fe3d.skyEntity_setColor(newID, _fe3d.skyEntity_getColor(previewID));
	_fe3d.skyEntity_select(newID);
}

void SceneEditor::_placeSky(const string& newID, const array<string, 6>& diffuseMapPaths, float lightness, float rotationSpeed, Vec3 color)
{
	_loadedSkyID = newID;

	// Delete old
	if (_fe3d.skyEntity_isExisting(newID))
	{
		_fe3d.skyEntity_delete(newID);
	}

	// Create new
	_fe3d.skyEntity_add(newID);
	_fe3d.skyEntity_setDiffuseMaps(newID, diffuseMapPaths);
	_fe3d.skyEntity_setLightness(newID, lightness);
	_fe3d.skyEntity_setRotationSpeed(newID, rotationSpeed);
	_fe3d.skyEntity_setColor(newID, color);
	_fe3d.skyEntity_select(newID);
}

void SceneEditor::_placeTerrain(const string& newID, const string& previewID)
{
	// If editing scene, save ID
	if (!_currentSceneID.empty())
	{
		_loadedTerrainID = newID;
	}

	// Delete old
	if (_fe3d.terrainEntity_isExisting(newID))
	{
		_fe3d.terrainEntity_delete(newID);
	}

	// Create TERRAIN entity
	_fe3d.terrainEntity_add(newID, _fe3d.terrainEntity_getHeightMapPath(previewID));
	_fe3d.terrainEntity_select(newID);

	// Fill TERRAIN entity
	_fe3d.terrainEntity_setMaxHeight(newID, _fe3d.terrainEntity_getMaxHeight(previewID));
	_fe3d.terrainEntity_setUvRepeat(newID, _fe3d.terrainEntity_getUvRepeat(previewID));
	_fe3d.terrainEntity_setBlendMapped(newID, _fe3d.terrainEntity_isBlendMapped(previewID));
	_fe3d.terrainEntity_setLightness(newID, _fe3d.terrainEntity_getLightness(previewID));
	_fe3d.terrainEntity_setBlendRepeatR(newID, _fe3d.terrainEntity_getBlendRepeatR(previewID));
	_fe3d.terrainEntity_setBlendRepeatG(newID, _fe3d.terrainEntity_getBlendRepeatG(previewID));
	_fe3d.terrainEntity_setBlendRepeatB(newID, _fe3d.terrainEntity_getBlendRepeatB(previewID));
	_fe3d.terrainEntity_setNormalMapped(newID, _fe3d.terrainEntity_isNormalMapped(previewID));
	_fe3d.terrainEntity_setNormalMappedR(newID, _fe3d.terrainEntity_isNormalMappedR(previewID));
	_fe3d.terrainEntity_setNormalMappedG(newID, _fe3d.terrainEntity_isNormalMappedG(previewID));
	_fe3d.terrainEntity_setNormalMappedB(newID, _fe3d.terrainEntity_isNormalMappedB(previewID));
	_fe3d.terrainEntity_setSpecularLighted(newID, _fe3d.terrainEntity_isSpecularLighted(previewID));
	_fe3d.terrainEntity_setSpecularLightingFactor(newID, _fe3d.terrainEntity_getSpecularLightingFactor(previewID));
	_fe3d.terrainEntity_setSpecularLightingIntensity(newID, _fe3d.terrainEntity_getSpecularLightingIntensity(previewID));

	// Diffuse map
	if (_fe3d.terrainEntity_getDiffuseMapPath(previewID) != "")
	{
		_fe3d.terrainEntity_setDiffuseMap(newID, _fe3d.terrainEntity_getDiffuseMapPath(previewID));
	}

	// Normal map
	if (_fe3d.terrainEntity_getNormalMapPath(previewID) != "")
	{
		_fe3d.terrainEntity_setNormalMap(newID, _fe3d.terrainEntity_getNormalMapPath(previewID));
	}

	// Normal map R
	if (_fe3d.terrainEntity_getNormalMapPathR(previewID) != "")
	{
		_fe3d.terrainEntity_setNormalMapR(newID, _fe3d.terrainEntity_getNormalMapPathR(previewID));
	}

	// Normal map G
	if (_fe3d.terrainEntity_getNormalMapPathG(previewID) != "")
	{
		_fe3d.terrainEntity_setNormalMapG(newID, _fe3d.terrainEntity_getNormalMapPathG(previewID));
	}

	// Normal map B
	if (_fe3d.terrainEntity_getNormalMapPathB(previewID) != "")
	{
		_fe3d.terrainEntity_setNormalMapB(newID, _fe3d.terrainEntity_getNormalMapPathB(previewID));
	}

	// Blend map
	if (_fe3d.terrainEntity_getBlendMapPath(previewID) != "")
	{
		_fe3d.terrainEntity_setBlendMap(newID, _fe3d.terrainEntity_getBlendMapPath(previewID));
	}

	// Blend map red
	if (_fe3d.terrainEntity_getBlendMapPathR(previewID) != "")
	{
		_fe3d.terrainEntity_setDiffuseMapR(newID, _fe3d.terrainEntity_getBlendMapPathR(previewID));
	}

	// Blend map green
	if (_fe3d.terrainEntity_getBlendMapPathG(previewID) != "")
	{
		_fe3d.terrainEntity_setDiffuseMapG(newID, _fe3d.terrainEntity_getBlendMapPathG(previewID));
	}

	// Blend map blue
	if (_fe3d.terrainEntity_getBlendMapPathB(previewID) != "")
	{
		_fe3d.terrainEntity_setDiffuseMapB(newID, _fe3d.terrainEntity_getBlendMapPathB(previewID));
	}
}

void SceneEditor::_placeTerrain(const string& newID, const string& heightMapPath, float maxHeight, float uvRepeat, bool isBlendMapped, 
	float lightness, float blendRepeatR, float blendRepeatG, float blendRepeatB, bool isNormalMapped, bool isNormalMappedR, bool isNormalMappedG,
	bool isNormalMappedB, bool isSpecular, float specularFactor,
	float specularIntensity, const string& diffuseMapPath, const string& normalMapPath, const string& normalMapPathR,
	const string& normalMapPathG, const string& normalMapPathB, const string& blendMapPath,
	const string& blendMapPathR, const string& blendMapPathG, const string& blendMapPathB)
{
	_loadedTerrainID = newID;

	// Delete old
	if (_fe3d.terrainEntity_isExisting(newID))
	{
		_fe3d.terrainEntity_delete(newID);
	}

	// Create TERRAIN entity
	_fe3d.terrainEntity_add(newID, heightMapPath);
	_fe3d.terrainEntity_select(newID);

	// Fill TERRAIN entity
	_fe3d.terrainEntity_setMaxHeight(newID, maxHeight);
	_fe3d.terrainEntity_setUvRepeat(newID, uvRepeat);
	_fe3d.terrainEntity_setBlendMapped(newID, isBlendMapped);
	_fe3d.terrainEntity_setLightness(newID, lightness);
	_fe3d.terrainEntity_setBlendRepeatR(newID, blendRepeatR);
	_fe3d.terrainEntity_setBlendRepeatG(newID, blendRepeatG);
	_fe3d.terrainEntity_setBlendRepeatB(newID, blendRepeatB);
	_fe3d.terrainEntity_setNormalMapped(newID, isNormalMapped);
	_fe3d.terrainEntity_setNormalMappedR(newID, isNormalMappedR);
	_fe3d.terrainEntity_setNormalMappedG(newID, isNormalMappedG);
	_fe3d.terrainEntity_setNormalMappedB(newID, isNormalMappedB);
	_fe3d.terrainEntity_setSpecularLighted(newID, isSpecular);
	_fe3d.terrainEntity_setSpecularLightingFactor(newID, specularFactor);
	_fe3d.terrainEntity_setSpecularLightingIntensity(newID, specularIntensity);

	// Texture maps
	if (diffuseMapPath != "") _fe3d.terrainEntity_setDiffuseMap(newID, diffuseMapPath);
	if (normalMapPath != "") _fe3d.terrainEntity_setNormalMap(newID, normalMapPath);
	if (normalMapPathR != "") _fe3d.terrainEntity_setNormalMapR(newID, normalMapPathR);
	if (normalMapPathG != "") _fe3d.terrainEntity_setNormalMapG(newID, normalMapPathG);
	if (normalMapPathB != "") _fe3d.terrainEntity_setNormalMapB(newID, normalMapPathB);
	if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap(newID, blendMapPath);
	if (blendMapPathR != "")  _fe3d.terrainEntity_setDiffuseMapR(newID, blendMapPathR);
	if (blendMapPathG != "")  _fe3d.terrainEntity_setDiffuseMapG(newID, blendMapPathG);
	if (blendMapPathB != "")  _fe3d.terrainEntity_setDiffuseMapB(newID, blendMapPathB);
}

void SceneEditor::_placeWater(const string& newID, const string& previewID)
{
	// If editing scene, save ID
	if (!_currentSceneID.empty())
	{
		_loadedWaterID = newID;
	}

	// Delete old
	if (_fe3d.waterEntity_isExisting(newID))
	{
		_fe3d.waterEntity_delete(newID);
	}

	// Create WATER entity
	_fe3d.waterEntity_add(newID);

	// Fill WATER entity
	_fe3d.waterEntity_setPosition(newID, _fe3d.waterEntity_getPosition(previewID));
	_fe3d.waterEntity_setSize(newID, _fe3d.waterEntity_getSize(previewID));
	_fe3d.waterEntity_setWaving(newID, _fe3d.waterEntity_isWaving(previewID));
	_fe3d.waterEntity_setRippling(newID, _fe3d.waterEntity_isRippling(previewID));
	_fe3d.waterEntity_setSpecularLighted(newID, _fe3d.waterEntity_isSpecularLighted(previewID));
	_fe3d.waterEntity_setReflective(newID, _fe3d.waterEntity_isReflective(previewID));
	_fe3d.waterEntity_setRefractive(newID, _fe3d.waterEntity_isRefractive(previewID));
	_fe3d.waterEntity_setWaveHeightFactor(newID, _fe3d.waterEntity_getWaveHeightFactor(previewID));
	_fe3d.waterEntity_setSpecularLightingFactor(newID, _fe3d.waterEntity_getSpecularLightingFactor(previewID));
	_fe3d.waterEntity_setSpecularLightingIntensity(newID, _fe3d.waterEntity_getSpecularLightingIntensity(previewID));
	_fe3d.waterEntity_setTransparency(newID, _fe3d.waterEntity_getTransparency(previewID));
	_fe3d.waterEntity_setColor(newID, _fe3d.waterEntity_getColor(previewID));
	_fe3d.waterEntity_setUvRepeat(newID, _fe3d.waterEntity_getUvRepeat(previewID));
	_fe3d.waterEntity_setSpeed(newID, _fe3d.waterEntity_getSpeed(previewID));

	// DUDV map
	if (_fe3d.waterEntity_getDudvMapPath(previewID) != "")
	{
		_fe3d.waterEntity_setDudvMap(newID, _fe3d.waterEntity_getDudvMapPath(previewID));
	}

	// Normal map
	if (_fe3d.waterEntity_getNormalMapPath(previewID) != "")
	{
		_fe3d.waterEntity_setNormalMap(newID, _fe3d.waterEntity_getNormalMapPath(previewID));
	}

	// Displacement map
	if (_fe3d.waterEntity_getDisplacementMapPath(previewID) != "")
	{
		_fe3d.waterEntity_setDisplacementMap(newID, _fe3d.waterEntity_getDisplacementMapPath(previewID));
	}
}

void SceneEditor::_placeWater(const string& newID, Vec3 position, float size, bool isWaving, bool isRippling, bool isSpecularLighted, bool isReflective,
	bool isRefractive, float waveHeightFactor, float specularFactor, float specularIntensity, float transparency, Vec3 color, float uvRepeat, Vec2 speed,
	const string& dudvMapPath, const string& normalMapPath, const string& displacementMapPath)
{
	_loadedWaterID = newID;

	// Delete old
	if (_fe3d.waterEntity_isExisting(newID))
	{
		_fe3d.waterEntity_delete(newID);
	}

	// Create WATER entity
	_fe3d.waterEntity_add(newID);
	_fe3d.waterEntity_select(newID);

	// Fill WATER entity
	_fe3d.waterEntity_setPosition(newID, position);
	_fe3d.waterEntity_setSize(newID, size);
	_fe3d.waterEntity_setWaving(newID, isWaving);
	_fe3d.waterEntity_setRippling(newID, isRippling);
	_fe3d.waterEntity_setSpecularLighted(newID, isSpecularLighted);
	_fe3d.waterEntity_setReflective(newID, isReflective);
	_fe3d.waterEntity_setRefractive(newID, isRefractive);
	_fe3d.waterEntity_setWaveHeightFactor(newID, waveHeightFactor);
	_fe3d.waterEntity_setSpecularLightingFactor(newID, specularFactor);
	_fe3d.waterEntity_setSpecularLightingIntensity(newID, specularIntensity);
	_fe3d.waterEntity_setTransparency(newID, transparency);
	_fe3d.waterEntity_setColor(newID, color);
	_fe3d.waterEntity_setUvRepeat(newID, uvRepeat);
	_fe3d.waterEntity_setSpeed(newID, speed);

	// Texture maps
	if (dudvMapPath != "") _fe3d.waterEntity_setDudvMap(newID, dudvMapPath);
	if (normalMapPath != "") _fe3d.waterEntity_setNormalMap(newID, normalMapPath);
	if (displacementMapPath != "") _fe3d.waterEntity_setDisplacementMap(newID, displacementMapPath);
}
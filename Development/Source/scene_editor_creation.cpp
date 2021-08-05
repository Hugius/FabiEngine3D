#include "scene_editor.hpp"
#include "logger.hpp"

bool SceneEditor::_copyPreviewSky(const string& newID, const string& previewID)
{
	// Error checking
	if (_fe3d.skyEntity_isExisting(newID))
	{
		Logger::throwWarning("Scene sky with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.skyEntity_isExisting(previewID))
	{
		Logger::throwWarning("Base sky of scene sky with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create new sky
	_fe3d.skyEntity_create(newID);
	_fe3d.skyEntity_setDiffuseMaps(newID, _fe3d.skyEntity_getDiffuseMapPaths(previewID));
	_fe3d.skyEntity_setLightness(newID, _fe3d.skyEntity_getLightness(previewID));
	_fe3d.skyEntity_setRotationSpeed(newID, _fe3d.skyEntity_getRotationSpeed(previewID));
	_fe3d.skyEntity_setColor(newID, _fe3d.skyEntity_getColor(previewID));
	_fe3d.skyEntity_selectMainSky(newID);

	// Save ID
	_loadedSkyID = newID;

	return true;
}

bool SceneEditor::_copyPreviewTerrain(const string& newID, const string& previewID)
{
	// Error checking
	if (_fe3d.terrainEntity_isExisting(newID))
	{
		Logger::throwWarning("Scene terrain with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.terrainEntity_isExisting(previewID))
	{
		Logger::throwWarning("Base terrain of scene terrain with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if (_fe3d.terrainEntity_isExisting(newID))
	{
		_fe3d.terrainEntity_delete(newID);
	}

	// Create terrain entity
	_fe3d.terrainEntity_create(newID, _fe3d.terrainEntity_getHeightMapPath(previewID));
	_fe3d.terrainEntity_select(newID);

	// Fill terrain entity
	_fe3d.terrainEntity_setMaxHeight(newID, _fe3d.terrainEntity_getMaxHeight(previewID));
	_fe3d.terrainEntity_setUvRepeat(newID, _fe3d.terrainEntity_getUvRepeat(previewID));
	_fe3d.terrainEntity_setLightness(newID, _fe3d.terrainEntity_getLightness(previewID));
	_fe3d.terrainEntity_setBlendRepeatR(newID, _fe3d.terrainEntity_getBlendRepeatR(previewID));
	_fe3d.terrainEntity_setBlendRepeatG(newID, _fe3d.terrainEntity_getBlendRepeatG(previewID));
	_fe3d.terrainEntity_setBlendRepeatB(newID, _fe3d.terrainEntity_getBlendRepeatB(previewID));
	_fe3d.terrainEntity_setSpecularLighted(newID, _fe3d.terrainEntity_isSpecularLighted(previewID));
	_fe3d.terrainEntity_setSpecularLightingFactor(newID, _fe3d.terrainEntity_getSpecularLightingFactor(previewID));
	_fe3d.terrainEntity_setSpecularLightingIntensity(newID, _fe3d.terrainEntity_getSpecularLightingIntensity(previewID));

	// Diffuse map
	if (_fe3d.terrainEntity_hasDiffuseMap(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMap(newID, _fe3d.terrainEntity_getDiffuseMapPath(previewID));
	}

	// Normal map
	if (_fe3d.terrainEntity_hasNormalMap(previewID))
	{
		_fe3d.terrainEntity_setNormalMap(newID, _fe3d.terrainEntity_getNormalMapPath(previewID));
	}

	// Normal map R
	if (_fe3d.terrainEntity_hasNormalMapR(previewID))
	{
		_fe3d.terrainEntity_setNormalMapR(newID, _fe3d.terrainEntity_getNormalMapPathR(previewID));
	}

	// Normal map G
	if (_fe3d.terrainEntity_hasNormalMapG(previewID))
	{
		_fe3d.terrainEntity_setNormalMapG(newID, _fe3d.terrainEntity_getNormalMapPathG(previewID));
	}

	// Normal map B
	if (_fe3d.terrainEntity_hasNormalMapB(previewID))
	{
		_fe3d.terrainEntity_setNormalMapB(newID, _fe3d.terrainEntity_getNormalMapPathB(previewID));
	}

	// Blend map
	if (_fe3d.terrainEntity_hasBlendMap(previewID))
	{
		_fe3d.terrainEntity_setBlendMap(newID, _fe3d.terrainEntity_getBlendMapPath(previewID));
	}

	// Blend map red
	if (_fe3d.terrainEntity_hasDiffuseMapR(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMapR(newID, _fe3d.terrainEntity_getDiffuseMapPathR(previewID));
	}

	// Blend map green
	if (_fe3d.terrainEntity_hasDiffuseMapG(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMapG(newID, _fe3d.terrainEntity_getDiffuseMapPathG(previewID));
	}

	// Blend map blue
	if (_fe3d.terrainEntity_hasDiffuseMapB(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMapB(newID, _fe3d.terrainEntity_getDiffuseMapPathB(previewID));
	}

	// Save ID
	_loadedTerrainID = newID;

	return true;
}

bool SceneEditor::_copyPreviewWater(const string& newID, const string& previewID)
{
	// Error checking
	if (_fe3d.waterEntity_isExisting(newID))
	{
		Logger::throwWarning("Scene water with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.waterEntity_isExisting(previewID))
	{
		Logger::throwWarning("Base water of scene water with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if (_fe3d.waterEntity_isExisting(newID))
	{
		_fe3d.waterEntity_delete(newID);
	}

	// Create water entity
	_fe3d.waterEntity_create(newID);
	_fe3d.waterEntity_select(newID);

	// Fill water entity
	_fe3d.waterEntity_setPosition(newID, _fe3d.waterEntity_getPosition(previewID));
	_fe3d.waterEntity_setSize(newID, _fe3d.waterEntity_getSize(previewID));
	_fe3d.waterEntity_setWaving(newID, _fe3d.waterEntity_isWaving(previewID));
	_fe3d.waterEntity_setRippling(newID, _fe3d.waterEntity_isRippling(previewID));
	_fe3d.waterEntity_setSpecularLighted(newID, _fe3d.waterEntity_isSpecularLighted(previewID));
	_fe3d.waterEntity_setReflective(newID, _fe3d.waterEntity_isReflective(previewID));
	_fe3d.waterEntity_setRefractive(newID, _fe3d.waterEntity_isRefractive(previewID));
	_fe3d.waterEntity_setWaveHeight(newID, _fe3d.waterEntity_getWaveHeight(previewID));
	_fe3d.waterEntity_setQuality(newID, _fe3d.waterEntity_getQuality(previewID));
	_fe3d.waterEntity_setSpecularLightingFactor(newID, _fe3d.waterEntity_getSpecularLightingFactor(previewID));
	_fe3d.waterEntity_setSpecularLightingIntensity(newID, _fe3d.waterEntity_getSpecularLightingIntensity(previewID));
	_fe3d.waterEntity_setTransparency(newID, _fe3d.waterEntity_getTransparency(previewID));
	_fe3d.waterEntity_setColor(newID, _fe3d.waterEntity_getColor(previewID));
	_fe3d.waterEntity_setUvRepeat(newID, _fe3d.waterEntity_getUvRepeat(previewID));
	_fe3d.waterEntity_setSpeed(newID, _fe3d.waterEntity_getSpeed(previewID));

	// DUDV map
	if (_fe3d.waterEntity_hasDudvMap(previewID))
	{
		_fe3d.waterEntity_setDudvMap(newID, _fe3d.waterEntity_getDudvMapPath(previewID));
	}

	// Normal map
	if (_fe3d.waterEntity_hasNormalMap(previewID))
	{
		_fe3d.waterEntity_setNormalMap(newID, _fe3d.waterEntity_getNormalMapPath(previewID));
	}

	// Displacement map
	if (_fe3d.waterEntity_hasDisplacementMap(previewID))
	{
		_fe3d.waterEntity_setDisplacementMap(newID, _fe3d.waterEntity_getDisplacementMapPath(previewID));
	}

	// Save ID
	_loadedWaterID = newID;

	return true;
}

bool SceneEditor::_copyPreviewModel(const string& newID, const string& previewID, Vec3 position, bool fromOutside)
{
	// Error checking
	if (_fe3d.modelEntity_isExisting(newID) && !_fe3d.modelEntity_isInstanced(previewID))
	{
		Logger::throwWarning("Model with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.modelEntity_isExisting(previewID))
	{
		Logger::throwWarning("Base model of model with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create model entity
	_fe3d.modelEntity_create(newID, _fe3d.modelEntity_getMeshPath(previewID));
	_fe3d.modelEntity_setPosition(newID, position);
	_fe3d.modelEntity_setSize(newID, _fe3d.modelEntity_getSize(previewID));

	// Bind AABB entities to model entity
	for (const auto& previewAabbID : _fe3d.aabbEntity_getBoundIDs(previewID, true, false))
	{
		const string newAabbID = (newID + "@" + previewAabbID.substr(string(previewID + "_").size()));
		_fe3d.aabbEntity_create(newAabbID);
		_fe3d.aabbEntity_bindToModelEntity(newAabbID, newID);
		_fe3d.aabbEntity_setPosition(newAabbID, _fe3d.aabbEntity_getPosition(previewAabbID));
		_fe3d.aabbEntity_setSize(newAabbID, _fe3d.aabbEntity_getSize(previewAabbID));
	}

	// Diffuse map
	if (!_fe3d.modelEntity_isMultiParted(previewID) && _fe3d.modelEntity_hasDiffuseMap(previewID))
	{
		_fe3d.modelEntity_setDiffuseMap(newID, _fe3d.modelEntity_getDiffuseMapPath(previewID));
	}

	// Emission map
	if (!_fe3d.modelEntity_isMultiParted(previewID) && _fe3d.modelEntity_hasEmissionMap(previewID))
	{
		_fe3d.modelEntity_setEmissionMap(newID, _fe3d.modelEntity_getEmissionMapPath(previewID));
	}

	// Reflection map
	if (!_fe3d.modelEntity_isMultiParted(previewID) && _fe3d.modelEntity_hasReflectionMap(previewID))
	{
		_fe3d.modelEntity_setReflectionMap(newID, _fe3d.modelEntity_getReflectionMapPath(previewID));
	}

	// Normal map
	if (!_fe3d.modelEntity_isMultiParted(previewID) && _fe3d.modelEntity_hasNormalMap(previewID))
	{
		_fe3d.modelEntity_setNormalMap(newID, _fe3d.modelEntity_getNormalMapPath(previewID));
	}

	// Instancing
	if (_fe3d.modelEntity_isInstanced(previewID))
	{
		_fe3d.modelEntity_enableInstancing(newID, { Vec3(0.0f) });
	}

	// Set properties
	_fe3d.modelEntity_setStaticToCamera(newID, _fe3d.modelEntity_isStaticToCamera(previewID));
	_fe3d.modelEntity_setFaceCulled(newID, _fe3d.modelEntity_isFaceCulled(previewID));
	_fe3d.modelEntity_setTransparent(newID, _fe3d.modelEntity_isTransparent(previewID));
	_fe3d.modelEntity_setReflectionType(newID, _fe3d.modelEntity_getReflectionType(previewID));
	_fe3d.modelEntity_setSpecularLighted(newID, _fe3d.modelEntity_isSpecularLighted(previewID));
	_fe3d.modelEntity_setSpecularFactor(newID, _fe3d.modelEntity_getSpecularFactor(previewID));
	_fe3d.modelEntity_setSpecularIntensity(newID, _fe3d.modelEntity_getSpecularIntensity(previewID));
	_fe3d.modelEntity_setLightness(newID, _fe3d.modelEntity_getLightness(previewID));
	_fe3d.modelEntity_setColor(newID, _fe3d.modelEntity_getColor(previewID));
	_fe3d.modelEntity_setUvRepeat(newID, _fe3d.modelEntity_getUvRepeat(previewID));
	_fe3d.modelEntity_setLevelOfDetailEntity(newID, _fe3d.modelEntity_getLevelOfDetailEntityID(previewID));
	_fe3d.modelEntity_setBright(newID, _fe3d.modelEntity_isBright(previewID));

	// Save original transformation
	if (_isEditorLoaded)
	{
		_initialModelPosition[newID] = _fe3d.modelEntity_getPosition(previewID);
		_initialModelRotation[newID] = _fe3d.modelEntity_getRotation(previewID);
		_initialModelSize[newID] = _fe3d.modelEntity_getSize(previewID);
	}

	// Save ID
	if (fromOutside)
	{
		_outsideLoadedModelIDs[newID] = previewID;
	}
	else
	{
		_loadedModelIDs[newID] = previewID;
	}

	return true;
}

bool SceneEditor::_copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position, bool fromOutside)
{
	// Error checking
	if (_fe3d.billboardEntity_isExisting(newID))
	{
		Logger::throwWarning("Billboard with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.billboardEntity_isExisting(previewID))
	{
		Logger::throwWarning("Base billboard of billboard with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create billboard entity
	_fe3d.billboardEntity_create(newID);

	// Bind AABB entity
	_fe3d.aabbEntity_bindToBillboardEntity(newID, newID);

	// Diffuse map
	if (_fe3d.billboardEntity_hasDiffuseMap(previewID))
	{
		_fe3d.billboardEntity_setDiffuseMap(newID, _fe3d.billboardEntity_getDiffuseMapPath(previewID));
	}

	// Text
	if (!_fe3d.billboardEntity_getFontPath(previewID).empty())
	{
		_fe3d.billboardEntity_setFont(newID, _fe3d.billboardEntity_getFontPath(previewID));
		_fe3d.billboardEntity_setTextContent(newID, _fe3d.billboardEntity_getTextContent(previewID));
	}

	// Start sprite animation
	if (_fe3d.billboardEntity_isSpriteAnimationStarted(previewID))
	{
		_fe3d.billboardEntity_setSpriteAnimationRows(newID, _fe3d.billboardEntity_getSpriteAnimationRows(previewID));
		_fe3d.billboardEntity_setSpriteAnimationColumns(newID, _fe3d.billboardEntity_getSpriteAnimationColumns(previewID));
		_fe3d.billboardEntity_setSpriteAnimationFramestep(newID, _fe3d.billboardEntity_getSpriteAnimationFramestep(previewID));
		_fe3d.billboardEntity_startSpriteAnimation(newID, -1);
	}

	// Set properties
	_fe3d.billboardEntity_setPosition(newID, position);
	_fe3d.billboardEntity_setSize(newID, _fe3d.billboardEntity_getSize(previewID));
	_fe3d.billboardEntity_setCameraFacingX(newID, _fe3d.billboardEntity_isFacingCameraX(previewID));
	_fe3d.billboardEntity_setCameraFacingY(newID, _fe3d.billboardEntity_isFacingCameraY(previewID));
	_fe3d.billboardEntity_setColor(newID, _fe3d.billboardEntity_getColor(previewID));
	_fe3d.billboardEntity_setShadowed(newID, _fe3d.billboardEntity_isShadowed(previewID));
	_fe3d.billboardEntity_setReflected(newID, _fe3d.billboardEntity_isReflected(previewID));
	_fe3d.billboardEntity_setTransparent(newID, _fe3d.billboardEntity_isTransparent(previewID));
	_fe3d.billboardEntity_setLightness(newID, _fe3d.billboardEntity_getLightness(previewID));
	_fe3d.billboardEntity_setBright(newID, _fe3d.billboardEntity_isBright(previewID));

	// Save ID
	if (fromOutside)
	{
		_outsideLoadedBillboardIDs[newID] = previewID;
	}
	else
	{
		_loadedBillboardIDs[newID] = previewID;
	}

	return true;
}

bool SceneEditor::_copyPreviewAudio(const string& newID, const string& previewID, Vec3 position, bool fromOutside)
{
	// Error checking
	if (_fe3d.soundEntity_isExisting(newID))
	{
		Logger::throwWarning("Sound with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.soundEntity_isExisting(previewID))
	{
		Logger::throwWarning("Base audio of sound with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Add soundEntity
	_fe3d.soundEntity_create(newID, _fe3d.soundEntity_getFilePath(previewID));
	_fe3d.soundEntity_make3D(newID, position, 0.0f, 0.0f);

	// Save ID
	if (fromOutside)
	{
		_outsideLoadedSoundIDs[newID] = previewID;
	}
	else
	{
		_loadedSoundIDs[newID] = previewID;
	}

	return true;
}
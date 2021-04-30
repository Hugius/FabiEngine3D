#include "scene_editor.hpp"

bool SceneEditor::_copyPreviewSky(const string& newID, const string& previewID)
{
	// Error checking
	if (_fe3d.skyEntity_isExisting(newID))
	{
		_fe3d.logger_throwWarning("Scene sky with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.skyEntity_isExisting(previewID))
	{
		_fe3d.logger_throwWarning("Base sky of scene sky with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create new sky
	_fe3d.skyEntity_add(newID);
	_fe3d.skyEntity_setDiffuseMaps(newID, _fe3d.skyEntity_getDiffuseMapPaths(previewID));
	_fe3d.skyEntity_setLightness(newID, _fe3d.skyEntity_getLightness(previewID));
	_fe3d.skyEntity_setRotationSpeed(newID, _fe3d.skyEntity_getRotationSpeed(previewID));
	_fe3d.skyEntity_setColor(newID, _fe3d.skyEntity_getColor(previewID));
	_fe3d.skyEntity_select(newID);

	// Save ID
	_loadedSkyID = newID;

	return true;
}

bool SceneEditor::_copyPreviewTerrain(const string& newID, const string& previewID)
{
	// Error checking
	if (_fe3d.terrainEntity_isExisting(newID))
	{
		_fe3d.logger_throwWarning("Scene terrain with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.terrainEntity_isExisting(previewID))
	{
		_fe3d.logger_throwWarning("Base terrain of scene terrain with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if (_fe3d.terrainEntity_isExisting(newID))
	{
		_fe3d.terrainEntity_delete(newID);
	}

	// Create terrain entity
	_fe3d.terrainEntity_add(newID, _fe3d.terrainEntity_getHeightMapPath(previewID));
	_fe3d.terrainEntity_select(newID);

	// Fill terrain entity
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

	// Save ID
	_loadedTerrainID = newID;

	return true;
}

bool SceneEditor::_copyPreviewWater(const string& newID, const string& previewID)
{
	// Error checking
	if (_fe3d.waterEntity_isExisting(newID))
	{
		_fe3d.logger_throwWarning("Scene water with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.waterEntity_isExisting(previewID))
	{
		_fe3d.logger_throwWarning("Base water of scene water with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if (_fe3d.waterEntity_isExisting(newID))
	{
		_fe3d.waterEntity_delete(newID);
	}

	// Create water entity
	_fe3d.waterEntity_add(newID);
	_fe3d.waterEntity_select(newID);

	// Fill water entity
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

	// Save ID
	_loadedWaterID = newID;

	return true;
}

bool SceneEditor::_copyPreviewModel(const string& newID, const string& previewID, Vec3 position, bool fromOutside)
{
	// Error checking
	if (_fe3d.modelEntity_isExisting(newID) && !_fe3d.modelEntity_isInstanced(previewID))
	{
		_fe3d.logger_throwWarning("Model with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.modelEntity_isExisting(previewID))
	{
		_fe3d.logger_throwWarning("Base model of model with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Compose full entity ID
	const string newEntityID = _fe3d.modelEntity_isInstanced(previewID) ? previewID.substr(1) : newID;

	// Check if instanced entity
	if (_fe3d.modelEntity_isInstanced(previewID))
	{
		// Add to offsets
		if (_fe3d.modelEntity_isExisting(newEntityID))
		{
			auto offsets = _fe3d.modelEntity_getInstancedOffsets(newEntityID);
			offsets.push_back(position);
			_fe3d.modelEntity_setInstanced(newEntityID, true, offsets);
		}
		else
		{
			// Create new model entity
			_fe3d.modelEntity_add(newEntityID, _fe3d.modelEntity_getMeshPath(previewID), Vec3(0.0f), Vec3(0.0f), _fe3d.modelEntity_getSize(previewID));

			// Fill model entity
			_fe3d.modelEntity_setFaceCulled(newEntityID, _fe3d.modelEntity_isFaceCulled(previewID));
			_fe3d.modelEntity_setShadowed(newEntityID, _fe3d.modelEntity_isShadowed(previewID));
			_fe3d.modelEntity_setTransparent(newEntityID, _fe3d.modelEntity_isTransparent(previewID));
			_fe3d.modelEntity_setSkyReflective(newEntityID, _fe3d.modelEntity_isSkyReflective(previewID));
			_fe3d.modelEntity_setSceneReflective(newEntityID, _fe3d.modelEntity_isSceneReflective(previewID));
			_fe3d.modelEntity_setSpecularLighted(newEntityID, _fe3d.modelEntity_isSpecularLighted(previewID));
			_fe3d.modelEntity_setSpecularFactor(newEntityID, _fe3d.modelEntity_getSpecularFactor(previewID));
			_fe3d.modelEntity_setSpecularIntensity(newEntityID, _fe3d.modelEntity_getSpecularIntensity(previewID));
			_fe3d.modelEntity_setLightness(newEntityID, _fe3d.modelEntity_getLightness(previewID));
			_fe3d.modelEntity_setColor(newEntityID, _fe3d.modelEntity_getColor(previewID));
			_fe3d.modelEntity_setUvRepeat(newEntityID, _fe3d.modelEntity_getUvRepeat(previewID));
			_fe3d.modelEntity_setInstanced(newEntityID, true, { position });

			// Diffuse map
			if (_fe3d.modelEntity_getDiffuseMapPath(previewID) != "")
			{
				_fe3d.modelEntity_setDiffuseMap(newEntityID, _fe3d.modelEntity_getDiffuseMapPath(previewID));
			}

			// Light map
			if (_fe3d.modelEntity_getLightMapPath(previewID) != "")
			{
				_fe3d.modelEntity_setLightMap(newEntityID, _fe3d.modelEntity_getLightMapPath(previewID));
				_fe3d.modelEntity_setLightMapped(newEntityID, true);
			}

			// Reflection map
			if (_fe3d.modelEntity_getReflectionMapPath(previewID) != "")
			{
				_fe3d.modelEntity_setReflectionMap(newEntityID, _fe3d.modelEntity_getReflectionMapPath(previewID));
			}

			// Normal map
			if (_fe3d.modelEntity_getNormalMapPath(previewID) != "")
			{
				_fe3d.modelEntity_setNormalMap(newEntityID, _fe3d.modelEntity_getNormalMapPath(previewID));
				_fe3d.modelEntity_setNormalMapped(newEntityID, true);
			}
		}
	}
	else // Normal entity
	{
		// Add model entity
		_fe3d.modelEntity_add(newEntityID, _fe3d.modelEntity_getMeshPath(previewID), position, Vec3(0.0f), _fe3d.modelEntity_getSize(previewID));

		// Bind AABB entities to model entity
		for (const auto& previewAabbID : _fe3d.aabbEntity_getBoundIDs(previewID, true, false))
		{
			string newAabbID = newEntityID + "@" + previewAabbID.substr(string(previewID + "_").size());
			_fe3d.aabbEntity_bindToModelEntity(newEntityID, _fe3d.aabbEntity_getPosition(previewAabbID),
				_fe3d.aabbEntity_getSize(previewAabbID), true, true, newAabbID);
		}

		// Model properties
		_fe3d.modelEntity_setStaticToCamera(newEntityID, _fe3d.modelEntity_isStaticToCamera(previewID));
		_fe3d.modelEntity_setFaceCulled(newEntityID, _fe3d.modelEntity_isFaceCulled(previewID));
		_fe3d.modelEntity_setShadowed(newEntityID, _fe3d.modelEntity_isShadowed(previewID));
		_fe3d.modelEntity_setTransparent(newEntityID, _fe3d.modelEntity_isTransparent(previewID));
		_fe3d.modelEntity_setSkyReflective(newEntityID, _fe3d.modelEntity_isSkyReflective(previewID));
		_fe3d.modelEntity_setSceneReflective(newEntityID, _fe3d.modelEntity_isSceneReflective(previewID));
		_fe3d.modelEntity_setSpecularLighted(newEntityID, _fe3d.modelEntity_isSpecularLighted(previewID));
		_fe3d.modelEntity_setSpecularFactor(newEntityID, _fe3d.modelEntity_getSpecularFactor(previewID));
		_fe3d.modelEntity_setSpecularIntensity(newEntityID, _fe3d.modelEntity_getSpecularIntensity(previewID));
		_fe3d.modelEntity_setLightness(newEntityID, _fe3d.modelEntity_getLightness(previewID));
		_fe3d.modelEntity_setColor(newEntityID, _fe3d.modelEntity_getColor(previewID));
		_fe3d.modelEntity_setUvRepeat(newEntityID, _fe3d.modelEntity_getUvRepeat(previewID));
		_fe3d.modelEntity_setLevelOfDetailEntity(newEntityID, _fe3d.modelEntity_getLevelOfDetailEntityID(previewID));

		// Diffuse map
		if (_fe3d.modelEntity_getDiffuseMapPath(previewID) != "")
		{
			_fe3d.modelEntity_setDiffuseMap(newEntityID, _fe3d.modelEntity_getDiffuseMapPath(previewID));
		}

		// Light map
		if (_fe3d.modelEntity_getLightMapPath(previewID) != "")
		{
			_fe3d.modelEntity_setLightMap(newEntityID, _fe3d.modelEntity_getLightMapPath(previewID));
			_fe3d.modelEntity_setLightMapped(newEntityID, true);
		}

		// Reflection map
		if (_fe3d.modelEntity_getReflectionMapPath(previewID) != "")
		{
			_fe3d.modelEntity_setReflectionMap(newEntityID, _fe3d.modelEntity_getReflectionMapPath(previewID));
		}

		// Normal map
		if (_fe3d.modelEntity_getNormalMapPath(previewID) != "")
		{
			_fe3d.modelEntity_setNormalMap(newEntityID, _fe3d.modelEntity_getNormalMapPath(previewID));
			_fe3d.modelEntity_setNormalMapped(newEntityID, true);
		}
	}

	// Save original lightness & transformation
	if (_isEditorLoaded)
	{
		_initialModelLightness[newEntityID] = _fe3d.modelEntity_getLightness(previewID);
		_initialModelPosition[newEntityID] = _fe3d.modelEntity_getPosition(previewID);
		_initialModelRotation[newEntityID] = _fe3d.modelEntity_getRotation(previewID);
		_initialModelSize[newEntityID] = _fe3d.modelEntity_getSize(previewID);
	}

	// Save ID
	if (fromOutside)
	{
		_outsideLoadedModelIDs[newEntityID] = previewID;
	}
	else
	{
		_loadedModelIDs[newEntityID] = previewID;
	}

	return true;
}

bool SceneEditor::_copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position, bool fromOutside)
{
	// Error checking
	if (_fe3d.billboardEntity_isExisting(newID))
	{
		_fe3d.logger_throwWarning("Billboard with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.billboardEntity_isExisting(previewID))
	{
		_fe3d.logger_throwWarning("Base billboard of billboard with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Temporary values
	auto color = _fe3d.billboardEntity_getColor(previewID);
	auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(previewID);
	auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(previewID);

	// Add billboard entity
	Vec2 size = _fe3d.billboardEntity_getSize(previewID);
	_fe3d.billboardEntity_add(newID, color, position, Vec3(0.0f), size, isFacingX, isFacingY);

	// Determine billboard entity type
	if (_fe3d.billboardEntity_getDiffuseMapPath(previewID) != "") // Textured billboard
	{
		_fe3d.billboardEntity_setDiffuseMap(newID, _fe3d.billboardEntity_getDiffuseMapPath(previewID));
	}
	else if (_fe3d.billboardEntity_getFontPath(previewID) != "") // Text billboard
	{
		_fe3d.billboardEntity_setFont(newID, _fe3d.billboardEntity_getFontPath(previewID));
		_fe3d.billboardEntity_setTextContent(newID, _fe3d.billboardEntity_getTextContent(previewID));
	}

	// Animation
	if (_fe3d.billboardEntity_isAnimationStarted(previewID))
	{
		_fe3d.billboardEntity_setAnimationRows(newID, _fe3d.billboardEntity_getAnimationRows(previewID));
		_fe3d.billboardEntity_setAnimationColumns(newID, _fe3d.billboardEntity_getAnimationColumns(previewID));
		_fe3d.billboardEntity_setAnimationFramestep(newID, _fe3d.billboardEntity_getAnimationFramestep(previewID));
		_fe3d.billboardEntity_startAnimation(newID, -1);
	}

	// Bind AABB entity to billboard entity
	_fe3d.aabbEntity_bindToBillboardEntity(newID, true, true);

	// Miscellaneous
	_fe3d.billboardEntity_setTransparent(newID, _fe3d.billboardEntity_isTransparent(previewID));
	_fe3d.billboardEntity_setLightness(newID, _fe3d.billboardEntity_getLightness(previewID));

	// Save original lightness
	if (_isEditorLoaded)
	{
		_initialBillboardLightness[newID] = _fe3d.billboardEntity_getLightness(previewID);
	}

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
		_fe3d.logger_throwWarning("Sound with ID \"" + newID + "\" already exists!");
		return false;
	}
	if (!_fe3d.soundEntity_isExisting(previewID))
	{
		_fe3d.logger_throwWarning("Base audio of sound with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Add soundEntity
	_fe3d.soundEntity_add(newID, _fe3d.soundEntity_getFilePath(previewID));
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
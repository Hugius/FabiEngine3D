#include "scene_editor.hpp"

void SceneEditor::placeModel(const string& newID, const string& previewID, Vec3 position)
{
	// Compose full entity ID
	const string newEntityID = _fe3d.gameEntity_isInstanced(previewID) ? "instanced@" + previewID.substr(1) : newID;

	// If editing scene, save ID
	if (!_currentSceneID.empty())
	{
		_loadedModelIDs.push_back(newEntityID);
	}

	// Check if instanced entity
	if (_fe3d.gameEntity_isInstanced(previewID))
	{
		// Add to offsets
		if (_fe3d.gameEntity_isExisting(newEntityID))
		{
			auto offsets = _fe3d.gameEntity_getInstancedOffsets(newEntityID);
			offsets.push_back(position);
			_fe3d.gameEntity_setInstanced(newEntityID, true, offsets);
		}
		else
		{
			// Create new GAME entity
			_fe3d.gameEntity_add(newEntityID, _fe3d.gameEntity_getMeshPath(previewID), Vec3(0.0f), Vec3(0.0f), _fe3d.gameEntity_getSize(previewID));

			// Fill GAME entity
			_fe3d.gameEntity_setFaceCulled(newEntityID, _fe3d.gameEntity_isFaceCulled(previewID));
			_fe3d.gameEntity_setShadowed(newEntityID, _fe3d.gameEntity_isShadowed(previewID));
			_fe3d.gameEntity_setTransparent(newEntityID, _fe3d.gameEntity_isTransparent(previewID));
			_fe3d.gameEntity_setSkyReflective(newEntityID, _fe3d.gameEntity_isSkyReflective(previewID));
			_fe3d.gameEntity_setSceneReflective(newEntityID, _fe3d.gameEntity_isSceneReflective(previewID));
			_fe3d.gameEntity_setSpecularLighted(newEntityID, _fe3d.gameEntity_isSpecularLighted(previewID));
			_fe3d.gameEntity_setSpecularFactor(newEntityID, _fe3d.gameEntity_getSpecularFactor(previewID));
			_fe3d.gameEntity_setSpecularIntensity(newEntityID, _fe3d.gameEntity_getSpecularIntensity(previewID));
			_fe3d.gameEntity_setLightness(newEntityID, _fe3d.gameEntity_getLightness(previewID));
			_fe3d.gameEntity_setColor(newEntityID, _fe3d.gameEntity_getColor(previewID));
			_fe3d.gameEntity_setUvRepeat(newEntityID, _fe3d.gameEntity_getUvRepeat(previewID));
			_fe3d.gameEntity_setInstanced(newEntityID, true, { position });

			// Save original lightness & transformation
			if (_isEditorLoaded)
			{
				_initialModelLightness[newEntityID] = _fe3d.gameEntity_getLightness(previewID);
				_initialModelPosition[newEntityID] = _fe3d.gameEntity_getPosition(previewID);
				_initialModelRotation[newEntityID] = _fe3d.gameEntity_getRotation(previewID);
				_initialModelSize[newEntityID] = _fe3d.gameEntity_getSize(previewID);
			}

			// Diffuse map
			if (_fe3d.gameEntity_getDiffuseMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setDiffuseMap(newEntityID, _fe3d.gameEntity_getDiffuseMapPath(previewID));
			}

			// Light map
			if (_fe3d.gameEntity_getLightMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setLightMap(newEntityID, _fe3d.gameEntity_getLightMapPath(previewID));
				_fe3d.gameEntity_setLightMapped(newEntityID, true);
			}

			// Reflection map
			if (_fe3d.gameEntity_getReflectionMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setReflectionMap(newEntityID, _fe3d.gameEntity_getReflectionMapPath(previewID));
			}

			// Normal map
			if (_fe3d.gameEntity_getNormalMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setNormalMap(newEntityID, _fe3d.gameEntity_getNormalMapPath(previewID));
				_fe3d.gameEntity_setNormalMapped(newEntityID, true);
			}
		}
	}
	else // Normal entity
	{
		// Add GAME entity
		_fe3d.gameEntity_add(newEntityID, _fe3d.gameEntity_getMeshPath(previewID), position, Vec3(0.0f), _fe3d.gameEntity_getSize(previewID));

		// Bind AABB entities to GAME entity
		for (auto& previewAabbID : _fe3d.aabbEntity_getBoundIDs(previewID, true, false))
		{
			string newAabbID = newEntityID + "_" + previewAabbID.substr(string(previewID + "_").size());
			_fe3d.aabbEntity_bindToGameEntity(newEntityID, _fe3d.aabbEntity_getPosition(previewAabbID), 
				_fe3d.aabbEntity_getSize(previewAabbID), true, true, newAabbID);
		}

		// Model properties
		_fe3d.gameEntity_setStaticToCamera(newEntityID, _fe3d.gameEntity_isStaticToCamera(previewID));
		_fe3d.gameEntity_setFaceCulled(newEntityID, _fe3d.gameEntity_isFaceCulled(previewID));
		_fe3d.gameEntity_setShadowed(newEntityID, _fe3d.gameEntity_isShadowed(previewID));
		_fe3d.gameEntity_setTransparent(newEntityID, _fe3d.gameEntity_isTransparent(previewID));
		_fe3d.gameEntity_setSkyReflective(newEntityID, _fe3d.gameEntity_isSkyReflective(previewID));
		_fe3d.gameEntity_setSceneReflective(newEntityID, _fe3d.gameEntity_isSceneReflective(previewID));
		_fe3d.gameEntity_setSpecularLighted(newEntityID, _fe3d.gameEntity_isSpecularLighted(previewID));
		_fe3d.gameEntity_setSpecularFactor(newEntityID, _fe3d.gameEntity_getSpecularFactor(previewID));
		_fe3d.gameEntity_setSpecularIntensity(newEntityID, _fe3d.gameEntity_getSpecularIntensity(previewID));
		_fe3d.gameEntity_setLightness(newEntityID, _fe3d.gameEntity_getLightness(previewID));
		_fe3d.gameEntity_setColor(newEntityID, _fe3d.gameEntity_getColor(previewID));
		_fe3d.gameEntity_setUvRepeat(newEntityID, _fe3d.gameEntity_getUvRepeat(previewID));
		_fe3d.gameEntity_setLevelOfDetailEntity(newEntityID, _fe3d.gameEntity_getLevelOfDetailEntityID(previewID));

		// Save original lightness & transformation
		if (_isEditorLoaded)
		{
			_initialModelLightness[newEntityID] = _fe3d.gameEntity_getLightness(previewID);
			_initialModelPosition[newEntityID] = _fe3d.gameEntity_getPosition(previewID);
			_initialModelRotation[newEntityID] = _fe3d.gameEntity_getRotation(previewID);
			_initialModelSize[newEntityID] = _fe3d.gameEntity_getSize(previewID);
		}

		// Diffuse map
		if (_fe3d.gameEntity_getDiffuseMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setDiffuseMap(newEntityID, _fe3d.gameEntity_getDiffuseMapPath(previewID));
		}

		// Light map
		if (_fe3d.gameEntity_getLightMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setLightMap(newEntityID, _fe3d.gameEntity_getLightMapPath(previewID));
			_fe3d.gameEntity_setLightMapped(newEntityID, true);
		}

		// Reflection map
		if (_fe3d.gameEntity_getReflectionMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setReflectionMap(newEntityID, _fe3d.gameEntity_getReflectionMapPath(previewID));
		}

		// Normal map
		if (_fe3d.gameEntity_getNormalMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setNormalMap(newEntityID, _fe3d.gameEntity_getNormalMapPath(previewID));
			_fe3d.gameEntity_setNormalMapped(newEntityID, true);
		}
	}
}

void SceneEditor::_placeModel(bool scriptExecution, const string& modelName, const string& modelNumber, Vec3 position, Vec3 rotation, Vec3 size,
	const string& meshPath, const string& diffuseMapPath, const string& lightMapPath, const string& reflectionMapPath, const string& normalMapPath, 
	bool isFrozen, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isSpecular, int reflectionType, float specularFactor,
	float specularIntensity, float lightness, Vec3 color, float uvRepeat, const string& lodEntityID, bool isInstanced,
	vector<Vec3> instancedOffsets, vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes, string animationID)
{
	// Compose new model ID
	string newID = scriptExecution ? (modelName + "@" + modelNumber) : (modelNumber + "@" + modelName);
	_loadedModelIDs.push_back(newID);

	// Add GAME entity
	_fe3d.gameEntity_add(newID, meshPath, position, rotation, size);

	// Add AABBs
	for (unsigned int i = 0; i < aabbNames.size(); i++)
	{
		if (scriptExecution) // modelname_aabbname@123
		{
			_fe3d.aabbEntity_bindToGameEntity(newID, aabbPositions[i], aabbSizes[i], true, true, modelName + "_" + aabbNames[i] + "@" + modelNumber);
		}
		else // 123@modelname_aabbname
		{
			_fe3d.aabbEntity_bindToGameEntity(newID, aabbPositions[i], aabbSizes[i], true, true, newID + "_" + aabbNames[i]);
		}
	}

	// Model properties
	_fe3d.gameEntity_setStaticToCamera(newID, isFrozen);
	_fe3d.gameEntity_setFaceCulled(newID, isFaceCulled);
	_fe3d.gameEntity_setShadowed(newID, isShadowed);
	_fe3d.gameEntity_setTransparent(newID, isTransparent);
	_fe3d.gameEntity_setSpecularLighted(newID, isSpecular);
	_fe3d.gameEntity_setSpecularFactor(newID, specularFactor);
	_fe3d.gameEntity_setSpecularIntensity(newID, specularIntensity);
	_fe3d.gameEntity_setLightness(newID, lightness);
	_fe3d.gameEntity_setColor(newID, color);
	_fe3d.gameEntity_setUvRepeat(newID, uvRepeat);
	_fe3d.gameEntity_setLevelOfDetailEntity(newID, lodEntityID);
	_fe3d.gameEntity_setInstanced(newID, isInstanced, instancedOffsets);

	// Reflection type
	if (reflectionType == 1)
	{
		_fe3d.gameEntity_setSkyReflective(newID, true);
	}
	else if (reflectionType == 2)
	{
		_fe3d.gameEntity_setSceneReflective(newID, true);
	}

	// Save original lightness & transformation
	if (_isEditorLoaded)
	{
		_initialModelLightness[newID] = lightness;
		_initialModelPosition[newID] = position;
		_initialModelRotation[newID] = rotation;
		_initialModelSize[newID] = size;
	}

	// Diffuse map
	if (diffuseMapPath != "")
	{
		_fe3d.gameEntity_setDiffuseMap(newID, diffuseMapPath);
	}

	// Light map
	if (lightMapPath != "")
	{
		_fe3d.gameEntity_setLightMap(newID, lightMapPath);
		_fe3d.gameEntity_setLightMapped(newID, true);
	}

	// Reflection map
	if (reflectionMapPath != "")
	{
		_fe3d.gameEntity_setReflectionMap(newID, reflectionMapPath);
	}

	// Normal map
	if (normalMapPath != "")
	{
		_fe3d.gameEntity_setNormalMap(newID, normalMapPath);
		_fe3d.gameEntity_setNormalMapped(newID, true);
	}

	// Play animation
	if (!animationID.empty())
	{
		_animationEditor.startAnimation(animationID, newID, -1);
	}
}

void SceneEditor::placeBillboard(const string& newID, const string& previewID, Vec3 position)
{
	// If editing scene, save ID
	if (!_currentSceneID.empty())
	{
		_loadedBillboardIDs.push_back(newID);
	}

	// Temporary values
	auto color = _fe3d.billboardEntity_getColor(previewID);
	auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(previewID);
	auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(previewID);

	// Add BILLBOARD entity
	Vec2 size = _fe3d.billboardEntity_getSize(previewID);
	_fe3d.billboardEntity_add(newID, color, position, Vec3(0.0f), size, isFacingX, isFacingY);

	// Determine BILLBOARD entity type
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
	if (_fe3d.billboardEntity_isAnimationPlaying(previewID))
	{
		_fe3d.billboardEntity_setAnimationRows(newID, _fe3d.billboardEntity_getAnimationRows(previewID));
		_fe3d.billboardEntity_setAnimationColumns(newID, _fe3d.billboardEntity_getAnimationColumns(previewID));
		_fe3d.billboardEntity_setAnimationFramestep(newID, _fe3d.billboardEntity_getAnimationFramestep(previewID));
		_fe3d.billboardEntity_playSpriteAnimation(newID, -1);
	}

	// Bind AABB entity to BILLBOARD entity
	_fe3d.aabbEntity_bindToBillboardEntity(newID, true, true);

	// Miscellaneous
	_fe3d.billboardEntity_setTransparent(newID, _fe3d.billboardEntity_isTransparent(previewID));
	_fe3d.billboardEntity_setLightness(newID, _fe3d.billboardEntity_getLightness(previewID));

	// Save original lightness
	if (_isEditorLoaded)
	{
		_initialBillboardLightness[newID] = _fe3d.billboardEntity_getLightness(previewID);
	}
}

void SceneEditor::_placeBillboard(bool scriptExecution, const string& billboardName, const string& billboardNumber,
	const string& diffusePath, const string& fontPath, const string& textContent,
	Vec3 position, Vec3 rotation, Vec2 size, Vec3 color, bool facingX, bool facingY, bool isTransparent,
	bool isAnimated, int animationRows, int animationColumns, int animationFramestep, float lightness)
{
	// Compose new model ID
	string newID = scriptExecution ? (billboardName + "@" + billboardNumber) : (billboardNumber + "@" + billboardName);
	_loadedBillboardIDs.push_back(newID);

	if (diffusePath != "") // Textured billboard
	{
		_fe3d.billboardEntity_add(newID, diffusePath, position, rotation, size, isTransparent, facingX, facingY, true);
		_fe3d.billboardEntity_setColor(newID, color);

		// Animation
		if (isAnimated)
		{
			_fe3d.billboardEntity_setAnimationFramestep(newID, animationFramestep);
			_fe3d.billboardEntity_setAnimationRows(newID, animationRows);
			_fe3d.billboardEntity_setAnimationColumns(newID, animationColumns);
			_fe3d.billboardEntity_playSpriteAnimation(newID, -1);
		}
	}
	else if (fontPath != "") // Text billboard
	{
		_fe3d.billboardEntity_add(newID, textContent, fontPath, color, position, rotation, size, facingX, facingY);
	}
	else // Colored billboard
	{
		_fe3d.billboardEntity_add(newID, color, position, rotation, size, facingX, facingY);
	}
	
	// Bind AABB entity to BILLBOARD entity
	if (scriptExecution) // billboardname@123
	{
		_fe3d.aabbEntity_bindToBillboardEntity(newID, true, true, billboardName + "@" + billboardNumber);
	}
	else // 123@billboardname
	{
		_fe3d.aabbEntity_bindToBillboardEntity(newID, true, true, billboardNumber + "@" + billboardName);
	}

	// Miscellaneous
	_fe3d.billboardEntity_setLightness(newID, lightness);

	// Save original lightness
	if (_isEditorLoaded)
	{
		_initialBillboardLightness[newID] = lightness;
	}
}
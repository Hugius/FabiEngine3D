#include "scene_editor.hpp"

void SceneEditor::_placeModel(const string& newID, const string& previewID, vec3 position)
{
	// Check if instanced entity
	if (_fe3d.gameEntity_isInstanced(previewID))
	{
		const string instancedID = previewID.substr(1) + "_instanced";

		if (_fe3d.gameEntity_isExisting(instancedID)) // Add to offsets
		{
			auto offsets = _fe3d.gameEntity_getInstancedOffsets(instancedID);
			offsets.push_back(position);
			_fe3d.gameEntity_setInstanced(instancedID, true, offsets);
		}
		else
		{
			// Create new GAME entity
			_fe3d.gameEntity_add(instancedID, _fe3d.gameEntity_getObjPath(previewID), vec3(0.0f), vec3(0.0f), _fe3d.gameEntity_getSize(previewID));

			// Fill GAME entity
			_fe3d.gameEntity_setFaceCulled(instancedID, _fe3d.gameEntity_isFaceCulled(previewID));
			_fe3d.gameEntity_setShadowed(instancedID, _fe3d.gameEntity_isShadowed(previewID));
			_fe3d.gameEntity_setTransparent(instancedID, _fe3d.gameEntity_isTransparent(previewID));
			_fe3d.gameEntity_setSceneReflective(instancedID, _fe3d.gameEntity_isSceneReflective(previewID));
			_fe3d.gameEntity_setSpecularLighted(instancedID, _fe3d.gameEntity_isSpecularLighted(previewID));
			_fe3d.gameEntity_setSpecularFactor(instancedID, _fe3d.gameEntity_getSpecularFactor(previewID));
			_fe3d.gameEntity_setSpecularIntensity(instancedID, _fe3d.gameEntity_getSpecularIntensity(previewID));
			_fe3d.gameEntity_setLightness(instancedID, _fe3d.gameEntity_getLightness(previewID));
			_fe3d.gameEntity_setOriginalLightness(instancedID, _fe3d.gameEntity_getOriginalLightness(previewID));
			_fe3d.gameEntity_setColor(instancedID, _fe3d.gameEntity_getColor(previewID));
			_fe3d.gameEntity_setUvRepeat(instancedID, _fe3d.gameEntity_getUvRepeat(previewID));
			_fe3d.gameEntity_setInstanced(instancedID, true, { position });

			// Diffuse map
			if (_fe3d.gameEntity_getDiffuseMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setDiffuseMap(instancedID, _fe3d.gameEntity_getDiffuseMapPath(previewID));
			}

			// Light map
			if (_fe3d.gameEntity_getLightMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setLightMap(instancedID, _fe3d.gameEntity_getLightMapPath(previewID));
				_fe3d.gameEntity_setLightMapped(instancedID, true);
			}

			// Reflection map
			if (_fe3d.gameEntity_getReflectionMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setReflectionMap(instancedID, _fe3d.gameEntity_getReflectionMapPath(previewID));
				_fe3d.gameEntity_setSkyReflective(instancedID, true);
			}

			// Normal map
			if (_fe3d.gameEntity_getNormalMapPath(previewID) != "")
			{
				_fe3d.gameEntity_setNormalMap(instancedID, _fe3d.gameEntity_getNormalMapPath(previewID));
				_fe3d.gameEntity_setNormalMapped(instancedID, true);
			}
		}
	}
	else // Normal entity
	{
		// Add GAME entity
		_fe3d.gameEntity_add(newID, _fe3d.gameEntity_getObjPath(previewID), position, vec3(0.0f), _fe3d.gameEntity_getSize(previewID));

		// Bind AABB entities to GAME entity
		for (auto& previewAabbID : _fe3d.aabbEntity_getBoundIDs(previewID, true, false))
		{
			string newAabbID = newID + "_" + previewAabbID.substr(string(previewID + "_").size());
			_fe3d.aabbEntity_bindToGameEntity(newID, _fe3d.aabbEntity_getPosition(previewAabbID), _fe3d.aabbEntity_getSize(previewAabbID), true, newAabbID);
		}

		// Model properties
		_fe3d.gameEntity_setStaticToCamera(newID, _fe3d.gameEntity_isStaticToCamera(previewID));
		_fe3d.gameEntity_setFaceCulled(newID, _fe3d.gameEntity_isFaceCulled(previewID));
		_fe3d.gameEntity_setShadowed(newID, _fe3d.gameEntity_isShadowed(previewID));
		_fe3d.gameEntity_setTransparent(newID, _fe3d.gameEntity_isTransparent(previewID));
		_fe3d.gameEntity_setSceneReflective(newID, _fe3d.gameEntity_isSceneReflective(previewID));
		_fe3d.gameEntity_setSpecularLighted(newID, _fe3d.gameEntity_isSpecularLighted(previewID));
		_fe3d.gameEntity_setSpecularFactor(newID, _fe3d.gameEntity_getSpecularFactor(previewID));
		_fe3d.gameEntity_setSpecularIntensity(newID, _fe3d.gameEntity_getSpecularIntensity(previewID));
		_fe3d.gameEntity_setLightness(newID, _fe3d.gameEntity_getLightness(previewID));
		_fe3d.gameEntity_setOriginalLightness(newID, _fe3d.gameEntity_getOriginalLightness(previewID));
		_fe3d.gameEntity_setColor(newID, _fe3d.gameEntity_getColor(previewID));
		_fe3d.gameEntity_setUvRepeat(newID, _fe3d.gameEntity_getUvRepeat(previewID));
		_fe3d.gameEntity_setLevelOfDetailEntity(newID, _fe3d.gameEntity_getLevelOfDetailEntityID(previewID));

		// Diffuse map
		if (_fe3d.gameEntity_getDiffuseMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setDiffuseMap(newID, _fe3d.gameEntity_getDiffuseMapPath(previewID));
		}

		// Light map
		if (_fe3d.gameEntity_getLightMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setLightMap(newID, _fe3d.gameEntity_getLightMapPath(previewID));
			_fe3d.gameEntity_setLightMapped(newID, true);
		}

		// Reflection map
		if (_fe3d.gameEntity_getReflectionMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setReflectionMap(newID, _fe3d.gameEntity_getReflectionMapPath(previewID));
			_fe3d.gameEntity_setSkyReflective(newID, true);
		}

		// Normal map
		if (_fe3d.gameEntity_getNormalMapPath(previewID) != "")
		{
			_fe3d.gameEntity_setNormalMap(newID, _fe3d.gameEntity_getNormalMapPath(previewID));
			_fe3d.gameEntity_setNormalMapped(newID, true);
		}
	}
}

void SceneEditor::_placeModel(const string& newID, vec3 position, vec3 rotation, vec3 size, const string& objPath, const string& diffuseMapPath,
	const string& lightMapPath, const string& reflectionMapPath, const string& normalMapPath, bool isFrozen, bool isFaceCulled,
	bool isShadowed, bool isTransparent, bool isReflective, bool isSpecular, float specularFactor,
	float specularIntensity, float lightness, vec3 color, float uvRepeat, const string& lodEntityID, bool isInstanced,
	vector<vec3> instancedOffsets, vector<string> aabbNames, vector<vec3> aabbPositions, vector<vec3> aabbSizes)
{
	// Add GAME entity
	_fe3d.gameEntity_add(newID, objPath, position, rotation, size);

	// Add AABBs
	for (unsigned int i = 0; i < aabbNames.size(); i++)
	{
		_fe3d.aabbEntity_bindToGameEntity(newID, aabbPositions[i], aabbSizes[i], true, newID + "_" + aabbNames[i]);
	}

	// Model properties
	_fe3d.gameEntity_setStaticToCamera(newID, isFrozen);
	_fe3d.gameEntity_setFaceCulled(newID, isFaceCulled);
	_fe3d.gameEntity_setShadowed(newID, isShadowed);
	_fe3d.gameEntity_setTransparent(newID, isTransparent);
	_fe3d.gameEntity_setSceneReflective(newID, isReflective);
	_fe3d.gameEntity_setSpecularLighted(newID, isSpecular);
	_fe3d.gameEntity_setSpecularFactor(newID, specularFactor);
	_fe3d.gameEntity_setSpecularIntensity(newID, specularIntensity);
	_fe3d.gameEntity_setOriginalLightness(newID, lightness);
	_fe3d.gameEntity_setLightness(newID, lightness);
	_fe3d.gameEntity_setColor(newID, color);
	_fe3d.gameEntity_setUvRepeat(newID, uvRepeat);
	_fe3d.gameEntity_setLevelOfDetailEntity(newID, lodEntityID);
	_fe3d.gameEntity_setInstanced(newID, isInstanced, instancedOffsets);

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
		_fe3d.gameEntity_setSkyReflective(newID, true);
	}

	// Normal map
	if (normalMapPath != "")
	{
		_fe3d.gameEntity_setNormalMap(newID, normalMapPath);
		_fe3d.gameEntity_setNormalMapped(newID, true);
	}
}

void SceneEditor::_placeBillboard(const string& newID, const string& previewID, vec3 position)
{
	auto color = _fe3d.billboardEntity_getColor(previewID);
	auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(previewID);
	auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(previewID);

	// Add BILLBOARD entity
	vec2 size = _fe3d.billboardEntity_getSize(previewID);
	_fe3d.billBoardEntity_add(newID, color, position, vec3(0.0f), size, isFacingX, isFacingY);

	// Determine BILLBOARD entity type
	if (_fe3d.billboardEntity_getDiffuseMapPath(previewID) != "") // Textured billboard
	{
		_fe3d.billboardEntity_setDiffuseMap(newID, _fe3d.billboardEntity_getDiffuseMapPath(previewID), true);
	}
	else if (_fe3d.billboardEntity_getFontPath(previewID) != "") // Text billboard
	{
		_fe3d.billBoardEntity_setFont(newID, _fe3d.billboardEntity_getFontPath(previewID));
		_fe3d.billBoardEntity_setTextContent(newID, _fe3d.billboardEntity_getTextContent(previewID));
	}

	// Animation
	if (_fe3d.billboardEntity_isAnimationPlaying(previewID))
	{
		_fe3d.billboardEntity_setAnimationRows(newID, _fe3d.billboardEntity_getAnimationRows(previewID));
		_fe3d.billboardEntity_setAnimationColumns(newID, _fe3d.billboardEntity_getAnimationColumns(previewID));
		_fe3d.billboardEntity_setAnimationFramestep(newID, _fe3d.billboardEntity_getAnimationFramestep(previewID));
		_fe3d.billBoardEntity_playSpriteAnimation(newID, -1);
	}

	// Bind AABB entity to BILLBOARD entity
	_fe3d.aabbEntity_bindToBillboardEntity(newID, vec3(0.0f), true);

	// Miscellaneous
	_fe3d.billboardEntity_setTransparent(newID, _fe3d.billboardEntity_isTransparent(previewID));
}

void SceneEditor::_placeBillboard(const string& newID, const string& diffusePath, const string& fontPath, const string& textContent,
	vec3 position, vec3 rotation, vec2 size, vec3 color, bool facingX, bool facingY, bool isTransparent,
	bool isAnimated, int animationRows, int animationColumns, int animationFramestep)
{
	if (diffusePath != "") // Textured billboard
	{
		_fe3d.billBoardEntity_add(newID, diffusePath, position, rotation, size, isTransparent, facingX, facingY, true);
		_fe3d.billboardEntity_setColor(newID, color);

		// Animation
		if (isAnimated)
		{
			_fe3d.billboardEntity_setAnimationFramestep(newID, animationFramestep);
			_fe3d.billboardEntity_setAnimationRows(newID, animationRows);
			_fe3d.billboardEntity_setAnimationColumns(newID, animationColumns);
			_fe3d.billBoardEntity_playSpriteAnimation(newID, -1);
		}
	}
	else if (fontPath != "") // Text billboard
	{
		_fe3d.billBoardEntity_add(newID, textContent, fontPath, color, position, rotation, size, facingX, facingY);
	}
	else // Colored billboard
	{
		_fe3d.billBoardEntity_add(newID, color, position, rotation, size, facingX, facingY);
	}
	
	// Bind AABB entity to BILLBOARD entity
	_fe3d.aabbEntity_bindToBillboardEntity(newID, vec3(0.0f), true);
}
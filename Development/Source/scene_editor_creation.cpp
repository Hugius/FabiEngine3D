#include "scene_editor.hpp"

void SceneEditor::_placeSky(const string& newID, const string& previewID)
{
	_fe3d.skyEntity_add(newID);
	_fe3d.skyEntity_setDiffuseMaps(newID, _fe3d.skyEntity_getDiffuseMapPaths(previewID));
	_fe3d.skyEntity_setLightness(newID, _fe3d.skyEntity_getLightness(previewID));
	_fe3d.skyEntity_setRotationSpeed(newID, _fe3d.skyEntity_getRotationSpeed(previewID));
	_fe3d.skyEntity_setColor(newID, _fe3d.skyEntity_getColor(previewID));
	_fe3d.skyEntity_select(newID);
}

void SceneEditor::_placeSky(const string& newID, const array<string, 6>& diffuseMapPaths, float lightness, float rotationSpeed, vec3 color)
{
	_fe3d.skyEntity_add(newID);
	_fe3d.skyEntity_setDiffuseMaps(newID, diffuseMapPaths);
	_fe3d.skyEntity_setLightness(newID, lightness);
	_fe3d.skyEntity_setRotationSpeed(newID, rotationSpeed);
	_fe3d.skyEntity_setColor(newID, color);
	_fe3d.skyEntity_select(newID);
}

void SceneEditor::_placeTerrain(const string& newID, const string& previewID)
{
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
	_fe3d.terrainEntity_setSpecularLighted(newID, _fe3d.terrainEntity_isSpecularLighted(previewID));
	_fe3d.terrainEntity_setSpecularLightingIntensity(newID, _fe3d.terrainEntity_getSpecularLightingIntensity(previewID));

	// Diffuse maps
	if (_fe3d.terrainEntity_getDiffuseMapPath(previewID) != "")
	{
		_fe3d.terrainEntity_setDiffuseMap(newID, _fe3d.terrainEntity_getDiffuseMapPath(previewID));
	}

	// Blend map
	if (_fe3d.terrainEntity_getBlendMapPath(previewID) != "")
	{
		_fe3d.terrainEntity_setBlendMap(newID, _fe3d.terrainEntity_getBlendMapPath(previewID));
	}

	// Blend map red
	if (_fe3d.terrainEntity_getBlendMapPathR(previewID) != "")
	{
		_fe3d.terrainEntity_setBlendMapR(newID, _fe3d.terrainEntity_getBlendMapPathR(previewID));
	}

	// Blend map green
	if (_fe3d.terrainEntity_getBlendMapPathG(previewID) != "")
	{
		_fe3d.terrainEntity_setBlendMapG(newID, _fe3d.terrainEntity_getBlendMapPathG(previewID));
	}

	// Blend map blue
	if (_fe3d.terrainEntity_getBlendMapPathB(previewID) != "")
	{
		_fe3d.terrainEntity_setBlendMapB(newID, _fe3d.terrainEntity_getBlendMapPathB(previewID));
	}
}

void SceneEditor::_placeTerrain(const string& newID, const string& heightMapPath, float maxHeight, float uvRepeat, bool isBlendMapped, float lightness,
	float blendRepeatR, float blendRepeatG, float blendRepeatB, bool isSpecular, float specularIntensity, const string& diffuseMapPath, 
	const string& blendMapPath, const string& blendMapPathR, const string& blendMapPathG, const string& blendMapPathB)
{
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
	_fe3d.terrainEntity_setSpecularLighted(newID, isSpecular);
	_fe3d.terrainEntity_setSpecularLightingIntensity(newID, specularIntensity);

	// Texture maps
	if (diffuseMapPath != "") _fe3d.terrainEntity_setDiffuseMap(newID, diffuseMapPath);
	if (blendMapPath != "")   _fe3d.terrainEntity_setBlendMap(newID, blendMapPath);
	if (blendMapPathR != "")  _fe3d.terrainEntity_setBlendMapR(newID, blendMapPathR);
	if (blendMapPathG != "")  _fe3d.terrainEntity_setBlendMapG(newID, blendMapPathG);
	if (blendMapPathB != "")  _fe3d.terrainEntity_setBlendMapB(newID, blendMapPathB);
}

void SceneEditor::_placeWater(const string& newID, const string& previewID)
{
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

void SceneEditor::_placeWater(const string& newID, vec3 position, float size, bool isWaving, bool isRippling, bool isSpecularLighted, bool isReflective,
	bool isRefractive, float waveHeightFactor, float specularFactor, float specularIntensity, float transparency, vec3 color, float uvRepeat, vec2 speed,
	const string& dudvMapPath, const string& normalMapPath, const string& displacementMapPath)
{
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
#include "scene_editor.hpp"

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

void SceneEditor::_placeWater(const string& newID, Vec3 position, float size, bool isWaving, bool isRippling, bool isSpecularLighted, bool isReflective,
	bool isRefractive, float waveHeightFactor, float specularFactor, float specularIntensity, float transparency, Vec3 color, float uvRepeat, Vec2 speed,
	const string& dudvMapPath, const string& normalMapPath, const string& displacementMapPath)
{
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
	if (dudvMapPath != "")
	{
		_fe3d.waterEntity_setDudvMap(newID, dudvMapPath);
	}
	if (normalMapPath != "")
	{
		_fe3d.waterEntity_setNormalMap(newID, normalMapPath);
	}
	if (displacementMapPath != "")
	{
		_fe3d.waterEntity_setDisplacementMap(newID, displacementMapPath);
	}

	_loadedWaterID = newID;
}

void SceneEditor::_placeModel(const string& modelID, Vec3 position, Vec3 rotation, Vec3 size,
	const string& meshPath, const string& diffuseMapPath, const string& lightMapPath, const string& reflectionMapPath, const string& normalMapPath, 
	bool isFrozen, bool isFaceCulled, bool isShadowed, bool isTransparent, bool isSpecular, int reflectionType, float specularFactor,
	float specularIntensity, float lightness, Vec3 color, float uvRepeat, const string& lodEntityID, bool isInstanced,
	vector<Vec3> instancedOffsets, vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes, 
	string animationID, float minHeight, float maxHeight, float alpha)
{
	// Add MODEL entity
	_fe3d.modelEntity_add(modelID, meshPath, position, rotation, size);

	// Add AABBs
	for (unsigned int i = 0; i < aabbNames.size(); i++)
	{
		_fe3d.aabbEntity_bindToModelEntity(modelID, aabbPositions[i], aabbSizes[i], true, true, modelID + "@" + aabbNames[i]);
	}

	// Model properties
	_fe3d.modelEntity_setStaticToCamera(modelID, isFrozen);
	_fe3d.modelEntity_setFaceCulled(modelID, isFaceCulled);
	_fe3d.modelEntity_setShadowed(modelID, isShadowed);
	_fe3d.modelEntity_setTransparent(modelID, isTransparent);
	_fe3d.modelEntity_setSpecularLighted(modelID, isSpecular);
	_fe3d.modelEntity_setSpecularFactor(modelID, specularFactor);
	_fe3d.modelEntity_setSpecularIntensity(modelID, specularIntensity);
	_fe3d.modelEntity_setLightness(modelID, lightness);
	_fe3d.modelEntity_setColor(modelID, color);
	_fe3d.modelEntity_setUvRepeat(modelID, uvRepeat);
	_fe3d.modelEntity_setLevelOfDetailEntity(modelID, lodEntityID);
	_fe3d.modelEntity_setInstanced(modelID, isInstanced, instancedOffsets);
	_fe3d.modelEntity_setMinHeight(modelID, minHeight);
	_fe3d.modelEntity_setMaxHeight(modelID, maxHeight);
	_fe3d.modelEntity_setAlpha(modelID, alpha);

	// Reflection type
	if (reflectionType == 1)
	{
		_fe3d.modelEntity_setSkyReflective(modelID, true);
	}
	else if (reflectionType == 2)
	{
		_fe3d.modelEntity_setSceneReflective(modelID, true);
	}

	// Save original lightness & transformation
	if (_isEditorLoaded)
	{
		_initialModelLightness[modelID] = lightness;
		_initialModelPosition[modelID] = position;
		_initialModelRotation[modelID] = rotation;
		_initialModelSize[modelID] = size;
	}

	// Diffuse map
	if (diffuseMapPath != "")
	{
		_fe3d.modelEntity_setDiffuseMap(modelID, diffuseMapPath);
	}

	// Light map
	if (lightMapPath != "")
	{
		_fe3d.modelEntity_setLightMap(modelID, lightMapPath);
		_fe3d.modelEntity_setLightMapped(modelID, true);
	}

	// Reflection map
	if (reflectionMapPath != "")
	{
		_fe3d.modelEntity_setReflectionMap(modelID, reflectionMapPath);
	}

	// Normal map
	if (normalMapPath != "")
	{
		_fe3d.modelEntity_setNormalMap(modelID, normalMapPath);
		_fe3d.modelEntity_setNormalMapped(modelID, true);
	}

	// Play animation
	if (!animationID.empty())
	{
		_animationEditor.startAnimation(animationID, modelID, -1);
	}

	_loadedModelIDs.push_back(modelID);
}

void SceneEditor::_placeBillboard(const string& billboardID,
	const string& diffusePath, const string& fontPath, const string& textContent,
	Vec3 position, Vec3 rotation, Vec2 size, Vec3 color, bool facingX, bool facingY, bool isTransparent,
	bool isAnimated, int animationRows, int animationColumns, int animationFramestep, float lightness, float minHeight, float maxHeight)
{
	if (diffusePath != "") // Textured billboard
	{
		_fe3d.billboardEntity_add(billboardID, diffusePath, position, rotation, size, isTransparent, facingX, facingY, true);
		_fe3d.billboardEntity_setColor(billboardID, color);

		// Animation
		if (isAnimated)
		{
			_fe3d.billboardEntity_setAnimationFramestep(billboardID, animationFramestep);
			_fe3d.billboardEntity_setAnimationRows(billboardID, animationRows);
			_fe3d.billboardEntity_setAnimationColumns(billboardID, animationColumns);
			_fe3d.billboardEntity_playAnimation(billboardID, -1);
		}
	}
	else if (fontPath != "") // Text billboard
	{
		_fe3d.billboardEntity_add(billboardID, textContent, fontPath, color, position, rotation, size, facingX, facingY);
	}
	else // Colored billboard
	{
		_fe3d.billboardEntity_add(billboardID, color, position, rotation, size, facingX, facingY);
	}
	
	// Bind AABB entity to BILLBOARD entity
	_fe3d.aabbEntity_bindToBillboardEntity(billboardID, true, true);

	// Miscellaneous
	_fe3d.billboardEntity_setLightness(billboardID, lightness);
	_fe3d.billboardEntity_setMinHeight(billboardID, minHeight);
	_fe3d.billboardEntity_setMaxHeight(billboardID, maxHeight);

	// Save original lightness
	if (_isEditorLoaded)
	{
		_initialBillboardLightness[billboardID] = lightness;
	}

	_loadedBillboardIDs.push_back(billboardID);
}
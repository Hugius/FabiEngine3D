#include "scene_editor.hpp"
#include "logger.hpp"

const bool SceneEditor::_copyPreviewSky(const string& newID, const string& previewID)
{
	// Error checking
	if(_fe3d.skyEntity_isExisting(newID))
	{
		Logger::throwWarning("Scene sky with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.skyEntity_isExisting(previewID))
	{
		Logger::throwWarning("Editor sky of scene sky with ID \"" + newID + "\" not existing anymore!");
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

const bool SceneEditor::_copyPreviewTerrain(const string& newID, const string& previewID)
{
	// Error checking
	if(_fe3d.terrainEntity_isExisting(newID))
	{
		Logger::throwWarning("Scene terrain with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.terrainEntity_isExisting(previewID))
	{
		Logger::throwWarning("Editor terrain of scene terrain with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if(_fe3d.terrainEntity_isExisting(newID))
	{
		_fe3d.terrainEntity_delete(newID);
	}

	// Create terrain entity
	_fe3d.terrainEntity_create(newID, _fe3d.terrainEntity_getHeightMapPath(previewID));
	_fe3d.terrainEntity_select(newID);

	// Fill terrain entity
	_fe3d.terrainEntity_setMaxHeight(newID, _fe3d.terrainEntity_getMaxHeight(previewID));
	_fe3d.terrainEntity_setTextureRepeat(newID, _fe3d.terrainEntity_getTextureRepeat(previewID));
	_fe3d.terrainEntity_setLightness(newID, _fe3d.terrainEntity_getLightness(previewID));
	_fe3d.terrainEntity_setRedRepeat(newID, _fe3d.terrainEntity_getRedRepeat(previewID));
	_fe3d.terrainEntity_setGreenRepeat(newID, _fe3d.terrainEntity_getGreenRepeat(previewID));
	_fe3d.terrainEntity_setBlueRepeat(newID, _fe3d.terrainEntity_getBlueRepeat(previewID));
	_fe3d.terrainEntity_setSpecular(newID, _fe3d.terrainEntity_isSpecular(previewID));
	_fe3d.terrainEntity_setSpecularShininess(newID, _fe3d.terrainEntity_getSpecularShininess(previewID));
	_fe3d.terrainEntity_setSpecularIntensity(newID, _fe3d.terrainEntity_getSpecularIntensity(previewID));

	// Diffuse map
	if(_fe3d.terrainEntity_hasDiffuseMap(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMap(newID, _fe3d.terrainEntity_getDiffuseMapPath(previewID));
	}

	// Normal map
	if(_fe3d.terrainEntity_hasNormalMap(previewID))
	{
		_fe3d.terrainEntity_setNormalMap(newID, _fe3d.terrainEntity_getNormalMapPath(previewID));
	}

	// Normal map R
	if(_fe3d.terrainEntity_hasNormalMapR(previewID))
	{
		_fe3d.terrainEntity_setNormalMapR(newID, _fe3d.terrainEntity_getNormalMapPathR(previewID));
	}

	// Normal map G
	if(_fe3d.terrainEntity_hasNormalMapG(previewID))
	{
		_fe3d.terrainEntity_setNormalMapG(newID, _fe3d.terrainEntity_getNormalMapPathG(previewID));
	}

	// Normal map B
	if(_fe3d.terrainEntity_hasNormalMapB(previewID))
	{
		_fe3d.terrainEntity_setNormalMapB(newID, _fe3d.terrainEntity_getNormalMapPathB(previewID));
	}

	// Blend map
	if(_fe3d.terrainEntity_hasBlendMap(previewID))
	{
		_fe3d.terrainEntity_setBlendMap(newID, _fe3d.terrainEntity_getBlendMapPath(previewID));
	}

	// Blend map red
	if(_fe3d.terrainEntity_hasDiffuseMapR(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMapR(newID, _fe3d.terrainEntity_getDiffuseMapPathR(previewID));
	}

	// Blend map green
	if(_fe3d.terrainEntity_hasDiffuseMapG(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMapG(newID, _fe3d.terrainEntity_getDiffuseMapPathG(previewID));
	}

	// Blend map blue
	if(_fe3d.terrainEntity_hasDiffuseMapB(previewID))
	{
		_fe3d.terrainEntity_setDiffuseMapB(newID, _fe3d.terrainEntity_getDiffuseMapPathB(previewID));
	}

	// Save ID
	_loadedTerrainID = newID;

	return true;
}

const bool SceneEditor::_copyPreviewWater(const string& newID, const string& previewID)
{
	// Error checking
	if(_fe3d.waterEntity_isExisting(newID))
	{
		Logger::throwWarning("Scene water with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.waterEntity_isExisting(previewID))
	{
		Logger::throwWarning("Editor water of scene water with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if(_fe3d.waterEntity_isExisting(newID))
	{
		_fe3d.waterEntity_delete(newID);
	}

	// Create water entity
	_fe3d.waterEntity_create(newID);
	_fe3d.waterEntity_select(newID);

	// Fill water entity
	_fe3d.waterEntity_setHeight(newID, _fe3d.waterEntity_getHeight(previewID));
	_fe3d.waterEntity_setSize(newID, _fe3d.waterEntity_getSize(previewID));
	_fe3d.waterEntity_setSpecular(newID, _fe3d.waterEntity_isSpecular(previewID));
	_fe3d.waterEntity_setReflective(newID, _fe3d.waterEntity_isReflective(previewID));
	_fe3d.waterEntity_setRefractive(newID, _fe3d.waterEntity_isRefractive(previewID));
	_fe3d.waterEntity_setWaveHeight(newID, _fe3d.waterEntity_getWaveHeight(previewID));
	_fe3d.waterEntity_setQuality(newID, _fe3d.waterEntity_getQuality(previewID));
	_fe3d.waterEntity_setSpecularShininess(newID, _fe3d.waterEntity_getSpecularShininess(previewID));
	_fe3d.waterEntity_setSpecularIntensity(newID, _fe3d.waterEntity_getSpecularIntensity(previewID));
	_fe3d.waterEntity_setTransparency(newID, _fe3d.waterEntity_getTransparency(previewID));
	_fe3d.waterEntity_setColor(newID, _fe3d.waterEntity_getColor(previewID));
	_fe3d.waterEntity_setTextureRepeat(newID, _fe3d.waterEntity_getTextureRepeat(previewID));
	_fe3d.waterEntity_setSpeed(newID, _fe3d.waterEntity_getSpeed(previewID));

	// DUDV map
	if(_fe3d.waterEntity_hasDudvMap(previewID))
	{
		_fe3d.waterEntity_setDudvMap(newID, _fe3d.waterEntity_getDudvMapPath(previewID));
	}

	// Normal map
	if(_fe3d.waterEntity_hasNormalMap(previewID))
	{
		_fe3d.waterEntity_setNormalMap(newID, _fe3d.waterEntity_getNormalMapPath(previewID));
	}

	// Displacement map
	if(_fe3d.waterEntity_hasDisplacementMap(previewID))
	{
		_fe3d.waterEntity_setDisplacementMap(newID, _fe3d.waterEntity_getDisplacementMapPath(previewID));
	}

	// Save ID
	_loadedWaterID = newID;

	return true;
}

const bool SceneEditor::_copyPreviewModel(const string& newID, const string& previewID, Vec3 position, bool isFromOutside)
{
	// Error checking
	if(_fe3d.modelEntity_isExisting(newID) && !_fe3d.modelEntity_isInstanced(previewID))
	{
		Logger::throwWarning("Model with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.modelEntity_isExisting(previewID))
	{
		Logger::throwWarning("Editor model of model with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create model entity
	_fe3d.modelEntity_create(newID, _fe3d.modelEntity_getMeshPath(previewID));

	// Set instancing
	if(_fe3d.modelEntity_isInstanced(previewID))
	{
		_fe3d.modelEntity_enableInstancing(newID, { Vec3(0.0f) });
	}

	// Set properties
	_fe3d.modelEntity_setBasePosition(newID, position);
	_fe3d.modelEntity_setBaseSize(newID, _fe3d.modelEntity_getBaseSize(previewID));
	_fe3d.modelEntity_setLevelOfDetailSize(newID, _fe3d.modelEntity_getBaseSize(previewID));
	_fe3d.modelEntity_setStaticToCamera(newID, _fe3d.modelEntity_isStaticToCamera(previewID));
	_fe3d.modelEntity_setLevelOfDetailEntity(newID, _fe3d.modelEntity_getLevelOfDetailEntityID(previewID));
	_fe3d.modelEntity_setFaceCulled(newID, _fe3d.modelEntity_isFaceCulled(previewID));
	_fe3d.modelEntity_setRotationOrder(newID, _fe3d.modelEntity_getRotationOrder(previewID));

	// Set parts
	for(const auto& partID : _fe3d.modelEntity_getPartIDs(previewID))
	{
		// Set diffuse map
		if(_fe3d.modelEntity_hasDiffuseMap(previewID, partID))
		{
			_fe3d.modelEntity_setDiffuseMap(newID, partID, _fe3d.modelEntity_getDiffuseMapPath(previewID, partID));
		}

		// Set emission map
		if(_fe3d.modelEntity_hasEmissionMap(previewID, partID))
		{
			_fe3d.modelEntity_setEmissionMap(newID, partID, _fe3d.modelEntity_getEmissionMapPath(previewID, partID));
		}

		// Set specular map
		if(_fe3d.modelEntity_hasSpecularMap(previewID, partID))
		{
			_fe3d.modelEntity_setSpecularMap(newID, partID, _fe3d.modelEntity_getSpecularMapPath(previewID, partID));
		}

		// Set reflection map
		if(_fe3d.modelEntity_hasReflectionMap(previewID, partID))
		{
			_fe3d.modelEntity_setReflectionMap(newID, partID, _fe3d.modelEntity_getReflectionMapPath(previewID, partID));
		}

		// Set normal map
		if(_fe3d.modelEntity_hasNormalMap(previewID, partID))
		{
			_fe3d.modelEntity_setNormalMap(newID, partID, _fe3d.modelEntity_getNormalMapPath(previewID, partID));
		}

		// Set properties
		_fe3d.modelEntity_setLightness(newID, partID, _fe3d.modelEntity_getLightness(previewID, partID));
		_fe3d.modelEntity_setSpecular(newID, partID, _fe3d.modelEntity_isSpecular(previewID, partID));
		_fe3d.modelEntity_setSpecularShininess(newID, partID, _fe3d.modelEntity_getSpecularShininess(previewID, partID));
		_fe3d.modelEntity_setSpecularIntensity(newID, partID, _fe3d.modelEntity_getSpecularIntensity(previewID, partID));
		_fe3d.modelEntity_setReflective(newID, partID, _fe3d.modelEntity_isReflective(previewID, partID));
		_fe3d.modelEntity_setReflectionType(newID, partID, _fe3d.modelEntity_getReflectionType(previewID, partID));
		_fe3d.modelEntity_setReflectivity(newID, partID, _fe3d.modelEntity_getReflectivity(previewID, partID));
		_fe3d.modelEntity_setColor(newID, partID, _fe3d.modelEntity_getColor(previewID, partID));
		_fe3d.modelEntity_setTextureRepeat(newID, partID, _fe3d.modelEntity_getTextureRepeat(previewID, partID));
	}

	// Bind AABB entities to model entity
	for(const auto& previewAabbID : _fe3d.aabbEntity_getChildIDs(previewID, AabbParentType::MODEL_ENTITY))
	{
		const string newAabbID = (newID + "@" + previewAabbID.substr(string(previewID + "_").size()));
		_fe3d.aabbEntity_create(newAabbID);
		_fe3d.aabbEntity_setParent(newAabbID, newID, AabbParentType::MODEL_ENTITY);
		_fe3d.aabbEntity_setLocalPosition(newAabbID, _fe3d.aabbEntity_getPosition(previewAabbID));
		_fe3d.aabbEntity_setLocalSize(newAabbID, _fe3d.aabbEntity_getSize(previewAabbID));
	}

	// Save original transformation
	if(_isEditorLoaded)
	{
		_initialModelPosition[newID] = _fe3d.modelEntity_getBasePosition(previewID);
		_initialModelRotation[newID] = _fe3d.modelEntity_getBaseRotation(previewID);
		_initialModelSize[newID] = _fe3d.modelEntity_getBaseSize(previewID);
	}

	// Save ID
	if(isFromOutside)
	{
		_outsideLoadedModelIDs[newID] = previewID;
	}
	else
	{
		_loadedModelIDs[newID] = previewID;
	}

	return true;
}

const bool SceneEditor::_copyPreviewBillboard(const string& newID, const string& previewID, Vec3 position, bool isFromOutside)
{
	// Error checking
	if(_fe3d.billboardEntity_isExisting(newID))
	{
		Logger::throwWarning("Billboard with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.billboardEntity_isExisting(previewID))
	{
		Logger::throwWarning("Editor billboard of billboard with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create billboard entity
	_fe3d.billboardEntity_create(newID);

	// Bind AABB entity
	_fe3d.aabbEntity_create(newID);
	_fe3d.aabbEntity_setParent(newID, newID, AabbParentType::BILLBOARD_ENTITY);

	// Diffuse map
	if(_fe3d.billboardEntity_hasDiffuseMap(previewID) && !_fe3d.billboardEntity_isText(previewID))
	{
		_fe3d.billboardEntity_setDiffuseMap(newID, _fe3d.billboardEntity_getDiffuseMapPath(previewID));
	}

	// Emission map
	if(_fe3d.billboardEntity_hasEmissionMap(previewID))
	{
		_fe3d.billboardEntity_setEmissionMap(newID, _fe3d.billboardEntity_getEmissionMapPath(previewID));
	}

	// Text
	if(_fe3d.billboardEntity_isText(previewID))
	{
		_fe3d.billboardEntity_setFont(newID, _fe3d.billboardEntity_getFontPath(previewID));
		_fe3d.billboardEntity_setTextContent(newID, _fe3d.billboardEntity_getTextContent(previewID));
	}

	// Start sprite animation
	if(_fe3d.billboardEntity_isSpriteAnimationStarted(previewID))
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
	_fe3d.billboardEntity_setLightness(newID, _fe3d.billboardEntity_getLightness(previewID));

	// Save ID
	if(isFromOutside)
	{
		_outsideLoadedBillboardIDs[newID] = previewID;
	}
	else
	{
		_loadedBillboardIDs[newID] = previewID;
	}

	return true;
}

const bool SceneEditor::_copyPreviewSound(const string& newID, const string& previewID, Vec3 position, bool isFromOutside)
{
	// Error checking
	if(_fe3d.sound_isExisting(newID))
	{
		Logger::throwWarning("Sound with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.sound_isExisting(previewID))
	{
		Logger::throwWarning("Editor audio of sound with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create sound
	_fe3d.sound_create(newID, _fe3d.sound_getFilePath(previewID));
	_fe3d.sound_make3D(newID, position, 0.0f, 0.0f);

	// Save ID
	if(isFromOutside)
	{
		_outsideLoadedSoundIDs[newID] = previewID;
	}
	else
	{
		_loadedSoundIDs[newID] = previewID;
	}

	return true;
}
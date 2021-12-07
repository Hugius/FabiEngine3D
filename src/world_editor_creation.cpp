#include "world_editor.hpp"
#include "logger.hpp"

const bool WorldEditor::_copyPreviewSky(const string& newID, const string& previewID)
{
	// Error checking
	if(_fe3d.sky_isExisting(newID))
	{
		Logger::throwWarning("World sky with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.sky_isExisting(previewID))
	{
		Logger::throwWarning("Editor sky of world sky with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create new sky
	_fe3d.sky_create(newID);
	_fe3d.sky_setCubeMaps(newID, _fe3d.sky_getCubeMapPaths(previewID));
	_fe3d.sky_setLightness(newID, _fe3d.sky_getLightness(previewID));
	_fe3d.sky_setRotation(newID, _fe3d.sky_getRotation(previewID));
	_fe3d.sky_setColor(newID, _fe3d.sky_getColor(previewID));
	_fe3d.sky_selectMainSky(newID);

	// Save ID
	_loadedSkyID = newID;

	return true;
}

const bool WorldEditor::_copyPreviewTerrain(const string& newID, const string& previewID)
{
	// Error checking
	if(_fe3d.terrain_isExisting(newID))
	{
		Logger::throwWarning("World terrain with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.terrain_isExisting(previewID))
	{
		Logger::throwWarning("Editor terrain of world terrain with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if(_fe3d.terrain_isExisting(newID))
	{
		_fe3d.terrain_delete(newID);
	}

	// Create terrain entity
	_fe3d.terrain_create(newID, _fe3d.terrain_getHeightMapPath(previewID));
	_fe3d.terrain_select(newID);

	// Fill terrain entity
	_fe3d.terrain_setMaxHeight(newID, _fe3d.terrain_getMaxHeight(previewID));
	_fe3d.terrain_setTextureRepeat(newID, _fe3d.terrain_getTextureRepeat(previewID));
	_fe3d.terrain_setLightness(newID, _fe3d.terrain_getLightness(previewID));
	_fe3d.terrain_setRedRepeat(newID, _fe3d.terrain_getRedRepeat(previewID));
	_fe3d.terrain_setGreenRepeat(newID, _fe3d.terrain_getGreenRepeat(previewID));
	_fe3d.terrain_setBlueRepeat(newID, _fe3d.terrain_getBlueRepeat(previewID));
	_fe3d.terrain_setSpecular(newID, _fe3d.terrain_isSpecular(previewID));
	_fe3d.terrain_setSpecularShininess(newID, _fe3d.terrain_getSpecularShininess(previewID));
	_fe3d.terrain_setSpecularIntensity(newID, _fe3d.terrain_getSpecularIntensity(previewID));

	// Diffuse map
	if(_fe3d.terrain_hasDiffuseMap(previewID))
	{
		_fe3d.terrain_setDiffuseMap(newID, _fe3d.terrain_getDiffuseMapPath(previewID));
	}

	// Normal map
	if(_fe3d.terrain_hasNormalMap(previewID))
	{
		_fe3d.terrain_setNormalMap(newID, _fe3d.terrain_getNormalMapPath(previewID));
	}

	// Normal map R
	if(_fe3d.terrain_hasNormalMapR(previewID))
	{
		_fe3d.terrain_setNormalMapR(newID, _fe3d.terrain_getNormalMapPathR(previewID));
	}

	// Normal map G
	if(_fe3d.terrain_hasNormalMapG(previewID))
	{
		_fe3d.terrain_setNormalMapG(newID, _fe3d.terrain_getNormalMapPathG(previewID));
	}

	// Normal map B
	if(_fe3d.terrain_hasNormalMapB(previewID))
	{
		_fe3d.terrain_setNormalMapB(newID, _fe3d.terrain_getNormalMapPathB(previewID));
	}

	// Blend map
	if(_fe3d.terrain_hasBlendMap(previewID))
	{
		_fe3d.terrain_setBlendMap(newID, _fe3d.terrain_getBlendMapPath(previewID));
	}

	// Blend map red
	if(_fe3d.terrain_hasDiffuseMapR(previewID))
	{
		_fe3d.terrain_setDiffuseMapR(newID, _fe3d.terrain_getDiffuseMapPathR(previewID));
	}

	// Blend map green
	if(_fe3d.terrain_hasDiffuseMapG(previewID))
	{
		_fe3d.terrain_setDiffuseMapG(newID, _fe3d.terrain_getDiffuseMapPathG(previewID));
	}

	// Blend map blue
	if(_fe3d.terrain_hasDiffuseMapB(previewID))
	{
		_fe3d.terrain_setDiffuseMapB(newID, _fe3d.terrain_getDiffuseMapPathB(previewID));
	}

	// Save ID
	_loadedTerrainID = newID;

	return true;
}

const bool WorldEditor::_copyPreviewWater(const string& newID, const string& previewID)
{
	// Error checking
	if(_fe3d.water_isExisting(newID))
	{
		Logger::throwWarning("World water with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.water_isExisting(previewID))
	{
		Logger::throwWarning("Editor water of world water with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Delete old
	if(_fe3d.water_isExisting(newID))
	{
		_fe3d.water_delete(newID);
	}

	// Create water entity
	_fe3d.water_create(newID);
	_fe3d.water_select(newID);

	// Fill water entity
	_fe3d.water_setHeight(newID, _fe3d.water_getHeight(previewID));
	_fe3d.water_setSize(newID, _fe3d.water_getSize(previewID));
	_fe3d.water_setSpecular(newID, _fe3d.water_isSpecular(previewID));
	_fe3d.water_setReflective(newID, _fe3d.water_isReflective(previewID));
	_fe3d.water_setRefractive(newID, _fe3d.water_isRefractive(previewID));
	_fe3d.water_setWaveHeight(newID, _fe3d.water_getWaveHeight(previewID));
	_fe3d.water_setQuality(newID, _fe3d.water_getQuality(previewID));
	_fe3d.water_setSpecularShininess(newID, _fe3d.water_getSpecularShininess(previewID));
	_fe3d.water_setSpecularIntensity(newID, _fe3d.water_getSpecularIntensity(previewID));
	_fe3d.water_setTransparency(newID, _fe3d.water_getTransparency(previewID));
	_fe3d.water_setColor(newID, _fe3d.water_getColor(previewID));
	_fe3d.water_setTextureRepeat(newID, _fe3d.water_getTextureRepeat(previewID));
	_fe3d.water_setSpeed(newID, _fe3d.water_getSpeed(previewID));

	// DUDV map
	if(_fe3d.water_hasDudvMap(previewID))
	{
		_fe3d.water_setDudvMap(newID, _fe3d.water_getDudvMapPath(previewID));
	}

	// Normal map
	if(_fe3d.water_hasNormalMap(previewID))
	{
		_fe3d.water_setNormalMap(newID, _fe3d.water_getNormalMapPath(previewID));
	}

	// Displacement map
	if(_fe3d.water_hasDisplacementMap(previewID))
	{
		_fe3d.water_setDisplacementMap(newID, _fe3d.water_getDisplacementMapPath(previewID));
	}

	// Save ID
	_loadedWaterID = newID;

	return true;
}

const bool WorldEditor::_copyPreviewModel(const string& newID, const string& previewID, fvec3 position, bool isFromOutside)
{
	// Error checking
	if(_fe3d.model_isExisting(newID) && !_fe3d.model_isInstanced(previewID))
	{
		Logger::throwWarning("Model with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.model_isExisting(previewID))
	{
		Logger::throwWarning("Editor model of model with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create model entity
	_fe3d.model_create(newID, _fe3d.model_getMeshPath(previewID));

	// Set instancing
	if(_fe3d.model_isInstanced(previewID))
	{
		_fe3d.model_enableInstancing(newID, {fvec3(0.0f)});
	}

	// Set properties
	_fe3d.model_setBasePosition(newID, position);
	_fe3d.model_setBaseSize(newID, _fe3d.model_getBaseSize(previewID));
	_fe3d.model_setLevelOfDetailSize(newID, _fe3d.model_getBaseSize(previewID));
	_fe3d.model_setFrozen(newID, _fe3d.model_isFrozen(previewID));
	_fe3d.model_setLevelOfDetailEntityID(newID, _fe3d.model_getLevelOfDetailEntityID(previewID));
	_fe3d.model_setFaceCulled(newID, _fe3d.model_isFaceCulled(previewID));
	_fe3d.model_setRotationOrder(newID, _fe3d.model_getRotationOrder(previewID));

	// Set parts
	for(const auto& partID : _fe3d.model_getPartIDs(previewID))
	{
		// Set diffuse map
		if(_fe3d.model_hasDiffuseMap(previewID, partID))
		{
			_fe3d.model_setDiffuseMap(newID, partID, _fe3d.model_getDiffuseMapPath(previewID, partID));
		}

		// Set emission map
		if(_fe3d.model_hasEmissionMap(previewID, partID))
		{
			_fe3d.model_setEmissionMap(newID, partID, _fe3d.model_getEmissionMapPath(previewID, partID));
		}

		// Set specular map
		if(_fe3d.model_hasSpecularMap(previewID, partID))
		{
			_fe3d.model_setSpecularMap(newID, partID, _fe3d.model_getSpecularMapPath(previewID, partID));
		}

		// Set reflection map
		if(_fe3d.model_hasReflectionMap(previewID, partID))
		{
			_fe3d.model_setReflectionMap(newID, partID, _fe3d.model_getReflectionMapPath(previewID, partID));
		}

		// Set normal map
		if(_fe3d.model_hasNormalMap(previewID, partID))
		{
			_fe3d.model_setNormalMap(newID, partID, _fe3d.model_getNormalMapPath(previewID, partID));
		}

		// Set properties
		_fe3d.model_setLightness(newID, partID, _fe3d.model_getLightness(previewID, partID));
		_fe3d.model_setSpecular(newID, partID, _fe3d.model_isSpecular(previewID, partID));
		_fe3d.model_setSpecularShininess(newID, partID, _fe3d.model_getSpecularShininess(previewID, partID));
		_fe3d.model_setSpecularIntensity(newID, partID, _fe3d.model_getSpecularIntensity(previewID, partID));
		_fe3d.model_setReflective(newID, partID, _fe3d.model_isReflective(previewID, partID));
		_fe3d.model_setReflectionType(newID, partID, _fe3d.model_getReflectionType(previewID, partID));
		_fe3d.model_setReflectivity(newID, partID, _fe3d.model_getReflectivity(previewID, partID));
		_fe3d.model_setColor(newID, partID, _fe3d.model_getColor(previewID, partID));
		_fe3d.model_setTextureRepeat(newID, partID, _fe3d.model_getTextureRepeat(previewID, partID));
	}

	// Bind AABB entities to model entity
	for(const auto& previewAabbID : _fe3d.aabb_getChildIDs(previewID, AabbParentEntityType::MODEL))
	{
		const string newAabbID = (newID + "@" + previewAabbID.substr(string(previewID + "_").size()));
		_fe3d.aabb_create(newAabbID);
		_fe3d.aabb_setParentEntityID(newAabbID, newID);
		_fe3d.aabb_setParentEntityType(newAabbID, AabbParentEntityType::MODEL);
		_fe3d.aabb_setLocalPosition(newAabbID, _fe3d.aabb_getPosition(previewAabbID));
		_fe3d.aabb_setLocalSize(newAabbID, _fe3d.aabb_getSize(previewAabbID));
	}

	// Save initial transformation
	if(_isEditorLoaded)
	{
		_initialModelPosition[newID] = _fe3d.model_getBasePosition(previewID);
		_initialModelRotation[newID] = _fe3d.model_getBaseRotation(previewID);
		_initialModelSize[newID] = _fe3d.model_getBaseSize(previewID);
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

const bool WorldEditor::_copyPreviewBillboard(const string& newID, const string& previewID, fvec3 position, bool isFromOutside)
{
	// Error checking
	if(_fe3d.billboard_isExisting(newID))
	{
		Logger::throwWarning("Billboard with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.billboard_isExisting(previewID))
	{
		Logger::throwWarning("Editor billboard of billboard with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create billboard entity
	_fe3d.billboard_create(newID);

	// Bind AABB entity
	_fe3d.aabb_create(newID);
	_fe3d.aabb_setParentEntityID(newID, newID);
	_fe3d.aabb_setParentEntityType(newID, AabbParentEntityType::BILLBOARD);

	// Diffuse map
	if(_fe3d.billboard_hasDiffuseMap(previewID) && !_fe3d.billboard_isTextual(previewID))
	{
		_fe3d.billboard_setDiffuseMap(newID, _fe3d.billboard_getDiffuseMapPath(previewID));
	}

	// Emission map
	if(_fe3d.billboard_hasEmissionMap(previewID))
	{
		_fe3d.billboard_setEmissionMap(newID, _fe3d.billboard_getEmissionMapPath(previewID));
	}

	// Text
	if(_fe3d.billboard_isTextual(previewID))
	{
		_fe3d.billboard_setFont(newID, _fe3d.billboard_getFontPath(previewID));
		_fe3d.billboard_setTextContent(newID, _fe3d.billboard_getTextContent(previewID));
	}

	// Start sprite animation
	if(_fe3d.billboard_isSpriteAnimationStarted(previewID))
	{
		_fe3d.billboard_setSpriteAnimationRowCount(newID, _fe3d.billboard_getSpriteAnimationRowCount(previewID));
		_fe3d.billboard_setSpriteAnimationColumnCount(newID, _fe3d.billboard_getSpriteAnimationColumnCount(previewID));
		_fe3d.billboard_setSpriteAnimationFramestep(newID, _fe3d.billboard_getSpriteAnimationFramestep(previewID));
		_fe3d.billboard_startSpriteAnimation(newID, -1);
	}

	// Set properties
	_fe3d.billboard_setPosition(newID, position);
	_fe3d.billboard_setSize(newID, _fe3d.billboard_getSize(previewID));
	_fe3d.billboard_setFacingCameraX(newID, _fe3d.billboard_isFacingCameraX(previewID));
	_fe3d.billboard_setFacingCameraY(newID, _fe3d.billboard_isFacingCameraY(previewID));
	_fe3d.billboard_setColor(newID, _fe3d.billboard_getColor(previewID));
	_fe3d.billboard_setShadowed(newID, _fe3d.billboard_isShadowed(previewID));
	_fe3d.billboard_setReflected(newID, _fe3d.billboard_isReflected(previewID));
	_fe3d.billboard_setLightness(newID, _fe3d.billboard_getLightness(previewID));

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

const bool WorldEditor::_copyPreviewSound(const string& newID, const string& previewID, fvec3 position, bool isFromOutside)
{
	// Error checking
	if(_fe3d.sound3D_isExisting(newID))
	{
		Logger::throwWarning("3D sound with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.sound2D_isExisting(previewID))
	{
		Logger::throwWarning("2D sound with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	// Create sound
	_fe3d.sound3D_create(newID, _fe3d.sound2D_getAudioPath(previewID));
	_fe3d.sound3D_setPosition(newID, position);

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
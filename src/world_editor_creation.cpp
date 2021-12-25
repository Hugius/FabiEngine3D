#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::copyTemplateModel(const string& newID, const string& templateID, fvec3 position)
{
	_copyTemplateModel(newID, templateID, position, true);
}

void WorldEditor::copyTemplateBillboard(const string& newID, const string& templateID, fvec3 position)
{
	_copyTemplateBillboard(newID, templateID, position, true);
}

void WorldEditor::copyTemplateSound(const string& newID, const string& templateID, fvec3 position)
{
	_copyTemplateSound(newID, templateID, position, true);
}

const bool WorldEditor::_copyTemplateSky(const string& newID, const string& templateID)
{
	if(_fe3d.sky_isExisting(newID))
	{
		Logger::throwWarning("World sky with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.sky_isExisting(templateID))
	{
		Logger::throwWarning("Editor sky of world sky with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d.sky_create(newID);
	_fe3d.sky_setCubeMaps(newID, _fe3d.sky_getCubeMapPaths(templateID));
	_fe3d.sky_setLightness(newID, _fe3d.sky_getLightness(templateID));
	_fe3d.sky_setRotation(newID, _fe3d.sky_getRotation(templateID));
	_fe3d.sky_setColor(newID, _fe3d.sky_getColor(templateID));
	_fe3d.sky_selectMainSky(newID);

	_loadedSkyID = newID;

	return true;
}

const bool WorldEditor::_copyTemplateTerrain(const string& newID, const string& templateID)
{
	if(_fe3d.terrain_isExisting(newID))
	{
		Logger::throwWarning("World terrain with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.terrain_isExisting(templateID))
	{
		Logger::throwWarning("Editor terrain of world terrain with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	if(_fe3d.terrain_isExisting(newID))
	{
		_fe3d.terrain_delete(newID);
	}

	_fe3d.terrain_create(newID, _fe3d.terrain_getHeightMapPath(templateID));
	_fe3d.terrain_select(newID);

	_fe3d.terrain_setMaxHeight(newID, _fe3d.terrain_getMaxHeight(templateID));
	_fe3d.terrain_setTextureRepeat(newID, _fe3d.terrain_getTextureRepeat(templateID));
	_fe3d.terrain_setLightness(newID, _fe3d.terrain_getLightness(templateID));
	_fe3d.terrain_setRedTextureRepeat(newID, _fe3d.terrain_getRedTextureRepeat(templateID));
	_fe3d.terrain_setGreenTextureRepeat(newID, _fe3d.terrain_getGreenTextureRepeat(templateID));
	_fe3d.terrain_setBlueTextureRepeat(newID, _fe3d.terrain_getBlueTextureRepeat(templateID));
	_fe3d.terrain_setSpecular(newID, _fe3d.terrain_isSpecular(templateID));
	_fe3d.terrain_setSpecularShininess(newID, _fe3d.terrain_getSpecularShininess(templateID));
	_fe3d.terrain_setSpecularIntensity(newID, _fe3d.terrain_getSpecularIntensity(templateID));

	if(_fe3d.terrain_hasDiffuseMap(templateID))
	{
		_fe3d.terrain_setDiffuseMap(newID, _fe3d.terrain_getDiffuseMapPath(templateID));
	}

	if(_fe3d.terrain_hasNormalMap(templateID))
	{
		_fe3d.terrain_setNormalMap(newID, _fe3d.terrain_getNormalMapPath(templateID));
	}

	if(_fe3d.terrain_hasRedNormalMap(templateID))
	{
		_fe3d.terrain_setRedNormalMap(newID, _fe3d.terrain_getRedNormalMapPath(templateID));
	}

	if(_fe3d.terrain_hasGreenNormalMap(templateID))
	{
		_fe3d.terrain_setGreenNormalMap(newID, _fe3d.terrain_getGreenNormalMapPath(templateID));
	}

	if(_fe3d.terrain_hasBlueNormalMap(templateID))
	{
		_fe3d.terrain_setBlueNormalMap(newID, _fe3d.terrain_getBlueNormalMapPath(templateID));
	}

	if(_fe3d.terrain_hasBlendMap(templateID))
	{
		_fe3d.terrain_setBlendMap(newID, _fe3d.terrain_getBlendMapPath(templateID));
	}

	if(_fe3d.terrain_hasRedDiffuseMap(templateID))
	{
		_fe3d.terrain_setRedDiffuseMap(newID, _fe3d.terrain_getRedDiffuseMapPath(templateID));
	}

	if(_fe3d.terrain_hasGreenDiffuseMap(templateID))
	{
		_fe3d.terrain_setGreenDiffuseMap(newID, _fe3d.terrain_getGreenDiffuseMapPath(templateID));
	}

	if(_fe3d.terrain_hasBlueDiffuseMap(templateID))
	{
		_fe3d.terrain_setBlueDiffuseMap(newID, _fe3d.terrain_getBlueDiffuseMapPath(templateID));
	}

	_loadedTerrainID = newID;

	return true;
}

const bool WorldEditor::_copyTemplateWater(const string& newID, const string& templateID)
{
	if(_fe3d.water_isExisting(newID))
	{
		Logger::throwWarning("World water with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.water_isExisting(templateID))
	{
		Logger::throwWarning("Editor water of world water with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	if(_fe3d.water_isExisting(newID))
	{
		_fe3d.water_delete(newID);
	}

	_fe3d.water_create(newID);
	_fe3d.water_select(newID);

	_fe3d.water_setHeight(newID, _fe3d.water_getHeight(templateID));
	_fe3d.water_setSize(newID, _fe3d.water_getSize(templateID));
	_fe3d.water_setSpecular(newID, _fe3d.water_isSpecular(templateID));
	_fe3d.water_setReflective(newID, _fe3d.water_isReflective(templateID));
	_fe3d.water_setRefractive(newID, _fe3d.water_isRefractive(templateID));
	_fe3d.water_setWaveHeight(newID, _fe3d.water_getWaveHeight(templateID));
	_fe3d.water_setQuality(newID, _fe3d.water_getQuality(templateID));
	_fe3d.water_setSpecularShininess(newID, _fe3d.water_getSpecularShininess(templateID));
	_fe3d.water_setSpecularIntensity(newID, _fe3d.water_getSpecularIntensity(templateID));
	_fe3d.water_setTransparency(newID, _fe3d.water_getTransparency(templateID));
	_fe3d.water_setColor(newID, _fe3d.water_getColor(templateID));
	_fe3d.water_setTextureRepeat(newID, _fe3d.water_getTextureRepeat(templateID));
	_fe3d.water_setSpeed(newID, _fe3d.water_getSpeed(templateID));

	if(_fe3d.water_hasDudvMap(templateID))
	{
		_fe3d.water_setDudvMap(newID, _fe3d.water_getDudvMapPath(templateID));
	}

	if(_fe3d.water_hasNormalMap(templateID))
	{
		_fe3d.water_setNormalMap(newID, _fe3d.water_getNormalMapPath(templateID));
	}

	if(_fe3d.water_hasDisplacementMap(templateID))
	{
		_fe3d.water_setDisplacementMap(newID, _fe3d.water_getDisplacementMapPath(templateID));
	}

	_loadedWaterID = newID;

	return true;
}

const bool WorldEditor::_copyTemplateModel(const string& newID, const string& templateID, fvec3 position, bool isFromOutside)
{
	if(_fe3d.model_isExisting(newID))
	{
		Logger::throwWarning("Model with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.model_isExisting(templateID))
	{
		Logger::throwWarning("Editor model of model with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d.model_create(newID, _fe3d.model_getMeshPath(templateID));

	_fe3d.model_setBasePosition(newID, position);
	_fe3d.model_setBaseSize(newID, _fe3d.model_getBaseSize(templateID));
	_fe3d.model_setLevelOfDetailSize(newID, _fe3d.model_getBaseSize(templateID));
	_fe3d.model_setFrozen(newID, _fe3d.model_isFrozen(templateID));
	_fe3d.model_setLevelOfDetailEntityID(newID, _fe3d.model_getLevelOfDetailEntityID(templateID));
	_fe3d.model_setFaceCulled(newID, _fe3d.model_isFaceCulled(templateID));
	_fe3d.model_setRotationOrder(newID, _fe3d.model_getRotationOrder(templateID));

	for(const auto& partID : _fe3d.model_getPartIDs(templateID))
	{
		if(_fe3d.model_hasDiffuseMap(templateID, partID))
		{
			_fe3d.model_setDiffuseMap(newID, partID, _fe3d.model_getDiffuseMapPath(templateID, partID));
		}

		if(_fe3d.model_hasEmissionMap(templateID, partID))
		{
			_fe3d.model_setEmissionMap(newID, partID, _fe3d.model_getEmissionMapPath(templateID, partID));
		}

		if(_fe3d.model_hasSpecularMap(templateID, partID))
		{
			_fe3d.model_setSpecularMap(newID, partID, _fe3d.model_getSpecularMapPath(templateID, partID));
		}

		if(_fe3d.model_hasReflectionMap(templateID, partID))
		{
			_fe3d.model_setReflectionMap(newID, partID, _fe3d.model_getReflectionMapPath(templateID, partID));
		}

		if(_fe3d.model_hasNormalMap(templateID, partID))
		{
			_fe3d.model_setNormalMap(newID, partID, _fe3d.model_getNormalMapPath(templateID, partID));
		}

		_fe3d.model_setLightness(newID, partID, _fe3d.model_getLightness(templateID, partID));
		_fe3d.model_setSpecular(newID, partID, _fe3d.model_isSpecular(templateID, partID));
		_fe3d.model_setSpecularShininess(newID, partID, _fe3d.model_getSpecularShininess(templateID, partID));
		_fe3d.model_setSpecularIntensity(newID, partID, _fe3d.model_getSpecularIntensity(templateID, partID));
		_fe3d.model_setReflective(newID, partID, _fe3d.model_isReflective(templateID, partID));
		_fe3d.model_setReflectionType(newID, partID, _fe3d.model_getReflectionType(templateID, partID));
		_fe3d.model_setReflectivity(newID, partID, _fe3d.model_getReflectivity(templateID, partID));
		_fe3d.model_setColor(newID, partID, _fe3d.model_getColor(templateID, partID));
		_fe3d.model_setTextureRepeat(newID, partID, _fe3d.model_getTextureRepeat(templateID, partID));
	}

	for(const auto& templateAabbID : _fe3d.aabb_getChildIDs(templateID, AabbParentEntityType::MODEL))
	{
		const string newAabbID = (newID + "@" + templateAabbID.substr(string(templateID + "_").size()));
		_fe3d.aabb_create(newAabbID);
		_fe3d.aabb_setParentEntityID(newAabbID, newID);
		_fe3d.aabb_setParentEntityType(newAabbID, AabbParentEntityType::MODEL);
		_fe3d.aabb_setLocalPosition(newAabbID, _fe3d.aabb_getPosition(templateAabbID));
		_fe3d.aabb_setLocalSize(newAabbID, _fe3d.aabb_getSize(templateAabbID));
	}

	if(_isEditorLoaded)
	{
		_initialModelPosition[newID] = _fe3d.model_getBasePosition(templateID);
		_initialModelRotation[newID] = _fe3d.model_getBaseRotation(templateID);
		_initialModelSize[newID] = _fe3d.model_getBaseSize(templateID);
	}

	if(isFromOutside)
	{
		_outsideLoadedModelIDs[newID] = templateID;
	}
	else
	{
		_loadedModelIDs[newID] = templateID;
	}

	return true;
}

const bool WorldEditor::_copyTemplateBillboard(const string& newID, const string& templateID, fvec3 position, bool isFromOutside)
{
	if(_fe3d.billboard_isExisting(newID))
	{
		Logger::throwWarning("Billboard with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.billboard_isExisting(templateID))
	{
		Logger::throwWarning("Editor billboard of billboard with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d.billboard_create(newID);

	_fe3d.aabb_create(newID);
	_fe3d.aabb_setParentEntityID(newID, newID);
	_fe3d.aabb_setParentEntityType(newID, AabbParentEntityType::BILLBOARD);

	if(_fe3d.billboard_hasDiffuseMap(templateID) && !_fe3d.billboard_isTextual(templateID))
	{
		_fe3d.billboard_setDiffuseMap(newID, _fe3d.billboard_getDiffuseMapPath(templateID));
	}

	if(_fe3d.billboard_hasEmissionMap(templateID))
	{
		_fe3d.billboard_setEmissionMap(newID, _fe3d.billboard_getEmissionMapPath(templateID));
	}

	if(_fe3d.billboard_isTextual(templateID))
	{
		_fe3d.billboard_setFont(newID, _fe3d.billboard_getFontPath(templateID));
		_fe3d.billboard_setTextContent(newID, _fe3d.billboard_getTextContent(templateID));
	}

	_fe3d.billboard_setPosition(newID, position);
	_fe3d.billboard_setSize(newID, _fe3d.billboard_getSize(templateID));
	_fe3d.billboard_setFacingCameraX(newID, _fe3d.billboard_isFacingCameraX(templateID));
	_fe3d.billboard_setFacingCameraY(newID, _fe3d.billboard_isFacingCameraY(templateID));
	_fe3d.billboard_setColor(newID, _fe3d.billboard_getColor(templateID));
	_fe3d.billboard_setShadowed(newID, _fe3d.billboard_isShadowed(templateID));
	_fe3d.billboard_setReflected(newID, _fe3d.billboard_isReflected(templateID));
	_fe3d.billboard_setLightness(newID, _fe3d.billboard_getLightness(templateID));

	if(isFromOutside)
	{
		_outsideLoadedBillboardIDs[newID] = templateID;
	}
	else
	{
		_loadedBillboardIDs[newID] = templateID;
	}

	return true;
}

const bool WorldEditor::_copyTemplateSound(const string& newID, const string& templateID, fvec3 position, bool isFromOutside)
{
	if(_fe3d.sound3d_isExisting(newID))
	{
		Logger::throwWarning("sound3D with ID \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d.sound2d_isExisting(templateID))
	{
		Logger::throwWarning("sound2D with ID \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d.sound3d_create(newID, _fe3d.sound2d_getAudioPath(templateID));
	_fe3d.sound3d_setPosition(newID, position);

	if(isFromOutside)
	{
		_outsideLoadedSoundIDs[newID] = templateID;
	}
	else
	{
		_loadedSoundIDs[newID] = templateID;
	}

	return true;
}
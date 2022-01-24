#include "world_editor.hpp"
#include "logger.hpp"

void WorldEditor::copyTemplateModel(const string& newID, const string& templateID, const fvec3& position)
{
	_copyTemplateModel(newID, templateID, position, true);
}

void WorldEditor::copyTemplateQuad3d(const string& newID, const string& templateID, const fvec3& position)
{
	_copyTemplateQuad3d(newID, templateID, position, true);
}

void WorldEditor::copyTemplateText3d(const string& newID, const string& templateID, const fvec3& position)
{
	_copyTemplateText3d(newID, templateID, position, true);
}

void WorldEditor::copyTemplateSound(const string& newID, const string& templateID, const fvec3& position)
{
	_copyTemplateSound(newID, templateID, position, true);
}

const bool WorldEditor::_copyTemplateSky(const string& newID, const string& templateID)
{
	if(_fe3d->sky_isExisting(newID))
	{
		Logger::throwWarning("World sky with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->sky_isExisting(templateID))
	{
		Logger::throwWarning("Editor sky of world sky with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d->sky_create(newID);
	_fe3d->sky_setCubeMaps(newID, _fe3d->sky_getCubeMapPaths(templateID));
	_fe3d->sky_setLightness(newID, _fe3d->sky_getLightness(templateID));
	_fe3d->sky_setRotation(newID, _fe3d->sky_getRotation(templateID));
	_fe3d->sky_setColor(newID, _fe3d->sky_getColor(templateID));
	_fe3d->sky_select(newID);

	_loadedSkyId = newID;

	return true;
}

const bool WorldEditor::_copyTemplateTerrain(const string& newID, const string& templateID)
{
	if(_fe3d->terrain_isExisting(newID))
	{
		Logger::throwWarning("World terrain with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->terrain_isExisting(templateID))
	{
		Logger::throwWarning("Editor terrain of world terrain with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	if(_fe3d->terrain_isExisting(newID))
	{
		_fe3d->terrain_delete(newID);
	}

	_fe3d->terrain_create(newID, _fe3d->terrain_getHeightMapPath(templateID));
	_fe3d->terrain_select(newID);

	_fe3d->terrain_setMaxHeight(newID, _fe3d->terrain_getMaxHeight(templateID));
	_fe3d->terrain_setTextureRepeat(newID, _fe3d->terrain_getTextureRepeat(templateID));
	_fe3d->terrain_setLightness(newID, _fe3d->terrain_getLightness(templateID));
	_fe3d->terrain_setRedTextureRepeat(newID, _fe3d->terrain_getRedTextureRepeat(templateID));
	_fe3d->terrain_setGreenTextureRepeat(newID, _fe3d->terrain_getGreenTextureRepeat(templateID));
	_fe3d->terrain_setBlueTextureRepeat(newID, _fe3d->terrain_getBlueTextureRepeat(templateID));
	_fe3d->terrain_setSpecular(newID, _fe3d->terrain_isSpecular(templateID));
	_fe3d->terrain_setSpecularShininess(newID, _fe3d->terrain_getSpecularShininess(templateID));
	_fe3d->terrain_setSpecularIntensity(newID, _fe3d->terrain_getSpecularIntensity(templateID));

	if(_fe3d->terrain_hasDiffuseMap(templateID))
	{
		_fe3d->terrain_setDiffuseMap(newID, _fe3d->terrain_getDiffuseMapPath(templateID));
	}

	if(_fe3d->terrain_hasNormalMap(templateID))
	{
		_fe3d->terrain_setNormalMap(newID, _fe3d->terrain_getNormalMapPath(templateID));
	}

	if(_fe3d->terrain_hasRedNormalMap(templateID))
	{
		_fe3d->terrain_setRedNormalMap(newID, _fe3d->terrain_getRedNormalMapPath(templateID));
	}

	if(_fe3d->terrain_hasGreenNormalMap(templateID))
	{
		_fe3d->terrain_setGreenNormalMap(newID, _fe3d->terrain_getGreenNormalMapPath(templateID));
	}

	if(_fe3d->terrain_hasBlueNormalMap(templateID))
	{
		_fe3d->terrain_setBlueNormalMap(newID, _fe3d->terrain_getBlueNormalMapPath(templateID));
	}

	if(_fe3d->terrain_hasBlendMap(templateID))
	{
		_fe3d->terrain_setBlendMap(newID, _fe3d->terrain_getBlendMapPath(templateID));
	}

	if(_fe3d->terrain_hasRedDiffuseMap(templateID))
	{
		_fe3d->terrain_setRedDiffuseMap(newID, _fe3d->terrain_getRedDiffuseMapPath(templateID));
	}

	if(_fe3d->terrain_hasGreenDiffuseMap(templateID))
	{
		_fe3d->terrain_setGreenDiffuseMap(newID, _fe3d->terrain_getGreenDiffuseMapPath(templateID));
	}

	if(_fe3d->terrain_hasBlueDiffuseMap(templateID))
	{
		_fe3d->terrain_setBlueDiffuseMap(newID, _fe3d->terrain_getBlueDiffuseMapPath(templateID));
	}

	_loadedTerrainId = newID;

	return true;
}

const bool WorldEditor::_copyTemplateWater(const string& newID, const string& templateID)
{
	if(_fe3d->water_isExisting(newID))
	{
		Logger::throwWarning("World water with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->water_isExisting(templateID))
	{
		Logger::throwWarning("Editor water of world water with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	if(_fe3d->water_isExisting(newID))
	{
		_fe3d->water_delete(newID);
	}

	_fe3d->water_create(newID);
	_fe3d->water_select(newID);

	_fe3d->water_setHeight(newID, _fe3d->water_getHeight(templateID));
	_fe3d->water_setSize(newID, _fe3d->water_getSize(templateID));
	_fe3d->water_setSpecular(newID, _fe3d->water_isSpecular(templateID));
	_fe3d->water_setReflective(newID, _fe3d->water_isReflective(templateID));
	_fe3d->water_setRefractive(newID, _fe3d->water_isRefractive(templateID));
	_fe3d->water_setWaveHeight(newID, _fe3d->water_getWaveHeight(templateID));
	_fe3d->water_setQuality(newID, _fe3d->water_getQuality(templateID));
	_fe3d->water_setSpecularShininess(newID, _fe3d->water_getSpecularShininess(templateID));
	_fe3d->water_setSpecularIntensity(newID, _fe3d->water_getSpecularIntensity(templateID));
	_fe3d->water_setOpacity(newID, _fe3d->water_getOpacity(templateID));
	_fe3d->water_setColor(newID, _fe3d->water_getColor(templateID));
	_fe3d->water_setTextureRepeat(newID, _fe3d->water_getTextureRepeat(templateID));
	_fe3d->water_setSpeed(newID, _fe3d->water_getSpeed(templateID));

	if(_fe3d->water_hasDudvMap(templateID))
	{
		_fe3d->water_setDudvMap(newID, _fe3d->water_getDudvMapPath(templateID));
	}

	if(_fe3d->water_hasNormalMap(templateID))
	{
		_fe3d->water_setNormalMap(newID, _fe3d->water_getNormalMapPath(templateID));
	}

	if(_fe3d->water_hasDisplacementMap(templateID))
	{
		_fe3d->water_setDisplacementMap(newID, _fe3d->water_getDisplacementMapPath(templateID));
	}

	_loadedWaterId = newID;

	return true;
}

const bool WorldEditor::_copyTemplateModel(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->model_isExisting(newID))
	{
		Logger::throwWarning("Model with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->model_isExisting(templateID))
	{
		Logger::throwWarning("Editor model of model with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d->model_create(newID, _fe3d->model_getMeshPath(templateID));

	_fe3d->model_setBasePosition(newID, position);
	_fe3d->model_setBaseSize(newID, _fe3d->model_getBaseSize(templateID));
	_fe3d->model_setLevelOfDetailSize(newID, _fe3d->model_getBaseSize(templateID));
	_fe3d->model_setFrozen(newID, _fe3d->model_isFrozen(templateID));
	_fe3d->model_setLevelOfDetailEntityId(newID, _fe3d->model_getLevelOfDetailEntityId(templateID));
	_fe3d->model_setRotationOrder(newID, _fe3d->model_getRotationOrder(templateID));

	for(const auto& partId : _fe3d->model_getPartIds(templateID))
	{
		if(_fe3d->model_hasDiffuseMap(templateID, partId))
		{
			_fe3d->model_setDiffuseMap(newID, partId, _fe3d->model_getDiffuseMapPath(templateID, partId));
		}

		if(_fe3d->model_hasEmissionMap(templateID, partId))
		{
			_fe3d->model_setEmissionMap(newID, partId, _fe3d->model_getEmissionMapPath(templateID, partId));
		}

		if(_fe3d->model_hasSpecularMap(templateID, partId))
		{
			_fe3d->model_setSpecularMap(newID, partId, _fe3d->model_getSpecularMapPath(templateID, partId));
		}

		if(_fe3d->model_hasReflectionMap(templateID, partId))
		{
			_fe3d->model_setReflectionMap(newID, partId, _fe3d->model_getReflectionMapPath(templateID, partId));
		}

		if(_fe3d->model_hasNormalMap(templateID, partId))
		{
			_fe3d->model_setNormalMap(newID, partId, _fe3d->model_getNormalMapPath(templateID, partId));
		}

		_fe3d->model_setLightness(newID, partId, _fe3d->model_getLightness(templateID, partId));
		_fe3d->model_setSpecular(newID, partId, _fe3d->model_isSpecular(templateID, partId));
		_fe3d->model_setSpecularShininess(newID, partId, _fe3d->model_getSpecularShininess(templateID, partId));
		_fe3d->model_setSpecularIntensity(newID, partId, _fe3d->model_getSpecularIntensity(templateID, partId));
		_fe3d->model_setReflective(newID, partId, _fe3d->model_isReflective(templateID, partId));
		_fe3d->model_setReflectionType(newID, partId, _fe3d->model_getReflectionType(templateID, partId));
		_fe3d->model_setReflectivity(newID, partId, _fe3d->model_getReflectivity(templateID, partId));
		_fe3d->model_setColor(newID, partId, _fe3d->model_getColor(templateID, partId));
		_fe3d->model_setTextureRepeat(newID, partId, _fe3d->model_getTextureRepeat(templateID, partId));
		_fe3d->model_setFaceCulled(newID, partId, _fe3d->model_isFaceCulled(templateID, partId));
	}

	for(const auto& templateAabbId : _fe3d->aabb_getChildIds(templateID, AabbParentEntityType::MODEL))
	{
		const string newAabbId = (newID + "@" + templateAabbId.substr(string(templateID + "_").size()));
		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setParentEntityId(newAabbId, newID);
		_fe3d->aabb_setParentEntityType(newAabbId, AabbParentEntityType::MODEL);
		_fe3d->aabb_setLocalPosition(newAabbId, _fe3d->aabb_getPosition(templateAabbId));
		_fe3d->aabb_setLocalSize(newAabbId, _fe3d->aabb_getSize(templateAabbId));
	}

	if(_isEditorLoaded)
	{
		_initialModelPosition.insert(make_pair(newID, _fe3d->model_getBasePosition(templateID)));
		_initialModelRotation.insert(make_pair(newID, _fe3d->model_getBaseRotation(templateID)));
		_initialModelSize.insert(make_pair(newID, _fe3d->model_getBaseSize(templateID)));
	}

	if(isFromOutside)
	{
		_outsideLoadedModelIds.insert(make_pair(newID, templateID));
	}
	else
	{
		_loadedModelIds.insert(make_pair(newID, templateID));
	}

	return true;
}

const bool WorldEditor::_copyTemplateQuad3d(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->quad3d_isExisting(newID))
	{
		Logger::throwWarning("Quad3d with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->quad3d_isExisting(templateID))
	{
		Logger::throwWarning("Editor quad3d of quad3d with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d->quad3d_create(newID, false);

	_fe3d->aabb_create(newID, false);
	_fe3d->aabb_setParentEntityId(newID, newID);
	_fe3d->aabb_setParentEntityType(newID, AabbParentEntityType::QUAD3D);

	if(_fe3d->quad3d_hasDiffuseMap(templateID))
	{
		_fe3d->quad3d_setDiffuseMap(newID, _fe3d->quad3d_getDiffuseMapPath(templateID));
	}

	if(_fe3d->quad3d_hasEmissionMap(templateID))
	{
		_fe3d->quad3d_setEmissionMap(newID, _fe3d->quad3d_getEmissionMapPath(templateID));
	}

	_fe3d->quad3d_setPosition(newID, position);
	_fe3d->quad3d_setSize(newID, _fe3d->quad3d_getSize(templateID));
	_fe3d->quad3d_setFacingCameraX(newID, _fe3d->quad3d_isFacingCameraX(templateID));
	_fe3d->quad3d_setFacingCameraY(newID, _fe3d->quad3d_isFacingCameraY(templateID));
	_fe3d->quad3d_setColor(newID, _fe3d->quad3d_getColor(templateID));
	_fe3d->quad3d_setShadowed(newID, _fe3d->quad3d_isShadowed(templateID));
	_fe3d->quad3d_setReflected(newID, _fe3d->quad3d_isReflected(templateID));
	_fe3d->quad3d_setLightness(newID, _fe3d->quad3d_getLightness(templateID));

	if(isFromOutside)
	{
		_outsideLoadedQuadIds.insert(make_pair(newID, templateID));
	}
	else
	{
		_loadedQuadIds.insert(make_pair(newID, templateID));
	}

	return true;
}

const bool WorldEditor::_copyTemplateText3d(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->text3d_isExisting(newID))
	{
		Logger::throwWarning("Text3d with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->text3d_isExisting(templateID))
	{
		Logger::throwWarning("Editor text3d of text3d with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d->text3d_create(newID, _fe3d->text3d_getFontMapPath(templateID), false);

	_fe3d->aabb_create(newID, false);
	_fe3d->aabb_setParentEntityId(newID, newID);
	_fe3d->aabb_setParentEntityType(newID, AabbParentEntityType::TEXT3D);

	_fe3d->text3d_setPosition(newID, position);
	_fe3d->text3d_setSize(newID, _fe3d->text3d_getSize(templateID));
	_fe3d->text3d_setFacingCameraX(newID, _fe3d->text3d_isFacingCameraX(templateID));
	_fe3d->text3d_setFacingCameraY(newID, _fe3d->text3d_isFacingCameraY(templateID));
	_fe3d->text3d_setColor(newID, _fe3d->text3d_getColor(templateID));
	_fe3d->text3d_setShadowed(newID, _fe3d->text3d_isShadowed(templateID));
	_fe3d->text3d_setReflected(newID, _fe3d->text3d_isReflected(templateID));
	_fe3d->text3d_setLightness(newID, _fe3d->text3d_getLightness(templateID));
	_fe3d->text3d_setContent(newID, _fe3d->text3d_getContent(templateID));

	if(isFromOutside)
	{
		_outsideLoadedTextIds.insert(make_pair(newID, templateID));
	}
	else
	{
		_loadedTextIds.insert(make_pair(newID, templateID));
	}

	return true;
}

const bool WorldEditor::_copyTemplateSound(const string& newID, const string& templateID, const fvec3& position, bool isFromOutside)
{
	if(_fe3d->sound3d_isExisting(newID))
	{
		Logger::throwWarning("sound3D with id \"" + newID + "\" already exists!");
		return false;
	}
	if(!_fe3d->sound2d_isExisting(templateID))
	{
		Logger::throwWarning("sound2D with id \"" + newID + "\" not existing anymore!");
		return false;
	}

	_fe3d->sound3d_create(newID, _fe3d->sound2d_getAudioPath(templateID));
	_fe3d->sound3d_setPosition(newID, position);

	if(isFromOutside)
	{
		_outsideLoadedSoundIds.insert(make_pair(newID, templateID));
	}
	else
	{
		_loadedSoundIds.insert(make_pair(newID, templateID));
	}

	return true;
}
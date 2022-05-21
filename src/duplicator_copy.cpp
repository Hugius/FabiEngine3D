#include "duplicator.hpp"

void Duplicator::copyTemplateSky(const string & newId, const string & templateId)
{
	if(!_fe3d->sky_isExisting(templateId))
	{
		abort();
	}

	_fe3d->sky_create(newId);
	_fe3d->sky_select(newId);
	_fe3d->sky_setCubeMaps(newId, _fe3d->sky_getCubeMapPaths(templateId));
	_fe3d->sky_setLightness(newId, _fe3d->sky_getLightness(templateId));
	_fe3d->sky_setRotation(newId, _fe3d->sky_getRotation(templateId));
	_fe3d->sky_setColor(newId, _fe3d->sky_getColor(templateId));
	_fe3d->sky_setRotationOrder(newId, _fe3d->sky_getRotationOrder(templateId));

	_copiedSkyIds.insert({newId, templateId});
}

void Duplicator::copyTemplateTerrain(const string & newId, const string & templateId)
{
	if(!_fe3d->terrain_isExisting(templateId))
	{
		abort();
	}

	_fe3d->terrain_create(newId, _fe3d->terrain_getHeightMapPath(templateId));
	_fe3d->terrain_select(newId);
	_fe3d->terrain_setMaxHeight(newId, _fe3d->terrain_getMaxHeight(templateId));
	_fe3d->terrain_setTextureRepeat(newId, _fe3d->terrain_getTextureRepeat(templateId));
	_fe3d->terrain_setLightness(newId, _fe3d->terrain_getLightness(templateId));
	_fe3d->terrain_setColor(newId, _fe3d->terrain_getColor(templateId));
	_fe3d->terrain_setRedTextureRepeat(newId, _fe3d->terrain_getRedTextureRepeat(templateId));
	_fe3d->terrain_setGreenTextureRepeat(newId, _fe3d->terrain_getGreenTextureRepeat(templateId));
	_fe3d->terrain_setBlueTextureRepeat(newId, _fe3d->terrain_getBlueTextureRepeat(templateId));
	_fe3d->terrain_setSpecular(newId, _fe3d->terrain_isSpecular(templateId));
	_fe3d->terrain_setSpecularShininess(newId, _fe3d->terrain_getSpecularShininess(templateId));
	_fe3d->terrain_setSpecularIntensity(newId, _fe3d->terrain_getSpecularIntensity(templateId));

	if(_fe3d->terrain_hasDiffuseMap(templateId))
	{
		_fe3d->terrain_setDiffuseMap(newId, _fe3d->terrain_getDiffuseMapPath(templateId));
	}

	if(_fe3d->terrain_hasNormalMap(templateId))
	{
		_fe3d->terrain_setNormalMap(newId, _fe3d->terrain_getNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasRedNormalMap(templateId))
	{
		_fe3d->terrain_setRedNormalMap(newId, _fe3d->terrain_getRedNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasGreenNormalMap(templateId))
	{
		_fe3d->terrain_setGreenNormalMap(newId, _fe3d->terrain_getGreenNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasBlueNormalMap(templateId))
	{
		_fe3d->terrain_setBlueNormalMap(newId, _fe3d->terrain_getBlueNormalMapPath(templateId));
	}

	if(_fe3d->terrain_hasBlendMap(templateId))
	{
		_fe3d->terrain_setBlendMap(newId, _fe3d->terrain_getBlendMapPath(templateId));
	}

	if(_fe3d->terrain_hasRedDiffuseMap(templateId))
	{
		_fe3d->terrain_setRedDiffuseMap(newId, _fe3d->terrain_getRedDiffuseMapPath(templateId));
	}

	if(_fe3d->terrain_hasGreenDiffuseMap(templateId))
	{
		_fe3d->terrain_setGreenDiffuseMap(newId, _fe3d->terrain_getGreenDiffuseMapPath(templateId));
	}

	if(_fe3d->terrain_hasBlueDiffuseMap(templateId))
	{
		_fe3d->terrain_setBlueDiffuseMap(newId, _fe3d->terrain_getBlueDiffuseMapPath(templateId));
	}

	_copiedTerrainIds.insert({newId, templateId});
}

void Duplicator::copyTemplateWater(const string & newId, const string & templateId)
{
	if(!_fe3d->water_isExisting(templateId))
	{
		abort();
	}

	_fe3d->water_create(newId);
	_fe3d->water_select(newId);
	_fe3d->water_setHeight(newId, _fe3d->water_getHeight(templateId));
	_fe3d->water_setSize(newId, _fe3d->water_getSize(templateId));
	_fe3d->water_setSpecular(newId, _fe3d->water_isSpecular(templateId));
	_fe3d->water_setReflective(newId, _fe3d->water_isReflective(templateId));
	_fe3d->water_setRefractive(newId, _fe3d->water_isRefractive(templateId));
	_fe3d->water_setWaveHeight(newId, _fe3d->water_getWaveHeight(templateId));
	_fe3d->water_setSpecularShininess(newId, _fe3d->water_getSpecularShininess(templateId));
	_fe3d->water_setSpecularIntensity(newId, _fe3d->water_getSpecularIntensity(templateId));
	_fe3d->water_setEdged(newId, _fe3d->water_isEdged(templateId));
	_fe3d->water_setColor(newId, _fe3d->water_getColor(templateId));
	_fe3d->water_setTextureRepeat(newId, _fe3d->water_getTextureRepeat(templateId));
	_fe3d->water_setRippleSpeed(newId, _fe3d->water_getRippleSpeed(templateId));
	_fe3d->water_setWaveSpeed(newId, _fe3d->water_getWaveSpeed(templateId));
	_fe3d->water_setMaxDepth(newId, _fe3d->water_getMaxDepth(templateId));

	if(_fe3d->water_hasDudvMap(templateId))
	{
		_fe3d->water_setDudvMap(newId, _fe3d->water_getDudvMapPath(templateId));
	}

	if(_fe3d->water_hasNormalMap(templateId))
	{
		_fe3d->water_setNormalMap(newId, _fe3d->water_getNormalMapPath(templateId));
	}

	if(_fe3d->water_hasHeightMap(templateId))
	{
		_fe3d->water_setHeightMap(newId, _fe3d->water_getHeightMapPath(templateId));
	}

	_copiedWaterIds.insert({newId, templateId});
}

void Duplicator::copyTemplateModel(const string & newId, const string & templateId)
{
	if(!_fe3d->model_isExisting(templateId))
	{
		abort();
	}

	_fe3d->model_create(newId, _fe3d->model_getMeshPath(templateId));
	_fe3d->model_setBaseSize(newId, _fe3d->model_getBaseSize(templateId));
	_fe3d->model_setShadowed(newId, _fe3d->model_isShadowed(templateId));
	_fe3d->model_setReflected(newId, _fe3d->model_isReflected(templateId));
	_fe3d->model_setRefracted(newId, _fe3d->model_isRefracted(templateId));
	_fe3d->model_setLevelOfDetailId(newId, _fe3d->model_getLevelOfDetailId(templateId));
	_fe3d->model_setLevelOfDetailDistance(newId, _fe3d->model_getLevelOfDetailDistance(templateId));
	_fe3d->model_setRotationOrder(newId, _fe3d->model_getRotationOrder(templateId));

	for(const auto & partId : _fe3d->model_getPartIds(templateId))
	{
		_fe3d->model_setLightness(newId, partId, _fe3d->model_getLightness(templateId, partId));
		_fe3d->model_setBright(newId, partId, _fe3d->model_isBright(templateId, partId));
		_fe3d->model_setEmissionIntensity(newId, partId, _fe3d->model_getEmissionIntensity(templateId, partId));
		_fe3d->model_setSpecular(newId, partId, _fe3d->model_isSpecular(templateId, partId));
		_fe3d->model_setSpecularShininess(newId, partId, _fe3d->model_getSpecularShininess(templateId, partId));
		_fe3d->model_setSpecularIntensity(newId, partId, _fe3d->model_getSpecularIntensity(templateId, partId));
		_fe3d->model_setReflective(newId, partId, _fe3d->model_isReflective(templateId, partId));
		_fe3d->model_setRefractive(newId, partId, _fe3d->model_isRefractive(templateId, partId));
		_fe3d->model_setReflectionType(newId, partId, _fe3d->model_getReflectionType(templateId, partId));
		_fe3d->model_setRefractionType(newId, partId, _fe3d->model_getRefractionType(templateId, partId));
		_fe3d->model_setReflectivity(newId, partId, _fe3d->model_getReflectivity(templateId, partId));
		_fe3d->model_setRefractivity(newId, partId, _fe3d->model_getRefractivity(templateId, partId));
		_fe3d->model_setColor(newId, partId, _fe3d->model_getColor(templateId, partId));
		_fe3d->model_setTextureRepeat(newId, partId, _fe3d->model_getTextureRepeat(templateId, partId));
		_fe3d->model_setFaceCulled(newId, partId, _fe3d->model_isFaceCulled(templateId, partId));
		_fe3d->model_setMinAlpha(newId, partId, _fe3d->model_getMinAlpha(templateId, partId));
		_fe3d->model_setOpacity(newId, partId, _fe3d->model_getOpacity(templateId, partId));

		if(_fe3d->model_hasDiffuseMap(templateId, partId))
		{
			_fe3d->model_setDiffuseMap(newId, partId, _fe3d->model_getDiffuseMapPath(templateId, partId));
		}

		if(_fe3d->model_hasEmissionMap(templateId, partId))
		{
			_fe3d->model_setEmissionMap(newId, partId, _fe3d->model_getEmissionMapPath(templateId, partId));
		}

		if(_fe3d->model_hasSpecularMap(templateId, partId))
		{
			_fe3d->model_setSpecularMap(newId, partId, _fe3d->model_getSpecularMapPath(templateId, partId));
		}

		if(_fe3d->model_hasReflectionMap(templateId, partId))
		{
			_fe3d->model_setReflectionMap(newId, partId, _fe3d->model_getReflectionMapPath(templateId, partId));
		}

		if(_fe3d->model_hasRefractionMap(templateId, partId))
		{
			_fe3d->model_setRefractionMap(newId, partId, _fe3d->model_getRefractionMapPath(templateId, partId));
		}

		if(_fe3d->model_hasNormalMap(templateId, partId))
		{
			_fe3d->model_setNormalMap(newId, partId, _fe3d->model_getNormalMapPath(templateId, partId));
		}
	}

	for(const auto & templateAabbId : _fe3d->model_getChildAabbIds(templateId))
	{
		const auto newAabbId = ("model@" + newId + "@" + templateAabbId.substr(("model@" + templateId + "@").size()));

		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setVisible(newAabbId, false);
		_fe3d->aabb_setParentId(newAabbId, newId);
		_fe3d->aabb_setParentType(newAabbId, AabbParentType::MODEL);
		_fe3d->aabb_setLocalPosition(newAabbId, _fe3d->aabb_getLocalPosition(templateAabbId));
		_fe3d->aabb_setLocalSize(newAabbId, _fe3d->aabb_getLocalSize(templateAabbId));
	}

	_copiedModelIds.insert({newId, templateId});
}

void Duplicator::copyTemplateQuad3d(const string & newId, const string & templateId)
{
	if(!_fe3d->quad3d_isExisting(templateId))
	{
		abort();
	}

	_fe3d->quad3d_create(newId, false);
	_fe3d->quad3d_setSize(newId, _fe3d->quad3d_getSize(templateId));
	_fe3d->quad3d_setFacingCameraHorizontally(newId, _fe3d->quad3d_isFacingCameraHorizontally(templateId));
	_fe3d->quad3d_setFacingCameraVertically(newId, _fe3d->quad3d_isFacingCameraVertically(templateId));
	_fe3d->quad3d_setHorizontallyFlipped(newId, _fe3d->quad3d_isHorizontallyFlipped(templateId));
	_fe3d->quad3d_setVerticallyFlipped(newId, _fe3d->quad3d_isVerticallyFlipped(templateId));
	_fe3d->quad3d_setColor(newId, _fe3d->quad3d_getColor(templateId));
	_fe3d->quad3d_setBright(newId, _fe3d->quad3d_isBright(templateId));
	_fe3d->quad3d_setTextureRepeat(newId, _fe3d->quad3d_getTextureRepeat(templateId));
	_fe3d->quad3d_setShadowed(newId, _fe3d->quad3d_isShadowed(templateId));
	_fe3d->quad3d_setReflected(newId, _fe3d->quad3d_isReflected(templateId));
	_fe3d->quad3d_setRefracted(newId, _fe3d->quad3d_isRefracted(templateId));
	_fe3d->quad3d_setEmissionIntensity(newId, _fe3d->quad3d_getEmissionIntensity(templateId));
	_fe3d->quad3d_setLightness(newId, _fe3d->quad3d_getLightness(templateId));
	_fe3d->quad3d_setOpacity(newId, _fe3d->quad3d_getOpacity(templateId));
	_fe3d->quad3d_setMinAlpha(newId, _fe3d->quad3d_getMinAlpha(templateId));
	_fe3d->quad3d_setRotationOrder(newId, _fe3d->quad3d_getRotationOrder(templateId));

	if(_fe3d->quad3d_hasDiffuseMap(templateId))
	{
		_fe3d->quad3d_setDiffuseMap(newId, _fe3d->quad3d_getDiffuseMapPath(templateId));
	}

	if(_fe3d->quad3d_hasEmissionMap(templateId))
	{
		_fe3d->quad3d_setEmissionMap(newId, _fe3d->quad3d_getEmissionMapPath(templateId));
	}

	if(_fe3d->aabb_isExisting(templateId))
	{
		const auto newAabbId = ("quad3d@" + newId);

		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setVisible(newAabbId, false);
		_fe3d->aabb_setParentId(newAabbId, newId);
		_fe3d->aabb_setParentType(newAabbId, AabbParentType::QUAD3D);
	}

	_copiedQuad3dIds.insert({newId, templateId});
}

void Duplicator::copyTemplateQuad2d(const string & newId, const string & templateId)
{
	if(!_fe3d->quad2d_isExisting(templateId))
	{
		abort();
	}

	_fe3d->quad2d_create(newId, true);
	_fe3d->quad2d_setSize(newId, _fe3d->quad2d_getSize(templateId));
	_fe3d->quad2d_setHorizontallyFlipped(newId, _fe3d->quad2d_isHorizontallyFlipped(templateId));
	_fe3d->quad2d_setVerticallyFlipped(newId, _fe3d->quad2d_isVerticallyFlipped(templateId));
	_fe3d->quad2d_setColor(newId, _fe3d->quad2d_getColor(templateId));
	_fe3d->quad2d_setTextureRepeat(newId, _fe3d->quad2d_getTextureRepeat(templateId));
	_fe3d->quad2d_setOpacity(newId, _fe3d->quad2d_getOpacity(templateId));

	if(_fe3d->quad2d_hasDiffuseMap(templateId))
	{
		_fe3d->quad2d_setDiffuseMap(newId, _fe3d->quad2d_getDiffuseMapPath(templateId));
	}

	_copiedQuad2dIds.insert({newId, templateId});
}

void Duplicator::copyTemplateText3d(const string & newId, const string & templateId)
{
	if(!_fe3d->text3d_isExisting(templateId))
	{
		abort();
	}

	_fe3d->text3d_create(newId, _fe3d->text3d_getFontMapPath(templateId), false);
	_fe3d->text3d_setSize(newId, _fe3d->text3d_getSize(templateId));
	_fe3d->text3d_setFacingCameraHorizontally(newId, _fe3d->text3d_isFacingCameraHorizontally(templateId));
	_fe3d->text3d_setFacingCameraVertically(newId, _fe3d->text3d_isFacingCameraVertically(templateId));
	_fe3d->text3d_setHorizontallyFlipped(newId, _fe3d->text3d_isHorizontallyFlipped(templateId));
	_fe3d->text3d_setVerticallyFlipped(newId, _fe3d->text3d_isVerticallyFlipped(templateId));
	_fe3d->text3d_setColor(newId, _fe3d->text3d_getColor(templateId));
	_fe3d->text3d_setShadowed(newId, _fe3d->text3d_isShadowed(templateId));
	_fe3d->text3d_setReflected(newId, _fe3d->text3d_isReflected(templateId));
	_fe3d->text3d_setRefracted(newId, _fe3d->text3d_isRefracted(templateId));
	_fe3d->text3d_setLightness(newId, _fe3d->text3d_getLightness(templateId));
	_fe3d->text3d_setBright(newId, _fe3d->text3d_isBright(templateId));
	_fe3d->text3d_setOpacity(newId, _fe3d->text3d_getOpacity(templateId));
	_fe3d->text3d_setContent(newId, _fe3d->text3d_getContent(templateId));
	_fe3d->text3d_setMinAlpha(newId, _fe3d->text3d_getMinAlpha(templateId));
	_fe3d->text3d_setRotationOrder(newId, _fe3d->text3d_getRotationOrder(templateId));

	if(_fe3d->aabb_isExisting(templateId))
	{
		const auto newAabbId = ("text3d@" + newId);

		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setVisible(newAabbId, false);
		_fe3d->aabb_setParentId(newAabbId, newId);
		_fe3d->aabb_setParentType(newAabbId, AabbParentType::TEXT3D);
	}

	_copiedText3dIds.insert({newId, templateId});
}

void Duplicator::copyTemplateText2d(const string & newId, const string & templateId)
{
	if(!_fe3d->text2d_isExisting(templateId))
	{
		abort();
	}

	_fe3d->text2d_create(newId, _fe3d->text2d_getFontMapPath(templateId), true);
	_fe3d->text2d_setSize(newId, _fe3d->text2d_getSize(templateId));
	_fe3d->text2d_setHorizontallyFlipped(newId, _fe3d->text2d_isHorizontallyFlipped(templateId));
	_fe3d->text2d_setVerticallyFlipped(newId, _fe3d->text2d_isVerticallyFlipped(templateId));
	_fe3d->text2d_setColor(newId, _fe3d->text2d_getColor(templateId));
	_fe3d->text2d_setOpacity(newId, _fe3d->text2d_getOpacity(templateId));
	_fe3d->text2d_setContent(newId, _fe3d->text2d_getContent(templateId));

	_copiedText2dIds.insert({newId, templateId});
}

void Duplicator::copyTemplateAabb(const string & newId, const string & templateId)
{
	if(!_fe3d->aabb_isExisting(templateId))
	{
		abort();
	}

	_fe3d->aabb_create(newId, false);
	_fe3d->aabb_setBaseSize(newId, _fe3d->aabb_getBaseSize(templateId));
	_fe3d->aabb_setColor(newId, _fe3d->aabb_getColor(templateId));

	_copiedAabbIds.insert({newId, templateId});
}

void Duplicator::copyTemplatePointlight(const string & newId, const string & templateId)
{
	if(!_fe3d->pointlight_isExisting(templateId))
	{
		abort();
	}

	_fe3d->pointlight_create(newId);
	_fe3d->pointlight_setRadius(newId, _fe3d->pointlight_getRadius(templateId));
	_fe3d->pointlight_setColor(newId, _fe3d->pointlight_getColor(templateId));
	_fe3d->pointlight_setIntensity(newId, _fe3d->pointlight_getIntensity(templateId));
	_fe3d->pointlight_setShape(newId, _fe3d->pointlight_getShape(templateId));

	_copiedPointlightIds.insert({newId, templateId});
}

void Duplicator::copyTemplateSpotlight(const string & newId, const string & templateId)
{
	if(!_fe3d->spotlight_isExisting(templateId))
	{
		abort();
	}

	_fe3d->spotlight_create(newId);
	_fe3d->spotlight_setColor(newId, _fe3d->spotlight_getColor(templateId));
	_fe3d->spotlight_setYaw(newId, _fe3d->spotlight_getYaw(templateId));
	_fe3d->spotlight_setPitch(newId, _fe3d->spotlight_getPitch(templateId));
	_fe3d->spotlight_setIntensity(newId, _fe3d->spotlight_getIntensity(templateId));
	_fe3d->spotlight_setAngle(newId, _fe3d->spotlight_getAngle(templateId));
	_fe3d->spotlight_setDistance(newId, _fe3d->spotlight_getDistance(templateId));

	_copiedSpotlightIds.insert({newId, templateId});
}

void Duplicator::copyTemplateCaptor(const string & newId, const string & templateId)
{
	if(!_fe3d->captor_isExisting(templateId))
	{
		abort();
	}

	_fe3d->captor_create(newId);
	_fe3d->captor_setReflectionQuality(newId, _fe3d->captor_getReflectionQuality(templateId));
	_fe3d->captor_setRefractionQuality(newId, _fe3d->captor_getRefractionQuality(templateId));

	_copiedCaptorIds.insert({newId, templateId});
}

void Duplicator::copyTemplateSound3d(const string & newId, const string & templateId)
{
	if(!_fe3d->sound3d_isExisting(templateId))
	{
		abort();
	}

	_fe3d->sound3d_create(newId, _fe3d->sound3d_getAudioPath(templateId));
	_fe3d->sound3d_setMaxVolume(newId, _fe3d->sound3d_getMaxVolume(templateId));
	_fe3d->sound3d_setMaxDistance(newId, _fe3d->sound3d_getMaxDistance(templateId));

	_copiedSound3dIds.insert({newId, templateId});
}

void Duplicator::copyTemplateSound2d(const string & newId, const string & templateId)
{
	if(!_fe3d->sound2d_isExisting(templateId))
	{
		abort();
	}

	_fe3d->sound2d_create(newId, _fe3d->sound2d_getAudioPath(templateId));

	_copiedSound2dIds.insert({newId, templateId});
}
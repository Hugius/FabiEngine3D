#include "duplicator.hpp"

void Duplicator::copyEditorSky(const string & newId, const string & editorId)
{
	if(!_fe3d->sky_isExisting(editorId))
	{
		abort();
	}

	_fe3d->sky_create(newId);
	_fe3d->sky_select(newId);
	_fe3d->sky_setCubeMaps(newId, _fe3d->sky_getCubeMapPaths(editorId));
	_fe3d->sky_setLightness(newId, _fe3d->sky_getLightness(editorId));
	_fe3d->sky_setRotation(newId, _fe3d->sky_getRotation(editorId));
	_fe3d->sky_setColor(newId, _fe3d->sky_getColor(editorId));
	_fe3d->sky_setRotationOrder(newId, _fe3d->sky_getRotationOrder(editorId));

	_copiedSkyIds.insert({newId, editorId});
}

void Duplicator::copyEditorTerrain(const string & newId, const string & editorId)
{
	if(!_fe3d->terrain_isExisting(editorId))
	{
		abort();
	}

	_fe3d->terrain_create(newId, _fe3d->terrain_getHeightMapPath(editorId));
	_fe3d->terrain_select(newId);
	_fe3d->terrain_setMaxHeight(newId, _fe3d->terrain_getMaxHeight(editorId));
	_fe3d->terrain_setTextureRepeat(newId, _fe3d->terrain_getTextureRepeat(editorId));
	_fe3d->terrain_setLightness(newId, _fe3d->terrain_getLightness(editorId));
	_fe3d->terrain_setColor(newId, _fe3d->terrain_getColor(editorId));
	_fe3d->terrain_setRedTextureRepeat(newId, _fe3d->terrain_getRedTextureRepeat(editorId));
	_fe3d->terrain_setGreenTextureRepeat(newId, _fe3d->terrain_getGreenTextureRepeat(editorId));
	_fe3d->terrain_setBlueTextureRepeat(newId, _fe3d->terrain_getBlueTextureRepeat(editorId));
	_fe3d->terrain_setSpecular(newId, _fe3d->terrain_isSpecular(editorId));
	_fe3d->terrain_setSpecularShininess(newId, _fe3d->terrain_getSpecularShininess(editorId));
	_fe3d->terrain_setSpecularIntensity(newId, _fe3d->terrain_getSpecularIntensity(editorId));
	_fe3d->terrain_setShadowed(newId, _fe3d->terrain_isShadowed(editorId));

	if(_fe3d->terrain_hasDiffuseMap(editorId))
	{
		_fe3d->terrain_setDiffuseMap(newId, _fe3d->terrain_getDiffuseMapPath(editorId));
	}

	if(_fe3d->terrain_hasNormalMap(editorId))
	{
		_fe3d->terrain_setNormalMap(newId, _fe3d->terrain_getNormalMapPath(editorId));
	}

	if(_fe3d->terrain_hasRedNormalMap(editorId))
	{
		_fe3d->terrain_setRedNormalMap(newId, _fe3d->terrain_getRedNormalMapPath(editorId));
	}

	if(_fe3d->terrain_hasGreenNormalMap(editorId))
	{
		_fe3d->terrain_setGreenNormalMap(newId, _fe3d->terrain_getGreenNormalMapPath(editorId));
	}

	if(_fe3d->terrain_hasBlueNormalMap(editorId))
	{
		_fe3d->terrain_setBlueNormalMap(newId, _fe3d->terrain_getBlueNormalMapPath(editorId));
	}

	if(_fe3d->terrain_hasBlendMap(editorId))
	{
		_fe3d->terrain_setBlendMap(newId, _fe3d->terrain_getBlendMapPath(editorId));
	}

	if(_fe3d->terrain_hasRedDiffuseMap(editorId))
	{
		_fe3d->terrain_setRedDiffuseMap(newId, _fe3d->terrain_getRedDiffuseMapPath(editorId));
	}

	if(_fe3d->terrain_hasGreenDiffuseMap(editorId))
	{
		_fe3d->terrain_setGreenDiffuseMap(newId, _fe3d->terrain_getGreenDiffuseMapPath(editorId));
	}

	if(_fe3d->terrain_hasBlueDiffuseMap(editorId))
	{
		_fe3d->terrain_setBlueDiffuseMap(newId, _fe3d->terrain_getBlueDiffuseMapPath(editorId));
	}

	_copiedTerrainIds.insert({newId, editorId});
}

void Duplicator::copyEditorWater(const string & newId, const string & editorId)
{
	if(!_fe3d->water_isExisting(editorId))
	{
		abort();
	}

	_fe3d->water_create(newId);
	_fe3d->water_select(newId);
	_fe3d->water_setHeight(newId, _fe3d->water_getHeight(editorId));
	_fe3d->water_setSize(newId, _fe3d->water_getSize(editorId));
	_fe3d->water_setSpecular(newId, _fe3d->water_isSpecular(editorId));
	_fe3d->water_setReflective(newId, _fe3d->water_isReflective(editorId));
	_fe3d->water_setRefractive(newId, _fe3d->water_isRefractive(editorId));
	_fe3d->water_setWaveHeight(newId, _fe3d->water_getWaveHeight(editorId));
	_fe3d->water_setSpecularShininess(newId, _fe3d->water_getSpecularShininess(editorId));
	_fe3d->water_setSpecularIntensity(newId, _fe3d->water_getSpecularIntensity(editorId));
	_fe3d->water_setEdged(newId, _fe3d->water_isEdged(editorId));
	_fe3d->water_setColor(newId, _fe3d->water_getColor(editorId));
	_fe3d->water_setLightness(newId, _fe3d->water_getLightness(editorId));
	_fe3d->water_setTextureRepeat(newId, _fe3d->water_getTextureRepeat(editorId));
	_fe3d->water_setRippleSpeed(newId, _fe3d->water_getRippleSpeed(editorId));
	_fe3d->water_setWaveSpeed(newId, _fe3d->water_getWaveSpeed(editorId));
	_fe3d->water_setMaxDepth(newId, _fe3d->water_getMaxDepth(editorId));
	_fe3d->water_setDistortionSize(newId, _fe3d->water_getDistortionSize(editorId));
	_fe3d->water_setDistortionFactor(newId, _fe3d->water_getDistortionFactor(editorId));
	_fe3d->water_setCaptureOffset(newId, _fe3d->water_getCaptureOffset(editorId));
	_fe3d->water_setCapturingSky(newId, _fe3d->water_isCapturingSky(editorId));
	_fe3d->water_setCapturingTerrain(newId, _fe3d->water_isCapturingTerrain(editorId));
	_fe3d->water_setCapturingModels(newId, _fe3d->water_isCapturingModels(editorId));
	_fe3d->water_setCapturingQuad3ds(newId, _fe3d->water_isCapturingQuad3ds(editorId));
	_fe3d->water_setCapturingText3ds(newId, _fe3d->water_isCapturingText3ds(editorId));
	_fe3d->water_setCapturingAabbs(newId, _fe3d->water_isCapturingAabbs(editorId));

	if(_fe3d->water_hasDudvMap(editorId))
	{
		_fe3d->water_setDudvMap(newId, _fe3d->water_getDudvMapPath(editorId));
	}

	if(_fe3d->water_hasNormalMap(editorId))
	{
		_fe3d->water_setNormalMap(newId, _fe3d->water_getNormalMapPath(editorId));
	}

	if(_fe3d->water_hasHeightMap(editorId))
	{
		_fe3d->water_setHeightMap(newId, _fe3d->water_getHeightMapPath(editorId));
	}

	_copiedWaterIds.insert({newId, editorId});
}

void Duplicator::copyEditorModel(const string & newId, const string & editorId)
{
	if(!_fe3d->model_isExisting(editorId))
	{
		abort();
	}

	_fe3d->model_create(newId, _fe3d->model_getMeshPath(editorId));
	_fe3d->model_setBaseSize(newId, _fe3d->model_getBaseSize(editorId));
	_fe3d->model_setShadowed(newId, _fe3d->model_isShadowed(editorId));
	_fe3d->model_setReflected(newId, _fe3d->model_isReflected(editorId));
	_fe3d->model_setRefracted(newId, _fe3d->model_isRefracted(editorId));
	_fe3d->model_setLevelOfDetailId(newId, _fe3d->model_getLevelOfDetailId(editorId));
	_fe3d->model_setLevelOfDetailDistance(newId, _fe3d->model_getLevelOfDetailDistance(editorId));
	_fe3d->model_setRotationOrder(newId, _fe3d->model_getRotationOrder(editorId));

	for(const auto & partId : _fe3d->model_getPartIds(editorId))
	{
		_fe3d->model_setLightness(newId, partId, _fe3d->model_getLightness(editorId, partId));
		_fe3d->model_setBright(newId, partId, _fe3d->model_isBright(editorId, partId));
		_fe3d->model_setEmissionIntensity(newId, partId, _fe3d->model_getEmissionIntensity(editorId, partId));
		_fe3d->model_setSpecular(newId, partId, _fe3d->model_isSpecular(editorId, partId));
		_fe3d->model_setSpecularShininess(newId, partId, _fe3d->model_getSpecularShininess(editorId, partId));
		_fe3d->model_setSpecularIntensity(newId, partId, _fe3d->model_getSpecularIntensity(editorId, partId));
		_fe3d->model_setReflective(newId, partId, _fe3d->model_isReflective(editorId, partId));
		_fe3d->model_setRefractive(newId, partId, _fe3d->model_isRefractive(editorId, partId));
		_fe3d->model_setReflectionType(newId, partId, _fe3d->model_getReflectionType(editorId, partId));
		_fe3d->model_setRefractionType(newId, partId, _fe3d->model_getRefractionType(editorId, partId));
		_fe3d->model_setReflectivity(newId, partId, _fe3d->model_getReflectivity(editorId, partId));
		_fe3d->model_setRefractivity(newId, partId, _fe3d->model_getRefractivity(editorId, partId));
		_fe3d->model_setColor(newId, partId, _fe3d->model_getColor(editorId, partId));
		_fe3d->model_setTextureRepeat(newId, partId, _fe3d->model_getTextureRepeat(editorId, partId));
		_fe3d->model_setFaceCulled(newId, partId, _fe3d->model_isFaceCulled(editorId, partId));
		_fe3d->model_setMinAlpha(newId, partId, _fe3d->model_getMinAlpha(editorId, partId));
		_fe3d->model_setOpacity(newId, partId, _fe3d->model_getOpacity(editorId, partId));

		if(_fe3d->model_hasDiffuseMap(editorId, partId))
		{
			_fe3d->model_setDiffuseMap(newId, partId, _fe3d->model_getDiffuseMapPath(editorId, partId));
		}

		if(_fe3d->model_hasEmissionMap(editorId, partId))
		{
			_fe3d->model_setEmissionMap(newId, partId, _fe3d->model_getEmissionMapPath(editorId, partId));
		}

		if(_fe3d->model_hasSpecularMap(editorId, partId))
		{
			_fe3d->model_setSpecularMap(newId, partId, _fe3d->model_getSpecularMapPath(editorId, partId));
		}

		if(_fe3d->model_hasReflectionMap(editorId, partId))
		{
			_fe3d->model_setReflectionMap(newId, partId, _fe3d->model_getReflectionMapPath(editorId, partId));
		}

		if(_fe3d->model_hasRefractionMap(editorId, partId))
		{
			_fe3d->model_setRefractionMap(newId, partId, _fe3d->model_getRefractionMapPath(editorId, partId));
		}

		if(_fe3d->model_hasNormalMap(editorId, partId))
		{
			_fe3d->model_setNormalMap(newId, partId, _fe3d->model_getNormalMapPath(editorId, partId));
		}
	}

	for(const auto & editorAabbId : _fe3d->model_getChildAabbIds(editorId))
	{
		const auto newAabbId = ("model@" + newId + "@" + editorAabbId.substr(("model@" + editorId + "@").size()));

		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setVisible(newAabbId, false);
		_fe3d->aabb_bindToParent(newAabbId, newId, AabbParentType::MODEL);
		_fe3d->aabb_setLocalPosition(newAabbId, _fe3d->aabb_getLocalPosition(editorAabbId));
		_fe3d->aabb_setLocalSize(newAabbId, _fe3d->aabb_getLocalSize(editorAabbId));
	}

	_copiedModelIds.insert({newId, editorId});
}

void Duplicator::copyEditorQuad3d(const string & newId, const string & editorId)
{
	if(!_fe3d->quad3d_isExisting(editorId))
	{
		abort();
	}

	_fe3d->quad3d_create(newId, false);
	_fe3d->quad3d_setSize(newId, _fe3d->quad3d_getSize(editorId));
	_fe3d->quad3d_setFacingCameraHorizontally(newId, _fe3d->quad3d_isFacingCameraHorizontally(editorId));
	_fe3d->quad3d_setFacingCameraVertically(newId, _fe3d->quad3d_isFacingCameraVertically(editorId));
	_fe3d->quad3d_setHorizontallyFlipped(newId, _fe3d->quad3d_isHorizontallyFlipped(editorId));
	_fe3d->quad3d_setVerticallyFlipped(newId, _fe3d->quad3d_isVerticallyFlipped(editorId));
	_fe3d->quad3d_setColor(newId, _fe3d->quad3d_getColor(editorId));
	_fe3d->quad3d_setBright(newId, _fe3d->quad3d_isBright(editorId));
	_fe3d->quad3d_setTextureRepeat(newId, _fe3d->quad3d_getTextureRepeat(editorId));
	_fe3d->quad3d_setShadowed(newId, _fe3d->quad3d_isShadowed(editorId));
	_fe3d->quad3d_setReflected(newId, _fe3d->quad3d_isReflected(editorId));
	_fe3d->quad3d_setRefracted(newId, _fe3d->quad3d_isRefracted(editorId));
	_fe3d->quad3d_setEmissionIntensity(newId, _fe3d->quad3d_getEmissionIntensity(editorId));
	_fe3d->quad3d_setLightness(newId, _fe3d->quad3d_getLightness(editorId));
	_fe3d->quad3d_setOpacity(newId, _fe3d->quad3d_getOpacity(editorId));
	_fe3d->quad3d_setMinAlpha(newId, _fe3d->quad3d_getMinAlpha(editorId));
	_fe3d->quad3d_setRotationOrder(newId, _fe3d->quad3d_getRotationOrder(editorId));

	if(_fe3d->quad3d_hasDiffuseMap(editorId))
	{
		_fe3d->quad3d_setDiffuseMap(newId, _fe3d->quad3d_getDiffuseMapPath(editorId));
	}

	if(_fe3d->quad3d_hasEmissionMap(editorId))
	{
		_fe3d->quad3d_setEmissionMap(newId, _fe3d->quad3d_getEmissionMapPath(editorId));
	}

	if(!_fe3d->quad3d_getChildAabbIds(editorId).empty())
	{
		const auto newAabbId = ("quad3d@" + newId);

		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setVisible(newAabbId, false);
		_fe3d->aabb_bindToParent(newAabbId, newId, AabbParentType::QUAD3D);
	}

	_copiedQuad3dIds.insert({newId, editorId});
}

void Duplicator::copyEditorQuad2d(const string & newId, const string & editorId)
{
	if(!_fe3d->quad2d_isExisting(editorId))
	{
		abort();
	}

	_fe3d->quad2d_create(newId, true);
	_fe3d->quad2d_setSize(newId, _fe3d->quad2d_getSize(editorId));
	_fe3d->quad2d_setHorizontallyFlipped(newId, _fe3d->quad2d_isHorizontallyFlipped(editorId));
	_fe3d->quad2d_setVerticallyFlipped(newId, _fe3d->quad2d_isVerticallyFlipped(editorId));
	_fe3d->quad2d_setColor(newId, _fe3d->quad2d_getColor(editorId));
	_fe3d->quad2d_setTextureRepeat(newId, _fe3d->quad2d_getTextureRepeat(editorId));
	_fe3d->quad2d_setOpacity(newId, _fe3d->quad2d_getOpacity(editorId));
	_fe3d->quad2d_setLightness(newId, _fe3d->quad2d_getLightness(editorId));

	if(_fe3d->quad2d_hasDiffuseMap(editorId))
	{
		_fe3d->quad2d_setDiffuseMap(newId, _fe3d->quad2d_getDiffuseMapPath(editorId));
	}

	_copiedQuad2dIds.insert({newId, editorId});
}

void Duplicator::copyEditorText3d(const string & newId, const string & editorId)
{
	if(!_fe3d->text3d_isExisting(editorId))
	{
		abort();
	}

	_fe3d->text3d_create(newId, _fe3d->text3d_getFontMapPath(editorId), false);
	_fe3d->text3d_setSize(newId, _fe3d->text3d_getSize(editorId));
	_fe3d->text3d_setFacingCameraHorizontally(newId, _fe3d->text3d_isFacingCameraHorizontally(editorId));
	_fe3d->text3d_setFacingCameraVertically(newId, _fe3d->text3d_isFacingCameraVertically(editorId));
	_fe3d->text3d_setHorizontallyFlipped(newId, _fe3d->text3d_isHorizontallyFlipped(editorId));
	_fe3d->text3d_setVerticallyFlipped(newId, _fe3d->text3d_isVerticallyFlipped(editorId));
	_fe3d->text3d_setColor(newId, _fe3d->text3d_getColor(editorId));
	_fe3d->text3d_setShadowed(newId, _fe3d->text3d_isShadowed(editorId));
	_fe3d->text3d_setReflected(newId, _fe3d->text3d_isReflected(editorId));
	_fe3d->text3d_setRefracted(newId, _fe3d->text3d_isRefracted(editorId));
	_fe3d->text3d_setLightness(newId, _fe3d->text3d_getLightness(editorId));
	_fe3d->text3d_setBright(newId, _fe3d->text3d_isBright(editorId));
	_fe3d->text3d_setOpacity(newId, _fe3d->text3d_getOpacity(editorId));
	_fe3d->text3d_setContent(newId, _fe3d->text3d_getContent(editorId));
	_fe3d->text3d_setMinAlpha(newId, _fe3d->text3d_getMinAlpha(editorId));
	_fe3d->text3d_setRotationOrder(newId, _fe3d->text3d_getRotationOrder(editorId));

	if(!_fe3d->text3d_getChildAabbIds(editorId).empty())
	{
		const auto newAabbId = ("text3d@" + newId);

		_fe3d->aabb_create(newAabbId, false);
		_fe3d->aabb_setVisible(newAabbId, false);
		_fe3d->aabb_bindToParent(newAabbId, newId, AabbParentType::TEXT3D);
	}

	_copiedText3dIds.insert({newId, editorId});
}

void Duplicator::copyEditorText2d(const string & newId, const string & editorId)
{
	if(!_fe3d->text2d_isExisting(editorId))
	{
		abort();
	}

	_fe3d->text2d_create(newId, _fe3d->text2d_getFontMapPath(editorId), true);
	_fe3d->text2d_setSize(newId, _fe3d->text2d_getSize(editorId));
	_fe3d->text2d_setHorizontallyFlipped(newId, _fe3d->text2d_isHorizontallyFlipped(editorId));
	_fe3d->text2d_setVerticallyFlipped(newId, _fe3d->text2d_isVerticallyFlipped(editorId));
	_fe3d->text2d_setColor(newId, _fe3d->text2d_getColor(editorId));
	_fe3d->text2d_setOpacity(newId, _fe3d->text2d_getOpacity(editorId));
	_fe3d->text2d_setLightness(newId, _fe3d->text2d_getLightness(editorId));
	_fe3d->text2d_setContent(newId, _fe3d->text2d_getContent(editorId));

	_copiedText2dIds.insert({newId, editorId});
}

void Duplicator::copyEditorAabb(const string & newId, const string & editorId)
{
	if(!_fe3d->aabb_isExisting(editorId))
	{
		abort();
	}

	_fe3d->aabb_create(newId, false);
	_fe3d->aabb_setVisible(newId, false);
	_fe3d->aabb_setBaseSize(newId, _fe3d->aabb_getBaseSize(editorId));
	_fe3d->aabb_setColor(newId, _fe3d->aabb_getColor(editorId));

	_copiedAabbIds.insert({newId, editorId});
}

void Duplicator::copyEditorPointlight(const string & newId, const string & editorId)
{
	if(!_fe3d->pointlight_isExisting(editorId))
	{
		abort();
	}

	_fe3d->pointlight_create(newId);
	_fe3d->pointlight_setRadius(newId, _fe3d->pointlight_getRadius(editorId));
	_fe3d->pointlight_setColor(newId, _fe3d->pointlight_getColor(editorId));
	_fe3d->pointlight_setIntensity(newId, _fe3d->pointlight_getIntensity(editorId));
	_fe3d->pointlight_setShape(newId, _fe3d->pointlight_getShape(editorId));

	_copiedPointlightIds.insert({newId, editorId});
}

void Duplicator::copyEditorSpotlight(const string & newId, const string & editorId)
{
	if(!_fe3d->spotlight_isExisting(editorId))
	{
		abort();
	}

	_fe3d->spotlight_create(newId);
	_fe3d->spotlight_setColor(newId, _fe3d->spotlight_getColor(editorId));
	_fe3d->spotlight_setYaw(newId, _fe3d->spotlight_getYaw(editorId));
	_fe3d->spotlight_setPitch(newId, _fe3d->spotlight_getPitch(editorId));
	_fe3d->spotlight_setIntensity(newId, _fe3d->spotlight_getIntensity(editorId));
	_fe3d->spotlight_setAngle(newId, _fe3d->spotlight_getAngle(editorId));
	_fe3d->spotlight_setDistance(newId, _fe3d->spotlight_getDistance(editorId));

	_copiedSpotlightIds.insert({newId, editorId});
}

void Duplicator::copyEditorCaptor(const string & newId, const string & editorId)
{
	if(!_fe3d->captor_isExisting(editorId))
	{
		abort();
	}

	_fe3d->captor_create(newId);
	_fe3d->captor_setReflectionQuality(newId, _fe3d->captor_getReflectionQuality(editorId));
	_fe3d->captor_setRefractionQuality(newId, _fe3d->captor_getRefractionQuality(editorId));

	_copiedCaptorIds.insert({newId, editorId});
}

void Duplicator::copyEditorSound3d(const string & newId, const string & editorId)
{
	if(!_fe3d->sound3d_isExisting(editorId))
	{
		abort();
	}

	_fe3d->sound3d_create(newId, _fe3d->sound3d_getAudioPath(editorId));
	_fe3d->sound3d_setMaxVolume(newId, _fe3d->sound3d_getMaxVolume(editorId));
	_fe3d->sound3d_setMaxDistance(newId, _fe3d->sound3d_getMaxDistance(editorId));

	_copiedSound3dIds.insert({newId, editorId});
}

void Duplicator::copyEditorSound2d(const string & newId, const string & editorId)
{
	if(!_fe3d->sound2d_isExisting(editorId))
	{
		abort();
	}

	_fe3d->sound2d_create(newId, _fe3d->sound2d_getAudioPath(editorId));

	_copiedSound2dIds.insert({newId, editorId});
}
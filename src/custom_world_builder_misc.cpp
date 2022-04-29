#include "custom_world_builder.hpp"

void CustomWorldBuilder::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void CustomWorldBuilder::setCurrentProjectId(const string & currentProjectId)
{
	_currentProjectId = currentProjectId;
}

void CustomWorldBuilder::addGraphics()
{
	if(_isGraphicsAdded)
	{
		abort();
	}

	_isGraphicsAdded = true;
}

void CustomWorldBuilder::addSky(const string & skyId)
{
	if(find(_addedSkyIds.begin(), _addedSkyIds.end(), skyId) != _addedSkyIds.end())
	{
		abort();
	}

	_addedSkyIds.push_back(skyId);
}

void CustomWorldBuilder::addTerrain(const string & terrainId)
{
	if(find(_addedTerrainIds.begin(), _addedTerrainIds.end(), terrainId) != _addedTerrainIds.end())
	{
		abort();
	}

	_addedTerrainIds.push_back(terrainId);
}

void CustomWorldBuilder::addWater(const string & waterId)
{
	if(find(_addedWaterIds.begin(), _addedWaterIds.end(), waterId) != _addedWaterIds.end())
	{
		abort();
	}

	_addedWaterIds.push_back(waterId);
}

void CustomWorldBuilder::addModel(const string & modelId)
{
	if(find(_addedModelIds.begin(), _addedModelIds.end(), modelId) != _addedModelIds.end())
	{
		abort();
	}

	_addedModelIds.push_back(modelId);
}

void CustomWorldBuilder::addQuad3d(const string & quad3dId)
{
	if(find(_addedQuad3dIds.begin(), _addedQuad3dIds.end(), quad3dId) != _addedQuad3dIds.end())
	{
		abort();
	}

	_addedQuad3dIds.push_back(quad3dId);
}

void CustomWorldBuilder::addText3d(const string & text3dId)
{
	if(find(_addedText3dIds.begin(), _addedText3dIds.end(), text3dId) != _addedText3dIds.end())
	{
		abort();
	}

	_addedText3dIds.push_back(text3dId);
}

void CustomWorldBuilder::addAabb(const string & aabbId)
{
	if(find(_addedAabbIds.begin(), _addedAabbIds.end(), aabbId) != _addedAabbIds.end())
	{
		abort();
	}

	_addedAabbIds.push_back(aabbId);
}

void CustomWorldBuilder::addSound(const string & soundId)
{
	if(find(_addedSound3dIds.begin(), _addedSound3dIds.end(), soundId) != _addedSound3dIds.end())
	{
		abort();
	}

	_addedSound3dIds.push_back(soundId);
}

void CustomWorldBuilder::addPointlight(const string & pointlightId)
{
	if(find(_addedPointlightIds.begin(), _addedPointlightIds.end(), pointlightId) != _addedPointlightIds.end())
	{
		abort();
	}

	_addedPointlightIds.push_back(pointlightId);
}

void CustomWorldBuilder::addSpotlight(const string & spotlightId)
{
	if(find(_addedSpotlightIds.begin(), _addedSpotlightIds.end(), spotlightId) != _addedSpotlightIds.end())
	{
		abort();
	}

	_addedSpotlightIds.push_back(spotlightId);
}

void CustomWorldBuilder::addCaptor(const string & captorId)
{
	if(find(_addedCaptorIds.begin(), _addedCaptorIds.end(), captorId) != _addedCaptorIds.end())
	{
		abort();
	}

	_addedCaptorIds.push_back(captorId);
}

void CustomWorldBuilder::clearLoadedWorld()
{
	if(_loadedWorldId.empty())
	{
		abort();
	}

	if(_isGraphicsLoaded)
	{
		_fe3d->graphics_setAmbientLightingEnabled(false);
		_fe3d->graphics_setDirectionalLightingEnabled(false);
		_fe3d->graphics_setFogEnabled(false);
		_fe3d->graphics_setShadowsEnabled(false);
		_fe3d->graphics_setSkyExposureEnabled(false);
		_fe3d->graphics_setDofEnabled(false);
		_fe3d->graphics_setLensFlareEnabled(false);
		_fe3d->graphics_setBloomEnabled(false);
		_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
		_fe3d->graphics_setAmbientLightingIntensity(0.0f);
		_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
		_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
		_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
		_fe3d->graphics_setFogColor(fvec3(0.0f));
		_fe3d->graphics_setFogThickness(0.0f);
		_fe3d->graphics_setFogMinDistance(0.0f);
		_fe3d->graphics_setFogMaxDistance(0.0f);
		_fe3d->graphics_setShadowCircleEnabled(false);
		_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
		_fe3d->graphics_setShadowLookatOffset(fvec3(0.0f));
		_fe3d->graphics_setShadowSize(0.0f);
		_fe3d->graphics_setShadowLightness(0.0f);
		_fe3d->graphics_setShadowQuality(0);
		_fe3d->graphics_setShadowInterval(0);
		_fe3d->graphics_setShadowFollowingCameraX(false);
		_fe3d->graphics_setShadowFollowingCameraY(false);
		_fe3d->graphics_setShadowFollowingCameraZ(false);
		_fe3d->graphics_setBloomIntensity(0.0f);
		_fe3d->graphics_setBloomBlurCount(0);
		_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
		_fe3d->graphics_setBloomQuality(0);
		_fe3d->graphics_setSkyExposureIntensity(0.0f);
		_fe3d->graphics_setSkyExposureSpeed(0.0f);
		_fe3d->graphics_setDofDynamicDistance(0.0f);
		_fe3d->graphics_setDofBlurDistance(0.0f);
		_fe3d->graphics_setDofDynamic(false);
		_fe3d->graphics_setDofQuality(0);
		_fe3d->graphics_setLensFlareMap("");
		_fe3d->graphics_setLensFlareIntensity(0.0f);
		_fe3d->graphics_setLensFlareSensitivity(0.0f);
		_fe3d->graphics_setCubeReflectionQuality(0);
		_fe3d->graphics_setPlanarReflectionQuality(0);
		_fe3d->graphics_setPlanarRefractionQuality(0);
		_fe3d->graphics_setPlanarReflectionHeight(0.0f);
	}

	for(const auto & skyId : _loadedSkyIds)
	{
		_fe3d->sky_delete(skyId);
	}

	for(const auto & terrainId : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(terrainId);
	}

	for(const auto & waterId : _loadedWaterIds)
	{
		_fe3d->water_delete(waterId);
	}

	for(const auto & modelId : _loadedModelIds)
	{
		_fe3d->model_delete(modelId);
	}

	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(quad3dId);
	}

	for(const auto & text3dId : _loadedText3dIds)
	{
		_fe3d->text3d_delete(text3dId);
	}

	for(const auto & aabbId : _loadedAabbIds)
	{
		_fe3d->aabb_delete(aabbId);
	}

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(pointlightId);
	}

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(spotlightId);
	}

	for(const auto & captorId : _loadedCaptorIds)
	{
		_fe3d->captor_delete(captorId);
	}

	for(const auto & sound3dId : _loadedSound3dIds)
	{
		_fe3d->sound3d_delete(sound3dId);
	}

	_loadedSkyIds.clear();
	_loadedTerrainIds.clear();
	_loadedWaterIds.clear();
	_loadedModelIds.clear();
	_loadedQuad3dIds.clear();
	_loadedText3dIds.clear();
	_loadedAabbIds.clear();
	_loadedPointlightIds.clear();
	_loadedSpotlightIds.clear();
	_loadedCaptorIds.clear();
	_loadedSound3dIds.clear();
	_loadedWorldId = "";
	_isGraphicsLoaded = false;
}

const string & CustomWorldBuilder::getLoadedWorldId() const
{
	return _loadedWorldId;
}

const bool CustomWorldBuilder::isSkyAdded(const string & skyId) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), skyId) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isTerrainAdded(const string & terrainId) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), terrainId) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isWaterAdded(const string & waterId) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), waterId) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isModelAdded(const string & modelId) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), modelId) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isQuad3dAdded(const string & quad3dId) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), quad3dId) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isText3dAdded(const string & text3dId) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), text3dId) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isAabbAdded(const string & aabbId) const
{
	return find(_addedAabbIds.begin(), _addedAabbIds.end(), aabbId) != _addedAabbIds.end();
}

const bool CustomWorldBuilder::isPointlightAdded(const string & pointlightId) const
{
	return find(_addedPointlightIds.begin(), _addedPointlightIds.end(), pointlightId) != _addedPointlightIds.end();
}

const bool CustomWorldBuilder::isSpotlightAdded(const string & spotlightId) const
{
	return find(_addedSpotlightIds.begin(), _addedSpotlightIds.end(), spotlightId) != _addedSpotlightIds.end();
}

const bool CustomWorldBuilder::isCaptorAdded(const string & captorId) const
{
	return find(_addedCaptorIds.begin(), _addedCaptorIds.end(), captorId) != _addedCaptorIds.end();
}

const bool CustomWorldBuilder::isSound3dAdded(const string & sound3dId) const
{
	return find(_addedSound3dIds.begin(), _addedSound3dIds.end(), sound3dId) != _addedSound3dIds.end();
}

const bool CustomWorldBuilder::isGraphicsAdded() const
{
	return _isGraphicsAdded;
}

void CustomWorldBuilder::resetWorldBuild()
{
	_addedSkyIds.clear();
	_addedTerrainIds.clear();
	_addedWaterIds.clear();
	_addedModelIds.clear();
	_addedQuad3dIds.clear();
	_addedText3dIds.clear();
	_addedAabbIds.clear();
	_addedPointlightIds.clear();
	_addedSpotlightIds.clear();
	_addedCaptorIds.clear();
	_addedSound3dIds.clear();
	_isGraphicsAdded = false;
}
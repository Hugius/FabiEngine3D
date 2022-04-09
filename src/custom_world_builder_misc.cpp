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

void CustomWorldBuilder::addSky(const string & id)
{
	if(find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end())
	{
		abort();
	}

	_addedSkyIds.push_back(id);
}

void CustomWorldBuilder::addTerrain(const string & id)
{
	if(find(_addedTerrainIds.begin(), _addedTerrainIds.end(), id) != _addedTerrainIds.end())
	{
		abort();
	}

	_addedTerrainIds.push_back(id);
}

void CustomWorldBuilder::addWater(const string & id)
{
	if(find(_addedWaterIds.begin(), _addedWaterIds.end(), id) != _addedWaterIds.end())
	{
		abort();
	}

	_addedWaterIds.push_back(id);
}

void CustomWorldBuilder::addModel(const string & id)
{
	if(find(_addedModelIds.begin(), _addedModelIds.end(), id) != _addedModelIds.end())
	{
		abort();
	}

	_addedModelIds.push_back(id);
}

void CustomWorldBuilder::addQuad(const string & id)
{
	if(find(_addedQuad3dIds.begin(), _addedQuad3dIds.end(), id) != _addedQuad3dIds.end())
	{
		abort();
	}

	_addedQuad3dIds.push_back(id);
}

void CustomWorldBuilder::addText(const string & id)
{
	if(find(_addedText3dIds.begin(), _addedText3dIds.end(), id) != _addedText3dIds.end())
	{
		abort();
	}

	_addedText3dIds.push_back(id);
}

void CustomWorldBuilder::addAabb(const string & id)
{
	if(find(_addedAabbIds.begin(), _addedAabbIds.end(), id) != _addedAabbIds.end())
	{
		abort();
	}

	_addedAabbIds.push_back(id);
}

void CustomWorldBuilder::addSound(const string & id)
{
	if(find(_addedSound3dIds.begin(), _addedSound3dIds.end(), id) != _addedSound3dIds.end())
	{
		abort();
	}

	_addedSound3dIds.push_back(id);
}

void CustomWorldBuilder::addPointlight(const string & id)
{
	if(find(_addedPointlightIds.begin(), _addedPointlightIds.end(), id) != _addedPointlightIds.end())
	{
		abort();
	}

	_addedPointlightIds.push_back(id);
}

void CustomWorldBuilder::addSpotlight(const string & id)
{
	if(find(_addedSpotlightIds.begin(), _addedSpotlightIds.end(), id) != _addedSpotlightIds.end())
	{
		abort();
	}

	_addedSpotlightIds.push_back(id);
}

void CustomWorldBuilder::addReflection(const string & id)
{
	if(find(_addedReflectionIds.begin(), _addedReflectionIds.end(), id) != _addedReflectionIds.end())
	{
		abort();
	}

	_addedReflectionIds.push_back(id);
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
		_fe3d->graphics_setShadowFollowingCamera(false);
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

	for(const auto & id : _loadedSkyIds)
	{
		_fe3d->sky_delete(id);
	}

	for(const auto & id : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(id);
	}

	for(const auto & id : _loadedWaterIds)
	{
		_fe3d->water_delete(id);
	}

	for(const auto & id : _loadedModelIds)
	{
		_fe3d->model_delete(id);
	}

	for(const auto & id : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(id);
	}

	for(const auto & id : _loadedText3dIds)
	{
		_fe3d->text3d_delete(id);
	}

	for(const auto & id : _loadedAabbIds)
	{
		_fe3d->aabb_delete(id);
	}

	for(const auto & id : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(id);
	}

	for(const auto & id : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(id);
	}

	for(const auto & id : _loadedReflectionIds)
	{
		_fe3d->reflection_delete(id);
	}

	for(const auto & id : _loadedSound3dIds)
	{
		_fe3d->sound3d_delete(id);
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
	_loadedReflectionIds.clear();
	_loadedSound3dIds.clear();
	_loadedWorldId = "";
	_isGraphicsLoaded = false;
}

const string & CustomWorldBuilder::getLoadedWorldId() const
{
	return _loadedWorldId;
}

const bool CustomWorldBuilder::isSkyAdded(const string & id) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isTerrainAdded(const string & id) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isWaterAdded(const string & id) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isModelAdded(const string & id) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isQuad3dAdded(const string & id) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isText3dAdded(const string & id) const
{
	return find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end();
}

const bool CustomWorldBuilder::isAabbAdded(const string & id) const
{
	return find(_addedAabbIds.begin(), _addedAabbIds.end(), id) != _addedAabbIds.end();
}

const bool CustomWorldBuilder::isPointlightAdded(const string & id) const
{
	return find(_addedPointlightIds.begin(), _addedPointlightIds.end(), id) != _addedPointlightIds.end();
}

const bool CustomWorldBuilder::isSpotlightAdded(const string & id) const
{
	return find(_addedSpotlightIds.begin(), _addedSpotlightIds.end(), id) != _addedSpotlightIds.end();
}

const bool CustomWorldBuilder::isReflectionAdded(const string & id) const
{
	return find(_addedReflectionIds.begin(), _addedReflectionIds.end(), id) != _addedReflectionIds.end();
}

const bool CustomWorldBuilder::isSound3dAdded(const string & id) const
{
	return find(_addedSound3dIds.begin(), _addedSound3dIds.end(), id) != _addedSound3dIds.end();
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
	_addedReflectionIds.clear();
	_addedSound3dIds.clear();
	_isGraphicsAdded = false;
}
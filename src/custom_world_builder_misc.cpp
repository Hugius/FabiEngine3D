#include "custom_world_builder.hpp"

void CustomWorldBuilder::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void CustomWorldBuilder::resetWorldBuild()
{
	_addedSkyIds.clear();
	_addedTerrainIds.clear();
	_addedWaterIds.clear();
	_addedModelIds.clear();
	_addedQuadIds.clear();
	_addedTextIds.clear();
	_addedAabbIds.clear();
	_addedPointlightIds.clear();
	_addedSpotlightIds.clear();
	_addedReflectionIds.clear();
	_addedSoundIds.clear();
	_hasAddedLighting = false;
	_hasAddedGraphics = false;
}

void CustomWorldBuilder::addLighting()
{
	_hasAddedLighting = true;
}

void CustomWorldBuilder::addGraphics()
{
	_hasAddedGraphics = true;
}

void CustomWorldBuilder::addSky(const string& id)
{
	if(find(_addedSkyIds.begin(), _addedSkyIds.end(), id) != _addedSkyIds.end())
	{
		abort();
	}

	_addedSkyIds.push_back(id);
}

void CustomWorldBuilder::addTerrain(const string& id)
{
	if(find(_addedTerrainIds.begin(), _addedTerrainIds.end(), id) != _addedTerrainIds.end())
	{
		abort();
	}

	_addedTerrainIds.push_back(id);
}

void CustomWorldBuilder::addWater(const string& id)
{
	if(find(_addedWaterIds.begin(), _addedWaterIds.end(), id) != _addedWaterIds.end())
	{
		abort();
	}

	_addedWaterIds.push_back(id);
}

void CustomWorldBuilder::addModel(const string& id)
{
	if(find(_addedModelIds.begin(), _addedModelIds.end(), id) != _addedModelIds.end())
	{
		abort();
	}

	_addedModelIds.push_back(id);
}

void CustomWorldBuilder::addQuad3d(const string& id)
{
	if(find(_addedQuadIds.begin(), _addedQuadIds.end(), id) != _addedQuadIds.end())
	{
		abort();
	}

	_addedQuadIds.push_back(id);
}

void CustomWorldBuilder::addText(const string& id)
{
	if(find(_addedTextIds.begin(), _addedTextIds.end(), id) != _addedTextIds.end())
	{
		abort();
	}

	_addedTextIds.push_back(id);
}

void CustomWorldBuilder::addAabb(const string& id)
{
	if(find(_addedAabbIds.begin(), _addedAabbIds.end(), id) != _addedAabbIds.end())
	{
		abort();
	}

	_addedAabbIds.push_back(id);
}

void CustomWorldBuilder::addSound(const string& id)
{
	if(find(_addedSoundIds.begin(), _addedSoundIds.end(), id) != _addedSoundIds.end())
	{
		abort();
	}

	_addedSoundIds.push_back(id);
}

void CustomWorldBuilder::addPointlight(const string& id)
{
	if(find(_addedPointlightIds.begin(), _addedPointlightIds.end(), id) != _addedPointlightIds.end())
	{
		abort();
	}

	_addedPointlightIds.push_back(id);
}

void CustomWorldBuilder::addSpotlight(const string& id)
{
	if(find(_addedSpotlightIds.begin(), _addedSpotlightIds.end(), id) != _addedSpotlightIds.end())
	{
		abort();
	}

	_addedSpotlightIds.push_back(id);
}

void CustomWorldBuilder::addReflection(const string& id)
{
	if(find(_addedReflectionIds.begin(), _addedReflectionIds.end(), id) != _addedReflectionIds.end())
	{
		abort();
	}

	_addedReflectionIds.push_back(id);
}

void CustomWorldBuilder::clearLoadedWorld()
{
	_fe3d->gfx_setAmbientLightingEnabled(false);
	_fe3d->gfx_setDirectionalLightingEnabled(false);
	_fe3d->gfx_setFogEnabled(false);
	_fe3d->gfx_setShadowsEnabled(false);
	_fe3d->gfx_setSkyExposureEnabled(false);
	_fe3d->gfx_setDofEnabled(false);
	_fe3d->gfx_setLensFlareEnabled(false);
	_fe3d->gfx_setBloomEnabled(false);
	_fe3d->gfx_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->gfx_setAmbientLightingIntensity(0.0f);
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(0.0f);
	_fe3d->gfx_setFogColor(fvec3(0.0f));
	_fe3d->gfx_setFogThickness(0.0f);
	_fe3d->gfx_setFogMinDistance(0.0f);
	_fe3d->gfx_setFogMaxDistance(0.0f);
	_fe3d->gfx_setShadowCircleEnabled(false);
	_fe3d->gfx_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->gfx_setShadowLookatOffset(fvec3(0.0f));
	_fe3d->gfx_setShadowSize(0.0f);
	_fe3d->gfx_setShadowLightness(0.0f);
	_fe3d->gfx_setShadowQuality(0);
	_fe3d->gfx_setShadowInterval(0);
	_fe3d->gfx_setShadowFollowingCamera(false);
	_fe3d->gfx_setBloomIntensity(0.0f);
	_fe3d->gfx_setBloomBlurCount(0);
	_fe3d->gfx_setBloomType(BloomType::EVERYTHING);
	_fe3d->gfx_setBloomQuality(0);
	_fe3d->gfx_setSkyExposureIntensity(0.0f);
	_fe3d->gfx_setSkyExposureSpeed(0.0f);
	_fe3d->gfx_setDofDynamicDistance(0.0f);
	_fe3d->gfx_setDofBlurDistance(0.0f);
	_fe3d->gfx_setDofDynamic(false);
	_fe3d->gfx_setDofQuality(0);
	_fe3d->gfx_setLensFlareMap("");
	_fe3d->gfx_setLensFlareIntensity(0.0f);
	_fe3d->gfx_setLensFlareSensitivity(0.0f);
	_fe3d->gfx_setCubeReflectionQuality(0);
	_fe3d->gfx_setPlanarReflectionQuality(0);
	_fe3d->gfx_setPlanarRefractionQuality(0);
	_fe3d->gfx_setPlanarReflectionHeight(0.0f);

	for(const auto& id : _loadedSkyIds)
	{
		_fe3d->sky_delete(id);
	}

	for(const auto& id : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(id);
	}

	for(const auto& id : _loadedWaterIds)
	{
		_fe3d->water_delete(id);
	}

	for(const auto& id : _loadedModelIds)
	{
		_fe3d->model_delete(id);
	}

	for(const auto& id : _loadedQuadIds)
	{
		_fe3d->quad3d_delete(id);
	}

	for(const auto& id : _loadedTextIds)
	{
		_fe3d->text3d_delete(id);
	}

	for(const auto& id : _loadedAabbIds)
	{
		_fe3d->aabb_delete(id);
	}

	for(const auto& id : _loadedPointlightIds)
	{
		_fe3d->pointlight_delete(id);
	}

	for(const auto& id : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(id);
	}

	for(const auto& id : _loadedReflectionIds)
	{
		_fe3d->reflection_delete(id);
	}

	for(const auto& id : _loadedSoundIds)
	{
		_fe3d->sound3d_delete(id);
	}

	_loadedSkyIds.clear();
	_loadedTerrainIds.clear();
	_loadedWaterIds.clear();
	_loadedModelIds.clear();
	_loadedQuadIds.clear();
	_loadedTextIds.clear();
	_loadedAabbIds.clear();
	_loadedPointlightIds.clear();
	_loadedSpotlightIds.clear();
	_loadedReflectionIds.clear();
	_loadedSoundIds.clear();
}
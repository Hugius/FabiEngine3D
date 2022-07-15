#include "duplicator.hpp"

void Duplicator::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void Duplicator::deleteCopiedSky(const string & skyId)
{
	_fe3d->sky_delete(skyId);

	_copiedSkyIds.erase(skyId);
}

void Duplicator::deleteCopiedTerrain(const string & terrainId)
{
	_fe3d->terrain_delete(terrainId);

	_copiedTerrainIds.erase(terrainId);
}

void Duplicator::deleteCopiedWater(const string & waterId)
{
	_fe3d->water_delete(waterId);

	_copiedWaterIds.erase(waterId);
}

void Duplicator::deleteCopiedModel(const string & modelId)
{
	_fe3d->model_delete(modelId);

	_copiedModelIds.erase(modelId);
}

void Duplicator::deleteCopiedQuad3d(const string & quad3dId)
{
	_fe3d->quad3d_delete(quad3dId);

	_copiedQuad3dIds.erase(quad3dId);
}

void Duplicator::deleteCopiedQuad2d(const string & quad2dId)
{
	_fe3d->quad2d_delete(quad2dId);

	_copiedQuad2dIds.erase(quad2dId);
}

void Duplicator::deleteCopiedText3d(const string & text3dId)
{
	_fe3d->text3d_delete(text3dId);

	_copiedText3dIds.erase(text3dId);
}

void Duplicator::deleteCopiedText2d(const string & text2dId)
{
	_fe3d->text2d_delete(text2dId);

	_copiedText2dIds.erase(text2dId);
}

void Duplicator::deleteCopiedAabb(const string & aabbId)
{
	_fe3d->aabb_delete(aabbId);

	_copiedAabbIds.erase(aabbId);
}

void Duplicator::deleteCopiedPointlight(const string & pointlightId)
{
	_fe3d->pointlight_delete(pointlightId);

	_copiedPointlightIds.erase(pointlightId);
}

void Duplicator::deleteCopiedSpotlight(const string & spotlightId)
{
	_fe3d->spotlight_delete(spotlightId);

	_copiedSpotlightIds.erase(spotlightId);
}

void Duplicator::deleteCopiedCaptor(const string & captorId)
{
	_fe3d->captor_delete(captorId);

	_copiedCaptorIds.erase(captorId);
}

void Duplicator::deleteCopiedSound3d(const string & sound3dId)
{
	_fe3d->sound3d_delete(sound3dId);

	_copiedSound3dIds.erase(sound3dId);
}

void Duplicator::deleteCopiedSound2d(const string & sound2dId)
{
	_fe3d->sound2d_delete(sound2dId);

	_copiedSound2dIds.erase(sound2dId);
}

const string & Duplicator::getEditorSkyId(const string & skyId) const
{
	if(_copiedSkyIds.find(skyId) == _copiedSkyIds.end())
	{
		abort();
	}

	return _copiedSkyIds.at(skyId);
}

const string & Duplicator::getEditorTerrainId(const string & terrainId) const
{
	if(_copiedTerrainIds.find(terrainId) == _copiedTerrainIds.end())
	{
		abort();
	}

	return _copiedTerrainIds.at(terrainId);
}

const string & Duplicator::getEditorWaterId(const string & waterId) const
{
	if(_copiedWaterIds.find(waterId) == _copiedWaterIds.end())
	{
		abort();
	}

	return _copiedWaterIds.at(waterId);
}

const string & Duplicator::getEditorModelId(const string & modelId) const
{
	if(_copiedModelIds.find(modelId) == _copiedModelIds.end())
	{
		abort();
	}

	return _copiedModelIds.at(modelId);
}

const string & Duplicator::getEditorQuad3dId(const string & quad3dId) const
{
	if(_copiedQuad3dIds.find(quad3dId) == _copiedQuad3dIds.end())
	{
		abort();
	}

	return _copiedQuad3dIds.at(quad3dId);
}

const string & Duplicator::getEditorQuad2dId(const string & quad2dId) const
{
	if(_copiedQuad2dIds.find(quad2dId) == _copiedQuad2dIds.end())
	{
		abort();
	}

	return _copiedQuad2dIds.at(quad2dId);
}

const string & Duplicator::getEditorText3dId(const string & text3dId) const
{
	if(_copiedText3dIds.find(text3dId) == _copiedText3dIds.end())
	{
		abort();
	}

	return _copiedText3dIds.at(text3dId);
}

const string & Duplicator::getEditorText2dId(const string & text2dId) const
{
	if(_copiedText2dIds.find(text2dId) == _copiedText2dIds.end())
	{
		abort();
	}

	return _copiedText2dIds.at(text2dId);
}

const string & Duplicator::getEditorAabbId(const string & aabbId) const
{
	if(_copiedAabbIds.find(aabbId) == _copiedAabbIds.end())
	{
		abort();
	}

	return _copiedAabbIds.at(aabbId);
}

const string & Duplicator::getEditorPointlightId(const string & pointlightId) const
{
	if(_copiedPointlightIds.find(pointlightId) == _copiedPointlightIds.end())
	{
		abort();
	}

	return _copiedPointlightIds.at(pointlightId);
}

const string & Duplicator::getEditorSpotlightId(const string & spotlightId) const
{
	if(_copiedSpotlightIds.find(spotlightId) == _copiedSpotlightIds.end())
	{
		abort();
	}

	return _copiedSpotlightIds.at(spotlightId);
}

const string & Duplicator::getEditorCaptorId(const string & captorId) const
{
	if(_copiedCaptorIds.find(captorId) == _copiedCaptorIds.end())
	{
		abort();
	}

	return _copiedCaptorIds.at(captorId);
}

const string & Duplicator::getEditorSound3dId(const string & sound3dId) const
{
	if(_copiedSound3dIds.find(sound3dId) == _copiedSound3dIds.end())
	{
		abort();
	}

	return _copiedSound3dIds.at(sound3dId);
}

const string & Duplicator::getEditorSound2dId(const string & sound2dId) const
{
	if(_copiedSound2dIds.find(sound2dId) == _copiedSound2dIds.end())
	{
		abort();
	}

	return _copiedSound2dIds.at(sound2dId);
}
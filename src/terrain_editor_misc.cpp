#include "terrain_editor.hpp"

#include <algorithm>

const vector<string> & TerrainEditor::getLoadedTerrainIds() const
{
	return _loadedTerrainIds;
}

void TerrainEditor::deleteLoadedTerrains()
{
	for(const auto & terrainId : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(terrainId);
	}

	_loadedTerrainIds.clear();
}
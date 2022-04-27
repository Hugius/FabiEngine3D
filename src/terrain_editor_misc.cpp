#include "terrain_editor.hpp"

#include <algorithm>

const vector<string> & TerrainEditor::getLoadedEntityIds() const
{
	return _loadedTerrainIds;
}

void TerrainEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedTerrainIds)
	{
		_fe3d->terrain_delete(id);
	}

	_loadedTerrainIds.clear();
}
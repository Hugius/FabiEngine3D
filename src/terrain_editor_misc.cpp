#include "terrain_editor.hpp"

#include <algorithm>

const vector<string> & TerrainEditor::getLoadedEntityIds() const
{
	return _loadedEntityIds;
}

void TerrainEditor::deleteLoadedEntities()
{
	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->terrain_delete(id);
	}

	_loadedEntityIds.clear();
}
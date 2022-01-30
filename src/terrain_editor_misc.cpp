#include "terrain_editor.hpp"

#include <algorithm>

const vector<string>& TerrainEditor::getLoadedIds()
{
	sort(_loadedTerrainIds.begin(), _loadedTerrainIds.end());
	return _loadedTerrainIds;
}
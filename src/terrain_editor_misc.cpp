#include "terrain_editor.hpp"

#include <algorithm>

const vector<string>& TerrainEditor::getLoadedEntityIds()
{
	return _loadedEntityIds;
}
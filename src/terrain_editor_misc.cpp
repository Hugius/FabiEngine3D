#include "terrain_editor.hpp"

#include <algorithm>

void TerrainEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool TerrainEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& TerrainEditor::getLoadedTerrainIDs()
{
	sort(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end());
	return _loadedTerrainIDs;
}
#include "terrain_editor.hpp"

#include <algorithm>

void TerrainEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool TerrainEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& TerrainEditor::getLoadedIDs()
{
	sort(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end());
	return _loadedTerrainIDs;
}
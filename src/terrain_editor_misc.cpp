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

void TerrainEditor::unloadTerrainEntities()
{
	for(const auto& ID : _loadedTerrainIDs)
	{
		if(_fe3d.terrain_isExisting(ID))
		{
			_fe3d.terrain_delete(ID);
		}
	}
}

const vector<string>& TerrainEditor::getLoadedTerrainIDs()
{
	sort(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end());
	return _loadedTerrainIDs;
}
#include "terrain_editor.hpp"

#include <algorithm>

void TerrainEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool TerrainEditor::isLoaded()
{
	return _isEditorLoaded;
}

void TerrainEditor::unloadTerrainEntities()
{
	for(const auto& ID : _loadedTerrainIDs)
	{
		if(_fe3d.terrainEntity_isExisting(ID))
		{
			_fe3d.terrainEntity_delete(ID);
		}
	}
}

const vector<string>& TerrainEditor::getLoadedTerrainIDs()
{
	sort(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end());
	return _loadedTerrainIDs;
}
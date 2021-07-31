#include "water_editor.hpp"

#include <algorithm>

void WaterEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool WaterEditor::isLoaded()
{
	return _isEditorLoaded;
}

void WaterEditor::unloadWaterEntities()
{
	for (const auto& ID : _loadedWaterIDs)
	{
		if (_fe3d.waterEntity_isExisting(ID))
		{
			_fe3d.waterEntity_delete(ID);
		}
	}
}

const vector<string>& WaterEditor::getLoadedWaterIDs()
{
	std::sort(_loadedWaterIDs.begin(), _loadedWaterIDs.end());
	return _loadedWaterIDs;
}
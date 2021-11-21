#include "water_editor.hpp"

#include <algorithm>

void WaterEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool WaterEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void WaterEditor::unloadWaterEntities()
{
	for(const auto& ID : _loadedWaterIDs)
	{
		if(_fe3d.water_isExisting(ID))
		{
			_fe3d.water_delete(ID);
		}
	}
}

const vector<string>& WaterEditor::getLoadedWaterIDs()
{
	sort(_loadedWaterIDs.begin(), _loadedWaterIDs.end());
	return _loadedWaterIDs;
}
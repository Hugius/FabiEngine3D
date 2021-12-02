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

const vector<string>& WaterEditor::getLoadedWaterIDs()
{
	sort(_loadedWaterIDs.begin(), _loadedWaterIDs.end());
	return _loadedWaterIDs;
}
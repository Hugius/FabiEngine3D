#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool ModelEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedIDs()
{
	sort(_loadedModelIDs.begin(), _loadedModelIDs.end());
	return _loadedModelIDs;
}
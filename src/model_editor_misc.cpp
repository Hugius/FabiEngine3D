#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool ModelEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& ModelEditor::getLoadedIDs()
{
	sort(_loadedModelIds.begin(), _loadedModelIds.end());
	return _loadedModelIds;
}
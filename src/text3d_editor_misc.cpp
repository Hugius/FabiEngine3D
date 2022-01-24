#include "text3d_editor.hpp"

#include <algorithm>

void Text3dEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool Text3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Text3dEditor::getLoadedIDs()
{
	sort(_loadedTextIDs.begin(), _loadedTextIDs.end());
	return _loadedTextIDs;
}
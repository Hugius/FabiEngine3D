#include "text3d_editor.hpp"

#include <algorithm>

void Text3dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
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
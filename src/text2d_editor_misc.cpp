#include "text2d_editor.hpp"

#include <algorithm>

void Text2dEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool Text2dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Text2dEditor::getLoadedIDs()
{
	sort(_loadedTextIDs.begin(), _loadedTextIDs.end());
	return _loadedTextIDs;
}
#include "text_editor.hpp"

#include <algorithm>

void TextEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool TextEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& TextEditor::getLoadedIDs()
{
	sort(_loadedTextIDs.begin(), _loadedTextIDs.end());
	return _loadedTextIDs;
}
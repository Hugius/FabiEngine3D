#include "billboard_editor.hpp"

#include <algorithm>

void Quad3dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Quad3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad3dEditor::getLoadedIDs()
{
	sort(_loadedQuad3dIDs.begin(), _loadedQuad3dIDs.end());
	return _loadedQuad3dIDs;
}
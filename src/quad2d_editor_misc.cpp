#include "quad2d_editor.hpp"

#include <algorithm>

void Quad2dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Quad2dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad2dEditor::getLoadedIDs()
{
	sort(_loadedQuadIDs.begin(), _loadedQuadIDs.end());
	return _loadedQuadIDs;
}
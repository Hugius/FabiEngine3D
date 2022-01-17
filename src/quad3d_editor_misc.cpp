#include "quad3d_editor.hpp"

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
	sort(_loadedQuadIDs.begin(), _loadedQuadIDs.end());
	return _loadedQuadIDs;
}
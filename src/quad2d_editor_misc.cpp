#include "quad2d_editor.hpp"

#include <algorithm>

void QuadEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool QuadEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& QuadEditor::getLoadedIDs()
{
	sort(_loadedQuadIDs.begin(), _loadedQuadIDs.end());
	return _loadedQuadIDs;
}
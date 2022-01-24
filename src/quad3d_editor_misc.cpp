#include "quad3d_editor.hpp"

#include <algorithm>

void Quad3dEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool Quad3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad3dEditor::getLoadedIDs()
{
	sort(_loadedQuadIds.begin(), _loadedQuadIds.end());
	return _loadedQuadIds;
}
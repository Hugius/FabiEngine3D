#include "quad2d_editor.hpp"

#include <algorithm>

void Quad2dEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool Quad2dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad2dEditor::getLoadedIDs()
{
	sort(_loadedQuadIds.begin(), _loadedQuadIds.end());
	return _loadedQuadIds;
}
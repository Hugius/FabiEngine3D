#include "quad3d_editor.hpp"

#include <algorithm>

const bool Quad3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& Quad3dEditor::getLoadedIds()
{
	sort(_loadedQuadIds.begin(), _loadedQuadIds.end());
	return _loadedQuadIds;
}